// HtmlViewsDoc.h : interface of the CHtmlViewsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLVIEWSDOC_H__DB2D2F5C_1190_11D2_8436_0000B43382FE__INCLUDED_)
#define AFX_HTMLVIEWSDOC_H__DB2D2F5C_1190_11D2_8436_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CHtmlViewsDoc : public CDocument
{
protected: // create from serialization only
	CHtmlViewsDoc();
	DECLARE_DYNCREATE(CHtmlViewsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlViewsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHtmlViewsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHtmlViewsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLVIEWSDOC_H__DB2D2F5C_1190_11D2_8436_0000B43382FE__INCLUDED_)
