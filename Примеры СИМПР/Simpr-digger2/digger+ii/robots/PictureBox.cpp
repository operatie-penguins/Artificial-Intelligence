#pragma once
// PictureBox.cpp : implementation file
   //
#include "stdafx.h"
#include "PictureBox.h"
#include "mainfield.h"
#include "funcs.h"
extern MainField* MyField;   
   // CPictureBox
   
   IMPLEMENT_DYNAMIC(CPictureBox, CStatic)
   CPictureBox::CPictureBox()
   {
   }
   
   CPictureBox::~CPictureBox()
   {
   }
   
   
   BEGIN_MESSAGE_MAP(CPictureBox, CStatic)
    ON_WM_PAINT()
   END_MESSAGE_MAP()
   
   
   
   // CPictureBox message handlers
   void CPictureBox::FreeSrc()
   {
		for(int i=0;i<monsters;i++)
		{
			for(int n=0;n<states;n++)
				DeleteObject(Frames[i][n]);
			delete[] Frames[i];
		}
		delete[] Frames;
		delete[] Potions;
		DeleteObject(WallBmp);
   }
   void CPictureBox::ShowBitmap(CPaintDC *pdc) 
   {
    //Create a device context to load the bitmap into
    CDC dcMem;
    dcMem.CreateCompatibleDC(pdc);
   
    //Get the Display area available
    CRect lRect;
    GetClientRect(lRect);
    lRect.NormalizeRect();
   
    //select the bitmap into compatible device context
    CBitmap* pOldBitmap = (CBitmap*)dcMem.SelectObject(&m_bmpBitmap);
    //m_bmpBitmap.SetBitmapDimension(lRect.Width(),lRect  .Height());
   
    //copy & resize the window to the dialog window
    pdc->StretchBlt(0,0,lRect.Width(),lRect.Height(),&dcMem,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
   }


   void CPictureBox::OnPaint()
   {
    CPaintDC dc(this); // device context for painting
   
    RECT rect;
    GetClientRect(&rect);
    //dc.FillSolidRect(&rect, RGB(255,255,255));
   
    //if(m_sBitmap!="")
     ShowBitmap(&dc);
	DeleteDC(dc);
   }


void CPictureBox::SetBitmap(CString strBitmap)
{
    m_sBitmap = strBitmap;
   
    HBITMAP hBitmap = (HBITMAP) ::LoadImage(AfxGetInstanceHandle(),
    m_sBitmap, IMAGE_BITMAP, 0, 0, 
    LR_LOADFROMFILE | LR_CREATEDIBSECTION);
   
    // Do we have a valid handle for the loaded image?
    if (hBitmap)
    {
     // Delete the current bitmap
     if (m_bmpBitmap.DeleteObject())
        m_bmpBitmap.Detach(); // If there was a bitmap, detach it
     // Attach the currently loaded bitmap to the bitmap object
     m_bmpBitmap.Attach(hBitmap);
    }
    m_bmpBitmap.GetBitmap(&bm);  //Get Bitmap Structure
    Invalidate();
}

void CPictureBox::Init()
{
	CString way;
	Frames=new HBITMAP*[monsters];
	for(int i=0;i<monsters;i++)
		Frames[i]=new HBITMAP[states];

	Potions=new HBITMAP[potions];
	for(int i=0;i<monsters;i++)
		for(int n=0;n<states;n++)
		{
			way.Format("pic/%d_%d.bmp",i,n);
			Frames[i][n]= (HBITMAP) ::LoadImage(AfxGetInstanceHandle(),
				way.GetBuffer(), IMAGE_BITMAP, 0, 0, 
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			if(Frames[i][n]==NULL)
			{
				MessageBox("Fatal error: could not load monster image!!!");
				exit(3);
			} 
		}
		
		for(int n=0;n<potions;n++)
		{
			way.Format("pic/potion_%d.bmp",n);
			Potions[n]= (HBITMAP) ::LoadImage(AfxGetInstanceHandle(),
				way.GetBuffer(), IMAGE_BITMAP, 0, 0, 
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			if(Potions[n]==NULL)
			{
				MessageBox("Fatal error: could not load potion image!!!");
				exit(3);
			} 
		}
	WallBmp= (HBITMAP) ::LoadImage(AfxGetInstanceHandle(),"pic/wall.bmp", IMAGE_BITMAP, 0, 0, 
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if(WallBmp==NULL)
	{
		MessageBox("Fatal error: could not load wall image!!!");
		exit(3);
	} 
	BITMAP bm1;
	GetObject(Frames[0][6], sizeof(BITMAP), &bm1 );
	ItemWidth=bm1.bmWidth;
	ItemHeight=bm1.bmHeight;
	RECT rgn;
	this->GetWindowRect(&rgn);
	this->FieldWidth=(rgn.right-rgn.left)/ItemWidth;
	this->FieldHeight=(rgn.bottom-rgn.top)/ItemHeight;
	//DeleteObject(hBitmap);
	dc=CreateCompatibleDC(NULL);
}


void CPictureBox::DrawField()
{
	HDC TmpDC=CreateCompatibleDC(dc);
	BITMAPINFO bmInfo;
	ZeroMemory( &bmInfo.bmiHeader, sizeof(BITMAPINFOHEADER) );
	RECT rgn;
	this->GetWindowRect(&rgn);
	bmInfo.bmiHeader.biWidth=(rgn.right-rgn.left);
	bmInfo.bmiHeader.biHeight=(rgn.bottom-rgn.top);
	bmInfo.bmiHeader.biPlanes=1;
	bmInfo.bmiHeader.biBitCount=24;
	bmInfo.bmiHeader.biSizeImage=0;
	bmInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmInfo.bmiHeader.biClrUsed= 0;
	bmInfo.bmiHeader.biClrImportant= 0;

	BYTE *pbase;
	HBITMAP TmpBmp=CreateDIBSection(dc,
		&bmInfo,DIB_RGB_COLORS,(void**)&pbase,0,0);
	HGDIOBJ TmpObj=SelectObject(TmpDC,TmpBmp);

    //TmpDC.FillSolidRect(&rgn, RGB(255,255,255));
	rgn.bottom=40;//(rgn.bottom-rgn.top);
	rgn.right=30;////(rgn.right-rgn.left);
	rgn.left=10;
	rgn.top=10;
	//FillRect(TmpDC,&rgn,(HBRUSH) RGB(0,0,0));
	HDC dcBmp=CreateCompatibleDC(TmpDC);
	
	HGDIOBJ TmpObj2;
	//Draw player
	for(int x=0;x<MyField->PlayerField->width;x++)
		for(int y=0;y<MyField->PlayerField->height;y++)
			if(MyField->PlayerField->cells[x][y]!=NULL)
			{
				TmpObj2 = SelectObject(dcBmp,Frames[0][MyField->PlayerField->ContentsVec.at(0)->State]);
				BitBlt(TmpDC,ItemWidth*x,ItemHeight*y,ItemWidth,ItemHeight,dcBmp,0,0,SRCCOPY);
			}
	//SelectObject(TmpDC,TmpObj2);
	//DeleteDC(dcBmp);
	//Draw monsters
	for(int x=0;x<MyField->MonsterField->width;x++)
		for(int y=0;y<MyField->MonsterField->height;y++)
			if(MyField->MonsterField->cells[x][y]!=NULL)
			{
				Monster* m=MyField->MonsterField->cells[x][y];
				TmpObj2 = SelectObject(dcBmp,Frames[m->SkinId][m->State]);
				BitBlt(TmpDC,ItemWidth*x,ItemHeight*y,ItemWidth,ItemHeight,dcBmp,0,0,SRCCOPY);
			}
			
	for(int x=0;x<MyField->WallField->width;x++)
		for(int y=0;y<MyField->WallField->height;y++)
			if(MyField->WallField->cells[x][y]!=NULL)
			{
				//Wall* m=MyField->WallField->cells[x][y];
				TmpObj2 = SelectObject(dcBmp,WallBmp);
				BitBlt(TmpDC,ItemWidth*x,ItemHeight*y,ItemWidth,ItemHeight,dcBmp,0,0,SRCCOPY);
			}
	for(int x=0;x<MyField->BonusField->width;x++)
		for(int y=0;y<MyField->BonusField->height;y++)
			if(MyField->BonusField->cells[x][y]!=NULL)
			{
				Bonus* m=MyField->BonusField->cells[x][y];
				TmpObj2 = SelectObject(dcBmp,Potions[m->points-1]);
				BitBlt(TmpDC,ItemWidth*x,ItemHeight*y,ItemWidth,ItemHeight,dcBmp,0,0,SRCCOPY);
			}
	SelectObject(TmpDC,TmpObj2);
	DeleteDC(dcBmp);

	//DeleteObject(hBitmap);
	//hBitmap=TmpBmp;
	SelectObject(TmpDC,TmpObj);
	DeleteDC(TmpDC);

	//dc.SelectObject (&pen);
    // Do we have a valid handle for the loaded image?
    if (TmpBmp)
    {
     // Delete the current bitmap
     if (m_bmpBitmap.DeleteObject())
        m_bmpBitmap.Detach(); // If there was a bitmap, detach it
     // Attach the currently loaded bitmap to the bitmap object
     m_bmpBitmap.Attach(TmpBmp);
    }
    m_bmpBitmap.GetBitmap(&bm);  //Get Bitmap Structure
    Invalidate();
}