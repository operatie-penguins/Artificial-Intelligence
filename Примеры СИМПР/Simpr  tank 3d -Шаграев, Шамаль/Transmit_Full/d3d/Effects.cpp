#include "Effects.h"
#include <boost/bind.hpp>

EffParticleSystem::EffParticleSystem( int MaxBillboardsPerDraw )
	: MaxBillboards(MaxBillboardsPerDraw)
{
	BillboardsMesh = ResourceManager::GetInstance().Register(
		new ResDynamicMesh<VF>( MaxBillboards*4, MaxBillboards*6,
				boost::bind(&EffParticleSystem::CreateQuadsBuffer, this, _1) ),
		"ParticleSystemBillboardMesh" );

	ParamMesh = ResourceManager::GetInstance().Register(
		new ResDynamicMesh<ParamVF>( 4*MaxBillboards, 0 ),
		"ParticleSystemParamMesh" );
}

EffParticleSystem::~EffParticleSystem()
{
	for( TEffectList::iterator It = EffectList.begin(); It != EffectList.end(); )
	{
		EffParticleEffect *Eff = &(*It++);
		delete Eff;
	}

	BillboardsMesh->Release();
	ParamMesh->Release();
}

void EffParticleSystem::CreateQuadsBuffer( ResDynamicMesh<VF> *Mesh )
{
	VF *Quads = Mesh->Begin( true, true );
	for( int i=0; i < MaxBillboards; i++, Quads += 4 )
	{
		Quads[0].Position().X = -1;
		Quads[0].Position().Y = -1;
		Quads[1].Position().X = 1;
		Quads[1].Position().Y = -1;
		Quads[2].Position().X = 1;
		Quads[2].Position().Y = 1;
		Quads[3].Position().X = -1;
		Quads[3].Position().Y = 1;

		Mesh->Index( 4*i+0 );
		Mesh->Index( 4*i+1 );
		Mesh->Index( 4*i+2 );
		Mesh->Index( 4*i+0 );
		Mesh->Index( 4*i+2 );
		Mesh->Index( 4*i+3 );
	}
	Mesh->End();
}

//-------------------------------------------------------------------------------------

// Удаляет из очереди NumParitcles старых частиц.
void EffParticleSystem::FreeSpace( int NumParticles )
{
	int NumDeleted = 0;
	for( TEffectList::iterator It = EffectList.begin();
		NumDeleted < NumParticles && It != EffectList.end();  )
	{
		NumDeleted += It->GetParticlesNumber();
		EffParticleEffect *Eff = &*It++;
		delete Eff;
	}
}

void EffParticleSystem::UpadateParticles()
{
	float CurTime = SceneManager::GetInstance().GetAbsTime();
	ParamBuffer = ParamMesh->Begin( true, false, 4*SortList.size(), 0 );
	ParamVF *First = ParamBuffer;
	CurIndex = 0;
	for( TEffectList::iterator It = EffectList.begin(); It != EffectList.end(); )
	{
		EffParticleEffect *Eff = &(*It);
		++It;
		if( !Eff->IsAlive() )
		{
			delete Eff;
		}
		else
		{
			// Проверяем свободное место.
			if( MaxBillboards - CurIndex < Eff->GetParticlesNumber() )
			{
				FreeSpace( Eff->GetParticlesNumber() );
				// Перезапуск.
				ParamBuffer = First;
				CurIndex = 0;
				It = EffectList.begin();
				continue;
			}

			ParamVF *PrevBufferState = ParamBuffer;
			Eff->Update( CurTime );
			CurIndex += (ParamBuffer - PrevBufferState) >> 2;
		}
	}
	ParamMesh->End();
}

void EffParticleSystem::WriteParameter( const ParamVF& Data )
{
	for( int i=0; i < 4; i++ )
		ParamBuffer[i] = Data;
	ParamBuffer += 4;
}

void EffParticleSystem::WriteIndicesForParticle( int ParNum )
{
	int IndexBase = ParNum << 2;
	BillboardsMesh->Index( IndexBase + 0 );
	BillboardsMesh->Index( IndexBase + 1 );
	BillboardsMesh->Index( IndexBase + 2 );
	BillboardsMesh->Index( IndexBase + 0 );
	BillboardsMesh->Index( IndexBase + 2 );
	BillboardsMesh->Index( IndexBase + 3 );
}

