// MainFrm.h : interface of the CMainFrame class 
// 
///////////////////////////////////////////////////////////////////////////// 

#if !defined(AFX_MAINFRM_H__27D461AB_FCA7_4119_B32E_EDDF027485D8__INCLUDED_) 
#define AFX_MAINFRM_H__27D461AB_FCA7_4119_B32E_EDDF027485D8__INCLUDED_ 

#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 
#include <afxcview.h> 
#include "UpPaneView.h"  
#include "MyView.h"  
#include "EditPaneView.h" 
#include "SplitterWndEx.h" 
#include "clPlot.h" 
class CMainFrame : public CFrameWnd 
{ 

protected: // create from serialization only 
	CMainFrame(); 
	DECLARE_DYNCREATE(CMainFrame) 

	// Attributes 
public: 
	// Operations 
public: 
	RECT   rc;    
	int   FrmW,FrmH;    
	BOOL ifcreatesplitter; 
	BOOL ifrun; 
	CSplitterWndEx m_wndSplitter;  
	// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CMainFrame) 
public: 
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs); 
protected: 
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext); 
	//}}AFX_VIRTUAL 

	// Implementation 
public: 
	void SwitchDesign(); 
	void SwitchDisplay(); 
	virtual ~CMainFrame(); 
#ifdef _DEBUG 
	virtual void AssertValid() const; 
	virtual void Dump(CDumpContext& dc) const; 
#endif 

protected:  // control bar embedded members 
	CStatusBar  m_wndStatusBar; 
	CToolBar    m_wndToolBar; 

	// Generated message map functions 
protected: 
	//{{AFX_MSG(CMainFrame) 
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); 
	afx_msg void OnSize(UINT nType, int cx, int cy); 
	afx_msg void OnPaint(); 
	//}}AFX_MSG 
	DECLARE_MESSAGE_MAP() 
}; 

///////////////////////////////////////////////////////////////////////////// 

//{{AFX_INSERT_LOCATION}} 
// Microsoft Visual C++ will insert additional declarations immediately before the previous line. 

#endif // !defined(AFX_MAINFRM_H__27D461AB_FCA7_4119_B32E_EDDF027485D8__INCLUDED_) 