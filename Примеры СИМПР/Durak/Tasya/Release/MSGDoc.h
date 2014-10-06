// MSGDoc.h : interface of the CMSGDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGDOC_H__04020180_BDA5_466F_883A_94F9426BA400__INCLUDED_)
#define AFX_MSGDOC_H__04020180_BDA5_466F_883A_94F9426BA400__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMSGDoc : public CDocument
{
protected: // create from serialization only
	CMSGDoc();
	DECLARE_DYNCREATE(CMSGDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSGDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMSGDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMSGDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGDOC_H__04020180_BDA5_466F_883A_94F9426BA400__INCLUDED_)
