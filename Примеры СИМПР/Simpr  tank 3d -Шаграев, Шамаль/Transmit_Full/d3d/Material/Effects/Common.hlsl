#ifndef _COMMON
#define _COMMON

static const float RGB16Max = 32768.0f;

half4 PackResult( half4 Color, float ViewZ )
{
	return half4( Color.xyz, ViewZ / RGB16Max );
}

float UnpackDepth( half4 Sample )
{
	return Sample.w * RGB16Max;
}

#endif