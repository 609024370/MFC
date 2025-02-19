// MSDITestView.h : interface of the CMSDITestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSDITESTVIEW_H__58EAB96F_E2C7_11D4_AF92_C0ABC2000000__INCLUDED_)
#define AFX_MSDITESTVIEW_H__58EAB96F_E2C7_11D4_AF92_C0ABC2000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMSDITestView : public CView
{
protected: // create from serialization only
	CMSDITestView();
	DECLARE_DYNCREATE(CMSDITestView)

// Attributes
public:
	CMSDITestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSDITestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMSDITestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMSDITestView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MSDITestView.cpp
inline CMSDITestDoc* CMSDITestView::GetDocument()
   { return (CMSDITestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSDITESTVIEW_H__58EAB96F_E2C7_11D4_AF92_C0ABC2000000__INCLUDED_)
