#ifndef _DIB_H
#define _DIB_H

//������ʾBMP��CDib��
class CDib: public CObject
{
public:
	CDib();
	CDib(const char* fileName);				//���ļ���Ϊ�����Ĺ��캯��
	~CDib();
	BOOL LoadFromFile(LPCTSTR fileName);	//���ļ�����λͼ

	DWORD ImageSize();						//���λͼ��ʵ�ʴ�С
	int Width();							//���λͼ�Ŀ��
	int Height();							//���λͼ�ĸ߶�
	UINT UsedColors();						//���λͼ�õ�����ɫ��
	
	LPBITMAPINFOHEADER GetInfoHeaderPtr();	//�����Ϣͷָ��
	LPBITMAPINFO GetInfoPtr();				//�����Ϣָ��
	LPRGBQUAD GetRGBTablePtr();				//�����ɫ���ұ�ָ��
	BYTE* GetBmBitsPtr();					//��õ������ָ��

	BOOL NeedPalette();						//�����Ƿ���Ҫ��ɫ��
	HPALETTE GetDibPalette();				//����λͼ�ĵ�ɫ��
private:
	void Initialize();						//��ʼ������
	void Empty();							//��պ���
	DWORD ImageDataSize();					//����ͼ�������ֽ���
	HPALETTE CreateDibPalette();			//������ɫ�壬��������
private:
	LPBITMAPINFO m_pBmInfo;					//λͼ��Ϣָ��
	LPBITMAPINFOHEADER m_pBmInfoHeader;		//λͼ��Ϣͷָ��
	RGBQUAD * m_pRGBTable;					//λͼ��ɫ���ұ�ָ��
	BYTE * m_pDibBits;						//λͼ������
	BOOL m_bNeedPalette;					//λͼ�Ƿ���Ҫ��ɫ��
	HPALETTE m_hPalette;					//λͼ�ĵ�ɫ��
};

//��ʾ��CDib��װ��λͼ
ShowDib(CDC * pDC,CDib * pDib,CRect& rect,BOOL bStretch=TRUE);

#endif
