#if !defined(AFX_XTABCTRL_H__A11951B3_2F95_11D3_A896_00A0C9B6FB28__INCLUDED_)
#define AFX_XTABCTRL_H__A11951B3_2F95_11D3_A896_00A0C9B6FB28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// myTabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSVizTabCtrl window
#include <afxtempl.h>

class SVIZDLLEXPORT CSVizTabCtrl : public CTabCtrl
{
// Construction
public:
	CSVizTabCtrl();

// Attributes
public:

// Operations
public:
	void AddTab(CWnd* pWnd, LPTSTR lpszCaption, int iImage =0);
	void EnableTab(int iIndex, BOOL bEnable = TRUE);
	BOOL SelectTab(int iIndex);
	void DeleteAllTabs();
	void DeleteTab(int iIndex);
	void SetTopLeftCorner(CPoint pt);
	BOOL IsTabEnabled(int iIndex);

	void SetDisabledColor(COLORREF cr);
	void SetSelectedColor(COLORREF cr);
	void SetNormalColor(COLORREF cr);
	void SetMouseOverColor(COLORREF cr);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSVizTabCtrl)
	protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSVizTabCtrl();

	// Generated message map functions
protected:
	CArray<BOOL, BOOL> m_arrayStatusTab; //** enabled Y\N
	int m_iSelectedTab;
	POINT m_ptTabs;
	COLORREF m_crSelected;
	COLORREF m_crDisabled;
	COLORREF m_crNormal;
	COLORREF m_crMouseOver;

	int m_iIndexMouseOver;
	
	bool m_bMouseOver;
	bool m_bColorMouseOver;
	bool m_bColorNormal;
	bool m_bColorDisabled;
	bool m_bColorSelected;
	
	//{{AFX_MSG(CSVizTabCtrl)
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTABCTRL_H__A11951B3_2F95_11D3_A896_00A0C9B6FB28__INCLUDED_)
///////////////////////////////////////////////////////////////////////
// This file is a part of the SViz MFC Extention Class.
// 2001-2002 SVizSoft Software, All Rights Reserved.
//
// SVIZSOFT GRANTS TO YOU THE LIMITED RIGHT TO USE THIS SOFTWARE ON 
// A SINGLE COMPUTER. 
// THESE SOURCE FILE ARE CONSIDERED CONFIDENTIONAL AND ARE THE PROPERTY
// OF SVIZSOFT AND ARE NOT TO BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER
// WITHOUT THE EXPRESSED WRITTEN CONSENT OF SVIZ SOFTWARE.
// 
// You can contact us.
// admin@svizsoft.com
///////////////////////////////////////////////////////////////////////
