#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include "Utils.h"
#include <errno.h>
#include <algorithm>

#pragma once

struct ChunkInfo
{
	WORD Id;
	DWORD Len;
	FILE *F;

	ChunkInfo( FILE *Model ) : F(Model)
	{
		Next();
	}
	void Next()
	{
		fread( &Id, sizeof(WORD), 1, F );
		fread( &Len, sizeof(DWORD), 1, F );
	}
	void Skip()
	{
		fseek( F, Len-6, SEEK_CUR );
	}
	void ReadString( std::string& Str )
	{
		while( char C = fgetc( F ) )
			Str += C;
	}
};

enum ModFileStructure
{
	M3DMAGIC = 0x4D4D,
		MDATA = 0x3D3D,
			MASTER_SCALE = 0x0100,
			MAT_ENTRY = 0xAFFF,
				MAT_NAME = 0xA000,
				MAT_AMBIENT = 0xA010,
					COLOR_24 = 0x0011,
					LIN_COLOR_24 = 0x0012,
				MAT_DIFFUSE = 0xA020,
				MAT_SPECULAR = 0xA030,
				MAT_SHININESS = 0xA040,
				MAT_TRANSPARENCY = 0xA050,
				MAT_TEXMAP = 0xA200,
					MAT_MAPNAME = 0xA300,
					MAT_MAP_USCALE = 0xA354,
					MAT_MAP_VSCALE = 0xA356,
					MAT_MAP_UOFFSET = 0xA358,
					MAT_MAP_VOFFSET = 0xA35A,
					MAT_MAP_ANG = 0xA35C,
			NAMED_OBJECT = 0x4000,
				N_TRIOBJECT = 0x4100,
					POINT_ARRAY = 0x4110,
					FACE_ARRAY = 0x4120,
						MSH_MAT_GROUP = 0x4130,
						SMOOTH_GROUP = 0x4150,
					TEX_VERTS = 0x4140,
					MESH_MATRIX = 0x4160,
		KFDATA = 0xB000,
			OBJECT_NODE_TAG = 0xB002,
				NODE_ID = 0xB030,
				NODE_HDR = 0xB010,
				PIVOT = 0xB013,
				BOUNDBOX = 0xB014,
				POS_TRACK_TAG = 0xB020,
				ROT_TRACK_TAG = 0xB021

};

struct ModVector
{
	float X, Y, Z;
};

struct ModTexcoord
{
	float U, V;
};

struct ModFace
{
	WORD I1, I2, I3;
	WORD Flags;

	WORD VertexInd( int i ) const
	{
		assert( (unsigned)i < 3 );
		return (&I1)[i];
	}
	WORD& VertexInd( int i )
	{
		assert( (unsigned)i < 3 );
		return (&I1)[i];
	}
};

struct FaceMatInfo
{
	std::string Name;
	std::vector<WORD> FaceIndex;
};

class ModTrimesh
{
public:
	std::vector<FaceMatInfo> MatInfoList;

