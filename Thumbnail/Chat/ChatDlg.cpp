// ChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "ChatDlg.h"
#include "UserInfoDlg.h"
#include "SendToAllDlg.h"
#include  "WinXPButtonST.h"
#include "MacDlg.h"
#include "ChessDlg.h"
#include "ChoiceKindDlg.h"
#include "afxwin.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//#define WM_MYMESSAGE WM_USER+30


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
/*
UINT ReceiveThread(LPVOID lpParam)
{
	HWND handle= (HWND)lpParam;
	CChatDlg *dlg = (CChatDlg *)handle;
	return 0;

}
*/
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CWinXPButtonST m_bu;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_bu);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChatDlg �Ի���



CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	pdlg = NULL;
	hidenflag = true;
	//m_hIcon = AfxGetApp()->LoadIcon(IDB_BITMAP3);
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listctrl);
	DDX_Control(pDX, IDC_BUTTON1, m_menu);
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
//	ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
	ON_WM_CTLCOLOR()

	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnNMDblclkList2)
//	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnNMClickList2)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_HOTKEY,OnHotKey) 
//	ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnNMRclickList2)
ON_COMMAND(ID_140, On140)
ON_COMMAND(ID_149, OnDeleteUser)
ON_COMMAND(ID_147, OnAddUser)
ON_COMMAND(ID_150, On150)
ON_COMMAND(ID_148, OnSendToAll)
ON_COMMAND(ID_167, OnAbort)
ON_COMMAND(ID_169, OnMac)
ON_COMMAND(ID_172, OnChess)
END_MESSAGE_MAP()


// CChatDlg ��Ϣ�������

BOOL CChatDlg::OnInitDialog()
{
	
	CDialog::OnInitDialog();
	RegisterHotKey(m_hWnd,1001,MOD_CONTROL,'Q'); 
	RegisterHotKey(m_hWnd,1002,MOD_CONTROL,'q'); 
	//RegisterHotKey(m_hWnd,1003,MOD_CONTROL,'q');
	RegisterHotKey(m_hWnd,1003,MOD_CONTROL,13); 
	
	SetWindowText("����");

	
	

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO���ڴ���Ӷ���ĳ�ʼ������

	m_menu.SetRounded(true,true);

//��richedit�ĳ�ʼ��
	AfxInitRichEdit( );

	//����imagelist
	m_imagelist.Create(32,32,ILC_COLOR32|ILC_MASK,15,2);
	CBitmap bm[15];
	bm[0].LoadBitmap(IDB_BITMAP1);	
	bm[1].LoadBitmap(IDB_BITMAP2);
	bm[2].LoadBitmap(IDB_BITMAP3);
	bm[3].LoadBitmap(IDB_BITMAP4);	
	bm[4].LoadBitmap(IDB_BITMAP5);
	bm[5].LoadBitmap(IDB_BITMAP6);
	bm[6].LoadBitmap(IDB_BITMAP7);	
	bm[7].LoadBitmap(IDB_BITMAP8);
	bm[8].LoadBitmap(IDB_BITMAP9);
	bm[9].LoadBitmap(IDB_BITMAP10);	
	bm[10].LoadBitmap(IDB_BITMAP11);
	bm[11].LoadBitmap(IDB_BITMAP12);
	bm[12].LoadBitmap(IDB_BITMAP13);	
	bm[13].LoadBitmap(IDB_BITMAP14);
	bm[14].LoadBitmap(IDB_BITMAP15);
	m_imagelist.Add(&bm[0], RGB(0, 0, 0));
	m_imagelist.Add(&bm[1], RGB(0, 0, 0));
	m_imagelist.Add(&bm[2], RGB(0, 0, 0));
	m_imagelist.Add(&bm[3], RGB(0, 0, 0));
	m_imagelist.Add(&bm[4], RGB(0, 0, 0));
	m_imagelist.Add(&bm[5], RGB(0, 0, 0));
	m_imagelist.Add(&bm[6], RGB(0, 0, 0));

	m_imagelist.Add(&bm[7], RGB(0, 0, 0));
	m_imagelist.Add(&bm[8], RGB(0, 0, 0));
	m_imagelist.Add(&bm[9], RGB(0, 0, 0));
	m_imagelist.Add(&bm[10], RGB(0, 0, 0));
	m_imagelist.Add(&bm[11], RGB(0, 0, 0));
	m_imagelist.Add(&bm[12], RGB(0, 0, 0));

	m_imagelist.Add(&bm[13], RGB(0, 0, 0));
	m_imagelist.Add(&bm[14], RGB(0, 0, 0));

	m_listctrl.SetImageList(&m_imagelist, LVSIL_NORMAL);


	//��ʼ��������Ϣ��socket
	m_socket.SetHWnd((HWND)this);
	if(m_socket.Create(1600,SOCK_DGRAM,FD_READ|FD_WRITE,NULL)==SOCKET_ERROR)
	{
		AfxMessageBox("�����׽���ʧ��");
	}


//��ȡ�����ļ������û���Ϣ��userlist��
	CString filename;
	filename = "user\\user.ini";
	CFileFind filefind;
	if ( filefind.FindFile(filename,0) )
	{
		int  usercount;
		usercount = GetPrivateProfileInt(_T("usercount"), _T("count"),0, filename);

		if ( usercount != 0 )
		{
			for (int i = 0 ; i < usercount; i++)
			{
				CString sectionname;
				sectionname.Format("section%d",i+1);
				CString name,ip;
				int imageid;
				GetPrivateProfileString(sectionname, _T("name"),
					_T("QQ"), name.GetBuffer(MAX_PATH),
					MAX_PATH, filename);
				name.ReleaseBuffer ();

				GetPrivateProfileString(sectionname, _T("ip"),
					_T("192.168.0.0"), ip.GetBuffer(MAX_PATH),
					MAX_PATH, filename);
				ip.ReleaseBuffer ();

				imageid = GetPrivateProfileInt (sectionname, _T("imageid"),
							1, filename);
				user muser;
				muser.name = name;
				muser.ID = i;
				muser.ip = ip ;
				muser.Iimage = imageid;
				muser.inicount = i + 1;
				m_userlist.AddTail(muser);

				CString strname = name + "(������)";
				m_listctrl.InsertItem(i,strname,imageid);
				m_listctrl.SetItemData(i,muser.ID);
				CString onlineinfo = "onlineonline" ;
				m_socket.SendTo(onlineinfo,onlineinfo.GetLength(),1600,muser.ip ,0);

			}
		}
		
		

	}


	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChatDlg::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

HBRUSH CChatDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	
	HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
	return br;

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;
}


