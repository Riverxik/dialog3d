
// MFCOpenGL.h : главный файл заголовка для приложения MFCOpenGL
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CMFCOpenGLApp:
// О реализации данного класса см. MFCOpenGL.cpp
//

class CMFCOpenGLApp : public CWinApp
{
public:
	CMFCOpenGLApp();


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CMFCOpenGLApp theApp;
