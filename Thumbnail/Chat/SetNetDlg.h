#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "WinXPButtonST.h"

// CSetNetDlg �Ի���

class CSetNetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetNetDlg)

public:
	CSetNetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetNetDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CIPAddressCtrl m_ipadr;
	CString ip;
	int m_port;
	bool checked_server;
	virtual BOOL OnInitDialog();
	CEdit m_edit;
	CWinXPButtonST bt1;
	CWinXPButtonST bt2;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	CStatic m_static;
};
