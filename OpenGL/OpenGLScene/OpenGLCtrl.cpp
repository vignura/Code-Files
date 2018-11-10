// OpenGLCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGLScene.h"
#include "OpenGLCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OpenGLCtrl

OpenGLCtrl::OpenGLCtrl()
{
	m_fPosX = 0.0f;    // X position of model in camera view
	m_fPosY = 0.0f;    // Y position of model in camera view
	m_fZoom = 10.0f;   // Zoom on model in camera view
	m_fRotX = 0.0f;    // Rotation on model in camera view
	m_fRotY = 0.0f;    // Rotation on model in camera view

	m_fLastX = 0;
	m_fLastY = 0;

	m_bIsMaximized = false;
	m_FrameCount = 0;
	m_ulStartTick = GetTickCount();
	m_iSceneID = OGL_COLORED_CUBE;
}

OpenGLCtrl::~OpenGLCtrl()
{
}


BEGIN_MESSAGE_MAP(OpenGLCtrl, CWnd)
	//{{AFX_MSG_MAP(OpenGLCtrl)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// OpenGLCtrl message handlers


void OpenGLCtrl::oglCreate(CRect rect, CWnd *parent)
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

void OpenGLCtrl::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	ValidateRect(NULL);
}

int OpenGLCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	oglInitialize();
	
	return 0;
}

void OpenGLCtrl::oglInitialize(void)
{
	// Initial Setup:
	//
	static PIXELFORMATDESCRIPTOR pfd =
	{
	  sizeof(PIXELFORMATDESCRIPTOR),
	  1,
	  PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
	  PFD_TYPE_RGBA,
	  32,    // bit depth
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  16,    // z-buffer depth
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
	glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
	glClearDepth(1.0f);

	// Turn on backface culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Send draw request
	OnDraw(NULL);
}

void OpenGLCtrl::OnDraw(CDC *pDC)
{
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.0f);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);
}

void OpenGLCtrl::OnTimer(UINT nIDEvent) 
{
	CString Msg = "";
	float fFPS = 0;

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
	
	m_FrameCount++;
	fFPS = (m_FrameCount / ((float)(GetTickCount() - m_ulStartTick) / 1000.0f));
	Msg.Format("FPS: %f\n", fFPS);
	TRACE0(Msg);
	CWnd::OnTimer(nIDEvent);
}

void OpenGLCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;

	// Map the OpenGL coordinates.
	glViewport(0, 0, cx, cy);

	// Projection view
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// Set our current view perspective
	gluPerspective(35.0f, (float)cx / (float)cy, 0.01f, 2000.0f);

	// Model view
	glMatrixMode(GL_MODELVIEW);

// uncomment the below if the window needs to resized
#if 1
	switch (nType)
	{
		// If window resize token is "maximize"
		case SIZE_MAXIMIZED:
		{
			// Get the current window rect
			GetWindowRect(m_rect);
			ScreenToClient(&m_rect);
			
			m_oldWindow = m_rect;

			// Move the window accordingly
			MoveWindow(6, 6, cx - 14, cy - 14);

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
				 MoveWindow(m_oldWindow.left + 49,
							m_oldWindow.top + 50,
							m_originalRect.Width(),
							m_originalRect.Height());

			}

		break;
		}
	}
#endif 
}

void OpenGLCtrl::oglDrawScene(void)
{
	// Wireframe Mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	switch(m_iSceneID)
	{
		case OGL_COLORED_CUBE: 

			DrawColoredCube(0, 0, 0, 2.0);
			break;
		
		case OGL_SOLAR_SYSTEM:

			DrawSolarSystem();
			break;

		case OGL_CLOCK:
			
			DrawClock(SEC_HAND_CONTINUOUS);
			break;
		
		default:
			;
	}
}

void OpenGLCtrl::OnMouseMove(UINT nFlags, CPoint point) 
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

	  OnDraw(NULL);
	}

	// Right mouse button
	else if (nFlags & MK_RBUTTON)
	{
	  m_fZoom -= (float)0.1f * diffY;
	  OnDraw(NULL);
	}

	// Middle mouse button
	else if (nFlags & MK_MBUTTON)
	{
	  m_fPosX += (float)0.01f * diffX;
	  m_fPosY -= (float)0.01f * diffY;
	  OnDraw(NULL);
	}

	
	CWnd::OnMouseMove(nFlags, point);
}


void OpenGLCtrl::ChangeScene(int iSceneID)
{
	m_iSceneID = iSceneID;
}
