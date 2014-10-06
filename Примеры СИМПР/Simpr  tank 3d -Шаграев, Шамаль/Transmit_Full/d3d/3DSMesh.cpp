#include "3DSMesh.h"


void Res3DSMesh::Create( LPDIRECT3DDEVICE9 pDevice )
{
	VisNormals.clear();
	// Выделяем главный объект.
	Tokenizator Tknz( ObjectsStr );
	Tknz.Begin( '|' );
	ModelObject = Model->GetModObjectByName( Tknz.NextToken() );
	assert( ModelObject );
	// Сливаем меши детей к родителю.
	for( ; ; )
	{
		std::string ChildName = Tknz.NextToken();
		if( !ChildName.empty() )
		{
			ModObject *Child = Model->GetModObjectByName( ChildName );
			assert( Child );
			if ( !Child ) 
				continue;
			ModelObject->MatGroupList.Merge( Child->MatGroupList );
		}
		else
			break;
	}
	// Заполняем вершинный буфер.
	int NumVertices = ModelObject->MatGroupList.GetVertexCount();
	HRESULT HR = pDevice->CreateVertexBuffer( sizeof(VertexData)*NumVertices, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &VertexBuffer, NULL );
	if( FAILED(HR) )
		DXError(HR, "Failed on IDirect3DDevice9::CreateVertexBuffer" );
	// Копируем данные из модели в вершинный буфер.
	VertexData *BufferData = 0;
	HR = VertexBuffer->Lock( 0, 0, (void**)&BufferData, 0 );
	if( FAILED(HR) )
		DXError(HR, "Failed on IDirect3DVertexBuffer9::Lock" );
	for( vec_iter<const ModTrimesh*> TriMesh(ModelObject->MatGroupList.TriMeshes); TriMesh; ++TriMesh )
	{
		for( int i=0; i < (*TriMesh)->VertexCount; i++, BufferData++ )
		{
			BufferData->Position	= (*TriMesh)->Vertices[i];
			BufferData->Normal		= (*TriMesh)->Normals[i];
			BufferData->U			= (*TriMesh)->TexCoords[i].U;
			BufferData->V			= 1.0f - (*TriMesh)->TexCoords[i].V;

			// Добавляем к данным BBoxа.
			Boundary.AddPoint( *(Vector3*)&(*TriMesh)->Vertices[i] );

			// DEBUGGING
			//VisNormals.push_back( VisNormal( *(Vector3*)&BufferData->Normal, *(Vector3*)&BufferData->Position ) );
		}
	}
	VertexBuffer->Unlock();
	// Заполняем список материалов.
	int i = 0;
	for( const ModMaterialGroupList::MaterialGroup *Cur=ModelObject->MatGroupList.GetMaterialGroups(); Cur; Cur = Cur->Next, i++ )
	{
		ModMaterial *ModMat = Model->GetMaterialByName( Cur->MatName );
		assert( ModMat );
		ResTexture *MatTexture = 0;
		if( ModMat->HasTexture )
		{
			MatTexture = new ResTexture( Model->TextureFolder + "/" + ModMat->TextureName );
			MatTexture = ResourceManager::GetInstance().Register( MatTexture, ModMat->TextureName );
		}
		// Создаем индексный буфер.
		LPDIRECT3DINDEXBUFFER9 IndexBuffer = 0;
		int NumIndices = Cur->Indices.size();
		HR = pDevice->CreateIndexBuffer( sizeof(DWORD)*NumIndices,
			D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &IndexBuffer, NULL );
		if( FAILED(HR) )
			DXError(HR, "Failed on IDirect3DDevice9::CreateIndexBuffer" );
		DWORD *IndexData = 0;
		HR = IndexBuffer->Lock( 0, 0, (void**)&IndexData, 0 );
		if( FAILED(HR) )
			DXError( HR, "Failed on IDirect3DIndexBuffer9::Lock" );
		memcpy( IndexData, &Cur->Indices[0], sizeof(DWORD)*NumIndices ); 
		IndexBuffer->Unlock();
	
		// Регистрируем материал.
		MatInternal NewMat = {IndexBuffer/*,VertexDecl*/,MatTexture,NumIndices/3};
		if( Materials.size() > (size_t)i )
			Materials[i] = NewMat;
		else
		{
			Materials.push_back( NewMat );

			// Увеличиваем значения счетчика ссылок на единицу,
			// чтобы при пересоздании меша текстуры не создавались заново.
			MatTexture->AddRef();
		}
	}
	if( !pVertexDecl )
	{
		D3DVERTEXELEMENT9 VertexFmt[] =
		{
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};
		HR = pDevice->CreateVertexDeclaration( VertexFmt, &pVertexDecl );
		assert( !FAILED(HR) );
	}
	pSavedDevice = pDevice;
}

