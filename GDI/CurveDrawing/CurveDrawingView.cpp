// CurveDrawingView.cpp : implementation of the CCurveDrawingView class
//

#include "stdafx.h"
#include "CurveDrawing.h"
#include "SPlitterWndEx.h"
#include "CurveDrawingDoc.h"
#include "CurveDrawingView.h"
#include "UpPaneView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveDrawingView

IMPLEMENT_DYNCREATE(CCurveDrawingView, CView)

BEGIN_MESSAGE_MAP(CCurveDrawingView, CView)
	//{{AFX_MSG_MAP(CCurveDrawingView)
	ON_WM_TIMER()
	ON_COMMAND(IDM_RUN, OnRun)
	ON_COMMAND(IDM_STOP, OnStop)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveDrawingView construction/destruction

CCurveDrawingView::CCurveDrawingView()
{
	// TODO: add construction code here
	
}

CCurveDrawingView::~CCurveDrawingView()
{
}

BOOL CCurveDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCurveDrawingView drawing

void CCurveDrawingView::OnDraw(CDC* pDC)
{
	CCurveDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCurveDrawingView printing

BOOL CCurveDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCurveDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCurveDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCurveDrawingView diagnostics

#ifdef _DEBUG
void CCurveDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void CCurveDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCurveDrawingDoc* CCurveDrawingView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCurveDrawingDoc)));
	return (CCurveDrawingDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurveDrawingView message handlers
void CCurveDrawingView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}

void CCurveDrawingView::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	HMENU hMenu=::GetMenu(m_hWnd);
	EnableMenuItem(hMenu, IDM_STOP, MF_BYCOMMAND | MF_GRAYED);
    EnableMenuItem(hMenu, IDM_RUN, MF_BYCOMMAND | MF_ENABLED);
	CView::CalcWindowRect(lpClientRect, nAdjustType);
}

void CCurveDrawingView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pMainFrame=(CMainFrame*)GetParentFrame();
	//�Ƿ�������ݵ㣬����CMyView::OnDraw(CDC* pDC)�е�DrawCurve()�����Ƿ��ܱ�����
	//��������OnDraw������ִ�в������������UpdateAllViews��������������OnTime�����д���
	//OnDraw����ʱ����Ҫִ���ػ�����ͼ�Ĳ���DrawCurve���������������ڴ˴���ifdrawcurve
	//��־��λ
	((CCurveDrawingDoc*)GetDocument())->ifdrawcurve=TRUE;
	((CCurveDrawingDoc*)GetDocument())->UpdateAllViews(NULL);//��������View��OnDraw������ִ��
	CView::OnTimer(nIDEvent);
}

//����ͼ��������
void CCurveDrawingView::OnRun() 
{
	// TODO: Add your command handler code here
	CMainFrame* pMainFrame=(CMainFrame*)GetParentFrame();
	pMainFrame->SwitchDisplay();//���Run��ת��Ϊ������ʾ����
	SetTimer(1,1000,NULL);//�趨����ͼ����ʱ��
}

void CCurveDrawingView::OnStop() 
{
	// TODO: Add your command handler code here
	CMainFrame* pMainFrame=(CMainFrame*)GetParentFrame();
	pMainFrame->SwitchDesign();
}
