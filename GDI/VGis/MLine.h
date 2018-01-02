// MLine.h: interface for the MLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MLINE_H__F90A79B6_6A1B_435C_9A6B_7E8648BA8F81__INCLUDED_)
#define AFX_MLINE_H__F90A79B6_6A1B_435C_9A6B_7E8648BA8F81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Gis.h"
typedef struct
{
	float x;
	float y;
	float z;
}PointStruct;

class MLine : public Gis  //�����������
{
	DECLARE_SERIAL(MLine);	
	friend class CGisInterface;
protected:
	int	m_Number;				//����ֱ�ߵĶ�����Ŀ
	PointStruct	*m_PointList;	//�洢���������ָ��
	float m_MLineLong;			//����ֱ�ߵĳ���
public:
	virtual void Serialize(CArchive &ar);
	virtual void GetRect(float &MinX, float &MinY, float &MaxX, float &MaxY);
	virtual void Release();
	virtual void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);
	MLine(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,int Number,PointStruct *PointList);
	MLine();
	virtual ~MLine();

};

#endif // !defined(AFX_MLINE_H__F90A79B6_6A1B_435C_9A6B_7E8648BA8F81__INCLUDED_)
