#include "StdAfx.h"
#include "SeeFileViewTable.h"

SeeFileViewTable::SeeFileViewTable(void)
{
	// TODO:  �ڴ������ר�õĴ�������

	m_bSelectedFileEnable=true;								//�Ƿ���Ҫ�����ļ�
	m_bDealMouseAction=true;
	m_iDragInfo=-1;											//����ק���������͵�LIST��ʱ�����ݱ������Եȼ������ͽ�������

	m_uiViewStyle=STYLE_SMALL_PHOTO;						//ListCtrl�鿴����ʽֵ

	m_hLoadImage=NULL;										//����ͼ����߳�ָ�룬���벢���ţ�������DC
	m_hLoadBaseInfo=NULL;									//�����ļ�������Ϣ

	m_cmRightButtonMenu.LoadMenuA(IDR_MENU_ALZQ_LIST_PHOTO);	//��ȡȫ���Ҽ��˵��Ķ���

	m_brUnselectedBrush=new Gdiplus::SolidBrush(Gdiplus::Color(227,237,255));			//δѡ���ITEM����ˢ
	m_brSelectedBrush=new Gdiplus::SolidBrush(Gdiplus::Color(93,147,174));				//��ѡ���ITEM����ˢ
	m_brSelectedUnfoucBrush=new Gdiplus::SolidBrush(Gdiplus::Color(170,180,200));		//��ѡ���ITEM�����޽��㱳��ˢ
	m_brSelectBrush=new Gdiplus::SolidBrush(Gdiplus::Color(50,15,35,120));				//����ѡ��ʱ�ĸ��ǲ�����ɫ
	m_brScrollBarBakBrush=new Gdiplus::SolidBrush(Gdiplus::Color(250,250,240));			//�������ı���ˢ
	m_brScrollBarMidBakBrush=new Gdiplus::SolidBrush(Gdiplus::Color(253,246,225));		//�����������������ı���ˢ
	m_brScrollBarMidMouseOnBrush=new Gdiplus::SolidBrush(Gdiplus::Color(255,219,108));	//�����ͣ����µ��������鱳��ˢ
	m_brScrollBarMidDragBrush=new Gdiplus::SolidBrush(Gdiplus::Color(200,172,85));		//��������µ��������鱳��ˢ
	m_brBakBrush=new Gdiplus::SolidBrush(Gdiplus::Color(255,255,255));					//�ܵı���ˢ
	m_penFoucItem=new Gdiplus::Pen(Gdiplus::Color(0,0,0),1);							//���н����ITEM���
	m_penFoucItem->SetDashStyle(DashStyleDot);											//����Ϊ����
	m_penSelectedItem=new Gdiplus::Pen(Gdiplus::Color(0,0,0),1);						//��ѡ���ITEM���
	m_penItemBorder=new Gdiplus::Pen(Gdiplus::Color(50,15,35,120),1);					//Item��Եˢ
	m_penScrollBarMidBakBorder=new Gdiplus::Pen(Gdiplus::Color(232,186,88),2);			//�����������������ı�Եˢ
	m_penScrollBarMidMouseOnBorder=new Gdiplus::Pen(Gdiplus::Color(233,159,0),2);		//�����ͣ����µ����������Եˢ
	m_penScrollBarMidDragBorder=new Gdiplus::Pen(Gdiplus::Color(176,121,2),2);			//��������µ����������Եˢ
	m_brFontBrush = new SolidBrush( Gdiplus::Color(0,0,0) );

	m_sbcsScrollBarColorSet.normalBak=RGB(253,246,225);
	m_sbcsScrollBarColorSet.normalBorder=RGB(232,186,88);
	m_sbcsScrollBarColorSet.mouseOnBak=RGB(255,219,108);
	m_sbcsScrollBarColorSet.mouseOnBorder=RGB(233,159,0);
	m_sbcsScrollBarColorSet.mouseDownBak=RGB(200,172,85);
	m_sbcsScrollBarColorSet.mouseDownBorder=RGB(176,121,2);

	m_imgDefaultDisk=Gdiplus::Image::FromFile(L"res\\disk.png");							//Ĭ�ϴ���ͼ��
	m_imgDefaultFloder=Gdiplus::Image::FromFile(L"res\\floder.png");						//Ĭ���ļ���ͼ��
	m_imgDefaultPic=Gdiplus::Image::FromFile(L"res\\91See.bmp");							//ITEMĬ��ͼ��
	m_imgShadowRight=Gdiplus::Image::FromFile(L"res\\shadow_right.png");					//Ĭ���ļ���ͼ��
	m_imgShadowDown=Gdiplus::Image::FromFile(L"res\\shadow_down.png");						//ITEMĬ��ͼ��
	m_imgShadowRightDown=Gdiplus::Image::FromFile(L"res\\shadow_right_down.png");			//Ĭ���ļ���ͼ��

	m_ffFontFamily=new FontFamily(L"����");
	m_sfStringFormatLeft=new StringFormat();
	m_sfStringFormatLeft->SetAlignment(StringAlignmentNear);
	m_sfStringFormatRight=new StringFormat();
	m_sfStringFormatRight->SetAlignment(StringAlignmentFar);
	m_sfStringFormatCenter=new StringFormat();
	m_sfStringFormatCenter->SetAlignment(StringAlignmentCenter);
	m_fntFontBlod=new Gdiplus::Font(m_ffFontFamily,10,FontStyleBold,UnitPoint);
	m_fntFontNormal=new Gdiplus::Font(m_ffFontFamily,10,FontStyleRegular,UnitPoint);		//�������ֵ���ʽ���Ӵ�

	//�����ĵȼ�ͼ���б�
	m_cilLevelsIcon=new CImageList();
	m_cilLevelsIcon->DeleteImageList();
	m_cilLevelsIcon->Create(16,16,ILC_COLOR32 | TRUE, 6, 0);
	PublicFunc::ReadImageList("res\\levels.bmp",m_cilLevelsIcon);

	//�϶���������
	m_cilScrollBarUp=new CImageList();
	m_cilScrollBarUp->DeleteImageList();
	m_cilScrollBarUp->Create(20,20,ILC_COLOR32 | TRUE, 3, 0);
	PublicFunc::ReadImageList("res\\scrollUp.bmp",m_cilScrollBarUp);

	//�϶���������
	m_cilScrollBarDown=new CImageList();
	m_cilScrollBarDown->DeleteImageList();
	m_cilScrollBarDown->Create(20,20,ILC_COLOR32 | TRUE, 3, 0);
	PublicFunc::ReadImageList("res\\scrollDown.bmp",m_cilScrollBarDown);

	//�϶���������
	m_cilScrollBarLeft=new CImageList();
	m_cilScrollBarLeft->DeleteImageList();
	m_cilScrollBarLeft->Create(20,20,ILC_COLOR32 | TRUE, 3, 0);
	PublicFunc::ReadImageList("res\\scrollLeft.bmp",m_cilScrollBarLeft);

	//�϶���������
	m_cilScrollBarRight=new CImageList();
	m_cilScrollBarRight->DeleteImageList();
	m_cilScrollBarRight->Create(20,20,ILC_COLOR32 | TRUE, 3, 0);
	PublicFunc::ReadImageList("res\\scrollRight.bmp",m_cilScrollBarRight);

	m_wndPreviewBar=NULL;
	m_wndFavoriteBar=NULL;

	m_bCreateEdit=false;


	/**
	*	----�ػ沿�ֱ���----
	*/
	m_cbBakMemeryBmp=NULL;								//��������ͼ��Ĵ洢����
	m_cbWorkAreaBmp=NULL;								//������ʾ�����ͼ��洢����
	m_cbHeaderBmp=NULL;									//��ͷ��ͼ��洢����
	m_cbScrollVBmp=NULL;								//��ͷ��ͼ��洢����
	m_cbScrollHBmp=NULL;								//��ͷ��ͼ��洢����
	m_dcMemeryDC=NULL;									//�������Ƶ��ڴ�DC
	m_dcWorkAreaDC=NULL;								//��ʾ���򲿷ֵ��ڴ�DC
	m_dcHeaderDC=NULL;									//��ͷ���ֵ��ڴ�DC
	m_dcScrollVDC=NULL;									//������������ֵ��ڴ�DC
	m_dcScrollHDC=NULL;									//������������ֵ��ڴ�DC
	m_dcBakDC=NULL;										//�������Ƶ�DC

	m_bListGetFouc=false;								//List�Ƿ��ȡ������
	m_bMouseTracking=FALSE;

	m_iWorkAreaTop=0;									//��ǰ��ʾ���ֵĶ���Y����-���m_iWorkAreaHeight
	m_iWorkAreaBottom=0;								//��ǰ��ʾ���ֵĵײ�Y����-���m_iWorkAreaHeight
	m_iOldWorkAreaTop=0;								//��ǰ��ʾ���ֵĶ�������ǰY����-���m_iWorkAreaHeight
	m_iOldWorkAreaBottom=0;								//��ǰ��ʾ���ֵĵײ�����ǰY����-���m_iWorkAreaHeight
	m_iWorkAreaLeft=0;									//��ǰ��ʾ���ֵ���߽�����-���m_iWorkAreaWidth
	m_iWorkAreaRight=0;									//��ǰ��ʾ���ֵ��ұ߽�����-���m_iWorkAreaWidth
	m_iCurrentViewWidth=0;								//��ǰ��ʾ���ֵĿ��
	m_iCurrentViewHeight=0;								//��ǰ��ʾ���ֵĸ߶�
	m_iCurrentStartNItem=0;								//��ǰ��ʾ������ʾ�ĵ�һ��ITEM���
	m_iCurrentEndNItem=0;								//��ǰ��ʾ������ʾ�����һ��ITEM���
	m_iWorkAreaWidth=0;									//item��ʾ������
	m_iWorkAreaHeight=0;								//item��ʾ����߶�
	m_iWorkAreaTotalHeight=0;							//item��ʾ�����ܸ߶�
	m_iWorkAreaTotalWidth=0;							//item��ʾ�����ܿ��
	m_iItemWidth=0;										//ÿ��ITEM�Ŀ��
	m_iItemHeight=0;									//ÿ��ITEM�ĸ߶�
	m_iItemWithBorderWidth=0;							//ÿ��ITEM�Ŀ�ȴ��հ�����
	m_iItemWithBorderHeight=0;							//ÿ��ITEM�ĸ߶ȴ��հ�����
	m_iPerLineItemCount=0;								//��ǰ��������ÿ�д��ڶ��ٸ�ITEM
	m_iPerPageLineCount=0;								//��ǰ���������ܹ���ʾ����
	m_iTotalLineCount=0;								//�ܹ���Ҫ��ʾ������
	m_iShowItemHead=0;									//��ʾ��ITEM��Χ��ʼ
	m_iShowItemEnd=0;									//��ʾ��ITEM��Χ��β
	m_iTotalColumnCount=0;								//��������ͳ��

	m_uiScrollBarType=SCROLL_BAR_NONE;					//�϶�������ʽ�������
	InitColumnInfo();

	m_mpiMousePositionInfo.positionType=POSITION_OUT;
	m_maiMouseActionInfo.mouseCondition=MOUSE_NONE;
	m_maiMouseActionInfo.mousePositionInfo.positionType=POSITION_OUT;
	m_maiMouseActionInfo.mousePositionInfo.value=0;
}

SeeFileViewTable::~SeeFileViewTable(void)
{
	_DeleteBmp(m_cbBakMemeryBmp);							//��������ͼ��Ĵ洢����
	_DeleteBmp(m_cbWorkAreaBmp);							//������ʾ�����ͼ��洢����
	_DeleteBmp(m_cbHeaderBmp);								//��ͷ��ͼ��洢����
	_DeleteBmp(m_cbScrollVBmp);								//�����������ͼ��洢����
	_DeleteBmp(m_cbScrollHBmp);								//�����������ͼ��洢����
	_DeleteDC(m_dcMemeryDC);								//�������Ƶ��ڴ�DC
	_DeleteDC(m_dcWorkAreaDC);								//��ʾ���򲿷ֵ��ڴ�DC
	_DeleteDC(m_dcHeaderDC);								//��ͷ���ֵ��ڴ�DC
	_DeleteDC(m_dcScrollVDC);								//������������ֵ��ڴ�DC
	_DeleteDC(m_dcScrollHDC);								//������������ֵ��ڴ�DC

	m_cilLevelsIcon->DeleteImageList();		//�����ĵȼ�ͼ���б�
	m_cilScrollBarUp->DeleteImageList();	//�϶���������
	m_cilScrollBarDown->DeleteImageList();	//�϶���������
	m_cilScrollBarLeft->DeleteImageList();	//�϶���������
	m_cilScrollBarRight->DeleteImageList();	//�϶���������
	delete m_cilLevelsIcon;					//�����ĵȼ�ͼ���б�
	delete m_cilScrollBarUp;				//�϶���������
	delete m_cilScrollBarDown;				//�϶���������
	delete m_cilScrollBarLeft;				//�϶���������
	delete m_cilScrollBarRight;				//�϶���������
	PublicFunc::DeleteThread(m_hLoadImage);
	PublicFunc::DeleteThread(m_hLoadBaseInfo);
}
BEGIN_MESSAGE_MAP(SeeFileViewTable, CWnd)
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &SeeFileViewTable::OnLvnColumnclick)
	ON_WM_DROPFILES()
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, &SeeFileViewTable::OnLvnBegindrag)

	ON_MESSAGE(MES_ALZQ_BEGIN_DRAG_LV,&SeeFileViewTable::OnBeginDragLvOrType)
	ON_MESSAGE(MES_ALZQ_BEGIN_DRAG_TYPE,&SeeFileViewTable::OnBeginDragLvOrType)
	ON_MESSAGE(MES_ALZQ_END_DRAG_LV,&SeeFileViewTable::OnEndDragLvOrType)
	ON_MESSAGE(MES_ALZQ_END_DRAG_TYPE,&SeeFileViewTable::OnEndDragLvOrType)
	ON_MESSAGE(WM_MOUSELEAVE,&SeeFileViewTable::OnMouseLeave)
	ON_COMMAND(ID_ALZQ_LIST_VIEW, &SeeFileViewTable::OnAlzqListView)
	ON_COMMAND(ID_ALZQ_LIST_CUT, &SeeFileViewTable::OnAlzqListCut)
	ON_COMMAND(ID_ALZQ_LIST_COPY, &SeeFileViewTable::OnAlzqListCopy)
	ON_COMMAND(ID_ALZQ_LIST_CUT_FLODER, &SeeFileViewTable::OnAlzqListCutFloder)
	ON_COMMAND(ID_ALZQ_LIST_COPY_FLODER, &SeeFileViewTable::OnAlzqListCopyFloder)
	ON_COMMAND(ID_ALZQ_LIST_RENAME, &SeeFileViewTable::OnAlzqListRename)

	ON_COMMAND(ID_ALZQ_LIST_OTHER_CUT, &SeeFileViewTable::OnAlzqListCut)
	ON_COMMAND(ID_ALZQ_LIST_OTHER_COPY, &SeeFileViewTable::OnAlzqListCopy)
	ON_COMMAND(ID_ALZQ_LIST_OTHER_CUT_FLODER, &SeeFileViewTable::OnAlzqListCutFloder)
	ON_COMMAND(ID_ALZQ_LIST_OTHER_COPY_FLODER, &SeeFileViewTable::OnAlzqListCopyFloder)
	ON_COMMAND(ID_ALZQ_LIST_OTHER_RENAME, &SeeFileViewTable::OnAlzqListRename)
	ON_COMMAND(ID_ALZQ_LIST_ADDCOLECTION, &SeeFileViewTable::OnAlzqListAddcolection)

	ON_MESSAGE(MES_ALZQ_REFRESH_ALL,&SeeFileViewTable::OnRefreshAll)
	ON_MESSAGE(MES_ALZQ_REFRESH_ITEM,&SeeFileViewTable::OnRefreshItem)

	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_NCLBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_NCHITTEST()
	ON_WM_ACTIVATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()
	

//=====================================================================
// �� �� ����ResizeWorkAreaWithoutGroup
// ����������������ͼģʽ�£�����������ʾ�����С
// ���������int width,int height,bool setToSelected:�Ƿ�������ʾ����ѡ��ITEM��
// �����������
// �������ڣ�2008.10.11
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::_ResizeWorkAreaWithoutGroup(int width,int height,bool setToSelected)
{
	if(m_uiViewStyle == STYLE_SMALL_PHOTO)
	{
		//����ͼģʽ
		_ResizeWorkAreaWithoutGroupSmallPhoto(width,height,setToSelected);
	}
	else if(m_uiViewStyle == STYLE_REPORT)
	{
		//��ϸ��Ϣģʽ
		_ResizeWorkAreaWithoutGroupReport(width,height,setToSelected);
	}

	_BuildDC();

	if(m_uiScrollBarType)
	{
		//����������ʽ��Ϊ0ʱ��ʾ���ں����������һ������
		//�����϶������������
		ReSetScrollBarInfo();
	}
}
		

//=====================================================================
// �� �� ����_ResizeWorkAreaWithoutGroupSmallPhoto
// ����������SMALLPHOTO��ʽ�µ�����������ʾ�����С
// ���������
// ���������
// �������ڣ�2008.10.13
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_ResizeWorkAreaWithoutGroupSmallPhoto(int width,int height,bool setToSelected)
{
	//�������򲿷ֵļ���
	m_iWorkAreaWidth=width;					//ȷ��item��ʾ������
	m_iCurrentViewWidth=width;				//��ʾ������
	m_iCurrentViewHeight=height;			//��ʾ����߶�
	m_iWorkAreaHeight=height;				//item��ʾ����߶�
	m_iPerLineItemCount=((m_iWorkAreaWidth-1)/m_iItemWithBorderWidth);				//ÿ����ʾ��ITEM����
	if(m_iPerLineItemCount<=0){m_iPerLineItemCount=1;}

	//����ʾ��ʽΪ����ͼʱ���������¼���
	m_iTotalLineCount=((m_ficFileControl.m_iTotalCount-1)/m_iPerLineItemCount)+1;		//����һ����Ҫ��ʾ����
	if(m_ficFileControl.m_iTotalCount<=0){m_iTotalLineCount=0;}
	m_iWorkAreaTotalHeight=m_iTotalLineCount * m_iItemWithBorderHeight;					//������Ҫ��ʾ���ܸ߶ȣ�����ʾ������бȽϣ���ȷ���Ƿ���Ҫ��ʾ�϶���

	if(m_iWorkAreaTotalHeight>height)
	{
		//����Ҫ����ʾ�߶ȴ�����ʾ����߶�ʱ����Ҫ��������϶���
		m_uiScrollBarType=SCROLL_BAR_V;

		//�����������϶���ʱ����ʾ�����ȼ���,��Ҫ����ʾ�������Ƚ������¼���
		m_iWorkAreaWidth=m_iWorkAreaWidth-SCROLL_BAR_WIDTH_HEIGHT;
		
		//��ʼ���¼���ÿ�е�ITEM����
		m_iPerLineItemCount=((m_iWorkAreaWidth-1)/m_iItemWithBorderWidth);			//ÿ����ʾ��ITEM����
		if(m_iPerLineItemCount<=0){m_iPerLineItemCount=1;}
		m_iTotalLineCount=((m_ficFileControl.m_iTotalCount-1)/m_iPerLineItemCount)+1;	//����һ����Ҫ��ʾ����
		if(m_ficFileControl.m_iTotalCount<=0){m_iTotalLineCount=0;}
		m_iWorkAreaTotalHeight=m_iTotalLineCount * m_iItemWithBorderHeight;				//������Ҫ��ʾ���ܸ߶�
	}
	else
	{
		m_uiScrollBarType=SCROLL_BAR_NONE;
	}

	m_iPerPageLineCount=((m_iWorkAreaHeight-1)/m_iItemWithBorderHeight)+1;				//ÿҳ�ܹ���ʾ������
	m_iWorkAreaLeft=0;
	m_iWorkAreaRight=m_iWorkAreaWidth;
	m_iWorkAreaTotalWidth=m_iWorkAreaWidth;

	//���е�ǰ����Χ����
	if(setToSelected)
	{
		//����ʾ�������õ���һ����ѡ����
		int nItem=m_ficFileControl.GetFirstSelectedCode();		//��ȡ��һ����ѡ������
		SetWorkAreaToItemWithoutGroup(nItem);
	}
	else
	{
		if(m_iWorkAreaBottom>m_iWorkAreaTotalHeight)
		{
			m_iWorkAreaBottom=m_iWorkAreaTotalHeight>m_iWorkAreaHeight?m_iWorkAreaTotalHeight:m_iWorkAreaHeight;
			m_iWorkAreaTop=m_iWorkAreaBottom-m_iWorkAreaHeight;
		}
		if(m_iWorkAreaTop<0)
		{
			m_iWorkAreaTop=0;
			m_iWorkAreaBottom=m_iWorkAreaTop+m_iWorkAreaHeight;
		}
		//������ʾ��Χ
		ItemRange rang=SetShowItemRange(m_iWorkAreaTop,m_iWorkAreaBottom);
		m_iShowItemHead=rang.head;
		m_iShowItemEnd=rang.end;
	}
}
		

