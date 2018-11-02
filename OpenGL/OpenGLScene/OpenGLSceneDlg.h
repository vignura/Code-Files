// OpenGLSceneDlg.h : header file
//

#if !defined(AFX_OPENGLSCENEDLG_H__2D613E0D_BF46_42D2_81DA_7EE78B118F75__INCLUDED_)
#define AFX_OPENGLSCENEDLG_H__2D613E0D_BF46_42D2_81DA_7EE78B118F75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpenGLCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// COpenGLSceneDlg dialog

class COpenGLSceneDlg : public CDialog
{
// Construction
public:
	COpenGLSceneDlg(CWnd* pParent = NULL);	// standard constructor
	void SetSettingsVisible(bool bState);

private:
	OpenGLCtrl m_oglWindow;	

// Dialog Data
	//{{AFX_DATA(COpenGLSceneDlg)
	enum { IDD = IDD_OPENGLSCENE_DIALOG };
	int m_iComboSel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLSceneDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COpenGLSceneDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnRender();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLSCENEDLG_H__2D613E0D_BF46_42D2_81DA_7EE78B118F75__INCLUDED_)
