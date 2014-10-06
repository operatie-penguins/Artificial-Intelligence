#pragma once

int true_rand(int max);


BOOL LoadBitmapFromBMPFile( LPTSTR szFileName, HBITMAP *phBitmap,
   HPALETTE *phPalette );
HBITMAP ReplaceColor(HBITMAP hBmp,COLORREF cOldColor,COLORREF cNewColor,HDC hBmpDC=NULL);