//=====================================================================
// �� �� ����_ResizeWorkAreaWithoutGroupReport
// ����������REPORT��ʽ�µ�����������ʾ�����С
// ���������
// ���������
// �������ڣ�2008.10.13
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_ResizeWorkAreaWithoutGroupReport(int width,int height,bool setToSelected)
{
	//�������򲿷ֵļ���
	m_iWorkAreaWidth=width;										//ȷ��item��ʾ������
	m_iCurrentViewWidth=width;									//��ʾ������
	m_iCurrentViewHeight=height;								//��ʾ����߶�
	m_iWorkAreaHeight=height-REPORT_HEAD_HEIGHT;				//item��ʾ����߶�
	m_iPerLineItemCount=1;										//ÿ����ʾ��ITEM����

	//����ʾ��ʽΪ����ͼʱ���������¼���
	m_iTotalLineCount=m_ficFileControl.m_iTotalCount;			//һ����Ҫ��ʾ���������������
	m_iWorkAreaTotalHeight=m_iTotalLineCount * m_iItemWithBorderHeight;			//������Ҫ��ʾ���ܸ߶ȣ�����ʾ������бȽϣ���ȷ���Ƿ���Ҫ��ʾ�϶���

	//�����ݿ��ж�ȡ����Ϣ����ʱ���ù̶��ĳ�ʼ������
	InitColumnInfo();

	if(m_iWorkAreaTotalWidth > m_iWorkAreaWidth)
	{
		//����Ҫ��ʾ�Ŀ�ȴ�����ʾ����Ŀ��ʱ����Ҫ��ʾ������������ʹ��|=��������������
		m_uiScrollBarType=SCROLL_BAR_H;

		m_iWorkAreaHeight=m_iWorkAreaHeight-SCROLL_BAR_WIDTH_HEIGHT;
	}
	else
	{
		m_uiScrollBarType=SCROLL_BAR_NONE;
	}

	if(m_iWorkAreaHeight<0){m_iWorkAreaHeight=0;}

	if(m_iWorkAreaTotalHeight>m_iWorkAreaHeight)
	{
		//����Ҫ����ʾ�߶ȴ�����ʾ����߶�ʱ����Ҫ��������϶���
		m_uiScrollBarType|=SCROLL_BAR_V;

		//�����������϶���ʱ����ʾ�����ȼ���,��Ҫ����ʾ�������Ƚ������¼���
		m_iWorkAreaWidth=m_iWorkAreaWidth-SCROLL_BAR_WIDTH_HEIGHT;
	}

	m_iPerPageLineCount=((m_iWorkAreaHeight-1)/m_iItemWithBorderHeight)+1;				//ÿҳ�ܹ���ʾ������

	//���к�������ļ���
	if(m_iWorkAreaLeft<0){m_iWorkAreaLeft=0;}
	m_iWorkAreaRight=m_iWorkAreaLeft+m_iWorkAreaWidth;
	if(m_iWorkAreaTotalWidth>m_iWorkAreaWidth && m_iWorkAreaRight>m_iWorkAreaTotalWidth)
	{
		m_iWorkAreaRight=m_iWorkAreaTotalWidth;
		m_iWorkAreaLeft=m_iWorkAreaRight-m_iWorkAreaWidth;
	}

	//���е�ǰ����Χ����
	if(setToSelected)
	{
		//����ʾ�������õ���һ����ѡ����
		int nItem=m_ficFileControl.GetFirstSelectedCode();		//��ȡ��һ����ѡ������
		SetWorkAreaToItemWithoutGroup(nItem);
	}
	else
	{
		if(m_iWorkAreaBottom>m_iWorkAreaTotalHeight)
		{
			m_iWorkAreaBottom=m_iWorkAreaTotalHeight>m_iWorkAreaHeight?m_iWorkAreaTotalHeight:m_iWorkAreaHeight;
			m_iWorkAreaTop=m_iWorkAreaBottom-m_iWorkAreaHeight;
		}
		if(m_iWorkAreaTop<0)
		{
			m_iWorkAreaTop=0;
			m_iWorkAreaBottom=m_iWorkAreaTop+m_iWorkAreaHeight;
		}
		//������ʾ��Χ
		ItemRange rang=SetShowItemRange(m_iWorkAreaTop,m_iWorkAreaBottom);
		m_iShowItemHead=rang.head;
		m_iShowItemEnd=rang.end;
	}
}
	

//=====================================================================
// �� �� ����_CheckWorkArea
// ������������֤��ʾ�����Ƿ񳬳���Χ
// ���������
// ���������
// �������ڣ�2008.10.18
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_CheckWorkArea()
{
	if(m_iWorkAreaBottom>m_iWorkAreaTotalHeight)
	{
		m_iWorkAreaBottom=m_iWorkAreaTotalHeight>m_iWorkAreaHeight?m_iWorkAreaTotalHeight:m_iWorkAreaHeight;
		m_iWorkAreaTop=m_iWorkAreaBottom-m_iWorkAreaHeight;
	}
	if(m_iWorkAreaTop<0)
	{
		m_iWorkAreaTop=0;
		m_iWorkAreaBottom=m_iWorkAreaTop+m_iWorkAreaHeight;
	}

	//���к�������ļ���
	if(m_iWorkAreaLeft<0){m_iWorkAreaLeft=0;}
	m_iWorkAreaRight=m_iWorkAreaLeft+m_iWorkAreaWidth;
	if(m_iWorkAreaTotalWidth>m_iWorkAreaWidth && m_iWorkAreaRight>m_iWorkAreaTotalWidth)
	{
		m_iWorkAreaRight=m_iWorkAreaTotalWidth;
		m_iWorkAreaLeft=m_iWorkAreaRight-m_iWorkAreaWidth;
	}
	else if(m_iWorkAreaWidth>=m_iWorkAreaTotalWidth && m_iWorkAreaRight>m_iWorkAreaWidth)
	{
		m_iWorkAreaRight=m_iWorkAreaWidth;
		m_iWorkAreaLeft=0;
	}

	//������ʾ��Χ
	ItemRange rang=SetShowItemRange(m_iWorkAreaTop,m_iWorkAreaBottom);
	m_iShowItemHead=rang.head;
	m_iShowItemEnd=rang.end;
}
	

//=====================================================================
// �� �� ����ResizeWorkAreaWithoutGroup
// ����������������ͼģʽ�£�����������ʾ�����С
// ���������bool setToSelected:�Ƿ�������ʾ����ѡ��ITEM��
// �����������
// �������ڣ�2008.10.11
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::_ResizeWorkAreaWithoutGroup(bool setToSelected)
{
	_ResizeWorkAreaWithoutGroup(m_iCurrentViewWidth,m_iCurrentViewHeight,setToSelected);
}
	

//=====================================================================
// �� �� ����_ReDrawItems
// �������������»��Ʒ�Χ�ڵ�Item
// ���������int head,int end
// �����������
// �������ڣ�2008.10.11
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_ReDrawItems(int head,int end)
{
	_ReDrawItems(head,end,0,m_iWorkAreaWidth);
}
	

//=====================================================================
// �� �� ����_ReDrawItems
// �������������»��Ʒ�Χ�ڵ�Item
// ���������int head,int end,int leftLine,int rightLine
// �����������
// �������ڣ�2008.10.11
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_ReDrawItems(int head,int end,int leftLine,int rightLine)
{
	for(int i=head;i<=end;i++)
	{
		_PrintItem(i,leftLine,rightLine);
	}
}
	

//=====================================================================
// �� �� ����_ReDrawRect
// �������������»��������ڵ���
// ���������CRect rect:����������ķ�Χ
// �����������
// �������ڣ�2008.10.15
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_ReDrawRect(CRect rect)
{
	if(m_uiViewStyle & STYLE_SMALL_PHOTO | STYLE_REPORT)
	{
		//��Ϊ����ͼ��ʽʱ
		int top=rect.top+m_iWorkAreaTop;
		int bottom=rect.bottom+m_iWorkAreaTop;

		//���������߶ȷ�Χ�µ�ITEM��Χ
		ItemRange itemRange=SetShowItemRange(top,bottom);
		_ReDrawItems(itemRange.head,itemRange.end,rect.left,rect.right);

		if(m_uiViewStyle==STYLE_SMALL_PHOTO)
		{
			//������ͼ��ʽ���������հ�����
			if((itemRange.end+1) % m_iPerLineItemCount!=0)
			{
				//�����һ����ʾ��Item�޷�����ʾ��������
				CPoint pt=GetItemPosition(itemRange.end);
				pt.x+=m_iItemWithBorderWidth;
				
				if(!(pt.x>rect.right || pt.x+m_iItemWithBorderWidth<rect.left))
				{
					//����Ҫ������������Ҫ�ػ��������ʱ
					pt.y=pt.y-m_iWorkAreaTop;
					Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());
					graph.FillRectangle(m_brBakBrush,pt.x,pt.y,rect.right-pt.x,rect.bottom-pt.y);
				}
			}
		}
	}
}
	

//=====================================================================
// �� �� ����_PrintItem
// �������������Ʊ��ΪnItem��ITEM
// ���������int nItem:���,int leftLine,int rightLine
// ���������void
// �������ڣ�08.10.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵���������ڴ�ŵı���DC��
//=====================================================================
void SeeFileViewTable::_PrintItem(int nItem,int leftLine,int rightLine)
{
	if(nItem<m_iShowItemHead || nItem>m_iShowItemEnd)
	{
		//����ʾITEM������ʾ����������ʾ
		return ;
	}

	FileInfoList * file=m_ficFileControl.GetFile(nItem);

	//������ʾ������
	CPoint pt=GetItemPosition(nItem);
	pt.x=pt.x-m_iWorkAreaLeft;
	pt.y=pt.y-m_iWorkAreaTop;

	if(m_uiViewStyle == STYLE_SMALL_PHOTO)
	{
		if(!(pt.x>rightLine || pt.x+m_iItemWithBorderWidth<leftLine))
		{
			_PrintItemSmallPhoto(pt,file);
		}
	}
	else if(m_uiViewStyle == STYLE_REPORT)
	{
		_PrintItemReport(pt,file,leftLine,rightLine);
	}
}
	

//=====================================================================
// �� �� ����_PrintItemSmallPhoto
// ����������Itemͼ�������ƺ���
// ���������CPoint pt:��ʾITEM������
//			 FileInfoList * fileInfo:ITEMָ����ļ�
// ���������void
// �������ڣ�08.10.11
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_PrintItemSmallPhoto(CPoint pt,FileInfoList * fileInfo)
{
	USES_CONVERSION;
	Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());

	//���Ʊ�Ե�ı���ɫ
	graph.FillRectangle(
		m_brBakBrush
		,pt.x
		,pt.y
		,m_iItemWithBorderWidth,SMALL_PHOTO_ITEM_BORDER
		);
	graph.FillRectangle(
		m_brBakBrush
		,pt.x
		,pt.y+SMALL_PHOTO_ITEM_BORDER
		,SMALL_PHOTO_ITEM_BORDER
		,m_iItemWithBorderHeight-SMALL_PHOTO_ITEM_BORDER
		);
	graph.FillRectangle(
		m_brBakBrush
		,pt.x+m_iItemWithBorderWidth-SMALL_PHOTO_ITEM_BORDER
		,pt.y+SMALL_PHOTO_ITEM_BORDER
		,SMALL_PHOTO_ITEM_BORDER
		,m_iItemWithBorderHeight-SMALL_PHOTO_ITEM_BORDER
		);
	graph.FillRectangle(
		m_brBakBrush
		,pt.x+SMALL_PHOTO_ITEM_BORDER
		,pt.y+m_iItemWithBorderHeight-SMALL_PHOTO_ITEM_BORDER
		,m_iItemWithBorderWidth-(2*SMALL_PHOTO_ITEM_BORDER)
		,SMALL_PHOTO_ITEM_BORDER
		);

	CPoint printPt(pt.x+SMALL_PHOTO_ITEM_BORDER,pt.y+SMALL_PHOTO_ITEM_BORDER);

	Gdiplus::SolidBrush * brush;
	if(fileInfo->GetState(LVIS_SELECTED))
	{
		if(m_bListGetFouc)
		{
			brush=m_brSelectedBrush;
		}
		else
		{
			brush=m_brSelectedUnfoucBrush;
		}
	}
	else
	{
		//δѡ��
		brush=m_brUnselectedBrush;
	}
	//���Ʊ���
	graph.FillRectangle(brush,printPt.x,printPt.y,m_iItemWidth,m_iItemHeight);

	//����ͼ�󲿷�
	_PrintSmallPhoto(&graph,printPt,fileInfo);

	//�����Զ�����Ϣ����

	//��������
	CString name=fileInfo->GetFileName().c_str();
	WCHAR * wchar=A2W(name);
	RectF txtRectF(
		printPt.x
		,printPt.y+m_iItemHeight-PHOTO_SMALL_WORD_HEIGHT+5
		,m_iItemWidth
		,PHOTO_SMALL_WORD_HEIGHT-5);

	graph.DrawString(
		wchar
		,wcslen(wchar)
		,m_fntFontBlod
		,txtRectF
		,m_sfStringFormatCenter
		,m_brFontBrush);

	//����ITEM�߿�
	graph.DrawRectangle(m_penItemBorder,printPt.x,printPt.y,m_iItemWidth-1,m_iItemHeight-1);
}
	

//=====================================================================
// �� �� ����_PrintItemReport
// ����������Itemͼ�������ƺ���
// ���������CPoint pt:��ʾITEM������
//			 FileInfoList * fileInfo:ITEMָ����ļ�
//			 int leftLine,int rightLine:���Ƶ����ұ߽�
// ���������void
// �������ڣ�08.10.14
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵��������CDC����ػ��Ʋ����ṹ�壬�Ƿ񴰿�Ϊ����
//=====================================================================
void SeeFileViewTable::_PrintItemReport(CPoint pt,FileInfoList * fileInfo,int leftLine,int rightLine)
{
	USES_CONVERSION; 
	Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());

	//��ȡ���б���ɫˢ
	CPoint printPt(pt.x,pt.y);

	Gdiplus::SolidBrush * brush;
	if(fileInfo->GetState(LVIS_SELECTED))
	{
		if(m_bListGetFouc)
		{
			brush=m_brSelectedBrush;
		}
		else
		{
			brush=m_brSelectedUnfoucBrush;
		}
	}
	else
	{
		//δѡ��
		brush=m_brUnselectedBrush;
	}

	//���л���
	VectorColumnInfo::iterator iter=m_vciColumnsInfo.begin();
	for(int i=0;i<m_iTotalColumnCount;i++)
	{
		int left=iter->startPosition-m_iWorkAreaLeft;
		int right=iter->endPosition-m_iWorkAreaLeft;
		if(!(left>rightLine || right<leftLine))
		{
			//���Ʊ���ɫ
			printPt.x=left;
			graph.FillRectangle(brush,printPt.x,printPt.y,iter->width,REPORT_ITEM_HEIGHT);
	
			//��������������ʾ������ʱ
			if(i==0)
			{
				//��Ϊ����ʱ��Ҫ����ͼ�����
				//�������л��Ƶ���ʱ��ͼ����,��Ϊ������Ҫ���Ƶ������ͼ��С�����Ծ���һ����ʱDC�Ĳü�����ʹ��ͼ���ڷ�ΧСʱ������ȫ����
				CDC dc;
				dc.CreateCompatibleDC(NULL);
				CBitmap bmp;
				bmp.CreateCompatibleBitmap(m_dcWorkAreaDC,20,REPORT_ITEM_HEIGHT);
				dc.SelectObject(bmp);
				dc.FillSolidRect(0,0,iter->width,REPORT_ITEM_HEIGHT,RGB(255,255,255));
				//ʹ��ϵͳĬ��ͼ������ļ�����ͼ��
				SHFILEINFO shfi;
				HIMAGELIST hi=(HIMAGELIST)SHGetFileInfo(NULL,0,&shfi,sizeof(shfi),SHGFI_SYSICONINDEX|SHGFI_SMALLICON);		//ͼ���С16*16
				CImageList * iconList=CImageList::FromHandle(hi);

				POINT p;
				p.x=0;
				p.y=2;
				iconList->Draw(&dc,fileInfo->m_iNIcon,p,ILD_TRANSPARENT);

				m_dcWorkAreaDC->BitBlt(printPt.x,printPt.y,iter->width>20?20:iter->width,REPORT_ITEM_HEIGHT,&dc,0,0,SRCCOPY);

				dc.DeleteDC();
				bmp.DeleteObject();

				if(iter->width>20)
				{
					//�����п�ȴ���ͼ����ʾ��ռ���ʱ��Ҫ��ʾ����
					//��������
					CString str=fileInfo->GetFileBaseInfo(iter->infoType.code).c_str();
					WCHAR * wchar=A2W(str);
					RectF txtRectF(
						printPt.x+20
						,printPt.y+5
						,iter->width-20
						,REPORT_ITEM_HEIGHT-5);

					graph.DrawString(
						wchar
						,wcslen(wchar)
						,m_fntFontNormal
						,txtRectF
						,m_sfStringFormatCenter
						,m_brFontBrush);
				}
			}
			else
			{
				//�����У�ֻ�������
				//��������
				CString str=fileInfo->GetFileBaseInfo(iter->infoType.code).c_str();
				WCHAR * wchar=A2W(str);
				RectF txtRectF(
					printPt.x
					,printPt.y+5
					,iter->width
					,REPORT_ITEM_HEIGHT-5);

				graph.DrawString(
					wchar
					,wcslen(wchar)
					,m_fntFontNormal
					,txtRectF
					,m_sfStringFormatCenter
					,m_brFontBrush);
			}
		}

		iter++;
	}

	if(m_iWorkAreaTotalWidth<rightLine)
	{
		//�������������ұ߽�����ʾ�����ڣ���δ��ʾ�������Ϊ����ɫ
		graph.FillRectangle(m_brBakBrush,m_iWorkAreaTotalWidth-m_iWorkAreaLeft,printPt.y,m_iWorkAreaWidth-m_iWorkAreaTotalWidth,REPORT_ITEM_HEIGHT);			//����ʾ���ΪITEM�������
	}
	
	if (fileInfo->GetState(LVIS_FOCUSED)) 
	{
		//����ļ�Ϊ����״̬������ѡ��״̬�߿�
		graph.DrawRectangle(
			m_penFoucItem
			,0
			,printPt.y
			,m_iWorkAreaWidth-1
			,REPORT_ITEM_HEIGHT-1
			);
	}

	//����ITEM�߿�
	//graph.DrawRectangle(m_penItemBorder,0,printPt.y,m_iWorkAreaTotalWidth-1,m_iItemHeight-1);
}
	

