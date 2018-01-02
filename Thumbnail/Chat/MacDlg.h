#pragma once
#include "afxwin.h"
#include "WinXPButtonST.h"
#include "afxcmn.h"
#include "MacSocket.h"

// CMacDlg �Ի���

class CMacDlg : public CDialog
{
	DECLARE_DYNAMIC(CMacDlg)

public:
	CMacDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMacDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CWinXPButtonST m_begin;
	CWinXPButtonST m_end;
	CMacSocket m_UDPSocket;
	CString m_strIP;
	virtual BOOL OnInitDialog();
	CIPAddressCtrl m_ipctrl1;
	CIPAddressCtrl m_ipctrl2;
	CListCtrl m_listctrl;
	CProgressCtrl m_proctrl;
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBegin();
	afx_msg void OnEndScan();
	CSpinButtonCtrl m_spin;
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
	void OnReceive(void);
};
