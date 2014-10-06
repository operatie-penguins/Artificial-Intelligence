#pragma once
#include "Actor.h"
#include "Material.h"
#include "3DSMesh.h"
using std::vector;
using std::pair;

class GTank : public GActor
{
	Res3DSMesh		*Hull;
	Res3DSMesh		*Turret;
	GModel			*Model;
	Res3DSMesh		*Tracks;
	std::vector<Res3DSMesh*>	Wheels;
	float			TrackPos;

	// Материалы.
	ResMaterial		*HullMat;
	ShaderParam<D3DXMATRIX> MVPMatParam;
	ShaderParam<D3DXMATRIX> ModelViewIT;
	ResMaterial		*TracksMat;

	ShaderParam<float> TracksPos;

	D3DXMATRIXA16	ModelMat;
	D3DXMATRIXA16	World2Local;
	D3DXMATRIXA16	TurModelMat;  // Матрица от переходы от башни к корпусу.

	void SetupModelMat();
	void DrawWheels();

public:
	GTank();
	GRotator2D		TurretRot;
	void RotateTurret( float Angle );
	void GetTurretDir( Vector3& Dir ) const;
	void GetTurretCenter( Vector3& Center ) const;
	virtual void Draw();
	virtual void BeginFrame( float DeltaTime );
	virtual void EndFrame( float DeltaTime );

	// Не реализовано.
	void GTank::GetOBBox( OBBox& OBox ) const;
	void GTank::GetBBox( BBox& Box ) const;
	virtual ~GTank();

	bool TankCollide;
	bool WallCollide;
	bool MissileCollide;
	bool SeeUser;
	
	void Friction(float time, float mu);
	void SetPos(Vector3 NewPos)
	{
		Position.x = NewPos.x;
		Position.y = NewPos.y;
		Position.z = NewPos.z;
	}
};

enum TankEvents
{
	Searching, MissileHit, FoundTank, FoundCookie,
	TankHit, WallHit
};

class GComputerTank : public GTank
{
public:
	int Status;
	int status;
	bool missile;

	GComputerTank(Vector3 Position)
	{
		Status = 0;
		missile = false;

		SetPos(Position);
	}
	void Core()
	{
		if (!missile)
		{
			MissileHit();
			return;
		}
		RotateTurret( 50.0f );
		switch (Status)
		{
		case 0: 
			{

				RotateLocal( 90.0f ); 
				++Status;
				break;
			}	
		case 1:
			{
				if (!IsRotating())
				{					
					GoAhead(300.0f);
					++Status;
				}
				break;
			}
		case 2: 
			{ 
				if (!IsMoving())
				{
					RotateLocal( 180.0f ); 
					++Status;
				}
				break;
			}
		case 3: 
			{
				if (!IsRotating())
				{
					GoAhead(300.0f);
					++Status;
				}
				break;
			}
		case 4:
			{
				if (!IsMoving())
				{
					++Status;
				}
				break;
			}
		default:
			{
				Status = 0;
			}
		}
	}

	void MissileHit()
	{		
		switch (Status)
		{
		case 0: 
			{
				if (!IsMoving())
				{
					RotateTurret(360.0f);
					++Status;
				}
				break;
			}	
		case 1:
			{
				if (!TurretRot.IsRotating())
				{
					RotateLocal(180.0f);
					++Status;
				}
				break;
			}
		case 2: 
			{ 
				if (!IsRotating())
				{
					GoAhead(300.0f);
					++Status;
				}
				break;
			}
		case 3: 
			{
				if (!IsMoving())
				{
					RotateTurret(360.0f);
					++Status;
				}
				break;
			}
		case 4:
			{
				if (!TurretRot.IsRotating())
				{
					RotateLocal(90.0f);
					++Status;
				}
				break;
			}
		default:
			{
				if (!IsRotating())
				{
					Status = 0;
					missile = false;
				}
			}
		}
	}
	void FoundCookie()
	{

	}

	void Fire()
	{
	
	}

	void WallHit()
	{

	}
	void TankHit()
	{

	}
};