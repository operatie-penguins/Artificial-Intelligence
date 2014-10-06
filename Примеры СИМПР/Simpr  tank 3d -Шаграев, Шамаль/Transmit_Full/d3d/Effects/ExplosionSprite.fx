#include "../Shaders/Billboard.vsh"
#include "SoftParticles.hlsl"

const float UFrames  = 4.0;
const float VFrames  = 4.0;
const float SpriteWidth = 128.0;
const float SpriteHeight = 128.0;


PSInput ExplosionVS( in VSInput Inp,
					 out float4 OutPos : POSITION,
					 out float4 NextFrTC : TEXCOORD2 )
{
	PSInput Outp = BillboardVS( Inp, OutPos );
	
	float FrTime = 1.0 / (UFrames*VFrames);
	float CurTime = Inp.SizeLife.y;
	
	// Координаты текущеуго кадра.
	float Fr = floor( CurTime / FrTime );
	float Row = floor( Fr / UFrames);
	float Col = floor( fmod(Fr, UFrames) );
	float DU = 1.0 / UFrames;
	float DV = 1.0 / VFrames;
	float U = Col * DU;
	float V = Row * DV;
	
	float2 TC;
	TC.x = U + Outp.TexCoord.x * DU;
	TC.y = V + Outp.TexCoord.y * DV;
	
	// Координаты следующего кадра (для интерполяции).
	float NextFr = min( Fr+1, UFrames*VFrames-1 );
	Row = floor( NextFr / UFrames);
	Col = floor( fmod(NextFr, UFrames) );
	U = Col * DU;
	V = Row * DV;
	NextFrTC.x = U + Outp.TexCoord.x * DU;
	NextFrTC.y = V + Outp.TexCoord.y * DV;
	
	NextFrTC.z = Outp.TexCoord.x;
	NextFrTC.w = Outp.TexCoord.y;
	
	Outp.TexCoord.x = TC.x;
	Outp.TexCoord.y = TC.y;
	Outp.TexCoord.z = CurTime/FrTime - Fr;
	
	return Outp;
}

texture2D ExplSpriteTx
<
	string Name = "Textures/Sprites/explode_1.bmp";
>;

sampler ExplSpriteSamp = sampler_state
{
	Texture = <ExplSpriteTx>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture3D ExplSpriteVol
<
	string Name = "Textures/Sprites/ExplVol.dds";
>;

sampler ExplVolSamp = sampler_state
{
	Texture = <ExplSpriteVol>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = CLAMP;
	AddressV = CLAMP;
	AddressW = CLAMP;
};

half4 ExplosionSpritePS( in PSInput Inp,
						  in float4 NextFrTC : TEXCOORD2 ) : COLOR
{
	half4 Sample = tex2D( ExplSpriteSamp, Inp.TexCoord.xy );
	half4 NextSample = tex2D( ExplSpriteSamp, NextFrTC.xy );
	half4 Col;
	Col.xyz = lerp( Sample, NextSample, Inp.TexCoord.z ).xyz;
	float2 W2 = max( Col.xx, Col.yz );
	Col.w = max( W2.x, W2.y );
	
	// Предостерегаем от заплыва на предыдущую строку кадров.
	float Atten = 1.0 - 2.0*length(NextFrTC.zw - float2(0.5,0.5));
	Col.w *= smoothstep( 0.05, 0.1, Atten );
	
	return Col;
}

float SpriteNum;

half4 ExplosionSpritePS1( in PSInput Inp,
						  in float4 NextFrTC : TEXCOORD2,
						  in float Size : TEXCOORD3 ) : COLOR
{
	half4 Sample = tex3D( ExplVolSamp, float3(Inp.TexCoord.xy,SpriteNum) );
	half4 NextSample = tex3D( ExplVolSamp, float3(NextFrTC.xy,SpriteNum) );
	half4 Col;
	Col.xyz = lerp( Sample, NextSample, Inp.TexCoord.z ).xyz;
	float2 W2 = max( Col.xx, Col.yz );
	Col.w = max( W2.x, W2.y );
	
	// Предостерегаем от заплыва на предыдущую строку кадров.
	float Atten = 1.0 - 2.0*length(NextFrTC.zw - float2(0.5,0.5));
	Col.w *= smoothstep( 0.05, 0.1, Atten );
	
	// Мягкие частицы.
	Col.w *= SoftExplosion( Inp.vPos, Inp.Size );
	return Col;
}

technique RenderScene
{
	pass P0
	{
		ZWriteEnable = FALSE;
		ZFunc = ALWAYS;
		AlphaBlendEnable = TRUE;
		DestBlend = INVSRCALPHA;
		SrcBlend = SRCALPHA;
		CullMode = CW;
		VertexShader = compile vs_2_0 ExplosionVS();
		PixelShader = compile ps_2_0 ExplosionSpritePS1();
	}
}