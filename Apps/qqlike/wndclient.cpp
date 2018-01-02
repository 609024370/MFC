//**********************************************************************
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
//ԭ�ļ���wndclient.cpp
//
//��ʾ��QQ2009�Ľ���,�ͻ�������
//
//**********************************************************************/
#include "global.h"

TCHAR gszSearchTip[] = "�������Ѽ�������Ϣ";

enum
{
	LIST_ARRSRC_X = 14,			//��ͷͼ����Դͼ��X����
	LIST_ARRSRC_Y = 1,			//��ͷͼ����Դͼ��Y����
	LIST_ARRSRC_WIDTH = 6,		//��ͷͼ����Դͼ���
	LIST_ARRSRC_HEIGHT = 11,	//��ͷͼ����Դͼ���
	
	LIST_SELBKG_SRCX = 8,		//ѡ��״̬������Դͼ��X����
	LIST_SELBKG_SRCY = 1,		//ѡ��״̬������Դͼ��Y����
	LIST_SELBKG_SRCW = 3,		//ѡ��״̬������Դͼ����
	LIST_SELBKG_SRCH = 22,		//ѡ��״̬������Դͼ��߶�
	LIST_USERITEMHEIGHT = 52,	//�û��б���߶�
	LIST_USERSELBKG_SRCX = 10,	//�û�ѡ��״̬������Դͼ��X����
	LIST_USERHOTBKG_SRCX = 3,	//�û�����״̬������Դͼ��X����
	LIST_USERBKG_SRCY = 2		//�û�������Դͼ��Y����
	
};

BEGIN_REGMSG(WndClient)
	REGNOTIFY(NM_CUSTOMDRAW)
	REGNOTIFY(TCN_SELCHANGE)
	REGMSG(WM_DRAWITEM)
	REGMSG(WM_SIZE)
	REGMSG(WM_LINKHOVER)
	REGMSG(WM_LINKLEAVE)
	REGMSGEX(MYWM_COMMAND,OnTabMenuPop)
	REGCMD(IDC_QQFRIEND,OnUserListClick)
	REGCMD(IDC_QQGROUP,OnGroupListClick)
	REGMSG(WM_CREATE)
END_REGMSG

INITWINDOW(WndClient)()
{
	m_edSearch = NULL;
	m_nCurrTab = 0;
}