//=====================================================================
// �� �� ����_PrintSmallPhoto
// ��������������ͼ���ֵĻ��ƺ�����ֻ����ͼ����������־��ͼ���
// ���������Gdiplus::Graphics * graph,CPoint pt:��ʾITEM������
//			 FileInfoList * fileInfo:ITEMָ����ļ�
// ���������void
// �������ڣ�08.08.29
// �޸����ڣ�08.08.29
// �� �ߣ�alzq
// ����˵��������CDC����ػ��Ʋ����ṹ�壬�Ƿ�ѡ���Ƿ񴰿�Ϊ����
//=====================================================================
void SeeFileViewTable::_PrintSmallPhoto(Gdiplus::Graphics * graph,CPoint pt,FileInfoList * fileInfo)
{
	int pWidth=0;
	int pHeight=0;
	//��ʱ�洢��Imageָ��
	Gdiplus::Image * tmpImg;
	bool defaultIcon=false;
	if(fileInfo->m_bSmallPhotoEnable)
	{
		tmpImg=fileInfo->GetSmallPhotoImage();
		pWidth=fileInfo->m_iRealPhotoWidth;
		pHeight=fileInfo->m_iRealPhotoHeight;
	}
	else
	{
		if(fileInfo->CheckFileType(FILE_FLODER))
		{
			tmpImg=m_imgDefaultFloder;
			pWidth=tmpImg->GetWidth();
			pHeight=tmpImg->GetHeight();
		}
		else if(fileInfo->CheckFileType(FILE_DISK))
		{
			tmpImg=m_imgDefaultDisk;
			pWidth=tmpImg->GetWidth();
			pHeight=tmpImg->GetHeight();
		}
		else
		{
			//ʹ��ϵͳĬ��ͼ����ʾ
			SHFILEINFO shfi;
			HIMAGELIST hi=(HIMAGELIST)SHGetFileInfo(NULL,0,&shfi,sizeof(shfi),SHGFI_SYSICONINDEX|SHGFI_LARGEICON);
			m_cilIconList=CImageList::FromHandle(hi);
			defaultIcon=true;
			if(fileInfo->m_iNIcon==-1)
			{
				fileInfo->GetFileBaseInfo();
			}
			pWidth=32;
			pHeight=32;
		}
	}

	//��ʼ��������
	double scaleW=pWidth/(double)(m_ficFileControl.m_iSmallPhotoMaxWidth);
	double scaleH=pHeight/(double)(m_ficFileControl.m_iSmallPhotoMaxHeight);
	double scale=scaleW>scaleH?scaleW:scaleH;
	if(scale>1)
	{
		pWidth=(LONG)(pWidth/scale);
		pHeight=(LONG)(pHeight/scale);
	}

	//����ͼƬ����
	int photoX=pt.x
		+PHOTO_BORDER_WIDTH
		+((m_ficFileControl.m_iSmallPhotoMaxWidth-pWidth-PHOTO_SHADOW_WIDTH)/2);
	int photoY=pt.y
		+PHOTO_BORDER_WIDTH
		+PHOTO_SMALL_TARGET_HEIGHT
		+((m_ficFileControl.m_iSmallPhotoMaxHeight-pHeight-PHOTO_SHADOW_WIDTH)/2);

	//����ͼ��
	if(defaultIcon)
	{
		POINT p;
		p.x=photoX;
		p.y=photoY;
		m_cilIconList->Draw(m_dcWorkAreaDC,fileInfo->m_iNIcon,p,ILD_TRANSPARENT);
	}
	else
	{
		graph->DrawImage(tmpImg,photoX,photoY,pWidth,pHeight);
		
		if(!fileInfo->CheckFileType(FILE_FLODER) && !fileInfo->CheckFileType(FILE_DISK))
		{
			//������Ӱ
			graph->DrawImage(m_imgShadowRight,photoX+pWidth,photoY+PHOTO_SHADOW_MOVE,PHOTO_SHADOW_WIDTH,pHeight-PHOTO_SHADOW_MOVE);		//�����Ҳ���Ӱ
			graph->DrawImage(m_imgShadowDown,photoX+PHOTO_SHADOW_MOVE,photoY+pHeight,pWidth-PHOTO_SHADOW_MOVE,PHOTO_SHADOW_WIDTH);		//������Ӱ�²�
			graph->DrawImage(m_imgShadowRightDown,photoX+pWidth,photoY+pHeight,PHOTO_SHADOW_WIDTH,PHOTO_SHADOW_WIDTH);	//������Ӱ���䲿��
		}
	}

	//�����ļ���ʱ�����ļ�����ͼ��
	if(!fileInfo->CheckFileType(FILE_FLODER))
	{
		//ʹ��ϵͳĬ��ͼ������ļ�����ͼ��
		SHFILEINFO shfi;
		HIMAGELIST hi=(HIMAGELIST)SHGetFileInfo(NULL,0,&shfi,sizeof(shfi),SHGFI_SYSICONINDEX|SHGFI_SMALLICON);		//ͼ���С16*16
		CImageList * iconList=CImageList::FromHandle(hi);
		defaultIcon=true;

		POINT p;
		p.x=pt.x
			+m_iItemWidth
			-18;
		p.y=pt.y
			+2;
		iconList->Draw(m_dcWorkAreaDC,fileInfo->m_iNIcon,p,ILD_TRANSPARENT);

		//�����ļ���������������־
		p.x=pt.x
			+m_iItemWidth*3/5;
		m_cilLevelsIcon->Draw(m_dcWorkAreaDC,fileInfo->m_iPhotoLevel,p,ILD_TRANSPARENT);
	}
	
	if(fileInfo->GetState(LVIS_FOCUSED))
	{
		//����ļ�Ϊ��ѡ��״̬������ѡ��״̬�߿�
		graph->DrawRectangle(
			m_penFoucItem
			,pt.x
			,pt.y
			,m_iItemWidth-1
			,(2*PHOTO_BORDER_WIDTH)
				+PHOTO_SMALL_TARGET_HEIGHT
				+m_ficFileControl.m_iSmallPhotoMaxHeight
				+PHOTO_SHADOW_WIDTH
			);
	}
	else if (fileInfo->GetState(LVIS_SELECTED)) 
	{
		//����ļ�Ϊ��ѡ��״̬������ѡ��״̬�߿�
		graph->DrawRectangle(
			m_penSelectedItem
			,pt.x
			,pt.y
			,m_iItemWidth-1
			,(2*PHOTO_BORDER_WIDTH)
				+PHOTO_SMALL_TARGET_HEIGHT
				+m_ficFileControl.m_iSmallPhotoMaxHeight
				+PHOTO_SHADOW_WIDTH
			);
	}
}
	

//=====================================================================
// �� �� ����_DeleteDC
// ����������ɾ��CDC����
// ���������CDC * dc
// ���������void
// �������ڣ�08.08.29
// �޸����ڣ�08.08.29
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_DeleteDC(CDC * dc)
{
	if(dc)
	{
		dc->DeleteDC();
		delete dc;
	}
}
	

//=====================================================================
// �� �� ����_DeleteBmp
// ����������ɾ��CBitmap����
// ���������CBitmap * bmp
// ���������void
// �������ڣ�08.08.29
// �޸����ڣ�08.08.29
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_DeleteBmp(CBitmap * bmp)
{
	if(bmp)
	{
		bmp->DeleteObject();
		delete bmp;
	}
}
	

//=====================================================================
// �� �� ����_CreateDC
// ��������������DC����
// ���������CDC * dc,CBitmap * bmp,CDC * pDC,int width,int height
// ���������void
// �������ڣ�08.10.17
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_CreateDC(CDC * dc,CBitmap * bmp,CDC * pDC,int width,int height)
{
	dc=new CDC();
	dc->CreateCompatibleDC(NULL);
	bmp=new CBitmap();
	bmp->CreateCompatibleBitmap(pDC,width,height);
	dc->SelectObject(bmp);
}
	

//=====================================================================
// �� �� ����_BuildDC
// ����������������ʾ��DC
// ���������
// ���������
// �������ڣ�2008.10.17
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_BuildDC()
{
	_DeleteBmp(m_cbBakMemeryBmp);							//��������ͼ��Ĵ洢����
	_DeleteBmp(m_cbWorkAreaBmp);							//������ʾ�����ͼ��洢����
	_DeleteBmp(m_cbHeaderBmp);								//��ͷ��ͼ��洢����
	_DeleteBmp(m_cbScrollVBmp);								//�����������ͼ��洢����
	_DeleteBmp(m_cbScrollHBmp);								//�����������ͼ��洢����
	_DeleteDC(m_dcMemeryDC);								//�������Ƶ��ڴ�DC
	_DeleteDC(m_dcWorkAreaDC);								//��ʾ���򲿷ֵ��ڴ�DC
	_DeleteDC(m_dcHeaderDC);								//��ͷ���ֵ��ڴ�DC
	_DeleteDC(m_dcScrollVDC);								//������������ֵ��ڴ�DC
	_DeleteDC(m_dcScrollHDC);								//������������ֵ��ڴ�DC

	//�������ļ�����ONSIZE�����
	m_dcBakDC=GetDC();

	//�����ܵ���ʾ�ڴ�DC
	m_dcMemeryDC=new CDC();
	m_dcMemeryDC->CreateCompatibleDC(NULL);
	m_cbBakMemeryBmp=new CBitmap();
	m_cbBakMemeryBmp->CreateCompatibleBitmap(m_dcBakDC,m_iCurrentViewWidth,m_iCurrentViewHeight);
	m_dcMemeryDC->SelectObject(m_cbBakMemeryBmp);
	//_CreateDC(m_dcMemeryDC,m_cbBakMemeryBmp,m_dcBakDC,m_iCurrentViewWidth,m_iCurrentViewHeight);

	//������ʾ������ڴ�DC
	m_dcWorkAreaDC=new CDC();
	m_dcWorkAreaDC->CreateCompatibleDC(NULL);
	m_cbWorkAreaBmp=new CBitmap();
	m_cbWorkAreaBmp->CreateCompatibleBitmap(m_dcBakDC,m_iWorkAreaWidth,m_iWorkAreaHeight);
	m_dcWorkAreaDC->SelectObject(m_cbWorkAreaBmp);
	//_CreateDC(m_dcWorkAreaDC,m_cbWorkAreaBmp,m_dcBakDC,m_iWorkAreaWidth,m_iWorkAreaHeight);

	//������ͷ���ڴ�DC��������ϸ��Ϣ��ʽʱ����ΪNULL
	if(m_uiViewStyle & STYLE_REPORT)
	{
		m_dcHeaderDC=new CDC();
		m_dcHeaderDC->CreateCompatibleDC(NULL);
		m_cbHeaderBmp=new CBitmap();
		m_cbHeaderBmp->CreateCompatibleBitmap(m_dcBakDC,m_iWorkAreaTotalWidth,REPORT_HEAD_HEIGHT);
		m_dcHeaderDC->SelectObject(m_cbHeaderBmp);
		//_CreateDC(m_dcHeaderDC,m_cbHeaderBmp,m_dcBakDC,m_iWorkAreaTotalWidth,REPORT_HEAD_HEIGHT);

		//���Ʊ�ͷ
		DrawReportHeader(-1);
	}
	else
	{
		m_dcHeaderDC=NULL;
		m_cbHeaderBmp=NULL;
	}

	//����������������ڴ�DC�������������������ʱ����ΪNULL
	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		m_dcScrollVDC=new CDC();
		m_dcScrollVDC->CreateCompatibleDC(NULL);
		m_cbScrollVBmp=new CBitmap();
		m_cbScrollVBmp->CreateCompatibleBitmap(m_dcBakDC,SCROLL_BAR_WIDTH_HEIGHT,(m_uiScrollBarType & SCROLL_BAR_H?m_iCurrentViewHeight-SCROLL_BAR_WIDTH_HEIGHT:m_iCurrentViewHeight));
		m_dcScrollVDC->SelectObject(m_cbScrollVBmp);
		//_CreateDC(m_dcScrollVDC,m_cbScrollVBmp,m_dcBakDC,SCROLL_BAR_WIDTH_HEIGHT
		//	,(m_uiScrollBarType & SCROLL_BAR_H?m_iCurrentViewHeight-SCROLL_BAR_WIDTH_HEIGHT:m_iCurrentViewHeight));
	}
	else
	{
		m_dcScrollVDC=NULL;
		m_cbScrollVBmp=NULL;
	}

	//����������������ڴ�DC���������ں��������ʱ����ΪNULL
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		m_dcScrollHDC=new CDC();
		m_dcScrollHDC->CreateCompatibleDC(NULL);
		m_cbScrollHBmp=new CBitmap();
		m_cbScrollHBmp->CreateCompatibleBitmap(m_dcBakDC,m_iCurrentViewWidth,SCROLL_BAR_WIDTH_HEIGHT);
		m_dcScrollHDC->SelectObject(m_cbScrollHBmp);
		//_CreateDC(m_dcScrollHDC,m_cbScrollHBmp,m_dcBakDC,m_iCurrentViewWidth,SCROLL_BAR_WIDTH_HEIGHT);
	}
	else
	{
		m_dcScrollHDC=NULL;
		m_cbScrollHBmp=NULL;
	}

	//��ʼ��������ͼ���Լ���ť�������鲻��ʼ����
	InitScrollBar();

	//������DC�Ժ󽫲����ƵĲ�����䱳��ɫ
	FillOutofWorkArea();
}
	

//=====================================================================
// �� �� ����_MoveWorkArea
// �����������ƶ���������,���ǲ�ˢ����ʾ
// ���������int dx,int dy
// ���������
// �������ڣ�2008.10.20
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_MoveWorkArea(int dx,int dy)
{
	if(dx!=0)
	{
		m_iWorkAreaLeft+=dx;
		m_iWorkAreaRight+=dx;
	}
	if(dy!=0)
	{
		m_iWorkAreaTop+=dy;
		m_iWorkAreaBottom+=dy;
	}

	_CheckWorkArea();
}
	

//=====================================================================
// �� �� ����_DragSelect
// �����������ƶ���������,���ǲ�ˢ����ʾ
// ���������CPoint startPt:��ʼ����ѡ��ľ�������
//			 CPoint oldPt:��һ������ѡ������ľ�������
//			 CPoint nowPt:��ǰ�ľ�������
// ���������
// �������ڣ�2008.10.20
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::_DragSelect(CPoint startPt,CPoint oldPt,CPoint nowPt)
{
}
	

//=====================================================================
// �� �� ����InitLoadImageThread
// ������������ʼ������ͼ����߳�
// ���������bool killThread:���߳�����״̬ʱ�Ƿ�ɾ���߳�
// ���������void
// �������ڣ�08.09.15
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::InitLoadImageThread (bool killThread)
{
	if(killThread)
	{
		//���Ҫ��ֹ�߳�
		PublicFunc::DeleteThread(m_hLoadImage);
	}

	//��������ͼ����߳�
	m_hLoadImage=CreateThread(NULL,0,LoadImageFunc,this,0,NULL);
}
	

//=====================================================================
// �� �� ����InitLoadBaseInfoThread
// ������������ʼ�������ļ�������Ϣ���߳�
// ���������bool killThread:���߳�����״̬ʱ�Ƿ�ɾ���߳�
// ���������void
// �������ڣ�08.09.15
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::InitLoadBaseInfoThread (bool killThread)
{
	if(killThread)
	{
		//���Ҫ��ֹ�߳�
		PublicFunc::DeleteThread(m_hLoadBaseInfo);
	}

	//��������ͼ����߳�
	m_hLoadBaseInfo=CreateThread(NULL,0,LoadBaseInfoFunc,this,0,NULL);
}
		

//=====================================================================
// �� �� ����LoadImageFunc
// ��������������Image������߳�����
// ���������LPVOID lpParameter����SeeFileViewTableָ��
// ���������DWORD WINAPI
// �������ڣ�08.09.15
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
DWORD WINAPI  LoadImageFunc(LPVOID lpParameter)
{
	SeeFileViewTable * table = (SeeFileViewTable *)lpParameter;
	FileInfoControl *control = &(table->m_ficFileControl);
	FileInfoList * tmpIter;
	int tmpPos;
	
	bool loadSuc=false;			//�Ƿ���ȫ������ϣ�����������ж�

	//�����������ͼ
	while(!loadSuc)
	{
		//��ʼ������ͼ��λ��
		if(control->m_bLoadImagePosEnable)
		{
			tmpIter=control->m_filLoadImageBegin;
			tmpPos=control->m_iLoadImagePos;
			control->m_bLoadImagePosEnable=false;
		}
		else
		{
			tmpIter=control->GetHeader()->m_filNextItem;
			tmpPos=0;
		}

		while(tmpIter!=control->GetEnder())
		{
			if(control->m_bLoadImagePosEnable)
			{
				//�������ļ�λ����Чʱ���������������ļ���λ��
				tmpIter=control->m_filLoadImageBegin;
				tmpPos=control->m_iLoadImagePos;
				control->m_bLoadImagePosEnable=false;
			}

			if(tmpIter->CheckFileType(FILE_PHOTO) && tmpIter->m_bNeedGetSmallPhoto)
			{
				//����Ϊ����Ҫ��ȡ����ͼ
				tmpIter->m_bNeedGetSmallPhoto=false;
				//����Ҫ��ȡ����ͼʱ����ʱ��Ȼ��Ҫ���´���DC
				if( tmpIter->CreateSmallImage(control->m_iSmallPhotoMaxWidth,control->m_iSmallPhotoMaxHeight))
				{
					//������ͼ��ȡ�ɹ�ʱ����������ͼ��Ч
					tmpIter->m_bSmallPhotoEnable=true;
					//�����ػ����
					tmpIter->m_iiItemInfo.reDrawEnable=true;
					//�ػ��tmpPos��ͼ��
					table->PostMessageA(MES_ALZQ_REFRESH_ITEM,tmpPos);
					//table->ReFresh(false,false);
				}
			}			

			tmpIter=tmpIter->m_filNextItem;
			tmpPos++;
		}

		//����Ϊȫ���������
		loadSuc=true;

		//��ʼѭ���ж������ļ���Ϣ���ж��Ƿ�������
		tmpIter=control->GetHeader()->m_filNextItem;
		while(tmpIter!=control->GetEnder())
		{
			if(tmpIter->CheckFileType(FILE_PHOTO) && tmpIter->m_bNeedGetSmallPhoto)
			{
				//������Ҫ����IMAGEʱ������Ϊδ������ϲ��������ѭ��
				loadSuc=false;
				break;
			}

			tmpIter=tmpIter->m_filNextItem;
		}
	}

	//loadSuc=false;

	////������ϸ����ͼ
	//while(!loadSuc)
	//{
	//	//��ʼ������ͼ��λ��
	//	if(control->m_bLoadImagePosEnable)
	//	{
	//		tmpIter=control->m_filLoadImageBegin;
	//		tmpPos=control->m_iLoadImagePos;
	//		control->m_bLoadImagePosEnable=false;
	//	}
	//	else
	//	{
	//		tmpIter=control->GetHeader()->m_filNextItem;
	//		tmpPos=0;
	//	}

	//	while(tmpIter!=control->GetEnder())
	//	{
	//		if(control->m_bLoadImagePosEnable)
	//		{
	//			//�������ļ�λ����Чʱ���������������ļ���λ��
	//			tmpIter=control->m_filLoadImageBegin;
	//			tmpPos=control->m_iLoadImagePos;
	//			control->m_bLoadImagePosEnable=false;
	//		}

	//		if(tmpIter->GetIsPhoto() && tmpIter->m_bNeedGetSmallPhoto)
	//		{
	//			//����Ϊ����Ҫ��ȡ����ͼ
	//			tmpIter->m_bNeedGetSmallPhoto=false;
	//			//����Ҫ��ȡ����ͼʱ����ʱ��Ȼ��Ҫ���´���DC
	//			if( tmpIter->CreateSmallImage(control->m_iSmallPhotoMaxWidth,control->m_iSmallPhotoMaxHeight))
	//			{
	//				//������ͼ��ȡ�ɹ�ʱ����������ͼ��Ч
	//				tmpIter->m_bSmallPhotoEnable=true;
	//				//�����ػ����
	//				tmpIter->m_iiItemInfo.reDrawEnable=true;
	//				//�ػ��tmpPos��ͼ��
	//				table->RedrawItems(tmpPos,tmpPos);
	//			}
	//		}			

	//		tmpIter=tmpIter->m_filNextItem;
	//		tmpPos++;
	//	}

	//	//����Ϊȫ���������
	//	loadSuc=true;

	//	//��ʼѭ���ж������ļ���Ϣ���ж��Ƿ�������
	//	tmpIter=control->GetHeader()->m_filNextItem;
	//	while(tmpIter!=control->GetEnder())
	//	{
	//		if(tmpIter->GetIsPhoto() && tmpIter->m_bNeedGetSmallPhoto)
	//		{
	//			//������Ҫ����IMAGEʱ������Ϊδ������ϲ��������ѭ��
	//			loadSuc=false;
	//			break;
	//		}

	//		tmpIter=tmpIter->m_filNextItem;
	//	}
	//}
	return 0;
}
	

