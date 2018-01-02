// Text.cpp: implementation of the Text class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VGis.h"
#include "Text.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "GraphicsPara.h"
#include "math.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CText::CText()
{

}

CText::~CText()
{

}

CText::CText(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float Angle1, float Angle2,float TextHeight,float TextWide,float OffWide, byte TextFont, CString text)
	 :Gis(ColorPen,ColorBrush,LineWide,LineType,Layer ,id,Delete)
{
	m_StartX=StartX;
	m_StartY=StartY;
	m_Angle1=Angle1;
	m_Angle2=Angle2;
	m_TextHeight=TextHeight;
	m_TextWide=TextWide;
	m_OffWide=OffWide;
	m_Text=text;
}

void CText::Draw(CDC *pDC, int DrawMode, int DrawMode1, short BackColor)
{
	if (m_Delete)//ɾ������
		return;
	GraphicsPara *p_GP=0;
	p_GP = (GraphicsPara * )pGraphPara;

	short ColorPen=m_ColorPen;

	if (DrawMode1==2)
	{
		ColorPen=BackColor;
	}

	CFont Font;
	int high,wide,cc1,cc2,cd,angg;
	byte c1,c2;
	float x1,y1,ang1;
	char bz[4];
	const char *ls1;

	if (DrawMode==0)
		pDC->SetROP2(R2_COPYPEN);
	else if (DrawMode==1)
		pDC->SetROP2(R2_NOT);

	pDC->SetBkMode(TRANSPARENT);
	high=DLtoVL(m_TextHeight);		//��������߼��߶�
	ang1=(float)(m_Angle1*pi/180);	//����ı���X�����򻡶�
	if (high<3 || high > 200)		//����̫�����̫С����ʾ
		return;

	x1=m_StartX-m_TextHeight*(float)sin(ang1);	//��ע����ʵ�ʺ�����
	y1=m_StartY+m_TextHeight*(float)cos(ang1);	//��ע����ʵ��������

	angg=(int)(m_Angle2*10);
	wide=DLtoVL(m_TextWide);		//�����߼�������
	DPtoVP(x1,y1,cc1,cc2);			//��ע�����߼�����

	//��������
	Font.CreateFont(high,wide,angg,0,50,0,0,0,255,
		OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_SWISS, 
		"����");                 
	CFont *pOldFont=pDC->SelectObject(&Font);	//ѡ������
	pDC->SetBkMode(TRANSPARENT);				//���û���ģʽ
	pDC->SetTextColor(p_GP->GetColor(ColorPen));//�����ı���ɫ
	ls1=(const char *)m_Text;					//�ַ�ָ��ָ���ı�
	cd=strlen(ls1);
	while (cd>0)
	{//while
		c1=*ls1;
		c2=*(ls1+1);
		if (c1>127 && c2>127)			//�ж��Ƿ��Ǻ���
		{//if 127
			strncpy(bz,ls1,2);			//�����ú���
			bz[2]=0;					//
			ls1=ls1+2;					//�����ú���
			pDC->TextOut(cc1,cc2,bz);	//����Ļ�ϻ��ƺ���
			cd=cd-2;					//�ַ����ȼ�2
			//������һ���ַ���ʾ��λ��
			x1=x1+(m_TextWide*2+m_OffWide)*(float)cos(ang1);
			y1=y1+(m_TextWide*2+m_OffWide)*(float)sin(ang1);
			DPtoVP(x1,y1,cc1,cc2);//�õ����ַ���λ��
		}//End if 127
		else
		{
			strncpy(bz,ls1,1);		//����������ĸ
			bz[1]=0;
			ls1++;
			pDC->TextOut(cc1,cc2,bz);
			cd=cd-1;
			//������һ���ַ���ʾ��λ��
			x1=x1+(m_TextWide*1+m_OffWide)*(float)cos(ang1);
			y1=y1+(m_TextWide*1+m_OffWide)*(float)sin(ang1);
			DPtoVP(x1,y1,cc1,cc2);//�õ����ַ���λ��
		}
	}//End while

	pDC->SelectObject(pOldFont);


}

void CText::Release()
{
	delete this;
}

void CText::SetPara(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float Angle1, float Angle2,float TextHeight,float TextWide,float OffWide, byte TextFont, CString text)
{
	int nb=Delete;
	Gis::Gis(ColorPen,ColorBrush,LineWide,LineType,Layer,id,Delete);
	m_StartX=StartX;
	m_StartY=StartY;
	m_Angle1=Angle1;
	m_Angle2=Angle2;
	m_TextHeight=TextHeight;
	m_TextWide=TextWide;
	m_OffWide=OffWide;
	m_Text=text;
}


