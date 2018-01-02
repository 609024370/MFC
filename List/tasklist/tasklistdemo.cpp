// tasklistdemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "tasklistdemo.h"
#include "tasklistdemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTasklistdemoApp

BEGIN_MESSAGE_MAP(CTasklistdemoApp, CWinApp)
	//{{AFX_MSG_MAP(CTasklistdemoApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTasklistdemoApp construction

CTasklistdemoApp::CTasklistdemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTasklistdemoApp object

CTasklistdemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTasklistdemoApp initialization

BOOL CTasklistdemoApp::InitInstance()
{
	// Standard initialization

	CTasklistdemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