//=====================================================================
// �� �� ����LoadBaseInfoFunc
// ���������������ļ�������Ϣ���߳�����
// ���������LPVOID lpParameter����SeeFileViewTableָ��
// ���������DWORD WINAPI
// �������ڣ�08.09.16
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
DWORD WINAPI LoadBaseInfoFunc (LPVOID lpParameter)
{
	SeeFileViewTable * table = (SeeFileViewTable *)lpParameter;
	FileInfoControl *control = &(table->m_ficFileControl);
	FileInfoList * tmpIter;
	int tmpPos;
	
	bool loadSuc=false;			//�Ƿ���ȫ������ϣ�����������ж�

	while(!loadSuc)
	{
		//��ʼ������ͼ��λ��
		if(control->m_bLoadBaseInfoEnable)
		{
			tmpIter=control->m_filLoadImageBegin;
			tmpPos=control->m_iLoadImagePos;
			control->m_bLoadBaseInfoEnable=false;
		}
		else
		{
			tmpIter=control->GetHeader()->m_filNextItem;
			tmpPos=0;
		}

		while(tmpIter!=control->GetEnder())
		{
			if(control->m_bLoadBaseInfoEnable)
			{
				//�������ļ�λ����Чʱ���������������ļ���λ��
				tmpIter=control->m_filLoadImageBegin;
				tmpPos=control->m_iLoadImagePos;
				control->m_bLoadBaseInfoEnable=false;
			}

			if(tmpIter->m_bNeedGetBaseInfo)
			{
				//����Ҫ��ȡ�ļ�������Ϣʱ
				if( tmpIter->GetFileBaseInfo())
				{
					//��ȡ�ɹ�����Ϊ������Ϣ����Ҫ��ȡ
					tmpIter->m_bNeedGetBaseInfo=false;
					//�ػ��tmpPos��ͼ��
					table->PostMessageA(MES_ALZQ_REFRESH_ITEM,tmpPos);
					//table->ReFresh(false,false);
				}
			}			

			tmpIter=tmpIter->m_filNextItem;
			tmpPos++;
		}

		//����Ϊȫ���������
		loadSuc=true;

		//��ʼѭ���ж������ļ���Ϣ���ж��Ƿ�������
		tmpIter=control->GetHeader()->m_filNextItem;
		while(tmpIter!=control->GetEnder())
		{
			if(tmpIter->m_bNeedGetBaseInfo)
			{
				//������Ҫ�����ļ�������Ϣʱ������Ϊδ������ϲ��������ѭ��
				loadSuc=false;
				break;
			}

			tmpIter=tmpIter->m_filNextItem;
		}
	}

	return 0;
}
	

//=====================================================================
// �� �� ����OpenFloder
// �������������ļ���
// ���������string floderPath:��\�ŵ��ļ���·��
// ���������void
// �������ڣ�08.09.27
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵��������CDC����ػ��Ʋ����ṹ�壬�Ƿ�ѡ���Ƿ񴰿�Ϊ����
//=====================================================================
void SeeFileViewTable::OpenFloder(CString floderPath)
{
	m_sOpenFloderPath=floderPath;;
	this->GetParent()->PostMessageA(MES_ALZQ_OPEN_FLODER);
}
	

//=====================================================================
// �� �� ����GetItemCodeByMousePt
// ������������ȡ���λ���µ�ITEM���
// ���������CPoint pt
// ���������void
// �������ڣ�08.10.07
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int SeeFileViewTable::GetItemCodeByMousePt(CPoint pt)
{
	CRect  rect;  
	CPoint  point;  
	GetWindowRect(rect);  
	point.x=pt.x-rect.left;  
	point.y=pt.y-rect.top;			//����������LIST��λ��
	    
	return GetItemCodeByWindowPt(point);
}
	

//=====================================================================
// �� �� ����GetItemCodeByWindowPt
// ������������ȡ�������λ���µ�ITEM���
// ���������CPoint pt
// ���������void
// �������ڣ�08.10.07
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
int SeeFileViewTable::GetItemCodeByWindowPt(CPoint pt)
{
	if(m_uiViewStyle == STYLE_SMALL_PHOTO)
	{
		//��Ϊ����ͼʱ
		if(pt.x<0 || pt.y<0 || pt.x>m_iWorkAreaWidth || pt.y>m_iWorkAreaHeight)
		{
			//������ʾ��Χ��
			return -1;
		}

		//�ж�λ���Ƿ��ڷ�ITEM������
		pt.y+=m_iWorkAreaTop;
		if(pt.x>m_iItemWithBorderWidth * m_iPerLineItemCount)
		{
			return -1;
		}
		if(pt.y>m_iItemWithBorderHeight * m_iTotalLineCount)
		{
			return -1;
		}

		//���������ڵڼ���ITEM�ķ�Χ��
		int nItem=((pt.y/m_iItemWithBorderHeight)*m_iPerLineItemCount)+(pt.x/m_iItemWithBorderWidth);
		if(nItem>=m_ficFileControl.m_iTotalCount)
		{
			return -1;
		}

		//�ж��Ƿ�λ�ô���ITEM��Ŀհ�����
		int x=pt.x % m_iItemWithBorderWidth;
		int y=pt.y % m_iItemWithBorderHeight;
		if(x<=SMALL_PHOTO_ITEM_BORDER || m_iItemWithBorderWidth-x<=SMALL_PHOTO_ITEM_BORDER)
		{
			return -1;
		}
		if(y<=SMALL_PHOTO_ITEM_BORDER || m_iItemWithBorderHeight-y<=SMALL_PHOTO_ITEM_BORDER)
		{
			return -1;
		}

		return nItem;
	}
	else if(m_uiViewStyle == STYLE_REPORT)
	{
		//��Ϊ��ϸ��Ϣ��ʽʱ
		if(pt.x<0 || pt.y<REPORT_HEAD_HEIGHT || pt.x>m_iWorkAreaWidth || pt.y>m_iWorkAreaHeight+REPORT_HEAD_HEIGHT)
		{
			//������ʾ��Χ��
			return -1;
		}

		pt.y+=m_iWorkAreaTop-REPORT_HEAD_HEIGHT;
		if(pt.y>m_iItemWithBorderHeight * m_iTotalLineCount)
		{
			return -1;
		}

		//���������ڵڼ���ITEM�ķ�Χ��
		int nItem=pt.y/m_iItemWithBorderHeight;
		if(nItem>=m_ficFileControl.m_iTotalCount)
		{
			return -1;
		}

		return nItem;
	}

	return -1;
}
	

//=====================================================================
// �� �� ����RefreshPreview
// ����������ˢ��Ԥ������
// �����������
// �����������
// �������ڣ�2008.10.10
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::RefreshPreview(void)
{
	if(!m_wndPreviewBar)
	{
		return ;
	}

	int nItem=m_ficFileControl.GetFirstSelectedPhotoCode();

	if(nItem>=0)
	{
		FileInfoList * file=m_ficFileControl.GetFile(nItem);
		m_wndPreviewBar->m_csFileFullPath=file->GetFileFullPath().c_str();
	}
	else
	{
		m_wndPreviewBar->m_csFileFullPath="";
	}

	m_wndPreviewBar->RedrawWindow();
}
	

void SeeFileViewTable::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_mpiMousePositionInfo.positionType==POSITION_ITEM)
	{
		int nItem=GetItemCodeByWindowPt(point);
		
		if(nItem>=0)
		{
			//��ȡ˫��λ�õ��ļ���Ϣ
			FileInfoList * fileInfo=m_ficFileControl.GetFile(nItem);

			if(fileInfo->CheckFileType(FILE_FLODER) | fileInfo->CheckFileType(FILE_DISK))
			{
				//��˫���ļ���ʱ�����ļ���
				OpenFloder((fileInfo->GetFileFullPath()+"\\").c_str());
			}
			else
			{
				if(fileInfo->CheckFileType(FILE_PHOTO))
				{
					//��Ϊͼ���ļ�ʱ
					GetParent()->PostMessageA(MES_ALZQ_VIEW_PHOTO,nItem);
				}
			}
		}
	}
	else
	{
		SeeFileViewTable::OnLButtonDown(nFlags,point);
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}
	

//=====================================================================
// �� �� ����OnLvnColumnclick
// �����������������ݽ�������
// ���������NMHDR *pNMHDR, LRESULT *pResult
// ���������void
// �������ڣ�08.09.27
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(m_ficFileControl.m_iOrderType)
	{
		//��m_ficFileControl.m_iOrderType==1ʱ��ԭ���б��ǽ�������ʽ
		m_ficFileControl.SortAsc(pNMLV->iSubItem);
	}
	else
	{
		m_ficFileControl.SortDes(pNMLV->iSubItem);
	}

	Invalidate();

	*pResult = 0;
}

void SeeFileViewTable::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	 // ����һ������������Ŷ�ȡ���ļ�����Ϣ
	char szFileName[MAX_PATH + 1] = {0};

	// ͨ������iFiles����Ϊ0xFFFFFFFF,����ȡ�õ�ǰ�϶����ļ�������
	// ������Ϊ0xFFFFFFFF,��������Ժ�������������
	UINT nFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
		
	//�������λ�û�ȡλ���ļ���Ϣ
	CPoint  point;  
	GetCursorPos(&point);

	int nItem=GetItemCodeByMousePt(point);

	string filePath="";					//��Ҫ�϶������ļ�·��
	int floderCode=0;					//���϶������ļ��б��-Ĭ��Ϊ0

	if(nItem<0)
	{
		//�������Чʱ����겻���κ�ITEM��
		if(m_ficFileControl.m_iFilePathCount>1)
		{
			//���Ѿ�ѡȡ���ļ��д���1��ʱ�޷����е���ǰ�ļ���
			return ;
		}
		else
		{
			MapStringInt::iterator iter=m_ficFileControl.m_msiFilePathMap.begin();
			filePath=iter->first;

			floderCode=m_ficFileControl.m_msiFilePathMap[filePath];
		}
	}
	else
	{
		FileInfoList * fileInfo=m_ficFileControl.GetFile(nItem);
		
		if(!fileInfo->CheckFileType(FILE_FLODER))
		{
			//���ļ������ļ���ʱ��֧����ק���ļ���
			return ;
		}
		else
		{
			filePath=fileInfo->GetFileFullPath()+"\\";

			//�ж�Ŀ¼�Ƿ�����ѡȡ�ļ��м����У��ڵĻ�����Ҫ���ļ���ӽ��ļ�����
			floderCode=m_ficFileControl.m_msiFilePathMap[filePath];
		}
	}

	// ͨ��ѭ������ȡ���϶��ļ���File Name��Ϣ����������ӵ�ListBox��
	for(UINT i=0; i<nFiles; i++)
	{
		DragQueryFile(hDropInfo, i, szFileName, MAX_PATH);
		//��ȡ�ļ���
		string fullPath=string(szFileName);
		
		int mark_1=(int)fullPath.find_last_of("\\/");
		string fileName=string(fullPath,mark_1+1);
		string oldFilePath=string(fullPath,0,mark_1+1);

		if(oldFilePath.compare(filePath)!=0)
		{
			//�����ļ�·������Ҫ���Ƶ������ļ�·����ͬʱ�Ž��и��Ʋ���ӽ�����
			string newFileFullPath=filePath+fileName;

			int res=IDYES;
			if(access(newFileFullPath.c_str(),0)==0)
			{
				//�����Ƶ����ļ�����ʱѯ�ʣ�����ͬ��ѯ��ʱ
				res=AfxMessageBox(("�ļ���"+newFileFullPath+" �Ѿ����ڣ������Ƿ񸲸ǣ�").c_str(),MB_ICONQUESTION|MB_YESNO);
			}

			if(res==IDYES)
			{
				//���ļ����в��������ļ���ԭ�ļ��м��е���ǰ�ļ���
				MoveFileEx(fullPath.c_str(),newFileFullPath.c_str(),MOVEFILE_COPY_ALLOWED|MOVEFILE_REPLACE_EXISTING);
	
				if(floderCode)
				{
					//���ļ���ӽ�����
					FileInfoList * file=m_ficFileControl.AddFile(newFileFullPath,floderCode);
					file->GetFileBaseInfo();
				}
			}
		}
	}

	// �����˴���ק���������ͷŷ������Դ
	DragFinish(hDropInfo);

	//���������������Ϣ
	m_maiMouseActionInfo.dragStartPt=point;
	m_maiMouseActionInfo.mouseCondition &= ~MOUSE_LBT_DOWN;			//�ڲ���״̬��ʹ�û����

	//����������Ϊ�գ����ͷ�����ȡ����ʱ��������Ҽ��Ƿ���в�����������������Ϣ
	m_maiMouseActionInfo.mouseCondition=MOUSE_NONE;
	//�ͷ���궯������
	ReleaseCapture();

	m_maiMouseActionInfo.mousePositionInfo.positionType=m_mpiMousePositionInfo.positionType;
	m_maiMouseActionInfo.mousePositionInfo.value=m_mpiMousePositionInfo.value;

	if(floderCode)
	{
		//ˢ����ʾ
		RedrawWorkArea(true);
		Refresh();
	}

	//CListCtrl::OnDropFiles(hDropInfo);
}

void SeeFileViewTable::OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ���������� 
	int nItem=pNMLV->iItem;

	if(nItem<0)
	{
		//��δ��ק�κ�ITEMʱ
		return;
	}


	*pResult   =   0; 
}


//=====================================================================
// �� �� ����showEdit
// ������������ʾ�������༭��
// ����������û�ѡ�е��ļ�����ֵ
// �����������
// �������ڣ�2008.10.7
// �޸�����: alzq 08.10.09
// �� �ߣ�   ���Ի�
// ����˵���� 
//=====================================================================
void SeeFileViewTable::showEdit(int nItem)
{
	if(!m_bCreateEdit)
	{
 		m_wndEdit.Create(WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER,CRect(0,0,150,20),this,IDC_RENAME_EDIT);
		m_bCreateEdit=true;
	}
	CRect rcItem;
	FileInfoList * fileQ=this->m_ficFileControl.GetFile(nItem);
	//��ʾ���ļ���
	m_wndEdit.SetWindowTextA(fileQ->GetFileName().c_str());//.append(".").append(fileQ->GetFileExtName()).c_str());
	//���Item����λ�õľ���
	//this->GetItemRect(nItem,&rcItem,LVIR_LABEL);
	//�����������Ķ�����
	m_nSelect=nItem;
	//��Edit�ƶ�����ǰ���ε�λ��
	m_wndEdit.MoveWindow(rcItem);
	//��ʾEdit
	m_wndEdit.ShowWindow(SW_SHOW);
	//����Edit������������С
	m_wndEdit.SetSel(0,100);
	//���ý�����Edit��
	m_wndEdit.SetFocus();

	m_bDealMouseAction=false;
}

//=====================================================================
// �� �� ����DisposeEdit
// ������������ʧȥ����֮������û���������ļ����ж��Ƿ�����ļ������������
// �����������
// �����������
// �������ڣ�2008.9.2
// �޸�����: 2008.9.4--alzq 08.10.09
// �� �ߣ�   ���Ի�
// ����˵���� 
//=====================================================================
void SeeFileViewTable::DisposeEdit(void)
{
	CString newname="";
	//����û�������������ַ���
	m_wndEdit.GetWindowTextA(newname);
	//���ѡ�е��ļ���Ϣ�б�
	FileInfoList* renameFileInfo=this->m_ficFileControl.GetFile(m_nSelect);
	//���ѡ���ļ�����չ��
	string oldExtname=renameFileInfo->GetFileExtName();
	//��þ���չ���ĳ���
	int oldExtlength=(int)oldExtname.length();
	//�ж��û���������ļ����Ƿ�ǿ�
	if(!newname.IsEmpty())
	{
		//������չ��,����չ��������ԭ�ȵ���չ��
		if(newname.Find('.')!=-1&&(newname.Right(oldExtlength).Compare(oldExtname.c_str())!=0))
		{
			//�����Ի�����ʾ�Ƿ�ȥ�����ļ���չ��
			int nRet=AfxMessageBox("�ı��ļ�����չ�����ܵ����ļ������ã���ȷ��Ҫ�ı�����",MB_YESNO|MB_ICONQUESTION);	
			//ȷ�������
			if (nRet==IDYES)
			{
				//�������ļ�
				renameFileInfo->ISetFileNameAndExtName(newname.GetString());
			}
			else
			{
				//���򷵻أ�û�иı䣬��Ȼ��ԭ��
				//���ر༭��
				m_wndEdit.ShowWindow(SW_HIDE);
			}
		}
		//������չ��������չ����ԭ�ȵ���չ�����
		else if(newname.Find('.')!=-1&&(newname.Right(oldExtlength).Compare(oldExtname.c_str())==0))
		{
			//�������ļ�
			renameFileInfo->ISetFileName(newname.GetString());
		}
		else
		{
			//ִ�е������ʾ��û��������չ��
			//�������ļ�
			string newnameNoExt=newname;
			renameFileInfo->ISetFileName(newnameNoExt.append(".").append(renameFileInfo->GetFileExtName()));
		}
		//���»���item
		ReDrawItem(m_nSelect);

	}
	//���ر༭��
	m_wndEdit.ShowWindow(SW_HIDE);
	//�����������ļ�״̬����Ϊѡ��
	renameFileInfo->SetState(LVIS_SELECTED,true,LVIS_SELECTED); 

	m_bDealMouseAction=true;
}
	

