// DemoListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DemoList.h"
#include "DemoListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDemoListDlg �Ի���




CDemoListDlg::CDemoListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoListDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CDemoListDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDemoListDlg ��Ϣ�������

BOOL CDemoListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_ListCtrl.SetColColor(0,RGB(10,150,20)); //�����б���ɫ
	m_ListCtrl.SetColColor(2,RGB(30,100,90)); //�����б���ɫ
	m_ListCtrl.SetBkColor(RGB(50,10,10));        //���ñ���ɫ
	m_ListCtrl.SetItemColor(1,1,RGB(100,100,10)); //����ָ����Ԫ����ɫ
	m_ListCtrl.SetRowHeigt(25);               //�����и߶�
	m_ListCtrl.SetHeaderHeight(1.5);          //����ͷ���߶�
	m_ListCtrl.SetHeaderFontHW(16,0);         //����ͷ������߶�,�Ϳ��,0��ʾȱʡ������Ӧ 
	m_ListCtrl.SetHeaderTextColor(RGB(255,200,100)); //����ͷ��������ɫ
	m_ListCtrl.SetTextColor(RGB(0,255,255));  //�����ı���ɫ
	m_ListCtrl.SetHeaderBKColor(100,255,100,8); //����ͷ������ɫ
	m_ListCtrl.SetFontHW(15,0);               //��������߶ȣ��Ϳ��,0��ʾȱʡ���
	m_ListCtrl.SetColTextColor(2,RGB(255,255,100)); //�������ı���ɫ
	m_ListCtrl.SetItemTextColor(3,1,RGB(255,0,0));  //���õ�Ԫ��������ɫ

	m_ListCtrl.InsertColumn(0,_T("����"),LVCFMT_CENTER,55);
	m_ListCtrl.InsertColumn(1,_T("���"),LVCFMT_CENTER,60);
	m_ListCtrl.InsertColumn(2,_T("����"),LVCFMT_CENTER,60);
	m_ListCtrl.InsertColumn(3,_T("����ʱ��"),LVCFMT_CENTER,180);

	m_ListCtrl.InsertItem(0,"����");
	m_ListCtrl.SetItemText(0,1,"178CM");
	m_ListCtrl.SetItemText(0,2,"70KG");
	m_ListCtrl.SetItemText(0,3,"2009��1��15��23ʱ40��");

	m_ListCtrl.InsertItem(1,"����");
	m_ListCtrl.SetItemText(1,1,"178cm");
	m_ListCtrl.SetItemText(1,2,"70kg");
	m_ListCtrl.SetItemText(1,3,"2009��1��15��23ʱ40��");

	m_ListCtrl.InsertItem(2,"����");
	m_ListCtrl.SetItemText(2,1,"168cm");
	m_ListCtrl.SetItemText(2,2,"60kg");
	m_ListCtrl.SetItemText(2,3,"2009��1��15��23ʱ40��");

	SetWindowLong(m_ListCtrl.m_hWnd ,GWL_EXSTYLE,WS_EX_CLIENTEDGE);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);                     //������չ���Ϊ����
	::SendMessage(m_ListCtrl.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDemoListDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoListDlg::OnPaint()
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
//
HCURSOR CDemoListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

