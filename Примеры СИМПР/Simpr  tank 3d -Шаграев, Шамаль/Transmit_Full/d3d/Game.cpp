#include "ObjMain.h"
#include "Game.h"
#include <fstream>

std::map< std::string,std::set<GObject*> > GObject::ObjectBins;

int GLevelData::AddBlock( const Vector3& Center, int Align, const std::string& MaterialName )
{
	Blocks.push_back( GLevelBlock() );
	GLevelBlock& NewBlock = Blocks.back();
	Vector3 BlockSize;
	switch( Align )
	{
		case BLOCK_ALIGN_X:
			BlockSize = DefBlockSize;
			break;

		case BLOCK_ALIGN_Z:
			BlockSize = DefBlockSize.Pack( 2, 1, 0 );
			break;
		default:
			assert( 0 );
	}
	NewBlock.NoDraw = false;
	NewBlock.Block = BBox( Center - 0.5f*BlockSize, Center + 0.5f*BlockSize );
	NewBlock.Block += Vector3(0, 0.5f*DefBlockSize.y, 0);
	LevelBB += NewBlock.Block;
	// Создание материала.
	// Сначала ищем материал среди уже загруженных.
	ResMaterial *RegMat = 0;
	std::vector<ResMaterial*>::iterator Found
		= std::find_if( OpaqueMaterials.begin(), OpaqueMaterials.end(), ResMaterial::Cmp(MaterialName) );
	if( Found == OpaqueMaterials.end() )
	{
		Found = std::find_if( TranslucentMaterials.begin(), TranslucentMaterials.end(), ResMaterial::Cmp(MaterialName) );
		if( Found == TranslucentMaterials.end() )
		{
			// Нигде не обнаружен, загружаем материал.
			ResMaterial *NewMat = new ResMaterial( MaterialName, SceneManager::GetInstance().LightParams );
			NewMat = ResourceManager::GetInstance().Register( NewMat, MaterialName );
			if( NewMat->IsTranslucent() )
			{
				TranslucentMaterials.push_back( NewMat );
				NewBlock.MaterialId = TranslucentMaterials.size()-1;
			}
			else
			{
				OpaqueMaterials.push_back( NewMat );
				NewBlock.MaterialId = OpaqueMaterials.size()-1;
			}
			RegMat = NewMat;
		}
		else
		{
			NewBlock.MaterialId = Found - TranslucentMaterials.begin();
			RegMat = *Found;
		}
	}
	else
	{
		NewBlock.MaterialId = Found - OpaqueMaterials.begin();
		RegMat = *Found;
	}
	if( RegMat->IsTranslucent() )
		NewBlock.MaterialId |= MatTranslMask;
	return Blocks.size()-1;
}

void GLevelData::CreateVertexData( ResDynamicMesh<LVF> *Mesh )
{
	TNBs.clear();
	LVF *LevelData = Mesh->Begin( true, false );
	for( std::vector<GLevelBlock>::iterator It = Blocks.begin(); It != Blocks.end(); ++It, LevelData += 20 )
	{
		BBox& Block = It->Block;

		// Вычисляем текстурные координаты.
		float T = (Block.Max.z - Block.Min.z) / (Block.Max.x - Block.Min.x + Block.Max.z - Block.Min.z);
		float TC[20][2] = 
		{
			{0, 1}, {T, 1}, {0, 0}, {T, 0},
			{1-T, 1}, {1, 1}, {1-T, 0}, {1, 0},
			{0, 1}, {1-T,1},  {0, 0}, {1-T, 0},
			{T,1}, {1,1}, {T,0}, {1,0},
			{0,T}, {1-T,T}, {0,0}, {1-T,0}
		};

		// Локальную система координат полигона (для 3-х плоскостей).
		Vector3 TNB[][3] =
		{
			{ Vector3(0,0,1), Vector3(-1,0,0), Vector3(0,-1,0) },
			{ Vector3(-1,0,0), Vector3(0,0,-1), Vector3(0,-1,0) },
			{ Vector3(1,0,0), Vector3(0,1,0), Vector3(0,0,1) }
		};
		
		for( int n=0; n < 8; n++ )
		{
			int i = (n >> 2) & 1, j = (n >> 1) & 1, k = n & 1;
			LevelData[n].Position() = Vector3( Block.GetExtent(i).x, Block.GetExtent(j).y, Block.GetExtent(k).z );
			LevelData[n].TexCoord0() = Vector2( TC[n][0], TC[n][1] );
			LevelData[n].Tangent() = (i ? -1.0f : 1.0f) * TNB[0][0];
			LevelData[n].Normal() = (i ? -1.0f : 1.0f) * TNB[0][1];
			LevelData[n].Binormal() = TNB[0][2];
		}
		for( int n=8; n < 16; n++ )
		{
			int i = (n >> 2) & 1, j = (n >> 1) & 1, k = n & 1;
			LevelData[n].Position() = Vector3( Block.GetExtent(k).x, Block.GetExtent(j).y, Block.GetExtent(i).z );
			LevelData[n].TexCoord0() = Vector2( TC[n][0], TC[n][1] );
			LevelData[n].Tangent() = (i ? -1.0f : 1.0f) * TNB[1][0];
			LevelData[n].Normal() = (i ? -1.0f : 1.0f) * TNB[1][1];
			LevelData[n].Binormal() = TNB[1][2];
		}
		for( int n=16; n < 20; n++ )
		{
			int j = (n >> 1) & 1, k = n & 1;
			LevelData[n].Position() = Vector3( Block.GetExtent(k).x, Block.GetExtent(1).y, Block.GetExtent(j).z );
			LevelData[n].TexCoord0() = Vector2( TC[n][0], TC[n][1] );
			LevelData[n].Tangent() = TNB[2][0];
			LevelData[n].Normal() = TNB[2][1];
			LevelData[n].Binormal() = TNB[2][2];
		}

		// Копируем TNB базисы для визуализации.
		/*for( int i=0; i < 8; i++ )
		{
			TNBs.push_back( 
				TNBBasis(
				LevelData[i].Tangent(),
				LevelData[i].Normal(),
				LevelData[i].Binormal(),
				LevelData[i].Position() )
			);
		}*/
	}
	Mesh->End();
}

