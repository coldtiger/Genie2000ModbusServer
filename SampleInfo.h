/*
* ==========================================================================
* Name:         SampleInfo.cpp : Header of CSampleInfo Dialog.
* Project:      Example
* Purpose:      This file contains definations of CSampleInfo Dialog.
*				This dialog is responsible for displaying different Sample Info 
*				parameters for selected datasource.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#if !defined(AFX_SAMPLEINFO_H__F7548B9D_0E4C_4BE8_8D93_B0EB2F1AF8E3__INCLUDED_)
#define AFX_SAMPLEINFO_H__F7548B9D_0E4C_4BE8_8D93_B0EB2F1AF8E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SampleInfo.h :  file
//
/*
#ifndef _DATAACCESS_IDL_
#define	_DATAACCESS_IDL_
#include "dataaccess.h"
#endif	// _DATAACCESS_IDL_
*/
/////////////////////////////////////////////////////////////////////////////
// CSampleInfo dialog
#include "mvc.h"

class CSampleInfo : public CDialog
{
// Construction
public:
	CSampleInfo(CMvc* lpDispatch, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSampleInfo)
	enum { IDD = IDD_DIALOG_SAMPLEINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSampleInfo)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CMvc*	m_lpMvc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEINFO_H__F7548B9D_0E4C_4BE8_8D93_B0EB2F1AF8E3__INCLUDED_)
