// MainFrm.cpp : implementation of the CMainFrame class   
//   

#include "stdafx.h"   
#include "CurveDrawing.h"   
#include "CurveDrawingView.h"   
#include "MainFrm.h"   

#ifdef _DEBUG   
#define new DEBUG_NEW   
#undef THIS_FILE   
static char THIS_FILE[] = __FILE__;   
#endif   

/////////////////////////////////////////////////////////////////////////////   
// CMainFrame   

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)   

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)   
	//{{AFX_MSG_MAP(CMainFrame)   
	ON_WM_CREATE()   
	ON_WM_SIZE()   
	ON_WM_PAINT()   
	//}}AFX_MSG_MAP   
END_MESSAGE_MAP()   

static UINT indicators[] =   
{   
	ID_SEPARATOR,           // status line indicator   
	ID_INDICATOR_CAPS,   
	ID_INDICATOR_NUM,   
	ID_INDICATOR_SCRL,   
};   

/////////////////////////////////////////////////////////////////////////////   
// CMainFrame construction/destruction   

CMainFrame::CMainFrame()   
{   
	// TODO: add member initialization code here   
	ifrun=FALSE;   
	m_bAutoMenuEnable  = FALSE;   

}   

CMainFrame::~CMainFrame()   
{   
}   

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)   
{   
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)   
		return -1;   

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP   
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||   
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))   
	{   
		TRACE0("Failed to create toolbar\n");   
		return -1;      // fail to create   
	}   

	if (!m_wndStatusBar.Create(this) ||   
		!m_wndStatusBar.SetIndicators(indicators,   
		sizeof(indicators)/sizeof(UINT)))   
	{   
		TRACE0("Failed to create status bar\n");   
		return -1;      // fail to create   
	}   

	// TODO: Delete these three lines if you don't want the toolbar to   
	//  be dockable   
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);   
	EnableDocking(CBRS_ALIGN_ANY);   
	DockControlBar(&m_wndToolBar);   

	return 0;   
}   

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)   
{   
	if( !CFrameWnd::PreCreateWindow(cs) )   
		return FALSE;   
	// TODO: Modify the Window class or styles here by modifying   
	//  the CREATESTRUCT cs   

	return TRUE;   
}   

/////////////////////////////////////////////////////////////////////////////   
// CMainFrame diagnostics   

#ifdef _DEBUG   
void CMainFrame::AssertValid() const   
{   
	CFrameWnd::AssertValid();   
}   

void CMainFrame::Dump(CDumpContext& dc) const   
{   
	CFrameWnd::Dump(dc);   
}   

#endif //_DEBUG   

/////////////////////////////////////////////////////////////////////////////   
// CMainFrame message handlers   




BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)    
{   
	// TODO: Add your specialized code here and/or call the base class   
	GetClientRect(&rc);      
	FrmW   =   rc.right   -   rc.left   +   1;      
	FrmH   =   rc.bottom   -   rc.top   +   1;   
	ifcreatesplitter=m_wndSplitter.CreateStatic(this,   3,   1);      
	m_wndSplitter.CreateView(0,   0,   RUNTIME_CLASS(CCurveDrawingView),      
		CSize(FrmW,   FrmH),   pContext);   
	m_wndSplitter.CreateView(1,   0,   RUNTIME_CLASS(CUpPaneView),      
		CSize(0,   0),   pContext);      
	m_wndSplitter.CreateView(2,   0,   RUNTIME_CLASS(CMyView),      
		CSize(0,   0),   pContext);     
	return   TRUE;     
}   

void CMainFrame::OnSize(UINT nType, int cx, int cy)    
{   
	CFrameWnd::OnSize(nType, cx, cy);   
	//µ±¸Ä±ä´°¿Ú´óÐ¡Ê±£¬ÎÒÃÇ±ØÐëÖØÐÂ°²ÖÃ´°¿ÚµÄÎ»ÖÃ   
	// TODO: Add your message handler code here   
	if(TRUE==ifcreatesplitter)//½¨Á¢ÁË²ð·Ö´°¿Ú²Å¿É°²ÖÃ´°¿ÚÎ»ÖÃ   
	{   
		GetClientRect(&rc);   
		FrmW   =   rc.right   -   rc.left   +   1;      
		FrmH   =   rc.bottom   -   rc.top   +   1;   
		if(FALSE==ifrun)//ÔÚRun×´Ì¬ÏÂ£¬´°¿Ú´óÐ¡¸Ä±ä   
		{   
			m_wndSplitter.SetRowInfo(   0,   FrmH,   10  );      
			m_wndSplitter.SetRowInfo(   1,   0, 10     );   
			m_wndSplitter.SetRowInfo(   2,   0, 10   );   
		}   
		else//ÔÚStop×´Ì¬ÏÂ£¬´°¿Ú´óÐ¡¸Ä±ä   
		{   
			m_wndSplitter.SetRowInfo(   0,   0,   10  );      
			m_wndSplitter.SetRowInfo(   1,   FrmH/2, 10     );   
			m_wndSplitter.SetRowInfo(   2,   FrmH/2, 10   );   
		}   
		m_wndSplitter.RecalcLayout();   
	}   
}   

void CMainFrame::SwitchDisplay()   
{   
	//µÚÒ»ÐÐ´°¿Ú²»ÏÔÊ¾£¬µÚ¶þÈýÐÐ´°¿ÚÏÔÊ¾   
	m_wndSplitter.SetRowInfo(   0,   0,   10  );      
	m_wndSplitter.SetRowInfo(   1,   FrmH/2, 10     );   
	m_wndSplitter.SetRowInfo(   2,   FrmH/2, 10   );   
	m_wndSplitter.RecalcLayout();   
	CUpPaneView* pView=(CUpPaneView*)m_wndSplitter.GetPane(1,0);//ÓÃGetPane»ñµÃCUpPaneView¶ÔÏóÖ¸Õë   
	pView->AddList();   
	ifrun=TRUE;   
}   

void CMainFrame::SwitchDesign()   
{   
	m_wndSplitter.SetRowInfo(0,FrmH,10);      
	m_wndSplitter.SetRowInfo(1,0,10);   
	m_wndSplitter.SetRowInfo(2,0,10);   
	m_wndSplitter.RecalcLayout();   
	ifrun=FALSE;   
}   



void CMainFrame::OnPaint()    
{   
	CPaintDC dc(this); // device context for painting   

	// TODO: Add your message handler code here   

	// Do not call CFrameWnd::OnPaint() for painting messages   
}   