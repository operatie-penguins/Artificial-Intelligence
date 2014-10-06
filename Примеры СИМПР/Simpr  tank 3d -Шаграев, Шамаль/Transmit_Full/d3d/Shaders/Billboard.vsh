
struct VSInput
{
	float2 Corner : POSITION;
	float3 Pos : TEXCOORD0;
	float2 SizeLife : TEXCOORD1;
};

struct PSInput
{
	float3 TexCoord : TEXCOORD0;
	float4 vPos : TEXCOORD1;
	float Size : TEXCOORD3;
};

shared float4x4		ViewProj;
shared float4x4		ViewMat;

PSInput BillboardVS( in VSInput Inp,
						inout float4 OutPos : POSITION )
{
	PSInput Out = (PSInput)0;
	float Size = Inp.SizeLife.x*0.5;
	
	
	float2 Corner = Size * Inp.Corner;
	float3 vPos = Inp.Pos + Corner.x*ViewMat._11_21_31 + Corner.y*ViewMat._12_22_32;
	
	Out.TexCoord.xy = 0.5*Inp.Corner + float2(0.5,0.5);
	Out.TexCoord.z = Inp.SizeLife.y;
	
	OutPos = mul( float4(vPos, 1), ViewProj );
	
	// ѕередаем координаты и Depth дл€ м€гких частиц
	Out.vPos = OutPos;
	Out.vPos.z = dot( float4(vPos, 1), ViewMat._13_23_33_43 );
	
	Out.Size = Size;
	
	return Out;
}