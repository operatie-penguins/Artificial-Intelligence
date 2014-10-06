#pragma once
#include "meshobject3d.h"

class CHuman : public CMeshObject3D
{
public:
	bool Hod_h;

	CHuman(CScene3D* _Scene3D);
	~CHuman();

	bool Render();
	bool Update(float fElpasedTime);
};
