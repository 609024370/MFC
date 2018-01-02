/////////////////////////////////////////////////////////////////////////////
// Project��LOGSERVER
// Author��Paul Dilascia
// Date��������, ʮһ�� 07, 2002
// Description��һ���򵥵�ϵͳ���̳������ӣ���API������װ��һ��C++���У�ʵ�����̳������չ��
//
/////////////////////////////////////////////////////////////////////////////
// LOGSERVER.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LOGSERVER.h"
#include "about.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyApp

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	//{{AFX_MSG_MAP(CMyApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyApp construction

CMyApp::CMyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyApp object

CMyApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMyApp initialization

BOOL CMyApp::InitInstance()
{
	HANDLE hMutex;
	CString sMutexName = "LOG_SERVER";
	hMutex = CreateMutex( NULL, false, sMutexName );
    if( hMutex == NULL || ::GetLastError()== ERROR_ALREADY_EXISTS )
	{
		return false;
	}
	

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	m_pFrame = new CMainFrame;
	m_pMainWnd = m_pFrame;

	// create and load the frame with its resources

	m_pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	::SetWindowPos(m_pMainWnd->GetSafeHwnd(), HWND_NOTOPMOST/*HWND_TOPMOST*/, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE);
	
	// The one and only window has been initialized, so show and update it.
	m_pFrame->ShowWindow(SW_HIDE);
	m_pFrame->UpdateWindow();

//	OnAppAbout();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMyApp message handlers




// App command to run the About dialog
void CMyApp::OnAppAbout()
{
	CAboutDlg().DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMyApp message handlers


int CMyApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinApp::ExitInstance();
}
