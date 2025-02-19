#if !defined(AFX_COLORCHECKBOX_H__FDC9C955_9912_11D3_90E8_0020AFBC499D__INCLUDED_)
#define AFX_COLORCHECKBOX_H__FDC9C955_9912_11D3_90E8_0020AFBC499D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorCheckBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMacCheckBox window

class CMacCheckBox : public CButton
{
// Construction
public:
	CMacCheckBox();

// Attributes
public:

// Operations
public:
	void SetCheck(int nCheck);
	int GetCheck() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMacCheckBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMacCheckBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMacCheckBox)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void DrawCheckMark(CDC *pDC, CRect rect, UINT nStyle, UINT nState);
	COLORREF m_crFace;
	COLORREF m_crShadow;
	COLORREF m_crHilight;
	COLORREF m_crDkShadow;
	COLORREF m_crLiteShadow;
	void GetColors();
	void RedrawCheck();
	BOOL m_bMouseDown;
	BOOL m_bChecked;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCHECKBOX_H__FDC9C955_9912_11D3_90E8_0020AFBC499D__INCLUDED_)
