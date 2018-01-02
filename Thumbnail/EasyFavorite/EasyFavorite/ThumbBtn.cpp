//////////////////////////////////////////////////////////
//
//  ������ : ���켮
// ----------------------------------------------------
//  �� �ҽ��� ���� �ҽ��̸�, �� �ҽ��� ����� ���
//  �ݵ�� ���� �̸��� ���� �÷��ֽø� �����ϰڽ��ϴ�. ^^.
//
//  e-mail : seaousak@hotmail.com
//////////////////////////////////////////////////////////


// ThumbBtn.cpp : implementation file
//

#include "stdafx.h"
#include "EasyFavorite.h"
#include "ThumbBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CThumbCtl

IMPLEMENT_DYNCREATE(CThumbCtl, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CThumbCtl operations

BOOL CThumbCtl::displayFile(LPCTSTR bsFileName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bsFileName);
	return result;
}

BOOL CThumbCtl::haveThumbnail()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString CThumbCtl::FreeSpace()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CThumbCtl::UsedSpace()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CThumbCtl::TotalSpace()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}




/////////////////////////////////////////////////////////////////////////////
// CThumbBtn

CThumbBtn::CThumbBtn():m_strURL("temp.html")
{
}

CThumbBtn::~CThumbBtn()
{
}


BEGIN_MESSAGE_MAP(CThumbBtn, CButton)
	//{{AFX_MSG_MAP(CThumbBtn)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThumbBtn message handlers

int CThumbBtn::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rcBtn;	// Button�� ũ�⸦ ���մϴ�.
	GetWindowRect(rcBtn);

	// ThumbCtrl�� ũ�⸦ Button�� ũ�⺸�� �� 5 pixel ���� ���Դϴ�.
	CRect rcThumb;
	rcThumb.left = 5;
	rcThumb.top = 5;
	rcThumb.right = rcBtn.Width() - 5;
	rcThumb.bottom = rcBtn.Height() -5;
	
	m_ctrThumb.Create("ThumbCtrl",WS_VISIBLE|WS_CHILD,rcThumb,this, IDC_THUMB);	
	m_ctrThumb.displayFile(m_strURL);

	return 0;
}

void CThumbBtn::SetURL(CString strURL/* Short-Cut �� ��ġ */)
{
	m_ctrThumb.displayFile(strURL);
	m_strURL = strURL;
}

void CThumbBtn::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ShellExecute(NULL, "open",m_strURL, NULL, NULL, SW_SHOWNORMAL);

	CButton::OnLButtonDown(nFlags, point);
}
