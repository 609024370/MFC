//////////////////////////////////////////////////////////////////////////////
//������CFireCtrlApp
//���ܣ�Ӧ�ó���ĳ�ʼ��
//���ߣ��쾰��(jingzhou_xu@163.net)
//��֯��δ��������(Future Studio)
//���ڣ�2001.12.1
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_FIRECTRL_H__3E7C4EE6_4CBA_42CC_82DD_E3C5486784FA__INCLUDED_)
#define AFX_FIRECTRL_H__3E7C4EE6_4CBA_42CC_82DD_E3C5486784FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFireCtrlApp:
// See FireCtrl.cpp for the implementation of this class
//

class CFireCtrlApp : public CWinApp
{
public:
	CFireCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFireCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFireCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRECTRL_H__3E7C4EE6_4CBA_42CC_82DD_E3C5486784FA__INCLUDED_)
