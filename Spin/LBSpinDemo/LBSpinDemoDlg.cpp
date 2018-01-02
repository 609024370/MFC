// LBSpinDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LBSpinDemo.h"
#include "LBSpinDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CLBSpinDemoDlg dialog

CLBSpinDemoDlg::CLBSpinDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLBSpinDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLBSpinDemoDlg)
	m_nBuddy4 = 0;
	m_nBuddy1 = 0;
	m_nBuddy2 = 0;
	m_nBuddy3 = 0;
	m_nBuddy5 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLBSpinDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLBSpinDemoDlg)
	DDX_Control(pDX, IDC_SPIN6, m_LBSpinBtnCtrl_U_HOR);
	DDX_Control(pDX, IDC_SPIN5, m_SpinBtnCtrl);
	DDX_Control(pDX, IDC_SPIN4, m_LBSpinBtnCtrl_U);
	DDX_Control(pDX, IDC_SPIN3, m_LBSpinBtnCtrl_L);
	DDX_Control(pDX, IDC_SPIN1, m_LBSpinBtnCtrl_R);
	DDX_Text(pDX, IDC_EDIT4, m_nBuddy4);
	DDX_Text(pDX, IDC_EDIT1, m_nBuddy1);
	DDX_Text(pDX, IDC_EDIT2, m_nBuddy2);
	DDX_Text(pDX, IDC_EDIT3, m_nBuddy3);
	DDX_Text(pDX, IDC_EDIT5, m_nBuddy5);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLBSpinDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CLBSpinDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLBSpinDemoDlg message handlers

BOOL CLBSpinDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	m_LBSpinBtnCtrl_U.SetRange32(0,5);
	m_LBSpinBtnCtrl_U_HOR.SetRange32(0,5);
	m_LBSpinBtnCtrl_L.SetRange32(0,5);
	m_LBSpinBtnCtrl_R.SetRange32(0,5);

	m_SpinBtnCtrl.SetRange32(0,5);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLBSpinDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLBSpinDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLBSpinDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

