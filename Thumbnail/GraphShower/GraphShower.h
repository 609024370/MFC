// GraphShower.h : GraphShower Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CGraphShowerApp:
// �йش����ʵ�֣������ GraphShower.cpp
//

class CGraphShowerApp : public CWinApp
{
public:
	CGraphShowerApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	GdiplusStartupInput m_GdiplusStartupInput;
	ULONG_PTR			m_GdiplusToken;
public:
	virtual int ExitInstance();
};

extern CGraphShowerApp theApp;