//=====================================================================
// �� �� ����SetListStyle
// ���������������б����ʾ��ʽ
// ���������UINT style
// �����������
// �������ڣ�2008.10.11
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::SetListStyle(UINT style)
{
	//������ʽ
	m_uiViewStyle=style;

	if(style == STYLE_SMALL_PHOTO)
	{
		//��ԭ����ͼ��С��������ͼ��С��ͬʱ��������ͼ���ITEM��Χ
		SetSmallPhotoSize(200,160);		//����Ĭ�ϵ�����ͼ��Χ
	}
	else if(style == STYLE_REPORT)
	{
		SetReportItemSize();
	}

	//ȫ��ˢ�²�����ʾ
	_ResizeWorkAreaWithoutGroup(true);
	//��հ�����
	FillOutofWorkArea();
	RedrawWorkArea(true);
	Refresh();
}
	

//=====================================================================
// �� �� ����SetSmallPhotoSize
// ������������������ͼ��С
// ���������
// �����������
// �������ڣ�2008.10.11
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::SetSmallPhotoSize()
{
	//���㵱ǰÿ��ITEM�Ŀ����߶�
	m_iItemWidth=m_ficFileControl.m_iSmallPhotoMaxWidth
		+(2*PHOTO_BORDER_WIDTH)
		+PHOTO_SHADOW_WIDTH;
	m_iItemHeight=m_ficFileControl.m_iSmallPhotoMaxHeight
		+(2*PHOTO_BORDER_WIDTH)
		+PHOTO_SHADOW_WIDTH
		+PHOTO_SMALL_TARGET_HEIGHT
		+PHOTO_SMALL_WORD_HEIGHT;
	m_iItemWithBorderWidth=m_iItemWidth+(2*SMALL_PHOTO_ITEM_BORDER);						//ÿ��ITEM�Ŀ��
	m_iItemWithBorderHeight=m_iItemHeight+(2*SMALL_PHOTO_ITEM_BORDER);						//ÿ��ITEM�ĸ߶�

	//���¼������겢����ʾ
	_ResizeWorkAreaWithoutGroup(true);
	//��հ�����
	FillOutofWorkArea();
	RedrawWorkArea(true);
	Refresh();
}
	

//=====================================================================
// �� �� ����SetSmallPhotoSize
// ������������������ͼ��С
// ���������int width,int height
// �����������
// �������ڣ�2008.10.11
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::SetSmallPhotoSize(int width,int height)
{
	m_ficFileControl.SetSmallPhotoMaxSize(width,height);

	//����
	SetSmallPhotoSize();
}
	

//=====================================================================
// �� �� ����SetReportItemSize
// ����������������ϸ��Ϣ��ʽʱ�����ITEM��Ϣ
// ���������
// �����������
// �������ڣ�2008.10.11
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::SetReportItemSize()
{
	//���㵱ǰÿ��ITEM�Ŀ����߶�
	m_iItemHeight=REPORT_ITEM_HEIGHT;
	m_iItemWithBorderHeight=REPORT_ITEM_HEIGHT;											//ÿ��ITEM�ĸ߶�
}
	

//=====================================================================
// �� �� ����SetWorkAreaToItem
// ��������������ʾ�������õ����ΪnItem��Item��������
// ���������int nItem
// �����������
// �������ڣ�2008.10.11
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::SetWorkAreaToItem(int nItem)
{
	if(m_ficFileControl.m_bOrderByGroup)
	{
		//�������˷�������ʱ�����㷽ʽ��ͬ
	}
	else
	{
		SetWorkAreaToItemWithoutGroup(nItem);
	}
}
	

//=====================================================================
// �� �� ����SetWorkAreaToItemWithoutGroup
// ������������δ���������£�����ʾ�������õ����ΪnItem��Item��������
// ���������int nItem
// �����������
// �������ڣ�2008.10.11
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::SetWorkAreaToItemWithoutGroup(int nItem)
{
	//����ʾΪ����ͼ��ʽʱ
	if(nItem<0 || !m_uiScrollBarType)
	{
		//����ѡ��������϶�������ֻ��һҳ������ʾ��ҳ
		m_iWorkAreaTop=0;
		m_iWorkAreaBottom=m_iWorkAreaHeight;
	}
	else
	{
		int line=(nItem/m_iPerLineItemCount);				//ITEM�����У�������0��ʼ����
		int behindLine=m_iTotalLineCount-line;				//����ITEM�����е����һ�д��ڼ���

		if(behindLine<m_iPerPageLineCount)
		{
			//�������������ڣ�����󻹲���һҳʱ����ʾ���һҳ
			if(m_iWorkAreaTotalHeight>m_iWorkAreaHeight)
			{
				m_iWorkAreaTop=m_iWorkAreaTotalHeight-m_iWorkAreaHeight;
				m_iWorkAreaBottom=m_iWorkAreaTotalHeight;
			}
			else
			{
				m_iWorkAreaTop=0;
				m_iWorkAreaBottom=m_iWorkAreaHeight;
			}
		}
		else
		{
			//��ʾ��������Ϊ��һ�е�ҳ��
			m_iWorkAreaTop=m_iItemWithBorderHeight * line;
			m_iWorkAreaBottom=m_iWorkAreaTop + m_iWorkAreaHeight;
		}
	}

	ItemRange rang=SetShowItemRange(m_iWorkAreaTop,m_iWorkAreaBottom);
	m_iShowItemHead=rang.head;
	m_iShowItemEnd=rang.end;
}
	

//=====================================================================
// �� �� ����SetShowItemRange
// ������������ȡ�ڸ߶�top��bottom����ʾ��Item��Χ
// ���������int top,int bottom
// ���������ItemRange
// �������ڣ�2008.10.11
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
ItemRange SeeFileViewTable::SetShowItemRange(int top,int bottom)
{
	ItemRange rang;
	rang.head=((top/m_iItemWithBorderHeight)*m_iPerLineItemCount);								//��ʾ����ĵ�һ��ITEM
	if(m_ficFileControl.m_iTotalCount<=0)
	{
		rang.head=-1;
	}

	rang.end=((bottom/m_iItemWithBorderHeight)*m_iPerLineItemCount)+m_iPerLineItemCount-1;		//��ʾ��������һ��ITEM
	if(rang.end>=m_ficFileControl.m_iTotalCount)
	{
		rang.end=m_ficFileControl.m_iTotalCount-1;
	}

	return rang;
}
	

//=====================================================================
// �� �� ����GetItemPosition
// ������������ȡ��nItem��ITEM��λ��:�����ʾ������ڴ�DC(m_dcWorkAreaDC)
// ���������int nItem
// ���������CPoint
// �������ڣ�2008.10.12
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
CPoint SeeFileViewTable::GetItemPosition(int nItem)
{
	CPoint pt;
	pt.x=(nItem % m_iPerLineItemCount) * m_iItemWithBorderWidth;
	pt.y=(nItem/m_iPerLineItemCount)*m_iItemWithBorderHeight;
	return pt;
}
	

//=====================================================================
// �� �� ����OpenFloderList
// �������������ļ���
// ���������CString floderPath
// ���������
// �������ڣ�2008.10.12
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::OpenFloderList(CString filePath)
{
	//�ر����������߳�
	PublicFunc::DeleteThread(m_hLoadImage);
	PublicFunc::DeleteThread(m_hLoadBaseInfo);
	
	//ʹ���ļ���Ϣ�����࣬���ļ���
	string filePathString=filePath.GetBuffer(0);
	if(filePathString.find_last_of("\\")!=filePathString.length()-1)
	{
		filePathString+="\\";
	}
	m_ficFileControl.OpenFloder(filePathString,0);

	_ResizeWorkAreaWithoutGroup(true);
	//��հ�����
	FillOutofWorkArea();
	RedrawWorkArea(true);
	Refresh();

	//�����ܵ�ITEM����
	//m_sfvtFileViewTable.SetItemCount(m_sfvtFileViewTable.m_ficFileControl.m_iTotalCount);
	/*m_sfvtFileViewTable.SetItemCountEx(m_sfvtFileViewTable.m_ficFileControl.m_iTotalCount,LVSICF_NOINVALIDATEALL);
	if(m_sfvtFileViewTable.m_ficFileControl.m_iTotalCount==0)
	{
		 m_sfvtFileViewTable.Invalidate();
	}*/

	//����Image�����߳�
	InitLoadImageThread(true);
	//�����ļ�������Ϣ�����߳�
	InitLoadBaseInfoThread(true);
}
	

//=====================================================================
// �� �� ����Refresh
// ����������ˢ����Ļ
// ���������
// ���������
// �������ڣ�2008.10.17
// �޸����ڣ�
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::Refresh()
{
	if(!m_dcBakDC)
	{
		return ;
	}

	int dy=0;
	if(m_uiViewStyle & STYLE_REPORT)
	{
		//��Ϊ��ϸ��Ϣģʽʱ���߶���Ҫ+20
		dy=REPORT_HEAD_HEIGHT;
		//���Ʊ�ͷ����ʾDC��
		m_dcMemeryDC->BitBlt(0,0,m_iWorkAreaWidth,REPORT_HEAD_HEIGHT,m_dcHeaderDC,m_iWorkAreaLeft,0,SRCCOPY);
	}

	//������ʾ����
	m_dcMemeryDC->BitBlt(0,dy,m_iWorkAreaWidth,m_iWorkAreaHeight,m_dcWorkAreaDC,0,0,SRCCOPY);

	if(m_maiMouseActionInfo.mouseCondition & MOUSE_DRAG_SELECT)
	{
		//������������ѡ���ʱ��
		CPoint pt=m_maiMouseActionInfo.mousePositionInfo.pt;

		//���㳤��
		int x=abs(m_mpiMousePositionInfo.pt.x-pt.x);
		int y=abs(m_mpiMousePositionInfo.pt.y-pt.y);

		//�������Ͻ�����
		pt.x=pt.x<m_mpiMousePositionInfo.pt.x?pt.x:m_mpiMousePositionInfo.pt.x;
		pt.y=pt.y<m_mpiMousePositionInfo.pt.y?pt.y:m_mpiMousePositionInfo.pt.y;

		//�������������ɵ�ǰ��ʾ�Ĵ�������
		pt.x-=m_iWorkAreaLeft;
		pt.y-=m_iWorkAreaTop;

		if(pt.x>m_iWorkAreaWidth)
		{
			//�����Ͻ��������ұ߽���ʱ����ʾ
		}
		else if(pt.y>m_iWorkAreaHeight)
		{
		}
		else
		{
			if(pt.x<0)
			{
				x+=pt.x;
				pt.x=0;
			}
			if(pt.y<0)
			{
				y+=pt.y;
				pt.y=0;
			}

			if(pt.x+x>m_iWorkAreaWidth)
			{
				x=m_iWorkAreaWidth-pt.x;
			}
			if(pt.y+y>m_iWorkAreaHeight)
			{
				y=m_iWorkAreaHeight-pt.y;
			}
	
			Gdiplus::Graphics graph(m_dcMemeryDC->GetSafeHdc());
			graph.FillRectangle(m_brSelectBrush,pt.x,pt.y+dy,x,y);
		}
	}

	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//�����ں���������ʱ
		m_dcMemeryDC->BitBlt(0,m_iCurrentViewHeight-SCROLL_BAR_WIDTH_HEIGHT,m_sbsHScrollBarState.scrollTotalLength,SCROLL_BAR_WIDTH_HEIGHT,m_dcScrollHDC,0,0,SRCCOPY);
	}

	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//����������������ʱ
		m_dcMemeryDC->BitBlt(m_iCurrentViewWidth-SCROLL_BAR_WIDTH_HEIGHT,0,SCROLL_BAR_WIDTH_HEIGHT,m_sbsVScrollBarState.scrollTotalLength,m_dcScrollVDC,0,0,SRCCOPY);
	}

	//���ƻ���������
	DrawScrollBarMidBT();

	GetDC()->BitBlt(0,0,m_iCurrentViewWidth,m_iCurrentViewHeight,m_dcMemeryDC,0,0,SRCCOPY);
}
	

//=====================================================================
// �� �� ����Refresh
// ����������ˢ����Ļָ����Χ��ͼ��
// ���������CRect rect:ˢ�µķ�Χ
// ���������
// �������ڣ�2008.10.17
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::Refresh(CRect rect)
{
	int dy=0;
	if(m_uiViewStyle & STYLE_REPORT)
	{
		//��Ϊ��ϸ��Ϣģʽʱ���߶���Ҫ+20
		dy=REPORT_HEAD_HEIGHT;
		if(rect.top<dy && rect.right<=m_iWorkAreaWidth)
		{
			//�������ڰ�����ͷ��Χʱ
			//���Ʊ�ͷ����ʾDC��
			m_dcMemeryDC->BitBlt(
				rect.left
				,rect.top
				,rect.Width()
				,rect.bottom>dy?dy-rect.top:rect.Height()
				,m_dcHeaderDC
				,m_iWorkAreaLeft+rect.left
				,rect.top
				,SRCCOPY);
		}
	}

	//������ʾ����
	if(rect.bottom>dy && rect.left<m_iWorkAreaWidth)
	{
		m_dcMemeryDC->BitBlt(
			rect.left
			,rect.top>=dy?rect.top:dy
			,rect.right<=m_iWorkAreaWidth?rect.Width():m_iWorkAreaWidth-rect.left
			,rect.top>=dy?rect.Height():rect.bottom-dy
			,m_dcWorkAreaDC
			,rect.left
			,rect.top>=dy?rect.top-dy:0
			,SRCCOPY);
	}

	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//�����ں���������ʱ
		if(m_iCurrentViewHeight-rect.bottom<SCROLL_BAR_WIDTH_HEIGHT)
		{
			m_dcMemeryDC->BitBlt(
				rect.left
				,m_iCurrentViewHeight-rect.top<=SCROLL_BAR_WIDTH_HEIGHT?rect.top:m_iCurrentViewHeight-SCROLL_BAR_WIDTH_HEIGHT
				,rect.Width()
				,m_iCurrentViewHeight-rect.top<=SCROLL_BAR_WIDTH_HEIGHT?rect.Height():SCROLL_BAR_WIDTH_HEIGHT-(m_iCurrentViewHeight-rect.bottom)
				,m_dcScrollHDC
				,rect.left
				,m_iCurrentViewHeight-rect.top<=SCROLL_BAR_WIDTH_HEIGHT?SCROLL_BAR_WIDTH_HEIGHT-(m_iCurrentViewHeight-rect.top):0
				,SRCCOPY);
		}
	}

	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//����������������ʱ
		if(m_iCurrentViewWidth-rect.right<SCROLL_BAR_WIDTH_HEIGHT && rect.top<m_iWorkAreaHeight+dy)
		{
			m_dcMemeryDC->BitBlt(
				m_iCurrentViewWidth-rect.left<=SCROLL_BAR_WIDTH_HEIGHT?rect.left:m_iCurrentViewWidth-SCROLL_BAR_WIDTH_HEIGHT
				,rect.top
				,m_iCurrentViewWidth-rect.left<=SCROLL_BAR_WIDTH_HEIGHT?rect.Width():SCROLL_BAR_WIDTH_HEIGHT-(m_iCurrentViewWidth-rect.right)
				,rect.bottom>=m_iWorkAreaHeight+dy?m_iWorkAreaHeight-rect.top:rect.Height()
				,m_dcScrollVDC
				,m_iCurrentViewWidth-rect.left<=SCROLL_BAR_WIDTH_HEIGHT?SCROLL_BAR_WIDTH_HEIGHT-(m_iCurrentViewWidth-rect.left):0
				,rect.top
				,SRCCOPY);
		}
	}

	//���ƻ���������
	DrawScrollBarMidBT();

	GetDC()->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),m_dcMemeryDC,rect.left,rect.top,SRCCOPY);
}
	

//=====================================================================
// �� �� ����RefreshWorkArea
// ����������ˢ����Ļ�е���ʾ����
// ���������
// ���������
// �������ڣ�2008.10.17
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::RefreshWorkArea()
{
	int dy=0;
	if(m_uiViewStyle & STYLE_REPORT)
	{
		//��Ϊ��ϸ��Ϣģʽʱ���߶���Ҫ+20
		dy=REPORT_HEAD_HEIGHT;
	}
	GetDC()->BitBlt(0,dy,m_iWorkAreaWidth,m_iWorkAreaHeight,m_dcWorkAreaDC,0,0,SRCCOPY);
}
	

//=====================================================================
// �� �� ����ReDrawItem
// ��������������һ��ITEM��ˢ��ITEM�ķ�Χ
// ���������int nItem
// ���������
// �������ڣ�2008.10.17
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::ReDrawItem(int nItem)
{
	_ReDrawItems(nItem,nItem);
	CRect rect=GetItemRect(nItem);
	Refresh(rect);
}
	

//=====================================================================
// �� �� ����ReDrawItems
// �������������Ʒ�Χ�ڵ���,��ˢ����Ļ
// ���������int head,int end
// ���������
// �������ڣ�2008.10.17
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::ReDrawItems(int head,int end)
{
	_ReDrawItems(head,end);
	RefreshWorkArea();
}
	

//=====================================================================
// �� �� ����DrawScrollBarBT
// ���������������϶���DC�ϵİ�ť
// ���������
// ���������
// �������ڣ�2008.10.17
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::DrawScrollBarBT()
{
	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//���϶���Ϊ��ֱ����ʱ
		CPoint pt(0,0);
		//�������ϰ�ť
		m_cilScrollBarUp->Draw(m_dcScrollVDC,m_sbsVScrollBarState.upButState,pt,ILD_NORMAL);
		//�������°�ť
		pt.y=m_sbsVScrollBarState.scrollDragLength+SCROLL_BAR_WIDTH_HEIGHT;
		m_cilScrollBarDown->Draw(m_dcScrollVDC,m_sbsVScrollBarState.downButState,pt,ILD_NORMAL);
	}
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//���϶���Ϊˮƽ����ʱ 
		CPoint pt(0,0);
		//�������ϰ�ť
		m_cilScrollBarLeft->Draw(m_dcScrollHDC,m_sbsHScrollBarState.upButState,pt,ILD_NORMAL);
		//�������°�ť
		pt.x=m_sbsHScrollBarState.scrollDragLength+SCROLL_BAR_WIDTH_HEIGHT;
		m_cilScrollBarRight->Draw(m_dcScrollHDC,m_sbsHScrollBarState.downButState,pt,ILD_NORMAL);
	}
}
	

