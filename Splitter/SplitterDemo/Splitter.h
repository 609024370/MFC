// Splitter.h : SPLITTER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_SPLITTER_H__78A12252_2545_47FA_86E7_B7C04C16D66D__INCLUDED_)
#define AFX_SPLITTER_H__78A12252_2545_47FA_86E7_B7C04C16D66D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CSplitterApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� Splitter.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CSplitterApp : public CWinApp
{
public:
	CSplitterApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSplitterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CSplitterApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SPLITTER_H__78A12252_2545_47FA_86E7_B7C04C16D66D__INCLUDED_)
