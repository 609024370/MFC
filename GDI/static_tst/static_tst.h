// static_tst.h : main header file for the STATIC_TST application
//

#if !defined(AFX_STATIC_TST_H__F00F7A50_6964_43C1_B672_140BAD175D65__INCLUDED_)
#define AFX_STATIC_TST_H__F00F7A50_6964_43C1_B672_140BAD175D65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStaticTstApp:
// See static_tst.cpp for the implementation of this class
//

class CStaticTstApp : public CWinApp
{
public:
	CStaticTstApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticTstApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStaticTstApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIC_TST_H__F00F7A50_6964_43C1_B672_140BAD175D65__INCLUDED_)
