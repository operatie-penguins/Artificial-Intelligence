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

shared float4x4 ViewProj;
float4x4 ViewMat;

float3 PointA;
float3 PointB;
float3 PointC;


void MainVS( in float2 InPosition : POSITION,
			 in float T : TEXCOORD0,
			 out float4 OutPosition : POSITION,
			 out float2 TC : TEXCOORD0 )
{
	TC = float2(0.5,0.5) + 0.5*InPosition;
	float3 C = lerp( PointA, PointB, T );
	float3 D = lerp( PointB, PointC, T );
	float3 Pos = lerp( C, D, T );
	float Scale = 20.0f;
	InPosition *= Scale;
	float4 Corner;
	Corner.xyz = Pos +
		InPosition.x*float3(ViewMat[0][0], ViewMat[1][0], ViewMat[2][0]) +
		InPosition.y*float3(ViewMat[0][1], ViewMat[1][1], ViewMat[2][1]);
	Corner.w = 1;
	
	OutPosition = mul( Corner, ViewProj ); 
}

float4 MainPS( in float2 TC : TEXCOORD0 ) : COLOR0
{
	float4 ResColor = tex2D( DiffTexSampler, TC );
	
	float2 Dist2Center = TC - float2(0.5,0.5);
	ResColor.w = 0.5 - length(Dist2Center);
	return ResColor;
}

technique RenderSmoke
{
	pass P0
	{
		AlphaBlendEnable = TRUE;
		DestBlend = INVSRCALPHA;
		SrcBlend = SRCALPHA;
		CullMode = NONE;
		ZWriteEnable = FALSE;
		VertexShader = compile vs_2_0 MainVS();
		PixelShader = compile ps_2_0 MainPS();
	}
};