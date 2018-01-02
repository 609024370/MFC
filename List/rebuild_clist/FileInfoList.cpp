#include "StdAfx.h"
#include "FileInfoList.h"
#include "PublicFunc.h"
#include "ImgBaseFunc.h"

FileInfoList::FileInfoList(void)
{
	m_filUpItem=NULL;								//��������һ���ֵ
	m_filNextItem=NULL;								//��������һ���ֵ
	m_imgSmallPhotoImage=NULL;						//�������ͼ�ļ�
}

FileInfoList::~FileInfoList(void)
{
	//if(m_imgSmallPhotoImage!=NULL)
	//	{delete m_imgSmallPhotoImage;}		//�������ͼ�ļ�

}
	

//=====================================================================
// �� �� ����FileInfoList
// ��������������������ļ�����·�����Ƿ��ļ��г�ʼ�������Ϣ
// ���������string fileFullPath:�ļ�ȫ·��
//			 bool isDirectory:�Ƿ��ļ���
//			 bool isPhoto:�Ƿ�ͼ��
//			 LONG fileLength:�ļ�����
// ���������
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
FileInfoList::FileInfoList(string fileFullPath,UINT fileType,LONG fileLength)
{
	int mark_1;					//�ļ�����·�������һ��'/'��'\'λ��
	int fileNameLen;			//�ļ���չ������
	mark_1=(int)fileFullPath.find_last_of("\\/");

	m_uiFileType=fileType;

	m_sFileFullPath=fileFullPath;
	m_sFileName=string(fileFullPath,mark_1+1);
	m_sFilePath=string(fileFullPath,0,mark_1+1);
	if(!CheckFileType(FILE_FLODER))
	{
		//�������ļ���ʱ����ȡ��չ����
		fileNameLen=(int)m_sFileName.find_last_of(".");
		if(fileNameLen>=0)
		{
			m_sFileExtName=string(m_sFileName,fileNameLen+1);
			PublicFunc::LowStr(m_sFileExtName);
		}
		else
		{
			fileNameLen=(int)(m_sFileName.length());
			m_sFileExtName="";
		}
	}
	else
	{
		m_sFileExtName="";
	}

	m_iFloderCode=0;

	m_sFileSize="";									//�ļ���С
	m_sFileType="";									//�ļ�����
	m_sFileCreateTime="";							//�ļ�����ʱ��
	m_sFileEditTime="";								//�ļ��޸�ʱ��
	m_sFileOpenTime="";								//�ļ�����ʱ��
	//ͼ���С
	if(fileLength==0)
	{
		m_sFileSize="";
	}
	else
	{
		m_sFileSize=PublicFunc::Long2Str(fileLength/1024,0)+"KB";
	}
	m_sTakePhotoTime="";							//����ʱ��

	//��������ĳ�ʼ��
	m_bNeedGetInfo=true;							//�Ƿ���Ҫ��ȡ�ļ���Ϣ
	m_bNeedGetBaseInfo=true;						//�Ƿ���Ҫ��ȡ�ļ�������Ϣ
	m_bNeedGetSmallPhoto=true;						//�Ƿ���Ҫ��ȡ����ͼ
	m_bSmallPhotoEnable=false;						//����ͼ�Ƿ���Ч
	m_bFileEnable=true;								//�ļ��Ƿ���Ч���ļ����������Ƿ���Ч
	m_uiState=0;									//item״̬

	m_filUpItem=NULL;								//��������һ���ֵ
	m_filNextItem=NULL;								//��������һ���ֵ
	m_imgSmallPhotoImage=NULL;						//�������ͼ�ļ�
	m_iPhotoWidth=0;								//ͼ����
	m_iPhotoHeight=0;								//ͼ��߶�
	m_iRealPhotoWidth=0;							//ͼ��ʵ�ʿ��
	m_iRealPhotoHeight=0;							//ͼ��ʵ�ʸ߶�
	m_iNIcon=-1;									//��ϵͳͼ���е�λ�ñ��
	m_iGroupId=-1;									//��������ID
	m_iPhotoLevel=0;								//ͼƬ�����ȼ����
	m_iPhotoTypeCode=0;								//ͼƬ����������

	//������ʾ��ĳ�ʼ��
	m_iiItemInfo.nItem=-1;
	m_iiItemInfo.photoHeight=0;
	m_iiItemInfo.photoWidth=0;
	m_iiItemInfo.printPos=CPoint(0,0);
	m_iiItemInfo.reDrawEnable=true;
	m_iiItemInfo.state=0;
	m_iiItemInfo.style=-1;
}
	

