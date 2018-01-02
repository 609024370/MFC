#include "stdafx.h"
#include "Work.h"
#include "MainWin.h"
#include "Input.h"

/////////////////////////////////////////////////////////////////////////////

CWorkWin::CWorkWin()
{
	pCount=0;
	lSel=0;
	cPage=0;
	aPage=0;
	iIndex=0;
	Head=NULL;
	Tail=NULL;
	pFirst=NULL;
	pCur=NULL;
	memset(&fHead,0,sizeof(fHead));
	memcpy(&fHead,"QDB\0",4);
	fHead.rLen=sizeof(MYDATA);
	fName=_T("COMPAT.QDB");
}

CWorkWin::~CWorkWin()
{
	RECORD *xCur=Head;
	while(NULL!=Head)
	{
		Head=Head->next;
		delete xCur->Data; 
		delete xCur;
		xCur=Head;
    }
	pCur=pFirst=Head=Tail=NULL;
}


BEGIN_MESSAGE_MAP(CWorkWin,CWnd )
	//{{AFX_MSG_MAP(CWorkWin)
	ON_WM_PAINT()
	ON_COMMAND(ID_MY_LOAD, OnLoad)
	ON_COMMAND(ID_MY_SAVE, OnSave)
	ON_COMMAND(ID_MY_ADD, OnAddRecord)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_MY_MARK, OnMyMark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////

