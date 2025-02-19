#if !defined(AFX_VCLABEL_H__DC450E84_B846_4905_90B7_0E177AC5EA9D__INCLUDED_)
#define AFX_VCLABEL_H__DC450E84_B846_4905_90B7_0E177AC5EA9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CVcBackdrop;
class CVcFont;
class CVcTextLayout;
class COleFont;

/////////////////////////////////////////////////////////////////////////////
// CVcLabel wrapper class

class CVcLabel : public COleDispatchDriver
{
public:
	CVcLabel() {}		// Calls COleDispatchDriver default constructor
	CVcLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcLabel(const CVcLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CVcBackdrop GetBackdrop();
	CString GetFormat();
	void SetFormat(LPCTSTR lpszNewValue);
	CVcFont GetVtFont();
	BOOL GetAuto();
	void SetAuto(BOOL bNewValue);
	BOOL GetStanding();
	void SetStanding(BOOL bNewValue);
	CVcTextLayout GetTextLayout();
	short GetFormatLength();
	void SetRefFont(LPDISPATCH newValue);
	COleFont GetFont();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCLABEL_H__DC450E84_B846_4905_90B7_0E177AC5EA9D__INCLUDED_)
