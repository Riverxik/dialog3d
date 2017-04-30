#include "stdafx.h"
#include "OpenGLControl.h"

COpenGLControl::COpenGLControl(void)
{
	m_fPosX = 0.0f;		// X position of model in camera view
	m_fPosY = 0.0f;		// Y position of model in camera view
	m_fZoom = 5.0f;		// Zoom on model in camera view
	m_fRotX = 0.0f;		// Rotation on model in camera view
	m_fRotY	= 0.0f;		// Rotation on model in camera view
	m_bIsMaximized = false;
	m_bRayIsVisible = true;

	m_start_x = 0.0f; // x coord of start point
	m_start_y = 0.0f; // y coord of start point
	m_start_z = 0.0f; // z coord of start point
	m_length = 1.0f;  // x_max coord of start point
	m_width = 1.0f;   // y_max coord of start point
	m_height = 1.0f;  // z_max coord of start point
	m_scale = 1.0f;   // scale
	
	// �����
	for(unsigned i=0; i<SELECTING_OBJECT_COUNT; i++)
		obj[i]; // ������������� 8 ���� � 0,0,0
	
	//����
	for(unsigned i=0; i<SELECTING_OBJECT_COUNT; i++)
	{
		cubeColorArray[i][0] = 1.0f;
		cubeColorArray[i][1] = 1.0f;
		cubeColorArray[i][2] = 1.0f;
	}
	//�����
	cubeIndexArray[0][0] = 0;
	cubeIndexArray[0][1] = 3;
	cubeIndexArray[0][2] = 2;
	cubeIndexArray[0][3] = 1;
 
	cubeIndexArray[1][0] = 0;
	cubeIndexArray[1][1] = 1;
	cubeIndexArray[1][2] = 5;
	cubeIndexArray[1][3] = 4;
 
	cubeIndexArray[2][0] = 7;
	cubeIndexArray[2][1] = 4;
	cubeIndexArray[2][2] = 5;
	cubeIndexArray[2][3] = 6;
 
	cubeIndexArray[3][0] = 3;
	cubeIndexArray[3][1] = 7;
	cubeIndexArray[3][2] = 6;
	cubeIndexArray[3][3] = 2;
 
	cubeIndexArray[4][0] = 1;
	cubeIndexArray[4][1] = 2;
	cubeIndexArray[4][2] = 6;
	cubeIndexArray[4][3] = 5;
 
	cubeIndexArray[5][0] = 0;
	cubeIndexArray[5][1] = 4;
	cubeIndexArray[5][2] = 7;
	cubeIndexArray[5][3] = 3;
	// ���
	/*
		 1
		 |	 
		0|___2
		/
	   /3
	*/
	// �����
	// axisVertex[����� �����][����� ����������]
	axisVertex[0][0] = 0;
	axisVertex[0][1] = 0;
	axisVertex[0][2] = 0;
	axisVertex[1][0] = 0;
	axisVertex[1][1] = 1;
	axisVertex[1][2] = 0;
	axisVertex[2][0] = 1;
	axisVertex[2][1] = 0;
	axisVertex[2][2] = 0;
	axisVertex[3][0] = 0;
	axisVertex[3][1] = 0;
	axisVertex[3][2] = 1;
	// �����
	// axisColor[����� �����][����� ����������] = 0;
	axisColor[0][0] = 1;
	axisColor[0][1] = 1;
	axisColor[0][2] = 1;
	axisColor[1][0] = 0;
	axisColor[1][1] = 1;
	axisColor[1][2] = 0;
	axisColor[2][0] = 1;
	axisColor[2][1] = 0;
	axisColor[2][2] = 0;
	axisColor[3][0] = 0;
	axisColor[3][1] = 0;
	axisColor[3][2] = 1;
	// �����
	// axisIndex[����� �����][����� �����]
	axisIndex[0][0] = 0;
	axisIndex[0][1] = 1;
	axisIndex[1][0] = 0;
	axisIndex[1][1] = 2;
	axisIndex[2][0] = 0;
	axisIndex[2][1] = 3;
}

COpenGLControl::~COpenGLControl(void)
{
}

BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void COpenGLControl::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	ValidateRect(NULL);
}

