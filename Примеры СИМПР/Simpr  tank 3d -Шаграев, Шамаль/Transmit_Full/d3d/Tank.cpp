#include "Tank.h"
#include "Game.h"

// M1 AbramsGTank::GTank() : GActor()

GTank::GTank() : GActor()
{
	Register( "GTank" );
	ResourceManager& RM = ResourceManager::GetInstance();

	Model = GModel::LoadModel( "M1W11.3ds", "Models/", "Models/" );
	if( !Model )
	{
		Error( "Unable to load model" );
	}
	Hull = new Res3DSMesh( "studio.m13|studio.m11", Model );
	Hull = ResourceManager::GetInstance().Register( Hull, "Tank_Hull" );
	Turret = new Res3DSMesh( "studio.m14|studio.m10|studio.m1a|", Model );
	Turret = ResourceManager::GetInstance().Register( Turret, "Tank_Turret" );
	Tracks = new Res3DSMesh( "studio.m12", Model );
	Tracks = ResourceManager::GetInstance().Register( Tracks, "TankTracks" );

	/*Model = GModel::LoadModel( "M1_Kaw.3ds", "Models/M1/", "Models/M1/" );
	if( !Model )
	{
		Error( "Unable to load model" );
	}
	Hull = new Res3DSMesh( "Cylinder01", Model );
	Hull = ResourceManager::GetInstance().Register( Hull, "Tank_Hull" );
	Turret = new Res3DSMesh( "up", Model );
	Turret = ResourceManager::GetInstance().Register( Turret, "Tank_Turret" );
	Tracks = new Res3DSMesh( "Tracks", Model );
	Tracks = ResourceManager::GetInstance().Register( Tracks, "TankTracks" );*/

	// Загружаем пары колес.
	static const char* WhNames[] = {
		"WP1", "WP2", "WP3", "WP4", "WP5", "WP6", "WP7", "WP8", "WP9"
		//"Wp1", "Wp2", "Wp3", "Wp4", "Wp5", "Wp6", "Wp7", "Wp8", "Wp9"
	};


	for( int i=0; i < 9; i++ )
	{
		Wheels.push_back( 
			RM.Register( 
				new Res3DSMesh( WhNames[i], Model ),
				std::string("GTank")+WhNames[i]
			)
		);
		assert( Wheels[i] );
	}

	HullMat = ResourceManager::GetInstance().Register(
		new ResMaterial( "Effects/Tank/TankHull.fx", SceneManager::GetInstance().LightParams ),
		"Effects/Tank/TankHull.fx"
	);

	TracksMat = new ResMaterial( HullMat, "RenderTracks" );

	MVPMatParam.AttachTo( HullMat, "ModelViewProjMat" );
	TracksPos.AttachTo( TracksMat, "TrackPos" );
	ModelViewIT.AttachTo( HullMat, "ModelViewIT" );

	MovSpeed = 5.0f;//1.5f;
	RotSpeed = 1.0f;//0.2f;
	// Устанавливаем начальное направление.
	SetDirection( 90 );
	TurretRot.SetDirection( 90 );

	TrackPos = 0;
	
	TankCollide = false;
	WallCollide = false;
	MissileCollide = false;
	SeeUser = false;
}

GTank::~GTank()
{
	Hull->Release();
	Turret->Release();
	Tracks->Release();
	HullMat->Release();

	TracksMat->Release();

	std::for_each( Wheels.begin(), Wheels.end(), boost::bind(&Res3DSMesh::Release, _1) );

	Unregister( "GTank" );
}

// Поворот башней в локальной системе координат танка.
void GTank::RotateTurret( float Angle )
{
	TurretRot.RotateLocal( Angle );
}

