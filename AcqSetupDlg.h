/*
* ==========================================================================
* Name:         AcqSetupDlg.h : Header of CAcqSetupDlg Dialog.
* Project:      Example
* Purpose:      This file contains declaration functions of CAcqSetupDlg Dialog.
*				This dialog is responsible for displaying / configuring Acquition 
*				parameters for selected device.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#if !defined(AFX_ACQSETUPDLG_H__B2F57AA0_41DF_474D_B0FF_95BA93CDCFBB__INCLUDED_)
#define AFX_ACQSETUPDLG_H__B2F57AA0_41DF_474D_B0FF_95BA93CDCFBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAcqSetupDlg dialog

class CAcqSetupDlg : public CDialog
{
// Construction
public:
	CAcqSetupDlg (DeviceAccess::IDeviceAccessPtr pIDevAcc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAcqSetupDlg)
	enum { IDD = IDD_DIALOG_ACQSETUP };
	CEdit	m_Preset;
	CEdit	m_Stop;
	CEdit	m_Value;
	CEdit	m_Start;
	//}}AFX_DATA

private:
	BOOL SetupDevice ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAcqSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAcqSetupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonHv();
	virtual void OnOK();
	afx_msg void OnButtonRoi();
	afx_msg void OnRadioEnabled();
	afx_msg void OnRadioDisabled();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	DeviceAccess::IDeviceAccessPtr m_pIDevAcc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACQSETUPDLG_H__B2F57AA0_41DF_474D_B0FF_95BA93CDCFBB__INCLUDED_)
