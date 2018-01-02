// MLineRgn.cpp: implementation of the MLineRgn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VGis.h"
#include "MLineRgn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "GraphicsPara.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(MLineRgn,CObject,1)

MLineRgn::MLineRgn()
{
	m_Number=0;
}

MLineRgn::~MLineRgn()
{

}

MLineRgn::MLineRgn(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, int Number, PointStruct *PointList, bool bTransparent, bool bFill)
		 :MLine(ColorPen, ColorBrush, LineWide, LineType, Layer , id, Delete, Number,PointList)
{
	m_bTransparent=bTransparent;
	m_bFill=bFill;
}

void MLineRgn::Draw(CDC *pDC, int DrawMode, int DrawMode1, short BackColor)
{
    int i;

	if (m_Delete)//ɾ������
		return;
	GraphicsPara *p_GP=0;
	p_GP = (GraphicsPara * )pGraphPara;

	short LineType=0;
	short ColorPen=m_ColorPen;
	if (DrawMode==0)
		pDC->SetROP2(R2_COPYPEN);		//����ģʽ
	else if (DrawMode==1)
		pDC->SetROP2(R2_NOT);			//�趨��дģʽ

	short lt=0;
	if (DrawMode1==1)
	{
		LineType=1;
		lt=2;
	}
	else if (DrawMode1==2)
	{
		ColorPen=BackColor;				//���������ó�BackColor��ɫ��
	}
	short Number=m_Number;
	m_PointList[Number++]=m_PointList[0];
	POINT *ppt=new POINT[Number*4+1];	//BUG?
	CRgn rgn;
	for (int i=0;i<Number;i++)			//��ʵ������ת������Ļ�߼����꣬������ppt�Ժ����ʹ��
	{
		int x1,y1;
		DPtoVP(m_PointList[i].x,m_PointList[i].y,x1,y1);
		ppt[i].x=x1;
		ppt[i].y=y1;
	}

	CPen pen(lt,1,p_GP->GetColor(ColorPen));	//������ѡ�񻭱�
	CPen *pOldPen=pDC->SelectObject(&pen);
	
	for (i=0;i<Number-1;i++)//��ͼ
	{
		pDC->MoveTo(ppt[i]);
		pDC->LineTo(ppt[i+1]);
	}

	if (DrawMode1==0 || DrawMode1==2)//�����������ʾ
	{
		if (m_bFill)
		{
			COLORREF lColor=p_GP->GetColor(m_ColorBrush);
			if (DrawMode1==2)
				lColor=p_GP->GetColor(BackColor);
			CBrush brush(lColor);
			CBrush *pOldBrush=pDC->SelectObject(&brush);
			if (this->m_bTransparent)
				pDC->SetROP2(R2_NOP);
			else
				pDC->SetROP2(R2_COPYPEN);
			pDC->Polygon(ppt,Number);//���ƶ����
			pDC->SelectObject(pOldBrush);
			pDC->SetROP2(R2_COPYPEN);

		}
	}
	else if (DrawMode1==1)			//�����ѡ��ʱ������ʾ
	{
		rgn.CreatePolygonRgn(ppt,Number,1);	//����һ������
		pDC->InvertRgn(&rgn);

	}
	pDC->SelectObject(pOldPen);
	delete ppt;
}

void MLineRgn::Release()
{
	delete this;
}


void MLineRgn::GetRect(float &MinX, float &MinY, float &MaxX, float &MaxY)
{
	MinX=m_PointList[0].x;
	MinY=m_PointList[0].y;
	MaxX=m_PointList[0].x;
	MaxY=m_PointList[0].y;
	for (int i=1;i<m_Number;i++)
	{
		MinX=Min(MinX,m_PointList[i].x);
		MaxX=Max(MaxX,m_PointList[i].x);

		MinY=Min(MinY,m_PointList[i].y);
		MaxY=Max(MaxY,m_PointList[i].y);

	}
}

void MLineRgn::Serialize(CArchive &ar)
{
	MLine::Serialize(ar);

	int tran=0;
	
	int fill=0;


	if (ar.IsStoring())
	{
		if (m_bTransparent)
			tran=1;
		
		if (m_bFill)
			fill=1;

		ar<<fill<<m_mRgnArea<<tran;
	}
	else
	{
		ar>>fill>>m_mRgnArea>>tran;
	
		if (fill)
			m_bFill=true;
		else 
			m_bFill=false;
	}
}