// Предикат для упорядочивания двух блоков по удаленности от наблюдателя.
static bool BlockCmpFunc( const GLevelBlock* Lhs, const GLevelBlock* Rhs )
{
	Vector3 EyePos;
	SceneManager::GetInstance().GetEyePos( EyePos );
	float D1 = (0.5f*(Lhs->Block.Min+Lhs->Block.Max)-EyePos).Length();
	float D2 = (0.5f*(Rhs->Block.Min+Rhs->Block.Max)-EyePos).Length();
	return( D1 > D2 );
}

void TNBBasis::Draw()
{
	GAuxiliary::Get().DrawCoords( Tangent, Normal, Binormal, VPos );
}

void GLevelData::CreateIndicesForBlock( int BlockNum, MaterialBin *Bin )
{
	// Набор индексов для одиночного бокса.
	int IndexTemplate[] =
	{
		1, 0, 2,	1, 2, 3,
		4, 5, 7,	4, 7, 6,

		8, 9, 11,	11, 10, 8,
		12, 14, 13, 13, 14, 15,

		16, 17, 19, 19, 18, 16

	};

	int BaseVertexNum = BlockNum*20;
	for( int i=0; i < 30; i++ )
	{
		LevelMesh->Index( BaseVertexNum + IndexTemplate[i] );
	}
	Bin->Add( BaseVertexNum, 20, 10 );
}

void GLevelData::Draw()
{
	if( !HasVertexData )
	{
		// Сначала сортируем по материалам.
		std::sort( Blocks.begin(), Blocks.end() );
		// Создаем и заполняем вершинный буфер.
		// FIXME: необходимо делать это в более подходящем месте.
		LevelMesh = ResourceManager::GetInstance().Register(
			new ResDynamicMesh<LVF>( Blocks.size()*20, Blocks.size()*30,
									boost::bind(&GLevelData::CreateVertexData,this,_1) ),
			"LevelMesh" );
		HasVertexData = true;
	}

	// Создаем индексы для непрозрачных материалов.
	LevelMesh->Begin( false, true );
	std::vector<MaterialBin>	MaterialBins;
	MaterialBins.resize( OpaqueMaterials.size() );
	for( unsigned i=0; i < Blocks.size(); i++ )
	{
		if( Blocks[i].NoDraw )
			continue;
		if( Blocks[i].MaterialId & MatTranslMask )
			continue;
		MaterialBin *Bin = &MaterialBins[Blocks[i].MaterialId];
		CreateIndicesForBlock( i, Bin );
	}
	//MaterialBins[0].MinVertexIndex = 0;
	MaterialBins[0].StartIndex = 0;
	for( unsigned i = 1; i < OpaqueMaterials.size(); i++ )
	{
		//MaterialBins[i].MinVertexIndex = MaterialBins[i-1].MinVertexIndex + MaterialBins[i-1].NumVertices;
		MaterialBins[i].StartIndex = MaterialBins[i-1].StartIndex + MaterialBins[i-1].NumIndices;
	}

	// Создаем индексы для полупрозрачных материалов.
	// Создаем массив указателей на полупрозрачные блоки и сортируем его.
	TranslucentBlocks.clear();
	for( unsigned i=Blocks.size()-1; i >= 0; i-- )
	{
		if( !(Blocks[i].MaterialId & MatTranslMask) )
			break;
		TranslucentBlocks.push_back( &Blocks[i] );
	}
	std::sort( TranslucentBlocks.begin(), TranslucentBlocks.end(), BlockCmpFunc );

	// Добавляем индексы.
	TranslucentBins.clear();
	int PrevMatId = -1;
	for( unsigned i=0; i < TranslucentBlocks.size(); i++ )
	{
		if( TranslucentBlocks[i]->NoDraw )
			continue;
		GLevelBlock *CurBlock = TranslucentBlocks[i];
		int MaterialId = CurBlock->MaterialId & ~MatTranslMask;
		if( PrevMatId != MaterialId )
		{
			MaterialBin NewBin;
			NewBin.StartIndex = LevelMesh->NumUsedIndices();
			TranslucentBins.push_back( NewBin );
		}
		// Определяем номер первой вершины блока в вершинном буфере.
		int BlockNum = CurBlock - &Blocks.front();
		CreateIndicesForBlock( BlockNum, &TranslucentBins.back() );
		PrevMatId = MaterialId;
	}
	LevelMesh->End();

	// Рисуем все непрозрачные поверхности.
	for( unsigned int i=0; i < OpaqueMaterials.size(); i++ )
	{
		OpaqueMaterials[i]->Draw( LevelMesh, &MaterialBins[i] ); 
	}

	// Вспомогательная визуализация.
	/*for( std::vector<TNBBasis>::iterator I = TNBs.begin(); I != TNBs.end(); ++I )
	{
		I->Draw();
	}*/
}

