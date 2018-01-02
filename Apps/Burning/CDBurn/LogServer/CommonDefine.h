// CommonDefine.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(__COMMON_DEFINE_H__)
#define __COMMON_DEFINE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// ------------------------------------------------------------------------------------------
#define  WM_SOCKET_MSG_0		(WM_USER + 1200)
#define  WM_SOCKET_MSG_1		(WM_USER + 1201)

// ------------------------------------------------------------------------------------------ ���ݰ�����
// *************** ���ݰ����Ͷ��壬�������ݰ���ͨ��
// ���ݰ�������, TP--Type of Packet
enum ENUM_TYPE_OF_PACKET
{
	TP_SYS_DIAGNOSIS		= 0,	// ϵͳ���
};

// ���ݰ�������, TSP-- SubType of Packet
enum ENUM_SUBTYPE_OF_PACKET
{
	TSP_SYS_DIAGNOSIS		= 0,	// ϵͳ���
};

// ���ݰ�����
struct STRUCT_PACKET_TYPE
{
	ENUM_TYPE_OF_PACKET		nType;
	ENUM_SUBTYPE_OF_PACKET	nSubType;
};

// ------------------------------------------------------------------------------------------ ϵͳ�������
struct STRUCT_PACKET_FAULT_DIAGNOSIS
{
	STRUCT_PACKET_TYPE oTypeOfPacket;	// ���ݰ����͡���������ͨ��

	char sTypeOfFault[3];				// �澯����A1Ϊһ���澯
	char sDate[9];						// �����ա��磺20060421
	char sTime[7];						// ʱ���롣�磺121220
	char sSource[5];					// ��Դ��ϵͳ��ģ�顣�磺SW01,SW���Ź���������ϵͳ,01�����ݹ���ģ��;          
	char sTypeOfRecord[5];				// ���ࡣ�磺0001    
	char sDescr[64*1024];				// �澯�������磺STUDYID=22,SERIESID=5,COILTYPE=HEAD,SEQ=FSE2D,O1=-234.56,TG=13.6,RG=0.567

	//Modified by Tom, --2008.07.10
	void SetTypeOfPacket( ENUM_TYPE_OF_PACKET nType, ENUM_SUBTYPE_OF_PACKET nSubType )
	{
		oTypeOfPacket.nType = nType;
		oTypeOfPacket.nSubType = nSubType;
	};

	void SetTypeOfFault( char* sTypeOfFault1 )
	{
		memcpy( sTypeOfFault, sTypeOfFault1, 3 );
		SetDateTime();
	};
	void SetSource( char* sSource1 )
	{
		memcpy( sSource, sSource1, 5 );
	};
	void SetTypeOfRecord( char* sTypeOfRecord1 )
	{
		memcpy( sTypeOfRecord, sTypeOfRecord1, 5 );
	};
	void SetDescr( LPCSTR format, ... )
	{
		va_list arglist; 
		char buffer[2048]; 
		
		va_start (arglist,format); 
		sprintf( buffer, arglist );
		vsprintf( buffer, format, arglist ); 
		va_end (arglist); 

		memcpy( sDescr, buffer, 64*1024 );
	};

	void SetDateTime()
	{
		time_t nDateTime = mktime( CTime::GetCurrentTime().GetLocalTm() );			
		tm * pTm = localtime( &nDateTime );
		sprintf( sDate, "%04d%02d%02d", pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday );
		sprintf( sTime, "%02d%02d%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec );
	};
	
	void SendToLogServer( ENUM_TYPE_OF_PACKET nType, ENUM_SUBTYPE_OF_PACKET nSubType,
		char* sTypeOfFault1, char* sSource1, char* sTypeOfRecord1, LPCSTR format, ... )
	{
		SetTypeOfPacket( nType, nSubType );
		SetTypeOfFault( sTypeOfFault1 );
		SetSource( sSource1 );
		SetTypeOfRecord( sTypeOfRecord1 );
		
		// Descr
		va_list arglist; 
		char buffer[2048]; 
		
		va_start (arglist,format); 
		sprintf( buffer, arglist );
		vsprintf( buffer, format, arglist ); 
		va_end (arglist); 
		
		memcpy( sDescr, buffer, 64*1024 );
		
		// send this packet to log server
		HWND hReceiver = ::FindWindow( NULL, _T("LogServer") );
		if (hReceiver)
		{
			COPYDATASTRUCT cds;
			ZeroMemory(&cds, sizeof(COPYDATASTRUCT));
			cds.cbData = sizeof(STRUCT_PACKET_FAULT_DIAGNOSIS);	// length of packet
			cds.lpData = this;									// buffer of packet
			::SendMessage( hReceiver, WM_COPYDATA, (WPARAM) 0/*this*/, (LPARAM) &cds );
		}
	};
	
};
/*
struct STRUCT_PACKET_FAULT_DIAGNOSIS
{
	STRUCT_PACKET_TYPE oTypeOfPacket;// ���ݰ����͡���������ͨ��

	CString sTypeOfFault;		// A1��һ���澯
	CString sDate;				// �����ա���20060421
	CString sTime;				// ʱ���롣��121220
	CString sSource;			// SW01,SW���Ź���������ϵͳ,01�����ݹ���ģ��;          
	CString sTypeOfRecord;		// 0001������;    
	CString sDescr;				// (<64KByte)��STUDYID=22,SERIESID=5,COILTYPE=HEAD,SEQ=FSE2D,O1=-234.56,TG=13.6,RG=0.567	
};
*/

/** [zhlxu 2008.4.17] [] ���Log��¼���ݹ��˱�ʶ�� **/

/** [zhlxu 2008.4.17] **/



// ------------------------------------------------------------------------------------------


#endif // !defined(__COMMON_DEFINE_H__)
