// robotsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "robot.h"
#include "robots.h"
#include "rates.h"
#include "robotsDlg.h"
#include "TMessage.h"
#include "Field.h"
#include "PictureBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SIMPR_MESSAGE "KAWAII_SIMPR"
#define   CONDITIONS   0
#define ACTIONS   1
static UINT SimprMessage = RegisterWindowMessage(SIMPR_MESSAGE);
CMutex g_m;

Field* MyField;
rates purgatory;
// CAboutDlg dialog used for App About
vector <robot*> RobotVec;
int ActiveRobot=0;
robot* Robot;

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
//	ON_BN_CLICKED(IDC_BUTTON3, &CrobotsDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDOK, &CrobotsDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_PICTURE, &CrobotsDlg::OnStnClickedPicture)
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


void CrobotsDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	MyField=new Field(Pic.FieldWidth,Pic.FieldHeight);
	//MyField->Pic=this->Pic;
	robot* c;
	for(int i=0;i<20;i++)
	{
		c=MyField->PutRandomRobot();
		RobotVec.push_back(c);
	}
	Pic.DrawField();
	start.EnableWindow(0);
	stop.EnableWindow(1);
	//c->MakeRandMove();
	ActiveRobot=0;
	//delete(c);
	//SendMessage(SimprMessage, 0, 0);
}

void CrobotsDlg::OnBnClickedButton2()
{
	CSingleLock lock(&g_m);
    lock.Lock();
	//if(r==WAIT_OBJECT_0)
	{//mutex
		while(RobotVec.size()!=0)
		{
			delete(RobotVec.at(RobotVec.size()-1));
			RobotVec.resize(RobotVec.size()-1);
		}
		//RobotVec.clear();
		delete(MyField);
		start.EnableWindow(1);
		stop.EnableWindow(0);
	}
	lock.Unlock();
}


