// LineNet.cpp: implementation of the LineNet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VGis.h"
#include "LineNet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "GraphicsPara.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "GisInterface.h"
#include "Math.h"

IMPLEMENT_SERIAL( LineNet, CObject, 1 )

LineNet::LineNet()
{

}

LineNet::~LineNet()
{

}

LineNet::LineNet(short ColorPen, float x, float y, float rRadiu, short Layer, int id)
{
	m_ColorPen=ColorPen;
	m_x=x;
	m_y=y;
	m_rRadiu=rRadiu;
	m_Layer=Layer;
	m_id=id;
}

void LineNet::AddLink(int nID)
{
	for (int i=0;i<this->m_LinkNumb;i++)//����½ڵ��Ƿ����
	{
		if (nID==this->m_LinkID[i])//�½ڵ��Ѿ�����
			return;
	}
	m_LinkID[m_LinkNumb++]=nID;

}

void LineNet::Draw(CDC *pDC, int DrawMode, int DrawMode1, short BackColor)
{
	if (m_Delete)//ɾ������
		return;
	GraphicsPara *p_GP=0;
	p_GP = (GraphicsPara * )pGraphPara;
	CGisInterface *pInter=(CGisInterface*)pInetrface;

	if (DrawMode==0)
		pDC->SetROP2(R2_COPYPEN);
	else if (DrawMode==1)
		pDC->SetROP2(R2_NOT);
	short ColorPen = m_ColorPen;
	if (DrawMode1==2)
		ColorPen=BackColor;
	
	CPen pen(0,1,p_GP->GetColor(ColorPen));
	CPen *pOldPen=pDC->SelectObject(&pen);

	int x1,y1,x2,y2,x3,y3;
	DPtoVP(m_x,m_y,x1,y1);
	int rr=DLtoVL(m_rRadiu);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Ellipse(x1-rr,y1-rr,x1+rr,y1+rr);	//������������Բ
	BOOL bDelete;
	float xx,yy;
	if (DrawMode1==0)						//������������ƣ�����ָ�������������
	{
		for (int i=0;i<this->m_LinkNumb;i++)//�����е�����ѭ��
		{
			BOOL pb=pInter->GetNetXY(this->m_LinkID[i],xx,yy,bDelete);
			if (!pb || bDelete)
				continue;
			//�õ�ָ�����������ķ���
			double angle=this->AngleToRadian(this->GetAngle(xx,yy,m_x,m_y));
			DPtoVP(xx,yy,x2,y2);
			pDC->MoveTo(x1,y1);
			pDC->LineTo(x2,y2);
			//���Ƽ�ͷ����
			x2=(int)(x2*0.75+x1*0.25);
			y2=(int)(y2*0.75+y1*0.25);
			pDC->MoveTo(x2,y2);
			x3=x2+(int)(10*cos(angle+pi/6));
			y3=y2-(int)(10*sin(angle+pi/6));
			pDC->LineTo(x3,y3);
			pDC->MoveTo(x2,y2);
			x3=x2+(int)(10*cos(angle-pi/6));
			y3=y2-(int)(10*sin(angle-pi/6));
			pDC->LineTo(x3,y3);
		}
	}

	pDC->SelectObject(pOldPen);

}

void LineNet::Release()
{
	delete this;
}
