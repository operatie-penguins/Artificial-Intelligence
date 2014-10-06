#pragma once

#include "ObjMain.h"
#include "Rendering.h"
#include "DynMesh.h"
#include "Material.h"
#include "Scene.h"
#include "Camera.h"
#include "GameAux.h"

// Точечный источник света.
class GLight : public GObject
{
	float	Intensity;
	DWORD	Color;
public:
	GLight()
	{
		Register( "GLight" );
	}
	~GLight()
	{
		Unregister( "GLight" );
	}
};

struct GLevelBlock
{
public:
	BBox		Block;
	int			MaterialId;
	int			NoDraw;

	// Для сортировки.
	bool operator<( const GLevelBlock& Rhs )
	{
		return( MaterialId < Rhs.MaterialId );
	}
};

// DEBUGGING
struct TNBBasis
{
	Vector3 Tangent;
	Vector3 Normal;
	Vector3 Binormal;
	Vector3 VPos;

	TNBBasis( const Vector3& T, const Vector3& N, const Vector3& B, const Vector3& Pos ) 
		: Tangent(T), Normal(N), Binormal(B), VPos(Pos)
	{}
	void Draw();
};

// Содержит статическую геометрию уровня.
class GLevelData : public GRenderable
{
	std::vector<GLevelBlock>	Blocks;
	Vector3						DefBlockSize;
	typedef TVertex<3,3,0,2,0,3,3>	LVF;
	ResDynamicMesh<LVF>			*LevelMesh;
	bool						HasVertexData;
	// Данные о материалах.
	std::vector<ResMaterial*>	OpaqueMaterials,
								TranslucentMaterials;
	// Данные о полупрозрачных объектах.
	std::vector<MaterialBin>	TranslucentBins;
	std::vector<GLevelBlock*>	TranslucentBlocks;
	BBox						LevelBB;
	// Маска для выделения прозрачных материалов.
	static const int			MatTranslMask = 0x2000000;
public:
	GLevelData()
		: DefBlockSize( 40.0f, 80.0f, 20.0f ), HasVertexData(false)
	{
		Register( "GLevelData" );
	}
	enum BlockAlign
	{
		BLOCK_ALIGN_X = 0,
		BLOCK_ALIGN_Z = 1
	};
	// Установить новые размеры блока.
	void SetBlockSize( const Vector3& SizeXYZ )
	{
		DefBlockSize = SizeXYZ;
	}
	// Добавляет блок к данным уровня. Возвращает номер добалвенного блока.
	int AddBlock( const Vector3& Center, int Align, const std::string& MaterialName = "LevelMatGeneric.fx" );
	// Включает или выклюяает рисование блока.
	void SetBlockState( int Block, bool IsEnabled );
	void CreateVertexData( ResDynamicMesh<LVF> *Mesh );
	void SetSky( const std::string& SkyMaterialName, float SkydomeRadius );
	void DrawSky();
	void DrawTranslucentSurfaces();
	virtual void Draw();
	virtual void BeginFrame( float Delta )
	{}
	virtual void EndFrame( float Delta )
	{}
	virtual const BBox& GetOBBox() const
	{
		return LevelBB;
	}
	virtual const BBox& GetBBox() const
	{
		return LevelBB;
	}
	virtual ~GLevelData();

	BBox GetBlockOBBox(int i)
	{
		return Blocks[i].Block;
	}
private:
	void CreateIndicesForBlock( int BlockNum, MaterialBin *Bin );

	std::vector<TNBBasis> TNBs;
};

class Font
{
	std::string		Name;
	int				LineHeight;
	int				Base;
	int				ScaleW;
	int				ScaleH;
	int				Pages;
	bool			Packed;
	std::string		TextureFile;
	struct CharDesc
	{
		short	X;
		short	Y;
		short	Width;
		short	Height;
		short	XOffset;
		short	YOffset;
		short	XAdvance;
		short	Page;
	};
	std::map<int, CharDesc>				CharInfo;
	bool								HasKernings;
	stdext::hash_map< int,
		stdext::hash_map<int, short> >	Kernings;		// Таблица межсимвольных интревалов.
	ResTexture							*FontTexture;	
	ResDynamicMesh<FontVertex>			*FontMesh;
	ResMaterial							*FontMat;
	int									MaxMsgLen;

	void ParseFontFile( std::istream& Inp );
public:
	Font( const std::string& FontFolder, const std::string& FontFile, float ViewportWidth, float ViewportHeight, int MaxMessageLen = 256 );
	void DrawLine( float X, float Y, const std::string& Text );
	~Font();
};


class SkyDome
{
	typedef TVertex<3,0,false,2> VF;
	ResDynamicMesh<VF>	*DomeMesh;
	ResMaterial			*SkyMat;
	MaterialBin			WorkBin;
	float				Radius;
	int					TessLev;

	void FillVertexData( ResDynamicMesh<VF> *Mesh )
	{
		// Creating a hemisphere mesh.
		int TessLev = 20;
		int TessLev21 = TessLev*2+1;
		int NumVertices = (TessLev+1)*TessLev21;
		int NumIndices = TessLev*2*(TessLev*6);

		float DPhi = Constants::Pi2/(TessLev*2);
		float DTheta = Constants::HalfPi/TessLev;
		float Phi, Theta = 0;
		VF *Vertices = Mesh->Begin( true, true );
		for( int i=0; i <= TessLev; i++, Theta += DTheta )
		{
			Phi = 0;
			for( int j=0; j <= 2*TessLev; j++, Phi += DPhi, Vertices++ )
			{
				Vertices->Position().X = Radius*cos(Phi)*cos(Theta);
				Vertices->Position().Z = Radius*sin(Phi)*cos(Theta);
				Vertices->Position().Y = Radius*sin(Theta);
				Vertices->TexCoord0().X = Phi / Constants::Pi2;
				Vertices->TexCoord0().Y = Theta / Constants::HalfPi;
			}
		}
		// Create indices.
		for( int i = 0; i < 2*TessLev; i++ )
		{
			for( int j = 0; j < TessLev; j++ )
			{
				int I1 = j*TessLev21 + i, I2 = I1 + TessLev21;		
				Mesh->Index( I1 );
				Mesh->Index( I1+1 );
				Mesh->Index( I2 );
				Mesh->Index( I2 );
				Mesh->Index( I1+1 );
				Mesh->Index( I2+1 );
			}
		}
		Mesh->End();
	}

public:
	SkyDome( const std::string &SkyMaterial, float DomeRadius, int TessLevel = 20 )
		: Radius(DomeRadius), TessLev(TessLevel)
	{
		int TessLev21 = TessLev*2+1;
		int NumVertices = (TessLev+1)*TessLev21;
		int NumIndices = TessLev*2*(TessLev*6);
		DomeMesh = ResourceManager::GetInstance().Register(
			new ResDynamicMesh<VF>( NumVertices, NumIndices, boost::bind(&SkyDome::FillVertexData,this,_1) ),
			"DomeMesh" );

		WorkBin.MinVertexIndex = 0;
		WorkBin.NumVertices = NumVertices;
		WorkBin.NumPrimitives = NumIndices/3;
		WorkBin.StartIndex = 0;
		WorkBin.NumIndices = NumIndices;

		SkyMat = ResourceManager::GetInstance().Register( 
			new ResMaterial("Sky.fx", SceneManager::GetInstance().LightParams ),
			"SkyMat" );
	}
	void DrawSky()
	{
		SkyMat->Draw( DomeMesh, &WorkBin );
	}

	~SkyDome()
	{
		DomeMesh->Release();
		SkyMat->Release();
	}
};

//-----------------------------------------------------------------------------------------------------------