#include "3DSGen.hlsl"
#include "../Common.hlsl"
#include "../LitGeneric.hlsl"

texture2D DiffMap;

sampler DiffMapSampler = sampler_state
{
	Texture = <DiffMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

// Параметры материалов.
float Specular = 0.4f;
float SpecularPower = 15.0;
float3 AmbientColor = {0.2, 0.2, 0.2};

float4x4 ModelViewProjMat;

float4x4 ModelViewIT;

// Рендеринг с освещением.
PSInputLitModel  HullLitVS( in VSInputLitModel Inp )
{
	PSInputLitModel Outp = (PSInputLitModel)0;
	
	Outp.HPos = mul( float4( Inp.vPos, 1 ), ModelViewProjMat );
	Outp.vTexCoord = Inp.vTexCoord;
	LitModelSurfaceVS( Inp, Outp, ModelViewIT );
	return Outp;
}

half4 HullLitPS( in PSInputLitModel Inp ) : COLOR
{
	half4 DiffCol = tex2D( DiffMapSampler, Inp.vTexCoord );
	
	float DiffuseContrib, SpecularContrib;
	LitModelSurfacePhongPS( Inp, Specular, SpecularPower, DiffuseContrib, SpecularContrib );
	half4 Col = half4(SpecularContrib.xxx, 0) + DiffCol*half4(DiffuseContrib.xxx + AmbientColor.xyz, 1);
	
	return PackResult( Col, Inp.vPos.z );
}

float TrackPos;

PSInputGen TracksVS( in VSInputGen Inp,
				out float4 OutPos : POSITION )
{
	PSInputGen Outp = ModelVS( Inp, ModelViewProjMat, OutPos );
	Outp.TexCoord.x += fmod( TrackPos, 1.0 );
	return Outp;
}

technique RenderScene
{
	pass P0
	{
		CullMode = CW;
		VertexShader = compile vs_2_0 HullLitVS();
		PixelShader = compile ps_2_0 HullLitPS();
	}
}

technique RenderTracks
{
	pass P0
	{
		VertexShader = compile vs_2_0 TracksVS();
		PixelShader = compile ps_2_0 ModelPS( DiffMapSampler );
	}
}