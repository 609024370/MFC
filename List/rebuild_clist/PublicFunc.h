/**
*	made by alzq,xpb
*	08-08-28
*
*
*/

#pragma once

#define	EXIF_NONE						0
#define	EXIF_MATCH						1
#define	EXIF_COLORSPACE					2
#define	EXIF_COMPONENTSCONFIGURATION	3
#define	EXIF_EXIFVERSION				4
#define	EXIF_EXPOSUREMODE				5
#define	EXIF_FILESOURCE					6
#define	EXIF_FLASHPIXVERSION			7
#define	EXIF_FOCALPLANERESOLUTIONUNIT	8
#define	EXIF_ISOSPEEDRATINGS			9
#define	EXIF_METERINGMODE				10
#define	EXIF_ORIENTATION				11
#define	EXIF_RESOLUTIONUNIT				12
#define	EXIF_SCENECAPTURETYPE			13
#define	EXIF_WHITEBALANCE				14
#define	EXIF_YCBCRPOSITIONING			15

#include <map>
#include "FileInfoList.h"
#include "ImgBaseFunc.h"
#include   <shlobj.h>  

/**
*	EXIF��Ϣ�洢ITEM
*	DealMethodΪ��ȡʱ��Ҫ���еĴ�����Ҫ��Ϊ
*	0:������
*	1:����
*/
typedef struct ExifInfoValueItem
{
	string ItemName;
	int DealMethod;
	string Value;
}ExifInfoValueItem;


typedef	map<string,ExifInfoValueItem>	T_mapStrStr;

class PublicFunc
{
public:
private:
	static T_mapStrStr ExifTitleMap;		//���EXIF��Ϣ�����MAP
	static HANDLE T_hMutex;					//GDI��Graphics����ʱ�Ļ������
public:

	PublicFunc(void);
	~PublicFunc(void);
	//=====================================================================
	// �� �� ����InitPublicFuncs
	// ������������ʼ�������������в��ֳ�Ա
	// ���������void
	// ���������void
	// �������ڣ�08.10.07
	// �޸����ڣ�08.10.07
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static void InitPublicFuncs();


	//=====================================================================
	// �� �� ����DoChangeImageSize
	// ������������image�����������
	// ���������Image * image,				//ͼ�����ָ��
	//			 UINT nImageWidth,			//ͼ��Ҫ�趨�����ؿ����
	//			 UINT nImageHeight 			//ͼ��Ҫ�趨�����ظߣ����
	// ���������BOOL:�����Ƿ����óɹ�
	// �������ڣ�
	// �޸����ڣ�08.09.11
	// �� �ߣ�edit:alzq
	// ����˵���������б��е�pImage�Ѿ�ָ��һ����Ч�ĵ�ַ�ռ�,ͼ��������߰�ԭ������������
	//=====================================================================
	static BOOL DoChangeImageSize(Magick::Image * image,		//ͼ�����ָ��
						   UINT nImageWidth,				//ͼ��Ҫ�趨�����ؿ����
						   UINT nImageHeight );				//ͼ��Ҫ�趨�����ظߣ����


	/*
	����ֵ��TRUE��ʾͼ�����ݿ�����DC�ɹ�,FALSE��ʾͼ�����ݿ�����DC���ɹ�
	������Image &inImage				//ͼ�����ݶ���
			CDC &SrcDC 					//ͼ�񿽱���ȥ��DC
	*/
	static BOOL  DoDCSelectObject( Magick::Image * inImage,				//ͼ�����ݶ���
						CDC * SrcDC, 							//ͼ�񿽱���ȥ��DC
						CDC * pDC);	

	//=====================================================================
	// �� �� ����ReadImage
	// �������������ļ���ȡΪָ����С������ͼ
	// ���������FileInfoList * fileInfo
	//			 int width,int height
	// ���������Gdiplus::Image *
	// �������ڣ�08.08.29
	// �޸����ڣ�08.08.29
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static Gdiplus::Image * ReadImage(FileInfoList * fileInfo,int width,int height);

	//=====================================================================
	// �� �� ����Long2Str
	// ������������long������ת��Ϊstring
	// ���������LONG l:��Ҫת��������
	//			 int minSize:��С����
	// ���������string
	// �������ڣ�08.08.29
	// �޸����ڣ�08.08.29
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static string Long2Str(LONG l,int minSize);

	//=====================================================================
	// �� �� ����LockMutex
	// �����������ȴ�������󲢸�����������
	// ���������DWORD dwMilliseconds:�ȴ���ʱ�䣬��λ-����
	// ���������void
	// �������ڣ�08.10.07
	// �޸����ڣ�08.10.07
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static void LockMutex(DWORD dwMilliseconds);

