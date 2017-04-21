#if !defined(AFX_SAMPLEEDIT_H__5761CC9D_8782_4393_BB13_419A9C9099E2__INCLUDED_)
#define AFX_SAMPLEEDIT_H__5761CC9D_8782_4393_BB13_419A9C9099E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SampleEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSampleEdit dialog

class CSampleEdit : public CDialog
{
// Construction
public:
	CSampleEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSampleEdit)
	enum { IDD = IDD_DIALOG_SAMPLEINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSampleEdit)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEEDIT_H__5761CC9D_8782_4393_BB13_419A9C9099E2__INCLUDED_)
