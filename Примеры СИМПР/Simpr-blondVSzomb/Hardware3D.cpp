//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CHardware3D, source file
// Класс, осуществляющий инициализацию directX и устройства 
// рендеринга.
//////////////////////////////////////////////////////////////////



#include "Hardware3D.h"



//Конструктор
CHardware3D::CHardware3D(HWND _hWnd)
{
	hWnd = _hWnd;

	// Создаем объект D3D
    if( NULL == ( D3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )	
        return;
	

	//Заполняем структуру
	D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Создаем устройство
	if( FAILED( D3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &D3DDevice ) ) )
    {
		MessageBox(NULL, "Невозможно создать D3DDevice", "Ошибка!", MB_OK);
        return;
    }

	// Включаем Z-буффер
    D3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Включаем фоновый свет
    //D3DDevice->SetRenderState( D3DRS_AMBIENT, 0x33333333 );	
	D3DDevice->SetRenderState( D3DRS_LIGHTING,  FALSE );
	//D3DDevice->LightEnable( 0, TRUE );


}



//Деструктор
CHardware3D::~CHardware3D()
{
	if(D3DDevice != NULL)
		D3DDevice->Release();

	if(D3D != NULL)
		D3D->Release();
}