	//=====================================================================
	// �� �� ����UnLockMutex
	// ����������������������
	// ���������void
	// ���������void
	// �������ڣ�08.10.07
	// �޸����ڣ�08.10.07
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static void UnLockMutex();
		

	//=====================================================================
	// �� �� ����Time2Str
	// ������������ʱ������ת��Ϊ�̶����ַ�����ʽ
	// ���������LPSYSTEMTIME time
	// ���������string
	// �������ڣ�08.09.02
	// �޸����ڣ�08.09.02
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static string Time2Str(LPSYSTEMTIME time);
		

	//=====================================================================
	// �� �� ����GetFileType
	// ���������������ļ���չ���ó��ļ�����
	// ���������string exName:�ļ���չ��
	// ���������string
	// �������ڣ�08.09.02
	// �޸����ڣ�08.09.02
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static string GetFileType(string exName);
		

	//=====================================================================
	// �� �� ����InitExifMap
	// ������������ʼ��EXIF��Ϣ��ش洢����
	// ���������void
	// ���������void
	// �������ڣ�08.09.04
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static void InitExifMes(void);
		

	//=====================================================================
	// �� �� ����CreateExifInfoItem
	// ��������������һ��ExifInfoValueItem����
	// ���������String itemName,int dealMethod,String value;
	// ���������ExifInfoValueItem
	// �������ڣ�08.09.04
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static ExifInfoValueItem CreateExifInfoItem(string itemName,int dealMethod,string value);
		

	//=====================================================================
	// �� �� ����DealExifValue
	// ��������������EXIF��ITEM���ƴ���EXIFֵ
	// ���������string itemName:ITEM����
	//			 string value:ITEMֵ
	// ���������ExifInfoValueItem
	// �������ڣ�08.09.04
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static ExifInfoValueItem DealExifValue(string itemName,string value);
		

	//=====================================================================
	// �� �� ����DealExifMatch
	// ������������EXIF��Ϣ����Ҫ������ַ������м���
	// ���������string str
	// ���������string
	// �������ڣ�08.09.04
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static string DealExifMatch(string str);
		

	//=====================================================================
	// �� �� ����Number2Str
	// ����������������ת��ΪString�������涨С��λ
	// ���������double num,int maxS
	// ���������string
	// �������ڣ�08.09.04
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static string Number2Str(double num,int maxS);
		

	//=====================================================================
	// �� �� ����DeleteThread
	// ���������������߳�
	// ���������HANDLE handle:��Ҫ�������߳̾��
	// ���������void
	// �������ڣ�08.09.15
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static void DeleteThread (HANDLE handle);

	//=====================================================================
	// �� �� ����LowStr
	// �������������ַ���ȫ��ת��ΪСд
	// ���������string &str
	// ���������void
	// �������ڣ�08.09.24
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static void LowStr( string &str );

	//=====================================================================
	// �� �� ����CreateShortcut
	// �������������ַ���ȫ��ת��ΪСд
	// ���������LPCSTR szPath:��ݷ�ʽ����·��-������.lnk��β
	//			 LPCSTR szLink:ָ����ļ�·��
	// ���������BOOL
	// �������ڣ�08.10.07
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	static BOOL CreateLink(LPCSTR szPath,LPCSTR szLink);
	//=====================================================================
	// �� �� ����CutOrCopyFiles
	// ����������lpBuffer���ļ������б�uBufLen:�ַ������ȣ�bCopy����Ϊ���ƣ���Ϊ����
	// ���������
	// ���������void
	// �������ڣ�2008.10.8
	// �޸�����:
	// �� �ߣ�   jiangxh
	// ����˵���� 
	//=====================================================================
	static void PublicFunc::CutOrCopyFiles(char *lpBuffer,UINT uBufLen,BOOL bCopy);

	//=====================================================================
	// �� �� ����ReadShortcut
	// ����������
	// ���������
	// ���������void
	// �������ڣ�2008.10.10
	// �޸�����:
	// �� �ߣ�   jiangxh
	// ����˵���� 
	//=====================================================================
	static bool   ReadShortcut(LPWSTR   lpwLnkFile,   LPSTR   lpDescFile); 

	//=====================================================================
	// �� �� ����ReadImageList
	// ������������ָ��·����ȡCImageList
	// ���������CString imgPath,CImageList * list,int width,int height,int count
	// ���������void
	// �������ڣ�2008.10.13
	// �޸�����:
	// �� �ߣ�   alzq
	// ����˵���� 
	//=====================================================================
	static void   ReadImageList(CString imgPath,CImageList * list);

};

 
 


