/**********************************************************************
//
//
//        ##########                          ######  #########   # ######    #
//      #############                      ########### ######### #########  ###
//     ######## # ###  ##                 ############# ##    ## #####  # ####
//     ####  ##    ## ###                 ###     ### # #      #####   #####
//          #     ###  #            #     ##       ##  ##      ##     ###
//         ## ###### ##      ##  ####    ####          #       #     ##
//       #########  ###  ## ### #######   ######      ##      ##    ###
//      ######      ##  ######  ##  ##       ####     #      ##     ####
//     #######     ##   ###### ##  ###          ##   ##     ###    ######
//     #########   ##  ###### ## ######         ### ##    ###      #  #####
//    ##    ###### ####### ### #### ##  ## #######  ########      ##    ####
//    ##      #### ###  #  ### ### ##  ##########   ######       ##      ####
//   ##         ##                ##   #########    ####         #         ##
//               #              ###
//                              ##
//                             ###
//                             ##
//
//
//							RingSDK��ʾ����
//���ߣ��ٷ�
//
//e-mail:ringphone@sina.com
//
//ԭ�ļ���global.h
//
//��ʾ��QQ2009�Ľ���
//
**********************************************************************/
#ifndef _INC_QQ2009_GLOBAL_H
#define _INC_QQ2009_GLOBAL_H
#include "ringmain.h"
#include "ringdib.h"
#include "resource.h"

enum
{
	NCB_MINNORMAL = 0,
	NCB_MAXNORMAL,
	NCB_CLOSENORMAL,
	NCB_RESTORENORMAL,
	NCB_MINHOVER,
	NCB_MAXHOVER,
	NCB_CLOSEHOVER,
	NCB_RESTOREHOVER,
	NCB_MINDOWN,
	NCB_MAXDOWN,
	NCB_CLOSEDOWN,
	NCB_RESTOREDOWN,
	
	NCB_ENTIREWIDTH = 93,			//����ϵͳ��ť���
	NCB_MINWIDTH = 25,				//��С����ť���
	NCB_MAXWIDTH = 25,				//��󻯰�ť���
	NCB_CLOSEWIDTH = 43,				//�رհ�ť���
	NCB_HEIGHT = 17,					//ϵͳ��ť�߶�
	NCB_CORNERSIZE = 7,				//����԰�ǰ뾶
	NCB_TITLEHEIGHT = 95,			//���ڱ���������߶�
	NCB_BOTTOMHEIGHT = 53,			//���ڵ�������߶�
	NCB_QQBTNWIDTH = 45,				//���ڵ���QQ��ť������

	NCB_SIGNSPACE = 48,				//����ǩ���ര�����ұ߳ߴ�
	NCB_SPACE = 5,						//ϵͳ��ť�ര�����ұ߳ߴ�
	NCB_TOPPOS = 0,					//ϵͳ��ť�ര���ϱ߳ߴ�
	NCB_HOVERBTNHEIGHT = 22,		//�û����߰�ť����ͼ���߶�
	NCB_HOVERBORDERWIDTH = 2,		//�û�����ť�߿���
	NCB_USERBTNPOSX = 65,			//�û�����ť��Դ������ϽǺ�����
	NCB_USERBTNPOSY = 32,			//�û�����ť��Դ������Ͻ�������
	NCB_USERBANNER_X = 54,			//�û���������ǩ��������
	NCB_USERBANNER_Y = 23,			//�û���������ǩ��������

	NCB_TOOLTOPBTNCOUNT = 6,		//�û�ͷ���¹�������ť����
	NCB_TOOLTOP_X = 8,				//�û�ͷ���¹�����������
	NCB_TOOLTOP_Y = 72,				//�û�ͷ���¹�����������

	WND_MINWIDTH = 235,				//QQ���ڿɵ�����С���
	WND_MINHEIGHT = 329,				//QQ���ڿɵ�����С�߶�
	WND_BORDER = 2,					//���ڱ߿�ߴ�

