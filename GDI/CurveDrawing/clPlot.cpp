// clPlot.cpp : implementation file
//

#include "stdafx.h"
#include "curvedrawing.h"
#include "clPlot.h"
#include "CurveDrawingView.h"
#include "MyView.h"
#include "malloc.h"
#include <stdlib.h>
#include <afxwin.h>

#include  <math.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// clPlot

clPlot::clPlot()
{
	m_ctlBkColor= RGB(255,255,255);
//	m_ctlBkColor=RGB(255,0,0);
	m_gridColor	= RGB(127,127,127);
	m_lNoValues=0;
	m_lend=0;
	leftmargin=30;
	rightmargin=30;
	topmargin=25;
	bottommargin=25;
	off=3;
	scalevalue=1;
	m_legendBkColor		= RGB(255,255,255);

}

clPlot::~clPlot()
{
	if(m_pValue!=NULL)
		free(m_pValue);
}


BEGIN_MESSAGE_MAP(clPlot, CWnd)
	//{{AFX_MSG_MAP(clPlot)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// clPlot message handlers

void clPlot::DrawBasic(CDC* pDC)
{
	CBrush brushctlBkColor(m_ctlBkColor);
	pDC->FillRect(m_ctlRect,&brushctlBkColor);//��CMyView��ͼ��䱳��ɫ
	//��������ͼ�߿�
	m_plotRect.left=m_ctlRect.left+leftmargin;
	m_plotRect.right=m_ctlRect.right-rightmargin;
	m_plotRect.top=m_ctlRect.top+topmargin;
	m_plotRect.bottom=m_ctlRect.bottom-bottommargin;
	//��������ͼ�߿�
	pDC->Rectangle(m_plotRect);
}

void clPlot::DrawXAxisGrid(CDC *pDC)
{
	CPen *old1, *old, pen(PS_SOLID, 1, m_gridColor);//����
	CPen stick(PS_SOLID,0,RGB(0,0,0));//�̶ȱ�
	CPen mline(PS_SOLID,0,RGB(192,192,192));//С���
//����С���ȣ���Ϊ��100��С��10�����
	smallgridwidth=((double)m_plotRect.right-(double)m_plotRect.left)/100;

	old1=pDC->SelectObject(&mline);
	double x;
	for(int i=1;i<=99;i++)
	{
		x=m_plotRect.left+smallgridwidth*i;
		//��10�����
		if(0==i%10)
		{
			old=pDC->SelectObject(&pen);
			pDC->MoveTo(CPoint(x,m_plotRect.bottom-2));
	    	pDC->LineTo(CPoint(x,m_plotRect.top+1));
			pDC->SelectObject(old);

		}
		//��10��С��
		else
		{
			pDC->MoveTo(CPoint(x,m_plotRect.bottom-2));
			pDC->LineTo(CPoint(x,m_plotRect.top+1));
		}
		//������̶�
		old=pDC->SelectObject(&stick);
		pDC->MoveTo(CPoint(x,m_plotRect.top));
		pDC->LineTo(CPoint(x,m_plotRect.top-off));
		pDC->MoveTo(CPoint(x,m_plotRect.bottom));
		pDC->LineTo(CPoint(x,m_plotRect.bottom+off));
		pDC->SelectObject(old);

	}
	pDC->SelectObject(old1);
}

void clPlot::DrawYAxisGrid(CDC *pDC)
{
	CPen *old, *old1, pen(PS_SOLID, 1, m_gridColor);
	CPen stick(PS_SOLID,0,RGB(0,0,0));
	CPen mline(PS_SOLID,0,RGB(192,192,192));
	CFont m_font;
	m_font.CreatePointFont(100,"Arial",pDC);
	pDC->SelectObject(&m_font);
	pDC->DrawText("1.0",CRect(m_plotRect.right+5,m_plotRect.bottom-10,m_plotRect.right+30,m_plotRect.bottom+10),DT_CENTER);
		pDC->DrawText("5.0",CRect(m_plotRect.right+5,m_plotRect.top-5,m_plotRect.right+30,m_plotRect.top+15),DT_CENTER);
	//�����Ϊ��ʮ��С��1-4V
	double smallgridwidth=((double)m_plotRect.top-(double)m_plotRect.bottom)/40;
	old1=pDC->SelectObject(&mline);
	double y;
	for(int i=1;i<=39;i++)
	{
		y=m_plotRect.bottom+smallgridwidth*i;
		if(0==i%10)
		{
			scalevalue++;
			old=pDC->SelectObject(&pen);
			pDC->MoveTo(CPoint(m_plotRect.right-2,y));
	    	pDC->LineTo(CPoint(m_plotRect.left+1,y));
			//�������̶�ֵ
			char b[20];
			sprintf(b,"%.1f",scalevalue);
			pDC->DrawText(b,CRect(m_plotRect.right+5,y-10,m_plotRect.right+30,y+10),DT_CENTER);
			pDC->SelectObject(old);
		}
		else
		{
			pDC->MoveTo(CPoint(m_plotRect.right-2,y));
	    	pDC->LineTo(CPoint(m_plotRect.left+1,y));
		}
		//������̶�
		old=pDC->SelectObject(&stick);
		pDC->MoveTo(CPoint(m_plotRect.left,y));
		pDC->LineTo(CPoint(m_plotRect.left-off,y));
		pDC->MoveTo(CPoint(m_plotRect.right,y));
		pDC->LineTo(CPoint(m_plotRect.right+off,y));
		pDC->SelectObject(old);
	}
	pDC->SelectObject(old1);
	scalevalue=1;
}

