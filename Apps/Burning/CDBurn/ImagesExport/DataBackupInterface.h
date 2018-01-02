// Parameter.h: interface for the CDataBackupInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DataExportInterface__INCLUDED_)
#define _DataExportInterface__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include"stdafx.h"

// -----------------------------------------------------------------------------------------------------------
#pragma warning (disable : 4786)
#include <vector>

//extern "C" _declspec(dllexport) int Test();
/*

*/
// -----------------------------------------------------------------------------------------------------------

#ifndef _CHEN_SHI_
#define _CHEN_SHI_
#endif// 


class /*AFX_EXT_CLASS*/ CDataExportInterface  
{
public:
	CDataExportInterface();
	virtual ~CDataExportInterface();

private:

	int m_nStorageMediumType;	// 0-None; 1-Hard Disk; 2-CD; 3-DVD
	int m_nMoveOrCopy;			// 0-None; 1-Copy; 2-Move
	CString m_sLocalPath, m_sBackupPath;
	long m_CurFolderSize;//ͳ���ļ��д�С
	//��Ҫһ���м�����ݿ� û��ֻ������
	CString m_BackDbPath;

public:
	bool SaveImageDataToBmp(unsigned char *pDest,
						int w,
						int h,
						int format,
						char *pFileName);
	
	BOOL ExportStudyToBMP(CString szImageRootPath,CString szStudyID,CString strDestFilePathName,BOOL nSaveMed);
	//У��Path
	static BOOL CheckAndCreateDir(CString szDir);
//У����̿ռ�
	static BOOL CheckDiskSpaceAndEnWrite(CString szPath, int nTotalImage);
//�����������
	static bool ExportStudyToDicom(CString szImageRootPath,CString szStudyID,CString strDestFilePathName,BOOL nSaveMed);

//��������,���յ��������ݽṹ����ͼ�񵼳�
	/*********zyh add 2008.3.7 from cs*********/
	static long ExportAllSelStudyToTempDICOM(void *pExportBlockX);
	static long ThreadExportStudySendToPacs(LPVOID pVoid);
	/**********************************************/
	
	

	static BOOL ExportSelectStudy(void* pExportBlockX);
	/*********zyh add 2008.2.27*********/
	static BOOL ExportSelectStudy2(void *pExportBlockX, CProgressCtrl *pProcess);
	/**********************************************/
	
	static UINT ThreadExportStudy(LPVOID pVoid);
	int SetBackupParam();
	// ִ�б���
	// vStudyId����������Ҫ���ݵ�Study��Ŀ¼��
	bool ExecuteBackup( CString sLocalPath, CString sDatabaseName, std::vector<CString> vStudyId );
	// �������ݻָ�����
	// ���أ��������ݵ�·��
	CString SetRestoreParam(CString sLocalPath);
	// ִ�����ݻָ�
	// vStudyId����������Ҫ�ָ��ı���Study��Ŀ¼��
	// ע�⣺����copy���ݿ⵽����
	bool ExecuteRestore( CString sLocalPath, std::vector<CString> vStudyId );
	// ɾ�����ص�ͼ���ļ�
	bool DeleteImageFile( CString sLocalPath, std::vector<CString> vStudyId );
	////////////////////////////////////////////////////////////////////////////
	//������Ƕ�̬���ǲ��ķ������޷����ⲿ���á�
	bool CreateEqualFolders(CString csDirPath, CString csDesPath,int dMorC,bool bMdb);
	long GetFolderSize(CString sFolderPath);
	void CalculateFolderSize(CString csDirPath);
	bool DeleteFolderFiles(CString csDirPath);
	BOOL DeleteDirectory(char *DirName);
	bool DeleteDirAndFiles(CString csFilePath);
	bool CreateDirectoryMulty(CString csPathDir);
		
	
};

#endif // !defined(_DataBackupInterface__INCLUDED_)
