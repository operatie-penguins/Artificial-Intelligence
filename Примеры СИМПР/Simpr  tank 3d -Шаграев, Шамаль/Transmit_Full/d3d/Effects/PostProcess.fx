
/*texture2D OpaqueRT;

sampler OpaqueRTSampler = sampler_state
{
	Texture = <OpaqueRT>;
	MinFilter = POINT;
	MagFilter = POINT;
	MipFilter = NONE;
};

half4 PostProcessPS( float2 vTexCoord : TEXCOORD0 ) : COLOR
{
	half4 Sample = tex2D( OpaqueRTSampler, vTexCoord );
	return Sample.w / 1000.0;
}*/

shared texture2D OpaqueAndDepthPassTex;

sampler OpaqueDepthSampler = sampler_state
{
	Texture = <OpaqueAndDepthPassTex>;
	MinFilter = POINT;
	MagFilter = POINT;
	MipFilter = NONE;
};

// Выводим всю нерпозрачную геометрию на квадрат во весь экран.
half4 PostProcessPS( float2 vTexCoord : TEXCOORD0 ) : COLOR
{
	half4 Sample = tex2D( OpaqueDepthSampler, vTexCoord );
	return half4( Sample.xyz, 1 );
}

technique RenderScene
{
	pass P0
	{
		PixelShader = compile ps_2_0 PostProcessPS();
	}
}