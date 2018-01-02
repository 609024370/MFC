// MyListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "MyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)
CMyListCtrl::CMyListCtrl()
{
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_WM_CTLCOLOR()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CMyListCtrl ��Ϣ�������


HBRUSH CMyListCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CListCtrl::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
		return br;
	//return hbr;
}

void CMyListCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
  if (GetSelectedCount() > 0)
  {
	if (point.x == -1 && point.y == -1)
		{
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU1));
		

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();
		::GetCursorPos(&point);

		pPopup->TrackPopupMenu( TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
  }
	//CListCtrl::OnRButtonDown(nFlags, point);
}
