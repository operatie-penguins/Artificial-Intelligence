#ifndef _LIT_GENERIC
#define _LIT_GENERIC

// Реализация освещения для отдного источника света.

shared float3	LightDir;
shared float3	EyePos;

shared float4x4		ViewMat;

struct VSInputLitWorld
{
	float3		vPos	  : POSITION;
	float2		vTexCoord : TEXCOORD0;
	float3		vTangent  : TANGENT;
	float3		vNormal   : NORMAL;
	float3		vBinormal : BINORMAL;
};

struct VSOutputLitWorld
{
	float4 HPos			: POSITION;
	float2 vTexCoord	: TEXCOORD0;
	float3 vLightDir	: TEXCOORD1;
	float3 vPos			: TEXCOORD2;
	float3 vEyeDir		: TEXCOORD3;
	float3 vNormal		: TEXCOORD4;
};

void  LitWorldSurfaceVS( in VSInputLitWorld Inp, inout VSOutputLitWorld Outp )
{
	Outp.vLightDir.x = dot( LightDir, Inp.vTangent );
	Outp.vLightDir.y = dot( LightDir, Inp.vBinormal );
	Outp.vLightDir.z = dot( LightDir, Inp.vNormal );
	
	Outp.vPos = mul( float4(Inp.vPos, 1), ViewMat ).xyz;
	
	float3 vEyeDir = EyePos - Inp.vPos;
	Outp.vEyeDir.x = dot( vEyeDir, Inp.vTangent );
	Outp.vEyeDir.y = dot( vEyeDir, Inp.vBinormal );
	Outp.vEyeDir.z = dot( vEyeDir, Inp.vNormal );
}

float LitWorldSurfacePS( in VSOutputLitWorld Inp, in sampler NormalMapSampler )
{
	float3 BumpNormal = tex2D( NormalMapSampler, Inp.vTexCoord );
	BumpNormal = 2.0 * BumpNormal - float3(1, 1, 1);
	//BumpNormal = normalize( BumpNormal );
	float3 vLight = normalize( Inp.vLightDir );
	return max( dot( BumpNormal, vLight ), 0 );
}

void LitWorldSurfaceNoBumpVS( in VSInputLitWorld Inp, inout VSOutputLitWorld Outp )
{	
	Outp.vNormal = mul( float4(Inp.vNormal,0), ViewMat ).xyz;
	Outp.vPos = mul( float4(Inp.vPos, 1), ViewMat ).xyz;
	Outp.vEyeDir = -Outp.vPos;
	Outp.vLightDir = mul( float4(LightDir, 0), ViewMat ).xyz;
}

float LitWorldSurfaceNoBumpPS( in VSOutputLitWorld Inp )
{
	float3 vLight = normalize( Inp.vLightDir );
	float3 vEyeDir = normalize( Inp.vEyeDir );
	float3 vNormal = normalize( Inp.vNormal );
	
	return max( dot( vLight, vNormal ), 0 );
}

float LitWorldSurfaceSpecularOnlyPS( in VSOutputLitWorld Inp, float Specular, float SpecPower )
{
	float3 vLight = normalize( Inp.vLightDir );
	float3 vEyeDir = normalize( Inp.vEyeDir );
	float3 vHalfAng = normalize( vLight + vEyeDir );
	float3 vNormal = normalize( Inp.vNormal );
	float4 L = lit( dot(vLight, vNormal), dot(vHalfAng, vNormal), SpecPower );
	return L.y * L.z * Specular;
}

struct VSInputLitModel
{
	float3		vPos	  : POSITION;
	float2		vTexCoord : TEXCOORD0;
	float3		vNormal   : NORMAL;
};

struct PSInputLitModel
{
	float4 HPos			: POSITION;
	float2 vTexCoord    : TEXCOORD0;
	float3 vLightDir	: TEXCOORD1;
	float3 vPos			: TEXCOORD2;
	float3 vEyeDir		: TEXCOORD3;
	float3 vNormal		: TEXCOORD4;
};

void LitModelSurfaceVS( in VSInputLitModel Inp,
						 inout PSInputLitModel Outp,
						 float4x4 ModelViewMatIT )
{
	Outp.vNormal = mul( float4(Inp.vNormal, 0), ModelViewMatIT ).xyz;
	Outp.vLightDir = mul( float4(LightDir, 0), ViewMat ).xyz;
	
	// FIXME: работает только если ModelViewMatIT == ModelViewMat.
	Outp.vEyeDir = -mul( float4(Inp.vPos,1), ModelViewMatIT ).xyz;
	Outp.vPos = -Outp.vEyeDir;
}

float4 LitModelSurfacePS( in PSInputLitModel Inp )
{
	float3 vLight = normalize( Inp.vLightDir );
	float3 vNormal = normalize( Inp.vNormal );
	
	return max( dot( vLight, vNormal ), 0 );
}

void LitModelSurfacePhongPS( in PSInputLitModel Inp,
							 float Specular,
							 float SpecPower,
							 out float DiffuseContrib,
							 out float SpecularContrib )
{
	float3 vLight = normalize( Inp.vLightDir );
	float3 vEyeDir = normalize( Inp.vEyeDir );
	float3 vHalfAng = normalize( vLight + vEyeDir );
	float3 vNormal = normalize( Inp.vNormal );
	
	float4 L = lit( dot(vLight,vNormal), dot(vHalfAng,vNormal), SpecPower );
	DiffuseContrib = L.y;
	SpecularContrib = L.y*L.z*Specular;
}

#endif