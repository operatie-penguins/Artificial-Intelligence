   #pragma once
   
   // CPictureBox
   
   class CPictureBox : public CStatic
   {
    DECLARE_DYNAMIC(CPictureBox)
   
   public:
    CPictureBox();
    virtual ~CPictureBox();
    void SetBitmap(CString strBitmap);
	void Init();
	void DrawField();
	int FieldWidth,FieldHeight;
   
   protected:
    DECLARE_MESSAGE_MAP()
    void ShowBitmap(CPaintDC *pDC);
    CString m_sBitmap;
    CBitmap m_bmpBitmap;
    BITMAP bm;
	long ItemWidth,ItemHeight;
	HBITMAP hBitmap;
	HDC dc;
   public:
    afx_msg void OnPaint();
   };