void GLevelData::DrawTranslucentSurfaces()
{
	if( !HasVertexData )
		return;
	int PrevMatId = -1;
	for( unsigned i = 0; i < TranslucentBlocks.size(); i++ )
	{
		GLevelBlock *CurBlock = TranslucentBlocks[i];
		int MaterialId = CurBlock->MaterialId & ~MatTranslMask;
		// Идущие подряд одинаковые материалы объединены в одной корзине.
		if( PrevMatId == MaterialId )
			continue;
		TranslucentMaterials[MaterialId]->Draw( LevelMesh, &TranslucentBins[i] );
		PrevMatId = MaterialId;
	}
}

void GLevelData::SetBlockState( int Block, bool IsEnabled )
{
	assert( (unsigned)Block < Blocks.size() );
	Blocks[Block].NoDraw = !IsEnabled;
}

GLevelData::~GLevelData()
{
	if( HasVertexData )
		LevelMesh->Release();
	std::vector<ResMaterial*> Materials;
	Materials.insert( Materials.begin(), OpaqueMaterials.begin(), OpaqueMaterials.end() );
	Materials.insert( Materials.end(), TranslucentMaterials.begin(), TranslucentMaterials.end() );
	for( unsigned int i=0; i < Materials.size(); i++ )
		Materials[i]->Release();
	Unregister( "GLevelData" );
}

//-------------------------------------------------------------------------------------------------------------

Font::Font( const std::string& FontFolder, 
		   const std::string& FontFile,
		   float ViewportWidth,
		   float ViewportHeight,
		   int MaxMessageLen ) : Name(FontFile), HasKernings(false), MaxMsgLen(MaxMessageLen)
{
	std::fstream FF( (FontFolder + "/" + FontFile).c_str(), std::ios::in );
	if ( !FF.fail() )
		ParseFontFile( FF );
	else
	{
		// TODO: Использовать стандартный шрифт.
		AppError() << "File not found: " << FontFile;
	}
	// Создаем ресурсы.
	FontTexture = ResourceManager::GetInstance().Register(
		new ResTexture( FontFolder + "/" + TextureFile ), TextureFile
	);
	FontMesh = ResourceManager::GetInstance().Register(
		new ResDynamicMesh<FontVertex>( MaxMsgLen*6, MaxMsgLen*2 ),
		Name
	);
	FontMat = ResourceManager::GetInstance().Register( new ResMaterial("Font.fx"), "Font.fx" );
	FontMat->AttachTexture( FontTexture );
	FontMat->SetFloatParameter( "ScreenWidth", ViewportWidth );
	FontMat->SetFloatParameter( "ScreenHeight", ViewportHeight );
}