	// Десериализующий конструктор.
	ModTrimesh( ChunkInfo& Chunk )
		: Normals(0)
	{
		long Total = Chunk.Len-6, Len = 0;
		while ( Len < Total )
		{
			Chunk.Next();
			Len += Chunk.Len;

			switch ( Chunk.Id )
			{
				// Vertex list
				case POINT_ARRAY:
					fread( &VertexCount, sizeof(WORD), 1, Chunk.F );
					Vertices.resize( VertexCount );
					fread( &Vertices[0], sizeof(ModVector), VertexCount, Chunk.F );
					break;

				// список текстурных координат
				case TEX_VERTS:
					fread( &NumTexCoords, sizeof(WORD), 1, Chunk.F );
					TexCoords.resize( NumTexCoords );
					fread( &TexCoords[0], sizeof(ModTexcoord), NumTexCoords, Chunk.F );
					break;

				// Face list
				case FACE_ARRAY:
				{
					fread( &FaceCount, sizeof(WORD), 1, Chunk.F );
					Faces.resize( FaceCount );
					//Faces = new ModFace[FaceCount];
					fread( &Faces[0], sizeof(ModFace), FaceCount, Chunk.F );

					long SubGroupLen = Chunk.Len - FaceCount*sizeof(ModFace) - sizeof(WORD) - 6;
					// Process material lists. Not realized yet
					while ( SubGroupLen )
					{
						Chunk.Next();
						SubGroupLen -= Chunk.Len;

						switch( Chunk.Id )
						{
							// материалы для граней
							case MSH_MAT_GROUP:
							{
								MatInfoList.push_back( FaceMatInfo() );
								FaceMatInfo *MatInfo = &MatInfoList.back();
								Chunk.ReadString( MatInfo->Name );
								WORD NumIndices;
								fread( &NumIndices, sizeof(WORD), 1, Chunk.F );
								MatInfo->FaceIndex.resize( NumIndices );
								fread( &MatInfo->FaceIndex[0], sizeof(WORD), NumIndices, Chunk.F );

								break;
							}

							case SMOOTH_GROUP:
							{
								SmoothGroups.resize( FaceCount );
								fread( &SmoothGroups[0], sizeof(DWORD), FaceCount, Chunk.F );
								break;
							}

							default:
								Chunk.Skip();
						}
					}
					break;
				}

				// Local coordinate matrix
				case MESH_MATRIX:
					fread( &Local[0], sizeof(float)*3, 1, Chunk.F );
					fread( &Local[1], sizeof(float)*3, 1, Chunk.F );
					fread( &Local[2], sizeof(float)*3, 1, Chunk.F );
					fread( &Local[3], sizeof(float)*3, 1, Chunk.F );
					Local[0][3] = 0;
					Local[1][3] = 0;
					Local[2][3] = 0;
					Local[3][3] = 1;
					break;

				// Nothing more yet
				default:
					Chunk.Skip();
			}
		}
		assert( Len == Total );
		CalculateVertexNormals();
		//CalculateVertexNormals1();
		// Некоторые материалы могут вовсе не иметь текстуры,
		// поэтому создаем фиктивные текстурные координаты - все 0.
		if( TexCoords.empty() )
		{
			TexCoords.resize( VertexCount );
			ModTexcoord ZZ = {0,0};
			std::fill( TexCoords.begin(), TexCoords.end(), ZZ );
		}
	}

	// Вычисляем нормали к вершинам (усредняем нормали к граням)
	void CalculateVertexNormals()
	{
		if ( Faces.empty() || Vertices.empty() )
			return;

		Normals = new ModVector[VertexCount];
		memset( Normals, 0, sizeof(*Normals)*VertexCount );
		ModFace *pFace = &Faces[0];
		for ( int i=0; i < FaceCount; i++, pFace++ )
		{
			ModVector AB;
			AB.X = Vertices[pFace->I2].X - Vertices[pFace->I1].X;
			AB.Y = Vertices[pFace->I2].Y - Vertices[pFace->I1].Y;
			AB.Z = Vertices[pFace->I2].Z - Vertices[pFace->I1].Z;
			ModVector BC;
			BC.X = Vertices[pFace->I3].X - Vertices[pFace->I2].X;
			BC.Y = Vertices[pFace->I3].Y - Vertices[pFace->I2].Y;
			BC.Z = Vertices[pFace->I3].Z - Vertices[pFace->I2].Z;
			// Вычисляем нормаль.
			ModVector N;
			N.X = AB.Z * BC.Y - BC.Z * AB.Y;
			N.Y = -AB.X * BC.Z + BC.X * AB.Z;
			N.Z = AB.X * BC.Y - BC.X * AB.Y;

			// What the fuck?
			if( pFace->Flags & 4 )
				N.X = -N.X;

			Normals[pFace->I1].X += N.X;
			Normals[pFace->I1].Y += N.Y;
			Normals[pFace->I1].Z += N.Z;
			Normals[pFace->I2].X += N.X;
			Normals[pFace->I2].Y += N.Y;
			Normals[pFace->I2].Z += N.Z;
			Normals[pFace->I3].X += N.X;
			Normals[pFace->I3].Y += N.Y;
			Normals[pFace->I3].Z += N.Z;
		}
		// Нормировка результата.
		ModVector *pN = Normals;
		for ( int i=0; i < VertexCount; i++, pN++ )
		{
			float Len = pN->X*pN->X + pN->Y*pN->Y + pN->Z*pN->Z;
			if ( Len )
			{
				Len = 1.0f / sqrt( Len );
				pN->X *= Len;
				pN->Y *= Len;
				pN->Z *= Len;
			}
		}
	}

