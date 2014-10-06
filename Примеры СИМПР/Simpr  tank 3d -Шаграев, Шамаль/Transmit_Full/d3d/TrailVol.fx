// Рисование летящих и горящих хреновин.

texture2D DiffTexture
<
	string Name = "Textures/Effects/fire_right.dds";
>;

sampler DiffTexSampler =
sampler_state
{
	Texture = <DiffTexture>;
	AddressU = CLAMP;
	AddressV = CLAMP;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = POINT;
};

shared float4x4		ViewProj;
shared float3		EyePos;

float3		A;
float3		B;
float3		C;
// Объединить в один параметр.
float		EffectTime;
float		Size;
float		Len;
float		VolLen;

void MainVS( in float3 InPosition : POSITION,
			 in float T : TEXCOORD0,
			 out float4 OutPosition : POSITION,
			 out float3 RayDir : TEXCOORD0,
			 out float3 RayOrg : TEXCOORD1 )
{
	float3 Pos = lerp( lerp(A,B,T), lerp(B,C,T), T );
	
	// Находим базис в пространстве объема.
	float3 Tangent = 2.0f*(T*A + (1.0-2.0*T)*B - C*(1.0-T));
	Tangent = normalize( Tangent );
	float3 Binormal = cross( Tangent, float3(0,1,0) );
	float3 Normal = cross( Tangent, Binormal );
	
	// Рассчитываем мировые координаты вершины.
	InPosition *= Size;
	float4 NewPos;
	NewPos.xy = Pos + Normal*InPosition.y + Binormal*InPosition.x;
	NewPos.z = Pos.z;
	NewPos.w = 1.0;
	
	// Рассчитываем параметры луча.
	float InvSize = 1.0 / Size;
	float PosZVolSpace = (EffectTime - T)/Len;
	RayOrg.x = InvSize*dot( EyePos-Pos, Binormal );
	RayOrg.y = InvSize*dot( EyePos-Pos, Normal );
	RayOrg.z = 1.0 / VolLen * dot( EyePos-Pos, Tangent ) + PosZVolSpace;
	
	float3 D;
	D.xy = InPosition.xy*InvSize;
	D.z = PosZVolSpace;
	RayDir = normalize(D - RayOrg);
	
	OutPosition = mul( NewPos, ViewProj );
}

void BoxRayIntersect(	float3 RayDir,
						float3 RayOrg,
						float3 BoxMin,
						float3 BoxMax,
						out float Near,
						out float Far )
{
	float3 InvDir = 1.0 / RayDir;
	float3 TBot = InvDir * (BoxMin - RayOrg);
	float3 TTop = InvDir * (BoxMax - RayOrg);
	
	float3 TMin = min( TTop, TBot );
	float3 TMax = max( TTop, TBot );
	
	float2 T0 = max( TMin.xx, TMin.yz );
	Near = max( T0.x, T0.y );
	T0 = min( TMax.xx, TMax.yz );
	Far = min( T0.x, T0.y );
}

float4 TexFunc( float3 P )
{
	float2 TC;
	TC.x = 1.0 - P.z;
	TC.y = 0.5 + 0.5*length( P.xy );
	float4 Col = tex2D( DiffTexSampler, TC );
	return Col;
}

float4 MainPS( float3 RayDir : TEXCOORD0,
			   float3 RayOrg : TEXCOORD1 ) : COLOR
{	
	float Near, Far;
	BoxRayIntersect( RayDir, RayOrg, float3(-1,-1,0), float3(1,1,1), Near, Far );
	if( Near >= Far )
		discard;
	
	/*float3 P = RayOrg + Far*RayDir;
	
	float Atten = 1.0 - 0.5*length(P.xy);
	float4 Col = Atten*lerp( float4(1,0,0,1), float4(0,1,0,1), P.z );
	return Col;*/
	
	float3 PNear = RayOrg + Near*RayDir;
	float3 PFar = RayOrg + Far*RayDir;
	
	int NumSteps = 4;
	float3 Step = (PNear - PFar) / (NumSteps-1);
	float4 C = 0;
	float3 P = PFar;
	for( int i=0; i < NumSteps; i++ )
	{
		float4 S = TexFunc( P );
		P += Step;
		C = S.w*S + (1.0 - S.w)*C;
	}
	
	return C;
}

technique RenderSmoke
{
	pass P0
	{
		AlphaBlendEnable = TRUE;
		//FillMode = WIREFRAME;
		DestBlend = INVSRCALPHA;
		SrcBlend = SRCALPHA;
		CullMode = CW;
		//ZWriteEnable = FALSE;
		VertexShader = compile vs_2_a MainVS();
		PixelShader = compile ps_2_a MainPS();
	}
};