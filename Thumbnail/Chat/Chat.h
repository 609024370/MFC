// Chat.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CChatApp:
// �йش����ʵ�֣������ Chat.cpp
//

class CChatApp : public CWinApp
{
public:
	CChatApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChatApp theApp;
