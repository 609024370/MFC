// CommonDefine.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(__COMMON_DEFINE_FUNC_H__)
#define __COMMON_DEFINE_FUNC_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// ------------------------------------------------------------------------------------------
//*************** ��ģ��ʹ�õ�LOG���ݰ�
struct STRUCT_PACKET_LOG
{
	int		nTypeOfPacket;	
	char	sLogText[2048];		// LOG����
};

// ------------------------------------------------------------------------------------------
void OUT_LOG( LPCSTR format, ... );
void SEND_PACKET_TO_COMSERVER( HWND hCallingWnd, PVOID pData, int nLengthOfData );

// ------------------------------------------------------------------------------------------

#endif // !defined(__COMMON_DEFINE_H__)