//=====================================================================
// �� �� ����InitScrollBar
// ������������ʼ��������ͼ��
// ���������
// ���������
// �������ڣ�2008.10.17
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::InitScrollBar()
{
	if(!m_dcBakDC)
	{
		return ;
	}

	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//���϶���Ϊ��ֱ����ʱ
		Gdiplus::Graphics graph(m_dcScrollVDC->GetSafeHdc());
		CPoint pt(0,0);
		//��������������ɫ
		graph.FillRectangle(m_brScrollBarBakBrush,pt.x,pt.y,SCROLL_BAR_WIDTH_HEIGHT,m_sbsVScrollBarState.scrollTotalLength);
		//�������ϰ�ť
		m_cilScrollBarUp->Draw(m_dcScrollVDC,m_sbsVScrollBarState.upButState,pt,ILD_NORMAL);
		//�������°�ť
		pt.y=m_sbsVScrollBarState.scrollDragLength+SCROLL_BAR_WIDTH_HEIGHT;
		m_cilScrollBarDown->Draw(m_dcScrollVDC,m_sbsVScrollBarState.downButState,pt,ILD_NORMAL);

		//������λ��
		//pt.y=m_sbsVScrollBarState.scrollMidPosition;
		//�����м仮��ı���ɫ
		//graph.FillRectangle(m_brScrollBarMidBakBrush,pt.x,pt.y,SCROLL_BAR_WIDTH_HEIGHT,m_sbsVScrollBarState.scrollMidButLength);
		//�����м仮��ı�Եɫ
		//graph.DrawRectangle(m_penScrollBarMidBakBorder,pt.x+1,pt.y+1,SCROLL_BAR_WIDTH_HEIGHT-2,m_sbsVScrollBarState.scrollMidButLength-1);
	}
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//���϶���Ϊˮƽ����ʱ 
		Gdiplus::Graphics graph(m_dcScrollHDC->GetSafeHdc());
		CPoint pt(0,0);
		//��������������ɫ
		graph.FillRectangle(m_brScrollBarBakBrush,pt.x,pt.y,m_sbsHScrollBarState.scrollTotalLength,SCROLL_BAR_WIDTH_HEIGHT);
		//�������ϰ�ť
		m_cilScrollBarLeft->Draw(m_dcScrollHDC,m_sbsHScrollBarState.upButState,pt,ILD_NORMAL);
		//�������°�ť
		pt.x=m_sbsHScrollBarState.scrollDragLength+SCROLL_BAR_WIDTH_HEIGHT;
		m_cilScrollBarRight->Draw(m_dcScrollHDC,m_sbsHScrollBarState.downButState,pt,ILD_NORMAL);

		//���㻬����λ��
		//pt.x=m_sbsHScrollBarState.scrollMidPosition;
		//�����м仮��ı���ɫ
		//graph.FillRectangle(m_brScrollBarMidBakBrush,pt.x,pt.y,m_sbsHScrollBarState.scrollMidButLength,SCROLL_BAR_WIDTH_HEIGHT);
		//�����м仮��ı�Եɫ
		//graph.DrawRectangle(m_penScrollBarMidBakBorder,pt.x+1,pt.y+1,m_sbsHScrollBarState.scrollMidButLength-1,SCROLL_BAR_WIDTH_HEIGHT-2);
	}
}
	

//=====================================================================
// �� �� ����DrawScrollBarMidBT
// �������������ƻ������Ļ����飨����ʾDC�ϣ�
// ���������
// ���������
// �������ڣ�2008.10.17
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::DrawScrollBarMidBT()
{
	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//���㻬�����λ��
		int x=(m_iWorkAreaTop*(m_sbsVScrollBarState.scrollDragLength-m_sbsVScrollBarState.scrollMidButLength));
		m_sbsVScrollBarState.scrollMidPosition=SCROLL_BAR_WIDTH_HEIGHT+(x/(m_iWorkAreaTotalHeight-m_iWorkAreaHeight));
		//�����м仮��ı���ɫ
		m_dcMemeryDC->FillSolidRect(
			m_iCurrentViewWidth-SCROLL_BAR_WIDTH_HEIGHT
			,m_sbsVScrollBarState.scrollMidPosition
			,SCROLL_BAR_WIDTH_HEIGHT
			,m_sbsVScrollBarState.scrollMidButLength
			,m_sbcsScrollBarColorSet.normalBak);
		//�����м仮��ı�Եɫ
		//graph.DrawRectangle(m_penScrollBarMidBakBorder,pt.x+1,pt.y+1,SCROLL_BAR_WIDTH_HEIGHT-2,m_sbsVScrollBarState.scrollMidButLength-1);
	}
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//���㻬�����λ��
		int x=(m_iWorkAreaLeft*(m_sbsHScrollBarState.scrollDragLength-m_sbsHScrollBarState.scrollMidButLength));
		m_sbsHScrollBarState.scrollMidPosition=SCROLL_BAR_WIDTH_HEIGHT+(x/(m_iWorkAreaTotalWidth-m_iWorkAreaWidth));
		//�����м仮��ı���ɫ
		m_dcMemeryDC->FillSolidRect(
			m_sbsHScrollBarState.scrollMidPosition
			,m_iCurrentViewHeight-SCROLL_BAR_WIDTH_HEIGHT
			,m_sbsHScrollBarState.scrollMidButLength
			,SCROLL_BAR_WIDTH_HEIGHT
			,m_sbcsScrollBarColorSet.normalBak);
		//graph.FillRectangle(m_brScrollBarMidBakBrush,pt.x,pt.y,m_sbsHScrollBarState.scrollMidButLength,SCROLL_BAR_WIDTH_HEIGHT);
		//�����м仮��ı�Եɫ
		//graph.DrawRectangle(m_penScrollBarMidBakBorder,pt.x+1,pt.y+1,m_sbsHScrollBarState.scrollMidButLength-1,SCROLL_BAR_WIDTH_HEIGHT-2);
	}
}
	

//=====================================================================
// �� �� ����DrawReportHeader
// ����������������ϸ��Ϣ��ʽ�ı�ͷ,ָ���л�ȫ��
// ���������int nLine��-1Ϊȫ��������Ϊָ����
// ���������
// �������ڣ�2008.10.15
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::DrawReportHeader(int nLine)
{
	if(!m_dcBakDC)
	{
		return ;
	}

	Gdiplus::Graphics graph(m_dcHeaderDC->GetSafeHdc());

	VectorColumnInfo::iterator iter=m_vciColumnsInfo.begin();
	for(int i=0;i<m_iTotalColumnCount;i++)
	{
		int left=iter->startPosition;
		int right=iter->endPosition;
		if(nLine==-1 || nLine==i)
		{
			//������������ʾ��ͷʱ
			SolidBrush * brush;
			//��ȡ����ˢ
			switch(iter->headState)
			{
				case STATE_MOUSE_OVER:
					brush=m_brScrollBarMidMouseOnBrush; break;
				case STATE_MOUSE_LDOWN:
					brush=m_brScrollBarMidDragBrush; break;
				default:
					brush=m_brScrollBarMidBakBrush;
			};
			//���Ʊ�ͷ����ɫ
			graph.FillRectangle(brush,left,0,iter->width,REPORT_HEAD_HEIGHT);
			
			Pen * pen;
			//��ȡ��Եˢ
			switch(iter->headState)
			{
				case STATE_MOUSE_OVER:
					pen=m_penScrollBarMidMouseOnBorder; break;
				case STATE_MOUSE_LDOWN:
					pen=m_penScrollBarMidDragBorder; break;
				default:
					pen=m_penScrollBarMidBakBorder;
			};
			graph.DrawRectangle(pen,left+1,1,iter->width-2,REPORT_HEAD_HEIGHT-2);

			//�������
			//�����п�ȴ���ͼ����ʾ��ռ���ʱ��Ҫ��ʾ����
			USES_CONVERSION;
			CString str=iter->columnName;
			WCHAR * wchar=A2W(str);
			RectF txtRectF(
				left
				,3
				,iter->width
				,REPORT_HEAD_HEIGHT-3);

			graph.DrawString(
				wchar
				,wcslen(wchar)
				,m_fntFontBlod
				,txtRectF
				,m_sfStringFormatCenter
				,m_brFontBrush);
		}

		iter++;
	}


	if(m_iWorkAreaTotalWidth<m_iWorkAreaWidth)
	{
		//�������������ұ߽�����ʾ�����ڣ���δ��ʾ�������Ϊ����ɫ
		graph.FillRectangle(m_brScrollBarMidBakBrush,m_iWorkAreaTotalWidth,0,m_iWorkAreaWidth-m_iWorkAreaTotalWidth,REPORT_ITEM_HEIGHT);			//����ʾ���ΪITEM�������
	}
}
	

//=====================================================================
// �� �� ����ReSetScrollBarInfo
// �������������¼����϶�������ز���
// ���������
// ���������
// �������ڣ�2008.10.13
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::ReSetScrollBarInfo()
{
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//����ť״̬��ʼ��
		m_sbsHScrollBarState.upButState=STATE_NONE;
		m_sbsHScrollBarState.midButState=STATE_NONE;
		m_sbsHScrollBarState.downButState=STATE_NONE;
		m_sbsHScrollBarState.scrollTotalLength=m_iCurrentViewWidth;
		m_sbsHScrollBarState.scrollDragLength=m_sbsHScrollBarState.scrollTotalLength-(2*SCROLL_BAR_WIDTH_HEIGHT);
		m_sbsHScrollBarState.scrollMidButLength=(m_sbsHScrollBarState.scrollDragLength*m_iWorkAreaWidth)/m_iWorkAreaTotalWidth;
		if(m_sbsHScrollBarState.scrollMidButLength<6){m_sbsHScrollBarState.scrollMidButLength=6;}

		//�������λ���ж��Ƿ���ĳһBUT�ϣ�ͬʱ�������ڽ��еĲ����ж�BUT�Ƿ���Ҫ���ڰ���״̬
	}
	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//����ť״̬��ʼ��
		m_sbsVScrollBarState.upButState=STATE_NONE;
		m_sbsVScrollBarState.midButState=STATE_NONE;
		m_sbsVScrollBarState.downButState=STATE_NONE;
		m_sbsVScrollBarState.scrollTotalLength=m_iCurrentViewHeight;
		if(m_uiScrollBarType & SCROLL_BAR_H)
		{
			m_sbsVScrollBarState.scrollTotalLength=m_sbsVScrollBarState.scrollTotalLength-SCROLL_BAR_WIDTH_HEIGHT;
		}
		m_sbsVScrollBarState.scrollDragLength=m_sbsVScrollBarState.scrollTotalLength-(2*SCROLL_BAR_WIDTH_HEIGHT);
		m_sbsVScrollBarState.scrollMidButLength=(m_sbsVScrollBarState.scrollDragLength*m_iWorkAreaHeight)/m_iWorkAreaTotalHeight;
		if(m_sbsVScrollBarState.scrollMidButLength<6){m_sbsVScrollBarState.scrollMidButLength=6;}

		//�������λ���ж��Ƿ���ĳһBUT�ϣ�ͬʱ�������ڽ��еĲ����ж�BUT�Ƿ���Ҫ���ڰ���״̬
	}

	InitScrollBar();
}
	

//=====================================================================
// �� �� ����InitColumnInfo
// ������������ʼ������Ϣ����Ҫ��ȡ���ݿ⣬��ʱ���ù̶���ʼ��
// ���������
// ���������
// �������ڣ�2008.10.13
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::InitColumnInfo()
{
	m_vciColumnsInfo.clear();
	m_iTotalColumnCount=0;
	int totalWidth=0;

	for(int i=0;i<7;i++)
	{
		ColumnInfo columnInfo;
		columnInfo.columnName.Format("%s%i","line_",i);
		columnInfo.infoType.code=i;
		columnInfo.orderedColumn=ORDER_NONE;
		columnInfo.width=200;
		columnInfo.startPosition=totalWidth;
		columnInfo.endPosition=columnInfo.startPosition+columnInfo.width;
		columnInfo.headState=SCROLL_BAR_NONE;
		columnInfo.contentState=HEAD_ALI_CENTER;

		totalWidth+=columnInfo.width;

		m_vciColumnsInfo.push_back(columnInfo);
		m_iTotalColumnCount++;
	}

	m_iWorkAreaTotalWidth=totalWidth;
}
	

//=====================================================================
// �� �� ����FillOutofWorkArea
// �������������ǹ���������ʾ����
// ���������
// ���������
// �������ڣ�2008.10.14
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::FillOutofWorkArea()
{
	//����DC���ж��Ҳ���ײ��Ƿ���ܴ��ڿհף�����������ϱ���ɫ
	if(m_uiViewStyle == STYLE_SMALL_PHOTO)
	{
		//������ͼ��ʽ���������հ�����
		//��������հ׿��
		int hBorder=m_iWorkAreaWidth -(( m_iPerPageLineCount>1?m_iPerLineItemCount:m_ficFileControl.m_iTotalCount)*m_iItemWithBorderWidth);
		if(hBorder>0)
		{
			Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());
			graph.FillRectangle(m_brBakBrush,m_iWorkAreaWidth-hBorder,0,hBorder,m_iWorkAreaHeight);
		}

		//�������հ׸߶�
		if(!(m_uiScrollBarType & SCROLL_BAR_V))
		{
			//ֻ�е������������϶���ʱ�Ŵ��ڿհ�����
			int vBorder=m_iWorkAreaHeight -(m_iTotalLineCount * m_iItemWithBorderHeight);
			if(vBorder>0)
			{
				Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());
				graph.FillRectangle(m_brBakBrush,0,m_iWorkAreaHeight-vBorder,m_iWorkAreaWidth-hBorder,vBorder);
			}
		}
	}
	else if(m_uiViewStyle == STYLE_REPORT)
	{
		//��ϸ��Ϣ��ʽʱ���޺���հ���Ҫ����
		//�������հ׸߶�
		if(!(m_uiScrollBarType & SCROLL_BAR_V))
		{
			//ֻ�е������������϶���ʱ�Ŵ��ڿհ�����
			int vBorder=m_iWorkAreaHeight -(m_iTotalLineCount * m_iItemWithBorderHeight);
			if(vBorder>0)
			{
				Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());
				graph.FillRectangle(m_brBakBrush,0,m_iWorkAreaHeight-vBorder,m_iWorkAreaWidth,vBorder);
			}
		}
	}
}
	

//=====================================================================
// �� �� ����SetMousePositionTypeAndValue
// ����������������������Ϣ�е�λ����Ϣ�����ֵ
// ���������CPoint pt:��Դ��ڵ�����
// ���������
// �������ڣ�2008.10.14
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::SetMousePositionInfo(CPoint pt)
{
	m_mpiMousePositionInfo.pt.x=pt.x+m_iWorkAreaLeft;
	m_mpiMousePositionInfo.pt.y=pt.y+m_iWorkAreaTop;
	
	if(m_uiViewStyle & STYLE_REPORT)
	{
		m_mpiMousePositionInfo.pt.y-=REPORT_HEAD_HEIGHT;
	}

	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//����������������ʱ
		if(m_iCurrentViewWidth-pt.x<=SCROLL_BAR_WIDTH_HEIGHT && pt.y<=m_sbsVScrollBarState.scrollTotalLength)
		{
			//�����λ������������Χ��ʱ����ʼ�������λ���ж������������ĸ�λ����
			if(pt.y<=SCROLL_BAR_WIDTH_HEIGHT)
			{
				//����������ϰ�ť�ĸ߶ȷ�Χ��
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_V_UP_BT;
				return ;
			}
			else if(pt.y>=m_sbsVScrollBarState.scrollMidPosition && pt.y<=m_sbsVScrollBarState.scrollMidPosition+m_sbsVScrollBarState.scrollMidButLength)
			{
				//������ڻ�����ķ�Χ��ʱ
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_V_MID_BT;
				m_mpiMousePositionInfo.value=m_iWorkAreaTop;
				return ;
			}
			else if(m_sbsVScrollBarState.scrollTotalLength-pt.y<=SCROLL_BAR_WIDTH_HEIGHT)
			{
				//����������°�ť�ĸ߶ȷ�Χ��
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_V_DOWN_BT;
				return ;
			}
			else
			{
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_V_DRAG_SPACE;
				return ;
			}
		}
	}
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//�����ں���������ʱ
		if(m_iCurrentViewHeight-pt.y<=SCROLL_BAR_WIDTH_HEIGHT)
		{
			//�����λ������������Χ��ʱ����ʼ�������λ���ж������������ĸ�λ����
			if(pt.x<=SCROLL_BAR_WIDTH_HEIGHT)
			{
				//����������ϰ�ť�ĸ߶ȷ�Χ��
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_H_LEFT_BT;
				return ;
			}
			else if(pt.x>=m_sbsHScrollBarState.scrollMidPosition && pt.x<=m_sbsHScrollBarState.scrollMidPosition+m_sbsHScrollBarState.scrollMidButLength)
			{
				//������ڻ�����ķ�Χ��ʱ
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_H_MID_BT;
				m_mpiMousePositionInfo.value=m_iWorkAreaLeft;
				return ;
			}
			else if(m_sbsHScrollBarState.scrollTotalLength-pt.x<=SCROLL_BAR_WIDTH_HEIGHT)
			{
				//����������°�ť�ĸ߶ȷ�Χ��
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_H_RIGHT_BT;
				return ;
			}
			else
			{
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_H_DRAG_SPACE;
				return ;
			}
		}
	}
	if(m_uiViewStyle & STYLE_REPORT)
	{
		//���б���ʽ������ϸ��Ϣ��ʽʱ�����ڱ�ͷ
		if(pt.y<REPORT_HEAD_HEIGHT)
		{
			//�����λ���ڱ�ͷ��Χ��ʱ
			VectorColumnInfo::iterator iter=m_vciColumnsInfo.begin();
			for(int i=0;i<m_iTotalColumnCount;i++)
			{
				if(pt.x>iter->startPosition+3 && pt.x<iter->endPosition-3)
				{
					//����겻��λ�ڱ�ͷ���Ӵ�ʱ
					m_mpiMousePositionInfo.positionType=POSITION_HEAD_ITEM;
					m_mpiMousePositionInfo.value=i;
					return ;
				}
				else if(pt.x>=iter->endPosition-3 && pt.x<=iter->endPosition+3)
				{
					//�����λ�ڱ�ͷ���Ӵ�ʱ,��ЧֵΪ���Ӵ�ǰһ����ͷ�ı��
					m_mpiMousePositionInfo.positionType=POSITION_HEAD_MID;
					m_mpiMousePositionInfo.value=i;
					return ;
				}

				iter++;
			}
		}
	}

	//ʣ��ֻ��������ʾ�����ڣ���ʱȡλ�õ�ITEM���
	int nItem=GetItemCodeByWindowPt(pt);
	if(nItem<0)
	{
		//�����С��0��˵�����λ�ò���ITEM
		m_mpiMousePositionInfo.positionType=POSITION_WORKAREA_NONE;
		return ;
	}
	else
	{
		m_mpiMousePositionInfo.positionType=POSITION_ITEM;
		m_mpiMousePositionInfo.value=nItem;
		return ;
	}
}
	

//=====================================================================
// �� �� ����MoveWorkArea
// �����������ƶ���������
// ���������int dx,int dy
// ���������
// �������ڣ�2008.10.16
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::MoveWorkArea(int dx,int dy)
{
	if(dx!=0)
	{
		m_iWorkAreaLeft+=dx;
		m_iWorkAreaRight+=dx;
	}
	if(dy!=0)
	{
		m_iWorkAreaTop+=dy;
		m_iWorkAreaBottom+=dy;
	}

	_CheckWorkArea();
	RedrawWorkArea(true);
}
	

//=====================================================================
// �� �� ����SetWorkArea
// �������������ÿ�������λ��
// ���������CPoint pt
// ���������
// �������ڣ�2008.10.16
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::SetWorkArea(CPoint pt)
{
	m_iWorkAreaLeft=pt.x;
	m_iWorkAreaTop=pt.y;
	m_iWorkAreaRight=m_iWorkAreaLeft+m_iWorkAreaWidth;
	m_iWorkAreaBottom=m_iWorkAreaTop+m_iWorkAreaHeight;

	_CheckWorkArea();
	RedrawWorkArea(true);
	Refresh();
}
	

