
// MFCOpenGL.h : ������� ���� ��������� ��� ���������� MFCOpenGL
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CMFCOpenGLApp:
// � ���������� ������� ������ ��. MFCOpenGL.cpp
//

class CMFCOpenGLApp : public CWinApp
{
public:
	CMFCOpenGLApp();


// ���������������
public:
	virtual BOOL InitInstance();

// ����������
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CMFCOpenGLApp theApp;
