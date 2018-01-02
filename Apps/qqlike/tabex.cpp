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
//tabex.cpp
//
//��ʾ��QQ2009�Ľ���,TAB�ؼ��Ի棬�����ñ����򣬷�ͨ�ÿؼ���
//
**********************************************************************/
#include "global.h"

enum
{
	TAB_ICONWIDTH = 18,		//TABͼ����
	TAB_ICONHEIGHT = 16,		//TABͼ��߶�

	TABARR_WIDTH = 7,			//TAB������ͷ���
	TABARR_HEIGHT = 4,		//TAB������ͷ�߶�
	TABARR_POSX = 11,			//TAB������ͷ���ұ߿����
	TABARR_SRCX = 68,			//TAB������ͷ��Դͼ����Xλ��
	TABARR_SRCY = 10,			//TAB������ͷ��Դͼ����Yλ��
};

void RingTabEx::SetSkin(UINT uBkg,UINT uIcon)
{
	m_dibBkgSrc.Load(uBkg);
	m_dibIcons.Load(MAKEINTRESOURCE(uIcon),"GIF",GIF);
	m_dibTab.Create(WINVAR(SM_CXSCREEN)/3,m_dibBkgSrc.Height());
}

void RingTabEx::UpdateHSL(UINT uBkg,UINT uIcon,int h,int s,int l)
{
	m_dibBkgSrc.Load(uBkg);
	m_dibIcons.Load(MAKEINTRESOURCE(uIcon),"GIF",GIF);
	m_dibBkgSrc.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibIcons.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	InvalidateRect(m_hWnd,NULL,TRUE);
}

LRESULT RingTabEx::RingdowProc(HWND,RINGPARAMS param)
{
	LRESULT res;
	switch(param.uMsg)
   {
		case WM_LBUTTONDOWN:
		{	
			TCHITTESTINFO tci;
			tci.pt.x = param.mousept.x;
			tci.pt.y = param.mousept.y;
			tci.flags = TCHT_ONITEM;
			
			int i = TabCtrl_HitTest(m_hWnd,&tci);
			if(i == GetCurSel())
			{
				RECT rc;
				GetItemRect(i,&rc);
				rc.left = rc.right - TABARR_POSX;
				if(PtInRect(&rc,tci.pt))
					PostMessage(GetParent(),MYWM_COMMAND,(WPARAM)m_hWnd,0);
			}
			res = RingTab::RingdowProc(m_hWnd,param);
			InvalidateRect(m_hWnd,NULL,TRUE);
			return res;
		}
		case WM_SIZE:
			SendMessage(m_hWnd,TCM_SETITEMSIZE,0,MAKELONG((param.mousept.x-3)/3,m_dibBkgSrc.Height()));
			break;
		case WM_NCCALCSIZE:
			return 0;
		case WM_MOUSEMOVE:
		{
			TCHITTESTINFO tci;
			tci.pt.x = param.mousept.x;
			tci.pt.y = param.mousept.y;
			tci.flags = TCHT_ONITEM;
			
			int i = TabCtrl_HitTest(m_hWnd,&tci);
			if(i >= 0)
			{
				TCITEM tc;
				tc.mask = TCIF_STATE;
				tc.dwState = 0;
				tc.dwStateMask = TCIS_HIGHLIGHTED;
				GetItemInfo(i,&tc);
				if(tc.dwState == 0)
					TabCtrl_HighlightItem(m_hWnd,i,TRUE);
				if(m_nHot >= 0 && m_nHot != i)
					TabCtrl_HighlightItem(m_hWnd,m_nHot,FALSE);
				m_nHot = i;
			}
			break;
		}
		case WM_MOUSELEAVE:
			if(m_nHot >= 0)
				TabCtrl_HighlightItem(m_hWnd,m_nHot,FALSE);
			m_nHot = -1;
			break;
	}	
	return RingTab::RingdowProc(m_hWnd,param);
}

