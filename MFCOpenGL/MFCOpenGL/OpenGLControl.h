#pragma once
#include "afxwin.h"

#include <gl/gl.h>
#include <gl/glu.h>

class COpenGLControl : public CWnd
{
	public:
		/******************/
		/* Public Members */
		/******************/
		UINT_PTR m_unpTimer;
		// View information variables
		float	 m_fLastX;
		float	 m_fLastY;
		float	 m_fPosX;
		float	 m_fPosY;
		float	 m_fZoom;
		float	 m_fRotX;
		float	 m_fRotY;
		bool	 m_bIsMaximized;

		// Draw information
		float	 m_start_x;		// ��������� ����� �� ��� X
		float	 m_start_y;		// ��������� ����� �� ��� Y
		float	 m_start_z;		// ��������� ����� �� ��� Z
		float	 m_length;		// ����� �������
		float	 m_width;		// ������ �������
		float	 m_height;		// ������ �������
		float	 m_scale;		// ����������� ����������

		// Massive of Vertex
		GLfloat cubeVertexArray[8][3];	// ������ ������ ����-����
		GLfloat cubeColorArray[8][3];	// ������ ������ ������
		GLubyte cubeIndexArray[6][4];	// ������ ������ ����-����

	private:
		/*******************/
		/* Private Members */
		/*******************/
		// Window information
		CWnd  *hWnd;
		HDC   hdc;			
		HGLRC hrc;			
		int   m_nPixelFormat;
		CRect m_rect;
		CRect m_oldWindow;
		CRect m_originalRect;
		GLUquadricObj* m_Obj[8]; //��� ����

	public:
		COpenGLControl(void);
		virtual ~COpenGLControl(void);

		void oglCreate(CRect rect, CWnd *parent);//��������
		void oglInitialize(void);				// �������������
		void oglDrawScene(void);				// ���������
		void oglFillIn(void);					// ����������
		void oglRecalculate(void);				// �������������� ��������� (��� ���������)
		int RetrieveObjectID(int x, int y);		// ���������� � ����� ������ ������ (���������� ����� ���)

		// Added message classes:
		afx_msg void OnPaint();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg	void OnDraw(CDC *pDC);
		afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnTimer(UINT nIDEvent);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

		DECLARE_MESSAGE_MAP()
		afx_msg void OnBnClickedButtonApplyChanges();
};