//=====================================================================
// �� �� ����GetFileName
// ���������������ļ���
// ���������void
// ���������string
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
string FileInfoList::GetFileName()
{
	return m_sFileName;
}
	

//=====================================================================
// �� �� ����GetFilePath
// ���������������ļ�·��
// ���������void
// ���������string
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
string FileInfoList::GetFilePath()
{
	return m_sFilePath;
}
	

//=====================================================================
// �� �� ����GetFileExtName
// ���������������ļ���չ��
// ���������void
// ���������string
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
string FileInfoList::GetFileExtName()
{
	return m_sFileExtName;
}
	

//=====================================================================
// �� �� ����GetFileFullPath
// ���������������ļ�����·��
// ���������void
// ���������string
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
string FileInfoList::GetFileFullPath()
{
	return m_sFileFullPath;
}
	

//=====================================================================
// �� �� ����GetFileBaseInfo
// ������������ȡ�ļ�������Ϣ�е�ĳһ��
// ���������int INFO_TYPE:�ڱ��ļ���ͷ�Ժ궨��
// ���������string
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
string FileInfoList::GetFileBaseInfo(int INFO_TYPE)
{
	switch(INFO_TYPE)
	{
	case FILE_NAME:
		return m_sFileName;
	case FILE_SIZE:
		return m_sFileSize;
	case FILE_TYPE:
		return m_sFileType;
	case FILE_CREATE_TIME:
		return m_sFileCreateTime;
	case FILE_EDIT_TIME:
		return m_sFileEditTime;
	case FILE_CHANGE_TIME:
		return m_sFileEditTime;
	case FILE_PHOTO_SIZE:
		return m_sPhotoSize;
	case FILE_TAKE_PHOTO_TIME:
		return m_sTakePhotoTime;
	default:
		return "";
	}
}
	

//=====================================================================
// �� �� ����SetFileType
// ���������������ļ�����
// ���������UINT
// ���������void
// �������ڣ�08.10.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoList::SetFileType(UINT type)
{
	m_uiFileType=type;
}
	

//=====================================================================
// �� �� ����CheckFileType
// �����������ж��ļ�����
// ���������UINT
// ���������BOOL
// �������ڣ�08.10.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
BOOL FileInfoList::CheckFileType(UINT type)
{
	return m_uiFileType & type;
}
	

//=====================================================================
// �� �� ����SetFileName
// ���������������ļ���
// ���������string
// ���������void
// �������ڣ�08.10.07
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoList::SetFileName(string fileName)
{
	m_sFileName=fileName;
}
	

//=====================================================================
// �� �� ����GetSmallPhotoImage
// ������������ȡ����ͼ�ļ�
// ���������void
// ���������Image *
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
Gdiplus::Image * FileInfoList::GetSmallPhotoImage()
{
	return m_imgSmallPhotoImage;
}
	

//=====================================================================
// �� �� ����GetFileBaseInfo
// ������������ȡ�ļ�������Ϣ
// ���������void
// ���������BOOL:���ض�ȡ�Ƿ�ɹ�
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
BOOL FileInfoList::GetFileBaseInfo()
{
	try
	{
		/**
		*	��ȡ�ļ�������Ϣ
		*/
		//��ȡ�ļ���С

		//��ȡ�ļ��������޸ģ�������ʱ��
		WIN32_FILE_ATTRIBUTE_DATA fileTimeData;
		SYSTEMTIME ftCreationTime;
		SYSTEMTIME ftLastWriteTime;
		SYSTEMTIME ftLastAccessTime;
		GetFileAttributesEx(m_sFileFullPath.c_str(),GetFileExInfoStandard,&fileTimeData);	//��ȡ����ʱ��
		FileTimeToSystemTime(&fileTimeData.ftCreationTime,&ftCreationTime);					//ת������ʱ��
		FileTimeToSystemTime(&fileTimeData.ftLastWriteTime,&ftLastWriteTime);				//ת���޸�ʱ��
		FileTimeToSystemTime(&fileTimeData.ftLastAccessTime,&ftLastAccessTime);				//ת��������ʱ��

		//������ʱ������������MAP��
		m_sFileCreateTime=PublicFunc::Time2Str(&ftCreationTime);
		m_sFileEditTime=PublicFunc::Time2Str(&ftLastWriteTime);
		m_sFileEditTime=PublicFunc::Time2Str(&ftLastAccessTime);
		
		if(m_iNIcon==-1)
		{
			SHFILEINFO shfi;
			SHGetFileInfo((m_sFileFullPath.c_str()),
			        0,
			        &shfi,
			        sizeof(SHFILEINFO),
					SHGFI_DISPLAYNAME | SHGFI_TYPENAME | SHGFI_LARGEICON | SHGFI_ICON);
			m_iNIcon=shfi.iIcon;
		}

		m_bNeedGetBaseInfo=false;

		return TRUE;
	}
	catch(Error e)
	{
		AfxMessageBox(e.what());
		return FALSE;
	}
}
	

