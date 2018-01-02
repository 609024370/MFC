// ExpandDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExpandDialog.h"
#include "ExpandDialogDlg.h"

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
// CExpandDialogDlg dialog

CExpandDialogDlg::CExpandDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExpandDialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExpandDialogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExpandDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpandDialogDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExpandDialogDlg, CDialog)
	//{{AFX_MSG_MAP(CExpandDialogDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MORE_BUTTON, OnMoreButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpandDialogDlg message handlers

BOOL CExpandDialogDlg::OnInitDialog()
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
	
	// �ڶԻ���Ϊ��С״̬ʱ����ʼ��ʾ��
	ExtendDlg(IDC_SEPARATE,FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExpandDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExpandDialogDlg::OnPaint() 
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
HCURSOR CExpandDialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExpandDialogDlg::ExtendDlg(int nResourceID, BOOL bExpand)
{
	// ���bExpand==TRUE������չ�Ի���Ϊ���
	// ������С�Ի����µĶԻ���ĵײ�Ϊ��ԴnResourceID�ؼ��ָ�
	static CRect rcLarge;
	static CRect rcSmall;
	CString sExpand;
	
	// �ڿ�ʼʱ������Ի����������С�ߴ�
	if(rcLarge.IsRectNull())
	{
		CRect rcLandmark;
		// �õ��ָ�����ָ��
		CWnd* pWndLandmark=GetDlgItem(nResourceID);
		ASSERT(pWndLandmark);

		// �õ��Ի���ĳߴ�
		GetWindowRect(rcLarge);
		// �õ��ָ����ڶԻ����е�λ��
		pWndLandmark->GetWindowRect(rcLandmark);

		rcSmall=rcLarge;
		rcSmall.bottom=rcLandmark.top;
	}

	if(bExpand)
	{
		// ��չ�Ի����������öԻ�����ԭʼ����󣩳ߴ磨rcLarge��
		SetWindowPos(NULL,0,0,rcLarge.Width(),rcLarge.Height(),
					SWP_NOMOVE|SWP_NOZORDER);

		sExpand="<<&Less";
		EnableVisibleChildren();
	}
	else
	{
		// ��С�Ի����������öԻ�������С�ߴ磨rcSmall��
		SetWindowPos(NULL,0,0,rcSmall.Width(),rcSmall.Height(),
					SWP_NOMOVE|SWP_NOZORDER);

		sExpand="&More>>";
		EnableVisibleChildren();
	}

	// ���ð�ť������
	SetDlgItemText(IDC_MORE_BUTTON,sExpand);
}

void CExpandDialogDlg::EnableVisibleChildren()
{
	// ����Ĵ���ʹ���ڵ�ǰ�Ի����еİ�ťʧЧ��
	// �������Ա���ʹ��Tab�����߿�ݼ��ƶ������صĿؼ�

	// �õ���һ���ӿؼ�
	CWnd* pWndCtrl=GetWindow(GW_CHILD);
	CRect rcRest;
	CRect rcControl;
	CRect rcShow;

	GetWindowRect(rcShow);

	// �����Ի����еĿؼ�
	while(pWndCtrl!=NULL)
	{
		pWndCtrl->GetWindowRect(rcControl);

		if(rcRest.IntersectRect(rcShow,rcControl))
			pWndCtrl->EnableWindow(TRUE);
		else
			pWndCtrl->EnableWindow(FALSE);

		// �õ��ڿؼ����е���һ��
		pWndCtrl=pWndCtrl->GetWindow(GW_HWNDNEXT);
	}
}

void CExpandDialogDlg::OnMoreButton() 
{
	// ����bExpand���ڸ��ٶԻ�����չ/������״̬
	static BOOL bExpand = TRUE;

	// ��IDC_SEPARATE�ָ�Ի���
	ExtendDlg(IDC_SEPARATE,bExpand);
	bExpand=!bExpand;
}
