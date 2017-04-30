#pragma once
#include "afxwin.h"

#include <gl/gl.h>
#include <gl/glu.h>
#include <glaux.h>

#define NUMBER_OF_VERTEX 8
#define SELECTING_OBJECT_COUNT 8
#define SELECTING_BUFFER 4 * SELECTING_OBJECT_COUNT

struct myvector
{
	float x;
	float y;
	float z;
	myvector(){x=y=z=0;};

	bool operator!=(const myvector &vec) const
	{return !((*this).x == vec.x && (*this).y == vec.y && (*this).z == vec.z);}
	bool operator!=(const int _num) const
	{return !((*this).x == _num && (*this).y == _num && (*this).z == _num);}
	void Set(float _x, float _y, float _z){x=_x; y=_y; z=_z;};
};

struct myobject
{
	myvector center; //Центральная точка
	myobject(){center.Set(0,0,0);};
};

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
		bool	 m_bRayIsVisible;

		// Draw information
		float	 m_start_x;		// Ближайшая точка по оси X
		float	 m_start_y;		// Ближайшая точка по оси Y
		float	 m_start_z;		// Ближайшая точка по оси Z
		float	 m_length;		// Длина объекта
		float	 m_width;		// Ширина объекта
		float	 m_height;		// Высота объекта
		float	 m_scale;		// Коэффициент увеличения

		// Massive of Vertex
		GLfloat cubeVertexArray[8][3];	// Массив вершин пара-педа
		GLfloat cubeColorArray[8][3];	// Массив цветов вершин
		GLubyte cubeIndexArray[6][4];	// Массив граней пара-педа

		GLfloat axisVertex[4][3];		// Массив точек оси
		GLfloat axisColor[4][3];		// Массив цветов оси
		GLubyte axisIndex[3][2];		// Массив точек линий

		myvector p1, p2;				// Луч определяющий пересечение с объектами
		myobject obj[SELECTING_OBJECT_COUNT];// 8 сфер для выбора точки начала координат
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
		GLUquadricObj* m_Obj[8]; //Для сфер

	public:
		COpenGLControl(void);
		virtual ~COpenGLControl(void);

		void oglCreate(CRect rect, CWnd *parent);//Создание
		void oglInitialize(void);				// Инициализация
		void oglDrawScene(void);				// Отрисовка
		void oglFillIn(void);					// Вписывание
		void oglRecalculate(void);				// Пересчитывание координат (для изменения)
		int RetrieveObjectID(int x, int y, 
				myvector &p1, myvector &p2);	// Вычисление в какой объект попали (переделать через луч)

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