// Установка матрицы преобразования объект -> мир.
void GTank::SetupModelMat()
{
	D3DXQUATERNION HullRot;
	D3DXMATRIXA16	Id( 1, 0, 0, 0,
		                0, 0, 1, 0,
						0, 1, 0, 0,
						0, 0, 0, 1
					  );
	D3DXQuaternionRotationAxis( &HullRot, &Up, DegToRad(Yaw) );
	D3DXMatrixAffineTransformation(
		&ModelMat,
		1,
		Mod2Vector3(Hull->GetRotCenter()),
		&HullRot,
		Position
	);
	D3DXMatrixMultiply( &ModelMat, &Id, &ModelMat );
	// FIXME: ортогональное + перенос.
	D3DXMatrixInverse( &World2Local, NULL, &ModelMat );

	// Вращаем башней.
	D3DXQUATERNION TurRotQ;
	D3DXQuaternionRotationAxis( &TurRotQ, &D3DXVECTOR3(0,0,1), DegToRad(TurretRot.Yaw) );
	D3DXMatrixAffineTransformation( &TurModelMat, 1, (D3DXVECTOR3*)&Turret->GetRotCenter(), &TurRotQ, 0 );
}

void GTank::DrawWheels()
{	
	static float WheelAngle = 0; // FIXME: Testing only.

	D3DXQUATERNION	WhRotQ;
	D3DXMATRIXA16	Rot;
	D3DXQuaternionRotationAxis( &WhRotQ, &D3DXVECTOR3(0,1,0), DegToRad(WheelAngle) );
	for( unsigned i=0; i < Wheels.size(); i++ )
	{
		D3DXMatrixAffineTransformation( &Rot, 1, *(Vector3*)&Wheels[i]->GetRotCenter(), &WhRotQ, 0 );
		D3DXMatrixMultiply( &Rot, &Rot, &ModelMat );
		D3DXMatrixMultiply( MVPMatParam.GetMatPtr(), &Rot, &SceneManager::GetInstance().GetViewProjMatrix() );
		D3DXMatrixMultiply( ModelViewIT.GetMatPtr(), &Rot, &SceneManager::GetInstance().GetViewMatrix() );

		HullMat->SetParameter( ModelViewIT );
		HullMat->SetParameter( MVPMatParam );
		Wheels[i]->Draw( HullMat );
	}

	// FIXME: Testing only.
	if (IsMoving() && (RemDist > 0))
		WheelAngle -= 0.8f;
	else if (IsMoving() && (RemDist < 0))
		WheelAngle += 0.8f;
	Vector3 Direction = GetDirVector();

	if (IsMovingVector())
		WheelAngle -= Sign(Speed.x*Direction.x + Speed.y*Direction.y)*sqrt(Speed.x*Speed.x + Speed.y*Speed.y)/20.0f;
}

void GTank::Draw()
{
	D3DXMatrixMultiply( MVPMatParam.GetMatPtr(), &ModelMat, &SceneManager::GetInstance().GetViewProjMatrix() );
	D3DXMatrixMultiply( ModelViewIT.GetMatPtr(), &ModelMat, &SceneManager::GetInstance().GetViewMatrix() );

	HullMat->SetParameter( MVPMatParam );
	HullMat->SetParameter( ModelViewIT );
	Hull->Draw( HullMat );

	//Hull->DrawNormals( IT );

	// Вращаем гусеницы.
	TracksPos = TrackPos;
	TracksMat->SetParameter( TracksPos );
	Tracks->Draw( TracksMat );

	D3DXMATRIX Rot;
	D3DXMatrixMultiply( &Rot, &TurModelMat, &ModelMat );
	D3DXMatrixMultiply( MVPMatParam.GetMatPtr(), &Rot, &SceneManager::GetInstance().GetViewProjMatrix() );

	D3DXMatrixMultiply( ModelViewIT.GetMatPtr(), &TurModelMat, ModelViewIT.GetMatPtr() );
	HullMat->SetParameter( ModelViewIT );
	HullMat->SetParameter( MVPMatParam );
	Turret->Draw( HullMat );

	//Turret->DrawNormals( Rot );
	DrawWheels();

	// DEBUGGING
	/*Vector3 RotPivot = Transform( ModelMat, *(Vector3*)&Hull->GetRotCenter() );
	GAuxiliary::Get().DrawCoords( Vector3(1,0,0), Vector3(0,1,0), Vector3(0,0,1),
		RotPivot );*/
	/*Vector3 TurretCenter, TurretDir;
	GetTurretCenter( TurretCenter );
	GetTurretDir( TurretDir );
	GAuxiliary::Get().DrawCoords( TurretDir, Vector3(0,1,0), Vector3(1,0,0), TurretCenter );*/
}

