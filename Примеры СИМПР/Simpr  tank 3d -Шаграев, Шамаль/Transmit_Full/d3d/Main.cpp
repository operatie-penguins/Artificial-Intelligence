#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <assert.h>
#include "Rendering.h"
#include <iomanip>
#include "Camera.h"
#include "Environment.h"

#include "GameAux.h"

#define SIMPR_MESSAGE 49821;

class SysTimer
{
	SysTimer( const SysTimer& );
	SysTimer& operator=( const SysTimer& );
public:
	SysTimer( float MaxFrameTimeSec, bool FixThread = false )
		: MaxFrameTime(MaxFrameTimeSec)
	{
		// Закрепляем поток к одному процессору.
		if( FixThread )
		{
			HANDLE CurProcess = GetCurrentProcess();
			DWORD_PTR PAM, SAM;
			GetProcessAffinityMask( CurProcess, &PAM, &SAM );
			// Выделяем младший единичный бит.
			PAM = PAM & (~PAM + 1);
			CloseHandle( CurProcess );
			HANDLE CurThread = GetCurrentThread();
			SetThreadAffinityMask( CurThread, PAM );
			CloseHandle( CurThread );
		}
		LARGE_INTEGER Freq;
		QueryPerformanceFrequency( &Freq );
		Frequency = (double)Freq.QuadPart;
	}
	double			Frequency;
	LARGE_INTEGER	PrevTime;
	float			MaxFrameTime;
public:
	void Reset();
	void GetTime( float* AbsTime, float* ElapsedTime ); 
};

void SysTimer::Reset()
{
	QueryPerformanceCounter( &PrevTime );
}

void SysTimer::GetTime( float *AbsTime, float *ElapsedTime )
{
	LARGE_INTEGER CurTime;
	QueryPerformanceCounter( &CurTime );
	if( AbsTime )
	{
		*AbsTime = (float)((double)CurTime.QuadPart / Frequency);
	}
	if( ElapsedTime )
	{
		*ElapsedTime = (float)((double)(CurTime.QuadPart - PrevTime.QuadPart) / Frequency );
		if( *ElapsedTime < 0 )
			*ElapsedTime = 0;
		if( *ElapsedTime > MaxFrameTime )
			*ElapsedTime = MaxFrameTime;
	}
	PrevTime = CurTime;
}

static IDirect3D9 *pD3D9;
static IDirect3DDevice9 *pDevice;
static D3DPRESENT_PARAMETERS PParam;
static float Aspect = 1.0f;

//static EffParticleSystem *ParSystem;

static Environment *Universe;
float AbsTime;
bool help = false;

