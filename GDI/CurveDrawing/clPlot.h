#if !defined(AFX_CLPLOT_H__2E93C8B4_33F9_49F3_AD16_F1A6316F37D1__INCLUDED_)
#define AFX_CLPLOT_H__2E93C8B4_33F9_49F3_AD16_F1A6316F37D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// clPlot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// clPlot window
//���ǽ�����һ���ṹ�壬���ڴ����������ͼ�ϵĵ���Ϣ
struct pValue
	{
		CTime ValueTime;
		float dValue;
	};
class clPlot : public CWnd
{
// Construction
public:
	clPlot();

// Attributes
public:
	COLORREF	m_ctlBkColor;		//CMyView���ֵı�����ɫ
	CRect		m_ctlRect;			//CMyView���ֵ���ͼ�ߴ�
	CRect		m_plotRect;         //����ͼ����߿�
	COLORREF	m_gridColor;
	long		m_lNoValues;	// no values (used for array size)
	pValue*		m_pValue;		//����ͼ��Ľṹ��
	long		m_lend;			//��ǰ�ж��ٸ���
	double smallgridwidth;      //����С����
	float intervalX; 
	float intervalY;			//���ǵ����������ͼ���߶�֮��ı���
	int leftmargin;					//���������ĸ��հױ߿�ľ���           
	int rightmargin;
	int topmargin;
	int bottommargin;
	int off;					//�����̶ȳ���
	float scalevalue;			//����̶�ֵ
	COLORREF 	m_legendBkColor;  //����Сͼ�걳��ɫ
	CRect m_legendRect;				//����Сͼ������
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(clPlot)
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawLegendShadow(CDC* pDC);
	void DrawLegend(CDC* pDC);
	void DrawCurve(CDC* pDC);//��������
	BOOL AddPoint(CTime valuetime, float value);//��ʵʱ���ݼ��뵽ʵʱ���ݿ�
	void DrawYAxisGrid(CDC * pDC);//��������դ��
	void DrawXAxisGrid(CDC * pDC);//���ƺ���դ��
	void DrawBasic(CDC* pDC);//���Ʊ���
	virtual ~clPlot();

	// Generated message map functions
protected:
	//{{AFX_MSG(clPlot)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLPLOT_H__2E93C8B4_33F9_49F3_AD16_F1A6316F37D1__INCLUDED_)
