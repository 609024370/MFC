#pragma once
#include "afxwin.h"
#include "WinXPButtonST.h"

// CInformDlg �Ի���

class CInformDlg : public CDialog
{
	DECLARE_DYNAMIC(CInformDlg)

public:
	CInformDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInformDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
public:
	CString info;

	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
