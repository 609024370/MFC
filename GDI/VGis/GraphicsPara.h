// GraphicsPara.h: interface for the GraphicsPara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSPARA_H__8371E831_B0A3_4599_9C6F_1FCE87722895__INCLUDED_)
#define AFX_GRAPHICSPARA_H__8371E831_B0A3_4599_9C6F_1FCE87722895__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct 
{
	char m_Name[21];	//ͼ�������
	BOOL m_Disp;		//�Ƿ���ʾ
	int	 m_reserved;	//����
}LayerStruct;

class GraphicsPara :public CObject   
{
	DECLARE_SERIAL(GraphicsPara);	
protected:
	int m_ColorNumberAll;		//�ܵ���ɫ��
	int m_LayerNumberAll;		//�ܵ�ͼ����
	int m_ColorNumber;			//ϵͳ��ǰ���е���ɫ��
	int	m_LayerNumber;			//ϵͳ��ǰ���е�ͼ����
	COLORREF* m_ColorList;			//�洢��ɫ������
	LayerStruct *m_LayerList;	//ͼ�������
public:
	virtual void Serialize(CArchive &ar);
	BOOL GetDisplayStatue(int n);
	COLORREF GetColor(int n);
	GraphicsPara();
	virtual ~GraphicsPara();

};

#endif // !defined(AFX_GRAPHICSPARA_H__8371E831_B0A3_4599_9C6F_1FCE87722895__INCLUDED_)