	// Вычисление нормалей через Smoothing Groups. НЕ РАБОТАЕТ.
	void CalculateVertexNormals1()
	{
		std::vector< std::vector<DWORD> >	FaceForVertex( Vertices.size() );
		std::vector<ModVector>	FaceNormals;

		for( std::vector<ModFace>::iterator It = Faces.begin(); It != Faces.end(); ++It )
		{
			int FaceIndex = It - Faces.begin();
			for( int i=0; i < 3; i++ )
				FaceForVertex[ It->VertexInd(i) ].push_back( FaceIndex );

			// Calculate face normal.
			ModVector AB;
			AB.X = Vertices[It->I2].X - Vertices[It->I1].X;
			AB.Y = Vertices[It->I2].Y - Vertices[It->I1].Y;
			AB.Z = Vertices[It->I2].Z - Vertices[It->I1].Z;
			ModVector BC;
			BC.X = Vertices[It->I3].X - Vertices[It->I2].X;
			BC.Y = Vertices[It->I3].Y - Vertices[It->I2].Y;
			BC.Z = Vertices[It->I3].Z - Vertices[It->I2].Z;
			ModVector N;
			N.X = AB.Z * BC.Y - BC.Z * AB.Y;
			N.Y = -AB.X * BC.Z + BC.X * AB.Z;
			N.Z = AB.X * BC.Y - BC.X * AB.Y;
		}
		std::vector<ModFace> NewFaces;
		NewFaces.reserve( Faces.size() );
		for( std::vector<ModFace>::iterator It = Faces.begin(); It != Faces.end(); ++It )
		{
			int Face1 = It - Faces.begin();
			NewFaces.push_back( ModFace() );
			ModFace *NewFace = &NewFaces.back();
			for( int i=0; i < 3; i++ )
			{
				int MinFaceInd = Face1;
				ModVector Normal =  FaceNormals[Face1];
				std::vector<DWORD>& FList = FaceForVertex[ It->VertexInd(i) ];
				for( std::vector<DWORD>::iterator Jt = FList.begin(); Jt != FList.end(); ++Jt )
				{
					// Check is face Jt belongs to the same smoothing group as It.
					int Face2 = *Jt;
					if( Face1 == Face2 )
						continue;
					if( SmoothGroups[Face1] == SmoothGroups[Face2] )
					{
						// Add normal to avarage.
						Normal.X += FaceNormals[Face2].X;
						Normal.Y += FaceNormals[Face2].Y;
						Normal.Z += FaceNormals[Face2].Z;
						MinFaceInd = Min( MinFaceInd, Face2 );
					}
				}
				// Normalizing result.
				float Len = Normal.X*Normal.X + Normal.Y*Normal.Y + Normal.Z*Normal.Z;
				if ( Len )
				{
					Len = 1.0f / sqrt( Len );
					Normal.X *= Len;
					Normal.Y *= Len;
					Normal.Z *= Len;
				}
				if( MinFaceInd == Face1 )
				{
					// Write a new vertex.
					ModFace *Face = &It[0];
					ModVertex V = {0};
					V.Position = Vertices[ Face->VertexInd(i) ];
					V.Normal = Normal;
					V.TexCoord = TexCoords[ Face->VertexInd(i) ];
					VertexData.push_back( V );
					NewFace->VertexInd( i ) = VertexData.size()-1;
				}
				else
				{
					NewFace->VertexInd( i ) = NewFaces[ MinFaceInd ].VertexInd( i );
				}
			}
		}

		Faces.clear();
		std::copy( NewFaces.begin(), NewFaces.end(), std::back_inserter( Faces ) );
		VertexCount = VertexData.size();
	}

	~ModTrimesh()
	{
		delete[] Normals;
	}

public:
	std::vector<ModVector>		Vertices;
	std::vector<ModTexcoord>	TexCoords;
	std::vector<ModFace>		Faces;
	std::vector<DWORD>			SmoothGroups;
	ModVector					*Normals;

	struct ModVertex
	{
		ModVector		Position;
		ModVector		Normal;
		ModTexcoord		TexCoord;
	};
	std::vector<ModVertex>		VertexData;

	// Local coordinate system
	float Local[4][4];

	// Счетчики
	WORD VertexCount;
	WORD FaceCount;
	WORD NumTexCoords;
};