void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;

	// Map the OpenGL coordinates.
	glViewport(0, 0, cx, cy);
	//int side = 0;
	//(cx > cy) ? side = cx : side = cy;
	//glViewport((cx - side) / 2, (cy - side) / 2, side, side);


	// Projection view
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// Set our current view perspective
	gluPerspective(35.0f, (float)cx / (float)cy, 0.01f, 2000.0f);

	// Model view
	glMatrixMode(GL_MODELVIEW);

	switch (nType)
	{
		// If window resize token is "maximize"
		case SIZE_MAXIMIZED:
		{
			// Get the current window rect
			GetWindowRect(m_rect);

			// Move the window accordingly
			MoveWindow(6, 6, cx - 14, cy - 14);

			// Get the new window rect
			GetWindowRect(m_rect);

			// Store our old window as the new rect
			m_oldWindow = m_rect;

			break;
		}

		// If window resize token is "restore"
		case SIZE_RESTORED:
		{
			// If the window is currently maximized
			if (m_bIsMaximized)
			{
				// Get the current window rect
				GetWindowRect(m_rect);

				// Move the window accordingly (to our stored old window)
				MoveWindow(m_oldWindow.left, m_oldWindow.top - 18, m_originalRect.Width() - 4, m_originalRect.Height() - 4);

				// Get the new window rect
				GetWindowRect(m_rect);

				// Store our old window as the new rect
				m_oldWindow = m_rect;
			}
		
			break;
		}
	}
}

int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;

	oglInitialize();

	return 0;
}

void COpenGLControl::OnDraw(CDC *pDC)
{
	// If the current view is perspective...
	
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.0f);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);
	glScalef(m_scale, m_scale, m_scale);
}

void COpenGLControl::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
		case 1:
		{
			// Clear color and depth buffer bits
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Draw OpenGL scene
			oglDrawScene();

			// Swap buffers
			SwapBuffers(hdc);

			break;
		}

		default:
			break;
	}

	CWnd::OnTimer(nIDEvent);
}

void COpenGLControl::OnMouseMove(UINT nFlags, CPoint point)
{
	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX  = (float)point.x;
	m_fLastY  = (float)point.y;

	// Left mouse button
	if (nFlags & MK_LBUTTON)
	{
		m_fRotX += (float)0.5f * diffY;

		if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f))
		{
			m_fRotX = 0.0f;
		}

		m_fRotY += (float)0.5f * diffX;

		if ((m_fRotY > 360.0f) || (m_fRotY < -360.0f))
		{
			m_fRotY = 0.0f;
		}
	}

	// Right mouse button
	else if (nFlags & MK_RBUTTON)
	{
		m_fZoom -= (float)0.1f * diffY;
	}

	// Middle mouse button
	else if (nFlags & MK_MBUTTON)
	{
		m_fPosX += (float)0.05f * diffX;
		m_fPosY -= (float)0.05f * diffY;
	}

	OnDraw(NULL);

	CWnd::OnMouseMove(nFlags, point);
}

void COpenGLControl::OnLButtonUp(UINT nFlags, CPoint point)
{
	//�������� ���������� ����
	if(nFlags && MK_CONTROL)
	{
		RetrieveObjectID(point.x, point.y, p1, p2); // ������ ���
		
	}

	/*int objectID;
	objectID = RetrieveObjectID(point.x, point.y);	
		
	switch (objectID)
	{
	case OBJECT_CUBE:
		AfxMessageBox(_T("�� ������ � ���!"));
			break;
	case OBJECT_SPHERE_1:
		AfxMessageBox(_T("������� ����� �1!"));
			break;
	case OBJECT_SPHERE_2:
		AfxMessageBox(_T("������� ����� �2!"));
			break;
	case OBJECT_SPHERE_3:
		AfxMessageBox(_T("������� ����� �3!"));
			break;
	case OBJECT_SPHERE_4:
		AfxMessageBox(_T("������� ����� �4!"));
			break;
	case OBJECT_SPHERE_5:
		AfxMessageBox(_T("������� ����� �5!"));
			break;
	case OBJECT_SPHERE_6:
		AfxMessageBox(_T("������� ����� �6!"));
			break;
	case OBJECT_SPHERE_7:
		AfxMessageBox(_T("������� ����� �7!"));
			break;
	case OBJECT_SPHERE_8:
		AfxMessageBox(_T("������� ����� �8!"));
			break;
	default:
		AfxMessageBox(_T("������!"));
			break;
		break;
	}*/
	CWnd::OnLButtonUp(nFlags, point);
}