//˫���б��е�ͼ�괦���¼�
void CChatDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ҵ�������ͼ�����б�ؼ��е�λ��
	POSITION pos = m_listctrl.GetFirstSelectedItemPosition();
	int nItem = m_listctrl.GetNextSelectedItem(pos);
	//CString name=m_listctrl.GetItemText(nItem,0);
	if (nItem == -1)
	{
		return;
	}
	int  id  = m_listctrl.GetItemData(nItem);
	//�ҵ��������ڽṹ�е�λ��
   POSITION pos1;
	user *muser;
	pos1 = m_userlist.GetHeadPosition();
	while ( pos1 != NULL )
	{
		muser = &m_userlist.GetNext (pos1);
		if ( muser->ID ==  id)
		{
			break;
		}
	}

	if ( muser->ID == -1)
	{
		MessageBox("û���ҵ�");
		return;
	}

	if (muser->pdlg == NULL)
	{
		muser->pdlg = new CMyDialog(muser->name,this);
		muser->pdlg->ip = muser->ip;
		muser->pdlg->Iimage = muser->Iimage ;
		muser->pdlg->Create(IDD_DIALOG1,this);
		muser->pdlg->ShowWindow(SW_SHOW);
	}
	if (!muser->pdlg->IsWindowVisible())
	{
		muser->pdlg->ShowWindow(SW_SHOW);
	}

	*pResult = 0;
}

//void CChatDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}

void CChatDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 
	 
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU2));
		CPoint point;

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();
		::GetCursorPos(&point);
		pPopup->TrackPopupMenu( TPM_RIGHTALIGN  , point.x, point.y,
			pWndPopupOwner);
	
	
	
}

void CChatDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��д�����ļ�
	/*
	if(MessageBox("ȷ���˳�QQ��?", "��ʾ", MB_ICONQUESTION|MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}*/