void GTank::Friction(float time, float mu)
{/*
	float g = 9.81f;
	if ( Speed.x > 0 )
	{
		Speed.x -= time*mu*g;
		if ( Speed.x < 0 ) 
			Speed.x = 0;
	}
	else
	{			
		Speed.x += time*mu*g;
		if ( Speed.x > 0 ) 
			Speed.x = 0;
	}

	if ( Speed.y > 0 )
	{
		Speed.y -= time*mu*g;
		if ( Speed.y < 0 ) 
			Speed.y = 0;
	}
	else
	{			
		Speed.y += time*mu*g;
		if ( Speed.y > 0 ) 
			Speed.y = 0;
	}

	if ( Speed.z > 0 )
	{
		Speed.z -= time*mu*g;
		if ( Speed.z < 0 ) 
			Speed.z = 0;
	}
	else
	{			
		Speed.z += time*mu*g;
		if ( Speed.z > 0 ) 
			Speed.z = 0;
	}

	Vector3 Direction = GetDirVector();
	float norma = sqrt(Speed.x*Speed.x + Speed.y * Speed.y);*/
	Speed.x *= 0.995;
	Speed.z *= 0.995;
	RotatingSpeed *= 0.95;
}
void GTank::BeginFrame( float DeltaTime )
{
	SetupModelMat();
	TurretRot.RotateOneStep( 0.2f );
	//Move();
	if ( IsMoving() && RemDist > 0 )
	{	
		TrackPos += 0.01f;
	}
	else if ( IsMoving() && RemDist < 0 )
	{	
		TrackPos -= 0.01f;
	}
	else if ( IsMovingVector() )
	{
		Vector3 Direction = GetDirVector();
		float quadr = Speed.x*Direction.x + Speed.z*Direction.z;
		TrackPos += quadr/1000;
	}
}

void GTank::EndFrame( float DeltaTime )
{
}

void GTank::GetOBBox( OBBox& OBox ) const
{
	BBox Box( Hull->GetBBox() );
	//Box += Turret->GetBBox().Transform( TurModelMat );
	OBox.LocalMat = World2Local;
	OBox.Box = Box;
}

void GTank::GetBBox( BBox& Box ) const
{
	Box = Hull->GetBBox();
	//Box += Turret->GetBBox().Transform( TurModelMat );
	Box = Box.Transform( ModelMat );
}

void GTank::GetTurretCenter( Vector3& Center ) const
{
	ModVector RotPivot = Turret->GetRotCenter();
	Center.x = RotPivot.X;
	Center.y = RotPivot.Y;
	Center.z = RotPivot.Z;
	Center = Transform( ModelMat, Center );
}

void GTank::GetTurretDir( Vector3& Dir ) const
{
	Dir = Vector3(-1, 0, 0);
	D3DXMATRIX Rot;
	D3DXMatrixMultiply( &Rot, &TurModelMat, &ModelMat );
	Dir = TransformVector( Rot, Dir ); 
}

