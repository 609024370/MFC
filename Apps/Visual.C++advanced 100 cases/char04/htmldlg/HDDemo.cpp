// HDDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HDDemo.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "HDDemoDoc.h"
#include "HDDemoView.h"
#include "DLGHTML.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHDDemoApp

BEGIN_MESSAGE_MAP(CHDDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CHDDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_DEMO_INPUTPARAMETERS, OnDemoInputparameters)
	ON_COMMAND(ID_DEMO_NOPARAMETERS, OnDemoNoparameters)
	ON_COMMAND(ID_DEMO_RETURNVALUES, OnDemoReturnvalues)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHDDemoApp construction

CHDDemoApp::CHDDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHDDemoApp object

CHDDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHDDemoApp initialization

BOOL CHDDemoApp::InitInstance()
{
	AfxEnableControlContainer();

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

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_HDDEMOTYPE,
		RUNTIME_CLASS(CHDDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CHDDemoView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	

	m_strUserName = "a";
	m_strProductId = "000-000000";
	m_strProductVer = "1.0";
	m_strCompName = "d";
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CHDDemoApp::OnAppAbout()
{
	CHtmlDialog dlg("HTML_RESOURCE", TRUE, AfxGetMainWnd());
	dlg.SetParam("Test Arguments");
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHDDemoApp message handlers


void CHDDemoApp::OnDemoInputparameters() 
{
	// TODO: Add your command handler code here
	CHtmlDialog dlg("HTML_RESOURCE", TRUE, AfxGetMainWnd());
	dlg.SetParam(m_strProductId+ ";" 
					+ m_strProductVer 
					+ ";" + m_strCompName 
					+ ";"+m_strUserName);
	dlg.DoModal();
}

void CHDDemoApp::OnDemoNoparameters() 
{
	OnAppAbout();
	
}

void CHDDemoApp::OnDemoReturnvalues() 
{
	CHtmlDialog dlg("HTML_RESOURCE", TRUE, AfxGetMainWnd());
	dlg.SetParam(m_strProductId+ ";" 
					+ m_strProductVer 
					+ ";" + m_strCompName 
					+ ";"+m_strUserName
					+ ";" + "1");

	dlg.DoModal();
	
	CString strRet = dlg.GetReturnString();
	int nBreak = strRet.Find(';');
	m_strCompName = strRet.Left(nBreak);
	m_strUserName = strRet.Right(strRet.GetLength() - nBreak - 1);

}

