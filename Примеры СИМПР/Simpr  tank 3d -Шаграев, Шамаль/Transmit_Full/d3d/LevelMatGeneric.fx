// Базовый материал уровня.

texture2D DiffTexture
<
	string Name = "wall.bmp";	
>;

sampler DiffTexSampler =
sampler_state
{
	Texture = <DiffTexture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

shared float4x4 WorldViewProj;

void MainVS( in float4 InPosition : POSITION,
		   in float4 InColor : COLOR0,
		   out float4 OutPosition : POSITION,
		   out float4 OutColor : COLOR0  )
{
	OutPosition = mul( InPosition,  WorldViewProj );
	OutColor = InColor;
}

void MainPS( in float4 InColor : COLOR0,
			 out float4 OutColor : COLOR0 )
{
	OutColor = tex2D( DiffTexSampler, float2(0,0) );
}

technique RenderScene
{
	pass P0
	{
		VertexShader = compile vs_2_0 MainVS();
		PixelShader = compile ps_2_0 MainPS();
	}
};