// DataManager.h: interface for the CDataManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAMANAGER_H__72878744_9F4F_4E1A_9E7D_BAC9E6C7CCEC__INCLUDED_)
#define AFX_DATAMANAGER_H__72878744_9F4F_4E1A_9E7D_BAC9E6C7CCEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// -----------------------------------------------------------------------------------------------------------
#pragma warning (disable:4786)
#include <string>
#include <map>
#include <vector>

// -----------------------------------------------------------------------------------------------------------
#include "CommonDefine.h"

// -----------------------------------------------------------------------------------------------------------

class CDataManager  
{
public:
	CDataManager();
	virtual ~CDataManager();

	static CDataManager m_Object;
	static CDataManager& GetHandle();
	
public:
	// Log��¼
	std::vector<STRUCT_PACKET_FAULT_DIAGNOSIS> m_vRecords;
	
	// ������Ϣ
	// ������Ϣ������LogServer.ini��
	// *** ͨ��UI������и�ѡ�������
	CString					m_sConfigFileName;		// �����ļ�ȫ·����
	CString					m_sWorkDirectory;		// ����Ŀ¼
	std::map<CString,bool>	m_mSaveRecordFlag;		// Log��¼���ݹ�������
	unsigned int			m_iPermittedLogFileNum;	// ����������Log�ļ�����

	void ReadOptionsFromFile();
	void WriteOptionsToFile();

	CString GetExeDirectory();

	// �ļ�����ά��
	std::vector<CString> m_vLogFilesName;	
	void FindLogFiles();
	void DeleteRedundanceFiles();
};

#endif // !defined(AFX_DATAMANAGER_H__72878744_9F4F_4E1A_9E7D_BAC9E6C7CCEC__INCLUDED_)
