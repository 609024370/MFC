// test.h : main header file for the TEST application
//

#if !defined(AFX_TEST_H__1175F4E4_3130_11D2_A84D_00A0C9727AA7__INCLUDED_)
#define AFX_TEST_H__1175F4E4_3130_11D2_A84D_00A0C9727AA7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestApp:
// See test.cpp for the implementation of this class
//

class CTestApp : public CWinApp
{
public:
	CTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_H__1175F4E4_3130_11D2_A84D_00A0C9727AA7__INCLUDED_)
