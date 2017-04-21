/*
* ==========================================================================
* Name:         AdjustDlg.h : Header File of CAdjustDlg Dialog.
* Project:      Example
* Purpose:      This file contains declaration of CAdjustDlg Dialog.
*				This dialog is responsible for Adjusting detector 
*				parameters (eg. Adjust Pole Zero).
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

//{{AFX_INCLUDES()
#include "adjustcontrol.h"
//}}AFX_INCLUDES
#if !defined(AFX_ADJUSTDLG_H__5F27AA4B_0077_4F49_887F_150736329B8C__INCLUDED_)
#define AFX_ADJUSTDLG_H__5F27AA4B_0077_4F49_887F_150736329B8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAdjustDlg dialog

class CAdjustDlg : public CDialog
{
// Construction
public:
	CAdjustDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAdjustDlg)
	enum { IDD = IDD_DIALOG_ADJUST };
	CAdjustControl	m_cIAdjustCtl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdjustDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdjustDlg)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetDevice (LPDISPATCH lpNewVal);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADJUSTDLG_H__5F27AA4B_0077_4F49_887F_150736329B8C__INCLUDED_)
