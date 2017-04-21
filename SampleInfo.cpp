/*
* ==========================================================================
* Name:         SampleInfo.cpp : Implementation of CSampleInfo Dialog.
* Project:      Example
* Purpose:      This file contains implementation functions of CSampleInfo Dialog.
*				This dialog is responsible for displaying different Sample Info 
*				parameters for selected datasource.
*				User can display this info from Edit->Sample Editor menu.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#include "stdafx.h"
#include "WinGAA.h"
#include "SampleInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleInfo dialog

CSampleInfo::CSampleInfo(CMvc* lpDispatch, CWnd* pParent /*=NULL*/)
	: CDialog(CSampleInfo::IDD, pParent)
{
	m_lpMvc = lpDispatch;

	//{{AFX_DATA_INIT(CSampleInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSampleInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSampleInfo, CDialog)
	//{{AFX_MSG_MAP(CSampleInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleInfo message handlers

BOOL CSampleInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	_variant_t vVar;
	CString strString;

	try 
	{
		vVar = m_lpMvc->GetParam ((ParamCodes) DeviceAccess::CAM_T_STITLE, 0, 0);
		strString = vVar.bstrVal;
		if (vVar.bstrVal) SysFreeString (vVar.bstrVal);
	}
	catch (...)
	{
		strString = _T("");
	}
	SetDlgItemText (IDC_EDIT_STITLE, strString);

	try 
	{
		vVar = m_lpMvc->GetParam((ParamCodes) DeviceAccess::CAM_T_SCOLLNAME, 0, 0);
		strString = vVar.bstrVal;
		// _variant_t releases string memory when they go out of scope, 
		// but here they are reused before going out of scope... 
		// so have to release the memory explicitely to clean memory
		if (vVar.bstrVal) SysFreeString (vVar.bstrVal);
	}
	catch (...)
	{
		strString = _T("");
	}
	SetDlgItemText (IDC_EDIT_NAME, strString);

	try 
	{
		vVar = m_lpMvc->GetParam((ParamCodes) DeviceAccess::CAM_T_SDESC1, 0, 0);
		strString = vVar.bstrVal;
		if (vVar.bstrVal) SysFreeString (vVar.bstrVal);
	}
	catch (...)
	{
		strString = _T("");
	}
	SetDlgItemText (IDC_EDIT_SDESC, strString);

	try 
	{
		vVar = m_lpMvc->GetParam((ParamCodes) DeviceAccess::CAM_T_SIDENT, 0, 0);
		strString = vVar.bstrVal;
		if (vVar.bstrVal) SysFreeString (vVar.bstrVal);
	}
	catch (...)
	{
		strString = _T("");
	}
	SetDlgItemText (IDC_EDIT_SID, strString);

	try 
	{
		vVar = m_lpMvc->GetParam((ParamCodes) DeviceAccess::CAM_T_STYPE, 0, 0);
		strString = vVar.bstrVal;
		if (vVar.bstrVal) SysFreeString (vVar.bstrVal);
	}
	catch (...)
	{
		strString = _T("");
	}
	SetDlgItemText (IDC_EDIT_TYPE, strString);

	try 
	{
		vVar = m_lpMvc->GetParam((ParamCodes) DeviceAccess::CAM_F_SQUANT, 0, 0);
		strString.Format ("%f", vVar.fltVal);
	}
	catch (...)
	{
		strString = _T("0.0");
	}
	SetDlgItemText (IDC_EDIT_QTY, strString);

	try 
	{
		vVar = m_lpMvc->GetParam((ParamCodes) DeviceAccess::CAM_F_SQUANTERR, 0, 0);
		strString.Format ("%f", vVar.fltVal);
	}
	catch (...)
	{
		strString = _T("0.0");
	}
	SetDlgItemText (IDC_EDIT_UNC, strString);

	try 
	{
		vVar = m_lpMvc->GetParam((ParamCodes) DeviceAccess::CAM_T_SUNITS, 0, 0);
		strString = vVar.bstrVal;
		if (vVar.bstrVal) SysFreeString (vVar.bstrVal);
	}
	catch (...)
	{
		strString = _T("");
	}
	SetDlgItemText (IDC_EDIT_UNITS, strString);

	try 
	{
		vVar = m_lpMvc->GetParam((ParamCodes) DeviceAccess::CAM_X_ASTIME, 0, 0);
		strString = vVar.bstrVal;
		if (vVar.bstrVal) SysFreeString (vVar.bstrVal);
	}
	catch (...)
	{
		strString = _T("");
	}
	SetDlgItemText (IDC_EDIT_ACQSTTIM, strString);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSampleInfo::OnOK() 
{
	VARIANT vVar;
	CString strString;

	try 
	{
		GetDlgItemText (IDC_EDIT_STITLE, strString);
		vVar = (_variant_t) (_bstr_t) strString;
		m_lpMvc->SetParam ((ParamCodes) DeviceAccess::CAM_T_STITLE, 0, 0, vVar);

		GetDlgItemText (IDC_EDIT_NAME, strString);
		vVar = (_variant_t) (_bstr_t) strString;
		m_lpMvc->SetParam ((ParamCodes) DeviceAccess::CAM_T_SCOLLNAME, 0, 0, vVar);

		GetDlgItemText (IDC_EDIT_SDESC, strString);
		vVar = (_variant_t) (_bstr_t) strString;
		m_lpMvc->SetParam ((ParamCodes) DeviceAccess::CAM_T_SDESC1, 0, 0, vVar);

		GetDlgItemText (IDC_EDIT_SID, strString);
		vVar = (_variant_t) (_bstr_t) strString;
		m_lpMvc->SetParam ((ParamCodes) DeviceAccess::CAM_T_SIDENT, 0, 0, vVar);

		GetDlgItemText (IDC_EDIT_TYPE, strString);
		vVar = (_variant_t) (_bstr_t) strString;
		m_lpMvc->SetParam ((ParamCodes) DeviceAccess::CAM_T_STYPE, 0, 0, vVar);

		GetDlgItemText (IDC_EDIT_QTY, strString);
		vVar = (_variant_t) (float) atof (strString);
		strString.Format ("%f", vVar.fltVal);
		m_lpMvc->SetParam ((ParamCodes) DeviceAccess::CAM_F_SQUANT, 0, 0, vVar);

		GetDlgItemText (IDC_EDIT_UNC, strString);
		vVar = (_variant_t) (float) atof (strString);
		strString.Format ("%f", vVar.fltVal);
		m_lpMvc->SetParam ((ParamCodes) DeviceAccess::CAM_F_SQUANTERR, 0, 0, vVar);

		GetDlgItemText (IDC_EDIT_UNITS, strString);
		vVar = (_variant_t) (_bstr_t) strString;
		m_lpMvc->SetParam ((ParamCodes) DeviceAccess::CAM_T_SUNITS, 0, 0, vVar);

		GetDlgItemText (IDC_EDIT_ACQSTTIM, strString);
		vVar = (_variant_t) (_bstr_t) strString;
		m_lpMvc->SetParam ((ParamCodes) DeviceAccess::CAM_X_ASTIME, 0, 0, vVar);
	}
	catch (...)
	{
		AfxMessageBox (_T("Failed to save current settings"), MB_OK | MB_ICONERROR);
	}
	
	CDialog::OnOK();
}
