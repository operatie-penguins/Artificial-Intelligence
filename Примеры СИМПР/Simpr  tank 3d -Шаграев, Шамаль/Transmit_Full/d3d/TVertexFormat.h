#pragma once

#include <vector>
#include <d3d9.h>
#include "Utils.h"
#include <boost/static_assert.hpp>

inline D3DVERTEXELEMENT9 VertexElem( WORD Stream, WORD Offset, BYTE Type, BYTE Method, BYTE Usage, BYTE UsageIndex )
{
	D3DVERTEXELEMENT9 VE;
	VE.Stream = Stream;
	VE.Offset = Offset;
	VE.Type	  = Type;
	VE.Method = Method;
	VE.Usage  = Usage;
	VE.UsageIndex = UsageIndex;
	return VE;
}

template< int N > struct FloatType;
template<> struct FloatType<1>
{
	float X;
};
template<> struct FloatType<2>
{
	float X, Y;
	FloatType( const Vector2& V ) : X(V.x), Y(V.y)
	{}
};
template<> struct FloatType<3>
{
	float X, Y, Z;
	FloatType( const Vector3& V ) : X(V.x), Y(V.y), Z(V.z)
	{}
	operator Vector3&()
	{
		return *(Vector3*)this;
	}
};
template<> struct FloatType<4>
{
	float X, Y, Z, W;
};

class FormatStringEnd
{
public:
	static std::vector<D3DVERTEXELEMENT9>& GetVertexFormat()
	{
		D3DVERTEXELEMENT9 End = D3DDECL_END();
		static std::vector<D3DVERTEXELEMENT9> FormatString( 1, End );
		return FormatString;
	}
};

enum PosOptions
{
	Position1f = 1,
	Position2f = 2,
	Position3f = 3,
	Position4f = 4
};

enum NormalOptions
{
	SkipNormal = 0,
	Normal1f = 1,
	Normal2f = 2,
	Normal3f = 3,
	Normal4f = 4
};

enum TexCoordOptions
{
	SkipTexCoord = 0,
	TexCoord1f = 1,
	TexCoord2f = 2,
	TexCoord3f = 3,
	TexCoord4f = 4
};

enum TangentOptions
{
	SkipTangent = 0,
	Tangent1f = 1,
	Tangent2f = 2,
	Tangent3f = 3,
	Tangent4f = 4
};

enum BinormalOptions
{
	SkipBinormal = 0,
	Binormal1f = 1,
	Binormal2f = 2,
	Binormal3f = 3,
	Binormal4f = 4
};

// —татически конфигурируема€ структура вершины.
// ”казать число компонент или их наличие/остсутсвие. ¬ случае нескольких потоков данных указать
// номер текущего потока и формат вершин следующего потока.
template< int NPosition, int NNormal, bool bColor4UB, int NTexCoord0, int NTexCoord1 = 0,
		int NTangent = 0, int NBinormal = 0, int StreamNum = 0, class NextStreamFormat = FormatStringEnd >
class TVertex
{
	enum
	{
		SizePosition	= NPosition*sizeof(float),
		SizeNormal		= NNormal*sizeof(float),
		SizeColor4UB	= bColor4UB*sizeof(DWORD),
		SizeTexCoord0	= NTexCoord0*sizeof(float),
		SizeTexCoord1	= NTexCoord1*sizeof(float),
		SizeTangent		= NTangent*sizeof(float),
		SizeBinormal	= NBinormal*sizeof(float)
	};
	enum
	{
		OffsetPosition = 0,
		OffsetNormal = OffsetPosition + SizePosition,
		OffsetColor4UB = OffsetNormal + SizeNormal,
		OffsetTexCoord0 = OffsetColor4UB + SizeColor4UB,
		OffsetTexCoord1 = OffsetTexCoord0 + SizeTexCoord0,
		OffsetTangent = OffsetTexCoord1 + SizeTexCoord1,
		OffsetBinormal = OffsetTangent + SizeTangent
	};