void COpenGLControl::oglCreate(CRect rect, CWnd *parent)
{
	CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL, (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	CreateEx(0, className, "OpenGL", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	// Set initial variables' values
	m_oldWindow	   = rect;
	m_originalRect = rect;

	hWnd = parent;
}

void COpenGLControl::oglInitialize(void)
{
	// Initial Setup:
	//
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32, // bit depth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16, // z-buffer depth
		0, 0, 0, 0, 0, 0, 0,
	};

	// Get device context only once.
	hdc = GetDC()->m_hDC;
	
	// Pixel format.
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	// Create the OpenGL Rendering Context.
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	// Basic Setup:
	//
	// Set color to use when clearing the background.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	// Turn on backface culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	
	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Send draw request
	OnDraw(NULL);
	// set settings
	glShadeModel(GL_FLAT);
	//glEnable(GL_CULL_FACE);

	// Set Vertex Array
	oglRecalculate(); // ��������� �������
}

void COpenGLControl::oglDrawScene(void)
{
	// ����������� ���������
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// ���
	glVertexPointer(3, GL_FLOAT, 0, axisVertex);
	glColorPointer(3, GL_FLOAT, 0, axisColor);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_BYTE, axisIndex);
	// ���������
	glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
	glColorPointer(3, GL_FLOAT, 0, cubeColorArray);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndexArray);
	// ���
	if(p1 != 0 && p2 !=0 && m_bRayIsVisible) //������� ���������� ���
	{
		glColor3d(1,1,0);
		glBegin(GL_LINES);
			glVertex3f(p1.x,p1.y,p1.z);
			glVertex3f(p2.x,p2.y,p2.z);
		glEnd();
	}
	// �����
	for(unsigned i=0; i<SELECTING_OBJECT_COUNT; i++)
	{
		glColor3ub(0,100,200);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(obj[i].center.x,obj[i].center.y,obj[i].center.z);
			auxSolidSphere(0.1);
		glPopMatrix();
	}	

	//// Sphere 1
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glColor3ub(0,150,0);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glTranslatef(m_start_x,m_start_y,m_start_z);
	//gluSphere(m_Obj[0], 0.1f*m_scale, 10, 10);
	//glPopMatrix();
	//// Sphere 2
	//glColor3ub(0,150,0);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glTranslatef(m_start_x,m_start_y,m_start_z + m_height);
	//	gluSphere(m_Obj[1], 0.1f*m_scale, 10, 10);
	//glPopMatrix();
	//// Sphere 3
	//glColor3ub(0,150,0);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glTranslatef(m_start_x,m_start_y + m_width,m_start_z + m_height);
	//	gluSphere(m_Obj[2], 0.1f*m_scale, 10, 10);
	//glPopMatrix();
	//// Sphere 4
	//glColor3ub(0,150,0);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glTranslatef(m_start_x,m_start_y + m_width,m_start_z);
	//	gluSphere(m_Obj[3], 0.1f*m_scale, 10, 10);
	//glPopMatrix();
	//// Sphere 5
	//glColor3ub(0,150,0);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glTranslatef(m_start_x + m_length,m_start_y,m_start_z);
	//gluSphere(m_Obj[4], 0.1f*m_scale, 10, 10);
	//glPopMatrix();
	//// Sphere 6
	//glColor3ub(0,150,0);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glTranslatef(m_start_x + m_length,m_start_y,m_start_z + m_height);
	//	gluSphere(m_Obj[5], 0.1f*m_scale, 10, 10);
	//glPopMatrix();
	//// Sphere 7
	//glColor3ub(0,150,0);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glTranslatef(m_start_x + m_length,m_start_y + m_width,m_start_z + m_height);
	//	gluSphere(m_Obj[6], 0.1f*m_scale, 10, 10);
	//glPopMatrix();
	//// Sphere 8
	//glColor3ub(0,150,0);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glTranslatef(m_start_x + m_length,m_start_y + m_width,m_start_z);
	//	gluSphere(m_Obj[7], 0.1f*m_scale, 10, 10);
	//glPopMatrix();

	//glBegin(GL_QUADS);
	//		// Front Side
	//		glVertex3f( m_start_x,  m_start_y, m_start_z);
	//		glVertex3f( m_start_x,  m_start_y, m_start_z+m_height);
	//		glVertex3f( m_start_x,  m_start_y+m_width, m_start_z+m_height);
	//		glVertex3f( m_start_x,  m_start_y+m_width, m_start_z);
	//		// Back Side
	//		glVertex3f( m_start_x+m_length,  m_start_y, m_start_z);
	//		glVertex3f( m_start_x+m_length,  m_start_y, m_start_z+m_height);
	//		glVertex3f( m_start_x+m_length,  m_start_y+m_width, m_start_z+m_height);
	//		glVertex3f( m_start_x+m_length,  m_start_y+m_width, m_start_z);
	//		// Top Side
	//		glVertex3f( m_start_x,  m_start_y, m_start_z+m_height);
	//		glVertex3f( m_start_x+m_length,  m_start_y, m_start_z+m_height);
	//		glVertex3f( m_start_x+m_length,  m_start_y+m_width, m_start_z+m_height);
	//		glVertex3f( m_start_x,  m_start_y+m_width, m_start_z+m_height);
	//		// Bottom Side
	//		glVertex3f( m_start_x,  m_start_y, m_start_z);
	//		glVertex3f( m_start_x+m_length,  m_start_y, m_start_z);
	//		glVertex3f( m_start_x+m_length,  m_start_y+m_width, m_start_z);
	//		glVertex3f( m_start_x,  m_start_y+m_width, m_start_z);
	//		// Right Side
	//		glVertex3f( m_start_x,  m_start_y, m_start_z);
	//		glVertex3f( m_start_x+m_length,  m_start_y, m_start_z);
	//		glVertex3f( m_start_x+m_length,  m_start_y, m_start_z+m_height);
	//		glVertex3f( m_start_x,  m_start_y, m_start_z+m_height);
	//		// Left Side
	//		glVertex3f( m_start_x,  m_start_y+m_width, m_start_z);
	//		glVertex3f( m_start_x+m_length,  m_start_y+m_width, m_start_z);
	//		glVertex3f( m_start_x+m_length,  m_start_y+m_width, m_start_z+m_height);
	//		glVertex3f( m_start_x,  m_start_y+m_width, m_start_z+m_height);
	//		/*
	//		// Front Side
	//		glVertex3f( 1.0f,  1.0f, 1.0f);
	//		glVertex3f(-1.0f,  1.0f, 1.0f);
	//		glVertex3f(-1.0f, -1.0f, 1.0f);
	//		glVertex3f( 1.0f, -1.0f, 1.0f);
	//		// Back Side
	//		glVertex3f(-1.0f, -1.0f, -1.0f);
	//		glVertex3f(-1.0f,  1.0f, -1.0f);
	//		glVertex3f( 1.0f,  1.0f, -1.0f);
	//		glVertex3f( 1.0f, -1.0f, -1.0f);
	//		// Top Side
	//		glVertex3f( 1.0f, 1.0f,  1.0f);
	//		glVertex3f( 1.0f, 1.0f, -1.0f);
	//		glVertex3f(-1.0f, 1.0f, -1.0f);
	//		glVertex3f(-1.0f, 1.0f,  1.0f);
	//		// Bottom Side
	//		glVertex3f(-1.0f, -1.0f, -1.0f);
	//		glVertex3f( 1.0f, -1.0f, -1.0f);
	//		glVertex3f( 1.0f, -1.0f,  1.0f);
	//		glVertex3f(-1.0f, -1.0f,  1.0f);
	//		// Right Side
	//		glVertex3f( 1.0f,  1.0f,  1.0f);
	//		glVertex3f( 1.0f, -1.0f,  1.0f);
	//		glVertex3f( 1.0f, -1.0f, -1.0f);
	//		glVertex3f( 1.0f,  1.0f, -1.0f);
	//		// Left Side
	//		glVertex3f(-1.0f, -1.0f, -1.0f);
	//		glVertex3f(-1.0f, -1.0f,  1.0f);
	//		glVertex3f(-1.0f,  1.0f,  1.0f);
	//		glVertex3f(-1.0f,  1.0f, -1.0f);
	//		*/
	//glEnd();
}

