// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyListCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
	m_bSortColumn=TRUE;//Ĭ�ϵ����ͷ������
	m_nSortItem=0;//Ĭ�ϵ�һ��
	m_bMode=TRUE;//Ĭ�Ͻ���
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteitem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers
int CALLBACK CMyListCtrl::MyCompareProcStrD(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	
	CMyListCtrl* pListCtrl = (CMyListCtrl*)lParamSort;
	//ASSERT( pListCtrl->IsKindOf( RUNTIME_CLASS( CMyListCtrl ) ) );
	
	CString strItem1 = pListCtrl->GetItemText((int)lParam1,pListCtrl->m_nSortItem);
	CString strItem2 = pListCtrl->GetItemText((int)lParam2,pListCtrl->m_nSortItem);
    
	return strcmp(strItem1,strItem2);
	
}

int CALLBACK CMyListCtrl::MyCompareProcStrA(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	
	CMyListCtrl* pListCtrl = (CMyListCtrl*)lParamSort;
	//ASSERT( pListCtrl->IsKindOf( RUNTIME_CLASS( CMyListCtrl ) ) );
	
	CString strItem1 = pListCtrl->GetItemText((int)lParam1,pListCtrl->m_nSortItem);
	CString strItem2 = pListCtrl->GetItemText((int)lParam2,pListCtrl->m_nSortItem);

    return strcmp(strItem1,strItem2)*-1;

}

int CALLBACK CMyListCtrl::MyCompareProcNumD(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	
	CMyListCtrl* pListCtrl = (CMyListCtrl*)lParamSort;
	//ASSERT( pListCtrl->IsKindOf( RUNTIME_CLASS( CMyListCtrl ) ) );
	
	CString strItem1 = pListCtrl->GetItemText((int)lParam1,pListCtrl->m_nSortItem);
	CString strItem2 = pListCtrl->GetItemText((int)lParam2,pListCtrl->m_nSortItem);
    
	double numItem1,numItem2;
	numItem1=atof(strItem1);
	numItem2=atof(strItem2);
	
	if(numItem1-numItem2>0.0)
		return 1;
	else
		return -1;
	
}

int CALLBACK CMyListCtrl::MyCompareProcNumA(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	
	CMyListCtrl* pListCtrl = (CMyListCtrl*)lParamSort;
	//ASSERT( pListCtrl->IsKindOf( RUNTIME_CLASS( CMyListCtrl ) ) );
	
	CString strItem1 = pListCtrl->GetItemText((int)lParam1,pListCtrl->m_nSortItem);
	CString strItem2 = pListCtrl->GetItemText((int)lParam2,pListCtrl->m_nSortItem);
    
	double numItem1,numItem2;
	numItem1=atof(strItem1);
	numItem2=atof(strItem2);
	
	if(numItem1-numItem2>=0.0)
		return -1;
	else
		return 1;
	
}

void CMyListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(m_bSortColumn)
	{

	if( pNMListView->iSubItem == m_nSortItem )
	{
        m_bMode = !m_bMode;
	}
	else
	{
		m_bMode = !m_bMode;
	    m_nSortItem = pNMListView->iSubItem;
	}

	BeginWaitCursor();
	SortColumn(m_nSortItem, m_bMode);
	EndWaitCursor();
	/*
	int count;
	count=GetItemCount();
	for (int i = 0; i < count; i++)
	{
	     SetItemData(i, i);
	}
	CString strType;
	strType=m_ColType.GetAt(nSortItem);
	//AfxMessageBox(strType);
	BeginWaitCursor();
	if(strType=="4")//����
	{
		if(bMode)
            SortItems(MyCompareProcNumD,(DWORD)this);
		else
		    SortItems(MyCompareProcNumA,(DWORD)this);
	}
	else//���ַ�����
	{
		if(bMode)
		    SortItems(MyCompareProcStrD,(DWORD)this);
		else
			SortItems(MyCompareProcStrA,(DWORD)this);

	}
	EndWaitCursor();
	*/
	}
	/////////
	*pResult = 0;
}

