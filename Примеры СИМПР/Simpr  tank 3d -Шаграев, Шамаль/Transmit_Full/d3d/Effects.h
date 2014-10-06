#pragma once

#include "Utils.h"
#include "Material.h"
#include "Scene.h"
#include <boost/intrusive/list.hpp>

using namespace boost::intrusive;

class EffParticle
{
public:
	typedef list_member_hook< > TListHook;
	TListHook	ListHook;
	float		Z;
	int			Index;
	class EffParticleEffect		*Effect;

	bool operator<( const EffParticle& Other ) const
	{
		return( Z > Other.Z );
	}
};

class EffParticleEffect
{
protected:
	class EffParticleSystem		*ParSystem;

	float				CreationTime;
	float				EffectTime;
	float				LastUpdateTime;
public:

	typedef list_member_hook< link_mode<auto_unlink> > TListHook;
	TListHook		ListHook;

	EffParticleEffect( class EffParticleSystem *ParticleSystem )
		: EffectTime(0), ParSystem(ParticleSystem)
	{
		LastUpdateTime =
		CreationTime = SceneManager::GetInstance().GetAbsTime();
	}

	bool IsAlive() const
	{
		return !( EffectTime > 0.99 );
	}

	// Возращает макс. количество частиц, которые будут добавлены при следующем Update.
	virtual int GetParticlesNumber() const = 0;
	virtual void Update( float CurTume ) = 0;
	virtual void Draw() = 0;

	virtual ~EffParticleEffect()
	{}
};

//------------------------------------------- Эффекты ----------------------------------------------------

// Адаптация кода из DirectX SDK.
class EffSmoke : public EffParticleEffect
{
	class SmokeParticle : public EffParticle
	{
	public:
		Vector3		Pos;
		Vector3		Vel;
		float		Life;
		float		Size;
	};

	std::vector<SmokeParticle>	SmokeParticles;

	// Параметры.
	float FadeDistance;
	float ParticleLifeSpan;
	float EmitRate;
	float ParticleVel;
	float ParticleMaxSize;
	float ParticleMinSize;

	int LastEmitted;
	void EmitParticle( SmokeParticle& Prt );
	float LastEmitTime;
	int NumPart;

public:

	// Общие характеристики.
	Vector3		EffPosition;
	Vector3		EffVelocity;
	float		EffLifeTime;

	EffSmoke( class EffParticleSystem *ParticleSystem, int NumParticles = 500 );
	virtual void Update( float CurTime );
	virtual void Draw();
	virtual int GetParticlesNumber() const
	{
		return SmokeParticles.size();
	}
	virtual ~EffSmoke();
};

class EffExplosionSprite : public EffParticleEffect
{
	EffParticle ExplSprite;

	// Параметры.
	float		LifeTime;
public:
	float		EffSize;
	Vector3		EffPosition;
	float		SpriteNum;
	
	EffExplosionSprite( class EffParticleSystem *ParticleSystem );
	virtual void Update( float CurTime );
	virtual void Draw();
	virtual int GetParticlesNumber() const
	{
		return 1;
	}
	virtual ~EffExplosionSprite();
};

class EffTrail : public EffParticleEffect
{
	class TrailSprite : public EffParticle
	{
	public:
		Vector3		Pos;
		float		Dist;
		float		Size;
	};

	std::vector<TrailSprite>	TrailSprites;
	float		LifeTime;
	float		DissolveTime;
	float		Density;
	//float		Size;
	int			MaxSprites;
	int			NumSprites;
	float		AnimPeriod;
	float		SizeMin;
	float		SizeMax;

	Vector3		A;
	Vector3		B;
	Vector3		C;
	float		TrailLen;
	float		FlyTime;

	// Подинтегральная функция для вычисления длины кривой.
	float CurveLenI( float T )
	{
		return (2.0f*(T*C + (1 - 2.0f*T)*B - (1 - T)*A )).Length();
	}
public:
	float		AnimTime;
	float		DissolveFactor;

	EffTrail( class EffParticleSystem *ParSystem,
		const Vector3& A,
		const Vector3& B,
		const Vector3& C,
		float TrailLength,
		float fFlyTime );
	~EffTrail();
	
	virtual int GetParticlesNumber() const
	{
		return MaxSprites;
	}

	virtual void Update( float CurTime );
	virtual void Draw();
};

// Настраивает эффекты, задействованные в системе частиц.
class EffParticleRenderer
{
	ResMaterial *SmokeMat;
	ResMaterial *ExplSprMat;
	ResMaterial *TrailMat;

public:
	ShaderParam<float>	AnimTime;
	ShaderParam<float>	DissolveFactor;
	ShaderParam<float>	SpriteNum;

	EffParticleRenderer();
	MaterialBin DrawBin;
	virtual void DrawParticleSubset( ResMaterial *Mat ) = 0;

	~EffParticleRenderer();
	void DrawSmoke( EffSmoke& Eff );
	void DrawExplosionSprite( EffExplosionSprite& Eff );
	void DrawTrail( EffTrail& Eff );
};

class EffParticleSystem : public EffParticleRenderer
{
public:
	typedef TVertex<0,0,0,3,2,0,0,1>			ParamVF;

private:
	typedef member_hook< EffParticleEffect, EffParticleEffect::TListHook, &EffParticleEffect::ListHook > TEffListOps;
	typedef list< EffParticleEffect, TEffListOps, constant_time_size<false> > TEffectList;

	TEffectList							EffectList;

	typedef TVertex<Position2f,SkipNormal,false,SkipTexCoord,SkipTexCoord,SkipTangent,SkipBinormal,0,ParamVF>	VF;

	// Основные ресурсы.
	typedef ResDynamicMesh<VF>		TBillboardsMesh;
	TBillboardsMesh					*BillboardsMesh;
	typedef ResDynamicMesh<ParamVF>	TParamMesh;
	TParamMesh						*ParamMesh;
	int								MaxBillboards;
	ParamVF							*ParamBuffer;
	int								CurIndex;

	void DrawParticleSubset( ResMaterial *Mat );
	void WriteIndicesForParticle( int ParNum );

	void FreeSpace( int NumParticles );
public:

	typedef member_hook< EffParticle, EffParticle::TListHook, &EffParticle::ListHook > TSortListOps;
	typedef list< EffParticle, TSortListOps, constant_time_size<true> > TParticleList;

	TParticleList					SortList;

	void CreateQuadsBuffer( ResDynamicMesh<VF> *Mesh );

	EffParticleSystem( int MaxBillboardsPerDraw );

	// Создание эффектов.
	void CreateSmoke( const Vector3& Position, const Vector3& Velocity, float LifeTime );
	void CreateExplSprite( const Vector3& Pos, float Size );
	void CreateFireTrail( const Vector3& A, const Vector3& B, const Vector3& C,
										float TrailLen, float FlyTime );

	// Общие методы.
	void DrawParticles();
	void UpadateParticles();
	void WriteParameter( const ParamVF& Data );
	int GetCurrentIndex() const
	{
		return CurIndex;
	}

	~EffParticleSystem();
};