#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "CrossDemo.h"

#define BEFORE    -2
#define AFTER     -1
#define BOTTOM     0
#define TOP        1
#define RIGHT      2
#define LEFT       3
#define STRAINGHT  4

#define YES	1
#define NO	0
#define CONDITIONS	 0
#define ACTIONS	    1

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
int Condition(WPARAM  wParam, LPARAM lParam);
int Action(WPARAM  wParam, LPARAM lParam);

char szWinName[] = "Перекресток";
char about_pr[] = "Перекресток, управляемый регулировщиком\nCopyright 2001-2005 Чибизова Н.В.\nМосковский энергетический институт (Технический университет)\nКафедра Прикладной математики";
int maxX, maxY, sizeX = 400, sizeY = 400, pos = 7, timeC = 0;
int stop = NO, permit = 1;
char str[256];
UINT MyMessage;
RECT rect  = {182, 183, 220, 221};
      
HINSTANCE hInst;
HBITMAP   hbit,  cbit;
HBITMAP   rbit[4], sbit[4], lbit[4], fbit[4], pbit[4], mbit[4];
HDC       memDC, cDC;
HDC       rDC[4],  sDC[4],  lDC[4],  fDC[4],  pDC[4],  mDC[4];
HWND      hwnd;
HDC       hdc;
HBRUSH    brush;
HPEN      pen;

class CCar
{ public:
    int from, to, go, place, xIncr, yIncr, turn, work, removal, r;
    RECT rect;
	CCar *prev, *next;
  public:
    CCar();
	~CCar();
	void Move();
 };

class CSpecCar
{ public:
    int type, from, place, xIncr, yIncr, work;
    RECT rect;
  public:
    CSpecCar();
	~CSpecCar();
	void Move();
 };

