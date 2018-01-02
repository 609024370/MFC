// GradualChangeView.cpp : implementation of the CGradualChangeView class
// Download by http://www.codefans.net

#include "stdafx.h"
#include "GradualChange.h"

#include "GradualChangeDoc.h"
#include "GradualChangeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define BMP_SIZE 1440000

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeView

IMPLEMENT_DYNCREATE(CGradualChangeView, CView)

BEGIN_MESSAGE_MAP(CGradualChangeView, CView)
	//{{AFX_MSG_MAP(CGradualChangeView)
	ON_COMMAND(ID_MYPLAY, OnMyplay)
	ON_WM_TIMER()
	ON_COMMAND(ID_MYSTOP, OnMystop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeView construction/destruction

CGradualChangeView::CGradualChangeView()
{
	// TODO: add construction code here
	m_pb1 = NULL;
	m_pb2 = NULL;
	m_pb3 = NULL;
}

CGradualChangeView::~CGradualChangeView()
{
	//���û�������ͷŶѿռ����ڳ����˳�ǰ�ͷ�֮
	if(m_pb1 != NULL)
	{
		free(m_pb1);
	}
	if(m_pb2 != NULL)
	{
		free(m_pb2);
	}
	if(m_pb3 != NULL)
	{
		free(m_pb3);
	}
}

BOOL CGradualChangeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeView drawing

void CGradualChangeView::OnDraw(CDC* pDC)
{
	CGradualChangeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeView diagnostics

#ifdef _DEBUG
void CGradualChangeView::AssertValid() const
{
	CView::AssertValid();
}

void CGradualChangeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGradualChangeDoc* CGradualChangeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGradualChangeDoc)));
	return (CGradualChangeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeView message handlers

void CGradualChangeView::OnMyplay() 
{
	// TODO: Add your command handler code here
	if(m_pb1 == NULL)
	{
		//��ʼ��������m_nCaseΪ1��ʾ��ǰҪ��ʾ��һ��ͼƬ�ĵ���
		m_nCount = 0;
		m_nCase = 1;

		//��ȡbmp�ļ�ͷ��Ϣ
		CFile f1, f2;
		f1.Open("bmp1.bmp", CFile::modeRead, NULL);
		f1.Seek(14, CFile::begin);
		f1.Read(&m_header, 40);
		f2.Open("bmp2.bmp", CFile::modeRead, NULL);
		f2.Seek(14, CFile::begin);
		f2.Read(&m_header, 40);

		//��̬����ռ䣬�����#define BMP_SIZE 1440000
		m_pb1 = (BYTE *)malloc(BMP_SIZE);
		m_pb2 = (BYTE *)malloc(BMP_SIZE);
		m_pb3 = (BYTE *)malloc(BMP_SIZE);
	
		//��ȡbmp�ļ�������������
		f1.ReadHuge(m_pb1, BMP_SIZE);
		f1.Close();
		f2.ReadHuge(m_pb2, BMP_SIZE);
		f2.Close();

		//������ʱ��������Ϊ1��ÿ100�����ж�һ��
		SetTimer(1, 100, NULL);
	}
}

void CGradualChangeView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//��û����ʾ�ڶ���ͼƬ����ʾ�ڶ���ͼƬ
	if(m_nCount >= 64 && m_nCase == 1)
	{
		m_nCase = 2;
		m_nCount = 0;
	}
	//����ͼƬ����ʾ����
	else if( m_nCount >= 64 && m_nCase == 3)
	{
		OnMystop();
		MessageBox("��ʾ���", "���", MB_OK);
	}
	else
	{
		//��ʾ��һ��ͼƬ
		if(m_nCase == 1)
		{
			m_nCount++;
			for(int i = 0; i < BMP_SIZE; i++)
				m_pb3[i] = m_nCount * m_pb1[i]/64;

			StretchDIBits(GetDC()->m_hDC, 0, 0, 800, 600, 0, 0, 800, 600, m_pb3, 
							((BITMAPINFO*)(&m_header)), DIB_RGB_COLORS, SRCCOPY);
		
		}
	
		else if(m_nCase == 2)
		{
			//��ʾ�ڶ���ͼƬ����������һ��ͼƬ
			m_nCount++;
			for(int i = 0; i < BMP_SIZE; i++)
				m_pb3[i] = ((64 - m_nCount) * m_pb1[i] + m_nCount * m_pb2[i]) / 64;

			StretchDIBits(GetDC()->m_hDC, 0, 0, 800, 600, 0, 0, 800, 600, m_pb3, 
							((BITMAPINFO*)(&m_header)), DIB_RGB_COLORS, SRCCOPY);

			//�����ȫ�����ˣ�m_nCaseֵ��Ϊ3
			if(m_nCount >= 64)
				m_nCase = 3;
		}
	}
}

void CGradualChangeView::OnMystop() 
{
	// TODO: Add your command handler code here

	//�ͷŶѿռ�
	if(m_pb1 != NULL)
	{
		free(m_pb1);
		m_pb1 = NULL;
	}
	if(m_pb2 != NULL)
	{
		free(m_pb2);
		m_pb2 = NULL;
	}
	if(m_pb3 != NULL)
	{
		free(m_pb3);
		m_pb3 = NULL;
	}

	//�رռ�ʱ��
	KillTimer(1);
}
