#pragma once
#include "ObjMain.h"

static const float ROT_THRESHOLD = 0.01f;

// Вращение в плоскости 0XZ
// 0 градусов - объект смотрит в глубь экрана.
class GRotator2D
{
public:
	D3DXVECTOR3		Up;
	float			DstYaw;
	float			Yaw;
	float			ModelYaw; // Начальный угол поворота модели.
	float			RotatingSpeed;
	GRotator2D() : Up(0,1,0), DstYaw(0), Yaw(0), RotatingSpeed(0)
	{}
	void Turn(float time)
	{
		Yaw += RotatingSpeed * time;
	}
	void Rotate(float value)
	{
		RotatingSpeed += value;
	}
	void SetDirection( float InitialYaw )
	{
		ModelYaw = InitialYaw;
	}
	bool IsRotating()
	{
		return !( (DstYaw - Yaw) > -ROT_THRESHOLD && (DstYaw - Yaw) < ROT_THRESHOLD );
	}
	void RotateLocal( float Angle )
	{
		DstYaw += Angle;
	}
	void RotateTo( float Angle )
	{
		DstYaw = Angle;
	}
	void StopRotation()
	{
		Yaw = DstYaw;
	}
	void RotateOneStep( float RotSpeed )
	{
		if( !IsRotating() )
			return;
		if( Yaw < DstYaw )
			Yaw += RotSpeed;
		else
		{
			Yaw -= RotSpeed;
			if( Yaw < DstYaw )
				StopRotation();
		}
	}

	D3DXVECTOR3 GetDirVector() const
	{
		return D3DXVECTOR3( sin(DegToRad(Yaw - ModelYaw)), 0, cos(DegToRad(Yaw - ModelYaw)) );
	}
};

class GActor : public GRenderable, public GRotator2D
{
protected:
	float			RemDist;	// Осталось пройти.
	float			MovSpeed;
	float			RotSpeed;
	bool			IsActive;
	friend	class	GCamera;
public:
	Vector3			Position;
	
	int				GameValue;	// Хелс, заряд и т.п.
	Vector3			Speed;
	GActor( GObject *Master = 0 ) : GRenderable(Master),  Position(0,0,0)
	{
		Register( "GActor" );
		MovSpeed = 0;
		RotSpeed = 0;
		RemDist = 0;
		Speed.x = 0;
		Speed.y = 0;
		Speed.z = 0;
	}
	
	virtual void Accelerate( float value )
	{
		Vector3 Direction = GetDirVector();
		Speed.x += Direction.x * value;
		Speed.z += Direction.z * value;
	}

	// Возвращает oriented bounding box объекта в мировых координатах.
	virtual void GetOBBox( OBBox& OBox ) const = 0;
	// Возвращает axis aligned box в мировых координатах.
	virtual void GetBBox( BBox& Box ) const = 0;

	virtual void GoAhead( float Distance )
	{
		RemDist += Distance;
	}
	virtual bool IsMoving() const
	{
		return( fabs(RemDist) > MovSpeed );
	}
	virtual bool IsMovingVector() const
	{
		return !((Speed.x == 0) && (Speed.z == 0));
	}
	virtual void Halt()
	{
		RemDist = 0;
		Speed.x = 0;
		Speed.y = 0;
		Speed.z = 0;
	}
	const Vector3& GetPos() const
	{
		return Position;
	}
	void Move()
	{
		RotateOneStep( RotSpeed );
		if( IsMoving() )
		{
			float Step = Sign(RemDist)*MovSpeed;
			RemDist -= Step;
			Position += GetDirVector()*Step;
		}
	}

	void Move(float time)
	{
		if (RotatingSpeed == 0)
			RotateOneStep( RotSpeed );
		if( IsMoving() )
		{
			float Step = Sign(RemDist)*MovSpeed;
			RemDist -= Step;
			Position += GetDirVector()*Step;
		}

		Turn(time);
		Position.x += Speed.x * time;
		Position.z += Speed.z * time;
	}

	// Обработка столкновений. Collided - указатель на объект,
	// препятствующий движению, иначе 0.
	virtual bool CanMoveOneStep( GObject **Collided )
	{
		Collided = 0;
		return true;
	}
	virtual ~GActor()
	{
		Unregister( "GActor" );
	}
};