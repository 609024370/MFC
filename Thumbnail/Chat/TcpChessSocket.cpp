// TcpChessSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "TcpChessSocket.h"
#include "ChessDlg.h"
// CTcpChessSocket

CTcpChessSocket::CTcpChessSocket()
{
}

CTcpChessSocket::~CTcpChessSocket()
{
}


// CTcpChessSocket ��Ա����

void CTcpChessSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CChessDlg * pdlg = (CChessDlg *) hwnd;
	pdlg->OnReceive();
	CSocket::OnReceive(nErrorCode);
}
void CTcpChessSocket::SetHwnd(HWND hw)
{
	hwnd = hw ;
}

void CTcpChessSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CSocket::OnAccept(nErrorCode);
}

void CTcpChessSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CChessDlg * pdlg = (CChessDlg *) hwnd;
	pdlg->SocketClose();
	CSocket::OnClose(nErrorCode);
}
