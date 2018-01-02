// ConfigInfo1.cpp: implementation of the CConfigInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogServer.h"
#include "ConfigInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------------------------------
CConfigInfo CConfigInfo::m_Object;

// -----------------------------------------------------------------------------------------------------------

CConfigInfo::CConfigInfo()
{
	//	SW02,PROSPECT���
	//	MS01,�����¿���
	//	RS01,��Ƶ�Ŵ���
	//	GS01,�ݶȷŴ���
	//	GS02,�ݶȵ�Դ
	//	GS03,�ȳ��Ŵ���
	//	SP01,����
	//	OS01,SIU
	//	OS02,�ſ�
	//	OS03,�綯����
	//	I000,��Ϣ��
	//	UNNO,unknown
	m_mRecordFilter["SW02"] = true;
	m_mRecordFilter["MS01"] = true;
	m_mRecordFilter["RS01"] = true;
	m_mRecordFilter["GS01"] = true;
}

CConfigInfo::~CConfigInfo()
{

}

CConfigInfo& CConfigInfo::GetHandle()
{
	return m_Object;
}