//�����û���Ϣ��ini�ļ���
	CString filename;
		filename = "user\\user.ini";
		CFileFind filefind;
		if ( filefind.FindFile(filename,0) )//�ҵ��ļ�
		{
			CFile::Remove(filename);
		}
		CFile file;
		file.Open(filename,CFile::modeCreate | CFile::modeWrite,NULL);
		file.Close();
		if ( filefind.FindFile(filename,0) )

		{
			int  usercount =m_userlist.GetCount();
			CString tempcount;
			tempcount.Format("%d",usercount);
			
			WritePrivateProfileString(_T("usercount"),_T("count"),tempcount,filename);
			POSITION pos = m_userlist.GetHeadPosition();
			CString sectionname;
			int count = 0;
			while ( pos != NULL )
			{
				user muser = m_userlist.GetAt(pos);
				sectionname.Format("section%d",count+1);
				WritePrivateProfileString(sectionname, _T("name"),
									      muser.name  , filename);
				WritePrivateProfileString(sectionname, _T("ip"),
									muser.ip  , filename);
				CString strid;
				strid.Format("%d",muser.Iimage);
				WritePrivateProfileString(sectionname, _T("imageid"),
						                  strid  , filename);

				CString buf = "downlinedownline" ;
				m_socket.SendTo(buf,buf.GetLength(),1600,muser.ip );
				count++;
				m_userlist.GetNext (pos);

			}
		
		}
		//�ͷ���Դ
	m_userlist.RemoveAll();
	m_socket.Close();
	UnregisterHotKey(m_hWnd, 1001); 
	UnregisterHotKey(m_hWnd, 1002); 
	UnregisterHotKey(m_hWnd, 1003); 
	CDialog::OnCancel();

	
}

//void CChatDlg::OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}



