////////////////////////////////////////////////////////////////////////// 


////////////////////////////////////////////////////////////////////////// 

  
#if !defined(INIFILE_H) 

#define INIFILE_H 

#if _MSC_VER > 1000 

#pragma once 

#endif // _MSC_VER > 1000 

#ifdef BIGLOBALS_IMP
   #define CLASS_DECL_BIGLOBALS __declspec(dllexport)
#else
   #define CLASS_DECL_BIGLOBALS __declspec(dllimport)
#endif  

class CLASS_DECL_BIGLOBALS CIniFile  

{ 
public: 
    CIniFile(); 
    virtual ~CIniFile(); 
    //    ����ini�ļ�·��
    //    �ɹ�����TRUE;���򷵻�FALSE 
    BOOL  SetPath(CString strPath);

    //    ���section�Ƿ����
    //    ���ڷ���TRUE;���򷵻�FALSE 
    BOOL  SectionExist(CString strSection); 
    //    ��ָ����Section��Key��ȡKeyValue
    //    ����KeyValue 
    CString   GetKeyValue(CString    strSection, CString    strKey);         

    //    ����Section��Key�Լ�KeyValue����Section����Key�������򴴽� 
    void  SetKeyValue(CString    strSection, CString    strKey, CString    strKeyValue); 
    //    ɾ��ָ��Section�µ�һ��Key 
    void  DeleteKey(CString strSection, CString strKey); 
    BOOL  AddKey(CString strSection, CString strKey); 

    //    ɾ��ָ����Section�Լ����µ�����Key 
    void  DeleteSection(CString strSection); 
    BOOL  AddSection(CString strSection);

     //    ������е�Section
     //    ����Section��Ŀ 
     int   GetAllSections(CStringArray& strArrSection); 
     //    ����ָ��Section�õ����µ�����Key��KeyValue
     //    ����Key����Ŀ 
     int   GetAllKeysAndValues(CString strSection,  CStringArray& strArrKey,  CStringArray& strArrKeyValue); 
     //       ɾ������Section 
     void   DeleteAllSections(); 
         
private: 

     //       ini�ļ�·�� 
     CString m_strPath;   
}; 

  

#endif // !defined(AFX_INIFILE_H__B5C0D7F7_8353_4C93_AAA4_38A688CA253C__INCLUDED_) 

