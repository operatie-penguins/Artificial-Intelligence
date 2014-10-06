//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Shibarshin A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CPlayer
//////////////////////////////////////////////////////////////////

#ifndef STAR_H
#define STAR_H



#include "MeshObject3D.h"

class CScene3D; 



class CPlayer : public CMeshObject3D
{
public:
	int Team;        //0 - att, 1 - def
	bool HaveBall;
	int Side;        //0 - left, 1 - center, 2 - right

	CPlayer(CScene3D* _Scene3D);
	~CPlayer();

	bool Render();
	bool Update(float fElpasedTime);

	void MoveForward();
	void MakePass(CPlayer* _CPlayer);

};



#endif