//=====================================================================
// �� �� ����LoadExifInfo
// ��������������Exif��Ϣ
// ���������void
// ���������void
// �������ڣ�08.09.16
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoList::LoadExifInfo()
{
	Magick::Image image(m_sFileFullPath);
	CImgBaseFunc cimgbasefunc;
	m_mssInfoMap=cimgbasefunc.GetImgExifDatas(image);

	m_bNeedGetInfo=false;
}
	

//=====================================================================
// �� �� ����CreateSmallImage
// ������������image�ļ���������
// ���������int width,int height
// ���������BOOL:�����Ƿ�ɹ�
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
BOOL FileInfoList::CreateSmallImage(int width,int height)
{
	try
	{
		//�������ݿ⣬��ѯ�Ƿ����ͬ·����ͬ�ļ���������ͼ

		USES_CONVERSION;
		Gdiplus::Image * image=new Gdiplus::Image(A2W(m_sFileFullPath.c_str()));

		if(image==NULL)
		{
			delete image;
			return FALSE;
		}

		m_iRealPhotoWidth=image->GetWidth();		//ͼ��ʵ�ʿ��
		m_iRealPhotoHeight=image->GetHeight();	//ͼ��ʵ�ʸ߶�
		double scaleW=(double)(m_iRealPhotoWidth)/width;
		double scaleH=(double)(m_iRealPhotoHeight)/height;
		double scale=scaleW>scaleH?scaleW:scaleH;
		if(scale>1)
		{
			m_iPhotoWidth=(LONG)(m_iRealPhotoWidth/scale);
			m_iPhotoHeight=(LONG)(m_iRealPhotoHeight/scale);
		}
		else
		{
			m_iPhotoWidth=m_iRealPhotoWidth;
			m_iPhotoHeight=m_iRealPhotoHeight;
		}

		Gdiplus::Image * tmpImg=image->GetThumbnailImage(m_iPhotoWidth,m_iPhotoHeight);
		//Gdiplus::Image * tmpImg=PublicFunc::ReadImage(this,200,160);

		if(tmpImg==NULL)
		{
			delete image;
			return FALSE;
		}

		m_imgSmallPhotoImage=tmpImg;

		delete image;
		return TRUE;
	}
	catch(Exception ex)
	{
		AfxMessageBox(_T(ex.what()));
		return FALSE;
	}
	catch (Magick::Error & e)
	{
		AfxMessageBox(_T(e.what()));
		return FALSE;
	}
}
	

//=====================================================================
// �� �� ����ISetFileName
// ���������������ļ���
// ���������string fileNewName:�µ��ļ�����������·��
// ���������BOOL:�����Ƿ����óɹ�
// �������ڣ�08.09.10
// �޸����ڣ�alzq 08.10.09
// �� �ߣ�alzq
// ����˵����
//=====================================================================
BOOL FileInfoList::ISetFileName(string fileNewName)
{
	//ʵ�ֺ���
	//��ȡԭ�ļ�·��
	string newFullPath=m_sFilePath;
	//�������ļ�����·��
	newFullPath.append(fileNewName);
	//�������ļ�
	int i=rename(m_sFileFullPath.c_str(),newFullPath.c_str());
	//�����µ��ļ���Ϣ
	m_sFileFullPath=newFullPath;
	m_sFileName=fileNewName;

	//����������չ��
	if(!CheckFileType(FILE_FLODER))
	{
		//�������ļ���ʱ����ȡ��չ����
		int fileNameLen=(int)m_sFileName.find_last_of(".");
		if(fileNameLen>=0)
		{
			m_sFileExtName=string(m_sFileName,fileNameLen+1);
			PublicFunc::LowStr(m_sFileExtName);
		}
		else
		{
			m_sFileExtName="";
		}
	}
	else
	{
		m_sFileExtName="";
	}

	return TRUE;
}
	

