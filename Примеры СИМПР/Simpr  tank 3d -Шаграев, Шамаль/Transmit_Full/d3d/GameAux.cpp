#include "GameAux.h"

GAuxiliary::GAuxiliary() : MaxSize(10000)
{
	AuxMesh = ResourceManager::GetInstance().Register(
		new ResDynamicMesh<AuxVF>( MaxSize, MaxSize*3 ), "AuxMesh" );

	AuxMat = ResourceManager::GetInstance().Register(
		new ResMaterial( "Effects/AuxMat.fx", SceneManager::GetInstance().LightParams ),
		"Effects/AuxMat.fx" );
}

GAuxiliary::~GAuxiliary()
{
	AuxMesh->Release();
	AuxMat->Release();
}

void GAuxiliary::BeginFrame( float CurTime )
{
	Clear();
}

void GAuxiliary::EndFrame( float CurTime )
{
}

void GAuxiliary::DrawBBox( const BBox &Box )
{
	int CurSize = Vertices.size();
	if( CurSize < MaxSize )
	{
		Vertices.resize( CurSize + 8 );

		WORD IndexArr[] = {
			1,0,4,1,4,5,	2,1,5,2,5,6,	3,2,6,3,6,7,	0,3,7,0,7,4
		};

		AuxVF *BoxVerts = &Vertices[CurSize];

		BoxVerts[0].Position() = Box.Min;
		BoxVerts[1].Position() = Vector3( Box.Min.x, Box.Min.y, Box.Max.z );
		BoxVerts[2].Position() = Vector3( Box.Max.x, Box.Min.y, Box.Max.z );
		BoxVerts[3].Position() = Vector3( Box.Max.x, Box.Min.y, Box.Min.z );
		BoxVerts[4].Position() = Vector3( Box.Min.x, Box.Max.y, Box.Min.z );
		BoxVerts[5].Position() = Vector3( Box.Min.x, Box.Max.y, Box.Max.z );
		BoxVerts[6].Position() = Box.Max;
		BoxVerts[7].Position() = Vector3( Box.Max.x, Box.Max.y, Box.Min.z );

		for( int i=0; i < 8; i++ )
			BoxVerts[i].Color4UB() = D3DCOLOR_RGBA(255,0,0,255);

		for( WORD *I = IndexArr; I < IndexArr + 24; ++I )
			Indices.push_back( *I + CurSize );

		TrilistBin.Add( CurSize, 8, 8 );
	}
}

void GAuxiliary::DrawOBBox( const OBBox& Box )
{
	int CurSize = Vertices.size();
	if( CurSize < MaxSize )
	{
		Vertices.resize( CurSize + 8 );

		WORD IndexArr[] = {
			0,2,6,0,6,4,	2,3,7,2,7,6,	3,1,5,3,5,7,	1,0,4,1,4,5
		};

		AuxVF *BoxVerts = &Vertices[CurSize];
		D3DXMATRIX L2World;
		D3DXMatrixInverse( &L2World, NULL, &Box.LocalMat );

		for( int i=0; i < 2; i++ )
			for( int j=0; j < 2; j++ )
				for( int k=0; k < 2; k++ )
				{
					BoxVerts[i*4+j*2+k].Position() = 
						Transform( L2World, Vector3( Box.Box.GetExtent(j).x, Box.Box.GetExtent(i).y, Box.Box.GetExtent(k).z ) );
				}

		for( int i=0; i < 8; i++ )
			BoxVerts[i].Color4UB() = D3DCOLOR_RGBA(255,0,0,255);

		for( WORD *I = IndexArr; I < IndexArr + 24; ++I )
			Indices.push_back( *I + CurSize );

		TrilistBin.Add( CurSize, 8, 8 );
	}
}

void GAuxiliary::DrawLine( const Vector3& From, const Vector3& To, D3DXCOLOR Col )
{
	AuxVF V1, V2;
	V1.Position() = From;
	V2.Position() = To;
	V1.Color4UB() = Col;
	V2.Color4UB() = Col;

	int Ind = Vertices.size();
	if( Ind >= MaxSize )
		return;
	Vertices.push_back( V1 );
	Vertices.push_back( V2 );
	LnIndices.push_back( Ind );
	LnIndices.push_back( Ind+1 );

	LinesBin.NumIndices += 2;
	LinesBin.NumPrimitives += 1;
	LinesBin.NumVertices = Ind+1;
}

// Рисует репер.
void GAuxiliary::DrawCoords( const Vector3& I, const Vector3& J, const Vector3& K, const Vector3& Org )
{
	DrawLine( Org, Org + 2.5f*I, D3DCOLOR_XRGB(255,0,0) );
	DrawLine( Org, Org + 2.5f*J, D3DCOLOR_XRGB(0,255,0) );
	DrawLine( Org, Org + 2.5f*K, D3DCOLOR_XRGB(0,0,255) );
}

void GAuxiliary::Draw()
{
	int NumIndices = TrilistBin.NumIndices + LinesBin.NumIndices;
	if( NumIndices )
	{
		// Соединяем все буферы индексов.
		LinesBin.StartIndex = Indices.size();
		std::copy( LnIndices.begin(), LnIndices.end(), std::back_inserter(Indices) );

		AuxVF *VertBuffer = AuxMesh->Begin( true, true, Vertices.size(), NumIndices );
		std::copy( Vertices.begin(), Vertices.end(), VertBuffer );
		std::for_each( Indices.begin(), Indices.end(), boost::bind(&ResDynamicMesh<AuxVF>::Index, AuxMesh, _1) );
		AuxMesh->End();
		
		// Рисуем все треугольники.
		if( TrilistBin.NumPrimitives )
			AuxMat->Draw( AuxMesh, &TrilistBin );

		if( LinesBin.NumPrimitives )
		{
			// Рисуем все линии.
			LinesBin.NumVertices = LinesBin.NumVertices - LinesBin.MinVertexIndex + 1;
			AuxMat->Draw(
				DrawCallDelegate<MaterialBin*>( AuxMesh,
												&ResDynamicMesh<AuxVF>::SetupDIPCall,
												&ResDynamicMesh<AuxVF>::DrawIPWithType<D3DPT_LINELIST>
											  ),
				&LinesBin
			);
		}
	}
}