class ModMaterialGroupList
{
public:
	struct MaterialGroup
	{
		MaterialGroup				*Next;
		std::string					MatName;
		std::vector<int>			Indices;
		MaterialGroup( const std::string& Name )
			: MatName(Name)
		{}
	};
	ModMaterialGroupList() : Head(0), NumVertices(0)
	{}
	~ModMaterialGroupList()
	{
		for( MaterialGroup*Cur=Head; Cur; )
		{
			MaterialGroup *Old = Cur;
			Cur = Cur->Next;
			delete Old;
		}
	}
	void AddMeshMaterials( const ModTrimesh *TriMesh )
	{
		for( vec_const_iter<FaceMatInfo> Material(TriMesh->MatInfoList); Material; ++Material )
		{
			// Ищем нужную группу
			MaterialGroup *Cur;
			for( Cur = Head; Cur; Cur=Cur->Next )
			{
				if( Cur->MatName == Material->Name )
					break;
			}
			if( !Cur )
			{
				Cur = new MaterialGroup(Material->Name);
				Cur->Next = Head;
				Head = Cur;
			}
			// Соствляем массив индексов.
			for( vec_const_iter<WORD> It(Material->FaceIndex); It; ++It )
			{
				Cur->Indices.push_back( NumVertices + TriMesh->Faces[*It].I1 );
				Cur->Indices.push_back( NumVertices + TriMesh->Faces[*It].I2 );
				Cur->Indices.push_back( NumVertices + TriMesh->Faces[*It].I3 );
			}
		}
		TriMeshes.push_back( TriMesh );
		NumVertices += TriMesh->VertexCount;
	}
	MaterialGroup* GetMaterialGroups() const
	{
		return Head;
	}
	int GetVertexCount() const
	{
		return NumVertices;
	}
	void Merge( const ModMaterialGroupList& Other )
	{
		for( vec_const_iter<const ModTrimesh*> TriMesh(Other.TriMeshes); TriMesh; ++TriMesh )
		{
			AddMeshMaterials( *TriMesh );
		}
	}
private:
	MaterialGroup					*Head;
	// Общее числов вершин для мешей всех материалов.
	int								NumVertices;
public:
	std::vector<const ModTrimesh*>	TriMeshes;
};

typedef BYTE ModColor[3];

class ModMaterial
{
	ModColor	Specular;
	ModColor	SpecularLin;

public:
	ModMaterial( ChunkInfo& Chunk ) : HasTexture(false)
	{
		long GroupLen = Chunk.Len-6;
		while ( GroupLen )
		{
			Chunk.Next();
			GroupLen -= Chunk.Len;
			switch( Chunk.Id )
			{
				case MAT_NAME:
					Chunk.ReadString( Name );
					break;

				// Бликовая совтавляющая освещения.
				case MAT_SPECULAR:
				{
					long SubGroupLen = Chunk.Len-6;
					while( SubGroupLen )
					{
						Chunk.Next();
						SubGroupLen -= Chunk.Len;
						switch( Chunk.Id )
						{
							case COLOR_24:
								fread( Specular, sizeof(ModColor), 1, Chunk.F );
								break;
							case LIN_COLOR_24:
								fread( SpecularLin, sizeof(ModColor), 1, Chunk.F );
								break;
							default:
								Chunk.Skip();
						}
					}
				}
				break;

				case MAT_TEXMAP:
				{
					// обработка подгруппы
					long SubGroupLen = Chunk.Len-6;
					while ( SubGroupLen )
					{
						Chunk.Next();
						SubGroupLen -= Chunk.Len;
						switch( Chunk.Id )
						{
							// имя текстуры
							case MAT_MAPNAME:
								HasTexture = true;
								Chunk.ReadString( TextureName );
								break;

							// параметры текстуры
							// FIXME: сразу формировать матрицу?
							case MAT_MAP_USCALE:
							case MAT_MAP_VSCALE:
							case MAT_MAP_UOFFSET:
							case MAT_MAP_VOFFSET:
							case MAT_MAP_ANG:
								Chunk.Skip();
								break;

							default:
								Chunk.Skip();
						}
					}
					break;
				}

				default:
					Chunk.Skip();
			}
		}
		assert( GroupLen == 0 );
	}

public:
	std::string				Name;
	bool					HasTexture;
	std::string				TextureName;
};

class ModTrack
{
public:
	std::string			ObjName;
	WORD				Id;
	WORD				ParentId;

