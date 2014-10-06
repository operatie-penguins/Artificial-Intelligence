// robotsDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "robot.h"
#include "PictureBox.h"


// CrobotsDlg dialog
class CrobotsDlg : public CDialog
{
// Construction
public:
	CrobotsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ROBOTS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT  OnSimpr(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton start;
	CButton stop;
	afx_msg void OnBnClickedButton2();
	void DrawRobot(robot* robot);
	CPictureBox Pic;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedOk();
	CStatic RateText;
	afx_msg void OnStnClickedPicture();
};