CCar *car, *p;
CCar *bLBegin  = NULL, *bLLast  = NULL, *bLWork;
CCar *bSRBegin = NULL, *bSRLast = NULL, *bSRWork;
CCar *rLBegin  = NULL, *rLLast  = NULL, *rLWork;
CCar *rSRBegin = NULL, *rSRLast = NULL, *rSRWork;
CCar *tLBegin  = NULL, *tLLast  = NULL, *tLWork;
CCar *tSRBegin = NULL, *tSRLast = NULL, *tSRWork;
CCar *lLBegin  = NULL, *lLLast  = NULL, *lLWork;
CCar *lSRBegin = NULL, *lSRLast = NULL, *lSRWork;
CSpecCar *spec = NULL;

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst,
                   LPSTR lpszArgs, int nWinMode)
{
 MSG msg;
 WNDCLASS wcl;
 HACCEL hAccel;
  
 wcl.style = CS_HREDRAW | CS_VREDRAW; //0;
 wcl.lpfnWndProc = (WNDPROC)WindowProc;
 wcl.cbClsExtra = 0;
 wcl.cbWndExtra = 0;
 wcl.hInstance = hThisInst;
 wcl.hIcon = LoadIcon(hThisInst, "CROSS_ICON");
 wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
 wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
 wcl.lpszMenuName = "CROSS_MENU";
 wcl.lpszClassName = szWinName;
 if (!RegisterClass(&wcl)) return 0;
 hwnd = CreateWindow(szWinName, "Перекресток",
                     WS_OVERLAPPED  | WS_CAPTION | WS_SYSMENU | 
                     WS_MINIMIZEBOX, 
                     CW_USEDEFAULT, CW_USEDEFAULT,
                     CW_USEDEFAULT, CW_USEDEFAULT,
                     HWND_DESKTOP, NULL, hThisInst, NULL);
 hInst = hThisInst;
 hAccel = LoadAccelerators(hThisInst, NULL);
 MoveWindow(hwnd, (maxX - sizeX)/2, (maxY - sizeY)/2 - 40,
                  sizeX + 6, sizeY + 45, TRUE);                 
 ShowWindow(hwnd, SW_SHOW);
 UpdateWindow(hwnd);
 hbit = LoadBitmap(hInst, "cross");
 SelectObject(memDC, hbit);
 BitBlt(hdc, 0, 0, sizeX, sizeY, memDC, 228, 0, SRCCOPY);
 cbit = LoadBitmap(hInst, "controller");
 SelectObject(cDC, cbit);
 BitBlt(memDC, 182, 183, 38, 38, cDC, 0, 0, SRCCOPY);
 InvalidateRect(hwnd, NULL, 1);
 rbit[BOTTOM] = LoadBitmap(hInst, "rightB");
 SelectObject(rDC[BOTTOM], rbit[BOTTOM]);
 sbit[BOTTOM] = LoadBitmap(hInst, "strainghtB");
 SelectObject(sDC[BOTTOM], sbit[BOTTOM]);
 lbit[BOTTOM] = LoadBitmap(hInst, "leftB");
 SelectObject(lDC[BOTTOM], lbit[BOTTOM]);
 fbit[BOTTOM] = LoadBitmap(hInst, "fairB");
 SelectObject(fDC[BOTTOM], fbit[BOTTOM]);
 pbit[BOTTOM] = LoadBitmap(hInst, "policeB");
 SelectObject(pDC[BOTTOM], pbit[BOTTOM]);
 mbit[BOTTOM] = LoadBitmap(hInst, "medicalB");
 SelectObject(mDC[BOTTOM], mbit[BOTTOM]);
 rbit[RIGHT] = LoadBitmap(hInst, "rightR");
 SelectObject(rDC[RIGHT], rbit[RIGHT]);
 sbit[RIGHT] = LoadBitmap(hInst, "strainghtR");
 SelectObject(sDC[RIGHT], sbit[RIGHT]);
 lbit[RIGHT] = LoadBitmap(hInst, "leftR");
 SelectObject(lDC[RIGHT], lbit[RIGHT]);
 fbit[RIGHT] = LoadBitmap(hInst, "fairR");
 SelectObject(fDC[RIGHT], fbit[RIGHT]);
 pbit[RIGHT] = LoadBitmap(hInst, "policeR");
 SelectObject(pDC[RIGHT], pbit[RIGHT]);
 mbit[RIGHT] = LoadBitmap(hInst, "medicalR");
 SelectObject(mDC[RIGHT], mbit[RIGHT]);
 rbit[TOP] = LoadBitmap(hInst, "rightT");
 SelectObject(rDC[TOP], rbit[TOP]);
 sbit[TOP] = LoadBitmap(hInst, "strainghtT");
 SelectObject(sDC[TOP], sbit[TOP]);
 lbit[TOP] = LoadBitmap(hInst, "leftT");
 SelectObject(lDC[TOP], lbit[TOP]);
 fbit[TOP] = LoadBitmap(hInst, "fairT");
 SelectObject(fDC[TOP], fbit[TOP]);
 pbit[TOP] = LoadBitmap(hInst, "policeT");
 SelectObject(pDC[TOP], pbit[TOP]);
 mbit[TOP] = LoadBitmap(hInst, "medicalT");
 SelectObject(mDC[TOP], mbit[TOP]);
 rbit[LEFT] = LoadBitmap(hInst, "rightL");
 SelectObject(rDC[LEFT], rbit[LEFT]);
 sbit[LEFT] = LoadBitmap(hInst, "strainghtL");
 SelectObject(sDC[LEFT], sbit[LEFT]);
 lbit[LEFT] = LoadBitmap(hInst, "leftL");
 SelectObject(lDC[LEFT], lbit[LEFT]);
 fbit[LEFT] = LoadBitmap(hInst, "fairL");
 SelectObject(fDC[LEFT], fbit[LEFT]);
 pbit[LEFT] = LoadBitmap(hInst, "policeL");
 SelectObject(pDC[LEFT], pbit[LEFT]);
 mbit[LEFT] = LoadBitmap(hInst, "medicalL");
 SelectObject(mDC[LEFT], mbit[LEFT]);
 SetTimer(hwnd, 1, 10, NULL);
 SetTimer(hwnd, 2, 100, NULL);
 srand((unsigned)time(NULL));
  while (GetMessage(&msg, NULL, 0, 0))
    if (!TranslateAccelerator(hwnd, hAccel, &msg))
     { TranslateMessage(&msg);
       DispatchMessage(&msg);
      }
 KillTimer(hwnd, 1);
 KillTimer(hwnd, 2);
 return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, 
                            WPARAM  wParam, LPARAM lParam)
{ PAINTSTRUCT paintstruct;
  int i;
    
  if (message == MyMessage)
   switch (HIWORD(wParam))
    { case CONDITIONS:
       return Condition(wParam, lParam);
      case ACTIONS:
       return Action(wParam, lParam);
     }
  else     
  switch (message)
   { case WM_DESTROY:
	  if (spec) delete spec;
	  for (car = bLBegin; car; )
	   { p = car; car = car->next; delete p; }
	  for (car = bSRBegin; car; )
	   { p = car; car = car->next; delete p; }
	  for (car = rLBegin; car; )
	   { p = car; car = car->next; delete p; }
	  for (car = rSRBegin; car; )
	   { p = car; car = car->next; delete p; }
	  for (car = tLBegin; car; )
	   { p = car; car = car->next; delete p; }
	  for (car = tSRBegin; car; )
	   { p = car; car = car->next; delete p; }
	  for (car = lLBegin; car; )
	   { p = car; car = car->next; delete p; }
	  for (car = lSRBegin; car; )
	   { p = car; car = car->next; delete p; }
	  DeleteDC(memDC);     DeleteDC(cDC);
   for (i = 0; i < 4; i++)
    { DeleteDC(rDC[i]);       DeleteDC(sDC[i]);
	     DeleteDC(lDC[i]);       DeleteDC(fDC[i]);
	     DeleteDC(pDC[i]);       DeleteDC(mDC[i]);
     }
	  DeleteObject(hbit);  DeleteObject(cbit);
	  DeleteObject(rbit);  DeleteObject(sbit);
	  DeleteObject(lbit);  DeleteObject(fbit);
	  DeleteObject(pbit);  DeleteObject(mbit);
	  DeleteObject(brush); DeleteObject(pen);
      PostQuitMessage(0);
      break;
     case WM_CLOSE:
      DestroyWindow(hwnd);
      return 0L;
     case WM_SIZE:
      break;
     case WM_TIMER:
	  if (wParam == 1)
	   { if (rand() % 10000 == 0 && !spec)
	      spec = new CSpecCar;
	     else if (rand() % 100 == 0 && permit)
	      car = new CCar;
	     for (car = bLBegin; car; car = car->next)
          if (car->work)
	       car->Move();
	     for (car = bSRBegin; car; car = car->next)
          if (car->work)
	       car->Move();
	     for (car = rLBegin; car; car = car->next)
          if (car->work)
	       car->Move();
	     for (car = rSRBegin; car; car = car->next)
          if (car->work)
	       car->Move();
	     for (car = tLBegin; car; car = car->next)
          if (car->work)
	       car->Move();
	     for (car = tSRBegin; car; car = car->next)
          if (car->work)
	       car->Move();
	     for (car = lLBegin; car; car = car->next)
          if (car->work)
	       car->Move();
	     for (car = lSRBegin; car; car = car->next)
          if (car->work)
	       car->Move();
		 if (spec) spec->Move();
		}
	   else
	    { timeC++;
          BitBlt(memDC, 182, 183, 38, 38, cDC, (pos - 1) * 38, 0, SRCCOPY);
          InvalidateRect(hwnd, &rect, 1);
		  if (spec && !spec->work) { delete spec; spec = NULL; }
	      for (car = bLBegin; car; )
           if (!car->work)
	        { p = car; car = car->next; delete p; }
		   else car = car->next;
	      for (car = bSRBegin; car; )
           if (!car->work)
	        { p = car; car = car->next; delete p; }
		   else car = car->next;
	      for (car = rLBegin; car; )
           if (!car->work)
	        { p = car; car = car->next; delete p; }
		   else car = car->next;
	      for (car = rSRBegin; car; )
           if (!car->work)
	        { p = car; car = car->next; delete p; }
		   else car = car->next;
	      for (car = tLBegin; car; )
           if (!car->work)
	        { p = car; car = car->next; delete p; }
		   else car = car->next;
	      for (car = tSRBegin; car; )
           if (!car->work)
	        { p = car; car = car->next; delete p; }
		   else car = car->next;
	      for (car = lLBegin; car; )
           if (!car->work)
	        { p = car; car = car->next; delete p; }
		   else car = car->next;
	      for (car = lSRBegin; car; )
           if (!car->work)
	        { p = car; car = car->next; delete p; }
		   else car = car->next;
		 }
      break;
     case WM_KEYUP:
      break;
     case WM_KEYDOWN:
      break;    
     case WM_CREATE:
      maxX  = GetSystemMetrics(SM_CXSCREEN);
      maxY  = GetSystemMetrics(SM_CYSCREEN);
      hdc   = GetDC(hwnd);
      memDC = CreateCompatibleDC(hdc);
      hbit  = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      cDC   = CreateCompatibleDC(hdc);
      cbit  = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      rDC[BOTTOM]   = CreateCompatibleDC(hdc);
      rbit[BOTTOM]  = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      sDC[BOTTOM]   = CreateCompatibleDC(hdc);
      sbit[BOTTOM]  = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      lDC[BOTTOM]   = CreateCompatibleDC(hdc);
      lbit[BOTTOM]  = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      fDC[BOTTOM]   = CreateCompatibleDC(hdc);
      fbit[BOTTOM]  = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      pDC[BOTTOM]   = CreateCompatibleDC(hdc);
      pbit[BOTTOM]  = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      mDC[BOTTOM]   = CreateCompatibleDC(hdc);
      mbit[BOTTOM]  = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      rDC[RIGHT]    = CreateCompatibleDC(hdc);
      rbit[RIGHT]   = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      sDC[RIGHT]    = CreateCompatibleDC(hdc);
      sbit[RIGHT]   = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      lDC[RIGHT]    = CreateCompatibleDC(hdc);
      lbit[RIGHT]   = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      fDC[RIGHT]    = CreateCompatibleDC(hdc);
      fbit[RIGHT]   = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      pDC[RIGHT]    = CreateCompatibleDC(hdc);
      pbit[RIGHT]   = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      mDC[RIGHT]    = CreateCompatibleDC(hdc);
      mbit[RIGHT]   = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      rDC[TOP]      = CreateCompatibleDC(hdc);
      rbit[TOP]     = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      sDC[TOP]      = CreateCompatibleDC(hdc);
      sbit[TOP]     = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      lDC[TOP]      = CreateCompatibleDC(hdc);
      lbit[TOP]     = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      fDC[TOP]      = CreateCompatibleDC(hdc);
      fbit[TOP]     = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      pDC[TOP]      = CreateCompatibleDC(hdc);
      pbit[TOP]     = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      mDC[TOP]      = CreateCompatibleDC(hdc);
      mbit[TOP]     = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      rDC[LEFT]     = CreateCompatibleDC(hdc);
      rbit[LEFT]    = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      sDC[LEFT]     = CreateCompatibleDC(hdc);
      sbit[LEFT]    = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      lDC[LEFT]     = CreateCompatibleDC(hdc);
      lbit[LEFT]    = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      fDC[LEFT]     = CreateCompatibleDC(hdc);
      fbit[LEFT]    = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      pDC[LEFT]     = CreateCompatibleDC(hdc);
      pbit[LEFT]    = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      mDC[LEFT]     = CreateCompatibleDC(hdc);
      mbit[LEFT]    = CreateCompatibleBitmap(hdc, sizeX, sizeY);
      brush = CreateSolidBrush(RGB(208, 208, 208));
      pen   = CreatePen(PS_SOLID, 1, RGB(208, 208, 208));
      SelectObject(memDC, brush);
      SelectObject(memDC, pen);
      ReleaseDC(hwnd, hdc);
      MyMessage = RegisterWindowMessage("MyMessage");
      break; 
     case WM_PAINT:
      hdc = BeginPaint(hwnd, &paintstruct);
      BitBlt(hdc, 0, 0, sizeX, sizeY, memDC, 0, 0, SRCCOPY);
      EndPaint(hwnd, &paintstruct);
      break;
     case WM_COMMAND:
       switch (LOWORD(wParam))
        { case ID_Stop:
		   stop = YES;
           break;
          case ID_About_pr:
           MessageBeep(MB_OK);
           MessageBox(hwnd, about_pr, "О программе", MB_OK | MB_ICONASTERISK);
           break;
         }
      break;     
     default:
      return DefWindowProc(hwnd, message, wParam, lParam);
    }
  return 0;
 }
 
