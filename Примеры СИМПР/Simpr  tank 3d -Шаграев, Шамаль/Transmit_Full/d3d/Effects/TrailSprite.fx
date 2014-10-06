
#include "../Shaders/Billboard.vsh"


PSInput TrailSpriteVS( in VSInput Inp,
					out float4 OutPos : POSITION )
{
	PSInput Outp = BillboardVS( Inp, OutPos );
	return Outp;
}

texture3D NoiseVol
<
	string Name = "TrailSpriteNoiseVolume";
	string TextureShader = "Effects/Trail.tsh";
	int Width = 128;
	int Height = 128;
	int Depth = 128;
	int MipLevels = 1;
>;

sampler NoiseVolSamp = sampler_state
{
	Texture = <NoiseVol>;
	MinFilter = LINEAR;
	MagFilter = POINT;
	MipFilter = POINT;
	AddressU = WRAP;
	AddressV = WRAP;
	AddressW = WRAP;
};

float	AnimTime;
float	DissolveFactor;


/*texture1D GradTex
<
	string Name = "Textures/Effects/grad3.dds";
>;

sampler GradTexSamp = sampler_state
{
	Texture = <GradTex>;
	MinFilter = POINT;
	MagFilter = POINT;
	MipFilter = POINT;
	AddressU = CLAMP;
};

half4 TrailSpritePS( in PSInput Inp ) : COLOR
{
	float Dist = 2.0*length( Inp.TexCoord.xy - float2(0.5,0.5) );
	float3 NoiseTC;
	NoiseTC = Inp.TexCoord;
	NoiseTC.z += AnimTime;
	float4 Noise = tex3D( NoiseVolSamp, NoiseTC );
	Dist += Noise.x*0.5;
	half4 Sample = tex1D( GradTexSamp, Dist );
	Sample.w = Noise.w;
	
	half4 Color;
	if( Inp.TexCoord.z > 0.99 )
		Color = Sample;
	else
		Color = Noise;
	Color.w = min( Color.w, DissolveFactor*exp(-3.5*(1 - Inp.TexCoord.z)) );
	return Color;
}

// Новая версия.

texture2D FireBallTex
<
	string Name = "Textures/Effects/explode8.tga";
>;

sampler FireBallSampler = sampler_state
{
	Texture = <FireBallTex>;
	AddressU = CLAMP;
	AddressV = CLAMP;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = POINT;
};*/

texture3D FireBallVol
<
	string Name = "Textures/Effects/FireBallVol1.dds";
>;

sampler FireBallVolSamp = sampler_state
{
	Texture = <FireBallVol>;
	AddressU = CLAMP;
	AddressV = CLAMP;
	AddressW = CLAMP;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
};

/*half4 TrailSpritePS1( in PSInput Inp ) : COLOR
{
	float NoiseSamp = tex3D( NoiseVolSamp, float3( Inp.TexCoord.xy, AnimTime + Inp.TexCoord.z ) );
	// Приводим к диапазону [-1,1].
	NoiseSamp = 2.0*NoiseSamp - 1.0;
	float2 TC = Inp.TexCoord.xy + 0.2*NoiseSamp.xx;
	half4 Col = tex2D( FireBallSampler, TC );
	// Lerp to grayscale.
	float GrFact = exp( -2.0*Inp.TexCoord.z );
	half4 ColGS = 0.33*Col.x + 0.33*Col.y + 0.34*Col.z;
	Col = lerp( Col, ColGS, GrFact );
	return Col * Inp.TexCoord.z;
}*/

half4 TrailSpritePS1V( in PSInput Inp ) : COLOR
{
	float NoiseSamp = tex3D( NoiseVolSamp, float3( Inp.TexCoord.xy, AnimTime + Inp.TexCoord.z ) );
	// Приводим к диапазону [-1,1].
	NoiseSamp = 2.0*NoiseSamp - 1.0;
	float3 TC;
	TC.xy = Inp.TexCoord.xy + 0.2*NoiseSamp.xx;
	TC.z = 1 - Inp.TexCoord.z;
	half4 Col = tex3D( FireBallVolSamp, TC );
	// Lerp to grayscale.
	float GrFact = exp( -2.0*Inp.TexCoord.z );
	half4 ColGS = 0.33*Col.x + 0.33*Col.y + 0.34*Col.z;
	Col = lerp( Col, ColGS, GrFact + DissolveFactor*(1-GrFact) );
	return float4( Col.xyz * Inp.TexCoord.z, Col.w*exp(-5.0*DissolveFactor) );
}

technique RenderScene
{
	pass P0
	{
		ZWriteEnable = FALSE;
		AlphaBlendEnable = TRUE;
		DestBlend = INVSRCALPHA;
		SrcBlend = SRCALPHA;
		CullMode = CW;
		VertexShader = compile vs_2_0 TrailSpriteVS();
		PixelShader = compile ps_2_0 TrailSpritePS1V();
	}
}