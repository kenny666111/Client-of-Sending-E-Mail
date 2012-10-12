#if !defined(AFX_TONGXUN_H__CFA009CC_9EFB_4E1D_8FAE_707ABD564019__INCLUDED_)
#define AFX_TONGXUN_H__CFA009CC_9EFB_4E1D_8FAE_707ABD564019__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TONGXUN.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// TONGXUN dialog
#include "MyODBC.h"
#include "ODBCSet.h"

class TONGXUN : public CDialog
{
// Construction
public:
	TONGXUN(CWnd* pParent = NULL);   // standard constructor
	CString name;
	CString email;
void BindGrid();
// Dialog Data
	//{{AFX_DATA(TONGXUN)
	enum { IDD = IDD_TONGXUN_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TONGXUN)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation


	private:


protected:

	// Generated message map functions
	//{{AFX_MSG(TONGXUN)
	afx_msg void OnSelectUser();
	virtual BOOL OnInitDialog();
	afx_msg void OnDelUser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TONGXUN_H__CFA009CC_9EFB_4E1D_8FAE_707ABD564019__INCLUDED_)
