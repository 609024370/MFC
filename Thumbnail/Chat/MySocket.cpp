// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "MySocket.h"
#include "ChatDlg.h"

// CMySocket

CMySocket::CMySocket()
{

}

CMySocket::~CMySocket()
{
}


// CMySocket ��Ա����

void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CChatDlg *pdlg = (CChatDlg*)m_hwnd;
	pdlg->OnReceive();
	CAsyncSocket::OnReceive(nErrorCode);
}
void CMySocket::SetHWnd(HWND hwnd)
{
	m_hwnd = hwnd;
}
