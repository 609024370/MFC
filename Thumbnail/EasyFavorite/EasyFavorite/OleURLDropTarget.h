//////////////////////////////////////////////////////////
//
//  ������ : ���켮
// ----------------------------------------------------
//  �� �ҽ��� ���� �ҽ��̸�, �� �ҽ��� ����� ���
//  �ݵ�� ���� �̸��� ���� �÷��ֽø� �����ϰڽ��ϴ�. ^^.
//
//  e-mail : seaousak@hotmail.com
//////////////////////////////////////////////////////////



#if !defined(AFX_OLEURLDROPTARGET_H__4B13BE66_7B3E_4FAA_B0A3_419EF939D700__INCLUDED_)
#define AFX_OLEURLDROPTARGET_H__4B13BE66_7B3E_4FAA_B0A3_419EF939D700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxole.h>

class COleURLDropTarget : public COleDropTarget  
{
public:
	COleURLDropTarget(CWnd* pParent = NULL);
	virtual ~COleURLDropTarget();

	void SetParent(CWnd* pParent);

   DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD 
                                                dwKeyState, CPoint point );
   DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD 
                                               dwKeyState, CPoint point );
   void OnDragLeave(CWnd* pWnd);
   
   BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT 
                                          dropEffect, CPoint point );

// ������
protected:
	CWnd* m_pParent;
};

#endif // !defined(AFX_OLEURLDROPTARGET_H__4B13BE66_7B3E_4FAA_B0A3_419EF939D700__INCLUDED_)
