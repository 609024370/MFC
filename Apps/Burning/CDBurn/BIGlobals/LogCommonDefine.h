// CommonDefine.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(__LOG_COMMON_DEFINE_H__)
#define __LOG_COMMON_DEFINE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ------------------------------------------ ϵͳ�������
// *************** ��¼��������
// ��Դģ�����, TSM--Type of Source Module
enum ENUM_TYPE_OF_SOURCE_MODULE
{
	TSM_NONE			= 0,	// NONE

	TSM_SW				= 1,	// ���������ϵͳ
	TSM_MW				= 2,	// ������ϵͳ
	TSM_RW				= 3,	// ��Ƶ��ϵͳ
	TSM_GW				= 4,	// �ݶ���ϵͳ
};

// ���������ʹ���, TD--Type of Data
enum ENUM_TYPE_OF_DATA
{
	TD_NONE				= 0,	// NONE 
	
	// SW-���������ϵͳ
	TD_TG				= 1,	// TG 
	TD_RG				= 2,	// RG
	TD_O1				= 3,	// O1
	TD_TUNING_MEAN		= 4,	// �ź�ƽ��ֵ

	// MW-������ϵͳ
	// (TBD)
};
// ���������ʹ���, TD--Type of Data
enum ENUM_SUBTYPE_OF_DATA
{
	STD_NONE			= 0,	// NONE 
		
	// SW-���������ϵͳ
	// RG -- ��������֧��32��ͨ��
	STD_RG1				= 1,	// ͨ��1
	STD_RG2				= 2,	// ͨ��2
	STD_RG3				= 3,	// ͨ��3
	STD_RG4				= 4,	// ͨ��4

	// TUNING -- ����ͨ��
	STD_TUNING_CHANNEL_I	= 33,	// ͨ��I
	STD_TUNING_CHANNEL_Q	= 34,	// ͨ��Q
};

// ��¼�Ĺ�����Ϣ
struct STRUCT_DIAGNOSIS_BASE
{
	ENUM_TYPE_OF_DATA			nDataType;			// ��Դģ���е�������������롣����¼�����͡��������ݵļ�¼��ȡ
	ENUM_SUBTYPE_OF_DATA		nDataSubType;		// ��Դģ���е������ӷ�����롣����¼�����͡�
													// ��nDataTypeΪTD_RGʱ��nDataSubTypeΪ����ͨ����
													// ��nDataTypeΪTD_TUNING_MEANʱ��nDataSubTypeΪI/Qͨ����
	
	ENUM_TYPE_OF_SOURCE_MODULE	nSourceModule;		// ��Դģ�����
	char sEquipNo[32];								// MRIϵͳ��š����豸ͳһ���,32 Bytes, SiteField.BISerialNum
	time_t nTime;									// ��¼������ʱ��
	char sStudyID[16];								// Study�ı��
	int  nSeriesID;									// Series�ı�ţ���ͬStudy�е�SeriesID���ظ�
	BYTE nBodyPartID;								// ��鲿λ����
	long nSequenceID;								// �������д��롣ֻ����ʽɨ�����в���ID
};

// *************** �����¼����
// ��¼ (TG��RG��O1)
// ��ͨ��Ҳʹ�ñ��ṹ
struct STRUCT_RECORD_DIAGNOSIS_TG_RG_O1
{
	STRUCT_DIAGNOSIS_BASE	oBaseInfo;
	int		nNumOfData;				// ʵ�����ݸ���
	float	fValue[50];				// һ��TG/RG/O1ֵ����Ч����ΪnNumOfData
};

// ��¼ (Coil Tuning Mean)
// I��Qͨ��ʹ�ñ��ṹ
struct STRUCT_RECORD_DIAGNOSIS_TUNING_MEAN
{
	STRUCT_DIAGNOSIS_BASE	oBaseInfo;	
	int		nNumOfData;				// ʵ�����ݸ���
	int		nTuneVoltage[200];		// Tune��ѹֵ����Ч����ΪnNumOfData
	int		nMatchVoltage[200];		// TMatch��ѹֵ����Ч����ΪnNumOfData
	int		nTuneStepVoltage[200];		// ��ѹֵ��������Ч����ΪnNumOfData
	int		nMatchStepVoltage[200];		// ��ѹֵ��������Ч����ΪnNumOfData
	float	fMean[200];				// �ź�ƽ��ֵ����Ч����ΪnNumOfData
};
//��Ҫ���ڼ�¼ʹ�õ�IQͨ����������
struct STRUCT_RECORD_POS_TUNING_MEAN
{
	CRect pRect;
	int nTuneVoltage;
	int nMatchVoltage;
	int nStepVoltage;
	float fMean;
};

// ------------------------------------------------------------------------------------------


#endif // !defined(__LOG_COMMON_DEFINE_H__)
