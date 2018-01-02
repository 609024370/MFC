// ConditionListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TestMyCanEditList.h"
#include "ConditionListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConditionListCtrl

CConditionListCtrl::CConditionListCtrl()
{
}

CConditionListCtrl::~CConditionListCtrl()
{
}


BEGIN_MESSAGE_MAP(CConditionListCtrl, CMyCanEditListCtrl)
	//{{AFX_MSG_MAP(CConditionListCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConditionListCtrl message handlers

void CConditionListCtrl::InitColumn()
{
	for(int i=this->GetHeaderCtrl()->GetItemCount()-1;i>=0;i--)
	{
		this->DeleteColumn(i);
	}
    //��ΪListCtrl�ĵ�һ��ʼ����LVCFMT_LEFT��
	//Ϊ��ʹ�������еı���ﵽLVCFMT_CENTER��Ч��,�Ȳ���һ������,��ɾ������
	InsertColumn(0,"test",LVCFMT_LEFT,70);
	InsertColumn(1,"���",LVCFMT_RIGHT,70);
	InsertColumn(2,"����",LVCFMT_LEFT,100);
	InsertColumn(3,"�Ա�",LVCFMT_CENTER,80);
	InsertColumn(4,"������λ",LVCFMT_LEFT,100);
	InsertColumn(5,"��ϵ�绰",LVCFMT_LEFT,100);
	InsertColumn(6,"��ע",LVCFMT_LEFT,80);
	DeleteColumn(0);////

	m_arrColType.RemoveAll();
	for(int j=0;j<6;j++)
	{
		m_arrColType.Add("11");
	}

	this->m_strArrColumnFmt.RemoveAll();
	this->m_strArrColumnFmt.Add("LVCFMT_RIGHT");
	this->m_strArrColumnFmt.Add("LVCFMT_LEFT");
	this->m_strArrColumnFmt.Add("LVCFMT_CENTER");
	this->m_strArrColumnFmt.Add("LVCFMT_LEFT");
	this->m_strArrColumnFmt.Add("LVCFMT_LEFT");
	this->m_strArrColumnFmt.Add("LVCFMT_LEFT");
	//////////
	this->SetSortColumn(FALSE);

	SetSubItemCanEdited(0);
	SetSubItemCanEdited(1);
	SetSubItemCanEdited(2);
	SetSubItemCanEdited(3);
	SetSubItemCanEdited(4);
	SetSubItemCanEdited(5);

	SetSubItemCanListBox(2);

}

void CConditionListCtrl::OnComboBoxSetFocus(const int &item, const int &subitem)
{
	CMyCanEditListCtrl::OnEditSetFocus(item,subitem);

	this->m_ComboBox.ResetContent();

	switch(subitem)
	{
	
	case 2:
		
		m_ComboBox.AddString("��");
		m_ComboBox.AddString("Ů");
		
		break;
	
	default:
		break;
	}

}

BOOL CConditionListCtrl::CreateChild()
{
	if( CMyCanEditListCtrl::CreateChild()!=TRUE)
	{
		return FALSE;
	}

	this->SetListCtrlFontSize(16);
	this->SetChildEditFontSize(16);
	this->SetChildComboBoxFontSize(12);

	return TRUE;

}

void CConditionListCtrl::InitItem()
{
	CMyCanEditListCtrl::InitItem();

}

BOOL CConditionListCtrl::InitListCtrl()
{
	if(CMyCanEditListCtrl::InitListCtrl()!=TRUE)
	{
		return FALSE;
	}

	return TRUE;


}
