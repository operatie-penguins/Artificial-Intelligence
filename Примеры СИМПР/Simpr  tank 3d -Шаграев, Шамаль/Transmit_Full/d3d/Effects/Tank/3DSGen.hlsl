// Основной шейдер для .3DS моделей.

struct VSInputGen
{
	float3	Pos			: POSITION;
	float3	Normal		: NORMAL;
	float2	TexCoord	: TEXCOORD0;
};


struct PSInputGen
{
	float2	TexCoord : TEXCOORD0;
};


PSInputGen ModelVS( in VSInputGen Inp,
					uniform float4x4 ModelViewProj,
					inout float4 OutPos : POSITION )
{
	PSInputGen Outp = (PSInputGen)0;
	OutPos = mul( float4(Inp.Pos,1), ModelViewProj );
	Outp.TexCoord = Inp.TexCoord;
	return Outp;
}


half4 ModelPS( in PSInputGen Inp,
				uniform sampler DiffMapSampler ) : COLOR
{
	half4 Sample = tex2D( DiffMapSampler, Inp.TexCoord );
	return Sample;
}