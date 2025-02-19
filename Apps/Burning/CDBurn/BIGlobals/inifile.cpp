////////////////////////////////////////////////////////////////////////// 


////////////////////////////////////////////////////////////////////////// 

  

#include "stdafx.h" 
//#include "test6.h" 
#include "IniFile.h" 

#ifdef _DEBUG 
#undef THIS_FILE 
static char THIS_FILE[]=__FILE__; 

#define new DEBUG_NEW 
#endif 

  

#define         MAX_SECTION         260      //Section最大长度 
#define         MAX_KEY             260      //KeyValues最大长度 
#define         MAX_ALLSECTIONS     65535    //所有Section的最大长度 
#define         MAX_ALLKEYS         65535    //所有KeyValue的最大长度 

////////////////////////////////////////////////////////////////////// 

// Construction/Destruction 

////////////////////////////////////////////////////////////////////// 

  

CIniFile::CIniFile() 
{ 

} 

CIniFile::~CIniFile() 

{ 

} 
////////////////////////////////////////////////////////////////////////// 

//   Public Functions 

////////////////////////////////////////////////////////////////////////// 

BOOL CIniFile::SetPath(CString strPath) 
{ 
     m_strPath = strPath; 
     //       检查文件是否存在 
     DWORD  dwFlag = GetFileAttributes((LPCTSTR)m_strPath); 
     //       文件或者路径不存在，返回FALSE 
     if( 0xFFFFFFFF == dwFlag ) 
          return FALSE; 
     //       路径是目录，返回FALSE 
     if (  FILE_ATTRIBUTE_DIRECTORY & dwFlag ) 
           return FALSE; 
     return TRUE; 
} 

  

BOOL CIniFile::SectionExist(CString strSection) 

{ 
     TCHAR chSection[MAX_SECTION]; 
     DWORD dwRetValue; 
     dwRetValue = GetPrivateProfileString((LPCTSTR)strSection, NULL, _T(""), chSection, 
                                          sizeof(chSection)/sizeof(TCHAR), (LPCTSTR)m_strPath); 
     return (dwRetValue>0); 
} 

  

CString CIniFile::GetKeyValue(CString strSection, CString strKey) 
{ 
     TCHAR    chKey[MAX_KEY]; 
     DWORD   dwRetValue; 
     CString strKeyValue=_T(""); 

     dwRetValue = GetPrivateProfileString((LPCTSTR)strSection, (LPCTSTR)strKey, _T(""), chKey, 
			                               sizeof(chKey)/sizeof(TCHAR), (LPCTSTR)m_strPath);      
     strKeyValue = chKey; 
     return strKeyValue; 
} 

  

void CIniFile::SetKeyValue(CString strSection, CString strKey, CString strKeyValue) 
{ 
      WritePrivateProfileString((LPCTSTR)strSection, (LPCTSTR)strKey, (LPCTSTR)strKeyValue, (LPCTSTR)m_strPath); 
} 

  

void CIniFile::DeleteKey(CString strSection, CString strKey) 
{ 
     WritePrivateProfileString( (LPCTSTR)strSection, (LPCTSTR)strKey, NULL,(LPCTSTR)m_strPath); 
} 

BOOL CIniFile::AddKey(CString strSection, CString strKey)
{
	WritePrivateProfileString( (LPCTSTR)strSection, (LPCTSTR)strKey, "null", (LPCTSTR)m_strPath); 
	return TRUE;
}


  

void CIniFile::DeleteSection(CString strSection) 

{ 
     WritePrivateProfileString( (LPCTSTR)strSection, NULL, NULL,(LPCTSTR)m_strPath); 
} 

  
BOOL CIniFile::AddSection(CString strSection)
{
//	if (!SectionExist(strSection)) {
	WritePrivateProfileString( (LPCTSTR)strSection, "null", "null", (LPCTSTR)m_strPath); 
	return TRUE;
}

int CIniFile::GetAllSections(CStringArray& strArrSection)
{ 
     int dwRetValue, i, j, iPos=0; 
     TCHAR chAllSections[MAX_ALLSECTIONS]; 
     TCHAR chTempSection[MAX_SECTION]; 
     ZeroMemory(chAllSections, MAX_ALLSECTIONS); 
     ZeroMemory(chTempSection, MAX_SECTION); 
     dwRetValue = GetPrivateProfileSectionNames(chAllSections, MAX_ALLSECTIONS, m_strPath); 

    //       因为Section在数组中的存放形式为“Section1”，0，“Section2”，0，0。
    //   所以如果检测到连续两个0，则break 

     for(i=0; i<MAX_ALLSECTIONS; i++) 
     { 
           if( chAllSections[i] == NULL ) 
           { 
                if( chAllSections[i] == chAllSections[i+1] ) 
                     break; 
           } 
     } 

     i++; //        保证数据读完 
     strArrSection.RemoveAll();       //       清空数组 
     
     for(j=0; j<i; j++) 
     { 
           chTempSection[iPos++] = chAllSections[j]; 
           if( chAllSections[j] == NULL ) 
           {  
                strArrSection.Add(chTempSection); 
                ZeroMemory(chTempSection, MAX_SECTION); 
                iPos = 0; 
           } 
     }
     return strArrSection.GetSize(); 
} 

  

int CIniFile::GetAllKeysAndValues(CString strSection, CStringArray&  strArrKey, CStringArray& strArrKeyValue) 

{ 
     int dwRetValue, i, j, iPos=0; 
     TCHAR chAllKeysAndValues[MAX_ALLKEYS]; 
     TCHAR chTempkeyAndValue[MAX_KEY]; 
     CString strTempKey; 

     ZeroMemory(chAllKeysAndValues, MAX_ALLKEYS); 
     ZeroMemory(chTempkeyAndValue, MAX_KEY); 

     dwRetValue = GetPrivateProfileSection( strSection, chAllKeysAndValues, MAX_ALLKEYS, m_strPath); 
     //    因为Section在数组中的存放形式为“Key1=KeyValue1”，0，“Key2=KeyValue2”，0
     //    所以如果检测到连续两个0，则break 

     for(i=0; i<MAX_ALLSECTIONS; i++) 
     { 
           if( chAllKeysAndValues[i] == NULL ) 
           { 
                    if( chAllKeysAndValues[i] == chAllKeysAndValues[i+1] ) 
                             break; 
           } 
     } 

     i++; 
     strArrKey.RemoveAll(); 
     strArrKeyValue.RemoveAll(); 
     
     for(j=0; j<i; j++) 
     { 
           chTempkeyAndValue[iPos++] = chAllKeysAndValues[j]; 
           if( chAllKeysAndValues[j] == NULL ) 
           {  
                strTempKey = chTempkeyAndValue; 
                strArrKey.Add( strTempKey.Left(strTempKey.Find('=')) ); 
                strArrKeyValue.Add( strTempKey.Mid(strTempKey.Find('=')+1) ); 
                ZeroMemory(chTempkeyAndValue, MAX_KEY); 
                iPos = 0; 
           } 
     } 
     return strArrKey.GetSize(); 
} 

  

void CIniFile::DeleteAllSections() 
{ 
     int nSecNum; 
     CStringArray strArrSection; 
     nSecNum = GetAllSections(strArrSection); 
     for(int i=0; i<nSecNum; i++) 
     { 
           WritePrivateProfileString((LPCTSTR)strArrSection[i], NULL, NULL, (LPCTSTR)m_strPath);      
     } 
} 
