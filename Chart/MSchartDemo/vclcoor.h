#if !defined(AFX_VCLCOOR_H__C7AD8FA6_E63C_422C_9FB8_83598CE7B08C__INCLUDED_)
#define AFX_VCLCOOR_H__C7AD8FA6_E63C_422C_9FB8_83598CE7B08C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CVcLCoor wrapper class

class CVcLCoor : public COleDispatchDriver
{
public:
	CVcLCoor() {}		// Calls COleDispatchDriver default constructor
	CVcLCoor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcLCoor(const CVcLCoor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetX();
	void SetX(long nNewValue);
	long GetY();
	void SetY(long nNewValue);
	void Set(long X, long Y);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCLCOOR_H__C7AD8FA6_E63C_422C_9FB8_83598CE7B08C__INCLUDED_)
