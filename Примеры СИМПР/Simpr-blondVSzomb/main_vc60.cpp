//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Main source file
//////////////////////////////////////////////////////////////////



#include "main.h"



#define USERMESSAGE "MyMessage"
UINT OurMessage;

#define DEF_SPEED 15.0f
#define ATT_SPEED 8.0f

int CurPlayer=0;
int CurH=0;
int CurZ=0;
int CurB=0;
int NumberZomby=3;
int NumberBlondes=3;
int NumberHuman=3;
int count=0;
float currand=0;
float randi=0;




/*
void InitGeometry()
{	
	CUSTOMVERTEX vertices[] =
    {
		{  0.0f,  -8.0f,  0.0f, D3DCOLOR_XRGB(0, 155, 0), },
        {500.0f,  -8.0f,  0.0f, D3DCOLOR_XRGB(0, 155, 0), }, // x, y, z, color
        {500.0f,  -8.0f,600.0f, D3DCOLOR_XRGB(0, 155, 0), },
        {  0.0f,  -8.0f,600.0f, D3DCOLOR_XRGB(0, 155, 0), },
		{  0.0f,  -8.0f,  0.0f, D3DCOLOR_XRGB(0, 155, 0), },
		{500.0f,  -8.0f,  0.0f, D3DCOLOR_XRGB(0, 155, 0), },
    };
	
    if( FAILED( Scene3D->Hardware3D->D3DDevice->CreateVertexBuffer( 6*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB1, NULL ) ) )
    {
        return;
    }
    
    VOID* pVertices;
    if( FAILED( g_pVB1->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 ) ) )
        return;
    memcpy( pVertices, vertices, sizeof(vertices) );
    g_pVB1->Unlock();



	CUSTOMVERTEX vertices2[] =
    {
		{300.0f,  -7.9f,  0.0f, D3DCOLOR_XRGB(255, 255, 255), },
        {305.0f,  -7.9f,  0.0f, D3DCOLOR_XRGB(255, 255, 255), }, // x, y, z, color
        {305.0f,  -7.9f,600.0f, D3DCOLOR_XRGB(255, 255, 255), },
        {300.0f,  -7.9f,600.0f, D3DCOLOR_XRGB(255, 255, 255), },
		{300.0f,  -7.9f,  0.0f, D3DCOLOR_XRGB(255, 255, 255), },
		{305.0f,  -7.9f,  0.0f, D3DCOLOR_XRGB(255, 255, 255), },
    };
	
    if( FAILED( Scene3D->Hardware3D->D3DDevice->CreateVertexBuffer( 6*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB2, NULL ) ) )
    {
        return;
    }
    
    VOID* pVertices2;
    if( FAILED( g_pVB2->Lock( 0, sizeof(vertices2), (void**)&pVertices2, 0 ) ) )
        return;
    memcpy( pVertices2, vertices2, sizeof(vertices2) );
    g_pVB2->Unlock();

	return;
}
*/

