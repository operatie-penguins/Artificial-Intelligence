// MSG.h : main header file for the MSG application
//

#if !defined(AFX_MSG_H__3951F1EC_31F4_4821_8823_72B9BF0AA127__INCLUDED_)
#define AFX_MSG_H__3951F1EC_31F4_4821_8823_72B9BF0AA127__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMSGApp:
// See MSG.cpp for the implementation of this class
//

class CMSGApp : public CWinApp
{
public:
	CMSGApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSGApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMSGApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSG_H__3951F1EC_31F4_4821_8823_72B9BF0AA127__INCLUDED_)
