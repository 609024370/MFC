// MyListBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "MyListBox.h"


// CMyListBox

IMPLEMENT_DYNAMIC(CMyListBox, CListBox)
CMyListBox::CMyListBox()
{
}

CMyListBox::~CMyListBox()
{
}


BEGIN_MESSAGE_MAP(CMyListBox, CListBox)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CMyListBox ��Ϣ�������


HBRUSH CMyListBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CListBox::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,0,0));
	pDC->SetBkColor(RGB(255,255,0));
	//HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
	return hbr;
}


void CMyListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CListBox::OnLButtonDown(nFlags, point);
}
