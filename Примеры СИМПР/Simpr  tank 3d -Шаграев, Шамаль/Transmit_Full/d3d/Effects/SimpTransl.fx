// Пример полупрозрачного материала.

#include "LitGeneric.hlsl"

float MatParams
<
	bool Translucent = true;
>;

float4 Color = { 0.7, 0.8, 0.1, 0.5 };

shared float4x4 ViewProj;


VSOutputLitWorld TranslucentVS( in VSInputLitWorld Inp )
{
	VSOutputLitWorld Outp = (VSOutputLitWorld)0;
	
	Outp.HPos = mul( float4(Inp.vPos, 1), ViewProj );
	Outp.vTexCoord = Inp.vTexCoord;
	
	return Outp;
}

half4 TranslucentPS( in VSOutputLitWorld Inp ) : COLOR
{
	half4 DiffColor = Color;
	// Добавить для тектурирования (описать DiffTexSampler).
	// DiffColor.xyz = tex2D( DiffTexSampler, Inp.vTexCoord ).xyz;
	return DiffColor;
}

technique RenderScene
{
	pass P0
	{
		CullMode = CCW;
		AlphaBlendEnable = TRUE;
		DestBlend = INVSRCALPHA;
		SrcBlend = SRCALPHA;
		VertexShader = compile vs_2_0 TranslucentVS();
		PixelShader = compile ps_2_0 TranslucentPS();
	}
	
	pass P1
	{
		CullMode = CW;
		AlphaBlendEnable = TRUE;
		DestBlend = INVSRCALPHA;
		SrcBlend = SRCALPHA;
		VertexShader = compile vs_2_0 TranslucentVS();
		PixelShader = compile ps_2_0 TranslucentPS();
	}
};