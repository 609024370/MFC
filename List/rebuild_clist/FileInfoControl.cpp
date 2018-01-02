#include "StdAfx.h"
#include "FileInfoControl.h"

FileInfoControl::FileInfoControl(void)
{
	m_filFileListHeader = NULL;
	m_filFileListEnder = NULL;
	m_filLastGetFileInfoP = NULL;			//����ȡ���ļ���ָ�룬��λ�����ʹ�üӿ������ٶ�
	m_filLoadImageBegin = NULL;				//����Image����Ŀ�ʼλ��ָ��
	InitFileInfoControl();
}

FileInfoControl::~FileInfoControl(void)
{
	DisposeChoose();
	if(m_filFileListHeader)
		delete m_filFileListHeader;
	if(m_filFileListEnder)
		delete m_filFileListEnder;

}
	

//=====================================================================
// �� �� ����GetHeader
// ������������ȡͷָ��
// ���������void
// ���������FileInfoList *
// �������ڣ�08.09.15
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
FileInfoList * FileInfoControl::GetHeader()
{
	return m_filFileListHeader;
}
	

//=====================================================================
// �� �� ����GetEnder
// ������������ȡβָ��
// ���������void
// ���������FileInfoList *
// �������ڣ�08.09.15
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
FileInfoList * FileInfoControl::GetEnder()
{
	return m_filFileListEnder;
}
	

//=====================================================================
// �� �� ����GetSmallPhotoMaxWidth
// ������������ȡ����ͼ�����
// ���������void
// ���������bool
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::GetSmallPhotoMaxWidth()
{
	return m_iSmallPhotoMaxWidth;
}
	

//=====================================================================
// �� �� ����GetIsPhoto
// ������������ȡ����ͼ���߶�
// ���������void
// ���������bool
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::GetSmallPhotoMaxHeight()
{
	return m_iSmallPhotoMaxHeight;
}
	

//=====================================================================
// �� �� ����SetSmallPhotoMaxSize
// ������������������ͼ���ߴ�
// ���������int width,int height
// ���������void
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::SetSmallPhotoMaxSize(int width,int height)
{
	m_iSmallPhotoMaxWidth=width;
	m_iSmallPhotoMaxHeight=height;
}
	

