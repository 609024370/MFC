// MacSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "MacSocket.h"
#include "MacDlg.h"
// CMacSocket
extern CMacDlg *pdlg;

CMacSocket::CMacSocket()
{
}

CMacSocket::~CMacSocket()
{
}


// CMacSocket ��Ա����

void CMacSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	pdlg->OnReceive();

	CSocket::OnReceive(nErrorCode);
}