CCar::CCar()
{ 
  permit = 0;
  from   = rand() % 4;
  to     = rand() % 3 + 2;
  place  = BEFORE;
  go     = work = 1;
  turn   = removal = 0;
  r      = rand() % 3;
  if (from == BOTTOM)
   { xIncr = 0; yIncr = -2;
	 if (to == LEFT || to == STRAINGHT && !r)
	  { rect.left  = 222; rect.top    = 400;
        rect.right = 250; rect.bottom = 442;
	    if (bLBegin == NULL)
	     { bLBegin = bLLast = this; prev = NULL; next = NULL; }
	    else
	     { bLLast->next = this; prev = bLLast; 
	       bLLast = this; next = NULL;
           if (rect.top - prev->rect.bottom < 14)
  	        { rect.top    = prev->rect.top    + 56;
	          rect.bottom = prev->rect.bottom + 56;
	         }
	      }
	   }
	 else
	  { rect.left  = 259; rect.top    = 400;
        rect.right = 288; rect.bottom = 442;
	    if (bSRBegin == NULL)
	     { bSRBegin = bSRLast = this; prev = NULL; next = NULL; }
	    else
	     { bSRLast->next = this; prev = bSRLast; 
	       bSRLast = this; next = NULL;
           if (rect.top - prev->rect.bottom < 14)
  	        { rect.top    = prev->rect.top    + 56;
	          rect.bottom = prev->rect.bottom + 56;
	         }
	      }
	   }
	}
  else if (from == RIGHT)
   { xIncr = -2; yIncr = 0;
	 if (to == LEFT || to == STRAINGHT && !r)
	  { rect.top    = 153; rect.left  = 400;
        rect.bottom = 182; rect.right = 442;
	    if (rLBegin == NULL)
	     { rLBegin = rLLast = this; prev = NULL; next = NULL; }
	    else
	     { rLLast->next = this; prev = rLLast; 
	       rLLast = this; next = NULL;
          if (rect.left - prev->rect.right < 14)
	       { rect.left  = prev->rect.left  + 56;
	         rect.right = prev->rect.right + 56;
	        }
	      }
	   }
	 else
	  { rect.top    = 116; rect.left  = 400;
        rect.bottom = 145; rect.right = 442;
	    if (rSRBegin == NULL)
	     { rSRBegin = rSRLast = this; prev = NULL; next = NULL; }
	    else
	     { rSRLast->next = this; prev = rSRLast; 
	       rSRLast = this; next = NULL;
          if (rect.left - prev->rect.right < 14)
	       { rect.left  = prev->rect.left  + 56;
	         rect.right = prev->rect.right + 56;
	        }
	      }
	   }
	}
  else if (from == TOP)
   { xIncr = 0; yIncr = 2;
	 if (to == LEFT || to == STRAINGHT && !r)
	  { rect.top    = -42; rect.left  = 152;
        rect.bottom =   0; rect.right = 181;
	    if (tLBegin == NULL)
	     { tLBegin = tLLast = this; prev = NULL; next = NULL; }
	    else
	     { tLLast->next = this; prev = tLLast; 
	       tLLast = this; next = NULL;
           if (prev->rect.top - rect.bottom < 14)
  	        { rect.top    = prev->rect.top    - 56;
	          rect.bottom = prev->rect.bottom - 56;
	         }
		  }
	   }
	 else
	  { rect.top    = -42; rect.left  = 114;
        rect.bottom =   0; rect.right = 143;
	    if (tSRBegin == NULL)
	     { tSRBegin = tSRLast = this; prev = NULL; next = NULL; }
	    else
	     { tSRLast->next = this; prev = tSRLast; 
	       tSRLast = this; next = NULL;
           if (prev->rect.top - rect.bottom < 14)
  	        { rect.top    = prev->rect.top    - 56;
	          rect.bottom = prev->rect.bottom - 56;
	         }
	      }
	   }
	}
  else if (from == LEFT)
   { xIncr = 2; yIncr = 0;
	 if (to == LEFT || to == STRAINGHT && !r)
	  { rect.top    = 223; rect.left  = -42;
        rect.bottom = 252; rect.right =   0;
	    if (lLBegin == NULL)
	     { lLBegin = lLLast = this; prev = NULL; next = NULL; }
	    else
	     { lLLast->next = this; prev = lLLast; 
	       lLLast = this; next = NULL;
          if (prev->rect.left - rect.right < 14)
	       { rect.left  = prev->rect.left  - 56;
	         rect.right = prev->rect.right - 56;
	        }
	      }
	   }
	 else
	  { rect.top    = 260; rect.left  = -42;
        rect.bottom = 289; rect.right =   0;
	    if (lSRBegin == NULL)
	     { lSRBegin = lSRLast = this; prev = NULL; next = NULL; }
	    else
	     { lSRLast->next = this; prev = lSRLast; 
	       lSRLast = this; next = NULL;
          if (prev->rect.left - rect.right < 14)
	       { rect.left  = prev->rect.left  - 56;
	         rect.right = prev->rect.right - 56;
	        }
	      }
	   }
	}
  if (to == RIGHT)
   BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, rDC[from], removal, 0, SRCCOPY);
  else if (to == STRAINGHT)
   BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, sDC[from], removal, 0, SRCCOPY);
  else
   BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, lDC[from], removal, 0, SRCCOPY);
  InvalidateRect(hwnd, &rect, 1);
  permit = 1;
 }

