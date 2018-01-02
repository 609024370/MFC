// Text.h: interface for the Text class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXT_H__6163B3C2_83E3_4EEB_8F9A_2B36321FED6E__INCLUDED_)
#define AFX_TEXT_H__6163B3C2_83E3_4EEB_8F9A_2B36321FED6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Gis.h"

class CText : public Gis  
{
	friend class CGisInterface;
protected:
	float m_StartX;		//��������
	float m_StartY;		//���������
	float m_Angle1;		//��ע�Ƕ�
	float m_Angle2;		//��ת�Ƕ�
	float m_TextHeight;	//����߶�
	float m_TextWide;	//������
	float m_OffWide;	//������
	byte  m_TextFont;	//��������
	CString m_Text;		//�ı�����
	int	  m_TextLong;	//�ı�����
public:

	void SetPara(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float Angle1, float Angle2,float TextHeight,float TextWide,float OffWide, byte TextFont, CString text);
	virtual void Release();
	virtual void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);
	CText(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float Angle1, float Angle2,float TextHeight,float TextWide,float OffWide, byte TextFont, CString text);
	CText();
	virtual ~CText();

};

#endif // !defined(AFX_TEXT_H__6163B3C2_83E3_4EEB_8F9A_2B36321FED6E__INCLUDED_)