RINGMSG(WndClient,WM_CREATE)
{
	SetBkgColor(0xFFFFFF);
	//����������
	m_edSearch = NewRingObj(itemof(RingEditEx));
	m_edSearch->SetSkin(IDG_SEARCHBAR);
	m_edSearch->Create(ES_AUTOHSCROLL,0,gszSearchTip,IDC_SEARCH,0,0,WND_MINWIDTH,26);
	m_edSearch->SetTextColor(0x00808080);
	m_edSearch->EnableDock(NULL,TBS_EX_NONE);
	//������Դ
	m_dibBkg.Create(1,1);
	m_dibBtnState.Load(IDB_SIDEBTNSTATE);
	m_dibBtnBorder.Load(IDB_SIDEBTNBORDER);
	m_dibListSrc.Load(MAKEINTRESOURCE(IDG_LISTTITLE),"GIF",GIF);
	m_dibHorzArr.Load(MAKEINTRESOURCE(IDG_LISTARR),"GIF",GIF);
	m_dibUsers.Load(MAKEINTRESOURCE(IDG_USERS),"GIF",GIF);
	m_dibList.Create(WINVAR(SM_CXSCREEN),LIST_USERITEMHEIGHT);
	//�����
	m_sidebar = NewRingObj(itemof(RingToolBar));
	m_sidebar->Create(IDB_SIDETOOL,TBSTYLE_FLAT);
	m_sidebar->InsertButton(0,0,IDS_SIDETOOL1,NULL,TBSTYLE_BUTTON|TBSTYLE_CHECKGROUP,TBSTATE_ENABLED|TBSTATE_CHECKED);
	m_sidebar->InsertButton(1,1,IDS_SIDETOOL2,NULL,TBSTYLE_BUTTON|TBSTYLE_CHECKGROUP);
	m_sidebar->InsertButton(2,2,IDS_SIDETOOL3,NULL,TBSTYLE_BUTTON|TBSTYLE_CHECKGROUP);
	m_sidebar->InsertButton(3,3,IDS_SIDETOOL4);
	m_sidebar->EnableDock(NULL,TBS_EX_NONE,TBS_FLAG_DOCKLEFT);
	//TAB�ϵĵ����˵�
	m_rm = new RingCoolMenu;
	m_rm->LoadPopup(MAKEINTRESOURCE(IDR_TABMENU));
	m_rm->SetItemDrawFunc(FUNC_DRAWMENU_DEF,TRUE,FUNC_DRAWPARENT_DEF);
	HBITMAP hbm = window->m_dibMenuBkg.GetBitmap();
	m_rm->SetBkg(hbm);
	DeleteObject(hbm);
	m_rm->SetSelectBkg(window->m_hBmMenuSel,0x00FFFFFF);
	//TAB�ؼ�
	m_tab = NewRingObj(itemof(RingTabEx));
	m_tab->SetSkin(IDB_TABBKG,IDG_TABICON);
	m_tab->Create(TCS_FIXEDWIDTH|TCS_HOTTRACK,RTV_FITPARENTSIZE,NULL,IDC_MAINTAB,0,0,0,0);
	m_tab->InsertTabs("||");
	//��ʼ���û��б�
	int i;
	for(i=0;i<3;i++)
	{
		m_list[i] = NewRingObj(itemof(RingListBoxEx));
		m_list[i]->Create(LBS_OWNERDRAWVARIABLE|LBS_HASSTRINGS|LBS_NOTIFY|LBS_NOINTEGRALHEIGHT|WS_VSCROLL,RTV_FITPARENTSIZE,
								"",IDC_QQFRIEND+i,0,0,0,0);
		m_tab->SetTabToWnd(i,m_list[i]);
	}
	m_list[0]->InitMailButton(IDG_MAIL);
	m_list[0]->AddStrings("�ҵĺ��� [8/8]|İ���� [0/0]|������ [0/0]");
	m_list[0]->SetItemHeight(m_dibListSrc.Height(),0);
	m_list[0]->SetItemHeight(m_dibListSrc.Height(),1);
	m_list[0]->SetItemHeight(m_dibListSrc.Height(),2);
	m_list[0]->SetData(0,QQLIST_ISTITLE|QQLIST_EXPANDED);
	m_list[0]->SetData(1,QQLIST_ISTITLE);
	m_list[0]->SetData(2,QQLIST_ISTITLE);
	
	m_list[1]->InitMailButton(IDG_MAIL);
	m_list[1]->AddString("������[0]");
	m_list[1]->SetItemHeight(m_dibListSrc.Height(),0);
	m_list[1]->SetData(0,QQLIST_ISTITLE);

	m_list[2]->InitMailButton(IDG_MAIL);
	//��Ӻ��ѣ�Ⱥ�������ϵ��
	MakeFriendList();
	MakeGroupList();
	MakeRecentList();
	
	return DefaultProc(param);
}

RINGMSG(WndClient,WM_SIZE)
{
	if(m_edSearch)
	{
		RECT rc;
		::GetClientRect(m_hWnd,&rc);
		MoveWindow(m_edSearch->Handle(),0,0,rc.right,26,TRUE);
	}
	return DefaultProc(param);
}

