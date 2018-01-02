// MyView.cpp : implementation file   
//   

#include "stdafx.h"   
#include "CurveDrawing.h"   
#include "MyView.h"   
#include "MainFrm.h"   
#ifdef _DEBUG   
#define new DEBUG_NEW   
#undef THIS_FILE   
static char THIS_FILE[] = __FILE__;   
#endif   

/////////////////////////////////////////////////////////////////////////////   
// CMyView   

IMPLEMENT_DYNCREATE(CMyView, CView)   

CMyView::CMyView()   
{   

}   

CMyView::~CMyView()   
{   
}   


BEGIN_MESSAGE_MAP(CMyView, CView)   
	//{{AFX_MSG_MAP(CMyView)   
	ON_WM_ERASEBKGND()   
	//}}AFX_MSG_MAP   
END_MESSAGE_MAP()   

/////////////////////////////////////////////////////////////////////////////   
// CMyView drawing   

void CMyView::OnDraw(CDC* pDC)   
{   
	CCurveDrawingDoc* pDoc = (CCurveDrawingDoc*)GetDocument();   
	// TODO: add draw code here   
	CMainFrame* pMainFrame=(CMainFrame*)GetParentFrame();   
	GetClientRect(m_plot.m_ctlRect);//�õ�CMyView���ֵ���ͼ�ߴ磬����m_ctlRect   

	//��ͼ   

	//������CCurveDrawingView::OnTime�г�����OnDraw��������ִ��DrawCurve��������ͼ   
	if(TRUE==((CCurveDrawingDoc*)GetDocument())->ifdrawcurve)   
	{   
		m_plot.DrawCurve(pDC);   
		pDoc->ifdrawcurve=FALSE;//����־��0���´ζ�ʱʱ�䵽��CCurveDrawingView::OnTime����1     
	}   

}   

/////////////////////////////////////////////////////////////////////////////   
// CMyView diagnostics   

#ifdef _DEBUG   
void CMyView::AssertValid() const   
{   
	CView::AssertValid();   
}   

void CMyView::Dump(CDumpContext& dc) const   
{   
	CView::Dump(dc);   

}   
#endif //_DEBUG   

/////////////////////////////////////////////////////////////////////////////   
// CMyView message handlers   
//�����������������㼼��ʹ�������ػ��ͼ�ο���������˸   
//1.������OnEraseBkgnd����,����������ÿ���ػ�֮ǰ�ÿհ�λͼ���������ĺ���,��������ÿ���������Զ����   
//λͼ����Ϊ����   
//2.����ʹ����˫����Ľṹ,���Ȱѱ���ͼ�λ������ڴ���,���ƺ���һ����ʾ��ȥ   
BOOL CMyView::OnEraseBkgnd(CDC* pDC)    
{   
	// TODO: Add your message handler code here and/or call default   
	CDC MemDC; //���ȶ���һ����ʾ�豸����   
	CBitmap MemBitmap;//����һ��λͼ����   
	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸   
	MemDC.CreateCompatibleDC(NULL);   
	//��ʱ�����ܻ�ͼ����Ϊû�еط���   
	//���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С   
	MemBitmap.CreateCompatibleBitmap(pDC,m_plot.m_ctlRect.Width(),m_plot.m_ctlRect.Height());   
	//��λͼѡ�뵽�ڴ���ʾ�豸��   
	//ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��   
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);   
	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����   
	//��Ҳ�������Լ�Ӧ���õ���ɫ   
	m_plot.DrawBasic(&MemDC);   
	m_plot.DrawLegendShadow(&MemDC);   
	m_plot.DrawXAxisGrid(&MemDC);   
	m_plot.DrawYAxisGrid(&MemDC);   
	m_plot.DrawLegend(&MemDC);   
	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ   
	pDC->BitBlt(0,0,m_plot.m_ctlRect.Width(),m_plot.m_ctlRect.Height(),&MemDC,0,0,SRCCOPY);   
	//��ͼ��ɺ������   
	MemBitmap.DeleteObject();   
	MemDC.DeleteDC();   
	return TRUE;   
}   