void CCar::Move()
{ 
  if (!go)
   { if (to == RIGHT)
      BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                    rect.bottom - rect.top, rDC[from], removal, 0, SRCCOPY);
     else if (to == STRAINGHT)
      BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                    rect.bottom - rect.top, sDC[from], removal, 0, SRCCOPY);
     else
      BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                    rect.bottom - rect.top, lDC[from], removal, 0, SRCCOPY);
     InvalidateRect(hwnd, &rect, 1); return;
	}
  if (prev && prev->place != AFTER)
   if (xIncr > 0 && prev->rect.left   - rect.right  < xIncr * 8 ||
       xIncr < 0 && prev->rect.right  - rect.left   > xIncr * 8 ||
	   yIncr > 0 && prev->rect.top    - rect.bottom < yIncr * 8 ||
	   yIncr < 0 && prev->rect.bottom - rect.top    > yIncr * 8)
   { if (to == RIGHT)
      BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                    rect.bottom - rect.top, rDC[from], removal, 0, SRCCOPY);
     else if (to == STRAINGHT)
      BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                    rect.bottom - rect.top, sDC[from], removal, 0, SRCCOPY);
     else
      BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                    rect.bottom - rect.top, lDC[from], removal, 0, SRCCOPY);
     InvalidateRect(hwnd, &rect, 1); return;
	}
  Rectangle(memDC, rect.left,  rect.top, rect.right, rect.bottom);
  InvalidateRect(hwnd, &rect, 1);
  rect.left += xIncr; rect.right  += xIncr;
  rect.top  += yIncr; rect.bottom += yIncr;
  if (turn)
   { if (from == BOTTOM)
      switch (++turn)
       { case 2:  removal += 50; xIncr++; break;
	     case 3:  removal += 50; xIncr++; break;
	  	 case 4:  removal += 50; 
		  		  rect.right  = rect.left + 44;
		          xIncr++; yIncr += 3; break;
	 	 case 5:  removal += 50; xIncr++; break;
		 case 6:  removal += 50; xIncr++; break;
		 case 7:  removal += 50; xIncr++; yIncr += 1; break;
		 case 8:  removal += 50; xIncr++; break;
		 case 9:  removal += 50; xIncr++; break;
		 case 10: removal += 50; xIncr = 2; yIncr = 0; turn = 0;
		  		  rect.right  = rect.left + 42;
                  rect.top = rect.bottom  - 29;
				  break;
		 case 80: xIncr = -1; yIncr = -6;
	              rect.right = rect.left   + 42;
                  rect.top   = rect.bottom - 42;
		 		  break;
		 case 81: removal += 50; xIncr--; break;
	     case 82: removal += 50; xIncr--; break;
		 case 83: removal += 50; xIncr--; yIncr += 3; break;
		 case 84: removal += 50; xIncr--; break;
		 case 85: removal += 50; xIncr--; break;
		 case 86: removal += 50; xIncr--; yIncr += 1; break;
		 case 87: removal += 50; xIncr--; break;
		 case 88: removal += 50; xIncr--; break;
		 case 89: removal += 50; xIncr = -2; yIncr = 0; turn = 0;
		  		  rect.right  = rect.left + 42;
                  rect.top = rect.bottom  - 29;
				  break;
	    }
     else if (from == RIGHT)
      switch (++turn)
       { case 2:  removal += 50; yIncr--; break;
	     case 3:  removal += 50; yIncr--; break;
	  	 case 4:  removal += 50; 
		          rect.top = rect.bottom  - 44;
		          yIncr--; xIncr += 3; break;
	 	 case 5:  removal += 50; yIncr--; break;
		 case 6:  removal += 50; yIncr--; break;
		 case 7:  removal += 50;
		  		  rect.right  = rect.left + 34;
				  yIncr--; xIncr += 1; break;
		 case 8:  removal += 50; yIncr--; break;
		 case 9:  removal += 50; yIncr--; break;
		 case 10: removal += 50; yIncr = -2; xIncr = 0; turn = 0;
		  		  rect.right  = rect.left + 29;
                  rect.bottom = rect.top  + 42;
				  break;
		 case 71: xIncr = -6; yIncr = 1;
	              rect.left = rect.right  - 44;
                  rect.top  = rect.bottom - 44;
		 		  removal += 50; break;
	     case 72: removal += 50; yIncr++; break;
		 case 73: removal += 50; yIncr++; xIncr += 3; break;
		 case 74: removal += 50; yIncr++; break;
		 case 75: removal += 50; yIncr++; break;
		 case 76: removal += 50; yIncr++; xIncr += 1; break;
		 case 77: removal += 50; yIncr++; break;
		 case 78: removal += 50; yIncr++; break;
		 case 79: removal += 50; yIncr = 2; xIncr = 0; turn = 0;
		  		  rect.right  = rect.left + 29;
                  rect.top = rect.bottom  - 42;
				  break;
	    }
     else if (from == TOP)
      switch (++turn)
       { case 2:  removal += 50; xIncr--; break;
	     case 3:  removal += 50; xIncr--; break;
	  	 case 4:  removal += 50; 
		  		  rect.right  = rect.left + 44;
		          xIncr--; yIncr -= 3; break;
	 	 case 5:  removal += 50; xIncr--; break;
		 case 6:  removal += 50; xIncr--; break;
		 case 7:  removal += 50; xIncr--; yIncr -= 1; break;
		 case 8:  removal += 50; xIncr--; break;
		 case 9:  removal += 50; xIncr--; break;
		 case 10: removal += 50; xIncr = -2; yIncr = 0; turn = 0;
		  		  rect.right  = rect.left + 42;
                  rect.bottom = rect.top  + 29;
				  break;
		 case 80: xIncr = 0; yIncr = 6;
	              rect.right   = rect.left + 50;
                  rect.bottom = rect.top   + 42;
		 		  removal += 50; xIncr++; break;
	     case 81: removal += 50; xIncr++; break;
		 case 82: removal += 50; xIncr++; yIncr -= 3; break;
		 case 83: removal += 50; xIncr++; break;
		 case 84: removal += 50; xIncr++; break;
		 case 85: removal += 50; xIncr++; yIncr -= 1; break;
		 case 86: removal += 50; xIncr++; break;
		 case 87: removal += 50; xIncr++; break;
		 case 88: removal += 50; xIncr = 2; yIncr = 0; turn = 0;
		  		  rect.left   = rect.right - 42;
                  rect.bottom = rect.top   + 29;
				  break;
	    }
     else if (from == LEFT)
      switch (++turn)
       { case 2:  removal += 50; yIncr++; break;
	     case 3:  removal += 50; yIncr++; break;
	  	 case 4:  removal += 50; 
		          rect.top = rect.bottom  - 44;
		          yIncr++; xIncr -= 3; break;
	 	 case 5:  removal += 50; yIncr++; break;
		 case 6:  removal += 50; yIncr++; break;
		 case 7:  removal += 50;
		  		  rect.right  = rect.left + 34;
				  yIncr++; xIncr -= 1; break;
		 case 8:  removal += 50; yIncr++; break;
		 case 9:  removal += 50; yIncr++; break;
		 case 10: removal += 50; yIncr = 2; xIncr = 0; turn = 0;
		  		  rect.right  = rect.left + 29;
                  rect.bottom = rect.top  + 42;
				  break;
		 case 76: xIncr = 6; yIncr = -1;
	              rect.left = rect.right  - 44;
                  rect.top  = rect.bottom - 44;
		 		  removal += 50; break;
	     case 77: removal += 50; yIncr--; break;
		 case 78: removal += 50; yIncr--; xIncr -= 3; break;
		 case 79: removal += 50; yIncr--; break;
		 case 80: removal += 50; yIncr--; break;
		 case 81: removal += 50; yIncr--; xIncr -= 1; break;
		 case 82: removal += 50; yIncr--; break;
		 case 83: removal += 50; yIncr--; break;
		 case 84: removal += 50; yIncr = -2; xIncr = 0; turn = 0;
		  		  rect.right  = rect.left + 29;
                  rect.top = rect.bottom  - 42;
				  break;
	    }
	 if (to == RIGHT)
	   BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                     rect.bottom - rect.top, rDC[from], removal, 0, SRCCOPY);
	 else
	   BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                     rect.bottom - rect.top, lDC[from], removal, 0, SRCCOPY);
     InvalidateRect(hwnd, &rect, 1);
     return;
    }
  if (to == RIGHT)
   BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, rDC[from], removal, 0, SRCCOPY);
  else if (to == STRAINGHT)
   BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, sDC[from], removal, 0, SRCCOPY);
  else
   BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, lDC[from], removal, 0, SRCCOPY);
  InvalidateRect(hwnd, &rect, 1);
  if (from == BOTTOM)
   if (rect.top < 278)
    { if (place == BEFORE && to == RIGHT)
       { turn = 1; xIncr = 1; yIncr = -6;
	     rect.right = rect.left    + 38;
         rect.top   = rect.bottom  - 44;
        }
	  else if (place == BEFORE && to == LEFT)
	   turn = 11;
	  place = AFTER;
	 }
  if (from == RIGHT)
   if (rect.left < 276)
    { if (place == BEFORE && to == RIGHT)
       { turn = 1; xIncr = -6; yIncr = -1;
	     rect.left = rect.right  - 44;
         rect.top  = rect.bottom - 39;
        }
	  else if (place == BEFORE && to == LEFT)
	   turn = 11;
	  place = AFTER;
	 }
  if (from == TOP)
   if (rect.bottom > 126)
    { if (place == BEFORE && to == RIGHT)
       { turn = 1; xIncr = -1; yIncr = 6;
	     rect.right  = rect.left  + 39;
         rect.bottom = rect.top   + 44;
        }
	  else if (place == BEFORE && to == LEFT)
	   turn = 11;
	  place = AFTER;
	 }
  if (from == LEFT)
   if (rect.left > 98)
    { if (place == BEFORE && to == RIGHT)
       { turn = 1; xIncr = 6; yIncr = 1;
	     rect.right  = rect.left + 44;
         rect.bottom = rect.top  + 39;
        }
	  else if (place == BEFORE && to == LEFT)
	   turn = 11;
	  place = AFTER;
	 }
  if (xIncr > 0 && rect.left   > 400 ||
      xIncr < 0 && rect.right  < 0   ||
      yIncr > 0 && rect.top    > 400 ||
      yIncr < 0 && rect.bottom < 0)
   work = 0;
 }

