#pragma once

#include "Resource.h"
#include "FileInfoControl.h"
#include "shellapi.h"
#include "ReNameEdit.h"

//=====================================================================
// �� �� ����LoadImageFunc
// ��������������Image������߳�����
// ���������LPVOID lpParameter����SeeFileViewTableָ��
// ���������DWORD WINAPI
// �������ڣ�08.09.16
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
DWORD WINAPI LoadImageFunc (LPVOID lpParameter);
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
DWORD WINAPI LoadBaseInfoFunc (LPVOID lpParameter);

//�洢�����������ɫ����
struct ScrollBarcColorSet
{
	COLORREF normalBak;
	COLORREF normalBorder;
	COLORREF mouseOnBak;
	COLORREF mouseOnBorder;
	COLORREF mouseDownBak;
	COLORREF mouseDownBorder;
};

//�ļ���ʾ����Ϣ�洢�ṹ
struct ScrollBarState
{
	UINT upButState;				//���ϰ�ť��״̬
	UINT downButState;				//���°�ť��״̬
	UINT midButState;				//�м��϶������״̬
	int scrollTotalLength;			//�ܵ��϶�������
	int scrollMidButLength;			//�м仮��ĳ���
	int scrollDragLength;			//�����϶��ĳ���
	int scrollMidPosition;			//����ܳ��ȣ�����������λ������
};

//ITEM�ķ�Χ
struct ItemRange
{
	int head;
	int end;
};

//��ȡ�ļ���Ϣʱ�Ĵ�������ṹ
struct InfoToGetFileInfo
{
	int code;
};

//��ϸ��Ϣ��ʽʱ��ÿ�е������Ϣ�洢����
struct ColumnInfo
{
	CString columnName;					//������
	int width;							//�п��
	InfoToGetFileInfo infoType;			//��ȡ����ʾ���ݵ���ر���
	UINT orderedColumn;					//�Ƿ�������
	UINT headState;						//��ͷ��״̬
	UINT contentState;					//����չʾ��ʽ�����뷽ʽHEAD_ALI��
	int startPosition;					//��ʼ��λ�ã����أ�
	int endPosition;					//����λ��
};

//�洢���λ����Ϣ
struct MousePositionInfo
{
	CPoint pt;							//����λ��(���������)�����������ʾ����ʱ��Ч
	UINT positionType;					//�궨�������(POSITION_)
	UINT value;							//��λ�������Ϣ����������λ�õ�����ţ�����ITEM����Ϣ
};

//�洢���λ���Լ������������Ϣ
struct MouseActionInfo
{
	MousePositionInfo mousePositionInfo;//���λ����Ϣ
	UINT mouseCondition;				//���״̬��Ϣ���궨�壨MOUSE_��
	CPoint dragStartPt;					//��ʼ��״̬ʱ���������-��������(��������)
};

typedef	vector<ColumnInfo>	VectorColumnInfo;

