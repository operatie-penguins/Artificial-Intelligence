
#include "meshobject3d.h"

class CPole :public CMeshObject3D
{
public:
	CPole(CScene3D* _Scene3D);
	~CPole();
	bool Render();
	bool Update(float fElpasedTime);
};