	// Десериализующий конструктор
	ModTrack( ChunkInfo& Chunk ) : PosData(0), RotData(0)
	{
		RotPivot.X = 0; RotPivot.Y = 0; RotPivot.Z = 0;
		long Total = Chunk.Len-6, Len = 0;
		while ( Len < Total )
		{
			Chunk.Next();
			Len += Chunk.Len;
			switch ( Chunk.Id )
			{
				case NODE_HDR:
					Chunk.ReadString( ObjName );
					fseek( Chunk.F, 4, SEEK_CUR );
					fread( &ParentId, sizeof(ParentId), 1, Chunk.F );
					break;

				case NODE_ID:
					fread( &Id, sizeof(Id), 1, Chunk.F );
					break;

				// центр вращения
				case PIVOT:
					fread( &RotPivot, sizeof(ModVector), 1, Chunk.F );
					break;

				case BOUNDBOX:
					fread( &BBMin, sizeof(BBMin), 1, Chunk.F );
					fread( &BBMax, sizeof(BBMax), 1, Chunk.F );
					break;

				case ROT_TRACK_TAG:
					fread( &RotFlags, sizeof(WORD), 1, Chunk.F );
					// пропускаем неизвестные данные
					fseek( Chunk.F, 8, SEEK_CUR );
					fread( &NumRot, sizeof(DWORD), 1, Chunk.F );
					RotData = new TrackRot[ NumRot ];
					for ( DWORD i = 0; i < NumRot; i++ )
					{
						fread( &RotData[i].Frame, sizeof(DWORD), 1, Chunk.F );
						fread( &RotData[i].SplineFlags, sizeof(WORD), 1, Chunk.F );
						fread( RotData[i].SplineInfo, sizeof(float)*NumTrackAttributes( RotData[i].SplineFlags ), 1, Chunk.F );
						// читаем угол и ось одним блоком
						fread( &RotData[i].Angle, 4*sizeof(float), 1, Chunk.F );
					}
					break;

				case POS_TRACK_TAG:
					fread( &PosFlags, sizeof(WORD), 1, Chunk.F );
					// пропускаем неизвестные данные
					fseek( Chunk.F, 8, SEEK_CUR );
					fread( &NumPos, sizeof(DWORD), 1, Chunk.F );
					PosData = new TrackPos[ NumPos ];
					for ( DWORD i = 0; i < NumPos; i++ )
					{
						fread( &PosData[i].Frame, sizeof(DWORD), 1, Chunk.F );
						fread( &PosData[i].SplineFlags, sizeof(WORD), 1, Chunk.F );
						// FIXME: не содержит этого?
						fread( PosData[i].SplineInfo, sizeof(float)*NumTrackAttributes( PosData[i].SplineFlags ), 1, Chunk.F );
						fread( &PosData[i].Position, sizeof(ModVector), 1, Chunk.F );
					}
					break;

				default:
					Chunk.Skip();
			}
		}
		assert( Len == Total );
	}

	enum TrackFlags
	{
		FLG_TENSION		= 0x1,
		FLG_CONTINUITY	= 0x2,
		FLG_BIAS		= 0x4,
		FLG_EASETO		= 0x8,
		FLG_EASEFROM	= 0x10
	};

	int NumTrackAttributes( WORD Flags )
	{
		int NumAttr = 0;
		if ( Flags & FLG_TENSION )
			NumAttr++;
		if ( Flags & FLG_CONTINUITY )
			NumAttr++;
		if ( Flags & FLG_BIAS )
			NumAttr++;
		if ( Flags & FLG_EASETO )
			NumAttr++;
		if ( Flags & FLG_EASEFROM )
			NumAttr++;
		return NumAttr;
	}

	~ModTrack()
	{
		delete[] PosData;
		delete[] RotData;
	}

	ModVector	RotPivot;
	ModVector	BBMin;
	ModVector	BBMax;

	// Trackpos data
	WORD		PosFlags;
	DWORD		NumPos;
	struct TrackPos
	{
		DWORD Frame;
		WORD SplineFlags;
		float SplineInfo[5];
		ModVector Position;
	} *PosData;

	// Trackrotate data
	WORD		RotFlags;
	DWORD		NumRot;
	struct TrackRot
	{
		DWORD Frame;
		WORD SplineFlags;
		float SplineInfo[5];
		float Angle;
		ModVector RotAxis;
	} *RotData;
};

