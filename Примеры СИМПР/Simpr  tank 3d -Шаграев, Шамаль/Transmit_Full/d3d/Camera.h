#pragma once
#include "Actor.h"

// FIXME: осуществлять через кватернионы воизбежании gimbal lockа.
struct GRotation
{
	D3DXVECTOR3 I, J, K;
	GRotation() : I(1,0,0), J(0,1,0), K(0,0,1)
	{}
	void RotateAxis( int Axis, float Angle )
	{
		D3DXMATRIX RM;
		switch( Axis )
		{
		case 0:
			D3DXMatrixRotationAxis( &RM, &I, Angle );
			D3DXVec3TransformNormal( &J, &J, &RM );
			D3DXVec3TransformNormal( &K, &K, &RM );
			break;
		case 1:
			D3DXMatrixRotationAxis( &RM, &J, Angle );
			D3DXVec3TransformNormal( &I, &I, &RM );
			D3DXVec3TransformNormal( &K, &K, &RM );
			break;
		case 2:
			D3DXMatrixRotationAxis( &RM, &K, Angle );
			D3DXVec3TransformNormal( &J, &J, &RM );
			D3DXVec3TransformNormal( &I, &I, &RM );
			break;
		default:
			assert( 0 );
		}
	}
	void GetMatrix( D3DXMATRIX& M) const
	{
		M._11 = I.x;
		M._21 = I.y;
		M._31 = I.z;
		M._41 = 0;
		M._12 = J.x;
		M._22 = J.y;
		M._32 = J.z;
		M._42 = 0;
		M._13 = K.x;
		M._23 = K.y;
		M._33 = K.z;
		M._43 = 0;
		M._14 = 0;
		M._24 = 0;
		M._34 = 0;
		M._44 = 1;
	}
};

class GCamera
{
	GActor			*Target;
	float			Yaw;
	float			Pitch;
	float			Dist;
public:
	GCamera() : Target(0), Dist(150.0f), Yaw(0), Pitch(3.14159265f/4)
	{}
	// Присоединяет камеру к объекту на расстоянии Dist.
	// FixDir - должна ли камера вращаться с объектом.
	void AttachToObject( GActor *Obj, float Distance )
	{
		Dist = Distance;
		Target = Obj;
	}
	void AlterateDist( float Delta )
	{
		Dist += Delta;
	}
	void RotateScrYX( float DeltaYaw, float DeltaPitch )
	{
		Yaw += DegToRad( DeltaYaw );
		ClampAngle( Yaw );
		Pitch += DegToRad( DeltaPitch );
		ClampAngle( Pitch );
	}
	void GetCameraPos( Vector3& Pos )
	{
		Vector3 TrgPos(0,0,0);
		if( Target )
			TrgPos = Target->GetPos();
		GRotation Rot;
		Rot.RotateAxis( 1, Yaw );
		Rot.RotateAxis( 0, Pitch );
		Pos = TrgPos - Dist*Rot.K;
	}
	void GetViewMatrix( D3DXMATRIX& M )
	{
		Vector3 TrgPos(0,0,0);
		if( Target )
			TrgPos = Target->GetPos();
		GRotation Rot;
		Rot.RotateAxis( 1, Yaw );
		Rot.RotateAxis( 0, Pitch );
		Rot.GetMatrix( M );
		M._41 = -TrgPos.Dot( Rot.I );
		M._42 = -TrgPos.Dot( Rot.J );
		M._43 = -TrgPos.Dot( Rot.K ) + Dist;
	}
};