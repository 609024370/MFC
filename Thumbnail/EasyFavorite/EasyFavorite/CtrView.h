//////////////////////////////////////////////////////////
//
//  ������ : ���켮
// ----------------------------------------------------
//  �� �ҽ��� ���� �ҽ��̸�, �� �ҽ��� ����� ���
//  �ݵ�� ���� �̸��� ���� �÷��ֽø� �����ϰڽ��ϴ�. ^^.
//
//  e-mail : seaousak@hotmail.com
//////////////////////////////////////////////////////////


#if !defined(AFX_CTRVIEW_H__F9E2FE7B_79B6_4349_AC38_CF41551A96F1__INCLUDED_)
#define AFX_CTRVIEW_H__F9E2FE7B_79B6_4349_AC38_CF41551A96F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CtrView.h : header file
//

#include "shlobj.h"

#define THUMB_WIDTH		200
#define THUMB_HEIGHT	200
#define THUMB_OFFSET	20
#define LEFT_OFFSET		10
#define RIGHT_OFFSET	10
#define TOP_OFFSET		10
#define BOTTOM_OFFSET	10

/////////////////////////////////////////////////////////////////////////////
// CCtrView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "OleURLDropTarget.h"

class CCtrView : public CFormView
{
public:
	CCtrView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCtrView)

// Form Data
public:
	//{{AFX_DATA(CCtrView)
	enum { IDD = IDD_CTRL_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	COleURLDropTarget	m_OleTarget;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtrView)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	HRESULT CreateInterShortcut (LPCSTR pszURL, LPCSTR pszURLfilename,
		LPCSTR szDescription,LPCTSTR szIconFile = NULL,int nIndex = -1);
	void RegisterOLE();
	void AddFavorite(CString strURL);
	virtual void PostNcDestroy();
	virtual BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual ~CCtrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCtrView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// ������
protected:
	int m_nTotalHeight;
	int m_nTotalThumb;
	int m_nControlID;

	CObArray		m_arrayThumb;	// CThumbBtn �� ���� Object Array �� ����ϴ�.
	CStringArray	m_arrayURL;		// URL �ּҸ� ���� ���� Object Array �� ����ϴ�.

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRVIEW_H__F9E2FE7B_79B6_4349_AC38_CF41551A96F1__INCLUDED_)
