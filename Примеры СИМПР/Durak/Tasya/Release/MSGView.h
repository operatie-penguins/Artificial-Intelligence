// MSGView.h : interface of the CMSGView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGVIEW_H__E43E5939_A5A8_42CD_B73D_ECC6042B9AF4__INCLUDED_)
#define AFX_MSGVIEW_H__E43E5939_A5A8_42CD_B73D_ECC6042B9AF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMSGView : public CView
{
protected: // create from serialization only
	CMSGView();
	DECLARE_DYNCREATE(CMSGView)

// Attributes
public:
	CMSGDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSGView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMSGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMSGView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MSGView.cpp
inline CMSGDoc* CMSGView::GetDocument()
   { return (CMSGDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGVIEW_H__E43E5939_A5A8_42CD_B73D_ECC6042B9AF4__INCLUDED_)