BOOL CWorkWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CWorkWin::OnPaint() 
{
	CPaintDC dc(this); 
	CMemDC xDC(&dc);
	CRect cr;
	GetClientRect(&cr);

	pCur=pFirst;
	for(int i=0;i<lSel;i++)
		pCur=pCur->next;

	CFont xFont,dFont;
	xFont.CreateFont(30,10,0,0,900,0,0,0,0,0,0,0,0,"����");
	dFont.CreateFont(20,7,0,0,0,0,0,0,0,0,0,0,0,"����");

    xDC.SetBkMode(0);
	xDC.SetTextColor(RGB(0,255,0));

	xDC.SelectObject(&xFont);
	//���Ʊ�ͷ
	xDC.FillSolidRect(CRect(20,20,80,50),RGB(60,50,50));
	xDC.DrawText("���",CRect(20,20,80,50),DT_CENTER);
	xDC.FillSolidRect(CRect(85,20,305,50),RGB(60,50,50));
	xDC.DrawText("��˾����",CRect(85,20,305,50),DT_CENTER);
	xDC.FillSolidRect(CRect(310,20,495,50),RGB(60,50,50));
	xDC.DrawText("ְλ����",CRect(310,20,495,50),DT_CENTER);
	xDC.FillSolidRect(CRect(500,20,650,50),RGB(60,50,50));
	xDC.DrawText("н��ˮƽ",CRect(500,20,650,50),DT_CENTER);
	//����ҳ��Ϣ
	CString tmp;
	tmp.Format("ҳ��: %d/%d",cPage,aPage);
    xDC.DrawText(tmp,CRect(40,670,180,700),DT_LEFT);
	//���Ʊ����
	xDC.FillSolidRect(CRect(190,670,290,700),RGB(60,50,50));
	xDC.DrawText("<<��ҳ",CRect(190,670,290,700),DT_CENTER);
	xDC.FillSolidRect(CRect(300,670,400,700),RGB(60,50,50));
	xDC.DrawText("<��һҳ",CRect(300,670,400,700),DT_CENTER);
	xDC.FillSolidRect(CRect(410,670,510,700),RGB(60,50,50));
	xDC.DrawText("��һҳ>",CRect(410,670,510,700),DT_CENTER);
	xDC.FillSolidRect(CRect(520,670,620,700),RGB(60,50,50));
	xDC.DrawText("βҳ>>",CRect(520,670,620,700),DT_CENTER);
    //����ѡ����
	if(pCur) 
		xDC.FillSolidRect(CRect(20,55+lSel*30,650,85+lSel*30),RGB(100,100,50));
    //���������嵥
     
	xDC.SelectObject(&dFont);
	RECORD *rSel=pFirst;
	for(int y=0;y<20;y++)
	{
        if(rSel==NULL) break;
		if(y==lSel) xDC.SetTextColor(RGB(255,0,0));
		else xDC.SetTextColor(RGB(255,255,150));
		tmp.Format("%04d",cPage*20-19+y);
		xDC.DrawText(tmp,CRect(20,55+y*30,80,85+y*30),DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 		xDC.DrawText(rSel->Data->name,CRect(90,55+y*30,305,85+y*30),DT_VCENTER|DT_SINGLELINE);
 		xDC.DrawText(rSel->Data->npost,CRect(315,55+y*30,495,85+y*30),DT_VCENTER|DT_SINGLELINE);
 		xDC.DrawText(rSel->Data->salary,CRect(500,55+y*30,595,85+y*30),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		if(rSel->Data->stype) tmp="Ԫ/��";
		else tmp="Ԫ/��";
 		xDC.DrawText(tmp,CRect(600,55+y*30,650,85+y*30),DT_VCENTER|DT_SINGLELINE);
        rSel=rSel->next;
	}


	
	xDC.SelectObject(&xFont);
   //���Ʒ����ǩ
	CString tStr[4]={"��\n��\n��\nϢ","��\n��\nҪ\n��","��\n˾\n��\n��","��\n��\n��\n��"};
	for(int k=0;k<4;k++)
	{
 		if(iIndex==k) 
		{
			xDC.FillSolidRect(CRect(1100,20+k*130,1130,150+k*130),RGB(180,180,100));
			xDC.SetTextColor(RGB(0,0,0));
		}
		else xDC.SetTextColor(RGB(0,255,0));
		xDC.Draw3dRect(CRect(1100,20+k*130,1130,150+k*130),RGB(100,100,100),RGB(100,100,100));
		xDC.DrawText(tStr[k],CRect(1100,20+k*130,1130,150+k*130),DT_CENTER);
	}
    //������ϸ��Ϣ
	CPen xPen(0,2,RGB(100,100,100));
	xDC.SelectObject(&xPen);
    xDC.MoveTo(670,20);
	xDC.LineTo(1130,20);
	xDC.LineTo(1130,540);
	xDC.LineTo(1100,540);
	xDC.LineTo(1100,700);
	xDC.LineTo(670,700);
	xDC.LineTo(670,20);

  //  xDC.FillSolidRect(CRect(670,20,1100,700),RGB(30,30,30));

	xDC.SetTextColor(RGB(255,255,150));
	int h;
	CString tmp2;
	if(pCur)
	{
		switch(iIndex)
		{
		case 0:	
			xDC.SelectObject(&xFont);
			tmp="";
			tmp.Format("\n%04d  ",cPage*20-19+lSel);
			for(h=0;h<pCur->Data->ls;h++)
				tmp+="��";
			tmp2.Format("\n\n����: %s",pCur->Data->name);
			tmp+=tmp2;
			tmp2.Format("\n��ַ: %s",pCur->Data->add);
			tmp+=tmp2;
			tmp2.Format("\n��ҵ: %s",pCur->Data->industry);
			tmp+=tmp2;
			tmp2.Format("\n����: %s",pCur->Data->attrib);
			tmp+=tmp2;
			tmp2.Format("\n��ģ: %s",pCur->Data->scale);
			tmp+=tmp2;
			tmp2.Format("\n��Դ: %s",pCur->Data->source);
			tmp+=tmp2;
			tmp2.Format("\n\n��ϵ: %s",pCur->Data->contact);
			tmp+=tmp2;
			tmp2.Format("\n\nְλ: %s",pCur->Data->npost);
			tmp+=tmp2;
			tmp2.Format("\nн��: %s",pCur->Data->salary);
			tmp+=tmp2;
			tmp+="\n����: ";
			if(pCur->Data->c1) tmp+="����� ";
			if(pCur->Data->c2) tmp+="��ס�� ";
			if(pCur->Data->c3) tmp+="�д�н�� ";
			tmp+="\n����: ";
			if(pCur->Data->c1) tmp+="���� ";
			if(pCur->Data->c2) tmp+="ҽ�� ";
			if(pCur->Data->c3) tmp+="���� ";
			tmp+="\n\n\n����: ";
			if(pCur->Data->end) tmp+="��Ͷ��";
			tmp2.Format("\n����: %s",pCur->Data->date);
			tmp+=tmp2;
			xDC.DrawText(tmp,CRect(680,30,1090,690),DT_LEFT|DT_WORDBREAK);
			break;
		case 1:
			xDC.SelectObject(&dFont);
			xDC.DrawText(pCur->Data->level,CRect(680,30,1090,690),DT_LEFT|DT_WORDBREAK);
			break;
		case 2:
			xDC.SelectObject(&dFont);
			xDC.DrawText(pCur->Data->introduction,CRect(680,30,1090,690),DT_LEFT|DT_WORDBREAK);
			break;
		case 3:
			xDC.SelectObject(&dFont);
			xDC.DrawText(pCur->Data->lsinfo,CRect(680,30,1090,690),DT_LEFT|DT_WORDBREAK);
			break;
		}
	}

}
BOOL CWorkWin::OnEraseBkgnd(CDC* pDC) 
{
	return true;
}


void CWorkWin::OnLoad() 
{
	FILE *fp=fopen(fName,"rb");
	if(NULL==fp)
	{
		AfxMessageBox("�ļ��򿪴���");
		return;
	}
	fread(&fHead,sizeof(fHead),1,fp);
	if(memcmp(fHead.Flag,"QDB\0",4)!=0)
	{
		AfxMessageBox("װ�����ݿ�ʧ��,���ݿ�������Ч!");
		fclose(fp);
		return;
	}
	fHead.rCount=0;
	while(1)
	{
		MYDATA  xData;
		fread(&xData,sizeof(MYDATA),1,fp);
		if(feof(fp)) break;
        AddRecord(&xData);
		fHead.rCount++;
	}
	SetPageInfo();
	fclose(fp); 
	Invalidate();
}

void CWorkWin::OnSave() 
{
	FILE *fp=fopen(fName,"wb");
	if(NULL==fp) 
	{
		AfxMessageBox("���ļ�����");
		return;
	}
    memcpy(fHead.Flag,"QDB\0",4);
	fHead.rLen=sizeof(MYDATA);

 	fwrite(&fHead,sizeof(fHead),1,fp);
   
	RECORD  *pCur=Head;
	while(pCur)
	{
		fwrite(pCur->Data,sizeof(MYDATA),1,fp);
		pCur=pCur->next;
	}	
}

void CWorkWin::OnAddRecord() 
{
	CInput in;
	if(IDOK!=in.DoModal()) return;
	AddRecord(&in.xData);
	fHead.rCount++;
	SetPageInfo();
	Invalidate();
}

void CWorkWin::AddRecord(MYDATA *pData)
{
	RECORD *p=new RECORD; 
	p->prev=NULL;
    p->next=NULL;
	MYDATA *q=new MYDATA; 
	memcpy(q,pData,sizeof(MYDATA));
	p->Data=q;

	if(NULL==Head) 
	{
		pCur=pFirst=Tail=Head=p;  
	}
	else 
	{
		p->prev=Tail;
		Tail->next=p;
		Tail=Tail->next;
	}
}


void CWorkWin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(point.x>20&&point.x<650)
	{
	   if(point.y>55&&point.y<650)
	   {
		   int item=(point.y-55)/30;
		   if(item<=pCount) 
		   {
			    lSel=item;
				pCur=pFirst;
				for(int i=0;i<lSel;i++)
					pCur=pCur->next;
				Invalidate();
		   }
		   return;
	   }	
	   if(point.y>670&&point.y<700)
	   {
		    if(point.x>190&&point.x<290) 
			{
				if(aPage) 
				{
					cPage=1;
					pFirst=Head;
					SetPageInfo();
					Invalidate();
				}
				return;
			}
		    if(point.x>300&&point.x<400) 
			{
				if(cPage>1) 
				{
					cPage--;
					for(int i=0;i<20;i++)
						pFirst=pFirst->prev;
					SetPageInfo();
					Invalidate();
				}
				return;
			}
		    if(point.x>410&&point.x<510) 
			{
				if(cPage<aPage) 
				{
					cPage++;
					for(int i=0;i<20;i++)
						pFirst=pFirst->next;
					SetPageInfo();
					Invalidate();
				}
				return;
			}
		    if(point.x>520&&point.x<700) 
			{
				if(aPage)
				{
					cPage=aPage;
					pFirst=Head;
					for(int i=0;i<cPage*20-20;i++)
						pFirst=pFirst->next;
					SetPageInfo();
					Invalidate();
				}
				return;
			}
	   }
	}
	if(point.x>1100&&point.x<1130)
	{
        int pItem=(point.y-20)/130;
		if(pItem>=0&&pItem<4) 
		{
			iIndex=pItem;
			Invalidate();
		}

	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CWorkWin::SetPageInfo()
{
	aPage=fHead.rCount/20;
	if(fHead.rCount%20) aPage++;
    if(aPage) 
	{
		if(cPage==0) cPage=1;
	    if(cPage<aPage) pCount=19;
	    else pCount=fHead.rCount%20-1;
		if(lSel>pCount) lSel=pCount;
	}
}

void CWorkWin::OnMyMark() 
{
	if(NULL==pCur) return;
	pCur->Data->end=1;
	CTime mt=CTime::GetCurrentTime();
	CString tmp=mt.Format("%Y��%m��%d��");
	memcpy(pCur->Data->date,tmp,14);
	Invalidate();
}