	unsigned char Data[
		SizePosition +
		SizeNormal + 
		SizeColor4UB + 
		SizeTexCoord0 + 
		SizeTexCoord1 +
		SizeTangent + 
		SizeBinormal ];
public:
	typedef FloatType<NPosition>	PosType;
	typedef FloatType<NNormal>		NormalType;
	typedef FloatType<NTexCoord0>	TexCoord0Type;
	typedef FloatType<NTexCoord1>	TexCoord1Type;
	typedef FloatType<NTangent>		TangentType;
	typedef FloatType<NBinormal>	BinormalType;
	enum { StreamNumber = StreamNum };

	PosType& Position()
	{
		BOOST_STATIC_ASSERT( SizePosition );
		return *(PosType*)Data;
	}
	NormalType& Normal()
	{
		BOOST_STATIC_ASSERT( SizeNormal );
		return *(NormalType*)(Data + OffsetNormal);
	}
	DWORD& Color4UB()
	{
		BOOST_STATIC_ASSERT( SizeColor4UB );
		return *(DWORD*)(Data + OffsetColor4UB);
	}
	TexCoord0Type& TexCoord0()
	{
		BOOST_STATIC_ASSERT( SizeTexCoord0 );
		return *(TexCoord0Type*)(Data + OffsetTexCoord0);
	}
	TexCoord1Type& TexCoord1()
	{
		BOOST_STATIC_ASSERT( SizeTexCoord1 );
		return *(TexCoord1Type*)(Data + OffsetTexCoord1);
	}
	TangentType& Tangent()
	{
		BOOST_STATIC_ASSERT( SizeTangent );
		return *(TangentType*)(Data + OffsetTangent);
	}
	BinormalType& Binormal()
	{
		BOOST_STATIC_ASSERT( SizeBinormal );
		return *(BinormalType*)(Data + OffsetBinormal);
	}
	static std::vector<D3DVERTEXELEMENT9>& GetVertexFormat();
};

template<
	int NPosition,
	int NNormal,
	bool bColor4UB,
	int NTexCoord0,
	int NTexCoord1,
	int NTangent,
	int NBinormal,
	int StreamNum,
	class NextStreamFormat
>	std::vector<D3DVERTEXELEMENT9>& TVertex<NPosition,
											NNormal,
											bColor4UB,
											NTexCoord0,
											NTexCoord1,
											NTangent,
											NBinormal,
											StreamNum,
											NextStreamFormat>::GetVertexFormat()
{
	static std::vector<D3DVERTEXELEMENT9> FormatString;
	if( FormatString.empty() )
	{
		D3DDECLTYPE FloatType[] = { D3DDECLTYPE_FLOAT1, D3DDECLTYPE_FLOAT2, D3DDECLTYPE_FLOAT3, D3DDECLTYPE_FLOAT4 };
		if( NPosition )
		{
			FormatString.push_back( VertexElem(StreamNum, OffsetPosition, FloatType[NPosition-1], D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0) );
		}
		if( NNormal )
		{
			FormatString.push_back( VertexElem(StreamNum, OffsetNormal, FloatType[NNormal-1], D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0) );
		}
		if( bColor4UB )
		{
			FormatString.push_back( VertexElem(StreamNum, OffsetColor4UB, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0) );
		}
		if( NTexCoord0 )
		{
			FormatString.push_back( VertexElem(StreamNum, OffsetTexCoord0, FloatType[NTexCoord0-1], D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0) );
		}
		if( NTexCoord1 )
		{
			FormatString.push_back( VertexElem(StreamNum, OffsetTexCoord1, FloatType[NTexCoord1-1], D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1) );
		}
		if( NTangent )
		{
			FormatString.push_back( VertexElem(StreamNum, OffsetTangent, FloatType[NTangent-1], D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0) );
		}
		if( NBinormal )
		{
			FormatString.push_back( VertexElem(StreamNum, OffsetBinormal, FloatType[NBinormal-1], D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0) );
		}
		FormatString.insert( FormatString.end(), NextStreamFormat::GetVertexFormat().begin(), NextStreamFormat::GetVertexFormat().end() );
	}
	return FormatString;
}