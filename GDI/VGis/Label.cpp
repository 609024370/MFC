// Label.cpp: implementation of the CLabel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vgis.h"
#include "Label.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "GraphicsPara.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CLabel,CObject,1)
CLabel::CLabel()
{	
	this->SetDefaultLogFont(m_lf);
	m_MinDisp=0;
	m_MaxDisp=20;
}

CLabel::~CLabel()
{

}

CLabel::CLabel(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY,float MaxDisp,float MinDisp,LOGFONT lf, CString text)
	   :Gis(ColorPen,ColorBrush,LineWide,LineType,Layer ,id,Delete)
{
	m_StartX=StartX;
	m_StartY=StartY;
	m_Text=text;
	m_MaxDisp=MaxDisp;
	m_MinDisp=MinDisp;
	m_lf=lf;
}

void CLabel::Draw(CDC *pDC, int DrawMode, int DrawMode1, short BackColor)
{
	if (m_Delete)//ɾ������
		return;

	if (this->GetBlc()<m_MinDisp || this->GetBlc()>m_MaxDisp)
		return;

	GraphicsPara *p_GP=0;
	p_GP = (GraphicsPara * )pGraphPara;

	int x1,y1;

	short ColorPen=m_ColorPen;

	if (DrawMode1==2)
	{
		ColorPen=BackColor;
	}

	CFont Font;
	

	if (DrawMode==0)
		pDC->SetROP2(R2_COPYPEN);
	else if (DrawMode==1)
		pDC->SetROP2(R2_NOT);

	pDC->SetBkMode(TRANSPARENT);
		
	this->DPtoVP(m_StartX,m_StartY,x1,y1);

	//��������
	Font.CreateFontIndirect(&m_lf);    
	
	CFont *pOldFont=pDC->SelectObject(&Font);	//ѡ������
	pDC->SetBkMode(TRANSPARENT);				//���û���ģʽ

	pDC->SetTextColor(p_GP->GetColor(ColorPen));//�����ı���ɫ

	pDC->TextOut(x1,y1,m_Text);	//����Ļ�ϻ��ƺ���


	pDC->SelectObject(pOldFont);
}

void CLabel::SetPara(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float MaxDisp, float MinDisp, LOGFONT lf, CString text)
{
	{
		m_ColorPen		=ColorPen;	//������ɫ
		m_ColorBrush	=ColorBrush;	//�����ɫ
		m_LineWide		=LineWide;	//�߿�
		m_LineType		=LineType;	//������
		m_Layer			=Layer;		//����ͼ��
		m_Delete		=Delete;		//�Ƿ���ɾ��״̬
		m_id			=id;			//Ψһ��ʶ	
	}
	m_StartX=StartX;
	m_StartY=StartY;
	m_Text=text;
	m_MaxDisp=MaxDisp;
	m_MinDisp=MinDisp;
	m_lf=lf;
}

void CLabel::SetPara(float StartX, float StartY, float MaxDisp, float MinDisp, LOGFONT lf, CString text)
{
	m_StartX=StartX;
	m_StartY=StartY;
	m_Text=text;
	m_MaxDisp=MaxDisp;
	m_MinDisp=MinDisp;
	m_lf=lf;
}

void CLabel::SetPara(CLabel &la)
{
	m_StartX=la.m_StartX;
	m_StartY=la.m_StartY;
	m_lf=la.m_lf;
	m_Text=la.m_Text;
	m_MaxDisp=la.m_MaxDisp;
	m_MinDisp=la.m_MinDisp;
}

void CLabel::SetDefaultLogFont(LOGFONT &lf)
{
	CFont font;
	font.CreateFont(
		14,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"����");
	font.GetLogFont(&lf);
}

void CLabel::Serialize(CArchive &ar)
{
	Gis::Serialize(ar);
	if (ar.IsStoring())
	{
//		ar<<m_MaxDisp<<m_MinDisp<<m_StartX<<m_StartY<<m_Text<<m_lf.lfCharSet<<m_lf.lfClipPrecision<<m_lf.lfEscapement<<m_lf.lfFaceName<<m_lf.lfHeight<<m_lf.lfItalic<<m_lf.lfOrientation<<m_lf.lfOutPrecision<<m_lf.lfPitchAndFamily<<m_lf.lfQuality<<m_lf.lfStrikeOut<<m_lf.lfUnderline<<m_lf.lfWeight<<m_lf.lfWidth;
	}
	else
	{
	//	ar>>m_MaxDisp>>m_MinDisp>>m_StartX>>m_StartY>>m_Text>>m_lf.lfCharSet>>m_lf.lfClipPrecision>>m_lf.lfEscapement>>m_lf.lfFaceName>>m_lf.lfHeight>>m_lf.lfItalic>>m_lf.lfOrientation>>m_lf.lfOutPrecision>>m_lf.lfPitchAndFamily>>m_lf.lfQuality>>m_lf.lfStrikeOut>>m_lf.lfUnderline>>m_lf.lfWeight>>m_lf.lfWidth;
	}
}
