
texture2D DiffTexture;

sampler DiffTexSampler =
sampler_state
{
	Texture = <DiffTexture>;
	MinFilter = POINT;
	MagFilter = POINT;
	MipFilter = NONE;
};

float ScreenWidth;
float ScreenHeight;

void MainVS( in float2 InPosition : POSITION,
			 inout float2 Texcoord : TEXCOORD0,
		     out float4 OutPosition : POSITION )
{
	OutPosition.x = (2.0f * InPosition.x  - ScreenWidth) / ScreenWidth;
	OutPosition.y = (2.0f * InPosition.y  - ScreenHeight) / ScreenHeight;
	OutPosition.z = 1.0f;
	OutPosition.w = 1.0f;
}

half4 MainPS( in float2 TexCoord : TEXCOORD0 ) : COLOR
{
	half4 OutColor = tex2D( DiffTexSampler, TexCoord );
	return OutColor*half4( 0, 1, 0, 1 );
}

technique RenderScene
{
	pass P0
	{
		AlphaBlendEnable = TRUE;
		DestBlend = INVSRCALPHA;
		SrcBlend = SRCALPHA;
		//BlendOp = MAX;
		ZFunc = ALWAYS;
		ZWriteEnable = FALSE;
		VertexShader = compile vs_2_0 MainVS();
		PixelShader = compile ps_2_0 MainPS();
	}
};