//=====================================================================
// �� �� ����InitFileInfoControl
// ������������ʼ���ļ���Ϣ������ƶ���
// ���������void
// ���������void
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵�����������ʼ������������ṹ�������ļ�ɸѡ��MAP�����ļ����Ͷ�ӦMAP��
//=====================================================================
void FileInfoControl::InitFileInfoControl()
{
	m_filFileListHeader=new FileInfoList();								//�洢�ļ�������Ϣ��ͷָ��
	m_filFileListHeader->InsertNext(new FileInfoList());				//��ͷָ������һ����ָ����Ϊβָ��
	m_filFileListEnder=m_filFileListHeader->m_filNextItem;				//�洢�ļ�������Ϣ��βָ��

	m_bFileChooseEnable=false;											//�Ƿ�ɸѡ�ļ��Ŀ��Ʊ���
	m_bLoadImagePosEnable=false;										//����Image�����λ���Ƿ���Ч
	m_bLoadBaseInfoEnable=false;										//����λ�ñ��������������Ϣ�Ƿ���Ч
	m_bOrderByGroup=false;												//�Ƿ�����ļ�����

	m_iTotalCount=0;													//�����ļ���ͳ�ƶ���
	m_iFilePathCount=0;													//ѡ����ļ���ͳ��
	m_iFilePathCode=0;													//ѡ����ļ��б�ţ��ۼӲ���֮ǰ�ظ�
	m_iMaxSearchDeep=0;													//����������
	m_iOrderType=1;														//�Ѿ����е���������
	m_iOrderItem=0;														//�Ѿ����е��������Զ�����
	m_iGroupType=0;														//���鷽ʽ
	m_iGroupCount=0;													//��������ͳ��

	m_iSmallPhotoMaxWidth=0;											//����ͼ�������
	m_iSmallPhotoMaxHeight=0;											//����ͼ�����߶�

	m_iFoucFileCode=-1;													//���н����ITEM�ı��
	m_filFoucFile=m_filFileListHeader;									//���н����ITEM��FILEָ��

	//��Ϊ�ӿ�����ٶȵı�����ʼ��
	_ResetSearchItems();

	m_iLoadImagePos=0;
	m_filLoadImageBegin=m_filFileListHeader->m_filNextItem;

	//�ļ�����ɸѡ��map��ʼ��
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("jpg",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("gif",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("bmp",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("tif",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("tiff",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("png",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("ico",true));

	//�ļ���չ����Ӧ�ļ����͵�map��ʼ��
	m_mssFileExtName2Type.insert(MapStringString::value_type("exe","��ִ���ļ�"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("bmp","windows λͼ"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("jpg","jpgͼ��"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("gif","gifͼ��"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("tiff","tiffͼ��"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("png","pngͼ��"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("ico","icoͼ��"));

	//�Ѿ�ѡȡ���ļ��м���map��ʼ��
	m_msiFilePathMap.clear();
}
	

//=====================================================================
// �� �� ����SearchAddFile
// �������������Ҳ�����ļ���
// ���������string floderPath:�ļ��е�·����"/"
//			 int searchDeep:��ǰ��Ѱ���
//			 int maxDeep:�����Ѱ���
// ���������void
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵������maxDeepΪ-1ʱΪ������ȵı�������searchDeep��maxDeep��Ϊ0ʱֻ������ǰ�ļ�����
//=====================================================================
void FileInfoControl::SearchAddFile(string floderPath,int searchDeep,int maxDeep)
{
	//�����ļ����Ƿ��ڱ�ѡ�񼯺����ж��ļ������ļ��Ƿ�Ӧ�ñ����
	bool AddFileEnable=m_msiFilePathMap[floderPath]==NULL?true:false;
	//��������
	CFileFind findfile;
	//��Ϊ�ӿ�����ٶȵı�����ʼ��
	_ResetSearchItems();
	//���ļ��м�����ѡ�����
	int floderCode=0;							//�ļ��б��
	if(AddFileEnable)
	{
		floderCode=AddSelectedFloder(floderPath);
	}

	if(floderPath.compare("�ҵĵ���\\")==0)
	{
		//��ѡ���ҵĵ���ʱ�������ļ���ʽ�������ļ���ͬ
		size_t szAllDriveStrings = GetLogicalDriveStrings(0,NULL);
		char * pDriveStrings = new char[szAllDriveStrings + sizeof(_T(""))];
		char * head=pDriveStrings;
		GetLogicalDriveStrings(szAllDriveStrings,pDriveStrings);
		size_t szDriveString = strlen(pDriveStrings);
		while(szDriveString > 0)
		{
			if(AddFileEnable)
			{
				//����������ļ�ʱ
				FileInfoList * file=_AddFile(string(pDriveStrings,strlen(pDriveStrings)-1),FILE_DISK,floderCode,0);
				file->SetFileName("���ش��� "+file->GetFileName());
			}
			
			pDriveStrings += szDriveString + 1;
			szDriveString = strlen(pDriveStrings);
		}
		delete head;
	}
	else
	{
		//�ж��Ƿ����ļ�
		floderPath=floderPath+"*.*";
		BOOL bfind=findfile.FindFile(floderPath.c_str());
		if(!bfind){return ;}		//�ļ�����û���ļ��򷵻�

		BOOL fileEnd=1;						//�Ƿ񵽴������ļ���ĩβ
		
		while(fileEnd)
		{
			fileEnd=findfile.FindNextFileA();
			//����ѯ��һ���ļ��ɹ�ʱ
			if(findfile.IsDots())
			{
				//Ϊ�ϼ�Ŀ¼��Ŀ¼
				//���ļ���Ϊ.����..ʱ������
			}
			else if(findfile.IsDirectory())
			{
				//��Ϊ�ļ���ʱ��ӽ��ļ�����Ȼ���ж��Ƿ���Ҫ�ݹ�
				if(AddFileEnable)
				{
					_AddFile(findfile.GetFilePath().GetBuffer(0),FILE_FLODER,floderCode,0);
				}
				
				//��δ���������������ʱ
				if(searchDeep<maxDeep || maxDeep==-1)
				{
					//����Ҫ��ѯ���ļ���ʱ,��ʼ�ݹ�
					SearchAddFile(findfile.GetFilePath().GetBuffer(0),searchDeep+1,maxDeep);
				}
			}
			//else��˵�����ļ�
			else
			{
				if(AddFileEnable)
				{
					//��Ϊ�ļ�ʱ��ӽ��ļ�����,�ں������������ļ���չ����ɸѡ�����Բ��ڴ˽���ɸѡ
					_AddFile(findfile.GetFilePath().GetBuffer(0),FILE_OHTER,floderCode,(LONG)(findfile.GetLength()));
				}
			}
		}
	}
}
	

//=====================================================================
// �� �� ����AddFile
// ��������������ļ�
// ���������string filePath:�ļ���·����"/"
//			 int floderCode:�����ļ������ļ��м����еı��
// ���������void
// �������ڣ�08.10.06
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
FileInfoList * FileInfoControl::AddFile(string filePath,int floderCode)
{
	
	DWORD type=GetFileAttributes(filePath.c_str());
	type &= FILE_ATTRIBUTE_DIRECTORY;

	long fileLen=0;
	if(!type)
	{
		CFileFind ff;
		ff.FindFile(filePath.c_str());
		ff.FindNextFileA();
		fileLen=ff.GetLength();
		ff.Close();
	}

	//��Ϊ�ļ�ʱ��ӽ��ļ�����,�ں������������ļ���չ����ɸѡ�����Բ��ڴ˽���ɸѡ
	return _AddFile(filePath,type,floderCode,fileLen);
}
	

//=====================================================================
// �� �� ����AddFile
// ��������������ļ�
// ���������string filePath,string floderPath
// ���������
// �������ڣ�08.10.07
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
FileInfoList * FileInfoControl::AddFile(string filePath,string floderPath)
{
	int floderCode=m_msiFilePathMap[floderPath];
	if(floderCode)
	{
		return AddFile(filePath,floderCode);
	}
	
	return NULL;
}
	

//=====================================================================
// �� �� ����AddFile
// ��������������ļ�
// ���������string filePath
// ���������
// �������ڣ�08.10.07
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
FileInfoList * FileInfoControl::AddFile(string filePath)
{
	_ResetSearchItems();
	int mark=(int)filePath.find_last_of("\\/");

	string floderPath=string(filePath,0,mark+1);
	return AddFile(filePath,floderPath);
}
	

//=====================================================================
// �� �� ����SearchDelFloderCodes
// ���������������ļ������Ѿ�ѡ����ļ��б�ż���
// ���������string floderPath:�ļ��е�·����"/"
//			 int searchDeep:��ǰ��Ѱ���
//			 int maxDeep:�����Ѱ���
//			 bool delMapIter:�Ƿ�ɾ����ѡ�����е��ļ������ļ�����
//			 VectorInt resVI:��Ѱ���Ľ���ļ���
// ���������void
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵���������������ҪӦ������ɾ��ѡȡ���ļ���ʱʹ�õ�
//=====================================================================
void FileInfoControl::SearchDelFloderCodes(string floderPath,int searchDeep,int maxDeep,bool delMapIter,VectorInt * resVI)
{
	int code=SearchDelSelectedFloder(floderPath,delMapIter);
	if(code!=-1)
	{
		//����ѡ���ļ��м������в�ѯ�����ļ���
		if(resVI!=NULL)
			resVI->push_back(code);
	}

	if(searchDeep<maxDeep || maxDeep==-1)
	{
		//��δ����������ʱ�������Ӷ���
		CFileFind findfile;
		//�ж��Ƿ����ļ�
		floderPath=floderPath+"*.*";
		BOOL bfind=findfile.FindFile(floderPath.c_str());
		if(!bfind){return ;}		//�ļ�����û���ļ��򷵻�
		
		while(findfile.FindNextFileA())
		{
			//����ѯ��һ���ļ��ɹ�ʱ
			if(findfile.IsDirectory())
			{
				//����Ҫ��ѯ���ļ���ʱ,��ʼ�ݹ�
				SearchDelFloderCodes(findfile.GetFilePath().GetBuffer(0),searchDeep+1,maxDeep,delMapIter,resVI);
			}
		}
	}
}
	

//=====================================================================
// �� �� ����JudgeAllSelected
// �����������ж��ļ����£��涨����ڣ��Ƿ���ȫ��ѡ��
// ���������string floderPath:�ļ��е�·����"/"
//			 int searchDeep:��ǰ��Ѱ���
//			 int maxDeep:�����Ѱ���
// ���������bool ����ĳ�ļ����£�����ȷ�Χ�ڣ��Ƿ���δ��ѡ����
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵��������true��ʾȫ��ѡ�У�����false��ʾ��δѡ����
//=====================================================================
bool FileInfoControl::JudgeAllSelected(string floderPath,int searchDeep,int maxDeep)
{
	if(!m_msiFilePathMap[floderPath])
	{
		//����ѡ���ļ��м������޲�ѯ�����ļ���
		return false;
	}

	if(searchDeep<maxDeep || maxDeep==-1)
	{
		//��δ����������ʱ�������Ӷ���
		CFileFind findfile;
		//�ж��Ƿ����ļ�
		floderPath=floderPath+"*.*";
		BOOL bfind=findfile.FindFile(floderPath.c_str());
		if(!bfind){return true;}		//�ļ�����û���ļ��򷵻�
		
		while(findfile.FindNextFileA())
		{
			//����ѯ��һ���ļ��ɹ�ʱ
			if(findfile.IsDirectory())
			{
				//����Ҫ��ѯ���ļ���ʱ,��ʼ�ݹ�
				if(!JudgeAllSelected(findfile.GetFilePath().GetBuffer(0),searchDeep+1,maxDeep))
				{
					return false;
				}
			}
		}
	}

	return true;
}
	

//=====================================================================
// �� �� ����OpenFloder
// ������������һ���ļ���
// ���������string  floderPath:�ļ��е�·����"/"
//			 int maxDeep:�����Ѱ���
// ���������void
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::OpenFloder(string  floderPath,int maxDeep)
{
	//������ֹ��ȡ�̵߳ȷ���Ĳ���


	//����Ѿ���ȡ���ļ�����
	DisposeChoose();

	//�����ļ���·����ȡ�ļ�����ӽ��ļ�����
	SearchAddFile(floderPath,0,maxDeep);
	if(m_iTotalCount>0)
	{
		m_iFoucFileCode=0;
		m_filFoucFile=m_filFileListHeader->m_filNextItem;
	}
	else
	{
		m_iFoucFileCode=-1;
		m_filFoucFile=m_filFileListHeader;
	}

	//��������߳�


}
	

//=====================================================================
// �� �� ����AddFloder
// �������������һ���ļ����е��ļ���������
// ���������string  floderPath:�ļ��е�·����"/"
//			 int maxDeep:�����Ѱ���
// ���������void
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::AddFloder(string  floderPath,int maxDeep)
{
	//������ֹ��ȡ�̵߳ȷ���Ĳ���


	//�����ļ���·����ȡ�ļ�����ӽ��ļ�����
	SearchAddFile(floderPath,0,maxDeep);

	//��������߳�


}
	

//=====================================================================
// �� �� ����AddSelectedFloder
// �������������һ���ļ��е���ѡ�ļ���MAP��
// ���������string  floderPath:�ļ���·��
// ���������int:�����ļ��еı��
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::AddSelectedFloder(string floderPath)
{
	m_iFilePathCount++;
	m_iFilePathCode++;
	m_msiFilePathMap[floderPath]=m_iFilePathCode;

	return m_iFilePathCode;
}
	

//=====================================================================
// �� �� ����SearchDelSelectedFloder
// ��������������ѡ�ļ���MAP�в���һ���ļ��У������ݲ���ѡ���Ƿ�ɾ���ļ������ļ�
// ���������string  floderPath:�ļ���·��
// ���������int ���ظ��ļ�������ѡ�����еı�ţ�Ϊ-1�򲻴���
//			 bool delSelectedFloder:�Ƿ��ڼ�����ɾ�����ļ��У��Լ��ļ������ļ�
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::SearchDelSelectedFloder(string floderPath,bool delSelectedFloder)
{
	if(m_msiFilePathMap[floderPath])
	{
		int code=m_msiFilePathMap[floderPath];
		if(delSelectedFloder)
		{
			//����Ҫɾ���ļ����ļ���ʱ
			m_iFilePathCount--;
			m_msiFilePathMap.erase(m_msiFilePathMap.find(floderPath));
			m_migiGroupMap.erase(m_migiGroupMap.find(code));

			//��������������Ϊͷָ���һ�����󣬼�ʵ�ʵĿ�ʼ����
			FileInfoList * iter=m_filFileListHeader->m_filNextItem;
			//��ʼѭ��ɾ����Ч����
			while(iter!=m_filFileListEnder)
			{
				//������δ���������βʱ
				if(iter->m_iFloderCode==code)
				{
					iter=_DelFile(iter,true);
				}
				else
				{
					iter=iter->m_filNextItem;
				}
			}
			//��ʼѭ��ɾ����Ч����
			iter=m_filFileListEnder->m_filNextItem;
			while(!iter)
			{
				//������δ���������βʱ
				if(iter->m_iFloderCode==code)
				{
					iter=_DelFile(iter,true);
				}
				else
				{
					iter=iter->m_filNextItem;
				}
			}
		}
		return code;
	}
	else
	{
		return -1;
	}
}
	

//=====================================================================
// �� �� ����DisposeChoose
// ��������������Ϊ��ѡ����
// ���������void
// ���������void
// �������ڣ�08.09.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::DisposeChoose()
{
	//��������������Ϊͷָ���һ�����󣬼�ʵ�ʵĿ�ʼ����
	if(m_filFileListHeader == NULL)
		return;
 	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	FileInfoList * tmpIter=NULL;
	//��ʼѭ��ɾ������

	//ɾ����������Ч����
	while(iter!=NULL && iter!=m_filFileListEnder)
	{
		//������δ���������βʱ
		tmpIter=iter->m_filNextItem;
		iter->Dispose();
		delete iter;
		iter=tmpIter;
	}
	//ɾ����������Ч����
	iter=m_filFileListEnder->m_filNextItem;
	while(iter)
	{
		//������δ���������βʱ
		tmpIter=iter->m_filNextItem;
		iter->Dispose();
		delete iter;
		iter=tmpIter;
	}

	//������ͷ����β�����м������������
	m_filFileListHeader->m_filNextItem=m_filFileListEnder;
	m_filFileListEnder->m_filUpItem=m_filFileListHeader;
	m_filFileListEnder->m_filNextItem=NULL;

	m_iTotalCount=0;								//�����ļ�ѡ���ͳ��
	m_iFilePathCount=0;								//ѡ����ļ���ͳ��
	m_msiFilePathMap.clear();						//�Ѿ�ѡ����ļ��еļ���MAP

	//��Ϊ�ӿ�����ٶȵı�����ʼ��
	_ResetSearchItems();
}
	

//=====================================================================
// �� �� ����DelFloder
// ����������ɾ���ļ�������һ���ļ��е��ļ�
// ���������string  floderPath:�ļ��е�·����"/"
//			 int maxDeep:�����Ѱ���
// ���������void
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::DelFloder(string  floderPath,int maxDeep)
{
	//��Ϊ�ӿ�����ٶȵı�����ʼ��
	_ResetSearchItems();

	//������ȷ�Χ�ڵ����б�ѡ���ļ��У����ڼ�����ɾ�����ļ�����
	SearchDelFloderCodes(floderPath,0,maxDeep,true,NULL);
}
	

//=====================================================================
// �� �� ����DelFile
// ������������������ɾ��һ���ļ�
// ���������FileInfoList * fileIter:�ļ��������ж���
//			 ,bool disposeEnable:�Ƿ��ͷ���Դ
// ���������FileInfoList * ����ɾ���������һ���ַ
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
FileInfoList * FileInfoControl::_DelFile(FileInfoList * fileIter,bool disposeEnable)
{
	if(fileIter->m_bFileEnable)
	{
		m_iTotalCount--;
	}

	FileInfoList * res=fileIter->DeleteSelf(disposeEnable);

	if(!disposeEnable)
	{
		//���ֻ�Ƿŵ���Чλ�ã�����Ҫ��ָ����õ�ENDER��
		m_filFileListEnder->InsertNext(fileIter);
	}
	return res;
}

//=====================================================================
// �� �� ����GetFile
// �����������������л�ȡcountλ�õ��ļ�
// ���������int count:�ļ��������е�λ�ã���0��ʼ
// ���������FileInfoList *
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
FileInfoList * FileInfoControl::GetFile(int count)
{
	if(count<0){return NULL;}

	FileInfoList * res=NULL;								//��󷵻ص�ָ��洢����
	int iterCnt;											//��ǰָ������λ��

	//������Ҫ��ȡ��λ���������β�����ȡֵλ�õľ���
	int distance=abs(m_iTotalCount-count);					//�������β������
	distance=distance>count?count:distance;					//�������ͷβ��������ֵ
	int distanceLast=abs(m_iLastGetFilePos-count);			//���������ȡֵλ�õľ���

	if(distance<distanceLast)
	{
		//������ͷ��βλ�ø���ʱ
		if(count<m_iTotalCount/2)
		{
			//��λ�ô�������ǰ��ʱ����ͷָ�뿪ʼ
			res=m_filFileListHeader->m_filNextItem;
			iterCnt=0;

			while(iterCnt<count)
			{
				res=res->m_filNextItem;
				iterCnt++;
			}
		}
		else
		{
			//��λ�ô��������벿ʱ����βָ�뿪ʼ
			res=m_filFileListEnder->m_filUpItem;
			iterCnt=m_iTotalCount-1;						//λ�ô�0��ʼ����ȫ���ļ�����-1

			while(iterCnt>count)
			{
				res=res->m_filUpItem;
				iterCnt--;
			}
		}
	}
	else
	{
		//���������ȡֵλ�����ʱ�������ȡֵλ�ÿ�ʼ
		res=m_filLastGetFileInfoP;
		iterCnt=m_iLastGetFilePos;

		if(count<m_iLastGetFilePos)
		{
			//��λ����ǰʱ����ǰ����
			while(iterCnt>count)
			{
				res=res->m_filUpItem;
				iterCnt--;
			}
		}
		else if(count>m_iLastGetFilePos)
		{
			//��λ���ں�ʱ��������
			while(iterCnt<count)
			{
				res=res->m_filNextItem;
				iterCnt++;
			}
		}
		else
		{
			//��λ����ͬʱ��ֱ�ӷ���
			return m_filLastGetFileInfoP;
		}
	}

	m_iLastGetFilePos=iterCnt;
	m_filLastGetFileInfoP=res;
	return res;
}
	

//=====================================================================
// �� �� ����GetFileType
// ���������������ļ���չ���ó��ļ�����
// ���������string exName:�ļ���չ��
// ���������string
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
string FileInfoControl::GetFileType(string exName)
{
	string name=m_mssFileExtName2Type[exName];
	if(name.compare("")==0)
	{
		return exName+"�ļ�";
	}

	return name;
}
	

//=====================================================================
// �� �� ����SortAttribute
// �����������������������
// ���������int INFO_TYPE:��FileInfoList.h�ж���ĺ�
//			 int sortOrder:����ʽ--0������-1������
// ���������void
// �������ڣ�08.09.12
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::SortAttribute(int INFO_TYPE,int sortOrder)
{
	if(sortOrder==0)
	{
		//��������
		SortAsc(INFO_TYPE);
	}
	else if(sortOrder==1)
	{
		//��������
		SortDes(INFO_TYPE);
	}
	else
	{
	}
}
	

//=====================================================================
// �� �� ����InsertItemByOrder
// ������������˳������µ��ļ�����
// ���������FileInfoList * item:��Ҫ������ļ�����
//			 int INFO_TYPE:��FileInfoList.h�ж���ĺ�
//			 int sortOrder:����ʽ--0������-1������
// ���������void
// �������ڣ�08.09.12
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::InsertItemByOrder(FileInfoList * item,int INFO_TYPE,int sortOrder)
{
	if(sortOrder==0)
	{
		//��������
		InsertItemAsc(INFO_TYPE,item);
	}
	else if(sortOrder==1)
	{
		//��������
		InsertItemDes(INFO_TYPE,item);
	}
	else
	{
		if(item->CheckFileType(FILE_FLODER))
		{
			m_filFileListHeader->InsertNext(item);
		}
		else
		{
			m_filFileListEnder->InsertFront(item);
		}
	}
}
	

//=====================================================================
// �� �� ����SortAsc
// ������������������
// ���������int INFO_TYPE:��FileInfoList.h�ж���ĺ�
// ���������void
// �������ڣ�08.09.12
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::SortAsc(int INFO_TYPE)
{
	//��Ϊ�ӿ�����ٶȵı�����ʼ��
	_ResetSearchItems();

	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	//������ͷβ����������ʱֱ�Ӳ���
	m_filFileListHeader->m_filNextItem=m_filFileListEnder;
	m_filFileListEnder->m_filUpItem=m_filFileListHeader;

	while(iter!=m_filFileListEnder)
	{
		FileInfoList * tmp=iter;
		iter=iter->m_filNextItem;

		InsertItemAsc(INFO_TYPE,tmp);
	}

	m_iOrderType=0;					//������������ʽ
	m_iOrderItem=INFO_TYPE;			//����������ʹ�õ�������
}
	

//=====================================================================
// �� �� ����InsertItemAsc
// ��������������������
// ���������int INFO_TYPE:��FileInfoList.h�ж���ĺ�
//			 FileInfoList * item:��Ҫ����Ķ���
// ���������void
// �������ڣ�08.09.12
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::InsertItemAsc(int INFO_TYPE,FileInfoList * item)
{
	FileInfoList * tmpIter=m_filFileListHeader->m_filNextItem;

	while(tmpIter!=m_filFileListEnder)
	{
		if(m_bOrderByGroup)
		{
			//�������˷���ʱ������˳������
			int comRes=_CompareGroup(tmpIter,item);
			if(comRes>0)
			{
				break;
			}
			if(comRes<0)
			{
				tmpIter=tmpIter->m_filNextItem;
				continue;
			}
		}

		if(_CompareFileInfo(tmpIter,item,INFO_TYPE)<=0)
		{
			tmpIter=tmpIter->m_filNextItem;
		}
		else
		{
			break;
		}
	}
	tmpIter->InsertFront(item);
}
	

//=====================================================================
// �� �� ����SortDes
// ������������������
// ���������int INFO_TYPE:��FileInfoList.h�ж���ĺ�
// ���������void
// �������ڣ�08.09.12
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::SortDes(int INFO_TYPE)
{
	//��Ϊ�ӿ�����ٶȵı�����ʼ��
	_ResetSearchItems();

	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	//������ͷβ����������ʱֱ�Ӳ���
	m_filFileListHeader->m_filNextItem=m_filFileListEnder;
	m_filFileListEnder->m_filUpItem=m_filFileListHeader;

	while(iter!=m_filFileListEnder)
	{
		FileInfoList * tmp=iter;
		iter=iter->m_filNextItem;

		InsertItemDes(INFO_TYPE,tmp);
	}

	m_iOrderType=1;					//������������ʽ
	m_iOrderItem=INFO_TYPE;			//����������ʹ�õ�������
}
	


//=====================================================================
// �� �� ����InsertItemDes
// ��������������������
// ���������int INFO_TYPE:��FileInfoList.h�ж���ĺ�
//			 FileInfoList * item:��Ҫ����Ķ���
// ���������void
// �������ڣ�08.09.12
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::InsertItemDes(int INFO_TYPE,FileInfoList * item)
{
	FileInfoList * tmpIter=m_filFileListHeader->m_filNextItem;

	while(tmpIter!=m_filFileListEnder)
	{
		if(m_bOrderByGroup)
		{
			//�������˷���ʱ������˳������
			int comRes=_CompareGroup(tmpIter,item);
			if(comRes>0)
			{
				break;
			}
			if(comRes<0)
			{
				tmpIter=tmpIter->m_filNextItem;
				continue;
			}
		}

		if(_CompareFileInfo(tmpIter,item,INFO_TYPE)>=0)
		{
			tmpIter=tmpIter->m_filNextItem;
		}
		else
		{
			break;
		}
	}
	tmpIter->InsertFront(item);
}
	

//=====================================================================
// �� �� ����GroupByFileName
// �������������ļ������з�������
// ���������
// ���������void
// �������ڣ�08.09.28
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::GroupByFileName()
{
	//ѭ����飬�������飬֮����ݷ����������
	FileInfoList * tmpIter=m_filFileListHeader->m_filNextItem;
	map<WCHAR,int> GroupExistMap;			//�Ѿ����ڵķ�����ϢMAP
	m_iGroupCount=0;						//��������ͳ�Ʊ���
	m_migiGroupMap.clear();

	while(tmpIter!=m_filFileListEnder)
	{
		//��ȡ�ļ�����һ���ַ�����Ϊ����Ҫ�ж����ĵ����⣬���Խ���ת��Ϊw_char
		USES_CONVERSION;
		LPWSTR tmpS=A2W(tmpIter->GetFileName().c_str());
		WCHAR wc=tmpS[0];

		if(!GroupExistMap[wc])
		{
			//�����ڵķ�����Ϣ���в����ڸ÷���ʱ�����µķ���
			GroupExistMap[wc]=m_iGroupCount+1;		//�洢ʱ��INT+1����INT�ش���0
			GroupInfo * info=new GroupInfo();
			info->groupName=wc;
			info->itemCount=0;
			info->seledItemCount=0;
			m_migiGroupMap.insert(MapIntGInfo::value_type(m_iGroupCount,info));
			//����ͳ������
			m_iGroupCount++;
		}

		//��ȡ������Ϣ��������
		int n=GroupExistMap[wc]-1;		//��ȡ���ʱ��Ҫ-1��ԭ
		GroupInfo * info=m_migiGroupMap[n];
		info->itemCount++;
		if(tmpIter->GetState(LVIS_SELECTED))
		{
			//��ITEM��ѡ������ط�����Ϣ�б�ѡ��ITEMͳ��+1
			info->seledItemCount++;
		}
		tmpIter->m_iGroupId=n;

		//��������һ��
		tmpIter=tmpIter->m_filNextItem;
	}

	//���÷���Ϊ��
	m_bOrderByGroup=true;


	if(m_iOrderType)
	{
		//��m_iOrderType==1ʱ��ԭ���б��ǽ�������ʽ
		SortDes(m_iOrderItem);
	}
	else
	{
		SortAsc(m_iOrderItem);
	}
}
	

//=====================================================================
// �� �� ����DisGroup
// ���������������з���
// ���������
// ���������void
// �������ڣ�08.09.28
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::DisGroup()
{
	m_bOrderByGroup=false;
}
	

//=====================================================================
// �� �� ����GetSelectedFileList
// ����������ɸѡ��ѡ�е��ļ�
// ���������CStringList * resultList:
//			,UINT selectType:ɸѡ��־
// ���������int:���ر������ַ����ĳ���
// �������ڣ�08.10.06
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::GetSelectedFileList(CStringList * resultList,UINT selectType)
{
	int len=0;			//�洢���ļ����ȣ�ÿ���ļ�����Ҫ+1���ȣ�

	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED) && iter->CheckFileType(selectType))
		{
			//���ļ���ѡ��ʱ
			CString s=iter->GetFileFullPath().c_str();
			resultList->AddTail(s);
			len+=strlen(s)+1;			//�ַ�����β����"\0"����+1
		}

		iter=iter->m_filNextItem;
	}

	return len;
}
	

//=====================================================================
// �� �� ����GetSelectedFileType
// ������������ȡ���б�ѡ���ļ����͵ı�ʾ��
// ���������
// ���������UINT:���ͱ�ʾ����
// �������ڣ�08.10.15
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
UINT FileInfoControl::GetSelectedFileType()
{
	UINT type=0;

	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED))
		{
			//���ļ���ѡ��ʱ
			type|=iter->m_uiFileType;
		}

		iter=iter->m_filNextItem;
	}

	return type;
}
	

//=====================================================================
// �� �� ����DelSelectedFile
// �����������������н�ѡ���ļ����õ���Чλ��
// ���������
// ���������
// �������ڣ�08.10.06
// �޸����ڣ�08.10.09
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::DelSelectedFile()
{
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED))
		{
			//���ļ���ѡ��ʱ
			iter=_DelFile(iter,false);
		}
		else
		{
			iter=iter->m_filNextItem;
		}
	}
}
	

//=====================================================================
// �� �� ����CheckSelectedFile
// ���������������ѡ���ļ������ļ�δѡ��ʱ������ɾ���ļ�
// ���������
// ���������
// �������ڣ�08.10.06
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::CheckSelectedFile()
{
	int count=0;
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED))
		{
			//���ļ���ѡ��ʱ
			if(access(iter->GetFileFullPath().c_str(),0)!=0)
			{
				//���ļ�������ʱ
				iter=_DelFile(iter,true);
				count++;
				continue;
			}
		}

		iter=iter->m_filNextItem;
	}

	if(!count)
	{
		_ResetSearchItems();
	}

	return count;
}
	