class ModObject
{
public:
	// Create from file
	ModObject( ChunkInfo& Chunk ) : Track(0)
	{
		long Total = Chunk.Len-6, Len = 0;
		// Load object name
		Chunk.ReadString( Name );
		Len += Name.length() + 1;
		// Process with children
		while ( Len < Total )
		{
			Chunk.Next();
			Len += Chunk.Len;
			
			switch ( Chunk.Id )
			{
				// Parse triangle mesh
				case N_TRIOBJECT:
					Meshes.push_back( new ModTrimesh( Chunk ) );
					MatGroupList.AddMeshMaterials( Meshes.back() );
					break;

				default:
					Chunk.Skip();
			}
		}
		assert( Len == Total );
	}
	~ModObject()
	{
		while ( !Meshes.empty() )
		{
			delete Meshes.back();
			Meshes.pop_back();
		}
		delete Track;
	}

public:
	std::string							Name;
	std::vector<ModTrimesh*>			Meshes;
	ModTrack							*Track;
	std::vector<ModObject*>				Children;
	ModMaterialGroupList				MatGroupList;
};

// TODO: Можно формировать полный путь к текстурам при создании материалов.
// TODO: Обеспечить уникальность теустурных имен.
class GModel
{
	std::map<std::string, ModObject*>		Objects;
	std::map<std::string, ModMaterial*>		Materials;
	friend class std::map<std::string,GModel>;
	GModel()
	{}
public:
	std::string		Name;
	std::string		TextureFolder;

	GModel( const std::string& ModelName, const std::string& TexturePath )
		: Name(ModelName), TextureFolder(TexturePath)
	{}
	
	// Статический конструктор.
	static GModel* LoadModel( const std::string& ModelName, const std::string& ModelPath, const std::string& TexturePath )
	{
		static std::map<std::string, GModel> Models;
		if( Models.find( ModelName ) != Models.end() )
			return &Models[ModelName];
		else
		{
			FILE *ModFile;
			if( !fopen_s( &ModFile, (ModelPath+"/"+ModelName).c_str(), "rb" ) )
			{
				GModel Mdl( ModelName, TexturePath );
				ChunkInfo Chunk( ModFile );
				if ( Chunk.Id == M3DMAGIC )
					Mdl.LoadScene( Chunk );
				else
					exit( 1 );
				fclose( ModFile );
				return &(Models[ModelName]=Mdl);
			}
			return 0;
		}
	}

	void LoadObjmesh( ChunkInfo& Chunk )
	{
		long Total = Chunk.Len-6, Len = 0;
		while ( Len < Total )
		{
			Chunk.Next();
			Len += Chunk.Len;
			switch ( Chunk.Id )
			{
				case NAMED_OBJECT:
				{
					ModObject *Obj = new ModObject( Chunk );
					Objects.insert( std::make_pair( Obj->Name, Obj ) );
					break;
				}

				case MAT_ENTRY:
				{
					ModMaterial *Mat = new ModMaterial( Chunk );
					Materials.insert( std::make_pair( Mat->Name, Mat ) );
					break;
				}
				
				default:
					Chunk.Skip();
			}
		}
		assert ( Len == Total );
	}

	void LoadScene( ChunkInfo& Chunk )
	{
		long Total = Chunk.Len-6, Len = 0;
		while ( Len < Total )
		{
			Chunk.Next();
			Len += Chunk.Len;
			// Parse chunk
			switch ( Chunk.Id )
			{	
				case MDATA:
					LoadObjmesh( Chunk );
					break;
				
				// Animation
				case KFDATA:
				{
					long SubGroupLen = Chunk.Len - 6;
					while( SubGroupLen )
					{
						Chunk.Next();
						SubGroupLen -= Chunk.Len;
						switch( Chunk.Id )
						{
							case OBJECT_NODE_TAG:
							{
								ModTrack *Track = new ModTrack( Chunk );
								ModObject *Obj = GetModObjectByName( Track->ObjName );
								if( Obj )
									Obj->Track = Track;
								else
									delete Track;
							}
							break;

							default:
								Chunk.Skip();
						}
					}
				}
				break;

				default:
					Chunk.Skip();
			}
		}
		assert( Len == Total );
	}

	ModObject* GetModObjectByName( const std::string& ObjName )
	{
		if ( Objects.find( ObjName ) != Objects.end() )
			return Objects[ObjName];
		return 0;
	}
	ModMaterial* GetMaterialByName( const std::string& MatName )
	{
		if( Materials.find( MatName ) != Materials.end() )
			return Materials[MatName];
		return 0;
	}
};