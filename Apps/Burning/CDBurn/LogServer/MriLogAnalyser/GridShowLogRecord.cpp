#include "stdafx.h"
#include "GridShowLogRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NUM_COLUMNS	12
static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
//		_T("�������"),
		_T("��ʼʱ��"),
		_T("����ʱ��"),
		_T("���˾���"),  
		_T("OPC"),
		_T("�Զ˾���"), 
		_T("DPC"),
		_T("SLC"),
		_T("��·��"),
		_T("Tx/Rx"),
		_T("�澯����"),
		_T("�澯������"),
		_T("��ע")
};
static int _gnColumnFmt[NUM_COLUMNS] = 
{
//		UG_ALIGNLEFT, 
		UG_ALIGNLEFT, 
		UG_ALIGNLEFT,
		UG_ALIGNLEFT,
		UG_ALIGNLEFT,
		UG_ALIGNLEFT,
		UG_ALIGNLEFT,
		UG_ALIGNCENTER,
		UG_ALIGNLEFT,
		UG_ALIGNLEFT,
		UG_ALIGNLEFT,
		UG_ALIGNLEFT,
		UG_ALIGNLEFT
};
static int _gnColumnWidth[NUM_COLUMNS] = 
{
//		150,
		150,
		150,
		70,
		80,
		70,
		80,
		40,
		60,
		40,
		50,
		90,
		90		
};

BEGIN_MESSAGE_MAP(CGridShowLogRecord,CUGCtrl)
	//{{AFX_MSG_MAP(CGridShowLogRecord)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int  LQSort_Func( const void * p1, const void * p2 );
CGridShowLogRecord *gPAlmthis = NULL;

//***************************************************
CGridShowLogRecord::CGridShowLogRecord()
{
	m_sortCol         = 0;
	m_sortedAscending = TRUE;

}

CGridShowLogRecord::~CGridShowLogRecord()
{
}

void CGridShowLogRecord::OnSetup()
{
	int rows = 1;
	int cols = NUM_COLUMNS;

	m_font.CreateFont( 14,0,0,0,500,0,0,0,0,0,0,0,0,"Arial" );
	SetDefFont(&m_font);
	
	m_sArrowIndex = AddCellType(&m_sortArrow);
	m_normalCellIndex = AddCellType(&m_normalCellType);
	SetUniformRowHeight(TRUE);

	CUGCell cell;
	GetGridDefault(&cell);
	cell.SetAlignment(UG_ALIGNLEFT);
	cell.SetHBackColor(RGB(255,192,192));
	cell.SetHTextColor(RGB(0,0,0));
	SetGridDefault(&cell);

	SetNumberRows(rows);
	SetNumberCols(cols);

	SetVScrollMode(UG_SCROLLTRACKING);

	SetBallisticMode(3);
	SetBallisticDelay(100);

	m_blackPen.CreatePen(PS_SOLID,1,RGB(100,100,100));

	SetCurrentCellMode(2);

	SetColWidth( -1, 50 );
	for ( int i=0; i< NUM_COLUMNS; i++ )
	{
		SetColWidth( i, _gnColumnWidth[i] );
	}
	SetDoubleBufferMode(1);

/*
	QuickSetCellType(m_sortCol,-1,m_sArrowIndex);
	QuickSetCellTypeEx(m_sortCol,-1,UGCT_SORTARROWDOWN);
	*/

}

void CGridShowLogRecord::OnGetCell(int col,long row,CUGCell *cell)
{
	cell->SetBackColor( GetSysColor( COLOR_BTNFACE ) );

	CString temp;
	if (!m_bMuteFlag) return;

	if (row < 0)
	{
		if (col < 0)
		{
			temp = "���";
		}
		else if ( col >=0 && col < NUM_COLUMNS )
		{
			temp = _gszColumnLabel[col];
		}
	}
	else
	{
/*
		if ( m_vAlmLstIdx.size() == 0 || row >= m_vAlmLstIdx.size() )
			return;
*/
				
		switch(col)
		{
/*
			case -1:// ���
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sNo;
				break;
			case 0:// ��ʼʱ��
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sStartTime;
				break;
			case 1:// ����ʱ��
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sEndTime;
				break;
			case 2:// ��ʼ�ֵ�����
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sStartPcName;
				break;
			case 3:// OPC
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sOpc;
				break;
			case 4:// ��ֹ�ֵ�����
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sEndPcName;
				break;
			case 5:// DPC
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sDpc;
				break;							
			case 6:// SLC
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sSlc;
				break;							
			case 7:// ��·��
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].pLnk->sZclinkcode;
				break;							
			case 8:// Tx/Rx
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sTxRx;
				break;
			case 9:// �澯����
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sAlmType;
				break;
			case 10:// �澯������
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sAlmSType;
				break;
			case 11:// ��ע
				temp = m_vAlmRecLstLnk[ m_vAlmLstIdx[row] ].sRemark;
				break;
*/
				
			default:
				temp = "";
				break;
		}
	}

	cell->SetText(temp);

	if ( row >= 0 && col >= 0 )
	{
//		cell->SetTextColor( GetAlmColorBySTypCode( m_vAlmRecLstLnk[  m_vAlmLstIdx[row]  ].nAlmStyp ) );
	}
}

void CGridShowLogRecord::Refresh()
{
}

void CGridShowLogRecord::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	
	if(updn == 0) return;
}

//  ��������
int  LQSort_Func( const void * p1, const void * p2 )
{
	int *pRow1 = (int*)p1;
	int *pRow2 = (int*)p2;
	int ret;
	CString Str1,Str2;

		return  ret;
}

