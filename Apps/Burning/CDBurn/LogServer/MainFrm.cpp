// MainFrm.cpp : implementation of the CMainFrame class
//
#include "stdafx.h"
#include "LogServer.h"
#include "MainFrm.h"
#include "CommonDefineFunc.h"
#include"stdio.h"
#include "shlwapi.h"
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
//��־��¼ȫ�ֱ���

//����DAO֧��
#include <afxdao.h>//����DAO���ݿ�֧��
#include"iostream.h"
#include"fstream.h"
CDaoDatabase db;				//���ݿ�
CDaoRecordset RecSet(&db);		//��¼��
#define DATABASE_NAME "��־�ļ����ݿ�.mdb"
#ifdef _CHEN_SHI_
char g_SystemPosName[][64]={
	"���������ϵͳ: ",
	"������ϵͳ: ",
	"��Ƶ��ϵͳ: ",
	"�ݶ���ϵͳ: "
};
char g_DataTypeName[][64]={
	"TG Value: ","RG Value: ","��ѹֵ: ","��������ֵ: "

};

#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
// Message ID used for tray notifications
#define WM_MY_TRAY_NOTIFICATION		WM_USER+0

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_MESSAGE(WM_MY_TRAY_NOTIFICATION, OnTrayNotification)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CLEAR,				OnViewClear)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CLEAR, OnUpdateViewClear)
	ON_WM_CLOSE()
	ON_COMMAND(ID_APP_OPEN, OnAppOpen)
	ON_COMMAND(ID_APP_SUSPEND, OnAppSuspend)
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_SOCKET_MSG_0, OnAcceptRequestForIntervention)	
	ON_MESSAGE(WM_SOCKET_MSG_1, OnAcceptRequestForDicomPrinter)	
	ON_COMMAND(ID_MENU_OPTIONS, OnMenuOptions)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() : m_trayIcon(IDR_TRAYICON)
{
	// TODO: add member initialization code here
	m_bShowTrayNotifications = TRUE;
	m_bShutdown = FALSE;

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 16;
	lf.lfWeight = FW_REGULAR;
	_tcscpy(lf.lfFaceName, _T("Fixedsys"));// Courier
	
	m_Font.CreateFontIndirect(&lf);
	
	m_BrushBk.CreateSolidBrush(BKCOLOR);

	m_pLogFileAccess = new CLogFileAccess();
}

CMainFrame::~CMainFrame()
{
	ReleaseComObjects();

	if ( m_pLogFileAccess )
	{
		delete m_pLogFileAccess;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}

	// Create child edit control for displaying messages
	CRect rc;
	if (!m_wndEdit.Create(
		WS_VISIBLE|WS_CHILD|WS_VSCROLL|ES_MULTILINE|ES_READONLY, rc, this, 
		AFX_IDW_PANE_FIRST))
		return -1;
	m_wndEdit.SetFont(&m_Font);		

	// Set up tray icon
	m_trayIcon.SetNotificationWnd(this, WM_MY_TRAY_NOTIFICATION);
	m_iWhichIcon = 1;
	m_trayIcon.SetIcon(IDI_MYICON);

	// ��ʼ��LogServer��Ŀ���豸��ͨ����
	InitComObjects();
	//��ʼ��������־
	//CLog::GetObj()<< "��ʼ����ʼ" <<endl ;
		
	
	return 0;
}

//////////////////
// Close window. Unless we are shutting down, just hide it.
void CMainFrame::OnClose() 
{
	if (m_bShutdown)
	{
		int nExit = MessageBox("Are you sure exit ?", "Log Server", MB_YESNO |
			MB_ICONQUESTION | MB_DEFBUTTON2);
		if (nExit == IDYES) 
		{
			
			CFrameWnd::OnClose();
		}
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
}
//////////////////
// Handle notification from tray icon: display a message.
//
LRESULT CMainFrame::OnTrayNotification(WPARAM uID, LPARAM lEvent)
{
	return 0;
}

////////////////////////////////////////////////////////////////
// Command handlers below.
//
void CMainFrame::OnViewClear() 
{
	m_wndEdit.SetWindowText("");	
}

void CMainFrame::OnUpdateViewClear(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndEdit.GetLineCount() > 1 || m_wndEdit.LineLength() > 0);
}

void CMainFrame::OnAppOpen() 
{
	ShowWindow(SW_SHOWMAXIMIZED/*SW_NORMAL*/);	
	SetForegroundWindow();
}

void CMainFrame::OnAppSuspend() 
{
	m_bShutdown = TRUE;		// really exit
	SendMessage(WM_CLOSE);	
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG
///////////////////////////////////////////////////////////////////////

void CMainFrame::InitComObjects()
{
	m_pComSocket_SysDiagnosis = new CComSocket_SysDiagnosis();
	m_pComSocket_SysDiagnosis->Init( m_hWnd, WM_SOCKET_MSG_0 );
}

void CMainFrame::ReleaseComObjects()
{
	delete m_pComSocket_SysDiagnosis;
}

// ����Windows Message���ݰ�
BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	DispatchPacket( pCopyDataStruct->lpData, pWnd );	
	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

// ����Windows Socket���ݰ�
void CMainFrame::OnAcceptRequestForIntervention(UINT wParam,LONG lParam)
{
	int message=lParam & 0x0000FFFF;	
	m_pComSocket_SysDiagnosis->AcceptRequest( WSAGETSELECTEVENT(lParam) );
}

void CMainFrame::OnAcceptRequestForDicomPrinter(UINT wParam,LONG lParam)
{
	int message=lParam & 0x0000FFFF;	
}

void CMainFrame::DispatchPacket( PVOID pData, CWnd* pCallingWnd )
{	
	STRUCT_PACKET_TYPE oPacketType;
	int nLenOfPacketType = sizeof(ENUM_TYPE_OF_PACKET) + sizeof(ENUM_SUBTYPE_OF_PACKET);
	memcpy ( &oPacketType, pData, nLenOfPacketType );

	switch ( oPacketType.nType )
	{
		case -1 /*TP_LOG*/:
			{
				STRUCT_PACKET_LOG* pPacket = (STRUCT_PACKET_LOG*) pData;
				m_wndEdit.SetSel(-1, -1);					// end of edit text
				m_wndEdit.ReplaceSel( pPacket->sLogText );	// append string
				m_wndEdit.SendMessage( EM_SCROLLCARET );	// make visible
			}
			break;
			
		case TP_SYS_DIAGNOSIS:
			{
				switch ( oPacketType.nSubType )
				{
					case TSP_SYS_DIAGNOSIS:
						m_pLogFileAccess->SaveToFile( pData );
						break;

					default:
						break;
				}
			}
			break;
			
		default:
			break;		
	}
}

void CMainFrame::OnMenuOptions() 
{
	COptionsDlg oOptionsDlg;
	oOptionsDlg.DoModal();
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	this->ShowWindow( SW_SHOWMAXIMIZED );
	
}