	//HitTest��չ����ֵ
	HT_USERBUTTON = 3330,			//���λ���û����԰�ť����
	HT_USERSIGN,						//����ǩ����ť
	HT_TOOLTOPFIRST,					//�û�ͷ���·���������һ����ť
	HT_TOOLTOPEND = HT_TOOLTOPFIRST + 5,		//�û�ͷ���·����������һ����ť
	HT_TOOLTR,							//������Ϣ���ӡ���ť
	HT_UIOPTION,						//�������ð�ť
	//����ǩ���༭��ID
	IDC_USERSIGN = 12301,
	IDC_MAINTAB,						//�ͻ���TAB�ؼ�ID
	IDC_SEARCH,							//������ID
	IDC_QQFRIEND,						//�����б�
	IDC_QQGROUP,						//Ⱥ�б�
	IDC_QQRECENT,						//�����ϵ���б�
	IDC_MAIL,							//�����б��ϵ����䰴ťID

	USERIMG_SIZE = 24					//�û�ͷ��ߴ�
};

#define QQLIST_EXPANDED			0x0000CDCD
#define QQLIST_ISTITLE			0xCDCD0000

extern TCHAR gszSearchTip[];

//�Ի�ؼ�
class RingTrackBarEx:public RingTrackBar
{
public:
	RingTrackBarEx():m_hbmLine(NULL),m_hbmThumb(NULL){m_sizeLine.cx=m_sizeLine.cy=m_sizeThumb.cx=m_sizeThumb.cy=0;}
	~RingTrackBarEx();
	
	void SetSkin(UINT idLine,UINT idThumb);
	
protected:
	LRESULT RingdowProc(HWND,RINGPARAMS);
	
private:
	HBITMAP m_hbmLine,m_hbmThumb;
	SIZE m_sizeLine,m_sizeThumb;
};

class RingEditEx:public RingEdit
{
public:
	RingEditEx():m_bShowTip(TRUE),m_rm(NULL){}
	~RingEditEx(){}

	void SetSkin(UINT uidImg);
	void UpdateHSL(UINT uidImg,int h,int s,int l);

protected:
	LRESULT RingdowProc(HWND,RINGPARAMS);
	LRESULT OnNCPaint();
	void OnNCLButtonDown(RINGPARAMS& param);

private:
	BOOL m_bShowTip;
	RingCoolMenu* m_rm;
	RingDIB m_dibSrc;
	
};

class RingTabEx:public RingTab
{
public:
	RingTabEx():m_nHot(-1){}
	~RingTabEx(){}

	void SetSkin(UINT uBkg,UINT uIcon);
	void UpdateHSL(UINT uBkg,UINT uIcon,int h,int s,int l);

protected:
	LRESULT RingdowProc(HWND,RINGPARAMS);
	LRESULT OnPaint(RINGPARAMS&);

private:
	RingDIB m_dibBkgSrc,m_dibIcons,m_dibTab;
	int m_nHot;
};

class RingListBoxEx:public RingListBox
{
public:
	RingListBoxEx():m_nHot(-1),m_bTrack(FALSE),m_btn(NULL){}
	~RingListBoxEx(){}

	int GetHotItem(){return m_nHot;}
	void InitMailButton(UINT uId);
	void DrawMailButton(RingDIB* dib,BOOL bHot,int x,int y);
	void DrawMailButtonHot();

protected:
	LRESULT RingdowProc(HWND,RINGPARAMS);
	void ReDrawItem(int nIndex);

private:
	int m_nHot;
	BOOL m_bTrack;
	RingStatic* m_btn;
	RingDIB m_dib;
};