LRESULT CALLBACK WndCallback( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
	if (Msg == 49955)
	{		
		WORD WParamHi = HIWORD(wParam);
		WORD WParamLo = LOWORD(wParam);;

		if (WParamHi == 0)
			return Universe->Conditions(WParamLo, lParam, AbsTime);
		return Universe->Actions(WParamLo, lParam);	
	}

	// Старые координаты курсора
	static int BeginX, BeginY;

	switch ( Msg )
	{
	case WM_DESTROY:
	case WM_CLOSE:
		PostQuitMessage( 0 );
		break;

	case WM_MOUSEMOVE:
	{
		POINTS Pos = MAKEPOINTS(lParam);
		if ( wParam == MK_LBUTTON )
		{
			RECT Rect;
			GetClientRect( hWnd, &Rect );
			D3DXQUATERNION SpinQuat;
			int Width = Rect.right - Rect.left;
			int Height = Rect.bottom - Rect.top;
			GCamera *ActiveCamera = SceneManager::GetInstance().GetActiveCamera();
			if( ActiveCamera )
			{
				ActiveCamera->RotateScrYX( 90.0f*(Pos.x-BeginX)/Width, 90.0f*(Pos.y-BeginY)/Height );
			}
		}
		BeginX = Pos.x;
		BeginY = Pos.y;
		break;
	}

	case WM_CHAR:
		{
			if( !Universe->UserTank )
				break;
			switch( wParam )
			{
				case 'a':
					Universe->UserTank->Rotate( -0.7f );
					break;
				case 'q':
					Universe->UserTank->RotateTurret( -0.4f );
					break;
				case 'e':
					Universe->UserTank->RotateTurret( 0.4f );
					break;
				case 'w':
					Universe->UserTank->Accelerate( 1.0f );
					break;
				case 's':
					Universe->UserTank->Accelerate( -1.0f );
					break;
				case 'd':
					Universe->UserTank->Rotate( 0.7f );
					break;
				case 'n':
					Universe->ParSystem->CreateExplSprite(Universe->UserTank->GetPos(), 400.0f);
					//ParSystem->CreateExplSprite( Vector3(150,0,0), 300 );
					break;
				case 'h':
					help = !help;
					break;
				case 'm':
					{
						Universe->UserTankFire();
					}
					break;
				default:
					;
			}
		}
		break;

	case WM_KEYDOWN:
		{
			float Dist = 0;
			if ( wParam == 33 )
			{
				Dist += 2.0f;
			}
			else if (wParam == 34)
			{
				Dist -= 2.0f;
			}
			GCamera *ActiveCamera = SceneManager::GetInstance().GetActiveCamera();
			if( ActiveCamera )
			{
				ActiveCamera->AlterateDist( Dist );
			}
		}
		break;

	case WM_SIZE:
		/*if ( pDevice )
		{
			PParam.BackBufferHeight = 0;
			PParam.BackBufferWidth = 0;
			HRESULT Res = pDevice->Reset( &PParam );
			if ( Res != D3D_OK )
				exit( 1 );
		}*/
		Aspect = (float)LOWORD(lParam)/HIWORD(lParam);
		break;

	default:
		return DefWindowProc( hWnd, Msg, wParam, lParam );
	}

	return 0;
}

void DrawModel( GRenderable *Obj = 0 )
{
	if( Obj )
		Obj->Draw();
}