class SeeFileViewTable :
	public CWnd
{
public:
	SeeFileViewTable(void);
	~SeeFileViewTable(void);

// Attributes //����, Ʒ��, ����, ����, ���
public:
	FileInfoControl m_ficFileControl;					//�ļ�������ƶ��󣬿��ƶ��ļ��Ļ�������

	bool m_bSelectedFileEnable;							//�Ƿ���Ҫ�����ļ�
	bool m_bDealMouseAction;							//�ж��Ƿ��������������Ӧ

	UINT m_uiViewStyle;									//ListCtrl�鿴����ʽֵ
	int m_iDragInfo;									//����ק���������͵�LIST��ʱ�����ݱ������Եȼ������ͽ�������

	string m_sOpenFloderPath;							//�򿪵��ļ���·

	CImageList * m_cilIconList;							//
	CImageList * m_cilLevelsIcon;						//�����ĵȼ�ͼ���б�
	CImageList * m_cilScrollBarUp;						//�϶���������
	CImageList * m_cilScrollBarDown;					//�϶���������
	CImageList * m_cilScrollBarLeft;					//�϶���������
	CImageList * m_cilScrollBarRight;					//�϶���������

	CMenu m_cmRightButtonMenu;							//�Ҽ��˵����б�
	CMenu * m_cmMenuChild;								//��ȡ����ϸ�Ҽ��˵�ָ��

	PreviewBar * m_wndPreviewBar;							//�ļ�Ԥ������ָ��
	FavoriteBar * m_wndFavoriteBar;							//�ղؼд���ָ��

public:
	SolidBrush * m_brUnselectedBrush;						//δѡ���ITEM����ˢ
	SolidBrush * m_brSelectedBrush;							//��ѡ���ITEM����ˢ
	SolidBrush * m_brSelectedUnfoucBrush;					//��ѡ���ITEM�����޽��㱳��ˢ
	SolidBrush * m_brSelectBrush;							//����ѡ��ʱ�ĸ��ǲ�����ɫ
	SolidBrush * m_brScrollBarBakBrush;						//�������ı���ˢ
	SolidBrush * m_brScrollBarMidBakBrush;					//�����������������ı���ˢ
	SolidBrush * m_brScrollBarMidMouseOnBrush;				//�����ͣ����µ��������鱳��ˢ
	SolidBrush * m_brScrollBarMidDragBrush;					//��������µ��������鱳��ˢ
	SolidBrush * m_brBakBrush;								//�ܵı���ˢ
	Pen * m_penFoucItem;									//���н����ITEM���
	Pen * m_penSelectedItem;								//��ѡ���ITEM���
	Pen * m_penItemBorder;									//Item��Եˢ
	Pen * m_penScrollBarMidBakBorder;						//�����������������ı�Եˢ
	Pen * m_penScrollBarMidMouseOnBorder;					//�����ͣ����µ����������Եˢ
	Pen * m_penScrollBarMidDragBorder;						//��������µ����������Եˢ
	SolidBrush * m_brFontBrush;								//����ˢ

	HANDLE m_hLoadImage;								//����ͼ����߳�ָ�룬���벢���ţ�������DC
	HANDLE m_hLoadBaseInfo;								//�����ļ�������Ϣ

	Gdiplus::Image * m_imgDefaultDisk;					//Ĭ�ϴ���ͼ��
	Gdiplus::Image * m_imgDefaultFloder;				//Ĭ���ļ���ͼ��
	Gdiplus::Image * m_imgDefaultPic;					//ITEMĬ��ͼ��
	Gdiplus::Image * m_imgShadowRight;					//��Ӱͼ���Ҳ�
	Gdiplus::Image * m_imgShadowDown;					//��Ӱͼ������
	Gdiplus::Image * m_imgShadowRightDown;				//��Ӱͼ�����

	FontFamily * m_ffFontFamily;						//�����ļ�������
	StringFormat * m_sfStringFormatLeft;				//�������ֵĸ�ʽ
	StringFormat * m_sfStringFormatRight;				//�������ֵĸ�ʽ
	StringFormat * m_sfStringFormatCenter;				//�������ֵĸ�ʽ
	Gdiplus::Font * m_fntFontBlod;						//�������ֵ���ʽ�Ӵ�
	Gdiplus::Font * m_fntFontNormal;					//�������ֵ���ʽ���Ӵ�

	COleDataSource m_DragSource;						//ִ����ק����ʱ��OLE����

	/**
	*	----�ػ沿�ֱ���----
	*/
	CBitmap * m_cbBakMemeryBmp;							//��������ͼ��Ĵ洢����
	CBitmap * m_cbWorkAreaBmp;							//������ʾ�����ͼ��洢����
	CBitmap * m_cbHeaderBmp;							//��ͷ��ͼ��洢����
	CBitmap * m_cbScrollVBmp;							//��ͷ��ͼ��洢����
	CBitmap * m_cbScrollHBmp;							//��ͷ��ͼ��洢����
	CDC * m_dcMemeryDC;									//�������Ƶ��ڴ�DC
	CDC * m_dcWorkAreaDC;								//��ʾ���򲿷ֵ��ڴ�DC
	CDC * m_dcHeaderDC;									//��ͷ���ֵ��ڴ�DC
	CDC * m_dcScrollVDC;								//������������ֵ��ڴ�DC
	CDC * m_dcScrollHDC;								//������������ֵ��ڴ�DC
	CDC * m_dcBakDC;									//�������Ƶ�DC

	bool m_bListGetFouc;								//List�Ƿ��ȡ������
	BOOL m_bMouseTracking;								//�Ƿ���������뿪����Ϣ

	int m_iCurrentViewWidth;							//��ǰ��ʾ���ֵĿ��
	int m_iCurrentViewHeight;							//��ǰ��ʾ���ֵĸ߶�
	int m_iCurrentStartNItem;							//��ǰ��ʾ������ʾ�ĵ�һ��ITEM���
	int m_iCurrentEndNItem;								//��ǰ��ʾ������ʾ�����һ��ITEM���
	int m_iWorkAreaTop;									//��ǰ��ʾ���ֵĶ���Y����-���m_iWorkAreaHeight
	int m_iWorkAreaBottom;								//��ǰ��ʾ���ֵĵײ�Y����-���m_iWorkAreaHeight
	int m_iOldWorkAreaTop;								//��ǰ��ʾ���ֵĶ�������ǰY����-���m_iWorkAreaHeight
	int m_iOldWorkAreaBottom;							//��ǰ��ʾ���ֵĵײ�����ǰY����-���m_iWorkAreaHeight
	int m_iWorkAreaLeft;								//��ǰ��ʾ���ֵ���߽�����-���m_iWorkAreaWidth
	int m_iWorkAreaRight;								//��ǰ��ʾ���ֵ��ұ߽�����-���m_iWorkAreaWidth
	int m_iOldWorkAreaLeft;								//��ǰ��ʾ���ֵ���߽����ǰ����-���m_iWorkAreaWidth
	int m_iOldWorkAreaRight;							//��ǰ��ʾ���ֵ��ұ߽����ǰ����-���m_iWorkAreaWidth
	int m_iWorkAreaWidth;								//item��ʾ������
	int m_iWorkAreaHeight;								//item��ʾ����߶�
	int m_iWorkAreaTotalHeight;							//item��ʾ�����ܸ߶�
	int m_iWorkAreaTotalWidth;							//item��ʾ�����ܿ��
	int m_iItemWidth;									//ÿ��ITEM�Ŀ��
	int m_iItemHeight;									//ÿ��ITEM�ĸ߶�
	int m_iItemWithBorderWidth;							//ÿ��ITEM�Ŀ�ȴ��հ�����
	int m_iItemWithBorderHeight;						//ÿ��ITEM�ĸ߶ȴ��հ�����
	int m_iPerLineItemCount;							//��ǰ��������ÿ�д��ڶ��ٸ�ITEM
	int m_iPerPageLineCount;							//��ǰ���������ܹ���ʾ����
	int m_iTotalLineCount;								//�ܹ���Ҫ��ʾ������
	int m_iShowItemHead;								//��ʾ��ITEM��Χ��ʼ
	int m_iShowItemEnd;									//��ʾ��ITEM��Χ��β
	int m_iTotalColumnCount;							//��������ͳ��

	UINT m_uiScrollBarType;								//�϶�������ʽ�������

	ScrollBarState m_sbsHScrollBarState;				//�����϶�����״̬
	ScrollBarState m_sbsVScrollBarState;				//�����϶�����״̬
	VectorColumnInfo m_vciColumnsInfo;					//��ϸ��Ϣ��ʽʱ��ÿ����Ϣ�洢����
	MouseActionInfo m_maiMouseActionInfo;				//��������Ϣ
	MousePositionInfo m_mpiMousePositionInfo;			//���λ����Ϣ
	ScrollBarcColorSet m_sbcsScrollBarColorSet;			//��������ɫ����
	/**
	*	----�ػ沿�ֽ���----
	*/

	// ������ʱ�ı༭��
	ReNameEdit m_wndEdit;
	bool m_bCreateEdit;			//�Ƿ񴴽��������ı༭����
	//���ѡ�е��ļ�
	int m_nSelect;

// Operations //��ת, ����, ʵʩ, ����, ҵ��, ����, ����, �����ж�
public:
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
	void InitLoadImageThread (bool killThread);
	//=====================================================================
	// �� �� ����InitLoadBaseInfoThread
	// ������������ʼ�������ļ�������Ϣ���߳�
	// ���������bool killThread:���߳�����״̬ʱ�Ƿ�ɾ���߳�
	// ���������void
	// �������ڣ�08.09.16
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	void InitLoadBaseInfoThread (bool killThread);
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
	void OpenFloder(CString floderPath);
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
	int GetItemCodeByMousePt(CPoint pt);
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
	int GetItemCodeByWindowPt(CPoint pt);
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
	void RefreshPreview(void);

	//=====================================================================
	// �� �� ����showEdit
	// ������������ʾ�������༭��
	// ����������û�ѡ�е��ļ�����ֵ
	// �����������
	// �������ڣ�2008.10.7
	// �޸�����: 
	// �� �ߣ�   ���Ի�
	// ����˵���� 
	//=====================================================================
	void showEdit(int nItem);
	//=====================================================================
	// �� �� ����DisposeEdit
	// ������������ʧȥ����֮������û���������ļ����ж��Ƿ�����ļ������������
	// �����������
	// �����������
	// �������ڣ�2008.10.7
	// �޸�����:  
	// �� �ߣ�   ���Ի�
	// ����˵���� 
	//=====================================================================
	void DisposeEdit(void);
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
	void SetListStyle(UINT style);
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
	void SetSmallPhotoSize();
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
	void SetSmallPhotoSize(int width,int height);
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
	void SetReportItemSize();
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
	void SetWorkAreaToItem(int nItem);
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
	void SetWorkAreaToItemWithoutGroup(int nItem);
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
	ItemRange SetShowItemRange(int top,int bottom);
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
	CPoint GetItemPosition(int nItem);
	//=====================================================================
	// �� �� ����OpenFloderList
	// �������������ļ���
	// ���������CString filePath
	// ���������
	// �������ڣ�2008.10.12
	// �޸�����:  
	// �� �ߣ�   alzq
	// ����˵����
	//=====================================================================
	void OpenFloderList(CString filePath);
	//=====================================================================
	// �� �� ����Refresh
	// ����������ˢ����Ļ
	// ���������
	// ���������
	// �������ڣ�2008.10.17
	// �޸�����:  
	// �� �ߣ�   alzq
	// ����˵����
	//=====================================================================
	void Refresh();
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
	void Refresh(CRect rect);
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
	void RefreshWorkArea();
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
	void ReDrawItem(int nItem);
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
	void ReDrawItems(int head,int end);
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
	void DrawScrollBarBT();
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
	void InitScrollBar();
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
	void DrawScrollBarMidBT();
	//=====================================================================
	// �� �� ����DrawReportHeader
	// ����������������ϸ��Ϣ��ʽ�ı�ͷ
	// ���������int nLine��-1Ϊȫ��������Ϊָ����
	// ���������
	// �������ڣ�2008.10.15
	// �޸�����:  
	// �� �ߣ�   alzq
	// ����˵����
	//=====================================================================
	void DrawReportHeader(int nLine);
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
	void ReSetScrollBarInfo();
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
	void InitColumnInfo();
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
	void FillOutofWorkArea();
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
	void SetMousePositionInfo(CPoint pt);
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
	void MoveWorkArea(int dx,int dy);
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
	void SetWorkArea(CPoint pt);
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
	void JumpLine(int lineCount);
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
	UINT DealLbtDownMes(UINT positionMes,UINT nFlags,CPoint point);
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
	void DragSelectedFiles();
	//=====================================================================
	// �� �� ����RedrawWorkArea
	// �������������»�����ʾ�����DC����
	// ���������bool reDraw
	// ���������void
	// �������ڣ�2008.10.17
	// �޸�����:  
	// �� �ߣ�   alzq
	// ����˵����
	//=====================================================================
	void RedrawWorkArea(bool reDraw);
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
	CRect GetItemRect(int nItem);

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
	afx_msg LRESULT OnBeginDragLvOrType(WPARAM wParam,LPARAM lParam);
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
	afx_msg LRESULT OnEndDragLvOrType(WPARAM wParam,LPARAM lParam);
	//=====================================================================
	// �� �� ����OnMouseLeave
	// ��������������뿪���ڴ�������
	// �����������
	// �����������
	// �������ڣ�2008.10.15
	// �޸�����:  
	// �� �ߣ�   alzq
	// ����˵���� 
	//=====================================================================
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
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
	afx_msg LRESULT OnRefreshAll(WPARAM wParam,LPARAM lParam);
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
	afx_msg LRESULT OnRefreshItem(WPARAM wParam,LPARAM lParam);

protected:
	//=====================================================================
	// �� �� ����_ResizeWorkAreaWithoutGroup
	// ����������������ͼģʽ�£�����������ʾ�����С
	// ���������int width,int height,bool setToSelected
	// �����������
	// �������ڣ�2008.10.11
	// �޸�����:  
	// �� �ߣ�   alzq
	// ����˵���� 
	//=====================================================================
	void _ResizeWorkAreaWithoutGroup(int width,int height,bool setToSelected);
	//=====================================================================
	// �� �� ����_ResizeWorkAreaWithoutGroup
	// ����������������ͼģʽ�£�����������ʾ�����С
	// ���������bool setToSelected
	// �����������
	// �������ڣ�2008.10.11
	// �޸�����:  
	// �� �ߣ�   alzq
	// ����˵���� 
	//=====================================================================
	void _ResizeWorkAreaWithoutGroup(bool setToSelected);
	//=====================================================================
	// �� �� ����_ResizeWorkAreaWithoutGroupSmallPhoto
	// ����������SMALLPHOTO��ʽ�µ�����������ʾ�����С
	// ���������int width,int height,bool setToSelected
	// ���������
	// �������ڣ�2008.10.13
	// �޸�����:  
	// �� �ߣ�   alzq
	// ����˵����
	//=====================================================================
	void _ResizeWorkAreaWithoutGroupSmallPhoto(int width,int height,bool setToSelected);
	//=====================================================================
	// �� �� ����_ResizeWorkAreaWithoutGroupReport
	// ����������REPORT��ʽ�µ�����������ʾ�����С
	// ���������int width,int height,bool setToSelected
	// ���������
	// �������ڣ�2008.10.13
	// �޸�����:  
	// �� �ߣ�   alzq
	// ����˵����
	//=====================================================================
	void _ResizeWorkAreaWithoutGroupReport(int width,int height,bool setToSelected);
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
	void _CheckWorkArea();
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
	void _ReDrawItems(int head,int end);
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
	void _ReDrawItems(int head,int end,int leftLine,int rightLine);
	//=====================================================================
	// �� �� ����_ReDrawRect
	// �������������»��������ڵ���
	// ���������CRect rect
	// �����������
	// �������ڣ�2008.10.15
	// �޸�����:  
	// �� �ߣ�   alzq
	// ����˵����
	//=====================================================================
	void _ReDrawRect(CRect rect);
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
	void _PrintItem(int nItem,int leftLine,int rightLine);
	//=====================================================================
	// �� �� ����_PrintItemSmallPhoto
	// ����������Itemͼ�������ƺ���
	// ���������CPoint pt:��ʾITEM������
	//			 FileInfoList * fileInfo:ITEMָ����ļ�
	// ���������void
	// �������ڣ�08.10.13
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵��������CDC����ػ��Ʋ����ṹ�壬�Ƿ񴰿�Ϊ����
	//=====================================================================
	void _PrintItemSmallPhoto(CPoint pt,FileInfoList * fileInfo);
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
	void _PrintItemReport(CPoint pt,FileInfoList * fileInfo,int leftLine,int rightLine);
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
	void _PrintSmallPhoto(Gdiplus::Graphics * graph,CPoint pt,FileInfoList * fileInfo);
	//=====================================================================
	// �� �� ����_DeleteDC
	// ����������ɾ��CDC����
	// ���������CDC * dc
	// ���������void
	// �������ڣ�08.10.17
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	void _DeleteDC(CDC * dc);
	//=====================================================================
	// �� �� ����_DeleteBmp
	// ����������ɾ��CBitmap����
	// ���������CBitmap * bmp
	// ���������void
	// �������ڣ�08.10.17
	// �޸����ڣ�
	// �� �ߣ�alzq
	// ����˵����
	//=====================================================================
	void _DeleteBmp(CBitmap * bmp);
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
	void _CreateDC(CDC * dc,CBitmap * bmp,CDC * pDC,int width,int height);
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
	void _BuildDC();
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
	void _MoveWorkArea(int dx,int dy);
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
	void _DragSelect(CPoint startPt,CPoint oldPt,CPoint nowPt);

// Overridables //�����ص�

// Implementation //ʵ��
public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
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
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAlzqListView();
	afx_msg void OnAlzqListCut();
	afx_msg void OnAlzqListCopy();
	afx_msg void OnAlzqListCutFloder();
	afx_msg void OnAlzqListCopyFloder();
	afx_msg void OnAlzqListRename();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnAlzqListAddcolection();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
