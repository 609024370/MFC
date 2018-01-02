// Graphics.h: interface for the Graphics class.
//
//////////////////////////////////////////////////////////////////////
#include <afxtempl.h>
#if !defined(AFX_GRAPHICS_H__26BBD078_6BA7_4859_838D_6333F78CD0B4__INCLUDED_)
#define AFX_GRAPHICS_H__26BBD078_6BA7_4859_838D_6333F78CD0B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define G_LINE 1		//��
#define G_MLINE 2		//������
#define G_CIRCLE 3		//Բ
#define G_ARC 4			//Բ��
#define G_TEXT 5		//
#define G_TAG 6			//��ͼ
#define G_MLINERGN 7	//�����	
#define G_LINENET 8		//����ڵ�
#define G_LABEL 9		//��ǩ
#define G_BIG 10		//�Ŵ�
#define G_SMALL 11		//��С
#define G_MOVE 12		//�ƶ�
#define G_RECT 13	//�ֲ��Ŵ�
#define G_ALL 14		//�鿴ȫͼ

#define MAX_STYLE 9

#include "Line.h"
#include "Circle.h"
#include "Arc.h"
#include "Text.h"
#include "MLine.h"
#include "MLineRgn.h"
#include "LineNet.h"
#include "GraphicsPara.h"
#include "Tag.h"
#include "Label.h"


class Graphics  
{
friend class CGisInterface;
private:
	int m_MaxID[MAX_STYLE];				//��ͼ�����ID
private:
	//����ͼ��
	CTypedPtrArray<CObArray,Line*> m_LineArray;
	CTypedPtrArray<CObArray,Circle*> m_CircleArray;
	CTypedPtrArray<CObArray,CArc*> m_ArcArray;
	CTypedPtrArray<CObArray,CText*> m_TextArray;
	CTypedPtrArray<CObArray,MLine*> m_MLineArray;
	CTypedPtrArray<CObArray,MLineRgn*> m_MLineRgnArray;
	CTypedPtrArray<CObArray,LineNet*> m_LineNetArray;
	CTypedPtrArray<CObArray,Tag*> m_TagArray;
	CTypedPtrArray<CObArray,CLabel*>m_LabelArray;
	//��ɫ
	GraphicsPara m_GraphPara;		//��ɫ����
	void *p_Interface;				//�ӿڻ���
public:
	virtual void Serialize(CArchive& ar);
	BOOL GetRect(float &MinX,float &MinY,float &MaxX,float &MaxY);
	void SetInterface(void *p);
	int CreateID(int Lb);
	void DrawBack(CDC *pDC,int cx,int cy,int bColor);
	void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);

	
	//����ͼ��
	LineNet * AddLineNetToLineNet(int sID/*Ŀ��ID*/,int eID/*Ҫ���ӵ�ID */);//��eID ���ӵ�sID
	int GetGraphIndex(short Lb,int ID);//����ָ��ID��ͼ�δ���±�
	int GetGraphUpperBound(short Lb);//���ָ��ͼ�ε�����±�
	int GetGraphSize(short Lb);//���ָ��ͼ�δ洢������
	void DeleteGraph(int Lb,int index);//ɾ��ָ��ͼ��ָ��������
	Gis* GetGraph(short Lb,int index);//���ָ��ͼ��ָ������

	//�����µ�ͼ��	
	CLabel* AddLabel(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY,float MaxDisp,float MinDisp,LOGFONT lf, CString text);
	LineNet * AddLineNet(short ColorPen, float x, float y, float rRadiu, short Layer, int id);
	MLine* AddMLine(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,int Number,PointStruct *PointList);
	MLineRgn* AddMLineRgn(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,int Number,PointStruct *PointList,bool bTransparent,bool bFill);
	CText* AddText(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float Angle1, float Angle2, float TextHeight, float TextWide, float OffWide, byte TextFont, CString text);
	Circle* AddCircle(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,float CircleX,float CircleY,float CircleR,bool bFill);
	CArc* AddArc(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,float CircleX,float CircleY,float CircleR,bool bFill,float Angle1,float Angle2);
	Line* AddLine(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,float x1,float y1,float x2,float y2);
	Tag* AddTag(short ColorPen, int Layer, bool Delete, float InsertX, float InsertY, float ScaleX, float ScaleY, float Angle, int id, int idBlock);

	Graphics();
	virtual ~Graphics();

};

#endif // !defined(AFX_GRAPHICS_H__26BBD078_6BA7_4859_838D_6333F78CD0B4__INCLUDED_)
