#pragma once

#include "ModLoad.h"
#include "Rendering.h"
#include "Material.h"
#include "GameAux.h"

inline Vector3 Mod2Vector3( const ModVector& MV )
{
	return Vector3( MV.X, MV.Z, MV.Y );
}

struct VisNormal
{
	Vector3 Normal;
	Vector3 VPos;
	
	VisNormal( const Vector3& N, const Vector3& Pos )
		: Normal(N), VPos(Pos)
	{}

	void Draw( const D3DXMATRIX& ModelMat )
	{
		Vector3 WPos = Transform( ModelMat, VPos );
		Vector3 WNorm = TransformVector( ModelMat, Normal );
		GAuxiliary::Get().DrawLine( WPos, WPos + 2.5f*WNorm, D3DCOLOR_XRGB(0,255,0) ); 
	}
};

class Res3DSMesh : public IResource
{
	ModObject						*ModelObject;
	GModel							*Model;
	std::string						ObjectsStr;
	LPDIRECT3DVERTEXBUFFER9			VertexBuffer;
	LPDIRECT3DDEVICE9				pSavedDevice;
	LPDIRECT3DVERTEXDECLARATION9	pVertexDecl;
	struct VertexData
	{
		ModVector		Position;
		ModVector		Normal;
		float			U, V;
	};
	struct MatInternal
	{
		LPDIRECT3DINDEXBUFFER9			pIndexBuffer;
		ResTexture						*Texture;
		int								NumPrimitives;
	};
	std::vector<MatInternal>	Materials;
	BBox	Boundary;

	// DEBUGGING
	std::vector<VisNormal> VisNormals;
public:
	Res3DSMesh( const std::string& ModObjectsStr, GModel *pModel )
		: ObjectsStr(ModObjectsStr), Model(pModel), VertexBuffer(0), pVertexDecl(0)
	{}
	void Create( LPDIRECT3DDEVICE9 pDevice );
	void Destroy();
	void Draw();
	void Draw( ResMaterial *Mat );
	const ModVector& GetRotCenter() const;
	const BBox& Res3DSMesh::GetBBox() const;

	void DrawNormals( const D3DXMATRIX& ModelMat )
	{
		for( std::vector<VisNormal>::iterator I = VisNormals.begin(); I != VisNormals.end(); ++I )
		{
			I->Draw( ModelMat );
		}
	}
private:

	void DrawMesh( MaterialBin *Bin );
	~Res3DSMesh();
};