//=====================================================================
// �� �� ����JumpLine
// ������������Խ��
// ���������int lineCount:�����������е��л�
// ���������
// �������ڣ�2008.10.16
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::JumpLine(int lineCount)
{
	if(lineCount>0)
	{
		lineCount=lineCount-1;
		lineCount=(lineCount*m_iItemWithBorderHeight)+(m_iItemWithBorderHeight-(m_iWorkAreaTop%m_iItemWithBorderHeight));
		MoveWorkArea(0,lineCount);
	}
	else if(lineCount<0)
	{
		lineCount=lineCount+1;
		lineCount=(lineCount*m_iItemWithBorderHeight)-(m_iWorkAreaTop%m_iItemWithBorderHeight?m_iWorkAreaTop%m_iItemWithBorderHeight:m_iItemWithBorderHeight);
		MoveWorkArea(0,lineCount);
	}
	
	Refresh();
}
	

//=====================================================================
// �� �� ����DealLbtDownMes
// ���������������������ʱ�����λ�õĲ���
// ���������UINT positionMes:λ����Ϣ
// ���������UINT���������Ĳ�����Ϣ�����ڷ�������궯����Ϣ������,UINT nFlags,CPoint point
// �������ڣ�2008.10.16
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
UINT SeeFileViewTable::DealLbtDownMes(UINT positionMes,UINT nFlags,CPoint point)
{
	if(positionMes==POSITION_ITEM)
	{
		//���������ITEM��ʱ
		if(!(nFlags & MK_CONTROL))
		{
			//��û�а���CONTROL��ʱ��������ITEMѡ��״̬ȡ��
 			m_ficFileControl.SetAllState(~LVIS_SELECTED,false,LVIS_SELECTED);
		}

		if(!(nFlags & MK_SHIFT))
		{
			//��δ����SHIFT��ʱ,ֻ���е����ļ���ѡ�񣬲��ҽ�ѡ����ļ�����Ϊ�����ļ�
			int nItem=m_mpiMousePositionInfo.value;
			FileInfoList * file=m_ficFileControl.GetFile(nItem);
			file->SetState(LVIS_SELECTED,true,0);
			m_ficFileControl.SetItemFouc(nItem,file);
		}
		else
		{
			//������SHIFT��ʱ��ѡ�񽹵��ļ������ļ����������ļ������ı佹���ļ�λ��
			int nItem=m_mpiMousePositionInfo.value;
			m_ficFileControl.SetFoucToItemState(nItem);
		}
	
		RedrawWorkArea(true);
		Refresh();

		RefreshPreview();

		//�������϶��ļ�����Ϣ,һ���������϶��ļ�����Ϣ���ٽ���OLE����,�Է�ֹ�ظ���OLE����
	}
	else if(positionMes==POSITION_WORKAREA_NONE)
	{
		//�����������ʾ�����ڵĿհײ���
		if(!(nFlags & (MK_CONTROL|MK_SHIFT)))
		{
			//��û�а���CONTROL��ʱ��������ITEMѡ��״̬ȡ��
 			m_ficFileControl.SetAllState(~LVIS_SELECTED,false,LVIS_SELECTED);

			RedrawWorkArea(true);
			Refresh();
		}

		RefreshPreview();

		return MOUSE_DRAG_SELECT;
	}
	else if(positionMes==POSITION_SCROLL_BAR_V_UP_BT)
	{
		//������������������������ϰ�ť
		JumpLine(-1);		//������һ��

		return MOUSE_SCROLL_V_UP;
	}
	else if(positionMes==POSITION_SCROLL_BAR_V_DOWN_BT)
	{
		//������������������������°�ť
		JumpLine(1);		//������һ��

		return MOUSE_SCROLL_V_DOWN;
	}
	else if(positionMes==POSITION_SCROLL_BAR_V_DRAG_SPACE)
	{
		//��������������������������հ�����
		if(point.y<m_sbsVScrollBarState.scrollMidPosition)
		{
			//�������λ���ڻ�����������ʱ
			JumpLine(-(m_iPerPageLineCount>1?m_iPerPageLineCount-1:1));		//������(һҳ������-1)����ÿҳһ��ʱ��������ת1��
		}
		else
		{
			//�������λ���ڻ�����������ʱ
			JumpLine(m_iPerPageLineCount>1?m_iPerPageLineCount-1:1);		//������(һҳ������-1)����ÿҳһ��ʱ��������ת1��
		}

		return MOUSE_SCROLL_V_AREA;
	}
	else if(positionMes==POSITION_SCROLL_BAR_V_MID_BT)
	{
		//��������������������Ļ�����

		return MOUSE_DRAG_SCROLL_V;
	}
	else if(positionMes==POSITION_SCROLL_BAR_H_LEFT_BT)
	{
		//��������ں���������������ť
		MoveWorkArea(-5,0);			//�����ƶ�
		Refresh();

		return MOUSE_SCROLL_H_LEFT;
	}
	else if(positionMes==POSITION_SCROLL_BAR_H_RIGHT_BT)
	{
		//��������ں��������������Ұ�ť
		MoveWorkArea(5,0);			//�����ƶ�
		Refresh();

		return MOUSE_SCROLL_H_RIGHT;
	}
	else if(positionMes==POSITION_SCROLL_BAR_H_DRAG_SPACE)
	{
		//��������ں��������������Ұ�ť
		if(point.x<m_sbsHScrollBarState.scrollMidPosition)
		{
			//�������λ���ڻ������ʱ,����
			MoveWorkArea(-m_iWorkAreaWidth,0);
		}
		else
		{
			//�������λ�ò��ڻ������ʱ,����
			MoveWorkArea(m_iWorkAreaWidth,0);
		}

		Refresh();

		return MOUSE_SCROLL_H_AREA;
	}
	else if(positionMes==POSITION_SCROLL_BAR_H_MID_BT)
	{
		//��������ں����������Ļ�����

		return MOUSE_DRAG_SCROLL_H;
	}

	return MOUSE_NONE;
}
	

//=====================================================================
// �� �� ����DragSelectedFiles
// ���������������б�ѡ���ļ�����OLE��ק���󣬿�ʼ��ק����
// ���������
// ���������
// �������ڣ�2008.10.17
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::DragSelectedFiles()
{
	int iLen=0;
	CStringList stringList;
	iLen=m_ficFileControl.GetSelectedFileList(&stringList,FILE_ALL);		//��ȡѡ����ļ�����·�����ϣ����ҵõ�����

	if(iLen>0)
	{
		//��ѡ����ļ�����0��ʱ�Ž�����ק����
		DROPEFFECT DropResult=DROPEFFECT_NONE;						//�������
		iLen=iLen+sizeof(DROPFILES) +1;  
		
		//����ȫ���ڴ�,׼���Ϸ�֮��,ע��˿��ڴ潫�ɽ����ϷŵĴ��ڸ�������   
		HGLOBAL hMemData = GlobalAlloc(GPTR,iLen);         
		ASSERT(hMemData != NULL);   

		//����������ڴ�,��������س�Ա   
		LPDROPFILES lpDropFiles = (LPDROPFILES)GlobalLock(hMemData);   
		ASSERT(lpDropFiles != NULL);   
		lpDropFiles->pFiles = sizeof(DROPFILES);
		#ifdef _UNICODE   
			lpDropFiles->fWide = TRUE;   
		#else   
			lpDropFiles->fWide = FALSE;   
		#endif           

		//��ѡ�е������ļ������θ��Ƶ�DROPFILES�ṹ�����(ȫ���ڴ���)   
		POSITION pItemPos = stringList.GetHeadPosition();
		char * pszStart = (char*)((LPBYTE)lpDropFiles + sizeof(DROPFILES));   
		while(pItemPos != NULL)     
		{   
			lstrcpy(pszStart, (LPCTSTR)stringList.GetNext(pItemPos));   
			pszStart = strchr(pszStart,'\0')   +   1;   //�´ε���ʼλ������һ�ν�β+1   
		} 

		m_DragSource.Empty(); 
		m_DragSource.CacheGlobalData(CF_HDROP,hMemData); 

		DropResult=m_DragSource.DoDragDrop(DROPEFFECT_COPY|DROPEFFECT_MOVE); 
		//�Դ����������жϣ������������Ҫ���ļ���������ɾ��
		switch(DropResult)   
		{   
			case DROPEFFECT_MOVE:
			case DROPEFFECT_COPY:   
				break;   
			default:   
				break;   
		}

		if(m_ficFileControl.CheckSelectedFile())
		{
			//ˢ����ʾ
			Invalidate();
		}

		//�����ڴ�
		GlobalUnlock(hMemData);
	}
}
	

//=====================================================================
// �� �� ����RedrawWorkArea
// �������������»�����ʾ�����DC����
// ���������bool reDraw:�Ƿ�ȫ�����»��ƣ��������þ�DC���бȽϺ󿽱��ܹ��������õĲ���
// ���������void
// �������ڣ�2008.10.17
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
void SeeFileViewTable::RedrawWorkArea(bool reDraw)
{
	if(!m_dcBakDC)
	{
		//���޽�������DCʱ��ֱ������
		return ;;
	}

	if(reDraw)
	{
		if(m_ficFileControl.m_iTotalCount>0)
		{
			//���ܵ�ITEM������Ϊ0ʱ�ſ�ʼ���ƣ����򲻽��л���
			_ReDrawItems(m_iShowItemHead,m_iShowItemEnd);

			if(m_uiViewStyle == STYLE_SMALL_PHOTO)
			{
				//������ͼ��ʽ���������հ�����
				if((m_iShowItemEnd+1) % m_iPerLineItemCount!=0)
				{
					//�����һ����ʾ��Item�޷�����ʾ��������
					CPoint pt=GetItemPosition(m_iShowItemEnd);
					pt.x+=m_iItemWithBorderWidth;
					pt.y=pt.y-m_iWorkAreaTop;
					Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());
					graph.FillRectangle(m_brBakBrush,pt.x,pt.y,(m_iPerLineItemCount*m_iItemWithBorderWidth)-pt.x,m_iItemWithBorderHeight);
				}
			}
		}
	}
	else
	{
		//����µ�������ɵ�����֮����
		int y=m_iWorkAreaTop-m_iOldWorkAreaTop;
		int x=m_iWorkAreaLeft-m_iOldWorkAreaLeft;

		if(y==0 && x==0)
		{
			//�����Ϊ0ʱ������Ҫ���»���
			return ;
		}

		//��DC������������ʱ
		int dy=0;
		if(m_uiViewStyle & STYLE_REPORT)
		{
			//��Ϊ��ϸ��Ϣ��ʽʱ��������ʾDC������DCʱ���߶���Ҫ��20
			dy=20;
		}

		//������Ҫ���»��Ƶ����·�Χ
		int top=m_iWorkAreaTop;
		int bottom=m_iOldWorkAreaTop;
		if(abs(y)<m_iWorkAreaHeight-m_iItemWithBorderHeight)
		{
			//���ƶ���ֵ�ȸ߶���һ�л�Сʱ����ʾ��ʱ��DC���������м�ֵ��
			if(y>0)
			{
				//����ֵ����0ʱ��ʾͼ�������ƶ�����Ҫ���»��Ƶķ�Χ��������
				top=m_iOldWorkAreaBottom;
				bottom=m_iWorkAreaBottom;

				//����ʾ����DC���ò��ֿ�������ʾDC�У��ٽ���ʾDC�п��ò��ֿ�������ʾ����DC
				m_dcMemeryDC->BitBlt(0,dy,m_iWorkAreaWidth,m_iWorkAreaHeight-y,m_dcWorkAreaDC,0,y,SRCCOPY);
				m_dcWorkAreaDC->BitBlt(0,0,m_iWorkAreaWidth,m_iWorkAreaHeight-y,m_dcMemeryDC,0,dy,SRCCOPY);
			}
			if(y<0)
			{
				//����ʾ����DC���ò��ֿ�������ʾDC�У��ٽ���ʾDC�п��ò��ֿ�������ʾ����DC
				m_dcMemeryDC->BitBlt(0,-y+dy,m_iWorkAreaWidth,m_iWorkAreaHeight+y,m_dcWorkAreaDC,0,0,SRCCOPY);
				m_dcWorkAreaDC->BitBlt(0,-y,m_iWorkAreaWidth,m_iWorkAreaHeight+y,m_dcMemeryDC,0,-y+dy,SRCCOPY);
			}
		}
		else
		{
			top=m_iWorkAreaTop;
			bottom=m_iWorkAreaBottom;
		}

		//������Ҫ���»��Ƶ����ҷ�Χ
		int left=m_iWorkAreaLeft;
		int right=m_iOldWorkAreaLeft;
		if(abs(x)<m_iWorkAreaWidth)
		{
			if(x>0)
			{
				//����ֵ����0ʱ����ʾ�����϶�
				left=m_iOldWorkAreaRight;
				right=m_iWorkAreaRight;

				//����ʾ����DC���ò��ֿ�������ʾDC�У��ٽ���ʾDC�п��ò��ֿ�������ʾ����DC
				m_dcMemeryDC->BitBlt(0,dy,m_iWorkAreaWidth-x,m_iWorkAreaHeight,m_dcWorkAreaDC,x,0,SRCCOPY);
				m_dcWorkAreaDC->BitBlt(0,0,m_iWorkAreaWidth-x,m_iWorkAreaHeight,m_dcMemeryDC,0,dy,SRCCOPY);
			}
			if(x<0)
			{
				//����ʾ����DC���ò��ֿ�������ʾDC�У��ٽ���ʾDC�п��ò��ֿ�������ʾ����DC
				m_dcMemeryDC->BitBlt(-x,dy,m_iWorkAreaWidth+x,m_iWorkAreaHeight,m_dcWorkAreaDC,0,0,SRCCOPY);
				m_dcWorkAreaDC->BitBlt(-x,0,m_iWorkAreaWidth+x,m_iWorkAreaHeight,m_dcMemeryDC,-x,dy,SRCCOPY);
			}
		}
		else
		{
			left=m_iWorkAreaLeft;
			right=m_iWorkAreaRight;
		}

		if(m_ficFileControl.m_iTotalCount>0)
		{
			if(y!=0)
			{
				//�������
				CRect rect(0,top-m_iWorkAreaTop,m_iWorkAreaWidth,bottom-m_iWorkAreaTop);
				//���»��������ڶ���
				_ReDrawRect(rect);
			}
			if(x!=0)
			{
				//�������,��Ҫ����ȫ���߶ȵ���Ϣ
				CRect rect(left-m_iWorkAreaLeft,0,right-m_iWorkAreaLeft,m_iWorkAreaHeight);
				//���»��������ڶ���
				_ReDrawRect(rect);
			}
		}

		return ;
	}

	m_iOldWorkAreaTop=m_iWorkAreaTop;								//��ǰ��ʾ���ֵĶ�������ǰY����-���m_iWorkAreaHeight
	m_iOldWorkAreaBottom=m_iWorkAreaBottom;							//��ǰ��ʾ���ֵĵײ�����ǰY����-���m_iWorkAreaHeight
	m_iOldWorkAreaLeft=m_iWorkAreaLeft;								//��ǰ��ʾ���ֵ���߽����ǰ����-���m_iWorkAreaWidth
	m_iOldWorkAreaRight=m_iWorkAreaRight;							//��ǰ��ʾ���ֵ��ұ߽����ǰ����-���m_iWorkAreaWidth
}
	

//=====================================================================
// �� �� ����GetItemRect
// ������������ȡITEM�ڵ�ǰ��ʾ���������
// ���������int nItem
// ���������CRect
// �������ڣ�2008.10.17
// �޸�����:  
// �� �ߣ�   alzq
// ����˵����
//=====================================================================
CRect SeeFileViewTable::GetItemRect(int nItem)
{
	CPoint pt;
	pt=GetItemPosition(nItem);
	pt.x-=m_iWorkAreaLeft;
	pt.y-=m_iWorkAreaTop;
	//����ITEM����ʾ���򶥵�����,���ITEM����ʾ����Χ
	CRect rect(
		pt.x
		,pt.y
		,pt.x+m_iItemWithBorderWidth==0?m_iWorkAreaWidth:m_iItemWithBorderWidth
		,pt.y+m_iItemWithBorderHeight);

	//������ʾ��Χ�Ĳ���,ȥ��
	if(rect.top<0){rect.top=0;}
	if(rect.left<0){rect.left=0;}
	if(rect.bottom>m_iWorkAreaHeight){rect.bottom=m_iWorkAreaHeight;}
	if(rect.right>m_iWorkAreaWidth){rect.right=m_iWorkAreaWidth;}

	if(m_uiViewStyle & STYLE_REPORT)
	{
		//��Ϊ��ϸ��Ϣ��ʽʱ�����ڱ�ͷ�߶�
		rect.top+=REPORT_HEAD_HEIGHT;
		rect.bottom+=REPORT_HEAD_HEIGHT;
	}

	return rect;
}
	

//=====================================================================
// �� �� ����OnBeginDragLvOrType
// ������������ʼ��ק�ȼ�������ʱ
// �����������
// �����������
// �������ڣ�2008.10.09
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
afx_msg LRESULT SeeFileViewTable::OnBeginDragLvOrType(WPARAM wParam,LPARAM lParam)
{
	m_iDragInfo=wParam;		//������ק�����õ����������ֵ

	return 0;
}
	

//=====================================================================
// �� �� ����OnEndDragLvOrType
// ����������������ק�ȼ�������ʱ
// �����������
// �����������
// �������ڣ�2008.10.09
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
afx_msg LRESULT SeeFileViewTable::OnEndDragLvOrType(WPARAM wParam,LPARAM lParam)
{
	CPoint point;
	GetCursorPos(&point);

	int nItem=GetItemCodeByMousePt(point);
	if(nItem<0)
	{
		//����ק���հ�����ʱ��������
		return 0;
	}

	FileInfoList * file=m_ficFileControl.GetFile(nItem);

	if(m_iDragInfo!=-1)
	{
		//�����洢��������Ϣ��Чʱ�Ž�������
		if(file->GetState(LVIS_SELECTED))
		{
			//����ק�����ļ���ѡ��ʱ���������б�ѡ���ļ�
			m_ficFileControl.SetSelectedLvOrType(m_iDragInfo,wParam);
		}
		else
		{
			//���ļ�δ��ѡ��ʱ�������ø��ļ�
			m_ficFileControl.SetItemLvOrType(nItem,m_iDragInfo,wParam);
		}
	}

	m_iDragInfo=-1;

	//��������Ϣ��ˢ����ʾ
	Invalidate();
	return 0;
}
	

//=====================================================================
// �� �� ����OnAlzqListView
// �����������鿴ͼƬ
// �����������
// �����������
// �������ڣ�2008.10.09
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::OnAlzqListView()
{
	// TODO: �ڴ���������������
	int nItem=m_ficFileControl.GetFirstSelectedCode();
	
	if(nItem>=0)
	{
		//��Ϊͼ���ļ�ʱ
		GetParent()->PostMessageA(MES_ALZQ_VIEW_PHOTO,nItem);
	}
}

//=====================================================================
// �� �� ����OnAlzqListCut
// ��������������
// �����������
// �����������
// �������ڣ�2008.10.09
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::OnAlzqListCut()
{
	// TODO: �ڴ���������������
	m_ficFileControl.DealSelectedFile(DEAL_FILE_CUT);
}

