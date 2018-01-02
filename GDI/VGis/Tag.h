// Tag.h: interface for the Tag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAG_H__5DA24C03_E573_415D_BC93_F2C45FB23950__INCLUDED_)
#define AFX_TAG_H__5DA24C03_E573_415D_BC93_F2C45FB23950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Gis.h"

#include "Block.h"

class Tag : public Gis  
{
	friend class CGisInterface;
protected:
	int m_idBlock;		//��ͼ��ı�ʶ��
	float m_InsertX;	//�����ĺ�����
	float m_InsertY;	//������������
	float m_ScaleX;		//�����������
	float m_ScaleY;		//�����������
	float m_Angle;		//��ͼ��ת�Ƕ�
	CBlock * p_Block;	//ָ���ӿ��ָ��
	
public:
	virtual void Release();
	Tag(short ColorPen,int Layer,bool Delete ,float InsertX,float InsertY,float ScaleX,float ScaleY,float Angle,int id,int idBlock);
	Tag();
	virtual ~Tag();

};

#endif // !defined(AFX_TAG_H__5DA24C03_E573_415D_BC93_F2C45FB23950__INCLUDED_)