/*
void RenderGeometry()
{
	D3DXMATRIXA16 MatW;
	Scene3D->Hardware3D->D3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

	if( SUCCEEDED( Scene3D->Hardware3D->D3DDevice->BeginScene() ) )
    {       
		D3DXMatrixIdentity(&MatW);
		Scene3D->Hardware3D->D3DDevice->SetTransform(D3DTS_WORLD, &MatW);	

        Scene3D->Hardware3D->D3DDevice->SetStreamSource( 0, g_pVB1, 0, sizeof(CUSTOMVERTEX) );
        Scene3D->Hardware3D->D3DDevice->SetFVF( D3DFVF_CUSTOMVERTEX );		
        Scene3D->Hardware3D->D3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
        Scene3D->Hardware3D->D3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 4 );


		Scene3D->Hardware3D->D3DDevice->SetStreamSource( 0, g_pVB2, 0, sizeof(CUSTOMVERTEX) );		
        Scene3D->Hardware3D->D3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
        Scene3D->Hardware3D->D3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 4 );

		Scene3D->Hardware3D->D3DDevice->EndScene();
	}

	Scene3D->Hardware3D->D3DDevice->Present( NULL, NULL, NULL, NULL );

	return;
}



bool FreeFwd(CPlayer* Player)
{
	for(int i=0; i<5; i++)
	{
		if(Players[i]->Team==1)
			if(fabs(Players[i]->Position.z - Player->Position.z) < 35
				&& fabs(Players[i]->Position.x - Player->Position.x) < 70)
				return false;
	}
	return true;
}



bool NearestToBall()
{
	int i;
	for(i=0; i<5; i++)
		if(Players[i]->Team==0 && Players[i]->HaveBall)
			break;

	for(int j=0; j<5; j++)
		if(Players[j]->Team==1 && j!=CurPlayer)
			if(D3DXVec3Length(&(Players[CurPlayer]->Position-Players[i]->Position)) < D3DXVec3Length(&(Players[j]->Position-Players[i]->Position)) )
				return true;
			else
				return false;

	return false;
}



int NearestPWB()
{
	int S=0;
	float Len=2000.0f;

	for(int i=0; i<5; i++)
		if(Players[i]->Team==0)
			if(D3DXVec3Length(&(Players[CurPlayer]->Position - Players[i]->Position)) < Len)
			{
				S=Players[i]->Side;
				Len = D3DXVec3Length(&(Players[CurPlayer]->Position-Players[i]->Position));
			}
	return S;
}


*/

