#include "stdafx.h"
#include <ctype.h>
#include "UGCtrl.h"
//#include "UGEdit.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
****************************************************/
CUGEdit::CUGEdit() : m_autoSize(TRUE), m_continueCol(0),
					 m_continueRow(0), 	m_lastKey(0) {
}

/***************************************************
****************************************************/
CUGEdit::~CUGEdit()
{
}

/***************************************************
****************************************************/
BEGIN_MESSAGE_MAP(CUGEdit, CEdit)
	//{{AFX_MSG_MAP(CUGEdit)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_MOUSEACTIVATE()
	ON_WM_SETCURSOR()
	ON_WM_GETDLGCODE()      
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/***************************************************
****************************************************/
void CUGEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);

	if( m_ctrl->m_GI->m_bCancelMode != FALSE )
	{
		if(pNewWnd->GetSafeHwnd() != NULL){
			if(pNewWnd != m_ctrl && pNewWnd->GetParent() != m_ctrl)
				m_cancel = TRUE;
		}
		else
			m_cancel = TRUE;
	}

	CString string;
	GetWindowText(string);
	if(m_ctrl->EditCtrlFinished(string,m_cancel,m_continueFlag,
	  m_continueCol,m_continueRow) == FALSE){
		m_ctrl->GotoCell(m_ctrl->m_editCol,m_ctrl->m_editRow);
		SetCapture();
		ReleaseCapture();
		SetFocus();
	}
}

/***************************************************
****************************************************/
void CUGEdit::OnSetFocus(CWnd* pOldWnd) 
{
	//get the original height
	RECT rect;
	GetClientRect(&rect);
	m_origHeight = rect.bottom +4;
	m_currentHeight = m_origHeight;

	CalcEditRect();


	m_cancel = FALSE;
	m_continueFlag = FALSE;

	SetSel(0,-1);
	
	m_lastKey = 0;
	
	CEdit::OnSetFocus(pOldWnd);
}

/***************************************************
****************************************************/
void CUGEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	m_lastKey = nChar;

	switch(nChar){
		case VK_TAB:{

			if(GetKeyState(VK_SHIFT)<0){
				m_continueCol = m_ctrl->m_editCol -1;
				m_continueRow = m_ctrl->m_editRow;
			}
			else{
				m_continueCol = m_ctrl->m_editCol +1;
				m_continueRow = m_ctrl->m_editRow;
			}

			m_continueFlag = TRUE;
			m_ctrl->SetFocus();
			return;
		}
		case VK_RETURN:{
			m_continueCol = m_ctrl->m_editCol;
			m_continueRow = m_ctrl->m_editRow +1;
			m_continueFlag = TRUE;
			m_ctrl->SetFocus();
			return;
		}
		case VK_ESCAPE:{
			m_cancel = TRUE;
			m_continueFlag = FALSE;
			m_ctrl->SetFocus();
			return;
		}
		case VK_UP:{
			
			if(m_currentHeight != m_origHeight)
				break;

			m_continueCol = m_ctrl->m_editCol;
			m_continueRow = m_ctrl->m_editRow-1;
			m_continueFlag = TRUE;
			m_ctrl->SetFocus();
			return;
		}
		case VK_DOWN:{
			
			if(m_currentHeight != m_origHeight)
				break;

			m_continueCol = m_ctrl->m_editCol;
			m_continueRow = m_ctrl->m_editRow+1;
			m_continueFlag = TRUE;
			m_ctrl->SetFocus();
			return;
		}
	}

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

/***************************************************
****************************************************/
void CUGEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	
	// allow OnEditVerify a look at the char...
	int col = m_ctrl->GetCurrentCol();
	long row = m_ctrl->GetCurrentRow();
	
	// First the datasource has a look ...
	if(m_ctrl->m_GI->m_defDataSource->OnEditVerify(col,row,this,&nChar) == FALSE)
		return;

	// then the ctrl class
	if(m_ctrl->OnEditVerify(col,row,this,&nChar)==FALSE)
		return;

	if(nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
		return;
	
	CEdit::OnChar(nChar, nRepCnt, nFlags);

}


