#pragma once
#include "afxwin.h"
#include "WinXPButtonST.h"
// CSendToAllDlg �Ի���

class CSendToAllDlg : public CDialog
{
	DECLARE_DYNAMIC(CSendToAllDlg)

public:
	CSendToAllDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSendToAllDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_str;
	CWinXPButtonST m_bt1;
	CWinXPButtonST m_bt2;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
