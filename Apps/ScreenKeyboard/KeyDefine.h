#pragma once

struct KEYDEF
{
	char cNormal;	 //�ַ���
	char cShifted;	 //shift����ʱ��ֵ
	int  cWidth;  //ͼ���С
	CRect rect;
	bool bHighlight;
};


#define TAB 0x02
#define CAPSLOCK 0x03
#define SHIFT 0x04
#define CTRL 0x05
#define BSPACE 0x06
#define ENTER 0x07
#define ALT 0x08
#define WINDOW 0x9
#define LEFT 0x0A
#define RIGHT 0x0B
#define UP 0x0C
#define DOWN 0x0D
#define ESC 0x0E
#define PUP 0x0F
#define PDN 0x10
#define HOME 0x11
#define END 0x12
#define INS 0x13
#define DEL 0x14
