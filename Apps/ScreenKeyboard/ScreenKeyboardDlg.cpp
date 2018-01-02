// ScreenKeyboardDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScreenKeyboard.h"
#include "ScreenKeyboardDlg.h"
//#include "TraceWin.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define HIGHLIGHTTEXTCOLOR  RGB(255,200,0)
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


// CScreenKeyboardDlg �Ի���



CScreenKeyboardDlg::CScreenKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScreenKeyboardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenKeyboardDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_DESTROY()
	ON_WM_NCHITTEST()
	ON_WM_ACTIVATE()
	ON_WM_SETFOCUS()
	ON_WM_NCACTIVATE()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CScreenKeyboardDlg ��Ϣ�������

BOOL CScreenKeyboardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//���ô�������

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

	LOGFONT temp;
	memset(&temp, 0, sizeof(LOGFONT));       // zero out structure
	temp.lfHeight = 18;                      // request a 12-pixel-height font
	temp.lfWeight = 800;
	strcpy(temp.lfFaceName, "Arial");        // request a face name "Arial"
	VERIFY(m_TextFont.CreateFontIndirect(&temp));  // create the font
    
	FillBkBrushColor();

	gFocus = NULL;

	AddKey(0x00,0x00,0); //signal row change
	AddKey(0x00,ESC,10);
	for(int fnkey = 0x70; fnkey < 0x7C; fnkey++)
	{
		AddKey(0x00,fnkey & 0xFF,10);
	}
	AddKey(0x00,INS,14);
	AddKey(0x00,DEL,-10);

	//first row
	AddKey(0x00,0x00,1); //signal row change
	AddKey('`','~',10);
	AddKey('1','!',10);
	AddKey('2','@',10);
	AddKey('3','#',10);
	AddKey('4','$',10);
	AddKey('5','%',10);
	AddKey('6','^',10);
	AddKey('7','&',10);
	AddKey('8','*',10);
	AddKey('9','(',10);
	AddKey('0',')',10);
	AddKey('-','_',10);
	AddKey('=','+',10);
	AddKey(0x00,BSPACE,14); //backspace
	AddKey(0x00,PUP,-12);

	//second row
	AddKey(0x00,0x00,2); //signal row change
	AddKey(0x00,TAB,14); //tab
	AddKey('q','Q',10);
	AddKey('w','W',10);
	AddKey('e','E',10);
	AddKey('r','R',10);
	AddKey('t','T',10);
	AddKey('y','Y',10);
	AddKey('u','U',10);
	AddKey('i','I',10);
	AddKey('o','O',10);
	AddKey('p','P',10);
	AddKey('[','{',10);
	AddKey(']','}',10);
	AddKey('\\','|',10);
	AddKey(0x00,PDN,-12);

	//third row
	AddKey(0x00,0x00,3); //signal row change
	AddKey(0x00,CAPSLOCK,18); //caps lock
	AddKey('a','A',10);
	AddKey('s','S',10);
	AddKey('d','D',10);
	AddKey('f','F',10);
	AddKey('g','G',10);
	AddKey('h','H',10);
	AddKey('j','J',10);
	AddKey('k','K',10);
	AddKey('l','L',10);
	AddKey(';',':',10);
	AddKey('\'','\"',10);
	AddKey(0x00,ENTER,16); //enter
	AddKey(0x00,HOME,-10);

	//fourth row
	AddKey(0x00,0x00,4); //signal row change
	AddKey(0x00,SHIFT,22); //shift
	AddKey('z','Z',10);
	AddKey('x','X',10);
	AddKey('c','C',10);
	AddKey('v','V',10);
	AddKey('b','B',10);
	AddKey('n','N',10);
	AddKey('m','M',10);
	AddKey(',','<',10);
	AddKey('.','>',10);
	AddKey('/','?',10);
	AddKey(0x00,SHIFT,22); //shift
	AddKey(0x00,END,-10);

	AddKey(0x00,0x00,5); //signal row change
	AddKey(0x00,CTRL,12); //ctrl
	AddKey(0x00,WINDOW,12); //window
	AddKey(0x00,ALT,12); //alt
	AddKey(' ',' ',76);
	AddKey(0x00,LEFT,12); //left
	AddKey(0x00,UP,12); //up
	AddKey(0x00,DOWN,12); //down
	AddKey(0x00,RIGHT,-12); //right

	CalcWidthHeight();  //���㴰���а�����С
	CalKeyRect();  //����ÿһ��������λ��

	SetWindowPos(&wndTopMost, 0, 0, 0, 0,  //�Ѵ��ڷŵ����
		SWP_NOSIZE | SWP_NOMOVE);

	//HGLOBAL hMem = GlobalAlloc(GPTR, 50); 
	//char *lpMem = (char *)GlobalLock(hMem); 
	//lstrcpy(lpMem, theApp.m_pszExeName); 
	//GlobalUnlock(hMem); 
	//SetProp(m_hWnd, "PROP_EXE_NAME",hMem); 

	::SetProp(m_hWnd, AfxGetApp()->m_pszExeName, (HANDLE)1);  //����ʹ�ó���ֻ����һ��ʵ��
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CScreenKeyboardDlg::CalcWidthHeight()
{
	pKeyWidth = 0;
	pKeyHeight = 0;
	KEYDEF * key;
	POSITION pos = cKeys.GetHeadPosition();
	long totalWidth = 0;
	long longest = 0;
	long rows = 0;
	while(pos)
	{
		key = cKeys.GetNext(pos);
		if((key->cNormal == 0x00) && (key->cShifted == 0x00))
		{
			rows++;
			if(totalWidth > longest)
			{
				longest = totalWidth;
			}
			totalWidth = 0;
		}
		else
		{
			totalWidth += abs(key->cWidth);
		}
	}
	CRect rect;
	GetClientRect(rect);
	pKeyHeight = rect.Height() / rows;
	pKeyWidth = (int)(((double)rect.Width()) / ((((double)(longest)) / 10)));
}

