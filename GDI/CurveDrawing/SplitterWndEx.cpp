// SplitterWndEx.cpp : implementation file   
//   

#include "stdafx.h"   
#include "CurveDrawing.h"   
#include "SplitterWndEx.h"   

#ifdef _DEBUG   
#define new DEBUG_NEW   
#undef THIS_FILE   
static char THIS_FILE[] = __FILE__;   
#endif   

/////////////////////////////////////////////////////////////////////////////   
// CSplitterWndEx   

CSplitterWndEx::CSplitterWndEx()   
{   
	m_cxSplitterGap = m_cySplitterGap = 1;//���÷ָ�򲻿ɼ��������С   
	m_cxSplitter=m_cySplitter=1;   
	//m_cxBorder = m_cyBorder = 0;   
}   

CSplitterWndEx::~CSplitterWndEx()   
{   
}   


BEGIN_MESSAGE_MAP(CSplitterWndEx, CSplitterWnd)   
	//{{AFX_MSG_MAP(CSplitterWndEx)   
	ON_WM_LBUTTONDOWN()   
	//}}AFX_MSG_MAP   
END_MESSAGE_MAP()   


/////////////////////////////////////////////////////////////////////////////   
// CSplitterWndEx message handlers   

void CSplitterWndEx::OnLButtonDown(UINT nFlags, CPoint point)    
{   
	// TODO: Add your message handler code here and/or call default   
	//������CSplitterWndEx::OnLButtonDown(nFlags, point);��ΪCWnd::OnLButtonDown(nFlags, point);�����Ͳ�����Ӧ�Էָ����ƶ��ˡ�   
	CWnd::OnLButtonDown(nFlags, point);   
}   