
// MFCOpenGLView.cpp : реализация класса CMFCOpenGLView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MFCOpenGL.h"
#endif

#include "MFCOpenGLDoc.h"
#include "MFCOpenGLView.h"
#include "OpenGLDialogDlg.h"

#include <GL/GL.h>
#include <GL/GLU.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int choice = 0;

// CMFCOpenGLView

IMPLEMENT_DYNCREATE(CMFCOpenGLView, CView)

BEGIN_MESSAGE_MAP(CMFCOpenGLView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// создание/уничтожение CMFCOpenGLView

CMFCOpenGLView::CMFCOpenGLView()
{
	// TODO: добавьте код создания

}

CMFCOpenGLView::~CMFCOpenGLView()
{
}

int CMFCOpenGLView::SetWindowPixelFormat(HDC hDC)
{
    int m_GLPixelIndex;
    PIXELFORMATDESCRIPTOR pfd;
    pfd.nSize       = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion    = 1;
    pfd.dwFlags   = PFD_DRAW_TO_WINDOW |
                    PFD_SUPPORT_OPENGL |
                    PFD_DOUBLEBUFFER;
    pfd.iPixelType     = PFD_TYPE_RGBA;
    pfd.cColorBits     = 32;
    pfd.cRedBits       = 8;
    pfd.cRedShift      = 16;
    pfd.cGreenBits     = 8;
    pfd.cGreenShift    = 8;
    pfd.cBlueBits      = 8;
    pfd.cBlueShift     = 0;
    pfd.cAlphaBits     = 0;
    pfd.cAlphaShift    = 0;
    pfd.cAccumBits     = 64;
    pfd.cAccumRedBits  = 16;
    pfd.cAccumGreenBits   = 16;
    pfd.cAccumBlueBits    = 16;
    pfd.cAccumAlphaBits   = 0;
    pfd.cDepthBits        = 32;
    pfd.cStencilBits      = 8;
    pfd.cAuxBuffers       = 0;
    pfd.iLayerType        = PFD_MAIN_PLANE;
    pfd.bReserved         = 0;
    pfd.dwLayerMask       = 0;
    pfd.dwVisibleMask     = 0;
    pfd.dwDamageMask      = 0;
    m_GLPixelIndex = ChoosePixelFormat( hDC, &pfd);
    if(m_GLPixelIndex==0) // Let's choose a default index.
    {
     m_GLPixelIndex = 1;
     if(DescribePixelFormat(hDC,m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pfd)==0)
       return 0;
    }
    if (SetPixelFormat( hDC, m_GLPixelIndex, &pfd)==FALSE)
        return 0;
    return 1;
}

BOOL CMFCOpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
		return CView::PreCreateWindow(cs);
}

// рисование CMFCOpenGLView

void CMFCOpenGLView::OnDraw(CDC* /*pDC*/)
{
	CMFCOpenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// диагностика CMFCOpenGLView

#ifdef _DEBUG
void CMFCOpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCOpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCOpenGLDoc* CMFCOpenGLView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCOpenGLDoc)));
	return (CMFCOpenGLDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CMFCOpenGLView


int CMFCOpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания
	pdc = new CClientDC(this);
	if(SetWindowPixelFormat(pdc->m_hDC)==FALSE)
		return -1;

	hGLRC = wglCreateContext(pdc->m_hDC);
	if(hGLRC == NULL)
			return -1;
	if(wglMakeCurrent(pdc->m_hDC, hGLRC)==FALSE)
		return -1;
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
	float pos[4] = {1,1,1,1};
	float dir[3] = {-1,-1,-1};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	// for DEV
		COpenGLDialogDlg mydlg;
		mydlg.DoModal(); //открываем диалог
		wglMakeCurrent(pdc->m_hDC,hGLRC);
		exit(-1);
	//
	return 0;
}