//=====================================================================
// �� �� ����SetAllState
// ���������������������״̬
// ���������UINT state,bool changeAll,UINT mask
// ���������
// �������ڣ�08.10.07
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::SetAllState(UINT state,bool changeAll,UINT mask)
{
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	while(iter!=m_filFileListEnder)
	{
		iter->SetState(state,changeAll,mask);

		iter=iter->m_filNextItem;
	}
}
	

//=====================================================================
// �� �� ����GetFloderCode
// ���������������������״̬
// ���������UINT state,bool changeAll,UINT mask
// ���������
// �������ڣ�08.10.07
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::GetFloderCode(string floderPath)
{
	int floderCode=m_msiFilePathMap[floderPath];
	
	return floderCode;
}
	

//=====================================================================
// �� �� ����DealSelectedFile
// ������������������ɾ����ѡ�е��ļ�
// ���������string newFloderPath,UINT dealType:dealTypeΪ0��������1������
// ���������
// �������ڣ�08.10.08
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::DealSelectedFile(string newFloderPath,UINT dealType,UINT cutOrCopy)
{
	int count=0;
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	if(cutOrCopy==DEAL_FILE_CUT)
	{
		while(iter!=m_filFileListEnder)
		{
			if(iter->GetState(LVIS_SELECTED))
			{
				//���ļ���ѡ��ʱ
				iter->ICutFile(newFloderPath,dealType);
			}

			iter=iter->m_filNextItem;
		}
	}
	else if(cutOrCopy==DEAL_FILE_COPY)
	{
		while(iter!=m_filFileListEnder)
		{
			if(iter->GetState(LVIS_SELECTED))
			{
				//���ļ���ѡ��ʱ
				iter->ICopyFile(newFloderPath,dealType);
			}

			iter=iter->m_filNextItem;
		}
	}

	return count;
}
	

