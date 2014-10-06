#pragma once

#include "Game.h"
#include "Rendering.h"

// Вспомогательные средства.

class GAuxiliary : public GRenderable
{
	GAuxiliary();
	~GAuxiliary();
	GAuxiliary( const GAuxiliary& );
	void operator=( const GAuxiliary& );

	typedef TVertex<3,0,true, 0>	AuxVF;
	ResDynamicMesh<AuxVF>			*AuxMesh;
	ResMaterial						*AuxMat;

	// Буфер вершин.
	std::vector<AuxVF>				Vertices;

	// Индексы для trilist-ов.
	std::vector<WORD>				Indices;
	MaterialBin						TrilistBin;

	// Индексы для линий.
	std::vector<WORD>				LnIndices;
	MaterialBin						LinesBin;

	int MaxSize;
public:
	void DrawBBox( const BBox& Box );
	void DrawOBBox( const OBBox& Box );
	void DrawLine( const Vector3& From, const Vector3& To, D3DXCOLOR Col );
	void DrawCoords( const Vector3& I, const Vector3& J, const Vector3& K, const Vector3& Org );

	void BeginFrame( float CurTime );
	void EndFrame( float CurTime );
	void Draw();

	void Clear()
	{
		LinesBin.Clear();
		TrilistBin.Clear();
		Vertices.clear();
		Indices.clear();
		LnIndices.clear();
	}

	static GAuxiliary& Get()
	{
		static GAuxiliary Instance;
		return Instance;
	}
};