#if !defined(AFX_MYSTATIC_H__B10E7BAF_1C1E_11D4_893F_0000B4B587FF__INCLUDED_)
#define AFX_MYSTATIC_H__B10E7BAF_1C1E_11D4_893F_0000B4B587FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyStatic window

class CMyStatic : public CStatic
{
// Construction
public:
	CMyStatic();						//���캯��
	COLORREF m_foreColor,m_backColor;	//ǰ��������ɫ
	BOOL m_bTrans;						//�Ƿ�͸��
	CFont * m_pFont;					//��ʾ����
// Attributes
public:
	//���¼��������ֱ����úͻ�ȡ��ʾ��ǰ��ɫ������ɫ�����塢͸������
	void SetForeColor(COLORREF foreColor);
	COLORREF GetForeColor();
	void SetBackColor(COLORREF backColor);
	COLORREF GetBackColor();
	void SetTransMode(BOOL bTrans);
	BOOL IsTrans();
	CFont * GetFontPtr();
	void SetFont(int nWeight,BOOL bItalic,BOOL bUnderlined,TCHAR * pFontName);
	void SetStyle(COLORREF foreColor,COLORREF backColor,BOOL bTrans);
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__B10E7BAF_1C1E_11D4_893F_0000B4B587FF__INCLUDED_)
