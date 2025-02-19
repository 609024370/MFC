// DlgColor.cpp : implementation file
//

#include "stdafx.h"
#include "CListCtrlExDemo.h"
#include "DlgColor.h"


// CDlgColor dialog

IMPLEMENT_DYNAMIC(CDlgColor, CDialog)

CDlgColor::CDlgColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgColor::IDD, pParent)
	, m_nColor(0)
{

}

CDlgColor::~CDlgColor()
{
}

void CDlgColor::DoDataExchange(CDataExchange* pDX)
{
	DDX_Radio(pDX, IDC_RADIO1, m_nColor);
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgColor, CDialog)
END_MESSAGE_MAP()


// CDlgColor message handlers

BOOL CDlgColor::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgColor::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == VK_TAB && (GetKeyState(VK_CONTROL)>>8 != -1))
		{
			return FALSE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
