// SetNetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "SetNetDlg.h"


// CSetNetDlg �Ի���

IMPLEMENT_DYNAMIC(CSetNetDlg, CDialog)
CSetNetDlg::CSetNetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetNetDlg::IDD, pParent)
	, m_port(0)
{
	checked_server = true;
}

CSetNetDlg::~CSetNetDlg()
{
}

void CSetNetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipadr);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDOK, bt1);
	DDX_Control(pDX, IDCANCEL, bt2);
	DDX_Control(pDX, IDC_STATIC6, m_static);
}


BEGIN_MESSAGE_MAP(CSetNetDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
END_MESSAGE_MAP()


// CSetNetDlg ��Ϣ�������

HBRUSH CSetNetDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetBkMode(TRANSPARENT);
	if ( nCtlColor != CTLCOLOR_EDIT) 
		hbr = ::CreateSolidBrush(RGB(128,128,200));
	return hbr;
	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CSetNetDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ( ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() == BST_CHECKED )
		checked_server = true;
	else
		checked_server = false;

	BYTE ipadr[4];
	m_ipadr.GetAddress(ipadr[0],ipadr[1],ipadr[2],ipadr[3]);
	ip.Format("%d.%d.%d.%d",ipadr[0],ipadr[1],ipadr[2],ipadr[3]);
	CString strport;
	m_edit.GetWindowText(strport);
	char * buf = strport.GetBuffer();
	 m_port = atoi(buf);
	OnOK();
}

void CSetNetDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	checked_server = false ;
	OnCancel();
}

BOOL CSetNetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//m_ration1.SetCheck( BST_CHECKED );
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck( BST_CHECKED );
	m_ipadr.SetAddress(192,168,0,168);
	m_edit.SetWindowText("5000");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

void CSetNetDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ipadr.EnableWindow(true);
	m_ipadr.ShowWindow(SW_SHOW);
	m_static.ShowWindow(SW_SHOW);
}

void CSetNetDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ipadr.EnableWindow(true);
	m_ipadr.ShowWindow(SW_HIDE);
	m_static.ShowWindow(SW_HIDE);
}