//�Ҽ��˵������û���Ϣ
void CChatDlg::On140()
{
	// TODO: �ڴ���������������
	POSITION pos = m_listctrl.GetFirstSelectedItemPosition();
	int i,nItem = m_listctrl.GetNextSelectedItem(pos);
	CString name=m_listctrl.GetItemText(nItem,0);

	POSITION pos1;
	user *muser;
	pos1 = m_userlist.GetHeadPosition();
	while ( pos1 != NULL )
	{
		muser = &m_userlist.GetNext (pos1);
		if ( muser->ID ==  nItem)
		{
			break;
		}
	}

	if ( muser->ID == -1)
	{
		MessageBox("û���ҵ�");
		return;
	}

	
	
	
	CUserInfoDlg dlg;
	dlg.m_name  = muser->name;
	dlg.ip = muser->ip;
	dlg.m_curentimage = muser->Iimage ;
	
	if (dlg.DoModal() == IDOK )
	{
		muser->name = dlg.m_name;
		muser->ip = dlg.ip ;
		if (muser->pdlg == NULL)
		{
			muser->pdlg = new CMyDialog(name,this);
			muser->pdlg->ip = muser->ip;
			muser->pdlg->Create(IDD_DIALOG1,this);
		}
		muser->pdlg->ip = dlg.ip ;
		muser->pdlg->m_name = dlg.m_name;
		muser->Iimage = dlg.m_curentimage  ;
		muser->pdlg->Iimage = muser->Iimage ;
		CString strbmp;
		int flag = muser->Iimage + 1;
		strbmp.Format("face//%d.bmp",flag);

		HBITMAP hbitmap = (HBITMAP)LoadImage(NULL,strbmp,IMAGE_BITMAP,0,0,
											LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
		muser->pdlg->m_image.SetBitmap(hbitmap);

		muser->pdlg->SetWindowText("��"+dlg.m_name+"������");

	//�ֽ�ɣ�
		char iptemp[4][4];
		for (int i=0;i<4;i++)
		{
			memset(iptemp[i],'\0',4);
		}
		CString s = dlg.ip;
		char *temp = s.GetBuffer();
		char *p1=strstr(temp,".");
		*p1='\0';
		strcpy(iptemp[0],temp);
		temp = p1 + 1;

		p1=strstr(temp,".");
		*p1='\0';
		strcpy(iptemp[1],temp);
		temp = p1 + 1;

		p1=strstr(temp,".");
		*p1='\0';
		strcpy(iptemp[2],temp);
		temp = p1 + 1;

		strcpy(iptemp[3],temp);
		int ipint[4];
		for ( i=0; i < 4; i++ )
		{
			ipint[i] = atoi(iptemp[i]);
		}
		muser->pdlg->m_ip.SetAddress( ipint[0],ipint[1],ipint[2],ipint[3] );

		
		LV_ITEM item;
		item.mask = LVIF_IMAGE|LVIF_TEXT;
		item.iItem = nItem;
		item.iSubItem = 0;
		item.pszText = muser->name.GetBuffer(muser->name.GetLength());
		item.cchTextMax = muser->name.GetLength();
		item.iImage = muser->Iimage ;
		m_listctrl.SetItem(&item);
	}//ifok
		
		

}
//�յ�socket��Ϣ
void CChatDlg::OnReceive()
{
	
	char strrev[1024];
	memset(strrev,'\0',1024);
	int nresult;
	UINT port;	
	CString ipstr;

	nresult=m_socket.ReceiveFrom(strrev,sizeof(strrev),ipstr,port);


	if ( (nresult != SOCKET_ERROR) )
	{
		
		
		POSITION pos1;
		user *pmuser;
		pos1 = m_userlist.GetHeadPosition();
		while ( pos1 != NULL )
		{
			pmuser = &m_userlist.GetNext (pos1);
			if( pmuser->ip == ipstr)
			{
				break;
			}
		}

		if ( pmuser->ID == -1)
		{
			return;
		}
		//��������Ϣ
		CString onlineflag = strrev;
		if (onlineflag == "1234567890mmm")
		{
			for (int i = 0 ;i < m_listctrl.GetItemCount() ; i++ )
			{
				int id_data = m_listctrl.GetItemData(i);
				if ( pmuser->ID == id_data)
				{
					CString str = pmuser->name +"(����)";
					m_listctrl.SetItemText(i,0,str);
					return;
				}
			}
		}
		if ( onlineflag ==  "onlineonline")
		{
			CString temp ;
			temp ="��ĺ���" +pmuser->name + "������Ŷ";
			//dlg.DoModal();
			if (pdlg == NULL)
			{
				pdlg = new CInformDlg(this);
				pdlg->Create (IDD_DIALOG4,this);
				pdlg->SetWindowText(temp);
				CPoint point(700,500);
				pdlg->ClientToScreen(&point);
				pdlg->CenterWindow(this);
				pdlg->ShowWindow(SW_SHOW);
			}
			
			if ( !pdlg->IsWindowVisible() )
			{
				pdlg->SetWindowText(temp);
				CPoint point(700,500);
				pdlg->ClientToScreen(&point);
				pdlg->CenterWindow(this);
				pdlg->ShowWindow(SW_SHOW);
			}

			for (int i = 0 ;i < m_listctrl.GetItemCount() ; i++ )
			{
				int id_data = m_listctrl.GetItemData(i);
				if ( pmuser->ID == id_data)
				{
					CString str = pmuser->name +"(����)";
					m_listctrl.SetItemText(i,0,str);
					//return;
				}
			}
			
			CString send = "1234567890mmm";
			m_socket.SendTo(send,send.GetLength(),1600,pmuser->ip ,0);
			return;
		}
		if (onlineflag == "downlinedownline")
		{
			CString temp ;
			temp = "��ĺ���"+pmuser->name + "�Ѿ�������";
			if (pdlg == NULL)
			{
				pdlg = new CInformDlg(this);
				pdlg->Create (IDD_DIALOG4,this);
				pdlg->SetWindowText(temp);
				CPoint point(700,500);
				pdlg->ClientToScreen(&point);
				pdlg->CenterWindow(this);
				pdlg->ShowWindow(SW_SHOW);
			}
			
			if ( !pdlg->IsWindowVisible() )
			{
				pdlg->SetWindowText(temp);
				CPoint point(700,500);
				pdlg->ClientToScreen(&point);
				pdlg->CenterWindow(this);
				pdlg->ShowWindow(SW_SHOW);
			}
			
			for (int i = 0 ;i < m_listctrl.GetItemCount() ; i++ )
			{
				int id_data = m_listctrl.GetItemData(i);
				if ( pmuser->ID == id_data)
				{
					CString str = pmuser->name +"(������)";
					m_listctrl.SetItemText(i,0,str);
					return;
				}
			}

			return;
		}

		if (pmuser->pdlg == NULL)
		{
			pmuser->pdlg = new CMyDialog(pmuser->name,this);
			pmuser->pdlg->ip = pmuser->ip;
			pmuser->pdlg->Create(IDD_DIALOG1,this);
			pmuser->pdlg->ShowWindow(SW_SHOW);
		}
		if (!pmuser->pdlg->IsWindowVisible())
		{
			pmuser->pdlg->ShowWindow(SW_SHOW);
		}
		CString temp;
		pmuser->pdlg->m_send.GetWindowText(temp);
		if ( temp != "����Ϣ")
		{
			pmuser->pdlg->m_edit.GetWindowText(pmuser->pdlg->info);
		}
		CString str = strrev;
		CTime t=CTime::GetCurrentTime();
		CString m_time = t.Format("%Y-%m-%d %H:%M");
		pmuser->pdlg->m_listbox.InsertString(0,pmuser->name+"����˵: "+str+"  "+m_time );
		pmuser->pdlg->m_edit.SetWindowText(str);
		pmuser->pdlg->m_edit.EnableWindow(false);
		pmuser->pdlg->m_send.SetWindowText("����Ϣ");
		pmuser->pdlg->SetForegroundWindow();
		
	}
	
	
}
//ɾ������
void CChatDlg::OnDeleteUser()
{
	// TODO: �ڴ���������������

	POSITION pos = m_listctrl.GetFirstSelectedItemPosition();
	int nItem = m_listctrl.GetNextSelectedItem(pos);
	if (nItem < 0)
	{
		return;
	}
	int id=(int)m_listctrl.GetItemData(nItem);
	m_listctrl.DeleteItem(nItem);
	POSITION pos1;
	user *muser;
	pos1 = m_userlist.GetHeadPosition();
	//muser = &m_userlist.GetAt(pos1);
	while ( pos1 != NULL )
	{
		muser = &m_userlist.GetNext (pos1);
		if ( muser->ID ==  id)
		{
			if(pos1  == NULL )
			{
				pos1 = m_userlist.GetTailPosition();
			}
			else
			{
				 m_userlist.GetPrev(pos1);
			}
			 m_userlist.RemoveAt(pos1) ; 
			break;
		}
		
	}

	if ( muser->ID == -1)
	{
		MessageBox("û���ҵ�");
		return;
	}

}
//��Ӻ���
void CChatDlg::OnAddUser()
{
	// TODO: �ڴ���������������
	CUserInfoDlg dlg;
	dlg.m_name = "�ǳ�";
	dlg.ip = "192.168.0.0";
	if (dlg.DoModal() == IDOK )
	{
		user muser ;
		int id = m_listctrl.GetItemCount();
		m_listctrl.InsertItem(id,dlg.m_name,dlg.m_curentimage );
		m_listctrl.SetItemData(id,id);
		muser.ID =id;
		muser.name = dlg.m_name ;
		muser.ip = dlg.ip ;
		muser.Iimage = dlg.m_curentimage ;
		m_userlist.AddTail(muser);
	
	}
}
//�����û�
void CChatDlg::On150()
{
	OnAddUser();
}
//��ϢȺ��
void CChatDlg::OnSendToAll()
{
	// TODO: �ڴ���������������
	CSendToAllDlg dlg;
	CString strsend;
	if (dlg.DoModal() == IDOK )
	{
		strsend = dlg.m_str;
	
		POSITION pos = m_userlist.GetHeadPosition();
		CAsyncSocket * psocket = new CAsyncSocket;
		if ( psocket->Create(1601,SOCK_DGRAM,FD_READ|FD_WRITE,NULL) ==SOCKET_ERROR)
		{
			AfxMessageBox("�����׽���ʧ��");
			delete psocket;
			return;
		}
	
		while ( pos != NULL )
		{
			 user tempuser = m_userlist.GetAt(pos);
			int result = psocket->SendTo(strsend,strsend.GetLength(),1600,tempuser.ip);
		
			if ( result == SOCKET_ERROR)
			{
				CString temp ;
				temp = "���͸�" + tempuser.name + "��Ϣʧ��";
				MessageBox(temp,"����ʧ����ʾ",MB_OK);
			//delete psocket;
			//return;
			}
		
			m_userlist.GetNext(pos);
		
		}
		psocket->Close();
		delete psocket;
	}
}
//�����ȼ�
LRESULT CChatDlg::OnHotKey(WPARAM wParam,LPARAM lParam) 
{
	if (wParam == 1001||wParam == 1002)
	{
		if (hidenflag == true )
		{
			m_forhwd =::GetForegroundWindow();
			::ShowWindow(m_forhwd,SW_HIDE);
			ShowWindow(SW_HIDE);
			hidenflag = false ;
		}
		else
		{
			this->ShowWindow(SW_SHOW);
			::ShowWindow(m_forhwd,SW_SHOW);
			hidenflag = true;
			
		}

	}
	if (wParam == 1003)
	{
		HWND m_hhwd =::GetForegroundWindow();
		
		::SendMessage(m_hhwd,WM_MYMESSAGE,0,0);
		
	}
	return 0;
}

void CChatDlg::OnAbort()
{
	// TODO: �ڴ���������������
	
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
  pDC->SetBkMode(TRANSPARENT);
	HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
	return br;
	//return hbr;
}



//����onok
void CChatDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}
//����oncancel
void CChatDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnCancel();
}
//ɨ��ͣ���ַ
void CChatDlg::OnMac()
{
	// TODO: �ڴ���������������
	CMacDlg dlg;
	dlg.DoModal();

}

void CChatDlg::OnChess()
{
	// TODO: �ڴ���������������
	CChoiceKindDlg kdlg;
	if ( kdlg.DoModal() == IDOK )
	{
			CChessDlg dlg;
		if ( kdlg.machine == true )
		{
			dlg.m_and_p_flag  = true;
			
		}
		dlg.DoModal();
	}
	

	

}