// Рисование через FFP.
void Res3DSMesh::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	VertexBuffer->GetDevice( &pDevice );
	pDevice->SetVertexDeclaration( pVertexDecl );
	pDevice->SetStreamSource( 0, VertexBuffer, 0, sizeof(VertexData) );
	int VertexCount = ModelObject->MatGroupList.GetVertexCount();
	for( vec_iter<MatInternal> Mat(Materials); Mat; ++Mat )
	{
		if( Mat->Texture )
			Mat->Texture->SetForRendering( 0 );

		pDevice->SetIndices( Mat->pIndexBuffer );
		pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, VertexCount, 0, Mat->NumPrimitives );
	}
	pDevice->Release();
}

void Res3DSMesh::DrawMesh( MaterialBin *Bin )
{
	HRESULT HR =
		pSavedDevice->DrawIndexedPrimitive( 
			D3DPT_TRIANGLELIST, Bin->BaseVertexIndex,
			Bin->MinVertexIndex,
			Bin->NumVertices,
			Bin->StartIndex,
			Bin->NumPrimitives );

	assert( !FAILED(HR) );
}

// Рисование через PPL.
void Res3DSMesh::Draw( ResMaterial *Mat )
{
	DrawCallDelegate<MaterialBin*> DrawSubset(
		boost::bind(&rand), // Просто фунция без аргументов.
		boost::bind(&Res3DSMesh::DrawMesh,this,_1)
	);

	pSavedDevice->SetVertexDeclaration( pVertexDecl );
	pSavedDevice->SetStreamSource( 0, VertexBuffer, 0, sizeof(VertexData) );
	int VertexCount = ModelObject->MatGroupList.GetVertexCount();
	for( vec_iter<MatInternal> ModelMat(Materials); ModelMat; ++ModelMat )
	{
		if( ModelMat->Texture )
			Mat->SetDiffuseMap( ModelMat->Texture );
		else
		{
			// TODO: Set dummy texture here.
		}

		MaterialBin DrawBin;
		DrawBin.NumVertices = VertexCount;
		DrawBin.NumPrimitives = ModelMat->NumPrimitives;

		pSavedDevice->SetIndices( ModelMat->pIndexBuffer );

		Mat->Draw( DrawSubset, &DrawBin );
	}
}

void Res3DSMesh::Destroy()
{
	if( VertexBuffer )
	{
		VertexBuffer->Release();
		VertexBuffer = 0;
	}
	for( vec_iter<MatInternal> Mat(Materials); Mat; ++Mat )
	{
		if( Mat->pIndexBuffer )
			Mat->pIndexBuffer->Release();
		if( Mat->Texture )
			Mat->Texture->Release();
	}
}

const ModVector& Res3DSMesh::GetRotCenter() const
{
	return *(const ModVector*)&ModelObject->Meshes[0]->Local[3];
}

const BBox& Res3DSMesh::GetBBox() const
{
	return Boundary;
}

Res3DSMesh::~Res3DSMesh()
{
	for( vec_iter<MatInternal> Mat(Materials); Mat; ++Mat )
	{
		if( Mat->Texture )
			Mat->Texture->Release();
	}
	if( pVertexDecl )
	{
		pVertexDecl->Release();
		pVertexDecl = 0;
	}
	ResourceManager::GetInstance().Unregister( this );
}