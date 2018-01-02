// SplitterDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_SPLITTERDLG_H__4EEC3C5F_57EC_4FDD_B7DE_7161B9445A7B__INCLUDED_)
#define AFX_SPLITTERDLG_H__4EEC3C5F_57EC_4FDD_B7DE_7161B9445A7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ControlSplitter.h"
/////////////////////////////////////////////////////////////////////////////
// CSplitterDlg �_�C�A���O

class CSplitterDlg : public CDialog
{
// �\�z
public:
	CSplitterDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSplitterDlg)
	enum { IDD = IDD_SPLITTER_DIALOG };
	CControlSplitter	m_splitter3;
	CControlSplitter	m_splitter2;
	CControlSplitter	m_splitter;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSplitterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSplitterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SPLITTERDLG_H__4EEC3C5F_57EC_4FDD_B7DE_7161B9445A7B__INCLUDED_)
