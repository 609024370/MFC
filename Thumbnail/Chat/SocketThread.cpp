// SocketThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "SocketThread.h"
#include "TcpChessSocket.h"
#include "ChessDlg.h"
extern CSocket m_socket;
extern CTcpChessSocket m_con_socket;
extern CChessDlg *ppdlg;

// CSocketThread

IMPLEMENT_DYNCREATE(CSocketThread, CWinThread)

CSocketThread::CSocketThread()
{
}

CSocketThread::~CSocketThread()
{
}

BOOL CSocketThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	m_socket.Listen(1) ;
	ppdlg->Accept();
	
	return TRUE;
}

int CSocketThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSocketThread, CWinThread)
END_MESSAGE_MAP()


// CSocketThread ��Ϣ�������
