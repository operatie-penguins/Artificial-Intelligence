
#include "../Shaders/Billboard.vsh"
#include "SoftParticles.hlsl"

texture3D VolumeDiffTexture
<
	string Name = "SmokeNoiseVolume";
	string TextureShader = "Effects/Smoke.tsh";
	int Width = 128;
	int Height = 128;
	int Depth = 128;
	int MipLevels = 1;
>;

sampler SampVolume = sampler_state
{
	texture = <VolumeDiffTexture>;
	MinFilter = POINT;
	MagFilter = POINT;
	MipFilter = POINT;
	AddressU = CLAMP;
	AddressV = CLAMP;
	AddressW = CLAMP;
};

half4 SmokeParticlePS( in PSInput Inp ) : COLOR
{
	half4 Sample = tex3D( SampVolume, Inp.TexCoord );
	Sample.w *= SoftSmoke( Inp.vPos, 2.0*Inp.Size );
	return Sample;
}

technique RenderScene
{
	pass P0
	{
		ZFunc = ALWAYS;
		ZWriteEnable = FALSE;
		AlphaBlendEnable = TRUE;
		DestBlend = INVSRCALPHA;
		SrcBlend = SRCALPHA;
		CullMode = CW;
		VertexShader = compile vs_2_0 BillboardVS();
		PixelShader = compile ps_2_0 SmokeParticlePS();
	}
}