RINGNOTIFY(WndClient,NM_CUSTOMDRAW)
{
	if(param.lpnmhdr->hwndFrom == m_sidebar->Handle())
	{
		if(param.lpnmcustomdraw->dwDrawStage == CDDS_PREPAINT)
			return CDRF_NOTIFYITEMDRAW;	//ָ��֪ͨ��ť�Ի�
		else if(param.lpnmcustomdraw->dwDrawStage == CDDS_ITEMPREPAINT)
		{
			int h = m_dibBtnState.Height();
			int w = m_dibBtnState.Width()/2;
			int offx = (param.lpnmcustomdraw->rc.right - param.lpnmcustomdraw->rc.left - w)/2;
			int offy = (param.lpnmcustomdraw->rc.bottom - param.lpnmcustomdraw->rc.top - h)/2;
			
			if(param.lpnmcustomdraw->uItemState == CDIS_CHECKED)
			{
				HIMAGELIST himg = m_sidebar->GetImageList();
				w = m_dibBtnBorder.Width()/2;
				h = m_dibBtnBorder.Height();
				m_dibBtnBorder.Draw(param.lpnmcustomdraw->hdc,param.lpnmcustomdraw->rc.left,
											param.lpnmcustomdraw->rc.top,w,0,w,h,w,h);
				ImageList_Draw(himg,param.lpnmcustomdraw->dwItemSpec-IDS_SIDETOOL1,param.lpnmcustomdraw->hdc,
									(param.lpnmcustomdraw->rc.left + param.lpnmcustomdraw->rc.right - 24)/2 + 1,
									(param.lpnmcustomdraw->rc.top + param.lpnmcustomdraw->rc.bottom - 24)/2 + 1,
									ILD_TRANSPARENT);
				return CDRF_SKIPDEFAULT;
			}
			else if(MASK_MATCH(param.lpnmcustomdraw->uItemState,CDIS_SELECTED))
			{
				if(param.lpnmcustomdraw->dwItemSpec == IDS_SIDETOOL4)
					m_dibBtnState.Draw(param.lpnmcustomdraw->hdc,param.lpnmcustomdraw->rc.left + offx,
											param.lpnmcustomdraw->rc.top + offy,w,0,w,h,w,h);
			}
			else if(MASK_MATCH(param.lpnmcustomdraw->uItemState,CDIS_HOT))
			{
				//����״̬
				if(param.lpnmcustomdraw->dwItemSpec == IDS_SIDETOOL4)
				{
					m_dibBtnState.Draw(param.lpnmcustomdraw->hdc,param.lpnmcustomdraw->rc.left + offx,
											param.lpnmcustomdraw->rc.top + offy,0,0,w,h,w,h);
				}
				else
				{
					w = m_dibBtnBorder.Width()/2;
					h = m_dibBtnBorder.Height();
					m_dibBtnBorder.Draw(param.lpnmcustomdraw->hdc,param.lpnmcustomdraw->rc.left,
												param.lpnmcustomdraw->rc.top,0,0,w,h,w,h);
				}
			}
			return TBCDRF_NOEDGES;	//���ཻ��ϵͳ���ƣ�ָ������Ҫ���ư�ť��߿�
		}
	}	
	return DefaultProc(param);
}

RINGNOTIFY(WndClient,TCN_SELCHANGE)
{
	int iCol = m_tab->GetCurSel();
	if(m_nCurrTab == iCol)
		return 0;
		
	//����Ч��
	int nStep,nLen=0,w,h,nOff;
	HWND hWndIn = m_list[iCol]->Handle();
	HWND hWndOut = m_list[m_nCurrTab]->Handle();
	RECT rc,rcin,rcout;
	m_tab->GetClientRect(&rcin);
	CopyRect(&rcout,&rcin);
	CopyRect(&rc,&rcin);
	w = rcin.right - rcin.left;
	h = rcin.bottom - rcin.top;
	nOff = w/20;
			
	if(iCol < m_nCurrTab)
	{
		OffsetRect(&rcin,-w,0);
		nStep = nOff;
	}
	else
	{
		OffsetRect(&rcin,w,0);
		nStep = -nOff;
	}
	MoveWindow(hWndIn,rcin.left,rcin.top,w,h,FALSE);
	ShowWindow(hWndIn,SW_SHOW);
			
	while(nLen + nOff < w)
	{
		OffsetRect(&rcin,nStep,0);
		OffsetRect(&rcout,nStep,0);
		MoveWindow(hWndIn,rcin.left,rcin.top,w,h,TRUE);
		MoveWindow(hWndOut,rcout.left,rcout.top,w,h,TRUE);
		nLen += nOff;
		Sleep(5);
	}
	ShowWindow(hWndOut,SW_HIDE);
	MoveWindow(hWndOut,rc.left,rc.top,w,h,TRUE);
	MoveWindow(hWndIn,rc.left,rc.top,w,h,TRUE);

	m_nCurrTab = iCol;
	return 0;
}

RINGMSGEX(WndClient,OnTabMenuPop)
{
	if((HWND)param.wParam == m_tab->Handle())
		m_rm->Popup(m_hWnd);
	return 0;
}