BOOL clPlot::AddPoint(CTime valuetime, float value)
{
//Ϊ�²����ĵ�����ڴ�,�˴�ע��malloc��realloc�������ڡ���Ŀ�ĵ�������һƪ����̸��������
	if(m_lNoValues > 0)
		m_pValue = (pValue*)realloc(m_pValue, (m_lNoValues+1)*sizeof(pValue));
	else
		m_pValue = (pValue*)malloc((m_lNoValues+1)*sizeof(pValue));
	//ע��m_pValueΪָ��pValue�ṹ���ָ�룬�����ǿ��԰ѵ���������ʹ��
	m_pValue[m_lend].dValue=value;
	m_pValue[m_lend].ValueTime=valuetime;
	m_lNoValues++;
	m_lend++;
	return TRUE;
}



void clPlot::DrawCurve(CDC* pDC)
{
	static int docnumber=0;
	docnumber++;
	CPen m_pen(PS_SOLID,1,RGB(255,0,0));//Ϊ����ͼ���߽����ĺ�ɫ����
	CPen* m_oldpen=pDC->SelectObject(&m_pen);
	//ʵ���õĲ���1-4�������
	float y=(double)(abs(rand())%20);
	float cy=y/4;
	if(cy<=1)
	{
		cy=1;
	}
	//����Ϊʵ������
	//����������Ĵ����ڴ棨ʵʱ���ݿ⣩
	AddPoint(CTime::GetCurrentTime(),cy);
	//�������������ݺ�ſ��Ի���һ����
	if(docnumber>=2)
	{
		int docnumber1=docnumber;
		//�������ǵ����������ͼ���ߴ�֮��ı���
		intervalY=m_plotRect.Height()/4;
		//��ĸ���С�ڵ���101ʱ
		if(docnumber<=100)
		{
			for(int i=0;i<docnumber-1;i++)
			{
				docnumber1--;
				//ע��VC��GDI��ͼ��Y���������ǳ��µģ�����������Ҫm_plotRect.Height()+topmargin-��ͼ�е�λ��
				pDC->MoveTo(CPoint(m_plotRect.left+smallgridwidth*(100-docnumber1),m_plotRect.Height()+topmargin-
					((m_pValue[i].dValue-1)*intervalY)));
				pDC->LineTo(CPoint(m_plotRect.left+smallgridwidth*(100-docnumber1+1),m_plotRect.Height()+topmargin-
					((m_pValue[i+1].dValue-1)*intervalY)));
			}
		}
		//��ĸ�������101ʱ���������ǵ�����ͼֻ����ʾ101���㣨100���񣩣����Ե���ĸ�������
		//101ʱ��������Ҫ��ʾ��101����
		else
		{
			for(int i=0;i<100;i++)
			{
				pDC->MoveTo(CPoint(m_plotRect.left+smallgridwidth*(i),m_plotRect.Height()+topmargin-
					((m_pValue[i+docnumber-1-100].dValue-1)*intervalY)));
				pDC->LineTo(CPoint(m_plotRect.left+smallgridwidth*(i+1),m_plotRect.Height()+topmargin-
					((m_pValue[i+docnumber-100].dValue-1)*intervalY)));
			}
		}
		pDC->SelectObject(m_oldpen);
	}
}

void clPlot::DrawLegend(CDC *pDC)
{
	//m_legendRectΪ����Сͼ�������
		m_legendRect.top=m_plotRect.top+50;
		m_legendRect.bottom=m_plotRect.top-15;
		m_legendRect.left=m_plotRect.left+20;
		m_legendRect.right=m_plotRect.left+150;
		CPen pen(PS_SOLID, 1, RGB(0,0,0));
		CPen *oPen = pDC->SelectObject(&pen);
		CBrush *oBrush , brush(m_legendBkColor);
		oBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(m_legendRect);
		pDC->SelectObject(oBrush);
		CPen m_pen(PS_SOLID,1,RGB(255,0,0));//Ϊ����ͼ���߽����ĺ�ɫ����
		pDC->SelectObject(&m_pen);
		pDC->MoveTo(CPoint(m_legendRect.left+10,m_legendRect.bottom+10));
		pDC->LineTo(CPoint(m_legendRect.left+40,m_legendRect.bottom+10));
		CFont m_font;
		m_font.CreatePointFont(90,"Arial",pDC);
		pDC->SelectObject(&m_font);
		pDC->TextOut(m_legendRect.left+60,m_legendRect.bottom+5,"ͨ��0");
		pDC->SelectObject(oPen);
}

void clPlot::DrawLegendShadow(CDC *pDC)
{
	
	CPen pen(PS_SOLID, 1, RGB(127,127,127));
	CPen *oPen = pDC->SelectObject(&pen);
	CBrush *oBrush , brush(RGB(127,127,127));
	oBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(CRect(m_legendRect.left+5,m_legendRect.top+5,m_legendRect.right+5, m_legendRect.bottom+5));
	pDC->SelectObject(oBrush);
	pDC->SelectObject(oPen);
	
}