/***************************************************
****************************************************/
int CUGEdit::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	return MA_ACTIVATE;
	//return CEdit::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

/***************************************************
****************************************************/
BOOL CUGEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(LoadCursor(NULL,IDC_IBEAM));
	return 1;
}


/***************************************************
****************************************************/
void CUGEdit::OnUpdate() 
{
	CalcEditRect();

}

/***************************************************
****************************************************/
void CUGEdit::CalcEditRect(){
		
	if(!m_autoSize)
		return;
	
	CString string;
	RECT	editRect;
	RECT	parentRect;
	RECT	fmtRect;
	CDC*	dc;
	CFont*	oldFont;

	GetWindowText(string);
	string += _T(" X X");

	GetWindowRect(&editRect);
	m_ctrl->m_editParent->ScreenToClient(&editRect);

	m_ctrl->m_editParent->GetClientRect(&parentRect);

	dc = GetDC();
	if(GetFont() != NULL)
		oldFont = (CFont *)dc->SelectObject(GetFont());

	CopyRect(&fmtRect,&editRect);
	fmtRect.right = parentRect.right;
	fmtRect.left +=2;
	
	dc->DrawText(string,&fmtRect,DT_CALCRECT|DT_WORDBREAK);
 	
	fmtRect.left -=2;

	if(GetFont() != NULL)
		dc->SelectObject(oldFont);
	ReleaseDC(dc);

	//if(fmtRect.right < editRect.right)
	//	fmtRect.right = editRect.right;

	if(fmtRect.bottom >= parentRect.bottom)
		fmtRect.bottom = parentRect.bottom - 1;

	
	if(fmtRect.right > editRect.right){
		int col;
		long row;
		RECT rect;
		m_ctrl->GetCellFromPoint(fmtRect.right+1,fmtRect.top+1,&col,&row,&rect);
		if(rect.right > parentRect.right)
			rect.right = parentRect.right;

		fmtRect.right = rect.right -1;
	}
	

	if(fmtRect.bottom > editRect.bottom){
		fmtRect.right = parentRect.right;
		int col;
		long row;
		RECT rect;
		m_ctrl->GetCellFromPoint(fmtRect.left +1,fmtRect.bottom+1,&col,&row,&rect);
		fmtRect.bottom = rect.bottom -1;
	}

	if(fmtRect.bottom >= parentRect.bottom)
		fmtRect.bottom = parentRect.bottom - 1;

	if(fmtRect.bottom < editRect.bottom)
		fmtRect.bottom = editRect.bottom;
	if(fmtRect.right < editRect.right)
		fmtRect.right = editRect.right;


	if(fmtRect.right != editRect.right || fmtRect.bottom != editRect.bottom){
		MoveWindow(&fmtRect,TRUE);
		GetParent()->ValidateRect(&fmtRect);
		m_currentHeight = fmtRect.bottom - fmtRect.top;
	}
}
/***************************************************
****************************************************/
BOOL CUGEdit::SetAutoSize(BOOL state){
	BOOL old = m_autoSize;

	if(state)
		m_autoSize = TRUE;
	else 
		m_autoSize = FALSE;

	return old;
}
/***************************************************
****************************************************/
UINT CUGEdit::OnGetDlgCode() 
{
	if(GetKeyState(VK_TAB)<0)
		return DLGC_WANTTAB;
	else if (GetKeyState(VK_RETURN)<0)
		return  DLGC_WANTALLKEYS;
	else if (GetKeyState(VK_ESCAPE)<0)
		return  DLGC_WANTALLKEYS;
	return CEdit::OnGetDlgCode();
}

/***************************************************
	GetLastKey is handy if you need to know if
	ESC cancelled the edit.  Key state is not 
	saved (shift, ctrl etc)
****************************************************/
UINT CUGEdit::GetLastKey() {
	return m_lastKey;
}