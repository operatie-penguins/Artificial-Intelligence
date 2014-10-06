#pragma once
#include "meshobject3d.h"

class CBlondes : public CMeshObject3D
{
public:
	bool Hod_b;

	CBlondes(CScene3D* _Scene3D);
	~CBlondes();

	bool Render();
	bool Update(float fElpasedTime);
};
