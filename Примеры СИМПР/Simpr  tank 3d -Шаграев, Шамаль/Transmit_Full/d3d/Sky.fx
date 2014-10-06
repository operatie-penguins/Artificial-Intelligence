
#include "Effects/Common.hlsl"

texture2D DiffTexture
<
	string Name = "Textures/Sky/Sky_horiz_10_4096.dds";
>;

sampler DiffTexSampler =
sampler_state
{
	Texture = <DiffTexture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = POINT;
};

shared float4x4		ViewProj;
shared float3		EyePos;
shared float4x4	ViewMat;


struct VSInput
{
	float3 vPos : POSITION;
	float2 vTexCoord : TEXCOORD0;
};

struct VSOutput
{
	float4  HPos : POSITION;
	float2	vTexCoord : TEXCOORD0;
	float3	vPos : TEXCOORD1;
};

VSOutput MainVS( in VSInput Inp )
{
	VSOutput Outp = (VSOutput)0;
	float3 vPos = Inp.vPos + EyePos;
	Outp.HPos = mul( float4(vPos, 1),  ViewProj );
	Outp.vPos = mul( float4(vPos, 1), ViewMat );
	Outp.vTexCoord.x = Inp.vTexCoord.x;
	Outp.vTexCoord.y = 1 - Inp.vTexCoord.y;
	return Outp;
}

half4 MainPS( in VSOutput Inp ) : COLOR
{
	half4 OutColor = tex2D( DiffTexSampler, Inp.vTexCoord );
	return PackResult( OutColor, Inp.vPos.z );
}

technique RenderScene
{
	pass P0
	{
		CullMode = CCW;
		VertexShader = compile vs_2_0 MainVS();
		PixelShader = compile ps_2_0 MainPS();
	}
};