//=====================================================================
// �� �� ����DealSelectedFile
// ���������������������ѡ���ļ������а�
// ���������UINT cutOrCopyΪ0��������1������
// ���������
// �������ڣ�08.10.08
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::DealSelectedFile(UINT cutOrCopy)
{
	int count=0;
	
	//ѡ�е��ļ��б�
	CStringList csList;
	//���ѡ�е��ļ��б�CStringList
	int len=GetSelectedFileList(&csList,FILE_ALL);

	//�����ڴ�
	HGLOBAL hMemData = GlobalAlloc(GPTR,len);
	ASSERT(hMemData != NULL);   

	//����������ڴ棬�ڴ��ֵΪchar*����   
	char * lpDropFiles = (char *)GlobalLock(hMemData);  
	//CStringList����ʼλ��
	POSITION pItemPos = csList.GetHeadPosition();
	char * pszStart = lpDropFiles;   
	while(pItemPos != NULL)     
	{   
		lstrcpy(pszStart, (LPCTSTR)csList.GetNext(pItemPos));   
		pszStart = strchr(pszStart,'\0')   +   1;   //�´ε���ʼλ������һ�ν�β+1   
	} 
	//��ѡ�е��ļ����������
	if(cutOrCopy==DEAL_FILE_COPY)
	{
		//����
		PublicFunc::CutOrCopyFiles(lpDropFiles,len,TRUE);
	}
	else
	{
		//����
		PublicFunc::CutOrCopyFiles(lpDropFiles,len,FALSE);
	}
	//�����ڴ�
	GlobalUnlock(hMemData);

	return count;
}
	