LRESULT RingTabEx::OnPaint(RINGPARAMS& param)
{
	PAINTSTRUCT ps;
	RECT wrc,rc;
	int nCnt = GetCount();
	int nSel = GetCurSel();
	int nFocus = TabCtrl_GetCurFocus(m_hWnd);
	TCITEM tc;
	tc.mask = TCIF_STATE;
	tc.dwState = 0;
	tc.dwStateMask = TCIS_BUTTONPRESSED|TCIS_HIGHLIGHTED;

	GetWindowRect(m_hWnd,&wrc);
	GetClientRect(&rc);
	MapWindowPoints(m_hWnd,HWND_DESKTOP,(LPPOINT)&rc,2);
	OffsetRect(&rc,-wrc.left,-wrc.top);
	OffsetRect(&wrc,-wrc.left,-wrc.top);

	BeginPaint(m_hWnd,&ps);
	ExcludeClipRect(ps.hdc,rc.left,rc.top,rc.right,rc.bottom);
	for(int i=0;i<nCnt;i++)
	{
		GetItemRect(i,&rc);
		GetItemInfo(i,&tc);

		if(i == nSel)
		{
			//���ұ߿�
			m_dibBkgSrc.DrawTo(&m_dibTab,0,0,3,0,1,m_dibBkgSrc.Height(),FALSE);
			m_dibBkgSrc.DrawTo(&m_dibTab,rc.right-rc.left-1,0,3,0,1,m_dibBkgSrc.Height(),FALSE);
			//����
			m_dibBkgSrc.StretchTo(&m_dibTab,1,0,rc.right-rc.left-2,m_dibBkgSrc.Height(),2,0,1,m_dibBkgSrc.Height(),FALSE);
			//�м�ͼ��
			m_dibIcons.DrawTo(&m_dibTab,(rc.right-rc.left-TAB_ICONWIDTH)/2,(rc.bottom-rc.top-TAB_ICONHEIGHT)/2,
									i*TAB_ICONWIDTH,TAB_ICONHEIGHT,TAB_ICONWIDTH,TAB_ICONHEIGHT);
			if(MASK_MATCH(tc.dwState,TCIS_HIGHLIGHTED))
			{
				//����������ͷ�������û�ͷ���е�������ͷ
				window->m_dibUser.DrawTo(&m_dibTab,rc.right - rc.left - TABARR_POSX,(rc.bottom-rc.top-TABARR_HEIGHT)/2,
												TABARR_SRCX,TABARR_SRCY,TABARR_WIDTH,TABARR_HEIGHT);
			}
		}
		else
		{
			//����
			if(MASK_MATCH(tc.dwState,TCIS_HIGHLIGHTED))
				m_dibBkgSrc.StretchTo(&m_dibTab,0,0,rc.right-rc.left,m_dibBkgSrc.Height(),1,0,1,m_dibBkgSrc.Height(),FALSE);
			else
				m_dibBkgSrc.StretchTo(&m_dibTab,0,0,rc.right-rc.left,m_dibBkgSrc.Height(),0,0,1,m_dibBkgSrc.Height(),FALSE);
			//�м�ͼ��
			m_dibIcons.DrawTo(&m_dibTab,(rc.right-rc.left-TAB_ICONWIDTH)/2,(rc.bottom-rc.top-TAB_ICONHEIGHT)/2,
									i*TAB_ICONWIDTH,0,TAB_ICONWIDTH,TAB_ICONHEIGHT);
		}
		m_dibTab.Draw(ps.hdc,rc.left,rc.top,0,0,rc.right-rc.left,rc.bottom-rc.top,rc.right-rc.left,rc.bottom-rc.top);
		ExcludeClipRect(ps.hdc,rc.left,rc.top,rc.right,rc.bottom);
	}
	FillRect(ps.hdc,&wrc,m_brush);
	EndPaint(m_hWnd,&ps);
	return TRUE;
}
