// LineNet.h: interface for the LineNet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINENET_H__F1E66713_26BA_41F9_B1B9_F440CF362A09__INCLUDED_)
#define AFX_LINENET_H__F1E66713_26BA_41F9_B1B9_F440CF362A09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Gis.h"

class LineNet : public Gis  
{
	DECLARE_SERIAL(LineNet);
	friend class CGisInterface;
public:
	float m_x,m_y;		//����������
	float m_rRadiu;		//�����Բ�İ뾶
	short m_LinkNumb;	//ָ����������ӵ����Ŀ
	int	  m_LinkID[10];	//ָ���������ʶ���

public:
	virtual void Release();
	virtual void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);
	void AddLink(int nID);
	LineNet(short ColorPen,float x,float y,float rRadiu,short Layer,int id);
	LineNet();
	virtual ~LineNet();

};

#endif // !defined(AFX_LINENET_H__F1E66713_26BA_41F9_B1B9_F440CF362A09__INCLUDED_)