//=====================================================================
// �� �� ����GetFirstSelectedCode
// ������������ȡ��һ����ѡ���ITEM�ı��
// ���������
// ���������
// �������ڣ�08.10.08
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::GetFirstSelectedCode()
{
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	int i=0;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED))
		{
			return i;
		}

		i++;
		iter=iter->m_filNextItem;
	}

	return -1;
}
	

//=====================================================================
// �� �� ����GetFirstSelectedPhotoCode
// ������������ȡ��һ����ѡ���ͼ��ı��
// ���������
// ���������
// �������ڣ�08.10.10
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::GetFirstSelectedPhotoCode()
{
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	int i=0;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED) && iter->CheckFileType(FILE_PHOTO))
		{
			return i;
		}

		i++;
		iter=iter->m_filNextItem;
	}

	return -1;
}
		

//=====================================================================
// �� �� ����SetSelectedLvOrType
// ������������ȡ��һ����ѡ���ITEM�ı��
// ���������int value:���õ�ֵ
//			 UINT dealTarget:���õ����ͣ�����DEAL_DRAG_LV��DEAL_DRAG_TYPE�ж�
// ���������
// �������ڣ�08.10.09
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::SetSelectedLvOrType(int value,UINT dealTarget)
{
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	if(dealTarget==DEAL_DRAG_LV)
	{
		//�޸�������Ϣʱ
		while(iter!=m_filFileListEnder)
		{
			if(iter->GetState(LVIS_SELECTED))
			{
				//��ITEM��ѡ��ʱ
				iter->m_iPhotoLevel=value;
			}
	
			iter=iter->m_filNextItem;
		}
	}
	else if(dealTarget==DEAL_DRAG_TYPE)
	{
		//�޸�������Ϣʱ
		while(iter!=m_filFileListEnder)
		{
			if(iter->GetState(LVIS_SELECTED))
			{
				//��ITEM��ѡ��ʱ
				iter->m_iPhotoTypeCode=value;
			}
	
			iter=iter->m_filNextItem;
		}
	}

}
//=====================================================================
// �� �� ����SetItemLvOrType
// ������������ȡ��һ����ѡ���ITEM�ı��
// ���������int nItem:���õĶ�����
//			 int value:���õ�ֵ
//			 UINT dealTarget:���õ����ͣ�����DEAL_DRAG_LV��DEAL_DRAG_TYPE�ж�
// ���������
// �������ڣ�08.10.09
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::SetItemLvOrType(int nItem,int value,UINT dealTarget)
{
	FileInfoList * file=GetFile(nItem);

	if(dealTarget==DEAL_DRAG_LV)
	{
		//�޸�������Ϣʱ
		file->m_iPhotoLevel=value;
	}
	else if(dealTarget==DEAL_DRAG_TYPE)
	{
		//�޸�������Ϣʱ
		file->m_iPhotoTypeCode=value;
	}
}
	

