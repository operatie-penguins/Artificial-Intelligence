
shared float4x4 ViewProj;

void AuxVS( in float3 Pos : POSITION,
			inout float4 Color : COLOR,
			out float4 OutPos : POSITION )
{
	OutPos = mul( float4(Pos,1), ViewProj );
}

float4 AuxPS( in float4 Col : COLOR ) : COLOR
{
	return Col;
}

technique RenderScene
{
	pass P0
	{
		FillMode = WIREFRAME;
		CullMode = NONE;
		VertexShader = compile vs_2_0 AuxVS();
		PixelShader = compile ps_2_0 AuxPS();
	}
}