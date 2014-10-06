// Стандарнтый материал c бамп-мэппингом.

#include "Effects/LitGeneric.hlsl"
#include "Effects/Common.hlsl"

texture2D DiffTexture
<
	string Name = "Textures/World/brick_uniform.tga";
>;

texture2D NormalMap
<
	string Name = "Textures/World/brick_uniformDOT3.tga";
>;

float MatParams
<
	bool Translucent = false;
>;

float3 AmbientColor = { 0.05, 0.05, 0.05 };
float2 TextureRepeatFactor = { 1, 1 };

sampler DiffTexSampler = sampler_state
{
	Texture = <DiffTexture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

sampler NormalMapSampler = sampler_state
{
	Texture = <NormalMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

shared float4x4 ViewProj;

VSOutputLitWorld MainVS( in VSInputLitWorld Inp )
{
	VSOutputLitWorld Outp = (VSOutputLitWorld)0;
	
	Outp.HPos = mul( float4( Inp.vPos, 1 ), ViewProj );
	Outp.vTexCoord = Inp.vTexCoord * TextureRepeatFactor;
	
	LitWorldSurfaceVS( Inp, Outp );
	
	return Outp;
}

half4 MainPS( in VSOutputLitWorld Inp ) : COLOR
{
	half4 Col = tex2D( DiffTexSampler, Inp.vTexCoord );
	
	Col *= half4(LitWorldSurfacePS( Inp, NormalMapSampler ).xxx + AmbientColor, 1);
	
	return PackResult( Col, Inp.vPos.z );
}

technique RenderScene
{
	pass P0
	{
		CullMode = CW;
		VertexShader = compile vs_2_0 MainVS();
		PixelShader = compile ps_2_0 MainPS();
	}
};
