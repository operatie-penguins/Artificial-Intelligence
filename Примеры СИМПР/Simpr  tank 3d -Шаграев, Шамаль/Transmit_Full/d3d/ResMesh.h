#pragma once

#include "Rendering.h"

// Базовый класс для меши
class IResMesh : public IResource
{
public:
	virtual void Lock( int NumVertices, int NumPrimitives ) = 0;
	virtual void Unlock() = 0;
	virtual void SetupDrawCall() = 0;
	virtual void Draw( MaterialBin& Bin ) = 0;
	virtual ~ResMesh()
	{}
};


class ResStaticMesh : public IResMesh
{
	int NumVert;
	int NumIndx;
	LPDIRECT3DVERTEXBUFFER9			pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9			pIndexBuffer;
	LPDIRECT3DVERTEXDECLARATION9	pVertexDecl;
	VertexData						*VD;						
public:
	ResStaticMesh( int NumVertices, int NumIndices, VertexData *pVD )
		: VD(pVD), NumVert(NumVertices), NumIndx(NumIndices), pVertexBuffer(0),
		pIndexBuffer(0), pVertexDecl(0)
	{}
	void Create( LPDIRECT3DEVICE9 pDevice );
	void Destroy();
	void Lock( int NumVertices, int NumIndices );
	void Unlock();
	void Draw( MaterialBin& Bin );
	void SetupDrawCall();
private:
	~ResStaticMesh();
};