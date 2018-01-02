// UpPaneView.cpp : implementation file   
//   

#include "stdafx.h"   
#include "CurveDrawing.h"   
#include "UpPaneView.h"   

#ifdef _DEBUG   
#define new DEBUG_NEW   
#undef THIS_FILE   
static char THIS_FILE[] = __FILE__;   
#endif   

/////////////////////////////////////////////////////////////////////////////   
// CUpPaneView   

IMPLEMENT_DYNCREATE(CUpPaneView, CListView)   

CUpPaneView::CUpPaneView()   
{   
}   

CUpPaneView::~CUpPaneView()   
{   
}   


BEGIN_MESSAGE_MAP(CUpPaneView, CListView)   
	//{{AFX_MSG_MAP(CUpPaneView)   
	// NOTE - the ClassWizard will add and remove mapping macros here.   
	//}}AFX_MSG_MAP   
END_MESSAGE_MAP()   

/////////////////////////////////////////////////////////////////////////////   
// CUpPaneView drawing   

void CUpPaneView::OnDraw(CDC* pDC)   
{   
	CDocument* pDoc = GetDocument();   
	// TODO: add draw code here   
}   

/////////////////////////////////////////////////////////////////////////////   
// CUpPaneView diagnostics   

#ifdef _DEBUG   
void CUpPaneView::AssertValid() const   
{   
	CListView::AssertValid();   
}   

void CUpPaneView::Dump(CDumpContext& dc) const   
{   
	CListView::Dump(dc);   
}   
#endif //_DEBUG   

/////////////////////////////////////////////////////////////////////////////   
// CUpPaneView message handlers   

void CUpPaneView::OnInitialUpdate()    
{   
	CListView::OnInitialUpdate();   

	// TODO: Add your specialized code here and/or call the base class   

}   

//����ʼ��list   
void CUpPaneView::AddList()   
{   
	CCurveDrawingDoc* pDoc=(CCurveDrawingDoc*)GetDocument();   
	CListCtrl& ctl=GetListCtrl();   
	// TODO: Add your specialized code here and/or call the base class     
	//�����б�ؼ����   
	DWORD dwStyle=::GetWindowLong(m_hWnd,GWL_STYLE);   
	dwStyle|=LVS_REPORT|LVS_SHOWSELALWAYS|LVS_EDITLABELS;      
	::SetWindowLong(m_hWnd,GWL_STYLE,dwStyle);   
	dwStyle=ctl.GetExtendedStyle();   
	dwStyle|= LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT;   
	//������չ���   
	ctl.SetExtendedStyle(dwStyle);     
	//�б�ؼ�ͷ����   
	LV_COLUMN lvcolumn;   
	CRect rect;   
	GetWindowRect(&rect);   
	TCHAR tittle[3][10] = {_T("����"),_T("��λ"),_T("��ַ")};   
	//����б�ؼ�ͷ   
	for(int i=0;i<3;i++)   
	{   
		lvcolumn.mask =LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT    
			|LVCF_WIDTH|LVCF_ORDER;   
		lvcolumn.fmt = LVCFMT_LEFT;   
		lvcolumn.pszText = tittle[i];   
		lvcolumn.iSubItem = i;   
		lvcolumn.iOrder = i;   
		lvcolumn.cx = rect.Height()/3;   
		GetListCtrl().InsertColumn(i, &lvcolumn);   
	}   
}   