LRESULT  CrobotsDlg::OnSimpr(WPARAM wParam, LPARAM lParam)
{
//int i=0;
	CString z;
	bool exit=false;
	bool same=true;
	if(!stop.IsWindowEnabled())
		exit=1;
	if(RobotVec.size()<=1)
		exit=1;
	bool AnotherCommand=0;
	for(int i=0;i<RobotVec.size();i++)
		if(RobotVec.at(i)->command!=RobotVec.at(0)->command)
			same=0;
	if(exit||same)
	{
		if(stop.IsWindowEnabled())
		{
			if(MyField->NeedRedraw)
				Pic.DrawField();
			OnBnClickedButton2();
		}
		return 0;
	}

	if(MyField->NeedRedraw)
		Pic.DrawField();
	//if(count==0)ActiveRobot++;
	//if(count==4)count=0;
	//else count++;

	//robot* Robot=RobotVec.at(ActiveRobot);
	CSingleLock lock(&g_m);
    lock.Lock();
	Sleep(2);
	robot* temp;
	//if(ActiveRobot==0){
	//	i++;
	//}
	//DWORD r=WaitForSingleObject(Sync,INFINITE);
	//if(r==WAIT_OBJECT_0)
	
		//robot* r=RobotVec.at(0);
		bool res;
		TMessage m;
		m.WParam=wParam;
		m.LParam=lParam;
		m.Result=0;//do not need
		m.Msg=0;//do not need
		memcpy_s(&m.WParamLo,sizeof(INT16)*6,&m.WParam,sizeof(INT32)*3);
			
		switch(m.WParamHi)
		{
			case CONDITIONS:	// Условия
			switch(m.WParamLo) 
			{
				case 1:	// Таблица 1
					switch(m.LParam)        // Номер условия
					{
						case 1:	//find any robot
							//detect active
							ActiveRobot++;
							if(ActiveRobot>=RobotVec.size())
								ActiveRobot=0;
							Robot=RobotVec.at(ActiveRobot);

							temp=Robot->FindNearest();
							if(temp==NULL)
								res= 0;
							else
								res=1;
								break;
						case 2:	//find dangerous
							temp=Robot->FindDangerousEnemy();
							if(temp==NULL)
								res= 0;
							else
								res=1; 
								break;
						case 3:	// joinable 
							temp=Robot->FindJoinableFriend();
							if(temp==NULL)
								res= 0;
							else
								res=1; 
								break;
						case 4:	// weak 
							temp=Robot->FindWeakEnemy();
							if(temp==NULL)
								res= 0;
							else
								res=1; 
								break;
						case 5: 
							if(RobotVec.size()==2)
								res=1;
							else res=0;
								break;
					}
				break;

				case 2:	// Таблица 2 
				switch(m.LParam)        // Номер условия
				{
					case 1:	
						res=purgatory.IsEmpty();
						break;
					case 2: 
						res=purgatory.IfSinner();
						break;
					case 3: 
						res=purgatory.IfKiller();
						break;
					case 4: 
						res=purgatory.IfDevil();
						break;
					case 5: 
						res=purgatory.IfGood();
						break;
					case 6: 
						res=purgatory.IfSaint();
						break;
				}
				z.Format("Итого прошло: грешников-%d, убийц-%d, дьяволов-%d, хороших-%d, святых-%d",purgatory.sinner,purgatory.killer,purgatory.devil,purgatory.good,purgatory.saint);
				RateText.SetWindowTextA(z.GetBuffer());
				break; //
				case 3:	// Таблица 3 
				switch(m.LParam)        // Номер условия
				{
					case 1:
						Robot=Robot->FindEnemy();//take turns
						temp=Robot->FindNearest();
						if(temp==NULL)
							res=0;
						else
							res=1;
						break;
					case 2:	
						res=Robot->IsEnemyUp();
						break;
					case 3: 
						res=Robot->IsEnemyDown();
						break;
					case 4: 
						res=Robot->IsEnemyLeft();
						break;
					case 5: 
						res=Robot->IsEnemyRight();
						break;
				}

			}
		 break;
			
		////////////
		case ACTIONS:	// Действия
			res=1;
			switch(m.WParamLo) 
			{
				case 1:	// Таблица 1 
					switch(m.LParam)        // Номер действия
					{
						case 1:	// 
							Robot->MakeRandMove();
						break;
						case 2:	// 
							Robot->RunFromDangerousEnemy();
						break;
						case 3:	//
							Robot->Kill(Robot->FindWeakEnemy());
						break;
						case 4:	// 
							Robot->Join(Robot->FindJoinableFriend());
						break;
					}
					break;
				case 2:	// Таблица 2 
					switch(m.LParam)        // Номер действия
					{
						case 1:	
							break;
						case 2:	// Действие 1 
							purgatory.MakeSinner();
							break;
						case 3:	
							purgatory.MakeKiller();
							break;
						case 4:	
							purgatory.MakeDevil();
							break;
						case 5:	
							purgatory.MakeGood();
							break;
						case 6:	
							purgatory.MakeSaint();
							break;
					}
			break;
				case 3:	// Таблица 3 
					switch(m.LParam)        // Номер действия
					{
						case 1:	
							Robot->Kill(Robot->FindNearest());
							break;
						case 2:	
							Robot->MoveUp();
							break;
						case 3:	// Действие 1 
							Robot->MoveDown();
							break;
						case 4:	
							Robot->MoveLeft();
							break;
						case 5:	
							Robot->MoveRight();
							break;
					}
			break;
			}
			break;
		}
	//ReleaseMutex(Sync);
		
    lock.Unlock();
	return res;
	
}


void CrobotsDlg::OnBnClickedButton3()
{
	
}

void CrobotsDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if(stop.IsWindowEnabled())
		OnBnClickedButton2();
	OnOK();
}

void CrobotsDlg::OnStnClickedPicture()
{
	// TODO: Add your control notification handler code here
}
