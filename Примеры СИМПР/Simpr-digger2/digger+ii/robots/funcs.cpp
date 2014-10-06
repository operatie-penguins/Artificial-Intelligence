#include "StdAfx.h"
#include <limits.h>
#include "funcs.h"
POINT AddPoints(POINT point1,POINT point2)
{
	POINT res;
	res.x=point1.x+point2.x;
	res.y=point1.y+point2.y;
	return res;
}
bool CmpPoints(POINT point1,POINT point2)
{
	if((point1.x==point2.x)&&(point1.y==point2.y))
		return 1;
	return 0;
}
bool IfPossible(int possibility)
{
	if(true_rand(100)<=possibility)
		return 1;
	return 0;
}
int true_rand(int max)
{
    unsigned int    number;
    errno_t         err;

	err = rand_s( &number );
    if (err != 0)
    {
        MessageBox(NULL,"The rand_s function failed!\n","ERROR",MB_OK);
    }
    return (double) number /(double) UINT_MAX * (max+1) ;

}





#define COLORREF2RGB(Color) (Color & 0xff00) | ((Color >> 16) & 0xff) \
                                 | ((Color << 16) & 0xff0000)

//-------------------------------------------------------------------------------

// ReplaceColor

//

// Author    : Dimitri Rochette drochette@ltezone.net

// Specials Thanks to Joe Woodbury for his comments and code corrections

//

// Includes  : Only <windows.h>

//

// hBmp	     : Source Bitmap

// cOldColor : Color to replace in hBmp

// cNewColor : Color used for replacement

// hBmpDC    : DC of hBmp ( default NULL ) could be NULL if hBmp is not selected

//

// Retcode   : HBITMAP of the modified bitmap or NULL for errors

//

//-------------------------------------------------------------------------------

HBITMAP ReplaceColor(HBITMAP hBmp,COLORREF cOldColor,COLORREF cNewColor,HDC hBmpDC)
{
    HBITMAP RetBmp=NULL;
    if (hBmp)
    {	
        HDC BufferDC=CreateCompatibleDC(NULL);	// DC for Source Bitmap

	if (BufferDC)
	{
	    HBITMAP hTmpBitmap = (HBITMAP) NULL;
	    if (hBmpDC)
	        if (hBmp == (HBITMAP)GetCurrentObject(hBmpDC, OBJ_BITMAP))
		{
		    hTmpBitmap = CreateBitmap(1, 1, 1, 1, NULL);
		    SelectObject(hBmpDC, hTmpBitmap);
		}
	    
            HGDIOBJ PreviousBufferObject=SelectObject(BufferDC,hBmp);
	    // here BufferDC contains the bitmap

			
	    HDC DirectDC=CreateCompatibleDC(NULL); // DC for working

	    if (DirectDC)
	    {
		// Get bitmap size

		BITMAP bm;
		GetObject(hBmp, sizeof(bm), &bm);
				
		// create a BITMAPINFO with minimal initilisation 

                // for the CreateDIBSection

		BITMAPINFO RGB32BitsBITMAPINFO; 
		ZeroMemory(&RGB32BitsBITMAPINFO,sizeof(BITMAPINFO));
		RGB32BitsBITMAPINFO.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		RGB32BitsBITMAPINFO.bmiHeader.biWidth=bm.bmWidth;
		RGB32BitsBITMAPINFO.bmiHeader.biHeight=bm.bmHeight;
		RGB32BitsBITMAPINFO.bmiHeader.biPlanes=1;
		RGB32BitsBITMAPINFO.bmiHeader.biBitCount=32;

                // pointer used for direct Bitmap pixels access

		UINT * ptPixels;	

		HBITMAP DirectBitmap = CreateDIBSection(DirectDC, 
                                       (BITMAPINFO *)&RGB32BitsBITMAPINFO, 
                                       DIB_RGB_COLORS,
                                       (void **)&ptPixels, 
                                       NULL, 0);
		if (DirectBitmap)
		{
		    // here DirectBitmap!=NULL so ptPixels!=NULL no need to test

		    HGDIOBJ PreviousObject=SelectObject(DirectDC, DirectBitmap);
		    BitBlt(DirectDC,0,0,
                           bm.bmWidth,bm.bmHeight,
                           BufferDC,0,0,SRCCOPY);
	
		    // here the DirectDC contains the bitmap


		    // Convert COLORREF to RGB (Invert RED and BLUE)

		    cOldColor=COLORREF2RGB(cOldColor);
		    cNewColor=COLORREF2RGB(cNewColor);

		    // After all the inits we can do the job : Replace Color

		    for (int i=((bm.bmWidth*bm.bmHeight)-1);i>=0;i--)
		    {
			if (ptPixels[i]==cOldColor)
				ptPixels[i]=cNewColor;
		    }
			COLORREF k=bm.bmWidth*bm.bmHeight-ptPixels[18*40+20];
		    // little clean up

		    // Don't delete the result of SelectObject because it's 

                    // our modified bitmap (DirectBitmap)

		    SelectObject(DirectDC,PreviousObject);
					
		    // finish

		    RetBmp=DirectBitmap;
		}
		// clean up

		DeleteDC(DirectDC);
	    }			
	    if (hTmpBitmap)
	    {
		SelectObject(hBmpDC, hBmp);
		DeleteObject(hTmpBitmap);
	    }
	    SelectObject(BufferDC,PreviousBufferObject);
	    // BufferDC is now useless

	    DeleteDC(BufferDC);
	}
    }
    return RetBmp;
}