CCar::~CCar()
{ 
  if (from == BOTTOM)
   if (to == RIGHT || to == STRAINGHT && r)
    { if (bSRBegin == bSRLast)
       { bSRBegin = bSRLast = NULL; }
      else if (this == bSRBegin)
       { bSRBegin = bSRBegin->next; bSRBegin->prev = NULL; }
      else if (this == bSRLast)
       { bSRLast = bSRLast->prev; bSRLast->next = NULL; }
      else
       { prev->next = next; next->prev = prev; }
	 }
   else
    { if (bLBegin == bLLast)
       { bLBegin = bLLast = NULL; }
      else if (this == bLBegin)
       { bLBegin = bLBegin->next; bLBegin->prev = NULL; }
      else if (this == bLLast)
       { bLLast = bLLast->prev; bLLast->next = NULL; }
      else
       { prev->next = next; next->prev = prev; }
	 }
  else if (from == RIGHT)
   if (to == RIGHT || to == STRAINGHT && r)
    { if (rSRBegin == rSRLast)
       { rSRBegin = rSRLast = NULL; }
      else if (this == rSRBegin)
       { rSRBegin = rSRBegin->next; rSRBegin->prev = NULL; }
      else if (this == rSRLast)
       { rSRLast = rSRLast->prev; rSRLast->next = NULL; }
      else
       { prev->next = next; next->prev = prev; }
	 }
   else
    { if (rLBegin == rLLast)
       { rLBegin = rLLast = NULL; }
      else if (this == rLBegin)
       { rLBegin = rLBegin->next; rLBegin->prev = NULL; }
      else if (this == rLLast)
       { rLLast = rLLast->prev; rLLast->next = NULL; }
      else
       { prev->next = next; next->prev = prev; }
	 }
  else if (from == TOP)
   if (to == RIGHT || to == STRAINGHT && r)
    { if (tSRBegin == tSRLast)
       { tSRBegin = tSRLast = NULL; }
      else if (this == tSRBegin)
       { tSRBegin = tSRBegin->next; tSRBegin->prev = NULL; }
      else if (this == tSRLast)
       { tSRLast = tSRLast->prev; tSRLast->next = NULL; }
      else
       { prev->next = next; next->prev = prev; }
	 }
   else
    { if (tLBegin == tLLast)
       { tLBegin = tLLast = NULL; }
      else if (this == tLBegin)
       { tLBegin = tLBegin->next; tLBegin->prev = NULL; }
      else if (this == rLLast)
       { tLLast = tLLast->prev; tLLast->next = NULL; }
      else
       { prev->next = next; next->prev = prev; }
	 }
  else if (from == LEFT)
   if (to == RIGHT || to == STRAINGHT && r)
    { if (lSRBegin == lSRLast)
       { lSRBegin = lSRLast = NULL; }
      else if (this == lSRBegin)
       { lSRBegin = lSRBegin->next; lSRBegin->prev = NULL; }
      else if (this == lSRLast)
       { lSRLast = lSRLast->prev; lSRLast->next = NULL; }
      else
       { prev->next = next; next->prev = prev; }
	 }
   else
    { if (lLBegin == lLLast)
       { lLBegin = lLLast = NULL; }
      else if (this == lLBegin)
       { lLBegin = lLBegin->next; lLBegin->prev = NULL; }
      else if (this == lLLast)
       { lLLast = lLLast->prev; lLLast->next = NULL; }
      else
       { prev->next = next; next->prev = prev; }
	 }
 }

