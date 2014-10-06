#include "Scene.h"

SceneManager::SceneManager() : AbsTime(0.0f)
{
	LightParams = ResourceManager::GetInstance().Register(
		new SharedParameterList,
		"GlobalParamList"
	);
	LightParams->RegisterParameter( "ViewProj", "float4x4" );
	LightParams->RegisterParameter( "EyePos", "float3" );
	LightParams->RegisterParameter( "ViewMat", "float4x4" );
	LightParams->RegisterParameter( "LightDir", "float3" );

	LightDir = Vector3( -1, 1, 0 );
	LightDir.Normalize();
	LightParams->SetVector( "LightDir", LightDir );
}

SceneManager::~SceneManager()
{
	LightParams->Release();
}

void SceneManager::SetActiveCamera( GCamera* Camera )
{
	ActiveCamera = Camera;
}

void SceneManager::GetEyePos( Vector3& Pos ) const
{
	ActiveCamera->GetCameraPos( Pos );
}

GCamera* SceneManager::GetActiveCamera()
{
	return ActiveCamera;
}

void SceneManager::SetProjection( const D3DXMATRIX& PM )
{
	ProjectionMatrix = PM;
}

float SceneManager::GetAbsTime() const
{
	return AbsTime;
}

// Вызывается в начале игрового цикла, до вызова соответствующего метода
// в других классах.
void SceneManager::BeginFrame( float CurTime )
{
	AbsTime = CurTime;
	if( ActiveCamera )
	{
		// Устанавливаем текущие матрицы.
		ActiveCamera->GetViewMatrix( ViewMat );
		D3DXMatrixMultiply( &ViewProj, &ViewMat, &ProjectionMatrix );
		LightParams->SetMatrix( "ViewProj", ViewProj );
		LightParams->SetMatrix( "ViewMat", ViewMat );
		Vector3 EyePos;
		ActiveCamera->GetCameraPos( EyePos );
		LightParams->SetVector( "EyePos", EyePos );
	}
}

void SceneManager::EndFrame( float CurTime )
{
	AbsTime = CurTime;
}

const D3DXMATRIX& SceneManager::GetViewMatrix() const
{
	return ViewMat;
}

const D3DXMATRIX& SceneManager::GetViewProjMatrix() const
{
	return ViewProj;
}

void SceneManager::GetViewDirection( Vector3& DirVec )
{
	DirVec.x = ViewMat._13;
	DirVec.y = ViewMat._23;
	DirVec.z = ViewMat._33;
}

SceneManager& SceneManager::GetInstance()
{
	static SceneManager SMng;
	return SMng;
}