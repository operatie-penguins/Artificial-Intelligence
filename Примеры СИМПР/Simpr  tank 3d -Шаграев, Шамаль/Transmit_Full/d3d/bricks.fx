// Стандартный материал без бамп-мэппинга.

#include "Effects/LitGeneric.hlsl"
#include "Effects/Common.hlsl"

texture2D DiffTexture
<
	string Name = "brick.jpg";
>;


float MatParams
<
	bool Translucent = false;
>;

float3 AmbientColor = { 0.65, 0.65, 0.65 };
float2 TextureRepeatFactor = { 25, 25 };

sampler DiffTexSampler = sampler_state
{
	Texture = <DiffTexture>;
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
	LitWorldSurfaceNoBumpVS( Inp, Outp );
	return Outp;
}

half4 MainPS( in VSOutputLitWorld Inp ) : COLOR
{
	half4 Col = tex2D( DiffTexSampler, Inp.vTexCoord );
	Col *= half4(LitWorldSurfaceNoBumpPS( Inp ).xxx + AmbientColor, 1);
	
	return PackResult( Col, Inp.vPos.z );
}

technique RenderScene
{
	pass P0
	{
		CullMode = CW;
		//FillMode = WIREFRAME;
		VertexShader = compile vs_2_0 MainVS();
		PixelShader = compile ps_2_0 MainPS();
	}
};