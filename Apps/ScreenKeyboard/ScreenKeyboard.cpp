// ScreenKeyboard.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ScreenKeyboard.h"
#include "ScreenKeyboardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScreenKeyboardApp

BEGIN_MESSAGE_MAP(CScreenKeyboardApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CScreenKeyboardApp ����

CScreenKeyboardApp::CScreenKeyboardApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CScreenKeyboardApp ����

CScreenKeyboardApp theApp;


// CScreenKeyboardApp ��ʼ��

BOOL CScreenKeyboardApp::InitInstance()
{
	if(IsProgrameRunning()) return FALSE; //�����һ���汾���о͹ر�

	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	CScreenKeyboardDlg dlg;
	m_pMainWnd = &dlg;
//	dlg.Create(IDD_SCREENKEYBOARD_DIALOG);
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO���ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO���ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


BOOL CScreenKeyboardApp::IsProgrameRunning(void)
{
	/////////////////////////////////////////////////////////////
	HANDLE hSem = CreateSemaphore(NULL, 1, 1, m_pszAppName); 
	// �ź����Ѵ��� 
	// �ź������ڣ����������һ��ʵ������ 
	if (GetLastError() == ERROR_ALREADY_EXISTS) 
	{ 
		// �ر��ź������ 
		CloseHandle(hSem); 
		// Ѱ����ǰʵ���������� 
		HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD); 
		while (::IsWindow(hWndPrevious)) 
		{ 
			// ��鴰���Ƿ���Ԥ��ı��? 
			// �У���������Ѱ�ҵ����� 
			if (::GetProp(hWndPrevious, m_pszExeName)) //��OnInitDialog()�������������
			{ 
				// ����������С������ָ����С 
				if (::IsIconic(hWndPrevious)) 
					::ShowWindow(hWndPrevious,SW_RESTORE); 

				// ���������� 
				::SetForegroundWindow(hWndPrevious); 

				// �������ĶԻ��򼤻� 
				::SetForegroundWindow( 
					::GetLastActivePopup(hWndPrevious)); 
				// �˳���ʵ�� 
				return TRUE; 
			} 
			// ����Ѱ����һ������ 
			hWndPrevious = ::GetWindow(hWndPrevious,GW_HWNDNEXT);
		} 
		// ǰһʵ���Ѵ��ڣ����Ҳ��������� 
		// ���ܳ����� 
		// �˳���ʵ�� 
		return TRUE; 
	} 
	return FALSE;
}