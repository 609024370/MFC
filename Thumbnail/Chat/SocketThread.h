#pragma once



// CSocketThread

class CSocketThread : public CWinThread
{
	DECLARE_DYNCREATE(CSocketThread)

protected:
	CSocketThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSocketThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