void CMFCOpenGLView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: добавьте свой код обработчика сообщений
	if(wglGetCurrentContext()!=NULL)
		wglMakeCurrent(NULL, NULL);
	if(hGLRC!=NULL)
	{
		wglDeleteContext(hGLRC);
		hGLRC = NULL;
	}
	delete pdc;
	CView::OnDestroy();
}


void CMFCOpenGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	/*
	glViewport ( 0, 0, cx, cy ) ;
	glMatrixMode ( GL_PROJECTION ) ;
	glLoadIdentity( ) ;
	glFrustum ( -1.0, 1.0, -1.0, 1.0, 2, 7.0 ) ;
	glMatrixMode ( GL_MODELVIEW ) ;
	glLoadIdentity( ) ; 
	gluLookAt(0,0,5, 0,0,0, 0,1,0);
	*/
	glViewport(0, 0, cx, cy);
       
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, cx, 0, cy, 0, 5);
       
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	
	/*
	   Function by Artem
	   void myReshapeFunc(int width, int height)
		{
		 //Сохранение новых параметров окна
		 globals::width = width;
		 globals::height = height;
		 //Изменение пространства вывода
		 glMatrixMode(GL_PROJECTION);
		 glLoadIdentity();
		 glViewport(0, 0, globals::width, globals::height);
		 glOrtho(-globals::width / 500, globals::width / 500, -globals::height / 500, globals::height / 500, globals::mynear, globals::myfar);
		 //Изменение положения камеры
		 glMatrixMode(GL_MODELVIEW);
		 glPushMatrix();
		 glLoadIdentity();
		 gluLookAt(globals::eyeX, globals::eyeY, globals::eyeZ, globals::centerX, globals::centerY, globals::centerZ, globals::upX, globals::upY, globals::upZ);
		 glPopMatrix();
		}
	*/
}

void CMFCOpenGLView::display()
{
	
	//hdc = GetDC()->m_hDC;
	//hrc = wglCreateContext(hdc);
	switch (choice)
	{
	case 0:
		{
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 1.0);
			glVertex2i(250, 450);
			glColor3f(0.0, 0.0, 1.0);
			glVertex2i(250, 150);
			glColor3f(0.0, 1.0, 0.0);
			glVertex2i(550, 150);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2i(550, 450);
			glEnd();
			SwapBuffers(wglGetCurrentDC());
		} break;
	case 1:
		{
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBegin(GL_POLYGON);
			glColor3f(1.0, 1.0, 1.0);
			glVertex2f(250,450);
			glColor3f(0.0, 0.0, 1.0);
			glVertex2f(250,150);
			glColor3f(0.0, 1.0, 0.0);
			glVertex2f(550,150);
			glEnd();
			SwapBuffers(wglGetCurrentDC());
		} break;
	case 2:
		{
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 1.0);
			glVertex2i(250, 300);
			glColor3f(0.0, 0.0, 1.0);
			glVertex2i(400, 450);
			glColor3f(0.0, 1.0, 0.0);
			glVertex2i(550, 300);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2i(400, 150);
			glEnd();
			SwapBuffers(wglGetCurrentDC());
		} break;
	default:
		break;
	}
	/*
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(0,1,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-2,-2,0);
	glVertex3f(2,-2,0);
	glVertex3f(2,2,0);
	glVertex3f(-2,2,0);
	glEnd;
	SwapBuffers(wglGetCurrentDC());
	*/
}

void CMFCOpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	
	if(nChar==VK_F2)
	{
		choice = 0;
	}
	if(nChar==VK_F3) choice = 1;
	if(nChar==VK_F4) choice = 2;
	if(nChar==VK_F5) 
	{
		COpenGLDialogDlg mydlg;
		mydlg.DoModal(); //открываем диалог
		wglMakeCurrent(pdc->m_hDC,hGLRC); //Возвращаем управление opengl в основное окно
		/*
		(wglMakeCurrent(pdc->m_hDC,hGLRC)==TRUE) ? AfxMessageBox(_T("All is good!"))
			: AfxMessageBox(_T("Something was wrong!"));
		*/
	}
}