//Обработчик событий
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int i;
	D3DXVECTOR3 temp;
	srand(GetTickCount());

	char buffa[120];
	currand=(rand()%100)/100.0f;
	sprintf(buffa,"%f",currand);
	


	if(uMsg == OurMessage)
		{
			//MessageBox(hWnd,"Сука","Говно",16);
			switch( HIWORD(wParam) )
			{
			case 0:
				{
					//MessageBox(hWnd,"Условия пошли","Говно",16);
					switch( LOWORD(wParam) )
					{
					case 1: 
						{
							//MessageBox(hWnd,"Таблица 1","Говно",16);
							switch(lParam)
							{
							case 1: //одни люди?
								if (NumberHuman == 9)
									return true;
								else
									return false;
							case 2: //Одни зомби?
								if (NumberZomby == 9)
									return true;
								else
									return false;
							case 3: //Одни блондинки?
								if (NumberBlondes == 9)
									return true;
								else
									return false;

							}
						}
					case 2: 
						{
							//MessageBox(hWnd,"Таблица 2","Говно",16);
							switch(lParam)
							{
							case 1: //Все люди сходили?
								{
								if (NumberHuman != 0)
								{
									for (int i=0; i<NumberHuman; i++)
									{
										if (Humans[i]->Hod_h == false)
											count++;
									}
									if (count != 0)
									{
										count = 0;
										return false;
									}

									else 
										return true;
									}
							
								else
									return true;
								}
							}
						}
					case 3: 
						{
							//MessageBox(hWnd,"Таблица 3","Говно",16);
							switch(lParam)
							{
							case 1: //Все зомби сходили?
								{
								if (NumberZomby != 0)
								{
									for (int i=0; i<NumberZomby; i++)
									{
										if (Zombies[i]->Hod_z == false)
											count++;
									}
									if (count != 0)
									{
										count=0;
										return false;
									}
									else 
										return true;
								}
								else
									return true;
								}
							}
						}
					case 4: 
						{
							//MessageBox(hWnd,"Таблица 4","Говно",16);
							switch(lParam)
							{
							case 1: //Все блондинки сходили?
								{
									if (NumberBlondes != 0)
									{
										for (int i=0; i<NumberBlondes; i++)
										{
											if (Blondees[i]->Hod_b == false)
												count++;
										}
										if (count != 0)
										{
											count = 0;
											return false;
										}
										else 
											return true;
									}
								else 
									return true;
								}
							}
						}
					case 5: 
						{//Ход людей
							//MessageBox(hWnd,"Таблица 5","Говно",16);
							switch(lParam)
							{
							case 1: //Зомби сверху
								randi = currand;
								for (i=0; i<NumberZomby; i++)
								{
									if (D3DXVec3Length(&(Humans[CurH]->Position - (Zombies[i]->Position - D3DXVECTOR3(0,0,10)))) < 1.0f)
									{
										randi=2;
										return true;
									}
									else
										return false;
								}
							case 2: // Зомби слева
								for (i=0; i<NumberZomby; i++)
								{
									if (D3DXVec3Length(&(Humans[CurH]->Position - (Zombies[i]->Position + D3DXVECTOR3(10,0,0)))) < 1.0f)
									{
										randi=2;
										return true;
									}
									else
										return false;
								}
							case 3:// Зомби справа
								for (i=0; i<NumberZomby; i++)
								{
									if (D3DXVec3Length(&(Humans[CurH]->Position - (Zombies[i]->Position - D3DXVECTOR3(10,0,0)))) < 1.0f)
									{
										randi=2;
										return true;
									}
									else
										return false;
								}
							case 4: //Зомби снизу
								for (i=0; i<NumberZomby; i++)
								{
									if (D3DXVec3Length(&(Humans[CurH]->Position - (Zombies[i]->Position + D3DXVECTOR3(0,0,10)))) < 1.0f)
									{
										randi=2;
										return true;
									}
									else
										return false;
								}
							case 5: //рандом < 0.25
								
								if (randi <= 0.25)
									return true;
								else
									return false;
							case 6://рандом > 0.25 & < 0.5
								if (randi > 0.25 && randi <= 0.5)
									return true;
								else
									return false;
							case 7://рандом > 0.5 & < 0.75
								if (randi > 0.5 && randi <= 0.75)
									return true;
								else
									return false;
							case 8://рандом > 0.75 & < 1
								if (randi > 0.75 && randi <= 1)
									return true;
								else
									return false;
							}
						}
					case 6: 
						{//Ход зомби
							//MessageBox(hWnd,"Таблица 6","Говно",16);
							switch(lParam)
							{
						case 1: //Человек сверху
						randi = currand;
								for (i=0; i<NumberHuman; i++)
								{
									if (D3DXVec3Length(&(Zombies[CurZ]->Position - (Humans[i]->Position - D3DXVECTOR3(0,0,10)))) < 1.0f)
									{
										randi=2;
										return true;
									}
									else
										return false;
								}
							case 2: //Человек слева
								for (i=0; i<NumberHuman; i++)
								{
									if (D3DXVec3Length(&(Zombies[CurZ]->Position - (Humans[i]->Position + D3DXVECTOR3(10,0,0)))) < 1.0f)
									{
										randi=2;
										return true;
									}
									else
										return false;
								}
							case 3://Человек справа
								for (i=0; i<NumberHuman; i++)
								{
									if (D3DXVec3Length(&(Zombies[CurZ]->Position - (Humans[i]->Position - D3DXVECTOR3(10,0,0)))) < 1.0f)
									{
										randi=2;
										return true;
									}
									else
										return false;
								}
							case 4: //Человек снизу
								for (i=0; i<NumberHuman; i++)
								{
									if (D3DXVec3Length(&(Zombies[CurZ]->Position - (Humans[i]->Position + D3DXVECTOR3(0,0,10)))) < 1.0f)
									{
										randi=2;
										return true;
									}
									else
										return false;
								}
							case 5: //рандом < 0.25
								if (randi <= 0.25)
									return true;
								else
									return false;
							case 6://рандом > 0.25 & < 0.5
								if (randi > 0.25 && randi <= 0.5)
									return true;
								else
									return false;
							case 7://рандом > 0.5 & < 0.75
								if (randi > 0.5 && randi <= 0.75)
									return true;
								else
									return false;
							case 8://рандом > 0.75 & < 1
								if (randi > 0.75 && randi <= 1)
									return true;
								else
									return false;
							}
						}
					case 7: 
						{// Ход блондинок
							//MessageBox(hWnd,"Таблица 7","Говно",16);
							switch(lParam)
							{
							case 1: //рандом < 0.25
								randi = currand;
								if (randi <= 0.25)
									return true;
								else
									return false;
							case 2://рандом > 0.25 & < 0.5
								if (randi > 0.25 && randi <= 0.5)
									return true;
								else
									return false;
							case 3://рандом > 0.5 & < 0.75
								if (randi > 0.5 && randi <= 0.75)
									return true;
								else
									return false;
							case 4://рандом > 0.75 & < 1
								if (randi > 0.75 && randi <= 1)
									return true;
								else
									return false;
							}
						}
					case 8:
						{
							switch(lParam)
							{
							case 1: //Попал на блондинку?
								for(int i=0; i<NumberBlondes; i++)
									{
										if (D3DXVec3Length(&(Humans[CurH]->Position - Blondees[i]->Position))<1.0f)
											return true;
										

								}
								return false;

							}
						}
					case 9:
						{
							switch(lParam)
							{
							case 1: //Попал на человека?
								for(i=0; i<NumberHuman; i++)
									{
										if (D3DXVec3Length(&(Humans[i]->Position - Zombies[CurZ]->Position))<1.0f)
											return true;

								}
								return false;
							case 2: //Попал на блондинку?

								for(i=0; i<NumberBlondes; i++)
									{
										if (D3DXVec3Length(&(Zombies[CurZ]->Position - Blondees[i]->Position))<1.0f)
											return true;
								}
								return false;

							}
						}
					case 10:
						{
							switch(lParam)
							{
							case 1: //Попалa на зомби?
								for(i=0; i<NumberZomby; i++)
								{
									
										if (D3DXVec3Length(&(Blondees[CurB]->Position - Zombies[i]->Position))<1.0f)
											return true;

								}
								return false;
								
							case 2: //Попалa на человека?
								for(i=0; i<NumberHuman; i++)
								{
										if (D3DXVec3Length(&(Humans[i]->Position - Blondees[CurB]->Position))<1.0f)
											return true;

								}
								return false;

							}
						}

					}//end LOWORD
				}//end 0
			case 1:
				{
					//MessageBox(hWnd,"Actions пошли","Говно",16);
					switch( LOWORD(wParam) )
					{
					case 1:
						{
							//MessageBox(hWnd,"Таблица 1","Говно",16);
							switch(lParam)
							{
							case 1://Победа людей!
								{
									MessageBox(hWnd,"Победа людей","Победа людей",0);
									return true;
								}
							case 2://Победа зомби
								{
									MessageBox(hWnd,"Победа зомби","Победа зомби",0);
									return true;
								}
							case 3://Победа блондинок
								{
									MessageBox(hWnd,"Победа блондинок","Победа блондинок",0);
									return true;
								}
							}
						}
					case 2:
						{//Ход людей
							//MessageBox(hWnd,"Таблица 2","Говно",16);
							switch(lParam)
							{
							case 1://Обнуляем ходы
								{
									for (int i=0; i<NumberHuman; i++)
										Humans[i]->Hod_h=false;
									CurH=0;
									return true;
								}
							}

						}
					case 3: //Ход зомби
						{
							//MessageBox(hWnd,"Таблица 3","Говно",16);
							switch(lParam)
							{
							case 1://Обнуляем ходы
								{
									for (int i=0; i<NumberZomby; i++)
										Zombies[i]->Hod_z=false;
									CurZ=0;
									return true;
								}
							}
						}
					case 4:// Ход блондинок
						{
							//MessageBox(hWnd,"Таблица 4","Говно",16);
							switch(lParam)
							{
							case 1:// Обнуляем ходы
								
									for (int i=0; i<NumberBlondes; i++)
										Blondees[i]->Hod_b=false;
									CurB=0;
									return true;
								
							}
						}
					case 5:
						{//Действия человека
							//MessageBox(hWnd,"Таблица 5","Говно",16);
							switch(lParam)
							{
							case 1://Идёт наверх
								
									Humans[CurH]->Position += D3DXVECTOR3(0,0,10);
									Humans[CurH]->Hod_h = true;
									if (Humans[CurH]->Position.z>80)
										Humans[CurH]->Position.z=80;
									return true;
								
							case 2://Идёт налево
								
									Humans[CurH]->Position -= D3DXVECTOR3(10,0,0);
									Humans[CurH]->Hod_h = true;
									if (Humans[CurH]->Position.x<30)
										Humans[CurH]->Position.x=30;
									return true;
								
							case 3://Идёт направо
								
									Humans[CurH]->Position += D3DXVECTOR3(10,0,0);
									Humans[CurH]->Hod_h = true;
									if (Humans[CurH]->Position.x>80)
										Humans[CurH]->Position.x=80;
									return true;
								
							case 4://Идёт вниз
								
									Humans[CurH]->Position -= D3DXVECTOR3(0,0,10);
									Humans[CurH]->Hod_h = true;
									if (Humans[CurH]->Position.z<30)
										Humans[CurH]->Position.z=30;
									return true;
								
							case 5: //стоит на месте
								
									Humans[CurH]->Hod_h = true;
									return true;

								
							}
						}
					case 6:
						{//Действия зомби
							//MessageBox(hWnd,"Таблица 6","Говно",16);
							switch(lParam)
							{
							case 1://Идёт наверх
								
									Zombies[CurZ]->Position += D3DXVECTOR3(0,0,10);
									Zombies[CurZ]->Hod_z = true;
									if (Zombies[CurZ]->Position.z>80)
										Zombies[CurZ]->Position.z=80;
									return true;
								
							case 2://Идёт налево
								
									Zombies[CurZ]->Position -= D3DXVECTOR3(10,0,0);
									Zombies[CurZ]->Hod_z = true;
									if (Zombies[CurZ]->Position.x<30)
										Zombies[CurZ]->Position.x=30;
									return true;
								
							case 3://Идёт направо
								
									Zombies[CurZ]->Position += D3DXVECTOR3(10,0,0);
									Zombies[CurZ]->Hod_z = true;
									if (Zombies[CurZ]->Position.x>80)
										Zombies[CurZ]->Position.x=80;
									return true;
								
							case 4://Идёт вниз
								
									Zombies[CurZ]->Position -= D3DXVECTOR3(0,0,10);
									Zombies[CurZ]->Hod_z = true;
									if (Zombies[CurZ]->Position.z<30)
										Zombies[CurZ]->Position.z=30;
									return true;
												
							}
						}
					case 7: //Действия блондинки
						{
								//MessageBox(hWnd,"Таблица 7","Говно",16);
							switch(lParam)
							{
							case 1://Идёт наверх
								
									Blondees[CurB]->Position += D3DXVECTOR3(0,0,10);
									Blondees[CurB]->Hod_b = true;
									if (Blondees[CurB]->Position.z>80)
										Blondees[CurB]->Position.z=80;
									return true;
								
							case 2://Идёт налево
								
									Blondees[CurB]->Position -= D3DXVECTOR3(10,0,0);
									Blondees[CurB]->Hod_b = true;
									if (Blondees[CurB]->Position.x<30)
										Blondees[CurB]->Position.x=30;
									return true;
								
							case 3://Идёт направо
								
									Blondees[CurB]->Position += D3DXVECTOR3(10,0,0);
									Blondees[CurB]->Hod_b = true;
									if (Blondees[CurB]->Position.x>80)
										Blondees[CurB]->Position.x=80;
									return true;
								
							case 4://Идёт вниз
								
									Blondees[CurB]->Position -= D3DXVECTOR3(0,0,10);
									Blondees[CurB]->Hod_b = true;
									if (Blondees[CurB]->Position.z<30)
										Blondees[CurB]->Position.z=30;
									return true;
												
							}
						}
					case 8:// Анализ хода
						{
							//MessageBox(hWnd,"Таблица 8","Говно",16);
							switch(lParam)
							{

							
							case 1://Человек настиг блондинку
									for(i=0; i<NumberBlondes; i++)
									{
										if (D3DXVec3Length(&(Humans[CurH]->Position - Blondees[i]->Position))<1.0f)
										{
									NumberBlondes--;
									NumberHuman++;
									Humans[NumberHuman-1]=new CHuman(Scene3D);
									Humans[NumberHuman-1]->LoadMesh("human.x","human.x","human.x");
									Humans[NumberHuman-1]->Position = Blondees[i]->Position;
									Humans[NumberHuman-1]->Hod_h=false;
									Scene3D->AddObject(Humans[NumberHuman-1]);
									Scene3D->DelObject(Blondees[i]);
									for (int j=i; j<NumberBlondes; j++)
											{
												Blondees[j]= Blondees[j+1];
											}
										}
									}
									CurH++;
									return true;

							case 2://пустая клетка
								CurH++;
								return true;
							}
						}

					case 9:// Анализ хода
						{
							//MessageBox(hWnd,"Таблица 9","Говно",16);
							switch(lParam)
							{


							case 1://Зомби настиг человека
									for(i=0; i<NumberHuman; i++)
									{
										if 
											(D3DXVec3Length(&(Zombies[CurZ]->Position - Humans[i]->Position))<1.0f)
										{
								
									NumberHuman--;
									NumberZomby++;
									Zombies[NumberZomby-1]=new CZomby(Scene3D);
									Zombies[NumberZomby-1]->LoadMesh("zomby.x","zomby.x","zomby.x");
									Zombies[NumberZomby-1]->Position = Humans[i]->Position;
									Zombies[NumberZomby-1]->Hod_z=false;
									Scene3D->AddObject(Zombies[NumberZomby-1]);
									Scene3D->DelObject(Humans[i]);
									for (int j=i; j<NumberHuman; j++)
											{
												Humans[j]= Humans[j+1];
											}
										}
									}
									CurZ++;
									return true;

							case 2://Зомби стал блондинкой
									for(i=0; i<NumberBlondes; i++)
									{
										if (D3DXVec3Length(&(Zombies[CurZ]->Position - Blondees[i]->Position))<1.0f)
										{
								
									NumberZomby--;
									NumberBlondes++;
									Blondees[NumberBlondes-1]=new CBlondes(Scene3D);
									Blondees[NumberBlondes-1]->LoadMesh("blonde.x","blonde.x","blonde.x");
									Blondees[NumberBlondes-1]->Position = Zombies[CurZ]->Position;
									Blondees[NumberBlondes-1]->Hod_b=false;
									Scene3D->AddObject(Blondees[NumberBlondes-1]);
									Scene3D->DelObject(Zombies[CurZ]);
									if (CurZ != NumberZomby)
									{
									for (int j=CurZ; j<NumberZomby; j++)
											{
												Zombies[j]= Zombies[j+1];
											}
									}
										}
										
									}
									return true;

							case 3://пустая клетка
								CurZ++;
								return true;
							}
						}

						case 10:// Анализ хода
						{
							//MessageBox(hWnd,"Таблица 10","Говно",16);
							switch(lParam)
							{

									case 1://Зомби стал блондинкой

									for(i=0; i<NumberZomby; i++)
									{
										if (D3DXVec3Length(&(Zombies[i]->Position - Blondees[CurB]->Position))<1.0f)
										{
								
											NumberZomby--;
											NumberBlondes++;
											Blondees[NumberBlondes-1]=new CBlondes(Scene3D);
											Blondees[NumberBlondes-1]->LoadMesh("blonde.x","blonde.x","blonde.x");
											Blondees[NumberBlondes-1]->Position = Zombies[i]->Position;
											Blondees[NumberBlondes-1]->Hod_b=false;
											Scene3D->AddObject(Blondees[NumberBlondes-1]);
											Scene3D->DelObject(Zombies[i]);
											for (int j=i; j<NumberZomby; j++)
											{
												Zombies[j]= Zombies[j+1];
											}
										}

									}
									CurB++;
									return true;

							case 2://Блондинка попала на человека
									for(i=0; i<NumberHuman; i++)
									{
										if (D3DXVec3Length(&(Humans[i]->Position - Blondees[CurB]->Position))< 1.0f)
										{
											NumberBlondes--;
											NumberHuman++;
											Humans[NumberHuman-1]=new CHuman(Scene3D);
											Humans[NumberHuman-1]->LoadMesh("human.x","human.x","human.x");
											Humans[NumberHuman-1]->Position = Blondees[CurB]->Position;
											Humans[NumberHuman-1]->Hod_h=false;
											Scene3D->AddObject(Humans[NumberHuman-1]);
											Scene3D->DelObject(Blondees[CurB]);
											for (int j=CurB; j<NumberBlondes; j++)
											{
												Blondees[j]= Blondees[j+1];
											}

										}
									}
									return true;

							

							case 3://пустая клетка
								CurB++;
								return true;

								
							}//свитч
						}//анализ хода
					}
				}
			}			
		}

		

	switch(uMsg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);
		break;	

	case WM_KEYDOWN:
		{
			switch( wParam )
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;				

			}
		}	
		

	default:
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}

	return 0;
}





