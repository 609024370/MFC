// ScreenKeyboard.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CScreenKeyboardApp:
// �йش����ʵ�֣������ ScreenKeyboard.cpp
//

class CScreenKeyboardApp : public CWinApp
{
public:
	CScreenKeyboardApp();

// ��д
	public:
	virtual BOOL InitInstance();

	BOOL IsProgrameRunning(void);

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CScreenKeyboardApp theApp;
