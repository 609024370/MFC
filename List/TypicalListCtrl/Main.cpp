/////////////////////////////////////////////////////////////////////////////
// Main.cpp : Defines the class behaviors for the application.
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Main.h"
#include "MainFrame.h"
#include "ChildFrame.h"
#include "MainDoc.h"
#include "MainView.h"
#include "About.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainApp
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMainApp, CWinApp)
	//{{AFX_MSG_MAP(CMainApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainApp construction
/////////////////////////////////////////////////////////////////////////////
CMainApp::CMainApp() {
}

/////////////////////////////////////////////////////////////////////////////
// CMainApp initialization
/////////////////////////////////////////////////////////////////////////////
BOOL CMainApp::InitInstance() {
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
	SetRegistryKey(_T("The Typical ListCtrl"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate *pDocTemplate;

	pDocTemplate = new CMultiDocTemplate(
			IDR_MAINTYPE,
			RUNTIME_CLASS(CMainDoc),
			RUNTIME_CLASS(CChildFrame),  // Custom MDI child frame
			RUNTIME_CLASS(CMainView)
			);

	AddDocTemplate(pDocTemplate);

	// Create main MDI Frame window
	CMainFrame *pMainFrame = new CMainFrame;

	if(!pMainFrame->LoadFrame(IDR_MAINFRAME))
			return FALSE;

	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if(!ProcessShellCommand(cmdInfo))
			return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// OnAppAbout : App command to run the dialog
/////////////////////////////////////////////////////////////////////////////
void CMainApp::OnAppAbout() {
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMainApp object
/////////////////////////////////////////////////////////////////////////////
CMainApp theApp;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