CSpecCar::CSpecCar()
{ 
  type = rand() % 3;
  from = rand() % 4;
  work = 1;
  place = BEFORE;
  if (from == BOTTOM)
   { xIncr = 0; yIncr = -4;
	 rect.left  = 221; rect.top    = 400;
     if (type == 0)                       // Пожарная
      { rect.right = 250; rect.bottom = 450;
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, fDC[from], 0, 0, SRCCOPY);
       }
     else if (type == 1)                 // Милиция
      { rect.right = 250; rect.bottom = 445;
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, pDC[from], 0, 0, SRCCOPY);
	   }
     else                                 // Скорая помощь
      { rect.right = 248; rect.bottom = 450;
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, mDC[from], 0, 0, SRCCOPY);
	   }
	}
  else if (from == RIGHT)
   { xIncr = -4; yIncr = 0;
	 rect.top  = 150; rect.left  = 400;
     if (type == 0)                       // Пожарная
      { rect.right = 450; rect.bottom = 179; // 29, 50
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, fDC[from], 0, 0, SRCCOPY);
       }
     else if (type == 1)                 // Милиция
      { rect.right = 445; rect.bottom = 179; //29, 45
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, pDC[from], 0, 0, SRCCOPY);
	   }
     else                                 // Скорая помощь
      { rect.right = 450; rect.bottom = 177; //27, 50
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, mDC[from], 0, 0, SRCCOPY);
	   }
	}
  else if (from == TOP)
   { xIncr = 0; yIncr = 4;
	 rect.bottom  = 0; rect.left  = 150;
     if (type == 0)                       // Пожарная
      { rect.right = 179; rect.top = -50; // 29, 50
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, fDC[from], 0, 0, SRCCOPY);
       }
     else if (type == 1)                 // Милиция
      { rect.right = 179; rect.top = -45; //29, 45
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, pDC[from], 0, 0, SRCCOPY);
	   }
     else                                 // Скорая помощь
      { rect.right = 177; rect.top = -50; //27, 50
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, mDC[from], 0, 0, SRCCOPY);
	   }
	}
  else if (from == LEFT)
   { xIncr = 4; yIncr = 0;
	 rect.top  = 220; rect.right  = 0;
     if (type == 0)                       // Пожарная
      { rect.left = -50; rect.bottom = 249; // 29, 50
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, fDC[from], 0, 0, SRCCOPY);
       }
     else if (type == 1)                 // Милиция
      { rect.left = -45; rect.bottom = 249; //29, 45
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, pDC[from], 0, 0, SRCCOPY);
	   }
     else                                 // Скорая помощь
      { rect.left = -50; rect.bottom = 247; //27, 50
        BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                      rect.bottom - rect.top, mDC[from], 0, 0, SRCCOPY);
	   }
	}
  InvalidateRect(hwnd, &rect, 1);
 }

