// PropListDemo.h : main header file for the PROPLISTDEMO application
//

#if !defined(AFX_PROPLISTDEMO_H__5B234865_2251_11D2_94BD_00207811FA68__INCLUDED_)
#define AFX_PROPLISTDEMO_H__5B234865_2251_11D2_94BD_00207811FA68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPropListDemoApp:
// See PropListDemo.cpp for the implementation of this class
//

class CPropListDemoApp : public CWinApp
{
public:
	CPropListDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropListDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPropListDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPLISTDEMO_H__5B234865_2251_11D2_94BD_00207811FA68__INCLUDED_)
