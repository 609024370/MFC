#if !defined(AFX_VCDATAPOINTS_H__5D4C79BB_F780_4DDE_9FF9_2FD216D40869__INCLUDED_)
#define AFX_VCDATAPOINTS_H__5D4C79BB_F780_4DDE_9FF9_2FD216D40869__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CVcDataPoint;

/////////////////////////////////////////////////////////////////////////////
// CVcDataPoints wrapper class

class CVcDataPoints : public COleDispatchDriver
{
public:
	CVcDataPoints() {}		// Calls COleDispatchDriver default constructor
	CVcDataPoints(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcDataPoints(const CVcDataPoints& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	CVcDataPoint GetItem(short Index);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCDATAPOINTS_H__5D4C79BB_F780_4DDE_9FF9_2FD216D40869__INCLUDED_)
