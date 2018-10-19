// OpenGLControl.h: interface for the OpenGLControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLCONTROL_H__915A66EF_1EAE_4960_9DC1_098EF33072CA__INCLUDED_)
#define AFX_OPENGLCONTROL_H__915A66EF_1EAE_4960_9DC1_098EF33072CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gl\gl.h>
#include <gl\glu.h>

class OpenGLControl : public CWnd  
{
public:
	
	UINT_PTR m_unpTimer;

private:

	// Window information
	CWnd    *hWnd;
	HDC     hdc;
	HGLRC   hrc;
	int     m_nPixelFormat;
	CRect   m_rect;
	CRect   m_oldWindow;
	CRect   m_originalRect;

public:

	OpenGLControl();
	virtual ~OpenGLControl();

	void oglCreate(CRect rect, CWnd *parent);

};

#endif // !defined(AFX_OPENGLCONTROL_H__915A66EF_1EAE_4960_9DC1_098EF33072CA__INCLUDED_)
