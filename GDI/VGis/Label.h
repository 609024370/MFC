// Label.h: interface for the CLabel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABEL_H__56DE6788_2065_4A82_9C46_9FAF8BACCDF2__INCLUDED_)
#define AFX_LABEL_H__56DE6788_2065_4A82_9C46_9FAF8BACCDF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Gis.h"

class CLabel : public Gis  
{
	DECLARE_SERIAL(CLabel);	
	friend class CGisInterface;
public:
	float m_StartX;		//��������
	float m_StartY;		//���������
	CString m_Text;		//�ı�����
	LOGFONT m_lf;		//����
	float m_MaxDisp;	//������ֵ
	float m_MinDisp;	//��С����ֵ
public:
	virtual void Serialize(CArchive &ar);
	void SetDefaultLogFont(LOGFONT &lf);
	void SetPara(CLabel &la);
	void SetPara(float StartX, float StartY, float MaxDisp, float MinDisp, LOGFONT lf, CString text);
	void SetPara(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY,float MaxDisp,float MinDisp,LOGFONT lf, CString text);
	virtual void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);
	CLabel(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float MaxDisp,float MinDisp,LOGFONT lf, CString text);
	CLabel();
	virtual ~CLabel();
	
};

#endif // !defined(AFX_LABEL_H__56DE6788_2065_4A82_9C46_9FAF8BACCDF2__INCLUDED_)