BEGIN_SETUPMAINWINDOW(IS_WINDOW)
	BEGIN_DEF_VAR(NEED_INIT)
		HRGN m_hrgn;
		HPEN m_pen;
		HBITMAP m_hBmMenuSel;
		int m_nCurWhere,m_nCurSysCmd,m_nSelTab;
		BOOL m_bInCapture;
		RECT m_rcUserBtn,m_rcUserSign,m_rcToolTop;
		RingEdit* m_editSign;
		RingToolBar *m_barbot;
		RingToolTip *m_tip;
		RingCoolMenu* m_rm;		
		ringINI m_ri;
		RingDIB m_dibBkg,m_dibBanner,m_dibBtnRc,m_dibNCBtns,m_dibCaption,m_dibUser,m_dibBot,m_dibBtnState;
		RingDIB m_dibUserBanner,m_dibHoverBtn,m_dibTatoo,m_dibToolTop,m_dibMenuBkg,m_dibMenuSel;
	END_DEF_VAR

	//�����û���������ǩ��
	void MakeUserBanner(LPCTSTR lpsName,LPCTSTR lpsSign);
	//������λ��
	int HitTest(RINGPARAMS& param);
	//�����ư�ť
	void CheckAndDrawButtons(int nWhich,int nOffset);
	//������̬ϵͳ��ť
	void DrawNCButton(int nIdx,int offset);
	//���ƹ�������ť
	void DrawToolButton(int nIdx,BOOL bDrawNormal);
	int DrawToolTopBtn(int nIdx,BOOL bDrawNormal,LPRECT lprc);
	int DrawToolRightBtn(int nIdx,BOOL bDrawNormal,LPRECT lprc);
	//�����û�ͷ���԰�ť
	void DrawUserButton(BOOL bSign,BOOL bDrawNormal);
	//�������������ư�ť�����Ͱ���״̬
	void DrawButtonState(RingDIB* dest,BOOL bPushed,int x,int y,int w,int h);
	//�����ɫ
	void UpdateHSL();
	void UpdateHSL(int h,int s,int l);
	void UpdateBottomTool();
	//���¿ͻ������ڳߴ缰λ��
	void UpdateClientWndPos();
		
	BEGIN_DEFMSG
		DEFMSG(WM_CREATE)
		DEFMSG(WM_ERASEBKGND)
		DEFMSG(WM_SIZE)
		DEFMSG(WM_MOVE)
		DEFMSG(WM_GETMINMAXINFO)
		DEFMSG(WM_NCCALCSIZE)
		DEFMSG(WM_NCPAINT)
		DEFMSG(WM_PAINT)
		DEFNOTIFY(NM_CUSTOMDRAW)
		DEFMSG(WM_ENTERSIZEMOVE)
		DEFMSG(WM_EXITSIZEMOVE)
		DEFMSG(WM_LBUTTONDBLCLK)
		DEFMSG(WM_LBUTTONDOWN)
		DEFMSG(WM_MOUSEMOVE)
		DEFMSG(WM_LBUTTONUP)
		DEFMSGEX(OnClickTaskIcon)		
		DEFCMD(OnShowWindow)
		DEFCMD(OnChangeSign)
		DEFCMD(OnExit)
		DEFMSG(WM_DESTROY)
	END_DEFMAINMSG
END_SETUPMAINWINDOW

//�������ô���
BEGIN_SETUPWINDOW(WndUIOp,IS_WINDOW)
	BEGIN_DEF_VAR(NEED_INIT)
		HPEN m_pen;
		RingStatic *m_stHead;
	END_DEF_VAR

	BOOL SetNavChild(LPCTSTR lpszCaption,HWND hWnd);

	BEGIN_DEFMSG
		DEFMSG(WM_ACTIVATE)
		DEFMSG(WM_NCCALCSIZE)
		DEFMSG(WM_NCPAINT)
		DEFCMD(OnSelTab)
		DEFMSGEX(OnHideClose)
		DEFMSG(WM_DESTROY)
		DEFMSG(WM_CREATE)
	END_DEFMSG(WndUIOp)
END_SETUPWINDOW(WndUIOp)

BEGIN_SETUPWINDOW(DlgUIColor,IS_DIALOG)
	BINDID(IDD_UICONFIG)
	BEGIN_DEF_VAR(NO_INIT)
		RingStatic* m_stColor[8];
		RingTrackBarEx *m_barHue,*m_barSum,*m_barLum,*m_barAlpha;
		RingToolTip* m_tip;
		int m_hue,m_sum,m_lum;
	END_DEF_VAR
	
	BEGIN_DEFMSG
		DEFMSG(WM_INITDIALOG)
		DEFMSG(WM_HSCROLL)
		DEFMSG(WM_DESTROY)
		DEFCMD(OnChooseColor)
	END_DEFMSG(DlgUIColor)
