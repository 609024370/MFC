#pragma once
#include "afxwin.h"
#include "WinXPButtonST.h"

// CChoiceKindDlg �Ի���

class CChoiceKindDlg : public CDialog
{
	DECLARE_DYNAMIC(CChoiceKindDlg)

public:
	CChoiceKindDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChoiceKindDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	bool machine;
	afx_msg void OnBnClickedOk();
	CWinXPButtonST m_ratio;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CWinXPButtonST bt1;
};
