/*
* ==========================================================================
* Name:         AboutDlg.h : Header file of CAboutDlg
* Project:      Example
* Purpose:      This file contains declaration of About Dialog.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#if !defined(AFX_ABOUTDLG_H__37C3B309_6C9C_4AD3_B88F_E57CE9C4D475__INCLUDED_)
#define AFX_ABOUTDLG_H__37C3B309_6C9C_4AD3_B88F_E57CE9C4D475__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif //AFX_ABOUTDLG_H__37C3B309_6C9C_4AD3_B88F_E57CE9C4D475__INCLUDED_
