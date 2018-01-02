// DestEquipCom.cpp: implementation of the CCom class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogServer.h"
#include "CommonDefineFunc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCom::CCom()
{
	CString sAppPath, sPathFile;
	::GetCurrentDirectory( 255, sAppPath.GetBuffer(255) );
	m_sConfigFileName.Format( "%s\\LogServer.ini", sAppPath );
	CFileFind fileFinder;
    BOOL bFileExist = fileFinder.FindFile( m_sConfigFileName );
	if ( !bFileExist )
	{
		OUT_LOG( "{Com} The config file was not been found ! NAME: %s", m_sConfigFileName );
	}
}

CCom::~CCom()
{
}

// ���������˷�������
void CCom::SendMessageToCallingWindow( HWND hCallingWnd, DWORD nByteOfPacket, void* pPacket )
{
	COPYDATASTRUCT cds;
	ZeroMemory(&cds, sizeof(COPYDATASTRUCT));
		
	cds.cbData = nByteOfPacket;	// lpData�ĳ��ȡ�cbData��ֵ������lpData���ݵĳ�����������򽫲�����Ӧ��Ϣ	// _tcslen(sImageFileName/*buffer*/) + sizeof(TCHAR);
	cds.lpData = pPacket;		// ���ݰ����ݣ���Ϊreal,int,string���ͣ�Ҳ��Ϊ�ṹ����						// sImageFileName.GetBuffer(255)/*buffer*/;
	
	if ( !hCallingWnd )
	{
		OUT_LOG( "{Com} Can't send data to WINDOW: NULL." );
	}
	
	::SendMessage( hCallingWnd, WM_COPYDATA, 0, (LPARAM) &cds );	
}