//=====================================================================
// �� �� ����SetItemFouc
// �������������ñ��λ�õ�ITEMΪ���н����ITEM
// ���������int nItem:���õĶ�����,FileInfoList * fileInfo=NULL
// ���������
// �������ڣ�08.10.15
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::SetItemFouc(int nItem,FileInfoList * fileInfo)
{
	FileInfoList * file=fileInfo?fileInfo:GetFile(nItem);
	m_filFoucFile->SetState(~LVIS_FOCUSED,false,LVIS_FOCUSED);
	file->SetState(LVIS_FOCUSED,false,LVIS_FOCUSED);
	m_iFoucFileCode=nItem;
	m_filFoucFile=file;
}
	

//=====================================================================
// �� �� ����SetFoucToItemState
// �������������ôӽ���ITEM��ʼ��ָ����ŵ�ITEM��״̬
// ���������int nItem
// ���������
// �������ڣ�08.10.15
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::SetFoucToItemState(int nItem)
{
	if(m_iFoucFileCode<0)
	{
		return ;
	}

	if(nItem>m_iFoucFileCode)
	{
		FileInfoList * iter=m_filFoucFile;
		int i=m_iFoucFileCode;
		while(i<=nItem)
		{
			iter->SetState(LVIS_SELECTED,false,LVIS_SELECTED);
			i++;
			iter=iter->m_filNextItem;
		}
	}
	else
	{
		FileInfoList * iter=m_filFoucFile;
		int i=m_iFoucFileCode;
		while(i>=nItem)
		{
			iter->SetState(LVIS_SELECTED,false,LVIS_SELECTED);
			i--;
			iter=iter->m_filUpItem;
		}
	}
}
	

