// InformDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "InformDlg.h"


// CInformDlg �Ի���

IMPLEMENT_DYNAMIC(CInformDlg, CDialog)
CInformDlg::CInformDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInformDlg::IDD, pParent)
{
}

CInformDlg::~CInformDlg()
{
}

void CInformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(CInformDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CInformDlg ��Ϣ�������

HBRUSH CInformDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
	return br;
	return hbr;
}

BOOL CInformDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
  
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

void CInformDlg::OnTimer(UINT nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(nIDEvent);
	CDialog::OnTimer(nIDEvent);
	CDialog::OnCancel();
}

void CInformDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	 SetTimer(0,2000,NULL);

	// TODO: �ڴ������Ϣ����������
}
