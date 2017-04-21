/*
* ==========================================================================
* Name:         Calibration.h :  Header of CCalibration Dialog.
* Project:      Example
* Purpose:      This file contains definations of CCalibration Dialog.
*				This dialog is responsible for displaying different calibration 
*				information for selected datasource.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#if !defined(AFX_CALIBRATION_H__BEE67EB4_DC3F_4883_A303_6CD516D21FEA__INCLUDED_)
#define AFX_CALIBRATION_H__BEE67EB4_DC3F_4883_A303_6CD516D21FEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalibration dialog

class CCalibration : public CDialog
{
// Construction
public:
	CCalibration(IDataAccessPtr lpDispatch, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalibration)
	enum { IDD = IDD_DIALOG_CAL };
	CStatic	m_LowTailTxt;
	CStatic	m_FwhmTxt;
	CStatic	m_ECalTxt;
	CListBox	m_EnegryCal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalibration)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalibration)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	IDataAccessPtr	m_lpDataAccess;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIBRATION_H__BEE67EB4_DC3F_4883_A303_6CD516D21FEA__INCLUDED_)
