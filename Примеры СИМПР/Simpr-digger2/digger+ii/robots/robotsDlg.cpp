// robotsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "monster.h"
#include "robots.h"
#include "player.h"
#include "robotsDlg.h"
#include "TMessage.h"
#include "mainfield.h"
#include "PictureBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SIMPR_MESSAGE "KAWAII_SIMPR"
#define   CONDITIONS   0
#define ACTIONS   1
static UINT SimprMessage = RegisterWindowMessage(SIMPR_MESSAGE);
CMutex g_m;

MainField* MyField;
PlayerDirection PlayerMove;
//rates purgatory;
// CAboutDlg dialog used for App About
//vector <robot*> RobotVec;
int ActiveMonster=0;
int ActiveBonus=0;
//HANDLE hEvent=CreateEvent(NULL,1,0,NULL);
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CrobotsDlg dialog




CrobotsDlg::CrobotsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CrobotsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BOOL CrobotsDlg::PreTranslateMessage(MSG* pMsg) 
{
	//bool found=1;
    if((pMsg->message==WM_KEYDOWN))
    {
		switch (pMsg->wParam)
		{
         case 38:
			 PlayerMove.up=1;
            break;
         case 40:
			 PlayerMove.down=1;
            break;
         case 37:
			 PlayerMove.left=1;
            break;
         case 39:
			 PlayerMove.right=1;
            break;
		// default:
			// found=0;
			// break;
		}
		//if(found)
			//SetEvent(hEvent);
		return 1;

	//CString z;
	//z.Format("%d",pMsg->wParam);
	//MessageBox(z);
       // if(pMsg->wParam==VK_RETURN)
       //     pMsg->wParam=VK_TAB;
    }	
    else return CDialog::PreTranslateMessage(pMsg);
}

void CrobotsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, start);
	DDX_Control(pDX, IDC_BUTTON2, stop);
	//DDX_Control(pDX, IDC_PICTURE, Pic);
	DDX_Control(pDX, IDC_PICTURE, Pic);
	DDX_Control(pDX, IDC_TEXT, RateText);
}

