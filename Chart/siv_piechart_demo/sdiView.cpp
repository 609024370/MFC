// sdiView.cpp : implementation of the CSdiView class
//

#include "stdafx.h"
#include "sdi.h"

#include "sdiDoc.h"
#include "sdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSdiView

IMPLEMENT_DYNCREATE(CSdiView, CView)

BEGIN_MESSAGE_MAP(CSdiView, CView)
	//{{AFX_MSG_MAP(CSdiView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSdiView construction/destruction

CSdiView::CSdiView()
{
	// TODO: add construction code here

}

CSdiView::~CSdiView()
{
}

BOOL CSdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSdiView drawing

void CSdiView::OnDraw(CDC* pDC)
{
	CSdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	CRect rect;
	GetClientRect( &rect );

	CPoint center;
	center.x = rect.left + 120;
	center.y = rect.bottom / 3;

	// this one draws the left pie - with title, legend on the right, and no fill
	pDoc->m_chart.SetTextColor( PIECOLOR_GRAY );
	pDoc->m_chart.Draw2D( (CPaintDC*)pDC, center, 100, TRUE, PIELEGEND_RIGHT, FALSE );

	center.x = rect.right - 90;
	pDoc->m_chart.SetTextColor( PIECOLOR_RED );
	// the pie on the right, red letters and the legend below...
	pDoc->m_chart.Draw2D( (CPaintDC*)pDC, center, 75, TRUE, PIELEGEND_BELOW );
}

/////////////////////////////////////////////////////////////////////////////
// CSdiView printing

BOOL CSdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSdiView diagnostics

#ifdef _DEBUG
void CSdiView::AssertValid() const
{
	CView::AssertValid();
}

void CSdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSdiDoc* CSdiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSdiDoc)));
	return (CSdiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSdiView message handlers
