// Рисование летящих и горящих хреновин.

texture2D DiffTexture
<
	//string Name = "Textures/Effects/fire_right.dds";
	//string Name = "Textures/Effects/1239296164511_e4533.png";
	string Name = "Vapour";
	string TextureShader = "Noise.psh";
	int Width = 128;
	int Height = 128;
	int MipLevels = 1;
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

float4x4	ViewMat;
float3		A;
float3		B;
float3		C;
// Объединить в один параметр.
float		EffectTime;
float		Size;
float		Len;
float		VolLen;

void MainVS( in float2 InPosition : POSITION,
			 in float T : TEXCOORD0,
			 out float4 OutPosition : POSITION,
			 out float2 TC : TEXCOORD0,
			 out float3 VolCoord : TEXCOORD1 )
{
	TC = InPosition;
	float3 Pos = lerp( lerp(A,B,T), lerp(B,C,T), T );
	InPosition *= Size;
	float4 Corner;
	Corner.xyz = Pos + InPosition.x*ViewMat._11_21_31 + InPosition.y*ViewMat._12_22_32;
	Corner.w = 1;
	
	// Получаем базис в объеме эффекта.
	float3 Front = 2.0f*(T*A + (1-2.0*T)*B - C*(1-T));
	Front = normalize( Front );
	float3 Right = cross( Front, float3(0,1,0) );
	float3 Up = cross( Front, Right );
	Up.y = -Up.y;
	
	// Находим коориднаты точки внутри объема.
	float InvSize = 1.0 / Size;
	VolCoord.x = InvSize * dot( Corner-Pos, Right );
	VolCoord.y = InvSize * dot( Corner-Pos, Up );
	VolCoord.z = (Size + dot( Corner-Pos, Front ))/VolLen + (EffectTime - T) / Len;
	
	OutPosition = mul( Corner, ViewProj );
}

float4 MainPS( in float2 TC : TEXCOORD0,
			   in float3 VolCoord : TEXCOORD1 ) : COLOR
{	
	float2 UV;
	UV.y  = 1.0 - length(VolCoord.xy);
	UV.x = 1.0 - VolCoord.z;
	float4 Col = tex2D( DiffTexSampler, UV );
	// Для плавного слияния с окружением, не подгоняем значение альфы к 0 на краях
	float w = 1.0 - length(TC);
	//Col.w = min( Col.w, w );
	return Col;
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