BEGIN_MESSAGE_MAP(CrobotsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CrobotsDlg::OnBnClickedButton1)
	ON_REGISTERED_MESSAGE(SimprMessage,&CrobotsDlg::OnSimpr)
	ON_BN_CLICKED(IDC_BUTTON2, &CrobotsDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CrobotsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CrobotsDlg message handlers

BOOL CrobotsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	Pic.Init();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CrobotsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CrobotsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CrobotsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CrobotsDlg::OnBnClickedOk()
{
	if(stop.IsWindowEnabled())
		OnBnClickedButton2();
	Pic.FreeSrc();
	//exit(0);
	OnOK();
}

void CrobotsDlg::OnBnClickedButton1()
{
	MyField=new MainField(Pic.FieldWidth,Pic.FieldHeight);
	MyField->PlayerField->PutRandomThing();
	MyField->MonsterField->PutRandomThing();
	MyField->MonsterField->PutRandomThing();

	MyField->WallField->PutRandomThing();
	MyField->WallField->PutRandomThing();
	MyField->WallField->PutRandomThing();
	MyField->WallField->PutRandomThing();
	MyField->WallField->PutRandomThing();
	MyField->WallField->PutRandomThing();
	MyField->WallField->PutRandomThing();
	MyField->WallField->PutRandomThing();
	MyField->WallField->PutRandomThing();
	MyField->WallField->PutRandomThing();
	MyField->WallField->PutRandomThing();
	MyField->WallField->PutRandomThing();

	
	MyField->BonusField->PutRandomThing();
	MyField->BonusField->PutRandomThing();
	MyField->BonusField->PutRandomThing();
	MyField->BonusField->PutRandomThing();
	MyField->BonusField->PutRandomThing();
	//MyField->MonsterField->PutRandomThing();
	//MyField->MonsterField->PutRandomThing();
	Pic.DrawField();
	start.EnableWindow(0);
	stop.EnableWindow(1);
	ActiveMonster=0;
	ActiveBonus=0;
}

void CrobotsDlg::OnBnClickedButton2()
{
	CSingleLock lock(&g_m);
    lock.Lock();
	//delete(MyField->PlayerField->ContentsVec.at(0));
	delete(MyField);
	start.EnableWindow(1);
	stop.EnableWindow(0);
	lock.Unlock();
}


LRESULT  CrobotsDlg::OnSimpr(WPARAM wParam, LPARAM lParam)
{
	if(!stop.IsWindowEnabled())
		return 0;
	CString z;
	bool exit=false;
	bool same=true;
	Player* player=MyField->PlayerField->ContentsVec.at(0);
	Monster* monster;
	Bonus* bonus;
	if(!stop.IsWindowEnabled())
		exit=1;
	if(exit)
	{
		if(stop.IsWindowEnabled())
		{
			Pic.DrawField();
			OnBnClickedButton2();
		}
		return 0;
	}

	Pic.DrawField();
	CSingleLock lock(&g_m);
    lock.Lock();
	//Sleep(2);
	bool res;
	TMessage m;
	m.WParam=(long)wParam;
	m.LParam=(long)lParam;
	m.Result=0;//do not need
	m.Msg=0;//do not need
	memcpy_s(&m.WParamLo,sizeof(INT16)*6,&m.WParam,sizeof(INT32)*3);
	
	
	if(MyField->MonsterField->ContentsVec.size()==0)
		MyField->MonsterField->PutRandomThing();
	
	unsigned int x=MyField->MonsterField->Active;
	if(x>=MyField->MonsterField->ContentsVec.size())
		MessageBox("WTF?!");
	monster=MyField->MonsterField->ContentsVec.at(x);

	switch(m.WParamHi)
	{
		case CONDITIONS:	// Условия
		switch(m.WParamLo) 
		{
			case 1:	// Таблица 1
				//WaitForSingleObject(hEvent,200);
				switch(m.LParam)        // Номер условия
				{
					case 1:
						if(player->State==0)
							res=1;
						else
							res=0;
						break;
					case 2:
						if(player->State==1)
							res=1;
						else
							res=0;
						break;
					case 3:
						if(player->State==2)
							res=1;
						else
							res=0;
						break;
					case 4:
						if(player->State==3)
							res=1;
						else
							res=0;
						break;
					case 5:
						if(player->State==4)
							res=1;
						else
							res=0;
						break;
					case 6:
						if(player->lifes>0)
							res=1;
						else
							res=0;
						break;
					case 7:
						bonus=player->FindNearestBonus();
						if(bonus==NULL)
							res=0;
						else
							res=1;
						break;
					case 8:
						bonus=player->FindNearestBonus();
						if(bonus==NULL)
							res=0;
						else
							res=!player->IsDangerousArea(player->NextStepToBonus(bonus));
						break;
					case 9:	
						res=player->AmIInDanger();
						break;
				}
			break;
			
			case 2:	// Таблица 2
				switch(m.LParam)        // Номер условия
				{
					case 1:
						if(monster->State==0)
							res=1;
						else
							res=0;
						break;
					case 2:
						if(monster->State==1)
							res=1;
						else
							res=0;
						break;
					case 3:
						if(monster->State==2)
							res=1;
						else
							res=0;
						break;
					case 4:
						if(monster->State==3)
							res=1;
						else
							res=0;
						break;
					case 5:
						if(monster->State==4)
							res=1;
						else
							res=0;
						break;
					case 6:
						//res=((monster->IfDie())&&(monster->State>4));//not dieing
						res=monster->IfDie();
						break;
					case 7:
						if(monster->FindClosePlayer()==NULL)
							res= 0;
						else
							res=1;
						break;
					case 8:	
						res=monster->IfGoForPlayer();
						break;
					case 9:	
						res=monster->IfEatWallNear();
						break;
					case 10:	
						res=monster->IfGoRandom();
						break;
					case 11:	
						if(MyField->MonsterField->Active>MyField->MonsterField->ContentsVec.size()-1)
							MessageBox("Wtf1?!");
						if(MyField->MonsterField->Active==MyField->MonsterField->ContentsVec.size()-1)
							res=1;
						else
							res=0;
						break;
				}
			break;
			case 3:	// Таблица 3
				switch(m.LParam)        // Номер условия
				{
					case 1:
						res=MyField->AddBonus();
						break;
					case 2:
						res=MyField->AddMonster();
						break;
					case 3:
						res=MyField->AddWall();
						break;
				}
			break;
		}
	 break;
		
	////////////
	case ACTIONS:	// Действия
		PlayerMove.Reset();
		z.Format("Осталось жизней: %d Очков: %d",player->lifes,player->points);
		RateText.SetWindowTextA(z.GetBuffer());
		res=1;
		switch(m.WParamLo) 
		{
			case 1:	// Таблица 1 
			//Sleep(500);
				switch(m.LParam)        // Номер действия
				{
					case 1:	//
					break;
					case 2:	// 
						player->State=1;
					break;
					case 3:	// 
						player->State=2;
					break;
					case 4:	// 
						player->State=3;
					break;
					case 5:	// 
						player->State=4;
					break;
					case 6:	// 
						player->Rebirth();
					//z.Format("Осталось жизней: %d Очков: %d",player->lifes,player->points);
					//RateText.SetWindowTextA(z.GetBuffer());
					break;
					case 7:	// 
						//player->Die();//end of game
						z.Format("Игра окончена! Очков: %d",player->points);
						RateText.SetWindowTextA(z.GetBuffer());
						OnBnClickedButton2();
						//player->State=0;
					break;
					case 8:
						player->MoveTo(player->NextStepToBonus(player->FindNearestBonus()));
					break;
					case 9:
						player->GoToSafeArea();
					break;
				}
				break;
			case 2:	// Таблица 2
				//Sleep(100);
				switch(m.LParam)        // Номер действия
				{
					case 1:	
						break;
					case 2:
						monster->State=1;
						break;
					case 3:	
						monster->State=2;
					break;
					case 4:
						monster->State=3;
						break;
					case 5:	
						monster->State=4;
						break;
					case 6:	
						monster->Die();
						if(MyField->MonsterField->Active>=MyField->MonsterField->ContentsVec.size())MyField->MonsterField->Active=0;
						break;
					case 7:	 
						monster->State=0;
						break;
					case 8:
						monster->Kill(monster->FindClosePlayer());
						break;
					case 9:
						monster->GoToPlayer();
						break;
					case 10:	
						monster->EatWall();
						break;
					case 11:	
						monster->MakeRandMove();
						break;
					case 12:
						if(monster->State>4)
							MyField->MonsterField->Active++;
						if(MyField->MonsterField->Active>=MyField->MonsterField->ContentsVec.size())MyField->MonsterField->Active=0;
					break;
					case 13:
						MyField->MonsterField->Active=0;
					break;
				}
				break;
				
			case 3:	// Таблица 3
				switch(m.LParam)       
				{
					case 1:
						MyField->BonusField->PutRandomThing();
						break;
					case 2:
						MyField->MonsterField->PutRandomThing();
						break;
					case 3:
						MyField->WallField->PutRandomThing();
						break;
				}
			break;
		}
		break;
	}
    lock.Unlock();
	return res;
	}
