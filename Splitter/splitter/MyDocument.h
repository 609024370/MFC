#if !defined(AFX_MYDOCUMENT_H__CF47D871_5027_11D5_AC0B_00104B2CD040__INCLUDED_)
#define AFX_MYDOCUMENT_H__CF47D871_5027_11D5_AC0B_00104B2CD040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDocument.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDocument document

class CMyDocument : public CDocument
{
protected:
	CMyDocument();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyDocument)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDocument)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDOCUMENT_H__CF47D871_5027_11D5_AC0B_00104B2CD040__INCLUDED_)
