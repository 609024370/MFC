// GisInterface.h: interface for the CGisInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GISINTERFACE_H__DDB02E76_054A_4CF2_B961_FFF0F7F81861__INCLUDED_)
#define AFX_GISINTERFACE_H__DDB02E76_054A_4CF2_B961_FFF0F7F81861__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graphics.h"
#include "TextDialog.h"

class CGisInterface : public CWnd  
{
private://��������
	CPoint pt1,pt2;
	CTextDialog m_TextDlg;				//��ע�ı��༭
	float T_x1,T_y1;					//��ע�ı�����
	CString T_PreText;					//��һ�α�ע�ı�
	PointStruct *m_Ps;					//����κͶ��ߵ���ʱ�洢��
	HCURSOR  m_cursor;					//���
	CBitmap   m_pBitmap;				//�ƶ�ʱ�����λͼ
	CDC m_MemDC;						//����λͼ��DC
private://��ͼ����
	LRESULT ChangeLabel(WPARAM wParam,LPARAM lParam);
	void ChangeText(CText *pText,int lParam);

	short m_PenColor;					//��ǰ������ɫ���
	short m_BkColor;					//������ɫ���
	short m_BrushColor;					//��ǰ��ˢ��ɫ���
	short m_LineWide;					//��ǰ�߿��
	short m_LineType;					//��ǰ����
	short m_Layer;						//��ǰͼ��
	BOOL  m_bFill;						//�Ƿ����

protected://��ͼ����
	int m_DrawCurrent;					//��ǰҪ���еĻ�ͼ��ʽ
	int m_PushNumber;					//�µĻ�ͼ��ʽ ��갴�µĴ���
public:
	Graphics m_Graph;


protected:	//ת����Ļ����
	int	  m_Brink;						//��Ե���
	float m_StartX,m_StartY,m_blc;		//��Ļ���½�ʵ������ͱ�����
	int   m_ScreenWidth,m_ScreenHeight; //�洢ͼ����Ļ��ʵ�ʿ�Ⱥ͸߶�
	int	  m_MapMode;					//�豸ӳ�䷽ʽ
	float m_MaxX,m_MaxY,m_MinX,m_MinY;	//�����С����


public:
	BOOL  Create(CWnd* lParent,const RECT& rect , DWORD dwStyle = WS_CHILD | WS_BORDER |WS_TABSTOP | WS_VISIBLE);
	//��Ļת�������� ����
	void SetScreenFromMaxMin(float MaxX,float MaxY,float MinX,float MinY,int Brink);
	void SetMapMode(int MapMode);
	int DLtoVL(float l);
	float VLtoDL(int l);
	void SetStartOrg(float x,float y,float blc);
	float VPtoDP(int x,int y,float &X,float &Y);
	float DPtoVP(float x,float y,int &X,int &Y);


public:
	virtual void Serialize(CArchive &ar);
	void AllGraph();
	void SetStartXY(float x,float y);
	float GetBlc();
	void SetBlc(float blc,CPoint pt);
	int SetDraw(int style);
	BOOL GetNetXY(int NetID,float &x,float &y,BOOL &Delete);
	void SetScreen(int ScreenWidth, int ScreenHeight);
	void Draw(CDC *pDC);
	CGisInterface();
	virtual ~CGisInterface();
protected:
	// Generated message map functions
	//{{AFX_MSG(CGisInterface)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_GISINTERFACE_H__DDB02E76_054A_4CF2_B961_FFF0F7F81861__INCLUDED_)
