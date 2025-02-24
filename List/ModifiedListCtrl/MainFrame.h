/////////////////////////////////////////////////////////////////////////////
// MainFrame.h : interface of the CMainFrame class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRAME_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_MAINFRAME_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000

	/////////////////////////////////////////////////////////////////////////////
	// Class CMainFrame
	/////////////////////////////////////////////////////////////////////////////
	class CMainFrame : public CMDIFrameWnd {
		DECLARE_DYNAMIC(CMainFrame)

		public:
			CMainFrame();

		// Attributes
		public:

		// Operations
		public:

		// Overrides
			// ClassWizard generated virtual function overrides
			//{{AFX_VIRTUAL(CMainFrame)
		public:
			virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
			//}}AFX_VIRTUAL

		// Implementation
		public:
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
				// NOTE - the ClassWizard will add and remove member functions here.
				//    DO NOT EDIT what you see in these blocks of generated code!
			//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
	};
	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_MAINFRAME_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