// Разбор файла со шрифтом.
void Font::ParseFontFile( std::istream& Inp )
{
	while( !Inp.eof() )
	{
		std::string Line;
		std::stringstream Tokens;
		std::getline( Inp, Line );
		Tokens << Line;
		std::string Tkn;
		Tokens >> Tkn;
		if( Tkn == "common" )
		{
			while( !Tokens.eof() )
			{
				Tokens >> Tkn;
				int Len = Tkn.find( '=' );
				std::string Key = Tkn.substr( 0, Len );
				std::string Val = Tkn.substr( Len+1 );
				std::stringstream Value;
				Value << Val;
				if( Key == "lineHeight" )
					Value >> LineHeight;
				else if( Key == "base" )
					Value >> Base;
				else if( Key == "scaleW" )
					Value >> ScaleW;
				else if( Key == "scaleH" )
					Value >> ScaleH;
				else if( Key == "pages" )
					Value >> Pages;
				else if( Key == "packed" )
					Value >> Packed;
			}
			// Обработка блока.
			if( Packed )
				AppError() << "Packed font formats are not supported : " << Name;
			if( Pages > 1 )
				AppError() << "Fonts with more then 1 pages are not supported : " << Name;
		}
		else if( Tkn == "page" )
		{
			while ( !Tokens.eof() )
			{
				Tokens >> Tkn;
				int Len = Tkn.find( '=' );
				std::string Key = Tkn.substr( 0, Len );
				std::string Val = Tkn.substr( Len+1 );
				std::stringstream Value;
				Value << Val;
				if( Key == "file" )
				{
					Value >> TextureFile;
					// Удаляем кавычки.
					TextureFile.erase( 0, 1 );
					TextureFile.erase( TextureFile.length()-1 );
				}
			}
		}
		else if( Tkn == "char" )
		{
			CharDesc Desc;
			int	Id;
			while ( !Tokens.eof() )
			{
				Tokens >> Tkn;
				int Len = Tkn.find( '=' );
				std::string Key = Tkn.substr( 0, Len );
				std::string Val = Tkn.substr( Len+1 );
				std::stringstream Value;
				Value << Val;
				if( Key == "id" )
					Value >> Id;
				else if( Key == "x" )
					Value >> Desc.X;
				else if( Key == "y" )
					Value >> Desc.Y;
				else if( Key == "width" )
					Value >> Desc.Width;
				else if( Key == "height" )
					Value >> Desc.Height;
				else if( Key == "xoffset" )
					Value >> Desc.XOffset;
				else if( Key == "yoffset" )
					Value >> Desc.YOffset;
				else if( Key == "xadvance" )
					Value >> Desc.XAdvance;
				else if( Key == "page" )
					Value >> Desc.Page;
			}
			CharInfo[Id] = Desc;
		}
		else if( Tkn == "kernings" )
			HasKernings = true;
		else if( Tkn == "kerning" )
		{
			int First, Second, Amount;
			while ( !Tokens.eof() )
			{
				Tokens >> Tkn;
				int Len = Tkn.find( '=' );
				std::string Key = Tkn.substr( 0, Len );
				std::string Val = Tkn.substr( Len+1 );
				std::stringstream Value;
				Value << Val;
				if( Key == "first" )
					Value >> First;
				else if( Key == "second" )
					Value >> Second;
				else if( Key == "amount" )
					Value >> Amount;
			}
			Kernings[First][Second] = Amount;
		}
	}
}

// Рисует текст. X,Y - экранные координаты, O - левый нижний угол видимой области.
void Font::DrawLine( float X, float Y, const std::string& Text )
{
	unsigned int Len = Text.length();
	assert( Len <= (unsigned)MaxMsgLen );
	FontVertex *Vertices = FontMesh->Begin( true, false, Len*6, Len*2  );
	for( unsigned int i = 0; i < Text.length(); i++, Vertices += 6 )
	{
		CharDesc *Ch = &CharInfo[ Text[i] ];
		FontVertex V0, V1, V2, V3;

		V0.X = X + Ch->XOffset;
		V0.Y = Y - Ch->YOffset;
		V0.U = (float)Ch->X / ScaleW;
		V0.V = (float)Ch->Y / ScaleH;

		V1.X = V0.X + (float)Ch->Width;
		V1.Y = V0.Y;
		V1.U = V0.U + (float)Ch->Width/ScaleW;
		V1.V = V0.V;

		V2.X = V1.X;
		V2.Y = V1.Y - (float)Ch->Height;
		V2.U = V1.U;
		V2.V = V1.V + (float)Ch->Height/ScaleH;

		V3.X = V0.X;
		V3.Y = V2.Y;
		V3.U = V0.U;
		V3.V = V2.V;

		Vertices[0] = V0;
		Vertices[1] = V1;
		Vertices[2] = V2;
		Vertices[3] = V0;
		Vertices[4] = V2;
		Vertices[5] = V3;

		X += Ch->XAdvance;
		if( HasKernings && i < Len )
			X += Kernings[Text[i]][Text[i+1]];
	}
	FontMesh->End();
	FontMat->Draw( FontMesh, Len*2 );
}

Font::~Font()
{
	FontTexture->Release();
	FontMesh->Release();
	FontMat->Release();
}

//-------------------------------------------------------------------------------------------------------