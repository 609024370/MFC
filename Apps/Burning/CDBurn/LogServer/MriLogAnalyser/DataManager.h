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
struct STRUCT_LOG_RECORD
{
	bool bShowBySeqName, bShowByCoilType;

	CString sAlarmLevel;				// �澯����A1Ϊһ���澯
	CString sDate;						// �����ա��磺20060421
	CString sTime;						// ʱ���롣�磺121220
	CString sSource;					// ��Դ��ϵͳ��ģ�顣�磺SW01,SW���Ź���������ϵͳ,01�����ݹ���ģ��;          
	CString sRecordType;				// ���ࡣ�磺0001    

	CString sStudyID;
	CString sSeriesID;
	CString sCoilType;
	CString sSequenceName;
	
	CString sO1, sTG, sRG, sSF;
//	CString sDescr[64*1024];				// �澯�������磺STUDYID=22,SERIESID=5,COILTYPE=HEAD,SEQ=FSE2D,O1=-234.56,TG=13.6,RG=0.567
};
// -----------------------------------------------------------------------------------------------------------

	
class CDataManager  
{
public:
	CDataManager();
	virtual ~CDataManager();

	static CDataManager m_Object;
	static CDataManager& GetHandle();

	// ������Ϣ
public:
	// ������Ϣ������LogServer.ini��
	// *** ͨ��UI������и�ѡ�������
	CString					m_sConfigFileName;		// �����ļ�ȫ·����
	CString					m_sWorkDirectory;		// ����Ŀ¼
	
	void ReadOptionsFromFile();
	void WriteOptionsToFile();	
	
	// Log��¼
public:
	// ��ѯʱ��� 
	CString m_sStartDate, m_sStartTime, m_sEndDate, m_sEndTime;
	// �û�����
	CString m_sNameOfInstitution, m_sSerialNumOfEquip;
	// ɨ�������¼
	std::vector<STRUCT_LOG_RECORD> m_vRecords_ScanParams;
	std::vector<STRUCT_LOG_RECORD*> m_vShownRecords;
	std::map<CString,CString> m_mSequenceName, m_mCoilType;
	
	void ReadLogRecordFromFile();
	bool ReadLogRecord( CString sFileName);
	void ParseLogRecord( CString sRecordStrng );
	void GetShownRecords();
	
};

#endif // !defined(AFX_DATAMANAGER_H__72878744_9F4F_4E1A_9E7D_BAC9E6C7CCEC__INCLUDED_)
