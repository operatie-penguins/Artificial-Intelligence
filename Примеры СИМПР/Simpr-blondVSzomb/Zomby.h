



#include "meshobject3d.h"


class CZomby: public CMeshObject3D
{
public:
	bool Hod_z; //0 - �� ������, 1 - ������

    CZomby(CScene3D* _Scene3D);
	~CZomby();

	bool Render();
	bool Update(float fElpasedTime);
};

