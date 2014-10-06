#pragma once

#include "Rendering.h"
#include "Camera.h"

class SceneManager
{
	SceneManager( const SceneManager& );
	SceneManager& operator=( const SceneManager& );
	GCamera*				ActiveCamera;
	float					AbsTime;
	friend class			EffectHelper;
	D3DXMATRIX				ProjectionMatrix;
	D3DXMATRIX				ViewMat;
	D3DXMATRIX				ViewProj;

	SceneManager();
	~SceneManager();

	// Глобальный направленный источник освещения.
	Vector3					LightDir;

	// Используемые техники.


public:
	SharedParameterList		*LightParams;

	void		SetLight( const Vector3& Dir );
	void		SetActiveCamera( GCamera* Camera );
	void		GetEyePos( Vector3& Pos ) const;
	GCamera*	GetActiveCamera();
	void		SetProjection( const D3DXMATRIX& PM );
	float		GetAbsTime() const;
	void		BeginFrame( float CurTime );
	void		EndFrame( float CurTime );
	const		D3DXMATRIX& GetViewMatrix() const;
	const		D3DXMATRIX& GetViewProjMatrix() const;
	void		GetViewDirection( Vector3& DirVec );

	static	SceneManager& GetInstance();
};