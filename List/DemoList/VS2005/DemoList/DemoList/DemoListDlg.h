// DemoListDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "ListCtrlCl.h"

// CDemoListDlg �Ի���
class CDemoListDlg : public CDialog
{
// ����
public:
	CDemoListDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DEMOLIST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrlCl m_ListCtrl;
};
