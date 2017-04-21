/*
* ==========================================================================
* Name:         SeqAnalyzer.h : Header file of CSeqAnalyzer Dialog.
* Project:      Example
* Purpose:      This file contains declaration of CSeqAnalyzer Dialog.
*				This dialog is responsible for selecting / displaying seq step.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

//{{AFX_INCLUDES()
#include "analysiseditor.h"
//}}AFX_INCLUDES
#if !defined(AFX_SEQANALYZER_H__F13D6563_71D5_4873_B2E5_7DBD6B99171B__INCLUDED_)
#define AFX_SEQANALYZER_H__F13D6563_71D5_4873_B2E5_7DBD6B99171B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CSeqAnalyzer dialog

class CSeqAnalyzer : public CDialog
{
// Construction
public:
	CSeqAnalyzer(LPDISPATCH	pDatasource, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSeqAnalyzer)
	enum { IDD = IDD_DIALOG_ANALYSIS };
	CAnalysisEditor	m_cIAnalysisEdit;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeqAnalyzer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSeqAnalyzer)
	virtual void OnOK();
	afx_msg void OnButtonLoad();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LPDISPATCH		m_pDatasource;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEQANALYZER_H__F13D6563_71D5_4873_B2E5_7DBD6B99171B__INCLUDED_)
