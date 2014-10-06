#pragma once
// PictureBox.cpp : implementation file
   //
#include "stdafx.h"
#include "PictureBox.h"
#include "field.h"
#include "funcs.h"
extern Field* MyField;   
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
	hBitmap = (HBITMAP) ::LoadImage(AfxGetInstanceHandle(),
    "poring3.bmp", IMAGE_BITMAP, 0, 0, 
    LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	BITMAP bm1;
	GetObject( hBitmap, sizeof(BITMAP), &bm1 );
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
	rgn.bottom=(rgn.bottom-rgn.top);
	rgn.right=(rgn.right-rgn.left);
	rgn.left=0;
	rgn.top=0;
	FillRect(TmpDC,&rgn,(HBRUSH) RGB(255,255,255));
	HDC dcBmp=CreateCompatibleDC(TmpDC);
	
	HGDIOBJ TmpObj2;
	for(int x=0;x<MyField->width;x++)
		for(int y=0;y<MyField->height;y++)
			if(MyField->cells[x][y]!=NULL)
			{
				HBITMAP hBitmap2=ReplaceColor(hBitmap,RGB(0,0,0),MyField->TeamColors[MyField->cells[x][y]->command]);
				TmpObj2 = SelectObject(dcBmp,hBitmap2);
				BitBlt(TmpDC,ItemWidth*x,ItemHeight*y,ItemWidth,ItemHeight,dcBmp,0,0,SRCCOPY);
				DeleteObject(hBitmap2);
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