void CSpecCar::Move()
{ 
  Rectangle(memDC, rect.left,  rect.top, rect.right, rect.bottom);
  InvalidateRect(hwnd, &rect, 1);
  rect.left += xIncr; rect.right  += xIncr;
  rect.top  += yIncr; rect.bottom += yIncr;
  if (type == 0)                       // Пожарная
   BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, fDC[from], 0, 0, SRCCOPY);
  else if (type == 1)                 // Милиция
   BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, pDC[from], 0, 0, SRCCOPY);
  else                                 // Скорая помощь
   BitBlt(memDC, rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, mDC[from], 0, 0, SRCCOPY);
  InvalidateRect(hwnd, &rect, 1);
  if (from == BOTTOM && rect.top    < 240 ||
      from == RIGHT  && rect.left   < 240 ||
      from == TOP    && rect.bottom > 240 ||
      from == LEFT   && rect.right  > 240)
   place = AFTER;
  if (xIncr > 0 && rect.left   > 400 ||
      xIncr < 0 && rect.right  < 0   ||
      yIncr > 0 && rect.top    > 400 ||
      yIncr < 0 && rect.bottom < 0)
   work = 0;
 }

CSpecCar::~CSpecCar()
{ 
 }

int Condition(WPARAM  wParam, LPARAM lParam)
{
  switch (LOWORD(wParam))
   { case 1: return stop;                            // Таблица 1
     case 2:                                         // Таблица 2 - Смена позиции регулировщика
	  if (spec || pos == 7 || timeC > 50)
       { timeC = 0; return YES; }
	  else return NO;
	 case 3:                                         // Таблица 3
	  switch (lParam)
       { case 1:                                     // Пожарная, милиция, скорая помощь?
		  if (spec) return YES;
		  else return NO;
	     case 2:                                     // Машина снизу?
		  for (car = bLBegin; car; car = car->next)
		   if (car->place != AFTER)
		    return YES;
		  for (car = bSRBegin; car; car = car->next)
		   if (car->place != AFTER)
		    return YES;
		  return NO;
	     case 3:                                     // Машина справа?
	      for (car = rLBegin; car; car = car->next)
		   if (car->place != AFTER)
		    return YES;
		  for (car = rSRBegin; car; car = car->next)
		   if (car->place != AFTER)
		    return YES;
		  return NO;
		 case 4:                                     // Машина сверху?
	      for (car = tLBegin; car; car = car->next)
		   if (car->place != AFTER)
		    return YES;
		  for (car = tSRBegin; car; car = car->next)
		   if (car->place != AFTER)
		    return YES;
		  return NO;
		 case 5:                                     // Машина снизу?
	      for (car = lLBegin; car; car = car->next)
		   if (car->place != AFTER)
		    return YES;
		  for (car = lSRBegin; car; car = car->next)
		   if (car->place != AFTER)
		    return YES;
		  return NO;
		}
     case 4:                                         // Таблица 4
	  switch (lParam)
	   { case 1:                                     // Есть машина в левом ряду?
		  for (bLWork = NULL, car = bLBegin; car; car = car->next)
		   if (car->place != AFTER && car->rect.top < 320)
		    { bLWork = car; return YES; }
		  return NO;
		 case 2:                                     // Машина едет налево?
		  if (bLWork && bLWork->to == LEFT) return YES;
		  else return NO;
		 case 3:                                     // Позиция регулировщика № 2?
		  if (pos == 2) return YES;
		  else return NO;
		 case 4:                                     // Позиция регулировщика № 3?
		  if (pos == 3) return YES;
		  else return NO;
		}
     case 5:                                         // Таблица 5
	  switch (lParam)
	   { case 1:                                     // Есть машина в правом ряду?
		  for (bSRWork = NULL, car = bSRBegin; car; car = car->next)
		   if (car->place != AFTER && car->rect.top < 320)
		    { bSRWork = car; return YES; }
		  return NO;
		 case 2:                                     // Машина едет направо?
		  if (bSRWork && bSRWork->to == RIGHT)     return YES;
		  else return NO;
		 case 3:                                     // Позиция регулировщика № 1?
		  if (pos == 1) return YES;
		  else return NO;
		 case 4:                                     // Позиция регулировщика № 2?
		  if (pos == 2) return YES;
		  else return NO;
		 case 5:                                     // Позиция регулировщика № 3?
		  if (pos == 3) return YES;
		  else return NO;
		}
     case 6:                                         // Таблица 6
	  switch (lParam)
	   { case 1:                                     // Есть машина в левом ряду?
		  for (rLWork = NULL, car = rLBegin; car; car = car->next)
		   if (car->place != AFTER && car->rect.left < 330)
		    { rLWork = car; return YES; }
		  return NO;
		 case 2:                                     // Машина едет налево?
		  if (rLWork && rLWork->to == LEFT) return YES;
		  else return NO;
		 case 3:                                     // Позиция регулировщика № 6?
		  if (pos == 6) return YES;
		  else return NO;
		 case 4:                                     // Позиция регулировщика № 1?
		  if (pos == 1) return YES;
		  else return NO;
		}
     case 7:                                         // Таблица 7
	  switch (lParam)
	   { case 1:                                     // Есть машина в правом ряду?
		  for (rSRWork = NULL, car = rSRBegin; car; car = car->next)
		   if (car->place != AFTER && car->rect.left < 330)
		    { rSRWork = car; return YES; }
		  return NO;
		 case 2:                                     // Машина едет направо?
		  if (rSRWork && rSRWork->to == RIGHT)     return YES;
		  else return NO;
		 case 3:                                     // Позиция регулировщика № 5?
		  if (pos == 5) return YES;
		  else return NO;
		 case 4:                                     // Позиция регулировщика № 6?
		  if (pos == 6) return YES;
		  else return NO;
		 case 5:                                     // Позиция регулировщика № 1?
		  if (pos == 1) return YES;
		  else return NO;
		}
     case 8:                                         // Таблица 8
	  switch (lParam)
	   { case 1:                                     // Есть машина в левом ряду?
		  for (tLWork = NULL, car = tLBegin; car; car = car->next)
		   if (car->place != AFTER && car->rect.bottom > 90)
		    { tLWork = car; return YES; }
		  return NO;
		 case 2:                                     // Машина едет налево?
		  if (tLWork && tLWork->to == LEFT) return YES;
		  else return NO;
		 case 3:                                     // Позиция регулировщика № 2?
		  if (pos == 2) return YES;
		  else return NO;
		 case 4:                                     // Позиция регулировщика № 5?
		  if (pos == 5) return YES;
		  else return NO;
		}
     case 9:                                         // Таблица 9
	  switch (lParam)
	   { case 1:                                     // Есть машина в правом ряду?
		  for (tSRWork = NULL, car = tSRBegin; car; car = car->next)
		   if (car->place != AFTER && car->rect.bottom > 90)
		    { tSRWork = car; return YES; }
		  return NO;
		 case 2:                                     // Машина едет направо?
		  if (tSRWork && tSRWork->to == RIGHT)     return YES;
		  else return NO;
		 case 3:                                     // Позиция регулировщика № 4?
		  if (pos == 4) return YES;
		  else return NO;
		 case 4:                                     // Позиция регулировщика № 2?
		  if (pos == 2) return YES;
		  else return NO;
		 case 5:                                     // Позиция регулировщика № 5?
		  if (pos == 5) return YES;
		  else return NO;
		}
     case 10:                                         // Таблица 10
	  switch (lParam)
	   { case 1:                                     // Есть машина в левом ряду?
		  for (lLWork = NULL, car = lLBegin; car; car = car->next)
		   if (car->place != AFTER && car->rect.right > 50)
		    { lLWork = car; return YES; }
		  return NO;
		 case 2:                                     // Машина едет налево?
		  if (lLWork && lLWork->to == LEFT) return YES;
		  else return NO;
		 case 3:                                     // Позиция регулировщика № 6?
		  if (pos == 6) return YES;
		  else return NO;
		 case 4:                                     // Позиция регулировщика № 4?
		  if (pos == 4) return YES;
		  else return NO;
		}
     case 11:                                         // Таблица 11
	  switch (lParam)
	   { case 1:                                     // Есть машина в правом ряду?
		  for (lSRWork = NULL, car = lSRBegin; car; car = car->next)
		   if (car->place != AFTER && car->rect.right > 50)
		    { lSRWork = car; return YES; }
		  return NO;
		 case 2:                                     // Машина едет направо?
		  if (lSRWork && lSRWork->to == RIGHT)     return YES;
		  else return NO;
		 case 3:                                     // Позиция регулировщика № 3?
		  if (pos == 3) return YES;
		  else return NO;
		 case 4:                                     // Позиция регулировщика № 6?
		  if (pos == 6) return YES;
		  else return NO;
		 case 5:                                     // Позиция регулировщика № 4?
		  if (pos == 4) return YES;
		  else return NO;
		}
    }
  return NO;
 }