AppError::~AppError()
{
	ResourceManager::GetInstance().ReleaseAll();
	::MessageBox( NULL, ErrString.str().c_str(), "Error", MB_ICONEXCLAMATION );
	assert( 0 );
	exit( 1 );
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR CmdLine, int iCmdShow )
{
	bool finish = false;
	WNDCLASS WC = {0};
	WC.lpszClassName = "D3D";
	WC.hInstance = hInstance;
	WC.style = CS_HREDRAW | CS_VREDRAW;
	WC.lpfnWndProc = WndCallback;

	RegisterClass( &WC );

	HWND hWnd = CreateWindow( "D3D", "Rendering", WS_CAPTION | WS_SYSMENU, 0, 0, 800, 600, NULL, NULL, hInstance, NULL );
	if ( !hWnd )
		return 1;

	ShowWindow( hWnd, SW_SHOWNORMAL );
	UpdateWindow( hWnd );

	// Initialize Direct3D
	if ( NULL == (pD3D9 = Direct3DCreate9( D3D_SDK_VERSION )))
		return 1;

	// Проверка устройства.
	D3DCAPS9 DeviceCaps;
	pD3D9->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps );
	if( DeviceCaps.VertexShaderVersion < D3DVS_VERSION(2,0) )
	{
		AppError() << "Vertex shaders of version 2.0 or higher required";
	}
	if( DeviceCaps.PixelShaderVersion < D3DPS_VERSION(2,0) )
	{
		AppError() << "Pixel shaders of version 2.0 or higher required";
	}
	
	PParam.Windowed = TRUE;
	PParam.EnableAutoDepthStencil = TRUE;
	PParam.AutoDepthStencilFormat = D3DFMT_D24X8;
	PParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	PParam.BackBufferFormat = D3DFMT_UNKNOWN;
	HRESULT Res;
	Res = pD3D9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &PParam, &pDevice );
	if( FAILED(Res) )
		return 1;

	ResourceManager::GetInstance().Init( pDevice, pD3D9, PParam );

	pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// Тестирование

	GCamera Cam1;
	SceneManager::GetInstance().SetActiveCamera( &Cam1 );
	Font Arial( "Fonts", "CouNew.fnt", 800.0f, 600.0f );
	Font NewFont( "Fonts", "CouNew.fnt", 800.0f, 600.0f );

	// Setup projection
	D3DXMATRIX Proj;
	D3DXMatrixPerspectiveFovLH( &Proj, 45.0f, Aspect, 0.5f, 1e6f );
	pDevice->SetTransform( D3DTS_PROJECTION, &Proj );
	SceneManager::GetInstance().SetProjection( Proj );

	Universe = new Environment("level1.txt");
	Cam1.AttachToObject( Universe->UserTank, 700.0f );

	SysTimer FrameTimer( 1.0f, true );
	SkyDome Sky( "Sky.fx", 10000.0f );
	//EffParticleSystem	ParticleSystem( 7000 );
	//ParSystem = &ParticleSystem;

	FrameTimer.GetTime( &AbsTime, 0 );
	// Инициализируем реальным временем. Для тестирования эффектов, созданных вне основного цикла.
	SceneManager::GetInstance().BeginFrame( AbsTime );

	// Создание ресурсов для пост-процессинга.
	SceneManager::GetInstance().LightParams->RegisterParameter( "OpaqueAndDepthPassTex", "texture2D" );

	ResMaterial *PostEff = ResourceManager::GetInstance().Register(
		new ResMaterial( "Effects/PostProcess.fx", SceneManager::GetInstance().LightParams ),
		"Effects/PostProcess.fx"
	);

	ResRenderTarget *OpaqueRT = ResourceManager::GetInstance().CreateRenderTarget( D3DFMT_A16B16G16R16  );
	PostEff->AttachTexture( OpaqueRT );

	std::stringstream StrWin;

	float FrameDelta = 0;
	
	while ( 1 )
	{
		FrameTimer.Reset();

		FrameTimer.GetTime( &AbsTime, 0 );
		for( GObject::GObjIterator It(GObject::GetClassBin("GObject")); !It.AtTheEnd(); ++It )
		{
			It->BeginFrame( AbsTime );
		}
		SceneManager::GetInstance().BeginFrame( AbsTime );

		// Рисование мира и соделей должно происходить после этого вызова.
		ResourceManager::GetInstance().SetRenderTarget( OpaqueRT );

		pDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0,0,220,0), 1, 0 );
		if ( !SUCCEEDED( pDevice->BeginScene() ) )
			assert( 0 );

		// Рисование частиц и полупрозрачных поверхностей должно проиходить после этих вызовов.
		ResourceManager::GetInstance().SetRenderTarget( 0 );
		ResourceManager::GetInstance().DrawFullScreenQuad( PostEff );

		Universe->Action(AbsTime);
		
		Sky.DrawSky();
		if (help)
		{
			Arial.DrawLine(400, 300, "Moving: w,a,s,d");
			Arial.DrawLine(400, 250, "Firing: m");
			Arial.DrawLine(400, 200, "Help on/off: h");
		}

		if (!finish && Universe->Win())
		{
			StrWin << "You win!";
			finish = true;
		}
		else
		if (!finish && Universe->Lost())
		{
			StrWin << "You loose!";
			finish = true;
		}

		Arial.DrawLine( 400, 300, StrWin.str() );

//		ParticleSystem.UpadateParticles();
//		ParticleSystem.DrawParticles();

//		World.DrawTranslucentSurfaces();

		//GAuxiliary::Get().Draw();


		std::stringstream Str;
		//Str << "Eye: " << EyePos.x << " " << EyePos.y << " " << EyePos.z;
		Str << "FPS: " << std::setprecision(2) << 1.0f / FrameDelta;
		Arial.DrawLine( 10, 60, Str.str() );

		std::stringstream Hp;
		Hp << "HP: " << Universe->UserTank->GameValue;
		NewFont.DrawLine( 160, 60, Hp.str() );

		pDevice->EndScene();
		if( D3DERR_DEVICELOST == pDevice->Present( NULL, NULL, NULL, NULL ) )
		{
			ResourceManager::GetInstance().OnDeviceLost( &PParam );
		}

		FrameTimer.GetTime( 0, &FrameDelta );
		
		MSG Msg;
		if ( PeekMessage( &Msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if( Msg.message == WM_QUIT )
				break;
			TranslateMessage( &Msg );
			DispatchMessage( &Msg );
		}
	}
	OpaqueRT->Release();
	PostEff->Release();
	delete Universe;
	return 0;
}