END_SETUPWINDOW(DlgUIColor)

BEGIN_SETUPWINDOW(DlgUITatoo,IS_DIALOG)
	BINDID(IDD_TATOOCONFIG)
	BEGIN_DEF_VAR(NO_INIT)
		RingStatic* m_stTatoo[9];
		RingToolTip* m_tip;
		int m_nTatooCnt,m_nCurrTatoo;
		HPEN m_pen;
	END_DEF_VAR
	
	BEGIN_DEFMSG
		DEFMSG(WM_INITDIALOG)
		DEFMSG(WM_PAINT)
		DEFMSG(WM_DESTROY)
		DEFCMD(OnSelTatoo)
		DEFCMD(OnSel1)
		DEFCMD(OnSel2)
		DEFCMD(OnSel3)
		DEFCMD(OnSel4)
		DEFCMD(OnSel5)
		DEFCMD(OnSel6)
		DEFCMD(OnSel7)
		DEFCMD(OnSel8)
		DEFCMD(OnSel9)
	END_DEFMSG(DlgUITatoo)
END_SETUPWINDOW(DlgUITatoo)

//QQ��ť����
BEGIN_SETUPWINDOW(WndQQButton,IS_WINDOW)
	BEGIN_DEF_VAR(NO_INIT)
		RingStatic *m_btn,*m_btnQQ;
		RingToolTip *m_tip;
		RingDIB m_dibBkg,m_dibQQ,m_dibArrBtn,m_dibQQBtn;
		BOOL m_bIsSideToolHide;
	END_DEF_VAR

	void UpdateHSL(int h=-1,int s=-1,int l=-1);

	BEGIN_DEFMSG
		DEFMSG(WM_LINKHOVER)
		DEFMSG(WM_LINKLEAVE)
		DEFMSG(WM_CREATE)
		DEFMSG(WM_PAINT)
		DEFCMD(OnSwitchSideTab)
	END_DEFMSG(WndQQButton)
END_SETUPWINDOW(WndQQButton)

//�ͻ�������
BEGIN_SETUPWINDOW(WndClient,IS_WINDOW)
	BEGIN_DEF_VAR(NEED_INIT)
		int m_nCurrTab;
		RingEditEx *m_edSearch;
		RingToolBar *m_sidebar;
		RingTabEx *m_tab;
		RingListBoxEx *m_list[3];
		RingCoolMenu* m_rm;
		RingDIB m_dibBkg,m_dibBtnState,m_dibBtnBorder,m_dibList,m_dibListSrc,m_dibHorzArr,m_dibUsers;
		ringStr m_str;
	END_DEF_VAR

	void UpdateHSL(int h=-1,int s=-1,int l=-1);
	//����QQ���ѣ�Ⱥ�������ϵ��3���б�
	void MakeFriendList();
	void MakeGroupList();
	void MakeRecentList();
	//�б��Ի溯��
	void DrawListTitle(int nIndex,LPDRAWITEMSTRUCT lpdraw,int w,int h);
	void DrawUserList(RingListBoxEx* list,LPDRAWITEMSTRUCT lpdraw,int w,int h);
	//�б�������Ĵ���
	BOOL ExpandList(RingListBox* list,int nIndex);

	BEGIN_DEFMSG
		DEFNOTIFY(NM_CUSTOMDRAW)
		DEFNOTIFY(TCN_SELCHANGE)
		DEFMSG(WM_DRAWITEM)
		DEFMSG(WM_SIZE)
		DEFMSG(WM_CREATE)
		DEFMSG(WM_LINKHOVER)
		DEFMSG(WM_LINKLEAVE)
		DEFMSGEX(OnTabMenuPop)
		DEFCMD(OnUserListClick)
		DEFCMD(OnGroupListClick)
	END_DEFMSG(WndClient)
END_SETUPWINDOW(WndClient)

#endif