RINGCMD(WndClient,OnUserListClick)
{
	if(event == LBN_SELCHANGE)
	{
		int nIndex = m_list[0]->GetCurSel();
		if(ExpandList(m_list[0],nIndex) && nIndex == 0)
		{
			MakeFriendList();
			RECT rc;
			GetWindowRect(m_list[0]->Handle(),&rc);
			SendMessage(m_list[0]->Handle(),WM_SIZE,0,MAKELONG(rc.right-rc.left,rc.bottom-rc.top));			
		}
		InvalidateRect(m_list[0]->Handle(),NULL,TRUE);
	}
}

RINGCMD(WndClient,OnGroupListClick)
{
	if(event == LBN_SELCHANGE)
	{
		ExpandList(m_list[1],m_list[1]->GetCurSel());
		InvalidateRect(m_list[1]->Handle(),NULL,TRUE);
	}
}

RINGMSG(WndClient,WM_LINKHOVER)
{
	int nIndex = m_tab->GetCurSel();
	RingListBoxEx *list = m_list[nIndex];
	list->DrawMailButtonHot();
	return TRUE;
}

RINGMSG(WndClient,WM_LINKLEAVE)
{
	int nIndex = m_tab->GetCurSel();
	RingListBoxEx *list = m_list[nIndex];
	nIndex = list->GetHotItem();
	RECT rc;
	list->GetItemRect(nIndex,&rc);
	InvalidateRect(list->Handle(),&rc,TRUE);
	return TRUE;
}

RINGMSG(WndClient,WM_DRAWITEM)
{
	if(param.lpdrawitem->CtlType == ODT_LISTBOX)
	{
		int w = param.lpdrawitem->rcItem.right - param.lpdrawitem->rcItem.left;
		int h = param.lpdrawitem->rcItem.bottom - param.lpdrawitem->rcItem.top;

		if(h > 0)
		{
			m_dibList.Fill(0x00FFFFFF);

			if(MASK_MATCH(param.lpdrawitem->itemData,QQLIST_ISTITLE))
				DrawListTitle(param.wParam - IDC_QQFRIEND,param.lpdrawitem,w,h);	//�����б����
			else
				DrawUserList(m_list[param.wParam - IDC_QQFRIEND],param.lpdrawitem,w,h);		//�����û�ͷ��
		}
		return TRUE;
	}
	
	return DefaultProc(param);
}

//�����б����
void RINGMETHOD(WndClient,DrawListTitle)(int nIndex,LPDRAWITEMSTRUCT lpdraw,int w,int h)
{
	if(MASK_MATCH(lpdraw->itemState,ODS_SELECTED))
	{
		//�б���⣬���Ʊ߿�
		m_dibListSrc.DrawTo(&m_dibList,0,0,0,0,1,m_dibListSrc.Height());
		m_dibListSrc.StretchTo(&m_dibList,1,0,w-2,h,1,0,1,m_dibListSrc.Height());
		m_dibListSrc.DrawTo(&m_dibList,w-1,0,m_dibListSrc.Width()-1,0,1,m_dibListSrc.Height());
		//����ѡ�б���
		m_dibListSrc.DrawTo(&m_dibList,1,1,LIST_SELBKG_SRCX,LIST_SELBKG_SRCY,LIST_SELBKG_SRCW,LIST_SELBKG_SRCH);
		m_dibListSrc.StretchTo(&m_dibList,1+LIST_SELBKG_SRCW,1,w-2*LIST_SELBKG_SRCW,h-2,
										LIST_SELBKG_SRCX+LIST_SELBKG_SRCW+1,1,1,LIST_SELBKG_SRCH);
		m_dibListSrc.DrawTo(&m_dibList,w-LIST_SELBKG_SRCW-1,1,LIST_SELBKG_SRCX+LIST_SELBKG_SRCW,LIST_SELBKG_SRCY,
									LIST_SELBKG_SRCW,LIST_SELBKG_SRCH);
	}
	else if(m_list[nIndex]->GetHotItem() == (int)lpdraw->itemID)
	{
		//���Ƹ�������
		m_dibListSrc.DrawTo(&m_dibList,1,1,1,1,LIST_SELBKG_SRCW,LIST_SELBKG_SRCH);
		m_dibListSrc.StretchTo(&m_dibList,1+LIST_SELBKG_SRCW,1,w-2*LIST_SELBKG_SRCW,h-2,
										LIST_SELBKG_SRCW,1,1,LIST_SELBKG_SRCH);
		m_dibListSrc.DrawTo(&m_dibList,w-LIST_SELBKG_SRCW-1,1,2+LIST_SELBKG_SRCW,LIST_SELBKG_SRCY,
									LIST_SELBKG_SRCW,LIST_SELBKG_SRCH);
	}
	//���Ƽ�ͷ
	if(MASK_MATCH(lpdraw->itemData,QQLIST_EXPANDED))
	{
		m_dibHorzArr.DrawTo(&m_dibList,3,(h-LIST_ARRSRC_WIDTH)/2,0,0,
									LIST_ARRSRC_HEIGHT,LIST_ARRSRC_WIDTH);
	}
	else
	{
		m_dibListSrc.DrawTo(&m_dibList,6,(h-LIST_ARRSRC_HEIGHT)/2,LIST_ARRSRC_X,LIST_ARRSRC_Y,
									LIST_ARRSRC_WIDTH,LIST_ARRSRC_HEIGHT);
	}
	//����
	m_dibList.Draw(lpdraw->hDC,lpdraw->rcItem.left,lpdraw->rcItem.top,0,0,w,h,w,h);
	lpdraw->rcItem.left += 21;
	SetBkMode(lpdraw->hDC,TRANSPARENT);
		
	LPCTSTR lps = m_list[nIndex]->GetText(lpdraw->itemID);
	DrawText(lpdraw->hDC,lps,lstrlen(lps),&lpdraw->rcItem,DT_VCENTER|DT_SINGLELINE|DT_LEFT);
}

