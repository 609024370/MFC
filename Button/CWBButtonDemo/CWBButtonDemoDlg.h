// CWBButtonDemoDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_CWBBUTTONDEMODLG_H__518122C7_358F_11D4_8F4F_00402656D980__INCLUDED_)
#define AFX_CWBBUTTONDEMODLG_H__518122C7_358F_11D4_8F4F_00402656D980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WBButton.h"

/////////////////////////////////////////////////////////////////////////////
// CCWBButtonDemoDlg �_�C�A���O

class CCWBButtonDemoDlg : public CDialog
{
// �\�z
public:
	CCWBButtonDemoDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CCWBButtonDemoDlg)
	enum { IDD = IDD_CWBBUTTONDEMO_DIALOG };
	CWBButton	m_btn6;
	CWBButton	m_btn5;
	CWBButton	m_btn4;
	CWBButton	m_btn3;
	CWBButton	m_btn2;
    CWBButton	m_btn;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CCWBButtonDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CCWBButtonDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CWBBUTTONDEMODLG_H__518122C7_358F_11D4_8F4F_00402656D980__INCLUDED_)
