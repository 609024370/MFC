// GraphShowerDoc.cpp : CGraphShowerDoc ���ʵ��
//

#include "stdafx.h"
#include "GraphShower.h"

#include "GraphShowerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphShowerDoc

IMPLEMENT_DYNCREATE(CGraphShowerDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphShowerDoc, CDocument)
END_MESSAGE_MAP()


// CGraphShowerDoc ����/����

CGraphShowerDoc::CGraphShowerDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CGraphShowerDoc::~CGraphShowerDoc()
{
}

BOOL CGraphShowerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGraphShowerDoc ���л�

void CGraphShowerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CGraphShowerDoc ���

#ifdef _DEBUG
void CGraphShowerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphShowerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGraphShowerDoc ����
