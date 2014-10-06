// Реализация плавных частиц (для дыма, взрываов и т.п.).

#include "Common.hlsl"

// Текстура, в которую срендерна вся непрозрачная геометрия,
// а в альфаканале линейные значения глубины.
shared texture2D	OpaqueAndDepthPassTex;

sampler OpaqueDepthSampler = sampler_state
{
	Texture = <OpaqueAndDepthPassTex>;
	MinFilter = POINT;
	MagFilter = POINT;
	MipFilter = NONE;
};


float SoftExplosion( float4 vPos,  float FadeDistance )
{
	float2 vScrCoord = vPos.xy / vPos.w;
	vScrCoord = float2(0.5, -0.5) * vScrCoord + float2(0.5, 0.5);
	
	float ParticleDepth = vPos.z;

	float FragDepth = UnpackDepth( tex2D( OpaqueDepthSampler, vScrCoord ) );
	
	// Trick to avoid RT clear.
	if( FragDepth < 1 )
		FragDepth = 32000.0f;
	
	float DepthDiff = FragDepth - ParticleDepth;
	if( DepthDiff < -FadeDistance )
		discard;
	
	float DepthFade;
	if( DepthDiff > FadeDistance )
		DepthFade = saturate( abs(DepthDiff) / FadeDistance );
	else
		DepthFade = 1 - abs(DepthDiff) / FadeDistance ;
	return DepthFade;
}


float SoftSmoke( float4 vPos,  float FadeDistance )
{
	float2 vScrCoord = vPos.xy / vPos.w;
	vScrCoord = float2(0.5, -0.5) * vScrCoord + float2(0.5, 0.5);
	
	float ParticleDepth = vPos.z;

	float FragDepth = UnpackDepth( tex2D( OpaqueDepthSampler, vScrCoord ) );
	
	// Trick to avoid RT clear.
	if( FragDepth < 1 )
		FragDepth = 32000.0f;
	
	float DepthDiff = FragDepth - ParticleDepth;
	if( DepthDiff < 0 )
		discard;
	
	float DepthFade = saturate( DepthDiff / FadeDistance );
	return DepthFade;
}