void COpenGLControl::oglFillIn(void)
{
	// ��������� ������ � ���� openGL
	/*
		1.���������� ������ � �����
		2.����� ������������ ���������� �� X & Y
		3.������� ����� ������������
		4.������� �� ��������� ���
	*/
	// ���������� � �����
	m_fPosX = 0;	// X position of model in camera view
	m_fPosY = 0;	// Y position of model in camera view
	OnMouseMove(NULL, NULL);
	//return;
	//
	double model[16];
	double project[16];
	int viewport[4];
	double WinPoints[NUMBER_OF_VERTEX][3] = {0};
	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, project);
	glGetIntegerv(GL_VIEWPORT, viewport);
	// ��������� 2D ��������� ����� � ����
	for(unsigned i=0; i<NUMBER_OF_VERTEX; i++)
		gluProject(
			 cubeVertexArray[i][0]
			,cubeVertexArray[i][1]
			,cubeVertexArray[i][2],
			model,project,viewport
			,&WinPoints[i][0]
			,&WinPoints[i][1]
			,&WinPoints[i][2]);
	// ������� ����������� � ������������ ��������
	double maxX, maxY, minX, minY;
	maxX = minX = WinPoints[0][0];
	maxY = minY = WinPoints[0][1];
	for(unsigned i=1; i<NUMBER_OF_VERTEX; i++)
	{
		if(WinPoints[i][0] > maxX) maxX = WinPoints[i][0];
		if(WinPoints[i][0] < minX) minX = WinPoints[i][0];
		if(WinPoints[i][1] > maxY) maxY = WinPoints[i][1];
		if(WinPoints[i][1] < minY) minY = WinPoints[i][1];
	}
	// ������������ �� ���������� �������
	double objX, objY;
	objX = fabs(maxX - minX);
	objY = fabs(maxY - minY);
	if(objX > objY)
		m_fZoom = viewport[2] / objX;
	else
		m_fZoom = viewport[3] / objY;
	
	OnMouseMove(NULL, NULL);
}

