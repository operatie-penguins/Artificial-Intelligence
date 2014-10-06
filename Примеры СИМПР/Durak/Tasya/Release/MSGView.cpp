// MSGView.cpp : implementation of the CMSGView class
//

#include "stdafx.h"
#include "MSG.h"

#include "MSGDoc.h"
#include "MSGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSGView

IMPLEMENT_DYNCREATE(CMSGView, CView)

BEGIN_MESSAGE_MAP(CMSGView, CView)
	//{{AFX_MSG_MAP(CMSGView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSGView construction/destruction

CMSGView::CMSGView()
{
	// TODO: add construction code here

}

CMSGView::~CMSGView()
{
}

BOOL CMSGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMSGView drawing

void CMSGView::OnDraw(CDC* pDC)
{
	CMSGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMSGView printing

BOOL CMSGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMSGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMSGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMSGView diagnostics

#ifdef _DEBUG
void CMSGView::AssertValid() const
{
	CView::AssertValid();
}

void CMSGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMSGDoc* CMSGView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSGDoc)));
	return (CMSGDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSGView message handlers
