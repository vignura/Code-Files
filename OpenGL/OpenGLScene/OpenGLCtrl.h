#if !defined(AFX_OPENGLCTRL_H__8E9A8381_CCDB_4576_A4E0_E7678E38A68C__INCLUDED_)
#define AFX_OPENGLCTRL_H__8E9A8381_CCDB_4576_A4E0_E7678E38A68C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenGLCtrl.h : header file
//
#include "DrawFun.h"

/////////////////////////////////////////////////////////////////////////////
// OpenGLCtrl window

#define OGL_COLORED_CUBE		0x0
#define OGL_SOLAR_SYSTEM		0x1

class OpenGLCtrl : public CWnd
{
// Construction
public:
	OpenGLCtrl();

// Attributes
private:

	// Window information
	CWnd    *hWnd;
	HDC     hdc;
	HGLRC   hrc;
	int     m_nPixelFormat;
	CRect   m_rect;
	CRect   m_oldWindow;
	CRect   m_originalRect;
	unsigned long m_FrameCount;
	unsigned long m_ulStartTick;
	int m_iSceneID;

	float m_fPosX;
	float m_fPosY;
	float m_fZoom;
	float m_fRotX;
	float m_fRotY;
	float m_fLastX;
	float m_fLastY;

public:
	UINT_PTR m_unpTimer;
	bool m_bIsMaximized;

// Operations
public:
	void oglCreate(CRect rect, CWnd *parent);
	void oglInitialize(void);
	void oglDrawScene(void);
	void ChangeScene(int iSceneID);

	afx_msg void OnDraw(CDC *pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OpenGLCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~OpenGLCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(OpenGLCtrl)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLCTRL_H__8E9A8381_CCDB_4576_A4E0_E7678E38A68C__INCLUDED_)
