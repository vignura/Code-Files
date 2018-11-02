// OpenGLSceneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGLScene.h"
#include "OpenGLSceneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLSceneDlg dialog

COpenGLSceneDlg::COpenGLSceneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenGLSceneDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenGLSceneDlg)
	m_iComboSel = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGLSceneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenGLSceneDlg)
	DDX_CBIndex(pDX, IDC_COMBO_OPENGL_SCENE, m_iComboSel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COpenGLSceneDlg, CDialog)
	//{{AFX_MSG_MAP(COpenGLSceneDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_RENDER, OnBtnRender)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLSceneDlg message handlers

BOOL COpenGLSceneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CRect rect;
	// Get size and position of the picture control
	GetDlgItem(IDC_STATIC_OPENGL_SCENE)->GetWindowRect(rect);

	// Convert screen coordinates to client coordinates
	ScreenToClient(rect);

	// Create OpenGL Control window
	m_oglWindow.oglCreate(rect, this);

	// Setup the OpenGL Window's timer to render
	m_oglWindow.m_unpTimer = m_oglWindow.SetTimer(1, 1, 0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpenGLSceneDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenGLSceneDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenGLSceneDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void COpenGLSceneDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

// uncomment to allow resize of openGl scene
#if 1
	switch (nType)
	{
	  case SIZE_RESTORED:
	  {
		 if (m_oglWindow.m_bIsMaximized)
		 {
			m_oglWindow.OnSize(nType, cx, cy);
			m_oglWindow.m_bIsMaximized = false;
			SetSettingsVisible(true);
		 }

		 break;
	  }

	  case SIZE_MAXIMIZED:
	  {
		 m_oglWindow.OnSize(nType, cx, cy);
		 m_oglWindow.m_bIsMaximized = true;
		 SetSettingsVisible(false);
		 break;
	  }
	}	
#endif
}

void COpenGLSceneDlg::OnBtnRender() 
{
	UpdateData(true);

	m_oglWindow.ChangeScene(m_iComboSel);
}


void COpenGLSceneDlg::SetSettingsVisible(bool bState)
{
	if(bState == true)
	{
		GetDlgItem(IDC_BTN_RENDER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_OPENGL_SCENE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SETTINGS)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_BTN_RENDER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_OPENGL_SCENE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SETTINGS)->ShowWindow(SW_HIDE);
	}
}
