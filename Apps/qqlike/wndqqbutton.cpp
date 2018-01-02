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
//ԭ�ļ���wndqqbutton.cpp
//
//��ʾ��QQ2009�Ľ���,�ײ�����������
//
**********************************************************************///////////////////////////////////////
#include "global.h"

//��ťID����
#define IDC_HIDETOOL		13401
#define IDC_QQMENUBTN	13402

enum
{
	QQBTN_WIDTH = 36,					//���½�QQ��ť��
	QQBTN_HEIGHT = 36,				//���½�QQ��ť��
	QQBTN_X = 2,						//���½�QQ��ťx����
	QQBTN_Y = 15,						//���½�QQ��ťy����
	QQBTN_QQ_X = 8,					//QQͼ����QQ��ť��x����
	QQBTN_QQ_Y = 8,					//QQͼ����QQ��ť��y����
	QQBTN_QQ_WIDTH = 19,				//QQͼ���
	QQBTN_QQ_HEIGHT = 20,			//QQͼ���

	BTN_PICWIDTH = 15,				//�л���߹�������ťͼ����
	BTN_PICHEIGHT = 14,				//�л���߹�������ťͼ��߶�
	BTN_WIDTH = 13,					//�л���߹�������ť���
	BTN_HEIGHT = 13,					//�л���߹�������ť�߶�
	BTN_X = 3,							//�л���߹�������ťx����
	BTN_Y = 1,							//�л���߹�������ťy����
};

BEGIN_REGMSG(WndQQButton)
	REGMSG(WM_LINKHOVER)
	REGMSG(WM_LINKLEAVE)
	REGMSG(WM_PAINT)
	REGCMD(IDC_HIDETOOL,OnSwitchSideTab)
	REGMSG(WM_CREATE)
END_REGMSG

RINGMSG(WndQQButton,WM_CREATE)
{
	m_bIsSideToolHide = FALSE;
	m_dibQQBtn.Create(QQBTN_WIDTH * 3,QQBTN_HEIGHT);

	//�����л���߹�������ť
	m_btn = NewRingObj(itemof(RingStatic));
	m_btn->Create(0,0,NULL,IDC_HIDETOOL,BTN_X,BTN_Y,BTN_WIDTH,BTN_HEIGHT);
	HRGN hrgn = CreateEllipticRgn(0,0,BTN_WIDTH,BTN_HEIGHT);
	SetWindowRgn(m_btn->Handle(),hrgn,TRUE);
	DeleteObject(hrgn);
	m_btn->SetHyperlink(0,0,FALSE);
	m_dibArrBtn.SetTarget(m_btn->Handle());

	//����QQ��ť
	m_btnQQ = NewRingObj(itemof(RingStatic));
	m_btnQQ->Create(0,0,NULL,IDC_QQMENUBTN,QQBTN_X,QQBTN_Y,QQBTN_WIDTH,QQBTN_HEIGHT);
	hrgn = CreateEllipticRgn(0,0,QQBTN_WIDTH,QQBTN_HEIGHT);
	SetWindowRgn(m_btnQQ->Handle(),hrgn,TRUE);
	DeleteObject(hrgn);
	m_btnQQ->SetHyperlink(0,0,FALSE);
	//�趨m_dibQQBtn��m_dibBkg�Ļ���Ŀ�괰��ΪQQ��ť
	m_dibQQBtn.SetTarget(m_btnQQ->Handle());
	m_dibBkg.SetTarget(m_btnQQ->Handle());

	//����������ʾ
	m_tip = NewRingObj(itemof(RingToolTip));
	m_tip->Create();
	m_tip->AddTool(m_btn->Handle(),"��������");
	m_tip->AddTool(m_btnQQ->Handle(),"���˵�");

	SetPos(0,0,NCB_QQBTNWIDTH,NCB_BOTTOMHEIGHT);
	return DefaultProc(param);
}