//=====================================================================
// �� �� ����OnAlzqListCopy
// ��������������
// �����������
// �����������
// �������ڣ�2008.10.09
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::OnAlzqListCopy()
{
	// TODO: �ڴ���������������
	m_ficFileControl.DealSelectedFile(DEAL_FILE_COPY);
}

//=====================================================================
// �� �� ����OnAlzqListCutFloder
// �����������ƶ���
// �����������
// �����������
// �������ڣ�2008.10.09
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::OnAlzqListCutFloder()
{
	// TODO: �ڴ���������������
	MoveOrCopyToDlg copyDlg;
	if (copyDlg.DoModal()==IDOK)
	{
		string newFolderPath;
		newFolderPath=copyDlg.m_targePath.GetBuffer(0);
		//�ж����һ���ַ��Ƿ���"\",���������
		if (newFolderPath.find_last_of("\\")!=newFolderPath.length()-1)
		{
			newFolderPath+="\\";
		}
		m_ficFileControl.DealSelectedFile(newFolderPath,DEAL_ASK,DEAL_FILE_CUT);
	}
}

//=====================================================================
// �� �� ����OnAlzqListCopyFloder
// �������������Ƶ�
// �����������
// �����������
// �������ڣ�2008.10.09
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::OnAlzqListCopyFloder()
{
	// TODO: �ڴ���������������
	MoveOrCopyToDlg copyDlg;
	if (copyDlg.DoModal()==IDOK)
	{
 		string newFolderPath;
		newFolderPath=copyDlg.m_targePath.GetBuffer(0);
		//�ж����һ���ַ��Ƿ���"\",���������
		if (newFolderPath.find_last_of("\\")!=newFolderPath.length()-1)
		{
			newFolderPath+="\\";
		}
		m_ficFileControl.DealSelectedFile( newFolderPath,DEAL_ASK,DEAL_FILE_COPY);
	}
}

//=====================================================================
// �� �� ����OnAlzqListRename
// ����������������
// �����������
// �����������
// �������ڣ�2008.10.09
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::OnAlzqListRename()
{
	// TODO: �ڴ���������������
	//��ȡѡ�еĵ�һ���ļ�
	int nSel=m_ficFileControl.GetFirstSelectedCode();
	//��ʾEdit
	showEdit(nSel);
}

//=====================================================================
// �� �� ����OnAlzqListAddcolection
// ������������ӵ��ղؼ�
// �����������
// �����������
// �������ڣ�2008.10.10
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void SeeFileViewTable::OnAlzqListAddcolection()
{
	if(!m_wndFavoriteBar)
	{
		return ;
	}

	// TODO: �ڴ���������������
	CStringList stringList;
	int len=m_ficFileControl.GetSelectedFileList(&stringList,FILE_FLODER|FILE_PHOTO);		//���������ַ�������ܳ���
	if(!len)
		return ;

	//CStringList����ʼλ��
	POSITION pItemPos = stringList.GetHeadPosition();
	while(pItemPos != NULL)     
	{   
		CString path=stringList.GetNext(pItemPos);
		m_wndFavoriteBar->InsertFovoriteItem(path.GetBuffer(0));
	}
}

void SeeFileViewTable::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	RefreshPreview();

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL SeeFileViewTable::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;//CListCtrl::OnEraseBkgnd(pDC);
}

void SeeFileViewTable::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//���洢����ʾDC�뵱ǰ��ʾDC������ʱ�����½����ڴ�DC��ͬʱ����
	if(!m_dcBakDC)
	{
		//������ػ���
		_BuildDC();
		// ��Ϊ��ͼ��Ϣ���� CListCtrl::OnPaint()
		RedrawWorkArea(true);
		Refresh();
	}
	else
	{
		Refresh();
	}
}

//=====================================================================
// �� �� ����OnSize
// ���������������ڴ�С���ʱ
// ���������UINT nType, int cx, int cy
// �����������
// �������ڣ�2008.10.10
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���������ڴ�С���ʱ����Ҫ�����µĹ�������
//			 ���ݵ�һ����ѡ����ȷ����ʾ����
//			 ��ʾ������ITEM��ŷ�Χ
//=====================================================================
void SeeFileViewTable::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(m_ficFileControl.m_bOrderByGroup)
	{
		//�����з�������ʱ�����㷽ʽ��ͬ����ʱԤ��λ��
	}
	else
	{
		//����������
		_ResizeWorkAreaWithoutGroup(cx,cy,true);
		//��հ�����
		FillOutofWorkArea();
		//�ػ�����DC
		RedrawWorkArea(true);
		//ˢ����ʾ
		Refresh();
	}
}

void SeeFileViewTable::OnMouseMove(UINT nFlags, CPoint point)
{
	MousePositionInfo oldInfo;
	oldInfo.pt=m_mpiMousePositionInfo.pt;
	oldInfo.positionType=m_mpiMousePositionInfo.positionType;
	oldInfo.value=m_mpiMousePositionInfo.value;
	//��ȡ��ǰλ�������Ϣ
	SetMousePositionInfo(point);

	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_maiMouseActionInfo.mouseCondition & MOUSE_DRAG_SCROLL_H)
	{
		//��������϶�����������ʱ���������λ��Y�����ж��Ƿ���Ч�϶�����������λ�û�ԭλ��
		int dy=point.y-(m_iCurrentViewHeight-(SCROLL_BAR_WIDTH_HEIGHT/2));
		if(abs(dy)<=SCROLL_DRAG_ENABLE_DISTANCE)
		{
			//���������Ч��Χ��ʱ,������ʾ����
			int x=point.x;
			x=(x-m_maiMouseActionInfo.dragStartPt.x)
				*(m_iWorkAreaTotalWidth-m_iWorkAreaWidth);
			x=x /(m_sbsHScrollBarState.scrollTotalLength-m_sbsHScrollBarState.scrollMidButLength-(2*SCROLL_BAR_WIDTH_HEIGHT));
			x=x+m_maiMouseActionInfo.mousePositionInfo.value;

			//������ʾ��Χ
			if(x<0)
			{
				x=0;
			}
			else if(x+m_iWorkAreaWidth>m_iWorkAreaTotalWidth)
			{
				x=m_iWorkAreaTotalWidth-m_iWorkAreaWidth;
			}

			if(x==m_iWorkAreaLeft)
			{
				//����Ҫ��ʾ�ķ�Χ�뵱ǰ��Χ��ͬʱ��ֱ����ʾ�ڴ�DC
				RefreshWorkArea();
			}
			else
			{
				//������ʾλ�ú����»���
				SetWorkArea(CPoint(x,m_iWorkAreaTop));
			}
		}
		else
		{
			if(m_maiMouseActionInfo.mousePositionInfo.value==m_iWorkAreaLeft)
			{
				//����Ҫ��ʾ�ķ�Χ�뵱ǰ��Χ��ͬʱ��ֱ����ʾ�ڴ�DC
				RefreshWorkArea();
			}
			else
			{
				//������ʾλ�ú����»���
				SetWorkArea(CPoint(m_maiMouseActionInfo.mousePositionInfo.value,m_iWorkAreaTop));
			}
		}
	}
	else if(m_maiMouseActionInfo.mouseCondition & MOUSE_DRAG_SCROLL_V)
	{
		//��������϶�����������ʱ���������λ��Y�����ж��Ƿ���Ч�϶�����������λ�û�ԭλ��
		int dx=point.x-(m_iCurrentViewWidth-(SCROLL_BAR_WIDTH_HEIGHT/2));
		if(abs(dx)<=SCROLL_DRAG_ENABLE_DISTANCE)
		{
			//���������Ч��Χ��ʱ,������ʾ����
			int y=point.y;
			y=(y-m_maiMouseActionInfo.dragStartPt.y)*(m_iWorkAreaTotalHeight-m_iWorkAreaHeight);
			y=y/(m_sbsVScrollBarState.scrollTotalLength-m_sbsVScrollBarState.scrollMidButLength-(2*SCROLL_BAR_WIDTH_HEIGHT));
			y=y+m_maiMouseActionInfo.mousePositionInfo.value;

			//������ʾ��Χ
			if(y<0)
			{
				y=0;
			}
			else if(y+m_iWorkAreaHeight>m_iWorkAreaTotalHeight)
			{
				y=m_iWorkAreaTotalHeight-m_iWorkAreaHeight;
			}

			if(y==m_iWorkAreaTop)
			{
				//����Ҫ��ʾ�ķ�Χ�뵱ǰ��Χ��ͬʱ��ֱ����ʾ�ڴ�DC
				RefreshWorkArea();
			}
			else
			{
				//������ʾλ�ú����»���
				SetWorkArea(CPoint(m_iWorkAreaLeft,y));
			}
		}
		else
		{
			if(m_maiMouseActionInfo.mousePositionInfo.value==m_iWorkAreaTop)
			{
				//����Ҫ��ʾ�ķ�Χ�뵱ǰ��Χ��ͬʱ��ֱ����ʾ�ڴ�DC
				RefreshWorkArea();
			}
			else
			{
				//������ʾλ�ú����»���
				SetWorkArea(CPoint(m_iWorkAreaLeft,m_maiMouseActionInfo.mousePositionInfo.value));
			}
		}
	}
	else if(m_maiMouseActionInfo.mouseCondition & MOUSE_LBT_DOWN && m_maiMouseActionInfo.mousePositionInfo.positionType==POSITION_ITEM && !(m_maiMouseActionInfo.mouseCondition & MOUSE_DRAG_FILE))
	{
		//������¼�Ϊ������£��Ұ��µ�λ����ITEMλ��ʱ���������λ���ж��Ƿ��ļ���ק
		CPoint pt(point.x,point.y);			//����������������ʾ����ľ�������
		if(abs(pt.x-m_maiMouseActionInfo.dragStartPt.x)+abs(pt.y-m_maiMouseActionInfo.dragStartPt.y)>20)
		{
			//����ǰ����Xλ����Yλ����ӣ�����20ʱ����Ϊ��ʱΪ�ļ���ק����
			DragSelectedFiles();
		}
	}
	else if(m_maiMouseActionInfo.mouseCondition & MOUSE_DRAG_SELECT)
	{
		//������������ѡ��ʱ

		//�������λ���ж��Ƿ��ƶ���ʾ����
		int dx=0;
		int dy=0;
		if(point.x<0)
		{
			//���������߽���ʱ,��ʾ���������ƶ�
			dx=point.x;
			m_mpiMousePositionInfo.pt.x=m_iWorkAreaLeft;
		}
		else if(point.x>m_iCurrentViewWidth)
		{
			dx=point.x-m_iCurrentViewWidth;
			m_mpiMousePositionInfo.pt.x=m_iWorkAreaRight;
		}

		if(point.y<0)
		{
			//��������ϱ߽�����ʱ,��ʾ���������ƶ�
			dy=point.y;
			m_mpiMousePositionInfo.pt.y=m_iWorkAreaTop;
		}
		else if(point.y>m_iCurrentViewHeight)
		{
			dy=point.y-m_iCurrentViewHeight;
			m_mpiMousePositionInfo.pt.y=m_iWorkAreaBottom;
		}

		if(dx!=0 || dy!=0)
		{
			//���������ʾ������ʱ,��Ҫ�ƶ���ʾ����,������ѡ����,�ƶ�����ʱ����ˢ����ʾ
			_MoveWorkArea(dx,dy);
			//������ǰ�����Ϣ���ھ�������
			m_mpiMousePositionInfo.pt.x+=dx;
			if(m_mpiMousePositionInfo.pt.x<0)
			{
				m_mpiMousePositionInfo.pt.x=0;
			}
			else if(m_mpiMousePositionInfo.pt.x>m_iWorkAreaTotalWidth)
			{
				m_mpiMousePositionInfo.pt.x=m_iWorkAreaTotalWidth;
			}

			m_mpiMousePositionInfo.pt.y+=dy;
			int maxHeight=m_iWorkAreaTotalHeight>m_iWorkAreaHeight?m_iWorkAreaTotalHeight:m_iWorkAreaHeight;
			if(m_mpiMousePositionInfo.pt.y<0)
			{
				m_mpiMousePositionInfo.pt.y=0;
			}
			else if(m_mpiMousePositionInfo.pt.y>maxHeight)
			{
				m_mpiMousePositionInfo.pt.y=maxHeight;
			}
		}

		//���õ�ǰѡ�񲿷ֵ�ITEM״̬,������ʾ���ֵ�ITEM���»��ƺ�ˢ����ʾ
		_DragSelect(m_maiMouseActionInfo.mousePositionInfo.pt,oldInfo.pt,m_mpiMousePositionInfo.pt);

		RedrawWorkArea(true);
		Refresh();
	}

	if   (!m_bMouseTracking)   
	{
		TRACKMOUSEEVENT   tme;   
		tme.cbSize   =   sizeof(TRACKMOUSEEVENT);   
		tme.dwFlags   =   TME_LEAVE;   
		tme.hwndTrack   =   m_hWnd;   
		tme.dwHoverTime   =   HOVER_DEFAULT;   
		m_bMouseTracking=::_TrackMouseEvent(&tme);
	}
	CWnd::OnMouseMove(nFlags, point);
}

void SeeFileViewTable::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	// TODO: �ڴ˴������Ϣ����������
	if(!m_bListGetFouc)
	{
		m_bListGetFouc=true;
	
		RedrawWorkArea(true);
		Refresh();
	}
}

void SeeFileViewTable::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������
	if(m_bListGetFouc)
	{
		m_bListGetFouc=false;
	
		RedrawWorkArea(true);
		Refresh();
	}
}

void SeeFileViewTable::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_maiMouseActionInfo.mouseCondition!=MOUSE_NONE)
	{
		//�����ڽ���������ʱ���������κβ���
	}
	else
	{
		//�����������������õ�ǰ��������Ϣ
		m_maiMouseActionInfo.mouseCondition|=DealLbtDownMes(m_mpiMousePositionInfo.positionType,nFlags,point);

		//���������������Ϣ
		m_maiMouseActionInfo.dragStartPt=point;
		m_maiMouseActionInfo.mousePositionInfo.pt=m_mpiMousePositionInfo.pt;
		m_maiMouseActionInfo.mousePositionInfo.positionType=m_mpiMousePositionInfo.positionType;
		m_maiMouseActionInfo.mousePositionInfo.value=m_mpiMousePositionInfo.value;
	}
	m_maiMouseActionInfo.mouseCondition|=MOUSE_LBT_DOWN;			//�����״̬������������״̬

	//��ȡ��궯������
	SetCapture();

	return ;//CWnd::OnLButtonDown(nFlags, point);
}

void SeeFileViewTable::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ȡ��궯������
	SetCapture();

	return ;//CWnd::OnRButtonDown(nFlags, point);
}

void SeeFileViewTable::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	RefreshPreview();
	
	CPoint pt;
	GetCursorPos(&pt);

	int nItem=GetItemCodeByMousePt(pt);

	if(nItem<0)
	{
		//���Ҽ����������ITEMʱ
	}
	else
	{
		FileInfoList * file=m_ficFileControl.GetFile(nItem);
		if(file->CheckFileType(FILE_PHOTO))
		{
			//���ļ���ͼ��ʱ
			m_cmMenuChild=m_cmRightButtonMenu.GetSubMenu(0);
		}
		else
		{
			//���ļ�����ͼ��ʱ
			m_cmMenuChild=m_cmRightButtonMenu.GetSubMenu(1);
		}

		m_cmMenuChild->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
	}

	CWnd::OnRButtonUp(nFlags, point);
}

void SeeFileViewTable::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CWnd::OnRButtonDblClk(nFlags, point);
}

void SeeFileViewTable::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//���������������Ϣ
	m_maiMouseActionInfo.dragStartPt=point;
	m_maiMouseActionInfo.mouseCondition &= ~MOUSE_LBT_DOWN;			//�ڲ���״̬��ʹ�û����

	//����������Ϊ�գ����ͷ�����ȡ����ʱ��������Ҽ��Ƿ���в�����������������Ϣ
	m_maiMouseActionInfo.mouseCondition=MOUSE_NONE;
	//�ͷ���궯������
	ReleaseCapture();

	m_maiMouseActionInfo.mousePositionInfo.positionType=m_mpiMousePositionInfo.positionType;
	m_maiMouseActionInfo.mousePositionInfo.value=m_mpiMousePositionInfo.value;

	Refresh();

	CWnd::OnLButtonUp(nFlags, point);
}

void SeeFileViewTable::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//�ͷ���궯������
	//ReleaseCapture();

	CWnd::OnNcLButtonUp(nHitTest, point);
}

BOOL SeeFileViewTable::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int i=-zDelta/120;
	JumpLine(i);

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

LRESULT SeeFileViewTable::OnNcHitTest(CPoint point)
{
	CRect  rect;  
	CPoint  pt;  
	GetWindowRect(rect);  
	pt.x=point.x-rect.left;  
	pt.y=point.y-rect.top;			//����������LIST��λ��
	 
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_maiMouseActionInfo.mouseCondition!=MOUSE_NONE)
	{
		//��������ڽ��в���ʱ
		if(m_maiMouseActionInfo.mousePositionInfo.positionType==m_mpiMousePositionInfo.positionType)
		{
			//����꿪ʼ������λ���뵱ǰ����λ��������ͬʱ
			if(m_maiMouseActionInfo.mouseCondition & (MOUSE_SCROLL_H_AREA|MOUSE_SCROLL_H_LEFT|MOUSE_SCROLL_H_RIGHT|MOUSE_SCROLL_V_AREA|MOUSE_SCROLL_V_DOWN|MOUSE_SCROLL_V_UP))
			{
				//�����ʱ����ĳЩ�¼�ʱ������ʽ������������ʱ����ʽ��ͬ
				DealLbtDownMes(m_mpiMousePositionInfo.positionType,0,pt);
			}
		}
	}

	//�������λ����Ϣ�ԱȽ��д���

	return CWnd::OnNcHitTest(point);
}

LRESULT SeeFileViewTable::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
	//����뿪����ʱ���еĲ���

	m_bMouseTracking = FALSE;
	return TRUE;
}

void SeeFileViewTable::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CWnd::OnActivate(nState, pWndOther, bMinimized);

	// TODO: �ڴ˴������Ϣ����������
}
	

//=====================================================================
// �� �� ����OnRefreshAll
// �������������ݸ����ڴ�洢DC,ˢ����ʾ
// �����������
// �����������
// �������ڣ�2008.10.20
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
afx_msg LRESULT SeeFileViewTable::OnRefreshAll(WPARAM wParam,LPARAM lParam)
{
	Refresh();
	
	return TRUE;
}
	

//=====================================================================
// �� �� ����OnRefreshItem
// ���������������ڴ�洢DCˢ�µ�һ������ָ����ITEM
// �����������
// �����������
// �������ڣ�2008.10.20
// �޸�����:  
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
afx_msg LRESULT SeeFileViewTable::OnRefreshItem(WPARAM wParam,LPARAM lParam)
{
	ReDrawItem(wParam);

	return TRUE;
}

void SeeFileViewTable::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent & (MOUSE_DRAG_SELECT|MOUSE_DRAG_FILE))
	{
		//������ק�ļ���������ѡ���ļ�ʱ,�������λ���ƶ�����
		CPoint pt;
		GetCursorPos(&pt);
		CRect rect;
		GetWindowRect(&rect);
		if(!rect.PtInRect(pt))
		{
			//����겻�ڴ�����ʱ
			OnNcHitTest(pt);
		}
	}

	CWnd::OnTimer(nIDEvent);
}