void CMyListCtrl::SortColumn(int column, BOOL descent)
{
	int count;
	count=GetItemCount();
	for (int i = 0; i < count; i++)
	{
	     SetItemData(i, i);
	}
	CString strType;
	strType=m_arrColType.GetAt(column);
	BOOL flag;
	//AfxMessageBox(strType);
	if(strType=="4")//����
	{
		if(descent)//����
             flag=SortItems(MyCompareProcNumD,(DWORD)this);
		else//����
		    flag=SortItems(MyCompareProcNumA,(DWORD)this);
	}
	else//���ַ�����
	{
		if(descent)//����
		    flag=SortItems(MyCompareProcStrD,(DWORD)this);
		else
			flag=SortItems(MyCompareProcStrA,(DWORD)this);
	}

}

//������,Ч����ͬ�ڵ����ͷ
void CMyListCtrl::ClickColumn(int column, BOOL descent)
{
	
	CHeaderCtrl *pHeaderCtrl;
	int columnCount;
	pHeaderCtrl=this->GetHeaderCtrl();
	columnCount=pHeaderCtrl->GetItemCount();
	if(columnCount==0)//����е�����Ϊ0,�˳�
		return;

	m_bMode = descent;
	m_nSortItem = column;

    BeginWaitCursor();
	SortColumn( column,  descent);
	EndWaitCursor();
    
}


void CMyListCtrl::DeleteSelected()
{
    int nitem ;
	CUIntArray delArray;
	POSITION pos;
	pos = GetFirstSelectedItemPosition();
    if (pos == NULL)
	{
		AfxMessageBox("�����б�������ѡ��һ��!");
        return;
	}
	while(pos)
	{
        nitem= GetNextSelectedItem(pos);
	    delArray.Add(nitem);
	}
	int i,j;
 	int temp;
	//��������齵������
 	for(i=0;i<delArray.GetSize();i++)
	{
 		for( j=i;j<delArray.GetSize();j++)
 		{
 			if(delArray.GetAt(i)<delArray.GetAt(j))
 			{
 				temp=delArray.GetAt(i);
                delArray.SetAt(i,delArray.GetAt(j));
 				delArray.SetAt(j,temp);
 			}
 		}
	}
	for(i=0;i<delArray.GetSize();i++)
	{
	    DeleteItem(delArray.GetAt(i));
	}
}


void CMyListCtrl::DeleteNoSelected()
{
    int nitem ;
	CUIntArray selectedArray;
	//CUIntArray delArray;
	POSITION pos;
	pos = GetFirstSelectedItemPosition();
    if (pos == NULL)
	{
		AfxMessageBox("�����б�������ѡ��һ��!");
        return;
	}
	while(pos)
	{
        nitem= GetNextSelectedItem(pos);
	    selectedArray.Add(nitem);
	}
	CString str;
	int i,j;
 	int temp;
	//��������齵������
 	for(i=0;i<selectedArray.GetSize();i++)
	{
 		for( j=i;j<selectedArray.GetSize();j++)
 		{
 			if(selectedArray.GetAt(i)<selectedArray.GetAt(j))
 			{
 				temp=selectedArray.GetAt(i);
                selectedArray.SetAt(i,selectedArray.GetAt(j));
 				selectedArray.SetAt(j,temp);
 			}
 		}
	}
    /////
	BOOL delFlag;
	for(i=GetItemCount()-1;i>=0;i--)
	{
		if(i>int(selectedArray.GetAt(0)))
		{
			DeleteItem(i);
		}
		delFlag=TRUE;
		for(j=0;j<selectedArray.GetSize();j++)
		{
			if(i==int(selectedArray.GetAt(j)))
			{
				delFlag=FALSE;
				break;
			}
		}
		
		if(delFlag==TRUE)
		{
			//str.Format("delIndex=%d",i);
			//AfxMessageBox(str);
			DeleteItem(i);
		}
	}
	
}

void CMyListCtrl::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

BOOL CMyListCtrl::IsSortColumn()
{
	return this->m_bSortColumn;

}

void CMyListCtrl::SetSortColumn(BOOL bSortColumn)
{
    this->m_bSortColumn=bSortColumn;
}