//=====================================================================
// �� �� ����ISetFileNameAndExtName
// ���������������ļ�������չ��
// ���������string fileNewName:�µ��ļ�����������·��
// ���������BOOL:�����Ƿ����óɹ�
// �������ڣ�08.09.10
// �޸����ڣ�alzq 08.10.09
// �� �ߣ�alzq
// ����˵����
//=====================================================================
BOOL FileInfoList::ISetFileNameAndExtName(string fileNewName)
{
	if(ISetFileName(fileNewName))
	{
		//�޸ĳɹ�ʱ����������չ��
		if(!CheckFileType(FILE_FLODER))
		{
			//�������ļ���ʱ����ȡ��չ����
			int fileNameLen=(int)m_sFileName.find_last_of(".");
			if(fileNameLen>=0)
			{
				m_sFileExtName=string(m_sFileName,fileNameLen+1);
				PublicFunc::LowStr(m_sFileExtName);
			}
			else
			{
				m_sFileExtName="";
			}
		}
		else
		{
			m_sFileExtName="";
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
	

//=====================================================================
// �� �� ����ICopyFile
// ���������������ļ���·��
// ���������string fileNewPath:���������ļ���·��������"/"
// ���������BOOL:�����Ƿ����óɹ�
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
BOOL FileInfoList::ICopyFile(string fileNewPath,UINT dealType)
{
	//ʵ�ֺ���
	string newFullPath=fileNewPath+m_sFileName;

	if(access(newFullPath.c_str(),0)==0)
	{
		//���ļ�����ʱ�����ݲ�����ʽ���ļ����в���
		if(dealType==DEAL_ASK)
		{
			int res=AfxMessageBox(("�ļ���"+newFullPath+" �Ѿ����ڣ������Ƿ񸲸ǣ�").c_str(),MB_ICONQUESTION|MB_YESNO);
			if(res==IDNO)
			{
				//��ѡ���ʱ
				return FALSE;
			}
		}
		else if(dealType==DEAL_RENAME)
		{
			int n=0;
			do
			{
				n++;
				string s="91����"+n;
				newFullPath=fileNewPath+s+m_sFileName;
			}while(access(newFullPath.c_str(),0)==0);
		}
		else if(dealType==DEAL_PASS)
		{
			//������ʱ��ֱ�ӷ���
			return FALSE;
		}
		//������ʱ����Ҫִ���κβ���
	}

	//���ļ����в��������ļ���ԭ�ļ��м��е���ǰ�ļ���
	CopyFile(m_sFileFullPath.c_str(),newFullPath.c_str(),FALSE);

	return TRUE;
}
	

//=====================================================================
// �� �� ����ICutFile
// ���������������ļ���ĳ�ļ���
// ���������string fileNewPath:���е����ļ���·��������"/"
// ���������BOOL:�����Ƿ����óɹ�
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
BOOL FileInfoList::ICutFile(string fileNewPath,UINT dealType)
{
	//ʵ�ֺ���
	string newFullPath=fileNewPath+m_sFileName;

	if(access(newFullPath.c_str(),0)==0)
	{
		//���ļ�����ʱ�����ݲ�����ʽ���ļ����в���
		if(dealType==DEAL_ASK)
		{
			int res=AfxMessageBox(("�ļ���"+newFullPath+" �Ѿ����ڣ������Ƿ񸲸ǣ�").c_str(),MB_ICONQUESTION|MB_YESNO);
			if(res!=IDYES)
			{
				//��ѡ���ʱ
				return FALSE;
			}
		}
		else if(dealType==DEAL_RENAME)
		{
			int n=0;
			do
			{
				n++;
				string s="91����"+n;
				newFullPath=fileNewPath+s+m_sFileName;
			}while(access(newFullPath.c_str(),0)==0);
		}
		else if(dealType==DEAL_PASS)
		{
			//������ʱ��ֱ�ӷ���
			return FALSE;
		}
		//������ʱ����Ҫִ���κβ���
	}

	//���ļ����в��������ļ���ԭ�ļ��м��е���ǰ�ļ���
	MoveFileEx(m_sFileFullPath.c_str(),newFullPath.c_str(),MOVEFILE_REPLACE_EXISTING);

	return TRUE;
}
	

//=====================================================================
// �� �� ����Dispose
// �����������ͷű��������Դ
// ���������void
// ���������void
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoList::Dispose()
{
 	try
 	{
 		m_mssInfoMap.clear();					//�ļ���Ϣ����MAP
 
 		m_filUpItem=NULL;						//��������һ���ֵ
 		m_filNextItem=NULL;						//��������һ���ֵ
 
 		m_sFileSize.~basic_string();			//�ļ���С
 		m_sFileType.~basic_string();			//�ļ�����
 		m_sFileCreateTime.~basic_string();		//�ļ�����ʱ��
 		m_sFileEditTime.~basic_string();		//�ļ��޸�ʱ��
 		m_sFileOpenTime.~basic_string();		//�ļ�����ʱ��
 		m_sPhotoSize.~basic_string();			//ͼ���С
 		m_sTakePhotoTime.~basic_string();		//����ʱ��
 
 		m_sFileName.~basic_string();			//��������չ�����ļ���
 		m_sFilePath.~basic_string();			//�ļ�·��������"/"
 		m_sFileExtName.~basic_string();			//�ļ���չ��
 		m_sFileFullPath.~basic_string();		//�ļ�����·���������ļ���ʲô��
 
 		if(m_imgSmallPhotoImage!=NULL){delete m_imgSmallPhotoImage;}		//�������ͼ�ļ�
 	}
 	catch(Exception e)
 	{
 		AfxMessageBox(e.what());
 	}
}
	

//=====================================================================
// �� �� ����InsertNext
// �����������ڱ�ITEM֮�����һ��ITEM
// ���������FileInfoList * nextItem:��Ҫ�����ITEMָ��
// ���������BOOL
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
BOOL FileInfoList::InsertNext(FileInfoList * nextItem)
{
	if(this->m_filNextItem!=NULL)
	{
		//����һ�Ϊ������Ҫ������һ��Ļص�ָ��
		this->m_filNextItem->m_filUpItem=nextItem;
	}
	nextItem->m_filNextItem=this->m_filNextItem;
	nextItem->m_filUpItem=this;
	this->m_filNextItem=nextItem;

	return TRUE;
}
	

//=====================================================================
// �� �� ����InsertFront
// �����������ڱ�ITEM֮ǰ����һ��ITEM
// ���������FileInfoList * nextItem:��Ҫ�����ITEMָ��
// ���������BOOL
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵��������TRUE��ʾ�ɹ��ڸ���ǰ���ITEM����Ӱ������ͷ
//			 ����FALSE��ʾ�ɹ����ITEM��������ͷ�Ѿ��ı�
//=====================================================================
BOOL FileInfoList::InsertFront(FileInfoList * nextItem)
{
	if(this->m_filUpItem==NULL)
	{
		//��һ��Ϊ��ʱ��ֻ���������ʱͷָ��ı�ΪnextItem
		nextItem->m_filUpItem=NULL;
		nextItem->m_filNextItem=this;
		this->m_filUpItem=nextItem;
		return FALSE;
	}
	else
	{
		//��һ�Ϊ��ʱ����Ҫ��������
		this->m_filUpItem->m_filNextItem=nextItem;
		nextItem->m_filUpItem=this->m_filUpItem;
		nextItem->m_filNextItem=this;
		this->m_filUpItem=nextItem;
		return TRUE;
	}
}
	

//=====================================================================
// �� �� ����DeleteSelf
// ����������ɾ������
// ���������bool disposeEnable
// ���������FileInfoList * ����ɾ���������һ���ַ
// �������ڣ�08.09.12
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵��������TRUE��ʾ�ɹ�
//			 ����FALSE��ʾ�ɹ����ITEM��������ͷ�Ѿ��ı�
//=====================================================================
FileInfoList * FileInfoList::DeleteSelf(bool disposeEnable)
{
	FileInfoList * res=m_filNextItem;
	if(m_filUpItem==NULL)
	{
		if(m_filNextItem!=NULL)
		{
			m_filNextItem->m_filUpItem=NULL;
		}
	}
	else
	{
		m_filUpItem->m_filNextItem=m_filNextItem;
		if(m_filNextItem!=NULL)
		{
			m_filNextItem->m_filUpItem=m_filUpItem;
		}
	}

	if(disposeEnable)
	{
		Dispose();
	}
	else
	{
		SetState(0,true,0);			//��״̬��0
		m_bFileEnable=false;		//�����ļ�Ϊ��Ч�ļ�
	}

	return res;
}
	

//=====================================================================
// �� �� ����SetState
// ����������ɾ������
// ���������UINT newState:�µ�״ֵ̬
//			 bool changeAll:�Ƿ���ȫ�滻״ֵ̬
//			 UINT mask:����
// ���������UINT �����µ�״̬
// �������ڣ�08.10.07
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
UINT FileInfoList::SetState(UINT newState,bool changeAll,UINT mask)
{
	if(changeAll)
	{
		m_uiState=newState;
	}
	else
	{
		//��λ�����ֱ�����λ����Ϊ0
		m_uiState&=~mask;
		m_uiState|=(newState & mask);
	}

	return m_uiState;
}
	

//=====================================================================
// �� �� ����GetState
// ����������ɾ������
// ���������UINT stateMask:��ȡ״̬�����ֱ���
// ���������UINT ����״̬
// �������ڣ�08.10.07
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
UINT FileInfoList::GetState(UINT stateMask)
{
	UINT tmpState=m_uiState & stateMask;
	return tmpState;
}
