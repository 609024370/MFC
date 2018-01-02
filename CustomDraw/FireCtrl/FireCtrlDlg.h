//////////////////////////////////////////////////////////////////////////////
//������CFireCtrlDlg
//���ܣ�����Ч��ʾ��ʵ�ֶԻ���
//���ߣ��쾰��(jingzhou_xu@163.net)
//��֯��δ��������(Future Studio)
//���ڣ�2001.12.1
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_FIRECTRLDLG_H__3466C315_3515_42FC_9080_F4D78A4E0338__INCLUDED_)
#define AFX_FIRECTRLDLG_H__3466C315_3515_42FC_9080_F4D78A4E0338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WBButton.h"				//����λͼ��ť��
#include "HyperLink.h"				//���볬������
#include "PictureEx.h"				//����GIF��̬ͼ����ʾ
#include "FireWnd.h"				//�������Ч���ؼ���
/////////////////////////////////////////////////////////////////////////////
// CFireCtrlDlg dialog

class CFireCtrlDlg : public CDialog
{
// Construction
public:
	CFireCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFireCtrlDlg)
	enum { IDD = IDD_FIRECTRL_DIALOG };
	CWBButton	m_About;			//λͼ��ť
	CWBButton	m_OK;				//λͼ��ť
	CFireWnd	m_FireCtrl;         //����Ч���ؼ� 
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFireCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFireCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRECTRLDLG_H__3466C315_3515_42FC_9080_F4D78A4E0338__INCLUDED_)