//�����û���Ϣ
void RINGMETHOD(WndClient,DrawUserList)(RingListBoxEx* list,LPDRAWITEMSTRUCT lpdraw,int w,int h)
{
	if(MASK_MATCH(lpdraw->itemState,ODS_SELECTED))
	{
		m_dibListSrc.StretchTo(&m_dibList,0,0,w,h,LIST_USERSELBKG_SRCX,LIST_USERBKG_SRCY,1,1,FALSE);
		if(list->GetHotItem() == (int)lpdraw->itemID)
			list->DrawMailButton(&m_dibList,FALSE,USERIMG_SIZE + 8,34);
	}
	else if(list->GetHotItem() == (int)lpdraw->itemID)
	{
		//���Ƹ�������
		m_dibListSrc.StretchTo(&m_dibList,0,0,w,h,LIST_USERHOTBKG_SRCX,LIST_USERBKG_SRCY,1,1,FALSE);
		list->DrawMailButton(&m_dibList,FALSE,USERIMG_SIZE + 8,34);
	}
	//����ͷ��
	m_dibUsers.DrawTo(&m_dibList,4,4,lpdraw->itemData*USERIMG_SIZE,0,USERIMG_SIZE,USERIMG_SIZE);
	//����
	m_dibList.Draw(lpdraw->hDC,lpdraw->rcItem.left,lpdraw->rcItem.top,0,0,w,h,w,h);

	//�����û���
	int n = SaveDC(lpdraw->hDC);
	SetBkMode(lpdraw->hDC,TRANSPARENT);
	SetTextColor(lpdraw->hDC,0);
	m_str = list->GetText(lpdraw->itemID);
	int nPos = m_str.indexOf("|");
	m_str[nPos] = '\0';
	RECT rc = {lpdraw->rcItem.left + USERIMG_SIZE + 8,lpdraw->rcItem.top + 6,lpdraw->rcItem.right,lpdraw->rcItem.bottom};
	DrawText(lpdraw->hDC,m_str.string(),lstrlen(m_str.string()),&rc,DT_LEFT|DT_SINGLELINE|DT_TOP);
	rc.top += 14;
	SetTextColor(lpdraw->hDC,0x00808080);
	DrawText(lpdraw->hDC,m_str.string()+nPos+1,lstrlen(m_str.string()+nPos+1),&rc,DT_LEFT|DT_SINGLELINE|DT_TOP);
	RestoreDC(lpdraw->hDC,n);
}

