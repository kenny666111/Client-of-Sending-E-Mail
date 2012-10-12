// MySmtpDlg.h : header file
//

#if !defined(AFX_MYSMTPDLG_H__EC7C3A4B_2FFC_4865_B900_215B054EFEFA__INCLUDED_)
#define AFX_MYSMTPDLG_H__EC7C3A4B_2FFC_4865_B900_215B054EFEFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMySmtpDlg dialog

#include "ZSmtp.h"
#include "ZFileDialog.h"
#include "ZString.h"
#include "MyODBC.h"
#include "ODBCSet.h"
#include "Splash.h"
class CMySmtpDlg : public CDialog
{
// Construction
public:
	CMySmtpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMySmtpDlg)
	enum { IDD = IDD_MYSMTP_DIALOG };
	BOOL	m_IsHtml;
	CString	m_name;
	CString	m_email;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySmtpDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMySmtpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSend();
	afx_msg void OnBtnAbout();
	afx_msg void OnBtnBrowser();
	afx_msg void OnBtnDelfile();
	afx_msg void OnButton1();
	afx_msg void OnAddUser();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
/*+++++++++++++++++++++++++++++++++++++++++++*/
private:
		deque<string> m_dqFiles;
		CComboBox* pCombo;
/*+++++++++++++++++++++++++++++++++++++++++++*/
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSMTPDLG_H__EC7C3A4B_2FFC_4865_B900_215B054EFEFA__INCLUDED_)