void CScreenKeyboardDlg::AddKey(char pNormal,  char pShifted, int pWidth)
{
	KEYDEF * key = new KEYDEF;
	key->cNormal = pNormal;
	key->cShifted = pShifted;
	key->cWidth = pWidth;
	key->bHighlight=false;
	cKeys.AddTail(key);
}

void CScreenKeyboardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScreenKeyboardDlg::DrawKey(CDC * dc, KEYDEF * key)
{
	CString label = " ";
	BOOL special = FALSE;
	CRect rc = key->rect;

	if(key->cNormal==0x00 && key->cShifted==0x00)
		return ;

	COLORREF OldColor = dc->GetTextColor() ;
	CPen Pen, TextPen;
	CPen *pOldPen = NULL ;
	if(!key->bHighlight)  //û�и�����ʾ
	{
		rc.DeflateRect(1,1);
		DoGradientFill(dc,&rc);
//		dc->FillSolidRect(rc,GetSysColor(COLOR_3DFACE));
		dc->Draw3dRect(rc,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DDKSHADOW));
		rc.DeflateRect(1,1);
		dc->Draw3dRect(rc,GetSysColor(COLOR_3DLIGHT),GetSysColor(COLOR_3DSHADOW));
	}
	else
	{
		rc.DeflateRect(1,1);
		dc->FillSolidRect(rc,RGB(0x20,0xff,0x99));  //����������ʱ�������ɫ
		dc->Draw3dRect(rc,GetSysColor(COLOR_3DLIGHT),GetSysColor(COLOR_3DSHADOW));
		rc.DeflateRect(1,1);
		dc->Draw3dRect(rc,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DDKSHADOW));
		dc->SetTextColor(HIGHLIGHTTEXTCOLOR) ;
		Pen.CreatePen(PS_SOLID,1,HIGHLIGHTTEXTCOLOR) ;
		pOldPen = dc->SelectObject(&Pen) ;
	}

	rc.DeflateRect(3,1);

	CFont *pOldFont=dc->SelectObject(&m_TextFont);		//������������ɫ�ʹ�С
	dc->SetTextColor(RGB(0x88,0x22,0x11));
	TextPen.CreatePen(PS_SOLID,2,RGB(0x88,0x22,0x11)) ; //���Ʒ��������ɫ�ʹ�С
	pOldPen = dc->SelectObject(&TextPen) ;

	if(key->cNormal == 0x00)
	{

		if(key->cShifted > 0x6F) //is a function
		{
			int fkeynum = key->cShifted - 0x6F;
			label.Format("F%d",fkeynum);
		}
		else
		{
			switch(key->cShifted)
			{
			case TAB:    // 0x02
				label = "Tab";
				break;
			case CAPSLOCK:    // 0x03
				label = "Caps";
				break;
			case SHIFT:    // 0x04
				label = "Shift";
				break;
			case CTRL:    // 0x05
				label = "Ctrl";
				break;
			case BSPACE:    // 0x06
				label = "Bspc";
				break;
			case ENTER:    // 0x07
				label = "Enter";
				break;
			case ALT:    // 0x08
				label = "Alt";
				break;
			case WINDOW:    // 0x9
				label = "Wnd";
				break;
			case ESC:
				label = "Esc";
				break;
			case LEFT:    // 0x0A
				special = TRUE;
				{
					int cx = (rc.left + rc.right)/2;
					int cy = (rc.top + rc.bottom)/2;
					int siz = rc.Width()/3;
					dc->MoveTo(cx+siz, cy);
					dc->LineTo(cx-siz, cy);
					dc->LineTo(cx-siz + (siz*4)/5, cy - siz/2);
					dc->MoveTo(cx-siz, cy);
					dc->LineTo(cx-siz + (siz*4)/5, cy + siz/2);
				}
				break;
			case RIGHT:    // 0x0B
				special = TRUE;
				{
					int cx = (rc.left + rc.right)/2;
					int cy = (rc.top + rc.bottom)/2;
					int siz = rc.Width()/3;
					dc->MoveTo(cx-siz, cy);
					dc->LineTo(cx+siz, cy);
					dc->LineTo(cx+siz - (siz*4)/5, cy - siz/2);
					dc->MoveTo(cx+siz, cy);
					dc->LineTo(cx+siz - (siz*4)/5, cy + siz/2);
				}
				break;
			case UP:    // 0x0C
				special = TRUE;
				{
					int cx = (rc.left + rc.right)/2;
					int cy = (rc.top + rc.bottom)/2;
					int siz = rc.Width()/3;
					dc->MoveTo(cx, cy+siz);
					dc->LineTo(cx, cy-siz);
					dc->LineTo(cx - siz/2, cy-siz + (siz*4)/5);
					dc->LineTo(cx, cy-siz);
					dc->LineTo(cx + siz/2, cy-siz + (siz*4)/5);
				}
				break;
			case DOWN:    // 0x0D
				special = TRUE;
				{
					int cx = (rc.left + rc.right)/2;
					int cy = (rc.top + rc.bottom)/2;
					int siz = rc.Width()/3;
					dc->MoveTo(cx, cy-siz);
					dc->LineTo(cx, cy+siz);
					dc->LineTo(cx - siz/2, cy+siz - (siz*4)/5);
					dc->LineTo(cx, cy+siz);
					dc->LineTo(cx + siz/2, cy+siz - (siz*4)/5);
				}
				break;
			case PUP: //0x0F
				label = "PgUp";
				break;
			case PDN: //0x10
				label = "PgDn";
				break;
			case HOME: //0x11
				label = "Home";
				break;
			case END: //0x12
				label = "End";
				break;
			case INS: //0x13
				label = "Ins";
				break;
			case DEL: //0x14
				label = "Del";
				break;
			default:
				ASSERT(FALSE);
				label = "#ERR#";
				break;
			}
		}
		if(!special)
		{
			CSize tsize;
			tsize = dc->GetTextExtent(label);
			dc->TextOut(
				((rc.left + rc.right)/2) - (tsize.cx/2), 
				((rc.top + rc.bottom)/2) - (tsize.cy/2), 
				label);
		}
	}
	else
	{
		if((key->cShifted >= 'A') && (key->cShifted <= 'Z'))
		{
			CSize tsize;
			label.Format("%c",key->cShifted);
			tsize = dc->GetTextExtent(label);
			dc->TextOut(
				((rc.left + rc.right)/2) - (tsize.cx/2), 
				((rc.top + rc.bottom)/2) - (tsize.cy/2), 
				label);
		}
		else
		{
			CSize tsize;
			tsize = dc->GetTextExtent("M");
			label.Format("%c",key->cShifted);
			dc->TextOut(rc.left, rc.top, label);
			label.Format("%c",key->cNormal);
			dc->TextOut(
				rc.right - tsize.cx, 
				rc.bottom - tsize.cy,
				label);
		}
	}
	dc->SetTextColor(OldColor) ;
	dc->SelectObject(pOldFont);
	if(pOldPen)
		dc->SelectObject(pOldPen) ;
}


// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CScreenKeyboardDlg::OnPaint() 
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
		DrawKeyboard();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CScreenKeyboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//********************************************************
// �������� ���������л���ʱ�򣬱��浱ǰ�������뽹�㴰�ھ��
// ��ڲ��� ��
//
// ���ز��� ��
//
// �������� �� 2005-1-26 16:54:20
// ����     �� ���     Mail: yangkui@seu.edu.cn
//********************************************************
BOOL CScreenKeyboardDlg::PreTranslateMessage(MSG* pMsg)
{
	HWND wnd = ::GetForegroundWindow();
	if(IsWindow(wnd))
	{
		if(wnd != this->m_hWnd)
		{
			if(gFocus != wnd)
			{
				if(IsWindow(gFocus))
				{
					AttachThreadInput(
						GetCurrentThreadId(),
						GetWindowThreadProcessId(gFocus,NULL),
						FALSE);
				}

				gFocus = wnd;
				AttachThreadInput(
					GetCurrentThreadId(),
					GetWindowThreadProcessId(gFocus,NULL),
					TRUE);
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CScreenKeyboardDlg::ReleaseFocus() 
{
	if(IsWindow(gFocus))
	{
		HWND wnd = ::GetForegroundWindow();
		if(IsWindow(wnd))
		{
			if(wnd == gFocus)
			{
				return;
			}
		}
		::SetForegroundWindow(gFocus);
	}
}

void CScreenKeyboardDlg::PostNcDestroy()
{
	CDialog::PostNcDestroy();
}

BOOL CScreenKeyboardDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	return CDialog::PreCreateWindow(cs);
}

//********************************************************
// �������� ���Ѱ����������͵�ָ��������ȥ
// ��ڲ��� ��
//
// ���ز��� ��
//
// �������� �� 2005-1-26 20:18:23
// ����     �� ���     Mail: yangkui@seu.edu.cn
//********************************************************
void CScreenKeyboardDlg::SendKey(KEYDEF * keydef)
{
	if(keydef->cNormal == 0x00)
	{
		int vk;
		BOOL uptoo = TRUE;
		if(keydef->cShifted > 0x6F) //is a function key
		{
			vk = keydef->cShifted;
		}
		else
		{
			switch(keydef->cShifted)  //�жϹ��ܼ�������
			{
			case TAB:    // 0x02
				vk = VkKeyScan(0x09) & 0xFF;
				break;
			case CAPSLOCK:    // 0x03
				vk = VK_CAPITAL;
				break;
			case SHIFT:    // 0x04
				vk = VK_SHIFT;
				if(GetKeyState(vk) & 0xF000) //shift �Ѿ�����
				{
					vk = VK_CONTROL;
					if(GetKeyState(vk) & 0xF000) //ctrl Ҳ����
					{
						vk = VK_SHIFT;
						keybd_event(vk,0,0,0);
					}
					vk = VK_SHIFT;
					keybd_event(vk,0,KEYEVENTF_KEYUP,0);
					return;
				}
				uptoo = FALSE;   //����shift״̬
				break;
			case CTRL:    // 0x05
				vk = VK_CONTROL;
				if(GetKeyState(vk) & 0xF000)   //ctrl�Ѿ���С
				{
					vk = VK_SHIFT;
					if(GetKeyState(vk) & 0xF000) //shift Ҳ����
					{
						vk = VK_CONTROL;
						keybd_event(vk,0,0,0);
					}
					vk = VK_CONTROL;
					keybd_event(vk,0,KEYEVENTF_KEYUP,0);
					return;
				}
				uptoo = FALSE;   //����ctrl״̬
				break;
			case BSPACE:    // 0x06
				vk = VK_BACK;
				break;
			case ENTER:    // 0x07
				vk = VkKeyScan(0x0D) & 0xFF;
				break;
			case ALT:    // 0x08
				vk = VK_MENU;
				break;
			case WINDOW:    // 0x9
				vk = VK_LWIN;
				break;
			case LEFT:    // 0x0A
				vk = VK_LEFT;
				break;
			case RIGHT:    // 0x0B
				vk = VK_RIGHT;
				break;
			case UP:    // 0x0C
				vk = VK_UP;
				break;
			case DOWN:    // 0x0D
				vk = VK_DOWN;
				break;
			case PUP: //0x0F
				vk = VK_PRIOR;
				break;
			case PDN: //0x10
				vk = VK_NEXT;
				break;
			case HOME: //0x11
				vk = VK_HOME;
				break;
			case END: //0x12
				vk = VK_END;
				break;
			case INS: //0x13
				vk = VK_INSERT;
				break;
			case DEL: //0x14
				vk = VK_DELETE;
				break;
			default:
				ASSERT(FALSE);
				break;
			}
		}
		keybd_event(vk,0,0,0);
		if(uptoo)
		{
			keybd_event(vk,0,KEYEVENTF_KEYUP,0);
		}
	}
	else
	{
		char pChar = keydef->cNormal;
		SHORT ks = VkKeyScan(pChar);
		BYTE key = ks & 0xFF;

		keybd_event(key,0,0,0);
		keybd_event(key,0,KEYEVENTF_KEYUP,0);

		//turn off the control and shift if they were down
		unsigned char vk = VK_SHIFT;
		if(GetKeyState(vk) & 0xF000)
		{
			keybd_event(vk,0,KEYEVENTF_KEYUP,0);
		}
		vk = VK_CONTROL;
		if(GetKeyState(vk) & 0xF000) //allow toggle
		{
			keybd_event(vk,0,KEYEVENTF_KEYUP,0);
		}
	}
}

//********************************************************
// �������� ����ȡ��ǰshift��ctrl��caps��״̬
// ��ڲ��� ����
//
// ���ز��� �������һλΪ1��ʾcapital���£�����ڶ�λΪ1��ʾshift����
//				�������λ���µĻ�����ʾcontrol����
// �������� �� 2005-1-26 20:18:55
// ����     �� ���     Mail: yangkui@seu.edu.cn
//********************************************************
int CScreenKeyboardDlg::DescribeKeyState() 
{
	int state = 0;
	short ks;
	ks = GetKeyState(VK_CAPITAL);
	if(ks & 0x000F) state += 0x01;
	ks = GetKeyState(VK_SHIFT);
	if(ks & 0xF000) state += 0x02;
	ks = GetKeyState(VK_CONTROL);
	if(ks & 0xF000) state += 0x04;
	return state;
}
//********************************************************
// �������� ���������еİ���
// ��ڲ��� ��
//
// ���ز��� ��
//
// �������� �� 2005-1-26 20:20:56
// ����     �� ���     Mail: yangkui@seu.edu.cn
//********************************************************
void CScreenKeyboardDlg::DrawKeyboard()
{
	CClientDC dc(this);
	CRect client;
	GetClientRect(client);
	CRgn clipRgn;
	clipRgn.CreateRectRgnIndirect(&client);
	dc.SelectClipRgn(&clipRgn);
	dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	dc.SetBkMode(TRANSPARENT);
	KEYDEF * key;
	POSITION pos = cKeys.GetHeadPosition();
	cCurrentKeyState = DescribeKeyState();
	int state = cCurrentKeyState;
	while(pos)
	{
		key = cKeys.GetNext(pos);
		if(key->cNormal == 0x00)
		{
			switch(key->cShifted)
			{
			case CAPSLOCK:
				key->bHighlight = false;
				if(state & 0x01)
				{
					key->bHighlight = true;
				}
				break;
			case SHIFT:
				key->bHighlight = false;
				if(state & 0x02)
				{
					key->bHighlight = true;
				}
				break;
			case CTRL:
				key->bHighlight = false;
				if(state & 0x04)
				{
					key->bHighlight = true;
				}
				break;
			default:
				break;
			}
		}
		DrawKey(&dc,key);
	}
}

// ���㰴���ľ�������
void CScreenKeyboardDlg::CalKeyRect(void)
{
	CRect client;
	GetClientRect(client);
	int x = 0;
	int y = -pKeyHeight;
	KEYDEF * key;
	POSITION pos = cKeys.GetHeadPosition();
	while(pos)
	{
		key = cKeys.GetNext(pos);
		if((key->cNormal == 0x00) && (key->cShifted == 0x00))
		{
			x = 0;
			y += pKeyHeight;
		}
		else
		{
			int width = ((abs(key->cWidth) * pKeyWidth) / 10);
			CRect rc(x,y,x + width, y + pKeyHeight);
			if(key->cWidth < 0)
			{
				rc.right = client.right;
			}
			x+= width;
			key->rect=rc;
		}
	}
}

void CScreenKeyboardDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	ReleaseFocus();
	CClientDC dc(this);
	dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	dc.SetBkMode(TRANSPARENT);
	KEYDEF * key;
	POSITION pos = cKeys.GetHeadPosition();
	cCurrentKeyState = DescribeKeyState();
	int state = cCurrentKeyState;
	while(pos)
	{
		key = cKeys.GetNext(pos);
		if(key->rect.PtInRect(point))  //����ڰ�����
		{
			if(key->bHighlight!=true)
			{
				key->bHighlight=true;	
				DrawKey(&dc,key);
			}
		}
		else if(key->bHighlight==true)  //������������Ҳ���Ļ�
		{
			if(key->cNormal == 0x00) //�ж��ǲ���shift,ctrl,caps
			{
				switch(key->cShifted)
				{
				case CAPSLOCK:
					if(!(state & 0x01))  //���ݵ�ǰ״̬��Ӧ������
					{
						key->bHighlight = false;  //�ص�
						DrawKey(&dc,key);
					}
					break;
				case SHIFT:
					if(!(state & 0x02))  //��Ӧ������
					{
						key->bHighlight = false;  //�ص�
						DrawKey(&dc,key);
					}
					break;
				case CTRL:
					if(!(state & 0x04))  //��Ӧ������
					{
						key->bHighlight = false;  //�ص�
						DrawKey(&dc,key);
					}	
					break;
				default:
					key->bHighlight = false;  //�������ܼ��ص�
					DrawKey(&dc,key);
					break;
				}
			}
			else
			{
				key->bHighlight = false;  //���ǹ��ܼ��ص�
				DrawKey(&dc,key);
			}
		}
	}
}

void CScreenKeyboardDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(IsWindow(gFocus))
	{
		::SetActiveWindow(gFocus);
	}
	return;
}

void CScreenKeyboardDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseFocus();

	CClientDC dc(this);
	dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	dc.SetBkMode(TRANSPARENT);
	KEYDEF * key;
	POSITION pos = cKeys.GetHeadPosition();
	while(pos)
	{
		key = cKeys.GetNext(pos);
		if(key->rect.PtInRect(point))
		{
			SendKey(key);
			DrawKey(&dc,key);
			return;
		}
	}
}

void CScreenKeyboardDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnLButtonDown(nFlags, point);
}

void CScreenKeyboardDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	OnLButtonDown(nFlags, point);
}

void CScreenKeyboardDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	OnLButtonUp(nFlags, point);
}

void CScreenKeyboardDlg::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	OnLButtonDown(nFlags, point);
}

BOOL CScreenKeyboardDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
//	ReleaseFocus();
	return TRUE;
}

//********************************************************
// �������� ��������ʱ���ͷ����еĹ��ܰ�ť״̬
// ��ڲ��� ��
//
// ���ز��� ��
//
// �������� �� 2005-1-26 20:21:18
// ����     �� ���     Mail: yangkui@seu.edu.cn
//********************************************************
void CScreenKeyboardDlg::OnClose()
{
	
	CDialog::OnClose();
}


void CScreenKeyboardDlg::OnDestroy()
{
	CDialog::OnDestroy();

	FreeBkBrushColor();

	POSITION pos = cKeys.GetHeadPosition();
	while(pos)
	{
		delete cKeys.GetNext(pos);
	}
	int state = DescribeKeyState();
	if(state & 0x01) keybd_event(VK_CAPITAL,0,KEYEVENTF_KEYUP,0);
	if(state & 0x02) keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
	if(state & 0x04) keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
}
	
