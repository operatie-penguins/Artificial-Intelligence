#include "LitGeneric.hlsl"
#include "Common.hlsl"

texture2D GroundTexture
<
	string Name = "Textures/World/CrackedEarth0018_5_S.tga";
>;

sampler GrassTexSampler = sampler_state
{
	Texture = <GroundTexture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

texture2D GroundNormalMap
<
	string Name = "Textures/World/CrackedEarth0018_5_SDOT3.tga";
>;

sampler GroundNormalMapSampler = sampler_state
{
	Texture = <GroundNormalMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

float TilingFactor = 16;

shared float4x4 ViewProj;

VSOutputLitWorld GroundVS( in VSInputLitWorld Inp )
{
	VSOutputLitWorld Outp = (VSOutputLitWorld)0;
	Outp.vTexCoord = Inp.vTexCoord * TilingFactor;
	Outp.HPos = mul( float4(Inp.vPos,1), ViewProj );
	LitWorldSurfaceVS( Inp, Outp );
	return Outp;
}

half4 GroundPS( in VSOutputLitWorld Inp ) : COLOR
{
	half4 Color = tex2D( GrassTexSampler, Inp.vTexCoord );
	Color *= LitWorldSurfacePS( Inp, GroundNormalMapSampler );
	return PackResult( Color, Inp.vPos.z );
}

technique RenderScene
{
	pass P0
	{
		CullMode = CW;
		VertexShader = compile vs_2_0 GroundVS();
		PixelShader = compile ps_2_0 GroundPS();
	}
}