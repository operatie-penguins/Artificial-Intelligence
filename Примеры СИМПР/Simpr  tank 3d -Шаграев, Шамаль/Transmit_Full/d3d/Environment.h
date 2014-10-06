#pragma once

#include <vector>
#include <iostream>

#include "Game.h"
#include "Tank.h"
#include "Time.h"
#include "Effects.h"

using std::vector;
using std::pair;
using std::cin;
using std::cout;

class Environment
{
public:
	GLevelData World;
	vector<GComputerTank*> CompTanks;
	GTank *UserTank;
	EffParticleSystem *ParSystem;
	double cur_time;

	float BlockDimensionSize;
	vector<vector<int> > map;
	vector<bool> ActiveCompTanks;
	bool IsActiveUserTank;
	std::vector<std::pair<int, int> > TankStartupPositions;
	std::vector<std::pair<int, int> > BonusStartupPositions;
	std::vector<std::pair<int, int> > MineStartupPositions;
	std::vector<int> WallBlockNumbers;

	std::vector<bool> CompFire;
	std::vector<double> CompFireTime;
	bool UserFire;
	double UserFireTime;

	int ColCount;
	int RowCount;
	float mu;
	float g;

	int ObjNumber;
	
	void GetNextObject()
	{
		++ObjNumber;
		if (ObjNumber == CompTanks.size() + 1)
			ObjNumber = 0;
	}

	void UserTankFire()
	{
		if (cur_time - UserFireTime > 0.5f)
		{
			UserFire = true;
			Vector3 A, B, C, D;
			UserTank->GetTurretCenter(A);
			UserTank->GetTurretDir(D);

			B.x = A.x + D.x * 200;
			B.y = A.y;
			B.z = A.z + D.z * 200;

			C.x = A.x + D.x * 10000;
			C.y = A.y;
			C.z = A.z + D.z * 10000;
			ParSystem->CreateFireTrail(A, B, C, 5000.0f, 1.0f );

			UserFireTime = cur_time;
		}
		else
			UserFire = false;
	}

	void CompTankFire(int n, int value = 10)
	{		
		if (cur_time - CompFireTime[n] > 0.5f)
		{
			CompFire[n] = true;
			Vector3 A, B, C, D;
			CompTanks[n]->GetTurretCenter(A);
			CompTanks[n]->GetTurretDir(D);

			B.x = A.x + D.x * 200;
			B.y = A.y;
			B.z = A.z + D.z * 200;

			C.x = A.x + D.x * 2000;
			C.y = A.y;
			C.z = A.z + D.z * 2000;

			ParSystem->CreateFireTrail(A, B, C, 5000.0f, 1.0f );

			CompFireTime[n] = cur_time;
		}
		else
			CompFire[n] = false;
	}

	void ReadDataFromFile(char *FileName)
	{
		freopen(FileName, "r", stdin);
		
		cin >> BlockDimensionSize >> RowCount >> ColCount;

		char *CurrentLine = new char[ColCount];
		map.resize(RowCount);
		cin.getline(CurrentLine, 10);

		World.SetBlockSize(Vector3(BlockDimensionSize*ColCount,1,BlockDimensionSize*RowCount));
		World.AddBlock( Vector3(0, -1, 0), GLevelData::BLOCK_ALIGN_X, "Ground.fx" );
		World.SetBlockSize(Vector3(BlockDimensionSize,BlockDimensionSize*1.5,BlockDimensionSize));
		for (int i = 0; i < RowCount; ++i)
		{
			map[i].resize(ColCount, 0);
			cin.getline( CurrentLine, 1000 );
			std::string Material;
			for ( int j = 0; j < ColCount; ++j )
			{
				switch ( CurrentLine[j] )
				{
				case '%': 
					map[i][j] = 10;
					Material = "BumpMaterial.fx";
					WallBlockNumbers.push_back(World.AddBlock( Vector3(BlockDimensionSize * ( i - ColCount / 2.0f ), 0, BlockDimensionSize * ( j - ColCount / 2.0f ) ), 1, Material ));
					break;
				case '#': 
					map[i][j] = 5;
					Material = "bricks.fx";
					WallBlockNumbers.push_back(World.AddBlock( Vector3(BlockDimensionSize * ( i - ColCount / 2.0f ), 0, BlockDimensionSize * ( j - ColCount / 2.0f ) ), 1, Material ));
					break;
				case 't':
					TankStartupPositions.push_back( std::pair<int, int>( i, j ) );
					break;
				case 'm':
					MineStartupPositions.push_back( std::pair<int, int>( i, j ) );
					break;
				case 'b':
					BonusStartupPositions.push_back( std::pair<int, int>( i, j ) );
					break;
				default:
					break;
				}						
			}
		}
	}

