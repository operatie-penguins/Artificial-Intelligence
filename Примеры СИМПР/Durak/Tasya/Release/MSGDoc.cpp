// MSGDoc.cpp : implementation of the CMSGDoc class
//

#include "stdafx.h"
#include "MSG.h"

#include "MSGDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSGDoc

IMPLEMENT_DYNCREATE(CMSGDoc, CDocument)

BEGIN_MESSAGE_MAP(CMSGDoc, CDocument)
	//{{AFX_MSG_MAP(CMSGDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSGDoc construction/destruction

CMSGDoc::CMSGDoc()
{
	// TODO: add one-time construction code here

}

CMSGDoc::~CMSGDoc()
{
}

BOOL CMSGDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMSGDoc serialization

void CMSGDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMSGDoc diagnostics

#ifdef _DEBUG
void CMSGDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMSGDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSGDoc commands
