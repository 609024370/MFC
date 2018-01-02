#if !defined(AFX_GIS_H__4453A35C_3EDD_4614_94F5_BAEDE0219D72__INCLUDED_)
#define AFX_GIS_H__4453A35C_3EDD_4614_94F5_BAEDE0219D72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Gis.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Gis window
#define pi 3.1415926


class Gis : public CObject
{
	DECLARE_SERIAL(Gis);	
	friend class CGisInterface;
protected:
protected:
	void *pInetrface;	//����ӿ�
	void *pGraphPara;	//��ɫ�ӿ�
	int DLtoVL(float l);
	float VLtoDL(int l);
	float VPtoDP(int x,int y,float &X,float &Y);
	float DPtoVP(float x,float y,int &X,int &Y);
	double GetAngle(int x1,int y1,int x2,int y2);
	double GetAngle(double  x1,double y1,double x2,double y2);
protected:
	short m_ColorPen;	//������ɫ
	short m_ColorBrush;	//�����ɫ
	float m_LineWide;	//�߿�
	short m_LineType;	//������
	short m_Layer;		//����ͼ��
	BOOL  m_Delete;		//�Ƿ���ɾ��״̬
	int	  m_id;			//Ψһ��ʶ
// Construction	
public:
	Gis();

// Attributes
public:
	

public:
	virtual void Serialize(CArchive &ar);
	int Min(int x1,int x2);
	int Max(int x1,int x2);
	float Min(float x1,float x2);
	virtual void GetRect(float &MinX,float &MinY,float &MaxX,float &MaxY);
	float GetBlc();
	virtual void Release();
	void SetInterface(void *p);
	void SetGraphPara(void *p);
	double AngleToRadian(double Angle);
	virtual void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);
	int GetID();
	Gis(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,BOOL Delete);
	virtual ~Gis();
	float Max(float x1,float x2);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIS_H__4453A35C_3EDD_4614_94F5_BAEDE0219D72__INCLUDED_)
