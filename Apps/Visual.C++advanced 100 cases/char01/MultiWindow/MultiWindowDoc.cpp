// MultiWindowDoc.cpp : implementation of the CMultiWindowDoc class
//

#include "stdafx.h"
#include "MultiWindow.h"

#include "MultiWindowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiWindowDoc

IMPLEMENT_DYNCREATE(CMultiWindowDoc, CDocument)

BEGIN_MESSAGE_MAP(CMultiWindowDoc, CDocument)
	//{{AFX_MSG_MAP(CMultiWindowDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiWindowDoc construction/destruction

CMultiWindowDoc::CMultiWindowDoc()
{
	// TODO: add one-time construction code here

}

CMultiWindowDoc::~CMultiWindowDoc()
{
}

BOOL CMultiWindowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMultiWindowDoc serialization

void CMultiWindowDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMultiWindowDoc diagnostics

#ifdef _DEBUG
void CMultiWindowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMultiWindowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultiWindowDoc commands
