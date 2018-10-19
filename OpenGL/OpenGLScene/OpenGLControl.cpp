// OpenGLControl.cpp: implementation of the OpenGLControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenGLScene.h"
#include "OpenGLControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OpenGLControl::OpenGLControl()
{

}

OpenGLControl::~OpenGLControl()
{

}

void OpenGLControl::oglCreate(CRect rect, CWnd *parent)
{
	CString className = AfxRegisterWndClass((CS_HREDRAW | CS_VREDRAW | CS_OWNDC), NULL, 
											(HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	CreateEx(0, className, "OpenGLCtrl", WS_CHILD | WS_VISIBLE |
		  WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	// Set initial variables' values
	m_oldWindow    = rect;
	m_originalRect = rect;

	hWnd = parent;
}
