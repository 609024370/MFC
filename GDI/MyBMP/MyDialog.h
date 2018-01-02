#if !defined(AFX_MYDIALOG_H__E10DB6E0_03C5_11D4_893F_0000B4B587FF__INCLUDED_)
#define AFX_MYDIALOG_H__E10DB6E0_03C5_11D4_893F_0000B4B587FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDialog.h : header file
// download by http://www.codefans.net

/////////////////////////////////////////////////////////////////////////////
// CMyDialog dialog

#include "Dib.h"
//�������
#define BACK_STYLE_NORMAL 0					//��ͨ��û�����ⱳ��
#define BACK_STYLE_BITMAP 1					//��λͼ��Ϊ����
#define BACK_STYLE_COLORED 2				//��ָ����ɫ��Ϊ����
//λͼ��ʾ���
#define BMP_STYLE_ORIGIN 0					//��λͼԭ��С��ʾ
#define BMP_STYLE_STRETCH 1					//��λͼ������ʾ
#define BMP_STYLE_TILE 2					//λͼƽ��

class CMyDialog : public CDialog
{
// Construction
public:
	//���صĹ��캯����pBmpNameĬ��ΪNULL�������ͺ���ͨ��CDialogһ���Ĺ���
	CMyDialog(const UINT IDD,CWnd* pParent = NULL,LPCTSTR pBmpName = NULL);
	virtual ~CMyDialog();					//��������
	virtual void Initialize();				//��ʼ������
	virtual void Empty();					//��պ���
	virtual BOOL LoadBmp(LPCTSTR pBmpName);	//����Bitmap
	//���¼��������ֱ����úͻ�ñ�����ʾ��񡢱�����ɫ��λͼ��ʾ���
	int GetBackStyle() { return m_nBackStyle; }
	CBrush * GetBackBrush() { return m_pBackBrush; }
	int GetBmpStyle() { return m_nBmpStyle; }
	void SetBackStyle(int nBackStyle);
	void SetBackBrush(COLORREF color);
	void SetBmpStyle(int nBmpStyle);
protected:
	CDib * m_pDib;							//����ͼ��CDib��ָ��
	CBrush * m_pBackBrush;					//������ɫ����
	int m_nBackStyle;						//������ʾ���
	int m_nBmpStyle;						//λͼ��ʾ���
// Dialog Data
	//{{AFX_DATA(CMyDialog)
	//��MyDialog��IDע�͵���ʹ�������ID
	//enum { IDD = _UNKNOWN_RESOURCE_ID_ };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
//protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDialog)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOG_H__E10DB6E0_03C5_11D4_893F_0000B4B587FF__INCLUDED_)
