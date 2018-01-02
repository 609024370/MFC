#include "stdafx.h"
#include "windows.h"
#include "windowsx.h"
#include "Dib.h"
// Download by http://www.codefans.net
CDib::CDib()
{
	Initialize();
}

CDib::CDib(const char* fileName)
{
	Initialize();
	LoadFromFile(fileName);		//����λͼ������ʼ��
}
//��ʼ��
void CDib::Initialize()
{
	m_pBmInfo		= 0;
	m_pBmInfoHeader = 0;
	m_pRGBTable		= 0;
	m_pDibBits		= 0;
	m_bNeedPalette	= FALSE;
	m_hPalette		= NULL;
}

CDib::~CDib()
{
	Empty();
}
//��պ���
void CDib::Empty()
{
	if(m_pBmInfo)
		GlobalFreePtr(m_pBmInfo);		//�ͷ�λͼռ�õ��ڴ�
	if(m_bNeedPalette && m_hPalette)	//�ͷŵ�ɫ��
		DeleteObject(m_hPalette);
}
//���ļ�����λͼ
BOOL CDib::LoadFromFile (LPCTSTR fileName)
{
	CFile file;
	//��λͼ�ļ�
	if(file.Open(fileName, CFile::modeRead|CFile::shareDenyWrite)!=TRUE)
	{
		CString errorStr;
		errorStr.Format(_T("��%s����"), (LPCTSTR)fileName);
		AfxMessageBox(errorStr);
		file.Close();
		return FALSE;
	}
	//����λͼ�ļ�ͷ
	BITMAPFILEHEADER bmFileHeader;
	file.Read((void*)&bmFileHeader, sizeof(bmFileHeader));
	//����Ƿ���λͼ��ʶ��,�������,��ʾ������Ϣ,������
	if (bmFileHeader.bfType != 0x4d42)
	{
		CString errorStr;
		errorStr.Format("%s ����λͼ�ļ�!!!", (LPCTSTR)fileName);
		AfxMessageBox(errorStr);
		file.Close();
		return FALSE;
	}
	//����λͼ���ݵĴ�С,�����ļ�����-�ļ�ͷ����
	DWORD fileLength = file.GetLength();
	DWORD dibSize = fileLength - sizeof(bmFileHeader);
	//Ϊλͼ���ݷ����ڴ�
	BYTE* pDib = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, dibSize);
	//��λͼ���ݶ����ڴ沢�ر��ļ�
	file.Read((void*)pDib, dibSize);
	file.Close();
	//��ʼ��λͼ��Ϣͷָ���λͼ��Ϣָ��
	m_pBmInfo = (LPBITMAPINFO) pDib;
	m_pBmInfoHeader = (LPBITMAPINFOHEADER) pDib;
	//���BITMAPINFOHEADER��biSizeImage����ȷ,����
	if (m_pBmInfoHeader->biSizeImage == 0)
		m_pBmInfoHeader->biSizeImage 
			= m_pBmInfoHeader->biWidth * m_pBmInfoHeader->biHeight;
	//���biClrUsedΪ0,�Ҳ������ɫͼ,����2��biBitCount�η�,����ֱ�ӷ�������ֵ
	if(m_pBmInfoHeader->biClrUsed == 0)
		m_pBmInfoHeader->biClrUsed = DWORD(1 << m_pBmInfoHeader->biBitCount);
	//�ж��Ƿ���Ҫ��ɫ��
	if(m_pBmInfoHeader->biClrUsed <= 256)
	{
		m_bNeedPalette = TRUE;
		//������ɫ���ұ��ƫ����,������ָ�븳ֵ
		m_pRGBTable = (RGBQUAD*)(pDib + m_pBmInfoHeader->biSize);
		m_hPalette = CreateDibPalette();
	}
	//����λͼ�������ƫ����,������ָ�븳ֵ
	DWORD clrTableSize = m_bNeedPalette ? UsedColors() * sizeof(RGBQUAD) : 0;
	m_pDibBits = pDib + m_pBmInfoHeader->biSize + clrTableSize;
	return TRUE;
}
//����λͼ�Ĵ�С(�߶�*���)
DWORD CDib::ImageSize()
{
	return m_pBmInfoHeader->biSizeImage;
}
//����λͼ�Ŀ��
int CDib::Width()
{
	return m_pBmInfoHeader->biWidth;
}
//����λͼ�ĸ߶�
int CDib::Height()
{
	return m_pBmInfoHeader->biHeight;
}
//����λͼʹ�õ���ɫ��
UINT CDib::UsedColors()
{
	return (int) m_pBmInfoHeader->biClrUsed;
}
//����λͼ����Ϣͷָ��
LPBITMAPINFOHEADER CDib::GetInfoHeaderPtr()
{
	return m_pBmInfoHeader;
}
//����λͼ����Ϣ��ָ��
LPBITMAPINFO CDib::GetInfoPtr()
{
	return m_pBmInfo;
}
//����λͼ����ɫ���ұ�ָ��
LPRGBQUAD CDib::GetRGBTablePtr()
{
	return m_pRGBTable;
}
//����λͼ�ĵ�����
BYTE* CDib::GetBmBitsPtr()
{
	return m_pDibBits;
}
//�����Ƿ���Ҫ��ɫ��
BOOL CDib::NeedPalette()
{
	return m_bNeedPalette;
}
//���ص�ɫ����
HPALETTE CDib::GetDibPalette()
{
	return m_hPalette;
}
//����ͼ�������ֽ���
DWORD CDib::ImageDataSize()
{
	return (Width()*Height()*m_pBmInfoHeader->biBitCount)/8;
}
//������ɫ�壬��������
HPALETTE CDib::CreateDibPalette()
{
	//�����ɫ��
	UINT numColors = UsedColors();
	//�����߼���ɫ��
	struct
	{
		WORD Version;
		WORD NumberOfEntries;
		PALETTEENTRY aEntries[256];
	}	logicalPalette = { 0x300, 256 };
	//��RGBTable�е�����ת���ɫ����
	for(UINT i=0; i<numColors; ++i)
	{
		logicalPalette.aEntries[i].peRed	= m_pRGBTable[i].rgbRed;
		logicalPalette.aEntries[i].peGreen	= m_pRGBTable[i].rgbGreen;
		logicalPalette.aEntries[i].peBlue	= m_pRGBTable[i].rgbBlue;
		logicalPalette.aEntries[i].peFlags	= 0;
	}
	//���ɵ�ɫ����
	HPALETTE hPalette = ::CreatePalette((LPLOGPALETTE)&logicalPalette);
	return hPalette;
}
//��ʾ��ʾ��CDib��װ��λͼ��bStretchΪ�Ƿ�����
ShowDib(CDC * pDC,CDib * pDib,CRect& rect,BOOL bStretch)
{
	BYTE* pBmBits			= pDib->GetBmBitsPtr();
	LPBITMAPINFO pBmInfo	= pDib->GetInfoPtr();
	UINT bmWidth			= pDib->Width();
	UINT bmHeight			= pDib->Height();
	//�����Ƿ����죬������ʾ�ľ���
	CRect drawRect;
	if(bStretch==TRUE)
		drawRect = rect;
	else
	{
		drawRect.left = rect.left;
		drawRect.top = rect.top;
		drawRect.right = rect.left+bmWidth;
		drawRect.bottom = rect.top+bmHeight;
	}
	//�����Ҫ��ɫ�壬���ɵ�ɫ��
	HPALETTE hPalette = NULL;
	HPALETTE hOldPalette = NULL;
	if(pDib->NeedPalette())
	{
		hPalette = pDib->GetDibPalette();
		hOldPalette = SelectPalette(pDC->m_hDC,hPalette, FALSE);
		RealizePalette(pDC->m_hDC);
	}
	//ʹ��StretchDIBits��ʾ
	::StretchDIBits(pDC->m_hDC,
		drawRect.left,drawRect.top,drawRect.Width(),drawRect.Height(),
		0, 0, bmWidth, bmHeight,
		pBmBits, pBmInfo, DIB_RGB_COLORS, SRCCOPY);
	//�ͷŵ�ɫ��
	if(pDib->NeedPalette())
	{
		::SelectPalette(pDC->m_hDC,hOldPalette,FALSE);
		::DeleteObject(hPalette);
	}
	return 0;
}