	Environment(char *source)
	{
		IsActiveUserTank = true;
		ObjNumber = 0;
		ReadDataFromFile(source);

		UserFire = false;
		UserFireTime = 0;

		CompFire.resize(TankStartupPositions.size() - 1, false);
		CompFireTime.resize(TankStartupPositions.size() - 1, false);

		ParSystem = new EffParticleSystem( 7000 );
		
		CompTanks.resize(TankStartupPositions.size() - 1);
		ActiveCompTanks.resize(TankStartupPositions.size() - 1, true);
		g = 9.81f;
		mu = 0.01f;
		srand( (unsigned) time(NULL));
		int UserTankStartupPositionNumber = rand() % (CompTanks.size());

		UserTank = new GTank();
		UserTank->GameValue = 100;
		
		UserTank->SetPos(Vector3
			(BlockDimensionSize * ( TankStartupPositions[UserTankStartupPositionNumber].first - ColCount / 2.0f ), 
			0,
			BlockDimensionSize * ( TankStartupPositions[UserTankStartupPositionNumber].second - ColCount / 2.0f )));
		
		int CompNumber = 0;
		for (int i = 0; i < CompTanks.size() + 1; ++i)
			if (i != UserTankStartupPositionNumber)
			{
				CompTanks[CompNumber] = new GComputerTank( Vector3 (
					BlockDimensionSize * ( TankStartupPositions[i].first - ColCount / 2.0f ), 
					0,
					BlockDimensionSize * ( TankStartupPositions[i].second - ColCount / 2.0f )));
				CompTanks[CompNumber++]->GameValue = 100;
			}
	}

	~Environment()
	{
		delete UserTank;
		for (int i = 0; i < CompTanks.size(); ++i)
			delete CompTanks[i];
		delete ParSystem;
	}

	void DestroyCompTank(int n)
	{
		if (ActiveCompTanks[n]) ParSystem->CreateExplSprite( CompTanks[n]->GetPos(), 400 );
		ActiveCompTanks[n] = false;
	}

	void DestroyUserTank()
	{	
		if (IsActiveUserTank)
		ParSystem->CreateExplSprite( UserTank->GetPos(), 400 );
		IsActiveUserTank = false;
	}

	bool SeeHuman(int comp_number)
	{
		BBox Box;
		UserTank->GetBBox(Box);
		float t;
		Vector3 p0; CompTanks[comp_number]->GetTurretCenter(p0);
		Vector3 dir; CompTanks[comp_number]->GetTurretDir(dir);
		return (Box.TestRayIntersection(p0, dir, t) && (t > 0));
	}

	
	void MissileHitUser()
	{
		if (IsActiveUserTank)
		{
			UserTank->GameValue -= 10;
			if (UserTank->GameValue <= 0)
				DestroyUserTank();
		}
	}

	void MissileHitComp(int n)
	{
		if (ActiveCompTanks[n])
		{
			CompTanks[n]->GameValue -= 20;
			if (CompTanks[n]->GameValue <= 0)
				DestroyCompTank(n);
		}
	}
	
