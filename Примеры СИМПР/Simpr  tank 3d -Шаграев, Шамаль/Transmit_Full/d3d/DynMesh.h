#pragma once

#include "Rendering.h"

// Интерфейс к буферам вершин и индексов.
// Данные могут изменяться только все сразу (изменять отдельные части нельзя).
// Нет проверок на переполнение.
template< class VD >
class ResDynamicMesh : public IResource
{
	int		MaxVert;
	int		MaxPrim;
	LPDIRECT3DVERTEXBUFFER9			pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9			pIndexBuffer;
	LPDIRECT3DVERTEXDECLARATION9	pVertexDecl;
	LPDIRECT3DDEVICE9				pMeshDevice;
	bool	NeedRecreation;
	bool	IBLocked;
	bool	VBLocked;
	WORD	*Indices, *IndStart;


	bool HasFiller;
	boost::function< void(ResDynamicMesh<VD>*) > VertexBufferFiller;
public:
	ResDynamicMesh( int MaxVertices, int MaxPrimitives )
		: pVertexBuffer(0), pIndexBuffer(0), pVertexDecl(0), pMeshDevice(0), MaxVert(MaxVertices), MaxPrim(MaxPrimitives),
		NeedRecreation(false), IBLocked(false), VBLocked(false), HasFiller(false)
	{}

	// Для ленивого пресоздания данных буфера (cоздающая процедура FillFunc в объекте Owner).
	ResDynamicMesh( int MaxVertices, int MaxPrimitives, boost::function<void(ResDynamicMesh<VD>*)> FillFunc )
		: pVertexBuffer(0), pIndexBuffer(0), pVertexDecl(0), pMeshDevice(0), MaxVert(MaxVertices), MaxPrim(MaxPrimitives),
		NeedRecreation(false), IBLocked(false), VBLocked(false),
		VertexBufferFiller( FillFunc ), HasFiller(true)
	{
	}

	// True если мешь была потеряна и необходимо пересоздать ее данные.
	// FIXME: избавиться от этого в пользу ленивого пересоздания.
	bool NeedDataRecreation() const
	{
		return NeedRecreation;
	}

	virtual void Create( LPDIRECT3DDEVICE9 pDevice )
	{
		HRESULT HR;
		if( !pVertexDecl )
		{
			HR = pDevice->CreateVertexDeclaration( &VD::GetVertexFormat()[0], &pVertexDecl );
			if( FAILED(HR) )
				DXError(HR, "failed on IDirect3DDevice9::CreateVertexDeclaration");
		}
		HR = pDevice->CreateVertexBuffer(
			sizeof(VD)*MaxVert,
			D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
			0,
			D3DPOOL_DEFAULT,
			&pVertexBuffer,
			NULL );
		if( FAILED(HR) )
			DXError(HR, "failed on IDirect3DDevice9::CreateVertexBuffer");
		// Индексный буфер может не требоваться.
		if( MaxPrim )
		{
			HR = pDevice->CreateIndexBuffer(
				sizeof(WORD)*MaxPrim*3, 
				D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_DEFAULT,
				&pIndexBuffer,
				NULL );
			if( FAILED(HR) )
				DXError(HR, "failed on IDirect3DDevice9::CreateIndexBuffer");
		}
		NeedRecreation = true;
		pMeshDevice = pDevice;

		if( HasFiller )
			VertexBufferFiller( this );
	}

	virtual void Destroy()
	{
		if( pVertexBuffer )
		{
			pVertexBuffer->Release();
			pVertexBuffer = 0;
		}
		if( pIndexBuffer )
		{
			pIndexBuffer->Release();
			pIndexBuffer = 0;
		}
	}

	VD* Begin( bool LockVertex, bool LockIndex,
		int NumVertices = 0, int NumPrimitives = 0 )
	{
		HRESULT HR;
		VD *VertexData = 0;
		if( LockVertex )
		{
			assert( !VBLocked );
			HR = pVertexBuffer->Lock( 0, sizeof(VD)*NumVertices, (void**)&VertexData, D3DLOCK_DISCARD );
			if( FAILED(HR) )
				DXError(HR, "failed on IDirect3DVertexBuffer9::Lock");
			VBLocked = true;
			NeedRecreation = false;
		}
		if( LockIndex )
		{
			assert( !IBLocked );
			Indices = 0;
			HR = pIndexBuffer->Lock( 0, sizeof(WORD)*NumPrimitives*3, (void**)&Indices, D3DLOCK_DISCARD );
			if( FAILED(HR) )
				DXError(HR, "failed on IDirect3DIndexBuffer9::Lock");
			IndStart = Indices;
			IBLocked = true;
		}
		return VertexData;
	}
	void Index( WORD Ind )
	{
		assert( IBLocked );
		*Indices++ = Ind;
	}
	int NumUsedIndices()
	{
		assert( IBLocked );
		return( Indices - IndStart );
	}
	void End()
	{
		if( VBLocked )
		{
			pVertexBuffer->Unlock();
			VBLocked = false;
		}
		if( IBLocked )
		{
			pIndexBuffer->Unlock();
			IBLocked = false;
		}
	}
	void SetupDPCall()
	{
		assert( !VBLocked );
		pMeshDevice->SetVertexDeclaration( pVertexDecl );
		pMeshDevice->SetStreamSource( VD::StreamNumber, pVertexBuffer, 0, sizeof(VD) );
	}
	void SetupDIPCall()
	{
		assert( !VBLocked );
		assert( !IBLocked );
		pMeshDevice->SetVertexDeclaration( pVertexDecl );
		pMeshDevice->SetStreamSource( VD::StreamNumber, pVertexBuffer, 0, sizeof(VD) );
		pMeshDevice->SetIndices( pIndexBuffer );
	}
	void AttachAsStreamSource()
	{
		pMeshDevice->SetStreamSource( VD::StreamNumber, pVertexBuffer, 0, sizeof(VD) );
	}

	// Отправляем данные видеокарте.
	void DrawP( int NumPrimitives )
	{
		HRESULT HR = pMeshDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, NumPrimitives );
		assert( !FAILED(HR) );
	}
	void DrawIP( MaterialBin *DrawBin )
	{
		HRESULT HR;
		HR=pMeshDevice->DrawIndexedPrimitive( 
			D3DPT_TRIANGLELIST,
			DrawBin->BaseVertexIndex,
			DrawBin->MinVertexIndex,
			DrawBin->NumVertices,
			DrawBin->StartIndex,
			DrawBin->NumPrimitives
		);
		assert( !FAILED(HR) );
	}

	// Рисование с указанием типа примитивов.
	template< D3DPRIMITIVETYPE PrimType >
	void DrawIPWithType( MaterialBin *DrawBin )
	{
		HRESULT HR;
		HR=pMeshDevice->DrawIndexedPrimitive( 
			PrimType,
			DrawBin->BaseVertexIndex,
			DrawBin->MinVertexIndex,
			DrawBin->NumVertices,
			DrawBin->StartIndex,
			DrawBin->NumPrimitives
		);
		assert( !FAILED(HR) );
	}
private:
	virtual ~ResDynamicMesh()
	{
		if( pVertexDecl )
		{
			pVertexDecl->Release();
			pVertexDecl = 0;
		}
		ResourceManager::GetInstance().Unregister( this );
	}
};