void EffParticleSystem::DrawParticles()
{
	SortList.sort();

	// Заполняем буфер индексов.
	BillboardsMesh->Begin( false, true, 0, 2*SortList.size() );
	std::for_each(
		SortList.begin(),
		SortList.end(),
		boost::bind( &EffParticleSystem::WriteIndicesForParticle, this, boost::bind(&EffParticle::Index,_1) )
	);
	BillboardsMesh->End();

	BillboardsMesh->SetupDIPCall();

	// Рисуем частицы.
	EffParticleEffect *PrevEffect = 0;
	int StartIndex = 0;
	DrawBin.Clear();
	for( TParticleList::iterator It = SortList.begin();
		It != SortList.end();
		++It )
	{
		if( PrevEffect != It->Effect )
		{
			StartIndex += DrawBin.NumIndices;
			if( PrevEffect )
				PrevEffect->Draw();
			DrawBin.Clear();
			DrawBin.StartIndex = StartIndex;
			PrevEffect = It->Effect;
		}
		DrawBin.Add( It->Index*4, 4, 2 );
	}
	if( PrevEffect )
		PrevEffect->Draw();
}

void EffParticleSystem::CreateSmoke(const Vector3 &Position, const Vector3 &Velocity, float LifeTime )
{
	EffSmoke *Eff = new EffSmoke( this );
	Eff->EffPosition = Position;
	Eff->EffVelocity = Velocity;
	Eff->EffLifeTime = LifeTime;
	EffectList.push_back( *Eff );
}

void EffParticleSystem::CreateExplSprite( const Vector3& Pos, float Size )
{
	EffExplosionSprite *Eff = new EffExplosionSprite( this );
	Eff->EffPosition = Pos;
	Eff->EffSize = Size;
	EffectList.push_back( *Eff );
}

void EffParticleSystem::CreateFireTrail( const Vector3& A, const Vector3& B, const Vector3& C,
										float TrailLen, float FlyTime )
{
	EffTrail *Eff = new EffTrail( this, A, B, C, TrailLen, FlyTime );
	EffectList.push_back( *Eff );
}

void EffParticleSystem::DrawParticleSubset( ResMaterial* Mat )
{
	DrawCallDelegate<MaterialBin*> DrawDeleg( ParamMesh, &TParamMesh::AttachAsStreamSource, &TParamMesh::DrawIP );
	Mat->Draw( DrawDeleg, &DrawBin );
}

//------------------------------------------------------------------------------------------------------------------

EffSmoke::EffSmoke( EffParticleSystem *ParticleSystem, int NumParticles )
		: EffParticleEffect(ParticleSystem), LastEmitted(0), NumPart(NumParticles)
{
	FadeDistance = 1.0f;
	ParticleLifeSpan = 10.0f;	// Время жизни частицы с.
	EmitRate = 120.0f;			// Скорость испускания частицы/с.
	ParticleVel = 30.0f;		// Скорость частиц.
	ParticleMaxSize = 60.0f;
	ParticleMinSize = 35.0f;
	NumPart = NumParticles = 500;

	LastEmitTime = 0;

	SmokeParticles.resize( NumParticles );

	// Инициализация частиц.
	for( std::vector<SmokeParticle>::iterator I = SmokeParticles.begin();
		I != SmokeParticles.end();
		++I )
	{
		I->Life = -1;
		I->Effect = this;
		ParSystem->SortList.push_back( *I );
	}
}

void EffSmoke::EmitParticle( SmokeParticle& Prt )
{
	Prt.Pos = EffPosition;
	Prt.Vel.x = EffVelocity.x + 0.5f*RandomFloat();
	Prt.Vel.y = EffVelocity.y + 0.5f*RandomFloat();
	Prt.Vel.z = EffVelocity.z + 0.5f*RandomFloat();
	Prt.Vel.Normalize();
	Prt.Vel *= ParticleVel;
	Prt.Life = 0;
	Prt.Size = 0;
}