int Action(WPARAM  wParam, LPARAM lParam)
{ 
  switch (LOWORD(wParam))
   { case 1:                                         // Таблица 1
      if (lParam == 0)
       { DestroyWindow(hwnd);
         return YES;
        }
	 case 3:                                         // Таблица 3
	  switch (lParam)
	   { case 1:                                     // Позиция № 1
          pos = 1; break;
	     case 2:                                     // Позиция № 2
          pos = 2; break;
		 case 3:                                     // Позиция № 3
          pos = 3; break;
		 case 4:                                     // Позиция № 4
          pos = 4; break;
		 case 5:                                     // Позиция № 5
          pos = 5; break;
		 case 6:                                     // Позиция № 6
          pos = 6; break;
		 case 7:                                     // Позиция № 7
          pos = 7; break;
         case 8:
          pos = pos % 6 + 1;
          if (pos == 2) pos = 3;
          else if (pos == 6) pos = 1;
          break;
		}
      BitBlt(memDC, 182, 183, 38, 38, cDC, (pos - 1) * 38, 0, SRCCOPY);
      InvalidateRect(hwnd, &rect, 1);
      return YES; 
	 case 4:                                         // Таблица 4
	  switch (lParam)
	   { case 1:                                     // Ехать
	      bLWork->go = 1; return YES;
		 case 2:                                     // Ждать
		  bLWork->go = 0; return YES;
		}
     case 5:                                         // Таблица 5
	  switch (lParam)
	   { case 1:                                     // Ехать
	      bSRWork->go = 1; return YES;
		 case 2:                                     // Ждать
		  bSRWork->go = 0; return YES;
		}
     case 6:                                         // Таблица 6
	  switch (lParam)
	   { case 1:                                     // Ехать
	      rLWork->go = 1; return YES;
		 case 2:                                     // Ждать
		  rLWork->go = 0; return YES;
		}
     case 7:                                         // Таблица 7
	  switch (lParam)
	   { case 1:                                     // Ехать
	      rSRWork->go = 1; return YES;
		 case 2:                                     // Ждать
		  rSRWork->go = 0; return YES;
		}
     case 8:                                         // Таблица 8
	  switch (lParam)
	   { case 1:                                     // Ехать
	      tLWork->go = 1; return YES;
		 case 2:                                     // Ждать
		  tLWork->go = 0; return YES;
		}
     case 9:                                         // Таблица 9
	  switch (lParam)
	   { case 1:                                     // Ехать
	      tSRWork->go = 1; return YES;
		 case 2:                                     // Ждать
		  tSRWork->go = 0; return YES;
		}
     case 10:                                         // Таблица 10
	  switch (lParam)
	   { case 1:                                     // Ехать
	      lLWork->go = 1; return YES;
		 case 2:                                     // Ждать
		  lLWork->go = 0; return YES;
		}
     case 11:                                         // Таблица 11
	  switch (lParam)
	   { case 1:                                     // Ехать
	      lSRWork->go = 1; return YES;
		 case 2:                                     // Ждать
		  lSRWork->go = 0; return YES;
		}
    }
  return YES;
 }