void RINGMETHOD(WndClient,UpdateHSL)(int h,int s,int l)
{
	window->m_dibBkg.DrawTo(&m_dibBkg,0,0,0,NCB_TITLEHEIGHT/2);
	HBITMAP hbm = m_dibBkg.GetBitmap();
	SetDockBackGround(hbm);
	DeleteObject(hbm);

	if(h < 0)
	{
		h = window->m_ri.GetInt("mainbkg","hue",0);
		s = window->m_ri.GetInt("mainbkg","Saturation",100);
		l = window->m_ri.GetInt("mainbkg","light",100);
	}

	m_dibBtnState.Load(IDB_SIDEBTNSTATE);
	m_dibBtnBorder.Load(IDB_SIDEBTNBORDER);
	m_dibHorzArr.Load(MAKEINTRESOURCE(IDG_LISTARR),"GIF",GIF);
	m_dibListSrc.Load(MAKEINTRESOURCE(IDG_LISTTITLE),"GIF",GIF);
	m_dibBtnState.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibBtnBorder.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibListSrc.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibHorzArr.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibListSrc.SetColorKey(m_dibListSrc.GetPixel(0,0));
	m_dibHorzArr.SetColorKey(m_dibHorzArr.GetPixel(0,1));

	m_tab->UpdateHSL(IDB_TABBKG,IDG_TABICON,h,s,l);
	m_edSearch->UpdateHSL(IDG_SEARCHBAR,h,s,l);

	hbm = window->m_dibMenuBkg.GetBitmap();
	m_rm->SetBkg(hbm);
	DeleteObject(hbm);
	m_rm->SetSelectBkg(window->m_hBmMenuSel,0x00FFFFFF);

	for(int i=0;i<3;i++)
		InvalidateRect(m_list[i]->Handle(),NULL,TRUE);
}

//����QQ���ѣ�Ⱥ�������ϵ��3���б�
void RINGMETHOD(WndClient,MakeFriendList)()
{
	m_list[0]->InsertString("RingSDK|",1,1);
	m_list[0]->InsertString("�ܲ�|������Ӣ�ۣ�Ωʹ����ٶ�",2,2);
	m_list[0]->InsertString("���|����褣�������",3,3);
	m_list[0]->InsertString("�����|��������,��������",4,4);
	m_list[0]->InsertString("����|���۵�������ɽ������ʤ֮������������",5,5);
	m_list[0]->InsertString("����|���˽���һ���",6,6);
	m_list[0]->InsertString("�ŷ�|���°׼����վ�Ҫ�뱸,����,��Ҫɱ����ʾ��!",7,7);	
	m_list[0]->InsertString("����|����������壬��������֮��!",8,8);
	m_list[0]->InsertString("С��|���ȣ���վ����!",9,9);

	for(int i=1;i<10;i++)
		m_list[0]->SetItemHeight(LIST_USERITEMHEIGHT,i);
}

void RINGMETHOD(WndClient,MakeGroupList)()
{
	m_list[1]->InsertString("RingSDK(1)|",0,0);
	m_list[1]->InsertString("�ҽ���QQȺ|",1,0);
	
	for(int i=0;i<2;i++)
		m_list[1]->SetItemHeight(LIST_USERITEMHEIGHT,i);
}

void RINGMETHOD(WndClient,MakeRecentList)()
{
	m_list[2]->InsertString("RingSDK(1)|",0,0);
	m_list[2]->InsertString("С��|���ȣ���վ����!",1,9);
	
	for(int i=0;i<2;i++)
		m_list[2]->SetItemHeight(LIST_USERITEMHEIGHT,i);
}

//�б�������Ĵ���
BOOL RINGMETHOD(WndClient,ExpandList)(RingListBox* list,int nIndex)
{
	BOOL bAdd = FALSE;
	DWORD dwData = list->GetData(nIndex);
	if(MASK_MATCH(dwData,QQLIST_ISTITLE))
	{
		int nCnt;
		if(MASK_MATCH(dwData,QQLIST_EXPANDED))
		{
			dwData = QQLIST_ISTITLE;
			nCnt = list->GetCount();
			for(int i=nIndex+1;i<nCnt;i++)
			{
				if(!MASK_MATCH(list->GetData(nIndex+1),QQLIST_ISTITLE))
					list->DelString(nIndex+1);
				else
					break;
			}
		}
		else
		{
			dwData = QQLIST_ISTITLE|QQLIST_EXPANDED;
			bAdd = TRUE;
		}
		list->SetData(nIndex,dwData);
	}
	return bAdd;
}