void EffSmoke::Update( float CurTime )
{
	float LifeSq;
	Vector3 Vel;
	float TimeDelta = CurTime - LastUpdateTime;
	LastUpdateTime = CurTime;
	EffectTime += TimeDelta / EffLifeTime;

	Vector3 Dir;
	SceneManager::GetInstance().GetViewDirection( Dir );

	int NumParticlesToEmit = (int)((CurTime - LastEmitTime) * EmitRate);
	if( NumParticlesToEmit > NumPart )
		NumParticlesToEmit = NumPart;
	if( NumParticlesToEmit > 0 )
	{
		for( int i=0; i < NumParticlesToEmit; i++ )
		{
			EmitParticle( SmokeParticles[LastEmitted] );
			if( ++LastEmitted >= NumPart )
				LastEmitted = 0;
		}
		LastEmitTime = CurTime;
	}

	int Ind = ParSystem->GetCurrentIndex();
	for( std::vector<SmokeParticle>::iterator It = SmokeParticles.begin();
		It != SmokeParticles.end();
		++It )
	{
		if( It->Life > -1 )
		{
			LifeSq = It->Life * It->Life;
			Vel = (1.0f - 0.5f*LifeSq) * It->Vel;
			Vel.y += 0.5f;

			It->Pos += TimeDelta * Vel;
			It->Life += TimeDelta / ParticleLifeSpan;
			It->Size = ParticleMinSize + (ParticleMaxSize - ParticleMinSize) * It->Life;

			if( It->Life > 0.99 )
				It->Life = -1;

			// Добавляем информацию для сортировки.
			It->Z = Dir.Dot( It->Pos );
			It->Index = Ind++;

			EffParticleSystem::ParamVF Vertex;
			Vertex.TexCoord0() = It->Pos;
			Vertex.TexCoord1().X = It->Size;
			Vertex.TexCoord1().Y = It->Life;
			ParSystem->WriteParameter( Vertex );
		}
	}
}

void EffSmoke::Draw()
{
	ParSystem->DrawSmoke( *this );
}

EffSmoke::~EffSmoke()
{
	for( std::vector<SmokeParticle>::iterator It = SmokeParticles.begin();
		It != SmokeParticles.end();
		++It )
	{
		ParSystem->SortList.erase( ParSystem->SortList.s_iterator_to(*It) );
	}
}

//----------------------------------------------------------------------------------------------------------------

EffExplosionSprite::EffExplosionSprite( EffParticleSystem *ParticleSystem )
	: EffParticleEffect(ParticleSystem)
{
	ExplSprite.Index = ParSystem->SortList.size();
	ExplSprite.Effect = this;
	ParSystem->SortList.push_back( ExplSprite );

	LifeTime = 1.0;
	SpriteNum = RandomFloat();
}

void EffExplosionSprite::Update( float CurTime )
{
	EffectTime += (CurTime - LastUpdateTime) / LifeTime;
	LastUpdateTime = CurTime;

	EffParticleSystem::ParamVF  Vertex;
	Vertex.TexCoord0() = EffPosition;
	Vertex.TexCoord1().X = EffSize;
	Vertex.TexCoord1().Y = EffectTime;
	ParSystem->WriteParameter( Vertex );

	Vector3 Dir;
	SceneManager::GetInstance().GetViewDirection( Dir );
	ExplSprite.Z = Dir.Dot( EffPosition );
	ExplSprite.Index = ParSystem->GetCurrentIndex();
}

void EffExplosionSprite::Draw()
{
	ParSystem->DrawExplosionSprite( *this );
}

EffExplosionSprite::~EffExplosionSprite()
{
	ParSystem->SortList.erase( ParSystem->SortList.s_iterator_to( ExplSprite ) );
}

//----------------------------------------------------------------------------------------------------------------

EffTrail::EffTrail( EffParticleSystem *ParticleSystem,
				   const Vector3& PA, const Vector3& PB, const Vector3& PC, float TrailLength, float fFlyTime )
	: EffParticleEffect( ParticleSystem ), A(PA), B(PB), C(PC), FlyTime( fFlyTime )
{
	// Параметры.
	//Size = 20.0f;
	Density = 0.25f;
	MaxSprites = 100;
	DissolveTime = 1.0f;
	AnimPeriod = 5.0f;

	SizeMin = 10.0f;
	SizeMax = 20.0f;

	LifeTime = FlyTime + DissolveTime;
	// Приводим к диапазону [0,1)
	FlyTime			/= LifeTime;
	DissolveTime	/= LifeTime;
	AnimPeriod		/= LifeTime;
	float CurveLen = IntegrateQuadrature( 0, 1, boost::bind(&EffTrail::CurveLenI,this,_1) );
	if( CurveLen < TrailLen )
		TrailLen = CurveLen;
	TrailLen = TrailLength / CurveLen;
	NumSprites = (int)(TrailLength * Density);
	if( NumSprites > MaxSprites )
		NumSprites = MaxSprites;

	TrailSprites.reserve( NumSprites );
}

EffTrail::~EffTrail()
{
	for( std::vector<TrailSprite>::iterator I = TrailSprites.begin();
		I != TrailSprites.end();
		++I )
	{
		ParSystem->SortList.erase( ParSystem->SortList.s_iterator_to( *I ) );
	}
}

