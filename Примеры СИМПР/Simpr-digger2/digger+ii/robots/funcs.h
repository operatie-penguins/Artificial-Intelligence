#pragma once

int true_rand(int max);
bool IfPossible(int possibility);

BOOL LoadBitmapFromBMPFile( LPTSTR szFileName, HBITMAP *phBitmap,
   HPALETTE *phPalette );
HBITMAP ReplaceColor(HBITMAP hBmp,COLORREF cOldColor,COLORREF cNewColor,HDC hBmpDC=NULL);
POINT AddPoints(POINT point1,POINT point2);
bool CmpPoints(POINT point1,POINT point2);