//=====================================================================
// �� �� ����AddFile
// �������������һ���ļ���������
// ���������string  fileFullPath:�ļ�������·��
//			 bool isDirectory:�Ƿ��ļ���
//			 int floderCode:�����ļ������Ѿ�ѡ���ļ��м����еı��
//			 LONG fileLength:�ļ�����
// ���������FileInfoList *
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵�����ڱ������а����˶��ļ���չ����ɸѡ
//=====================================================================
FileInfoList * FileInfoControl::_AddFile(string  fileFullPath,UINT fileType,int floderCode,LONG fileLength)
{
	FileInfoList * item=new FileInfoList(fileFullPath,fileType,fileLength);
	item->m_iFloderCode=floderCode;

	if(item->CheckFileType(FILE_FLODER))
	{
		//��Ϊ�ļ���ʱ
		item->m_sFileType="�ļ���";
	}
	else
	{
		//��Ϊ�ļ�ʱ
 		if(m_msbFileTypeControlMap[item->GetFileExtName()])
		{
			//��ɸѡ��Ϊtrueʱ����ӽ��ļ�����������Ϊͼ��
			item->SetFileType(FILE_PHOTO);
			item->m_sFileType=GetFileType(item->GetFileExtName());
		}
		else
		{
			if(!m_bFileChooseEnable)
			{
				//������Ҫͨ��ɸѡʱ
				if(m_msbFileTypeControlMap[item->GetFileExtName()])
				{
					//���ļ���չ����ɸѡ���д��ڣ����ʾ�ļ�Ϊͼ��
					item->SetFileType(FILE_PHOTO);
				}
				item->m_sFileType=GetFileType(item->GetFileExtName());
			}
			else
			{
				item->m_bFileEnable=false;		//�����ļ���Ч
			}
		}
	}

	if(item->m_bFileEnable)
	{
		//���ļ���Чʱ���������룬���ļ���Чʱ���뵽ĩβ�ڵ��
		//������ʽ���������Բ����ļ�
		m_iTotalCount++;
		InsertItemByOrder(item,m_iOrderItem,m_iOrderType);
	}
	else
	{
		m_filFileListEnder->InsertNext(item);
	}

	return item;
}
	

