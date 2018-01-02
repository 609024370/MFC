// ChoiceKindDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "ChoiceKindDlg.h"


// CChoiceKindDlg �Ի���

IMPLEMENT_DYNAMIC(CChoiceKindDlg, CDialog)
CChoiceKindDlg::CChoiceKindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChoiceKindDlg::IDD, pParent)
{
	machine = false;
}

CChoiceKindDlg::~CChoiceKindDlg()
{
}

void CChoiceKindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_ratio);
	DDX_Control(pDX, IDOK, bt1);
}


BEGIN_MESSAGE_MAP(CChoiceKindDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChoiceKindDlg ��Ϣ�������

void CChoiceKindDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ( ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck() == BST_CHECKED )
	{
		machine = true;
	}
	OnOK();
}

BOOL CChoiceKindDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(BST_CHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

HBRUSH CChoiceKindDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	pDC->SetBkMode(TRANSPARENT);
	hbr = ::CreateSolidBrush(RGB(128,128,200));
	
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