	void Action(float Time)
	{
		float delta_time = Time - cur_time;
		cur_time = Time;

		typedef member_hook< EffParticleEffect, EffParticleEffect::TListHook, &EffParticleEffect::ListHook > TEffListOps;
		typedef list< EffParticleEffect, TEffListOps, constant_time_size<false> > TEffectList;

		World.Draw();
		ParSystem->UpadateParticles();
		ParSystem->DrawParticles();

		Vector3 Dir; UserTank ->GetTurretDir(Dir);
		Vector3 TCenter; UserTank->GetTurretCenter(TCenter);
		Vector3 CompDir, CompCenter;
		TCenter -= Vector3(0, 10, 0);

		float Near = 4000;
		Vector3 NP = TCenter + Near*Dir;

		OBBox CompBox;
		OBBox CompBox2;
		OBBox UserBox;
		UserTank->GetOBBox(UserBox);

		for (int i = 0; i < CompTanks.size(); ++i)
		{
			if( ActiveCompTanks[i] )
			{
				CompTanks[i]->Move(0.1f);								
				CompTanks[i]->Draw();

				CompTanks[i]->GetTurretDir(CompDir);
				CompTanks[i]->GetTurretCenter(CompCenter);

				CompTanks[i]->SeeUser = SeeHuman(i);

				CompTanks[i]->GetOBBox( CompBox );

				if (UserFire)				
					if (CompBox.TestRayIntersection( TCenter, Dir, Near ) && (Near > 0))
					{
						CompTanks[i]->missile = true;
						CompTanks[i]->MissileCollide = true;
					}

				if (CompTanks[i]->Status == 5)
					CompTanks[i]->missile = false;			
				
				UserFire = false;

				if (CompFire[i])
					UserTank->MissileCollide = true;

				CompFire[i] = false;

				Vector3 dist = UserTank->Position - CompTanks[i]->Position;
				if (dist.Length() < 400)
					if (UserBox.CheckOBBox( CompBox ) || CompBox.CheckOBBox( UserBox ))
						CompTanks[i]->TankCollide = true;

				for (int j = i + 1; j < CompTanks.size(); ++j)
				{
					dist = CompTanks[i]->Position - CompTanks[j]->Position;
					if (dist.Length() < 400)
					{
						CompTanks[j]->GetOBBox( CompBox2 );
						if (CompBox2.CheckOBBox( CompBox ) || CompBox2.CheckOBBox( CompBox ))
						{
							CompTanks[i]->TankCollide = true;						
							CompTanks[j]->TankCollide = true;
						}
					}
				}
			}
		}
		
		if (IsActiveUserTank)
		{
			BBox wallBox;
			for (int i = 0; i < WallBlockNumbers.size(); ++i)
			{
				wallBox = World.GetBlockOBBox(WallBlockNumbers[i]);

				if (wallBox.CheckBBox( UserBox.Box ) || UserBox.CheckBBox( wallBox ))
					UserTank->WallCollide = true;
			}
			UserTank->Friction(delta_time, mu);
			UserTank->Move(0.1f);
			UserTank->Draw();
		}

		GAuxiliary::Get().Draw();
		/*
		UserTank->GetOBBox( UserBox );
		UserTank->MissileCollide = false;
		UserTank->TankCollide = false;
		UserTank->WallCollide = false;

		for (int i = 0; i < CompTanks.size(); ++i)
		{
			CompTanks[i]->MissileCollide = false;
			CompTanks[i]->TankCollide = false;
			CompTanks[i]->WallCollide = false;
			CompTanks[i]->SeeUser = false;
		}*/
	}


	bool Win()
	{
		int comp_number = 0;
		for (int i = 0; i < CompTanks.size(); ++i)
			if (ActiveCompTanks[i])
				return false;
		return true;
	}