/*
�⼸�����������������μ��̶Ի��򱻼���
����ȥ��ԭ��������Ϣ������˸������
*/
void CScreenKeyboardDlg::OnSetFocus(CWnd* pOldWnd)
{
	CDialog::OnSetFocus(pOldWnd);
}

UINT CScreenKeyboardDlg::OnNcHitTest(CPoint point)
{
	return CDialog::OnNcHitTest(point);
}

void CScreenKeyboardDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if(nState==WA_CLICKACTIVE && pWndOther!=NULL)
	{
		::SetActiveWindow(pWndOther->GetSafeHwnd());
		return;
	}

	CDialog::OnActivate(nState, pWndOther, bMinimized);
}

BOOL CScreenKeyboardDlg::OnNcActivate(BOOL bActive)
{
	return CDialog::OnNcActivate(bActive);
}

//�ص����������������-1��ʱ�򣬴��ڲ�����˸
int CScreenKeyboardDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return MA_NOACTIVATE ;  
	//	return CDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
}



//��ʼ����ť������ɫ����
void CScreenKeyboardDlg::FillBkBrushColor()
{
	for (int i = 0; i < 64; i ++)
	{
		m_BTBkColor[i].CreateSolidBrush(RGB(255 - (i / 4) , 255 - (i*2), 255-(i*3)));
	}
}

//�ͷű�����ɫ����
void CScreenKeyboardDlg::FreeBkBrushColor()
{
	for (int i = 0; i < 64; i ++)
		m_BTBkColor[i].DeleteObject();
}

//���ƽ���İ�ť��״
void CScreenKeyboardDlg::DoGradientFill(CDC *pDC, CRect* rect)
{
	CRect rct;

	int nWidth = rect->Width();	
	int nHeight = rect->Height();

	for (int i = rect->top; i <= rect->bottom; i++) 
	{
		rct.SetRect(rect->left, i, rect->right, i + 1);
		pDC->FillRect(&rct, &m_BTBkColor[((i-rect->top)*63) / nHeight]);
	}

}