void COpenGLControl::oglRecalculate(void)
{
	m_start_x = 0 - m_length/2;
	m_start_y = 0 - m_width/2;
	m_start_z = 0 - m_height/2;
	cubeVertexArray[0][0] = m_start_x;
	cubeVertexArray[0][1] = m_start_y;
	cubeVertexArray[0][2] = m_start_z;

	cubeVertexArray[1][0] = m_start_x;
	cubeVertexArray[1][1] = m_start_y;
	cubeVertexArray[1][2] = m_start_z + m_height;

	cubeVertexArray[2][0] = m_start_x;
	cubeVertexArray[2][1] = m_start_y + m_width;
	cubeVertexArray[2][2] = m_start_z + m_height;

	cubeVertexArray[3][0] = m_start_x;
	cubeVertexArray[3][1] = m_start_y + m_width;
	cubeVertexArray[3][2] = m_start_z;

	cubeVertexArray[4][0] = m_start_x + m_length;
	cubeVertexArray[4][1] = m_start_y;
	cubeVertexArray[4][2] = m_start_z;

	cubeVertexArray[5][0] = m_start_x + m_length;
	cubeVertexArray[5][1] = m_start_y;
	cubeVertexArray[5][2] = m_start_z + m_height;

	cubeVertexArray[6][0] = m_start_x + m_length;
	cubeVertexArray[6][1] = m_start_y + m_width;
	cubeVertexArray[6][2] = m_start_z + m_height;

	cubeVertexArray[7][0] = m_start_x + m_length;
	cubeVertexArray[7][1] = m_start_y + m_width;
	cubeVertexArray[7][2] = m_start_z;
	for(unsigned i=0; i<SELECTING_OBJECT_COUNT; i++)
	{
		obj[i].center.x = cubeVertexArray[i][0];
		obj[i].center.y = cubeVertexArray[i][1];
		obj[i].center.z = cubeVertexArray[i][2];
	}
}

int COpenGLControl::RetrieveObjectID(int x, int y, myvector &p1, myvector &p2)
{
	/*
		�������� ������ ����� �� ����������� ����
	*/
	double model[16];
	double project[16];
	double wx,wy,wz;
	int viewport[4];
	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, project);
	glGetIntegerv(GL_VIEWPORT, viewport);
	//�������� ������� ����� �������
	gluUnProject(x, viewport[3] - y, -1.0
		, model, project, viewport
		, &wx, &wy, &wz);
	p1.Set(wx, wy, wz);
	//�������� ������� ����� �������
	gluUnProject(x, viewport[3] - y, 1.0
		, model, project, viewport
		, &wx, &wy, &wz);
	p2.Set(wx, wy, wz);
	
	return 0;
}