//Инициализация
BOOL InitApplication(HINSTANCE hInst)
{
	WNDCLASSEX wc;

	wc.cbSize		= sizeof(wc);
	wc.style		= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	= WndProc;
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= hInst;
	wc.hIcon		= LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor		= LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName	= NULL;
	wc.lpszClassName= TITLE_STRING;
	wc.hIconSm		= NULL;

	if (!RegisterClassEx(&wc))
	{
		return FALSE;
	}
	
	hWnd = CreateWindow(
		TITLE_STRING,
		TITLE_STRING,
		WS_OVERLAPPEDWINDOW,
		0,0,
		Width,Height,
		NULL,NULL,hInst,NULL);

	if (hWnd == NULL)
	{
		return FALSE;
	}

	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);

	return TRUE;
}



//Главная функция
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR,int)
{
	MSG msg;
	


	if (hPrevInst)
	{	
		return FALSE;
	}

	if (!InitApplication(hInst))
	{
		return FALSE;
	}

	OurMessage = RegisterWindowMessage(USERMESSAGE);

	//Инициализация DirectX
	Hardware3D = new CHardware3D(hWnd);
	Camera3D = new CCamera3D(Hardware3D);
	Scene3D = new CScene3D(Hardware3D, Camera3D);

	srand(GetTickCount());	


//	InitGeometry();
/*
	Players[0] = new CPlayer(Scene3D);
	Players[0]->LoadMesh("chel_ball.x","chel.x","chel.x");
	Players[0]->HaveBall = true;
	Players[0]->Team = 0;
	Players[0]->Side = 0;
	Players[0]->Position = D3DXVECTOR3(20, 0, 500);
	Scene3D->AddObject(Players[0]);

	Players[1] = new CPlayer(Scene3D);
	Players[1]->LoadMesh("chel_ball.x","chel.x","chel.x");
	Players[1]->HaveBall = false;
	Players[1]->Team = 0;
	Players[1]->Side = 1;
	Players[1]->Position = D3DXVECTOR3(20, 0, 300);
	Scene3D->AddObject(Players[1]);

	Players[2] = new CPlayer(Scene3D);
	Players[2]->LoadMesh("chel_ball.x","chel.x","chel.x");
	Players[2]->HaveBall = false;
	Players[2]->Team = 0;
	Players[2]->Side = 2;
	Players[2]->Position = D3DXVECTOR3(20, 0, 100);
	Scene3D->AddObject(Players[2]);

	Players[3] = new CPlayer(Scene3D);
	Players[3]->LoadMesh("chel_ball.x","chel.x","chel.x");
	Players[3]->HaveBall = false;
	Players[3]->Team = 1;
	Players[3]->Side = -1;
	Players[3]->Position = D3DXVECTOR3(250, 0, 200);
	Scene3D->AddObject(Players[3]);

	Players[4] = new CPlayer(Scene3D);
	Players[4]->LoadMesh("chel_ball.x","chel.x","chel.x");
	Players[4]->HaveBall = false;
	Players[4]->Team = 1;
	Players[4]->Side = -1;
	Players[4]->Position = D3DXVECTOR3(250, 0, 420);
	Scene3D->AddObject(Players[4]);
	*/
    Zombies[0] = new CZomby(Scene3D);
    Zombies[0]->LoadMesh("zomby.x","zomby.x","zomby.x");
    Zombies[0]->Position = D3DXVECTOR3(70, 10, 50);
	Zombies[0]->Hod_z= false;
	Scene3D->AddObject(Zombies[0]);

	Zombies[1] = new CZomby(Scene3D);
    Zombies[1]->LoadMesh("zomby.x","zomby.x","zomby.x");
    Zombies[1]->Position = D3DXVECTOR3(70, 10, 60);
	Zombies[1]->Hod_z= false;
	Scene3D->AddObject(Zombies[1]);

	Zombies[2] = new CZomby(Scene3D);
    Zombies[2]->LoadMesh("zomby.x","zomby.x","zomby.x");
    Zombies[2]->Position = D3DXVECTOR3(70, 10, 70);
	Zombies[2]->Hod_z= false;
	Scene3D->AddObject(Zombies[2]);

	Humans[0] = new CHuman(Scene3D);
    Humans[0]->LoadMesh("human.x","human.x","human.x");
    Humans[0]->Position = D3DXVECTOR3(60, 10, 40);
	Humans[0]->Hod_h= false;
	Scene3D->AddObject(Humans[0]);

	Humans[1] = new CHuman(Scene3D);
    Humans[1]->LoadMesh("human.x","human.x","human.x");
    Humans[1]->Position = D3DXVECTOR3(40, 10, 40);
	Humans[1]->Hod_h= false;
	Scene3D->AddObject(Humans[1]);

	Humans[2] = new CHuman(Scene3D);
    Humans[2]->LoadMesh("human.x","human.x","human.x");
    Humans[2]->Position = D3DXVECTOR3(50, 10, 40);
	Humans[2]->Hod_h= false;
	Scene3D->AddObject(Humans[2]);

	Blondees[0] = new CBlondes(Scene3D);
    Blondees[0]->LoadMesh("blonde.x","blonde.x","blonde.x");
    Blondees[0]->Position = D3DXVECTOR3(30, 10, 60);
	Blondees[0]->Hod_b=false;
	Scene3D->AddObject(Blondees[0]);

	Blondees[1] = new CBlondes(Scene3D);
    Blondees[1]->LoadMesh("blonde.x","blonde.x","blonde.x");
    Blondees[1]->Position = D3DXVECTOR3(30, 10, 70);
	Blondees[1]->Hod_b=false;
	Scene3D->AddObject(Blondees[1]);

	Blondees[2] = new CBlondes(Scene3D);
    Blondees[2]->LoadMesh("blonde.x","blonde.x","blonde.x");
    Blondees[2]->Position = D3DXVECTOR3(40, 10, 70);
	Blondees[2]->Hod_b=false;
	Scene3D->AddObject(Blondees[2]);

	Pole[0] = new CPole(Scene3D);
    Pole[0]->LoadMesh("pole.x","pole.x","pole.x");
    Pole[0]->Position = D3DXVECTOR3(50, 0, 50);
	Scene3D->AddObject(Pole[0]);


	Scene3D->BuildQuadTree();



	g_dLastTime     = timeGetTime();

	//Главный цикл
	while(TRUE) 
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		g_dCurTime     = timeGetTime();
		g_fElpasedTime = (float)((g_dCurTime - g_dLastTime)*0.001);
		g_dLastTime    = g_dCurTime;				
		
		Scene3D->Update(g_fElpasedTime);

		//-----------------------------------------
	//	Hardware3D->D3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
      //                   D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

		//Начало сцены
	//	if( SUCCEEDED( Scene3D->Hardware3D->D3DDevice->BeginScene() ) )
	//	{ 
			Scene3D->Render();	//оставить и раскомментить в Сцене
			//RenderGeometry();
		//	Scene3D->Hardware3D->D3DDevice->EndScene();	
	//	}

	//	Scene3D->Hardware3D->D3DDevice->Present( NULL, NULL, NULL, NULL );
		//-------------------------------------------
		
	}

	
	return msg.wParam;
}