void EffTrail::Update( float CurTime )
{
	EffectTime += (CurTime - LastUpdateTime) / LifeTime;
	LastUpdateTime = CurTime;


	Vector3 Dir;
	SceneManager::GetInstance().GetViewDirection( Dir );

	// Частицы в полете.
	if( EffectTime < FlyTime )
	{
		AnimTime = fmod( EffectTime, AnimPeriod ) / AnimPeriod;
		DissolveFactor = 0;
		float T = EffectTime / FlyTime;
		float T0 = Max( T - TrailLen, 0.0f );

		float RealTrailLen = T - T0;
		int CurNumSprites = (int)( RealTrailLen/TrailLen * NumSprites );

		if( (unsigned)CurNumSprites > TrailSprites.size() )
		{
			int PrevSize = TrailSprites.size();
			TrailSprites.resize( CurNumSprites );
			for( std::vector<TrailSprite>::iterator I = TrailSprites.begin() + PrevSize;
				I != TrailSprites.end();
				++I )
			{
				I->Size = 0.5f*(SizeMin+SizeMax) + 0.25f*(SizeMax-SizeMin)*(2.0f*RandomFloat() - 1);
				I->Effect = this;
				ParSystem->SortList.push_back( *I );
			}
		}

		float DT = RealTrailLen / CurNumSprites;
		int Index = ParSystem->GetCurrentIndex();
		for( std::vector<TrailSprite>::iterator I = TrailSprites.begin();
			I != TrailSprites.end();
			++I, T -= DT )
		{
			I->Pos = (T*T)*C + (2.0f*T*(1 - T))*B + (1 - T)*(1 - T)*A;
			I->Index = Index++;
			I->Dist = (T - T0)/RealTrailLen;
			I->Z = Dir.Dot( I->Pos );

			EffParticleSystem::ParamVF Vertex;
			Vertex.TexCoord0() = I->Pos;
			Vertex.TexCoord1().X = I->Size;
			Vertex.TexCoord1().Y = I->Dist;
			ParSystem->WriteParameter( Vertex );
		}
	}
	else
	{
		// Частицы растворяются в воздухе.
		AnimTime = fmod( EffectTime, AnimPeriod ) / AnimPeriod;
		DissolveFactor = (EffectTime - FlyTime) / DissolveTime;

		int Index = ParSystem->GetCurrentIndex();
		for( std::vector<TrailSprite>::iterator I = TrailSprites.begin();
			I != TrailSprites.end();
			++I )
		{
			I->Index = Index++;
			I->Z = Dir.Dot( I->Pos );

			EffParticleSystem::ParamVF Vertex;
			Vertex.TexCoord0() = I->Pos;
			Vertex.TexCoord1().X = I->Size;
			Vertex.TexCoord1().Y = I->Dist;
			ParSystem->WriteParameter( Vertex );
		}
	}
}

void EffTrail::Draw()
{
	ParSystem->DrawTrail( *this );
}

//----------------------------------------------------------------------------------------------------------------

EffParticleRenderer::EffParticleRenderer()
{
	SmokeMat = ResourceManager::GetInstance().Register( 
		new ResMaterial( "Effects/Smoke.fx", SceneManager::GetInstance().LightParams ),
		"Smoke.fx" );

	ExplSprMat = ResourceManager::GetInstance().Register(
		new ResMaterial( "Effects/ExplosionSprite.fx", SceneManager::GetInstance().LightParams ),
		"ExplosionSprite.fx" );

	SpriteNum.AttachTo( ExplSprMat, "SpriteNum" );

	TrailMat = ResourceManager::GetInstance().Register(
		new ResMaterial( "Effects/TrailSprite.fx", SceneManager::GetInstance().LightParams ),
		"TrailSprite.fx" );

	AnimTime.AttachTo( TrailMat, "AnimTime" );
	DissolveFactor.AttachTo( TrailMat, "DissolveFactor" );
}

EffParticleRenderer::~EffParticleRenderer()
{
	ExplSprMat->Release();
	TrailMat->Release();
	SmokeMat->Release();
}

void EffParticleRenderer::DrawSmoke( EffSmoke &Eff )
{
	DrawParticleSubset( SmokeMat );
}

void EffParticleRenderer::DrawExplosionSprite( EffExplosionSprite& Eff )
{
	SpriteNum = Eff.SpriteNum;
	ExplSprMat->SetParameter( SpriteNum );
	DrawParticleSubset( ExplSprMat );
}

void EffParticleRenderer::DrawTrail( EffTrail& Eff )
{
	AnimTime = Eff.AnimTime;
	DissolveFactor = Eff.DissolveFactor;
	TrailMat->SetParameter( AnimTime );
	TrailMat->SetParameter( DissolveFactor );
	DrawParticleSubset( TrailMat );
}