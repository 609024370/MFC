// SendToAllDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "SendToAllDlg.h"


// CSendToAllDlg �Ի���

IMPLEMENT_DYNAMIC(CSendToAllDlg, CDialog)
CSendToAllDlg::CSendToAllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendToAllDlg::IDD, pParent)
	, m_str(_T(""))
{
}

CSendToAllDlg::~CSendToAllDlg()
{
}

void CSendToAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RICHEDIT21, m_str);
	DDX_Control(pDX, IDOK, m_bt1);
	DDX_Control(pDX, IDCANCEL, m_bt2);
}


BEGIN_MESSAGE_MAP(CSendToAllDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSendToAllDlg ��Ϣ�������

BOOL CSendToAllDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText("��ϢȺ��");
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

HBRUSH CSendToAllDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	 pDC->SetBkMode(TRANSPARENT);
	if (nCtlColor != CTLCOLOR_LISTBOX &&  nCtlColor !=  CTLCOLOR_EDIT)
	{
		HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
		return br;
	}

	return hbr;
}
