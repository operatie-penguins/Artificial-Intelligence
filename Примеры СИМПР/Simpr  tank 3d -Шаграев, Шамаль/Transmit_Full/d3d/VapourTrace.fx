// Рисование билбордов. Тест.
// FIXME: передавать транспонированную матрицу вида или Up и Right векторы.

texture2D DiffTexture;

sampler DiffTexSampler =
sampler_state
{
	Texture = <DiffTexture>;
	AddressU = WRAP;
	AddressV = WRAP;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = POINT;
};

shared float4x4		ViewProj;

float4x4	ViewMat;
float3		A;
float3		B;
float		EffectTime;
float		Size;

void MainVS( in float2 InPosition : POSITION,
			 in float T : TEXCOORD0,
			 out float4 OutPosition : POSITION,
			 out float2 TC : TEXCOORD0 )
{
	TC = float2(0.5,0.5) + 0.5*InPosition;
	float3 Pos = lerp( A, B, T );
	InPosition *= Size;
	float4 Corner;
	Corner.xyz = Pos + InPosition.x*ViewMat._11_21_31 + InPosition.y*ViewMat._12_22_32;
	Corner.w = 1;
	
	OutPosition = mul( Corner, ViewProj );
}

float4 MainPS( in float2 TC : TEXCOORD0 ) : COLOR
{
	float4 ResColor = tex2D( DiffTexSampler, TC );
	
	float2 Dist2Center = TC - float2(0.5,0.5);
	ResColor.w = 0.5 - length(Dist2Center);
	return ResColor*(1.0 - EffectTime);
}

technique RenderSmoke
{
	pass P0
	{
		AlphaBlendEnable = TRUE;
		//FillMode = WIREFRAME;
		DestBlend = INVSRCALPHA;
		SrcBlend = SRCALPHA;
		CullMode = NONE;
		ZWriteEnable = FALSE;
		VertexShader = compile vs_2_0 MainVS();
		PixelShader = compile ps_2_0 MainPS();
	}
};