// Circle.h: interface for the Circle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLE_H__07E58CB4_555E_4925_A966_09C84821717E__INCLUDED_)
#define AFX_CIRCLE_H__07E58CB4_555E_4925_A966_09C84821717E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Gis.h"

class Circle : public Gis  
{
	DECLARE_SERIAL(Circle);	
	friend class CGisInterface;
public:
	virtual void Serialize(CArchive &ar);
	virtual void GetRect(float &MinX, float &MinY, float &MaxX, float &MaxY);
	virtual void Release();
	virtual void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);
	Circle(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,float CircleX,float CircleY,float CircleR,bool bFill);
	Circle();
	virtual ~Circle();
protected:
	float	m_CircleX,m_CircleY,m_CircleR;	//Բ�ĵ������Լ��뾶
	BOOL	m_bFill;						//�Ƿ���� 1-���,0-��ͨ
	float	m_CircleLong;					//�ܳ�
	float	m_CircleArea;					//���
};

#endif // !defined(AFX_CIRCLE_H__07E58CB4_555E_4925_A966_09C84821717E__INCLUDED_)