	bool Lost()
	{
		return !IsActiveUserTank;
	}
	int Conditions(int TableNumber, int CondNumber, float cur_time)
	{
		bool res;
		switch (TableNumber)
		{
		case 1:
			{
				switch (CondNumber)
				{
				case 1: 
					{
						GetNextObject();
						int comp_number = 0;
						for (int i = 0; i < CompTanks.size(); ++i)
							if (ActiveCompTanks[i])
								++comp_number;
						res = comp_number == 0;
					}
					break;
				case 2:
					{				
						int comp_number = 0;
						for (int i = 0; i < CompTanks.size(); ++i)
							if (ActiveCompTanks[i])
								++comp_number;
						res = (!(comp_number == 0) && (!IsActiveUserTank));			
					}
					break;
				}
			}
			break;
		case 2:
			{
				switch (CondNumber)
				{
				case 1: res = ObjNumber > 0; break;
				case 2:	res = ObjNumber == 0; break;
				}			
			}
			break;
		case 3:
			{
				switch (CondNumber)
				{
				case 1: res = CompTanks[ObjNumber - 1]->TankCollide; break;
				case 2:	res = CompTanks[ObjNumber - 1]->WallCollide; break;
				case 3:	res = CompTanks[ObjNumber - 1]->MissileCollide; break;
				case 4:	res = CompTanks[ObjNumber - 1]->SeeUser; break;
				case 5: res = CompTanks[ObjNumber - 1]->GameValue <= 0; break;
				}		
			}
			break;
		case 4:
			{
				switch (CondNumber)
				{
				case 1: res = CompTanks[ObjNumber - 1]->Status == 0; break;
				case 2:	res = CompTanks[ObjNumber - 1]->Status == 1; break;
				case 3:	res = CompTanks[ObjNumber - 1]->Status == 2; break;
				case 4:	res = CompTanks[ObjNumber - 1]->Status == 3; break;
				case 5: res = CompTanks[ObjNumber - 1]->Status == 4; break;
				case 6: res = CompTanks[ObjNumber - 1]->IsRotating(); break;
				case 7: res = CompTanks[ObjNumber - 1]->IsMoving(); break;
				}
			}
			break;
		case 5:
			{
				switch (CondNumber)
				{
				case 1: res = CompTanks[ObjNumber - 1]->GameValue > 90; break;
				case 2: res = CompTanks[ObjNumber - 1]->GameValue > 80; break;
				case 3: res = CompTanks[ObjNumber - 1]->GameValue > 70; break;
				case 4: res = CompTanks[ObjNumber - 1]->GameValue > 60; break;
				case 5: res = CompTanks[ObjNumber - 1]->GameValue > 50; break;
				case 6: res = CompTanks[ObjNumber - 1]->GameValue > 45; break;
				case 7: res = CompTanks[ObjNumber - 1]->GameValue > 40; break;
				case 8: res = CompTanks[ObjNumber - 1]->GameValue > 35; break;
				case 9: res = CompTanks[ObjNumber - 1]->GameValue > 30; break;
				case 10: res = CompTanks[ObjNumber - 1]->GameValue > 25; break;
				case 11: res = CompTanks[ObjNumber - 1]->GameValue > 20; break;
				case 12: res = CompTanks[ObjNumber - 1]->GameValue > 15; break;
				case 13: res = CompTanks[ObjNumber - 1]->GameValue > 10; break;
				}
			}
			break;
		case 6:
			{
				switch (CondNumber)
				{
				case 1: res = UserTank->WallCollide; break;				
				case 2: res = UserTank->MissileCollide; break;	
				case 3: res = UserTank->GameValue <= 0; break;
				}
			}
			break;
		case 7:
			{
				switch (CondNumber)
				{
				case 1: res = CompTanks[ObjNumber - 1]->Status == 0; break;
				case 2:	res = CompTanks[ObjNumber - 1]->Status == 1; break;
				case 3:	res = CompTanks[ObjNumber - 1]->Status == 2; break;
				case 4:	res = CompTanks[ObjNumber - 1]->Status == 3; break;
				case 5: res = CompTanks[ObjNumber - 1]->Status == 4; break;
				case 6: res = CompTanks[ObjNumber - 1]->Status == 5; break; 
				case 7: res = CompTanks[ObjNumber - 1]->IsRotating(); break;
				case 8: res = CompTanks[ObjNumber - 1]->TurretRot.IsRotating(); break;
				case 9: res = CompTanks[ObjNumber - 1]->IsMoving(); break;
				}
			}	
		}
		if (res)
			return 1;
		else
			return 0;
	}
	int Actions(int TableNumber, int CondNumber)
	{
		switch (TableNumber)
		{
		case 3:
			{
				switch (CondNumber)
				{
				case 1: DestroyCompTank(ObjNumber - 1); break;
				case 2: 
					CompTanks[ObjNumber - 1]->GameValue -= 10; 
					CompTanks[ObjNumber - 1]->MissileCollide = false; 
					break;
				case 3: DestroyCompTank(ObjNumber - 1); break;
				}
			}
		case 4: 
			CompTanks[ObjNumber - 1]->Core(); 
			break;
		case 5: 
			{
				switch (CondNumber)
				{
				case 1: CompTankFire(ObjNumber - 1, 100); break;
				case 2: CompTankFire(ObjNumber - 1, 90); break;
				case 3: CompTankFire(ObjNumber - 1, 80); break;
				case 4: CompTankFire(ObjNumber - 1, 70); break;
				case 5: CompTankFire(ObjNumber - 1, 60); break;
				case 6: CompTankFire(ObjNumber - 1, 50); break;
				case 7: CompTankFire(ObjNumber - 1, 45); break;
				case 8: CompTankFire(ObjNumber - 1, 40); break;
				case 9: CompTankFire(ObjNumber - 1, 35); break;
				case 10: CompTankFire(ObjNumber - 1, 30); break;
				case 11: CompTankFire(ObjNumber - 1, 20); break;
				case 12: CompTankFire(ObjNumber - 1, 15); break;
				case 13: CompTankFire(ObjNumber - 1, 10); break;
				case 14: CompTankFire(ObjNumber - 1, 9); break;
				}	
			}
			break;
		case 6: 
			{
			switch (CondNumber)
				{
				case 1: DestroyUserTank(); break;
				case 2: UserTank->GameValue -= 20; UserTank->MissileCollide = false; break;
				}	
			}
			break;
		case 7: 
			{

			}
			CompTanks[ObjNumber-1]->Core(); break;
			break;
		}
	return 1;
	}
};