/*
vector<pair<float, float> > GTank::GetCorners()
{
	vector<pair<float, float> > result;

	pair<float, float> direction(GetDirVector().x, GetDirVector().z);
	pair<float, float> normal(direction.second, -direction.first);

	result.push_back(pair<float, float>
		((2*Position.x + direction.first * 130 + normal.first * 280) / 2, 
		(2*Position.z + direction.second * 130 + normal.second * 280) / 2));
	
	result.push_back(pair<float, float>
		((2*Position.x + direction.first * 130 - normal.first * 280) / 2, 
		(2*Position.z + direction.second * 130 - normal.second * 280) / 2));
	
	result.push_back(pair<float, float>
		((2*Position.x - direction.first * 130 - normal.first * 280) / 2, 
		(2*Position.z - direction.second * 130 - normal.second * 280) / 2));
	
	result.push_back(pair<float, float>
		((2*Position.x - direction.first * 130 + normal.first * 280) / 2, 
		(2*Position.z - direction.second * 130 + normal.second * 280) / 2));	

	return result;
}

bool GTank::Inside(pair<float, float> &point, pair<float, float> &center, pair<float, float> &v1, pair<float, float> &v2)
{
	pair<float, float> point_local(point.first - center.first, point.second - center.second);
	float b = ( point.first * v1.second - point.second * v1.first )/( v2.first * v1.second - v2.second * v1.first );
	float a = ( point.first * v2.second - point.second * v2.first )/( v1.first * v2.second - v1.second * v2.first );
	if ((a > 0) && (b > 0) && (a + b <= 1)) return true;
	return false;
}

bool GTank::Inside(pair<float, float> &point)
{
	vector<pair<float, float> > corners = GetCorners();
	pair<float, float> center(Position.x, Position.z);
	pair<float, float> local_point(point.first - center.first, point.second - center.second);
	for (int i = 0; i < 4; ++i)
	{
		pair<float, float> v1(corners[i].first - center.first, corners[i].second - center.second);
		pair<float, float> v2(corners[(i + 1) % 4].first - center.first, corners[(i + 1) % 4].second - center.second);

		if (Inside(local_point, center, v1, v2))
			return true;
	}
	return false;
}

pair<float, float> GTank::GetForce(std::vector<pair<float,float> > &EnemyCorners)
{
	vector<pair<float, float> > OwnCorners = GetCorners();
	pair<float, float> v1, v2;
	pair<float, float> center(Position.x, Position.z);

	float norma;

	for (int i = 0; i < 4; ++i)
	{
		v1 = EnemyCorners[i];
		v2 = EnemyCorners[(i + 1) % 4];
		
		for (int j = 0; j < 4; ++j)
		{
			if (Inside(OwnCorners[j], center, v1, v2))
			{
				norma = sqrt((v1.first + v2.first)*(v1.first + v2.first) + (v1.second + v2.second)*(v1.second + v2.second));
				return pair<float, float>((v1.first + v2.first)/norma, (v2.second + v2.second)/norma);
			}
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		v1 = OwnCorners[i];
		v2 = OwnCorners[(i + 1) % 4];
		
		for (int j = 0; j < 4; ++j)
		{
			if (Inside(EnemyCorners[j], center, v1, v2))
			{
				norma = sqrt((v1.first + v2.first)*(v1.first + v2.first) + (v1.second + v2.second)*(v1.second + v2.second));
				return pair<float, float>(-(v1.first + v2.first)/norma, -(v2.second + v2.second)/norma);
			}
		}
	}
	return pair<float, float>(0.0f,0.0f);
}

void GTank::FeelTheForce(pair<float, float> &force)
{
	float norma = sqrt( Speed.x * Speed.x + Speed.z * Speed.z );

	Speed.x += ( 10 + norma / 10 ) * force.first;
	Speed.y += ( 10 + norma / 10 ) * force.second;/*
	float scalar = fabs(Speed.x * force.first + Speed.z * force.second);
	Speed.x += 2 * force.first * scalar / normaForce / normaForce ;
	Speed.z += 2 * force.second * scalar / normaForce / normaForce ;
}*/