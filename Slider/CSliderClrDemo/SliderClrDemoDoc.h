// SliderClrDemoDoc.h : interface of the CSliderClrDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLIDERCLRDEMODOC_H__3B3BC8E8_9B92_4925_B7D8_3EE80DAD8067__INCLUDED_)
#define AFX_SLIDERCLRDEMODOC_H__3B3BC8E8_9B92_4925_B7D8_3EE80DAD8067__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSliderClrDemoDoc : public CDocument
{
protected: // create from serialization only
	CSliderClrDemoDoc();
	DECLARE_DYNCREATE(CSliderClrDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSliderClrDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSliderClrDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSliderClrDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDERCLRDEMODOC_H__3B3BC8E8_9B92_4925_B7D8_3EE80DAD8067__INCLUDED_)
