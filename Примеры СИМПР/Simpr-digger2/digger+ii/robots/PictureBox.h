   #pragma once
   
   // CPictureBox
   
   class CPictureBox : public CStatic
   {
    DECLARE_DYNAMIC(CPictureBox)
   
   public:
    CPictureBox();
    virtual ~CPictureBox();
    void FreeSrc();
    void SetBitmap(CString strBitmap);
	void Init();
	void DrawField();
	int FieldWidth,FieldHeight;
	static const int monsters=5;
    static const int states=9;
	static const int potions=9;
	static const int walls=9;
   protected:
    DECLARE_MESSAGE_MAP()
    void ShowBitmap(CPaintDC *pDC);
    CString m_sBitmap;
    CBitmap m_bmpBitmap;
    BITMAP bm;
	long ItemWidth,ItemHeight;
	HBITMAP** Frames;
	HBITMAP* Potions;
	HBITMAP WallBmp;
	HDC dc;
   public:
    afx_msg void OnPaint();
   };