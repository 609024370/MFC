#pragma once



// CMacSocket ����Ŀ��

class CMacSocket : public CSocket
{
public:
	CMacSocket();
	virtual ~CMacSocket();
	virtual void OnReceive(int nErrorCode);
};