//=====================================================================
// �� �� ����ResetSearchItems
// �����������������ò�ѯ��ض���
// ���������void
// ���������void
// �������ڣ�08.09.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void FileInfoControl::_ResetSearchItems()
{
	m_iLastGetFilePos=-1;								//����ȡ���ļ�λ�ã���Ҫ���ڼӿ������ٶ�
	m_filLastGetFileInfoP=m_filFileListHeader;			//����ȡ���ļ���ָ�룬��λ�����ʹ�üӿ������ٶ�
}
	

//=====================================================================
// �� �� ����CompareFileInfo
// �����������������ļ�������бȽ�
// ���������FileInfoList * item1,FileInfoList * item2
//			 int INFO_TYPE:��FileInfoList.h�ж���ĺ�
// ���������int:-1��ǰ��С��0��ȣ�1����С
// �������ڣ�08.09.12
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::_CompareFileInfo(FileInfoList * item1,FileInfoList * item2,int INFO_TYPE)
{
	if(item1->CheckFileType(FILE_FLODER) && !item2->CheckFileType(FILE_FLODER))
	{
		return 1;
	}
	else if(!item1->CheckFileType(FILE_FLODER) && item2->CheckFileType(FILE_FLODER))
	{
		return -1;
	}
	else
	{
		return item1->GetFileBaseInfo(INFO_TYPE).compare(item2->GetFileBaseInfo(INFO_TYPE));
	}
}
	

//=====================================================================
// �� �� ����_CompareGroup
// �����������������ļ�������бȽ�
// ���������FileInfoList * item1,FileInfoList * item2
// ���������int:-1��ǰ��С��0��ȣ�1����С
// �������ڣ�08.09.28
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int FileInfoControl::_CompareGroup(FileInfoList * item1,FileInfoList * item2)
{
	if(item1->m_iGroupId<item2->m_iGroupId)
	{
		return -1;
	}
	else if(item1->m_iGroupId>item2->m_iGroupId)
	{
		return 1;
	}
	return 0;
}