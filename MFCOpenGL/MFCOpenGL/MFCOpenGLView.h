
// MFCOpenGLView.h : ��������� ������ CMFCOpenGLView
//

#pragma once

class CMFCOpenGLView : public CView
{
private:
	CClientDC *pdc;
	HGLRC hGLRC;
	int SetWindowPixelFormat(HDC);
public:
	void display();

protected: // ������� ������ �� ������������
	CMFCOpenGLView();
	DECLARE_DYNCREATE(CMFCOpenGLView)

// ��������
public:
	CMFCOpenGLDoc* GetDocument() const;

// ��������
public:

// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����������
public:
	virtual ~CMFCOpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // ���������� ������ � MFCOpenGLView.cpp
inline CMFCOpenGLDoc* CMFCOpenGLView::GetDocument() const
   { return reinterpret_cast<CMFCOpenGLDoc*>(m_pDocument); }
#endif

