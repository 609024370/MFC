// ShutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CShut.h"
#include "ShutDlg.h"
#include "MyFade.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

byte pbit[16]=
	{
		0x55, 0, 0xaa, 0x0, 
		0x55, 0, 0xaa, 0x0, 
		0x55, 0, 0xaa, 0x0, 
		0x55, 0, 0xaa, 0x0, 
	};
static i=0;
/////////////////////////////////////////////////////////////////////////////
// CShutDlg dialog


CShutDlg::CShutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShutDlg)
	
	//}}AFX_DATA_INIT
}


void CShutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShutDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShutDlg, CDialog)
	//{{AFX_MSG_MAP(CShutDlg)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_BT_SHUTDOWN, OnBtShutdown)
	ON_BN_CLICKED(IDC_BT_RELOGIN, OnBtRelogin)
	ON_BN_CLICKED(IDC_BT_REBOOT, OnBtReboot)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShutDlg message handlers

void CShutDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	COLORREF color;
	CBrush br;
	int j=0;
	br.CreateSolidBrush(RGB(0, 0, 128));
	CRect r0;
	r0.top=rect.top;
	r0.left=rect.left;
	r0.right=rect.right;
	r0.bottom=rect.top+80;
	dc.FillRect(&r0, &br);
	r0.top=rect.bottom-40;
	r0.bottom=rect.bottom;
	dc.FillRect(&r0, &br);
	
	br.DeleteObject();
	rect.DeflateRect(0, 40);
	for(int i=0; i<rect.Height()/2+1; i+=1)
	{
		CRect rc;
		rc.left=rect.left;
		rc.right=rect.right;
		rc.top=rect.top+i;
		rc.bottom=rect.top+i+1;

		color=RGB(0, 120, 225-j);
		br.CreateSolidBrush(color);
		j++;
		dc.FillRect(&rc, &br);
		rc.top=rect.bottom-i;
		rc.bottom=rect.bottom-i-1;
		dc.FillRect(&rc, &br);
		br.DeleteObject();
	}

	CFont *pOldFont;
	pOldFont=dc.SelectObject(&font);
	dc.SetTextColor(RGB(255, 0, 0));
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText("���Թرռ������^_^!", 
		CRect(5, 5, 300, 300), DT_LEFT);

	dc.SelectObject(pOldFont);
	dc.SetTextColor(RGB(255, 255, 255));

	GetDlgItem(IDC_BT_SHUTDOWN)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.left-=6;
	rect.right+=6;
	rect.top=rect.bottom+6;
	rect.bottom=rect.top+15;
	dc.DrawText("�ػ�(&S)", &rect, DT_CENTER);

	GetDlgItem(IDC_BT_RELOGIN)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.left-=6;
	rect.right+=6;
	rect.top=rect.bottom+6;
	rect.bottom=rect.top+15;
	dc.DrawText("ע��(&L)", &rect, DT_CENTER);

	GetDlgItem(IDC_BT_REBOOT)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.left-=6;
	rect.right+=6;
	rect.top=rect.bottom+6;
	rect.bottom=rect.top+15;
	dc.DrawText("����(&R)", &rect, DT_CENTER);

	m_bt_shut.LoadBitmaps(IDB_SHUT, IDB_SHUT);
	m_bt_relogin.LoadBitmaps(IDB_RELOGIN, IDB_SHUT);
	m_bt_reboot.LoadBitmaps(IDB_REBOOT, IDB_SHUT);
/*
	�ⲿ��Ϊ���ϵ�һ���ϰ汾�Ĺػ�Ч�����룬���Ǻܺ�
	HBITMAP hbm=CreateBitmap(8, 8, 1, 1, pbit);
	HBRUSH hbr=CreatePatternBrush(hbm);
	HDC hdc=CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	HDC hdc0=::GetDC(0);
	SelectObject(hdc,hbr);
		
	PatBlt(hdc, 0, 0, GetDeviceCaps(hdc, VERTRES), 
		GetDeviceCaps(hdc, HORZRES ),
		0xa000c9);
*/
}

BOOL CShutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CenterWindow(NULL);
// 	memset(&lgfont, NULL, sizeof(lgfont));
// 	strcpy(lgfont.lfFaceName, "����");
// 	lgfont.lfCharSet=GB2312_CHARSET;
// 	lgfont.lfWidth=12;
// 	lgfont.lfHeight=12;
// 	font.CreateFontIndirect(&lgfont);

	m_bt_shut.SubclassDlgItem(IDC_BT_SHUTDOWN, this);
	m_bt_relogin.SubclassDlgItem(IDC_BT_RELOGIN, this);
	m_bt_reboot.SubclassDlgItem(IDC_BT_REBOOT, this);

	SetTimer(1, 500, NULL);

	//////////////////////////////////////////////////////////////////////////
	//������ϼ�ctrl+Alt+del
//	SystemParametersInfoA(SPI_SCREENSAVERRUNNING, true, 0, 0);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	return TRUE; 
}

BOOL CShutDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(pWnd->GetDlgCtrlID()==IDC_BT_REBOOT
		||pWnd->GetDlgCtrlID()==IDC_BT_RELOGIN
		||pWnd->GetDlgCtrlID()==IDC_BT_SHUTDOWN)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649)));
		//WINVER=0x0500
		return true;
	}
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return TRUE;
	//CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CShutDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	::InvalidateRect(0, 0, 1);
	AfxGetMainWnd()->ShowWindow(SW_SHOW);
	CDialog::OnCancel();
}

void CShutDlg::InitShut()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	//��ý��̱�ʶ��
	if(!::OpenProcessToken(::GetCurrentProcess(), 
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY , &hToken) )
	{
		::AfxMessageBox("��ý��̱�ʶ");
	}

	//��ùر�����ȨLUID
	::LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME , 
		&tkp.Privileges[0].Luid);
	tkp.PrivilegeCount=1;  //��������Ȩ
	tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED ;
	
	//��ùرս��̵�����Ȩ
	::AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
		(PTOKEN_PRIVILEGES)NULL, 0);

	if(::GetLastError()!=ERROR_SUCCESS)
	{
		::AfxMessageBox("׼��ע����");
	}

}

void CShutDlg::OnBtRelogin() 
{
	// TODO: Add your control notification handler code here
	InitShut();
	if(!::ExitWindowsEx(EWX_LOGOFF , 10))
	{
		MessageBox("ע��ʧ��", "������ʾ");
	}
}

void CShutDlg::OnBtShutdown() 
{
	InitShut();
	if(!::ExitWindowsEx(EWX_SHUTDOWN , 10))
	{
		MessageBox("�ػ�ʧ��", "������ʾ");
	}
}

void CShutDlg::OnBtReboot() 
{
	// TODO: Add your control notification handler code here
	InitShut();
	if(!::ExitWindowsEx(EWX_REBOOT , 10))
	{
		MessageBox("����ʧ��", "������ʾ");
	}
}

void CShutDlg::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);
	CMyFade::FadeScreen(this);
	ShowWindow(SWP_NOMOVE);
	SetForegroundWindow();
	KillTimer(1);
}