RINGCMD(WndQQButton,OnSwitchSideTab)
{
	if(event == STN_CLICKED)
	{
		//�л���߹�������ʾ����״̬���ù�����������δʵ�֣�������ı�һ�±��
		m_bIsSideToolHide = !m_bIsSideToolHide;
		if(m_bIsSideToolHide)
		{
			WndClient->m_sidebar->Show(SW_HIDE);
			m_tip->SetValue("չ�������",IDC_HIDETOOL);
		}
		else
		{
			WndClient->m_sidebar->Show(SW_SHOW);
			RingDockBar* bar = WndClient->m_sidebar->GetDockBar();
			if(bar)
				bar->Show(SW_SHOW);
			m_tip->SetValue("��������",IDC_HIDETOOL);
		}
		InvalidateRect(m_hWnd,NULL,TRUE);
	}
}

RINGMSG(WndQQButton,WM_PAINT)
{
	if(m_bIsSideToolHide)
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hWnd,&ps);
		m_dibArrBtn.Draw(ps.hdc,BTN_X + (BTN_WIDTH - BTN_PICWIDTH)/2,BTN_Y,m_dibArrBtn.Width()/2,0,
								BTN_PICWIDTH,BTN_PICHEIGHT,BTN_PICWIDTH,BTN_PICHEIGHT);
		EndPaint(m_hWnd,&ps);
		return 0;
	}
	else
		return DefaultProc(param);
}

RINGMSG(WndQQButton,WM_LINKHOVER)
{
	if((HWND)param.wParam == m_btn->Handle())
	{
		int sx = BTN_PICWIDTH;
		if(m_bIsSideToolHide)
			sx += m_dibArrBtn.Width()/2;
		m_dibArrBtn.Draw((BTN_WIDTH - BTN_PICWIDTH)/2,0,sx,0,BTN_PICWIDTH,BTN_PICHEIGHT,BTN_PICWIDTH,BTN_PICHEIGHT);
	}
	else if((HWND)param.wParam == m_btnQQ->Handle())
	{
		m_dibQQBtn.Draw(0,0,0,0,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
		Sleep(80);
		m_dibQQBtn.Draw(0,0,QQBTN_WIDTH,0,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
		Sleep(80);
		m_dibQQBtn.Draw(0,0,QQBTN_WIDTH*2,0,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
	}
	return TRUE;
}

RINGMSG(WndQQButton,WM_LINKLEAVE)
{
	if((HWND)param.wParam == m_btn->Handle())
	{
		int sx = 0;
		if(m_bIsSideToolHide)
			sx = m_dibArrBtn.Width()/2;
		m_dibArrBtn.Draw((BTN_WIDTH - BTN_PICWIDTH)/2,0,sx,0,BTN_PICWIDTH,BTN_PICHEIGHT,BTN_PICWIDTH,BTN_PICHEIGHT);
	}
	else if((HWND)param.wParam == m_btnQQ->Handle())
	{
		m_dibQQBtn.Draw(0,0,QQBTN_WIDTH,0,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
		Sleep(80);
		m_dibQQBtn.Draw(0,0,0,0,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
		Sleep(80);
		m_dibBkg.Draw(0,0,QQBTN_X,QQBTN_Y,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
	}
	return TRUE;
}

void RINGMETHOD(WndQQButton,UpdateHSL)(int h,int s,int l)
{
	if(h < 0)
	{
		h = window->m_ri.GetInt("mainbkg","hue",0);
		s = window->m_ri.GetInt("mainbkg","Saturation",100);
		l = window->m_ri.GetInt("mainbkg","light",100);
	}
	m_dibBkg.Load(IDB_QQBTN);
	m_dibBkg.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibArrBtn.Load(IDB_ARRBTN);
	m_dibArrBtn.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibQQ.Load(MAKEINTRESOURCE(IDP_QQ),"PNG",PNG);
	
	for(int i=0;i<3;i++)
	{
		m_dibBkg.DrawTo(&m_dibQQBtn,i*QQBTN_WIDTH,0,QQBTN_X,QQBTN_Y,QQBTN_WIDTH,QQBTN_HEIGHT,FALSE);
		m_dibQQ.AlphaTo(&m_dibQQBtn,QQBTN_QQ_X + i*QQBTN_WIDTH,QQBTN_QQ_Y,i*QQBTN_QQ_WIDTH,0,QQBTN_QQ_WIDTH,QQBTN_QQ_HEIGHT);
	}
	
	HBITMAP hbm = m_dibBkg.GetBitmap();
	SetBkgBitmap(hbm);
	DeleteObject(hbm);
}
