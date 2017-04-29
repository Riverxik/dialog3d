#pragma once

#include "OpenGLControl.h"
// ���������� ���� COpenGLDialogDlg

class COpenGLDialogDlg : public CDialog
{
	DECLARE_DYNAMIC(COpenGLDialogDlg)

public:
	COpenGLDialogDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~COpenGLDialogDlg();

// ������ ����������� ����
	enum { IDD = IDD_DLG };

protected:
	//COpenGLControl openGLConrol;
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV
	//added code
	HICON m_hIcon;
	COpenGLControl openGLControl;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(COpenGLDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonApplyChanges();
	float length;
	float width;
	float height;
	float delta_x;
	float delta_y;
	float delta_z;
	afx_msg void OnBnClickedButtonFillIn();
};