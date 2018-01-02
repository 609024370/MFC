//////////////////////////////////////////////////////////
//
//  ������ : ���켮
// ----------------------------------------------------
//  �� �ҽ��� ���� �ҽ��̸�, �� �ҽ��� ����� ���
//  �ݵ�� ���� �̸��� ���� �÷��ֽø� �����ϰڽ��ϴ�. ^^.
//
//  e-mail : seaousak@hotmail.com
//////////////////////////////////////////////////////////


// CtrView.cpp : implementation file
//

#include "stdafx.h"
#include "EasyFavorite.h"
#include "CtrView.h"

#include <Shlwapi.h>
#include "ThumbBtn.h"
#include <intshcut.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCtrView

IMPLEMENT_DYNCREATE(CCtrView, CFormView)

CCtrView::CCtrView()
	: CFormView(CCtrView::IDD)
{
	//{{AFX_DATA_INIT(CCtrView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_nControlID = 300;
	m_nTotalHeight = 0;
	m_nTotalThumb =0;

}

CCtrView::~CCtrView()
{
}

void CCtrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCtrView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCtrView, CFormView)
	//{{AFX_MSG_MAP(CCtrView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtrView diagnostics

#ifdef _DEBUG
void CCtrView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCtrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCtrView message handlers

BOOL CCtrView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext)
{
	return CFormView::Create(NULL, NULL, dwStyle, rect, pParentWnd, nID, pContext);
}


void CCtrView::PostNcDestroy()
{
	CThumbBtn *pTemp;

	// ��ü�� ����ϴ�.
	for (int i = 0 ; i < m_nTotalThumb; i++)
	{
		pTemp = (CThumbBtn *)m_arrayThumb.GetAt(i);
		delete pTemp;
	}

	m_arrayThumb.RemoveAll();
	m_arrayURL.RemoveAll();

	return;
}

void CCtrView::AddFavorite(CString strURL)
{
	if (::PathIsURL(strURL))	// �ùٸ� �ּҰ� ���Դ��� ����
	{
		CThumbBtn *pThumbBtn = new CThumbBtn;
		pThumbBtn->Create("ThumbBtn",WS_VISIBLE|WS_CHILD,
			CRect(LEFT_OFFSET, TOP_OFFSET + m_nTotalHeight, LEFT_OFFSET + THUMB_WIDTH, TOP_OFFSET + m_nTotalHeight + THUMB_HEIGHT),
			this, m_nControlID++);

		CreateInterShortcut (strURL, "c:\\temp.url" ,"Temp");

		///////////////////////////////////////
		pThumbBtn->SetURL("c:\\temp.url");
		m_nTotalThumb++;
		m_nTotalHeight += THUMB_HEIGHT + THUMB_OFFSET;
		m_arrayThumb.Add(pThumbBtn);
		m_arrayURL.Add(strURL);
	}

}



void CCtrView::RegisterOLE()
{
    BOOL success = m_OleTarget.Register(this);
    if(!success )
      MessageBox("Ole Register Drop Target Failed");             
	
	m_OleTarget.SetParent(this);

}

HRESULT CCtrView::CreateInterShortcut (LPCSTR pszURL, LPCSTR pszURLfilename,
	LPCSTR szDescription,LPCTSTR szIconFile ,int nIndex)
{
 HRESULT hres;

 CoInitialize(NULL); 

 IUniformResourceLocator *pHook;

 hres = CoCreateInstance (CLSID_InternetShortcut, NULL, CLSCTX_INPROC_SERVER,
  IID_IUniformResourceLocator, (void **)&pHook);

 if (SUCCEEDED (hres))
 {
  IPersistFile *ppf;
  IShellLink *psl;

  // Query IShellLink for the IPersistFile interface for 
  hres = pHook->QueryInterface (IID_IPersistFile, (void **)&ppf);
  hres = pHook->QueryInterface (IID_IShellLink, (void **)&psl);

  if (SUCCEEDED (hres))
  { 
   WORD wsz [MAX_PATH]; // buffer for Unicode string

   // Set the path to the shortcut target.
   pHook->SetURL(pszURL,0);

   hres = psl->SetIconLocation(szIconFile,nIndex);

   if (SUCCEEDED (hres))
   {
    // Set the description of the shortcut.
    hres = psl->SetDescription (szDescription);

    if (SUCCEEDED (hres))
    {
     // Ensure that the string consists of ANSI characters.
     MultiByteToWideChar (CP_ACP, 0, pszURLfilename, -1, wsz, MAX_PATH);

     // Save the shortcut via the IPersistFile::Save member function.
     hres = ppf->Save (wsz, TRUE);
    }
   }

   // Release the pointer to IPersistFile.
   ppf->Release ();
   psl->Release ();
  }

  // Release the pointer to IShellLink.
  pHook->Release ();

 }
 return hres;
} 
