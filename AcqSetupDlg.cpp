/*
* ==========================================================================
* Name:         AcqSetupDlg.cpp : Implementation of CAcqSetupDlg Dialog.
* Project:      Example
* Purpose:      This file contains implementation functions of CAcqSetupDlg Dialog.
*				This dialog is responsible for displaying / configuring Acquition 
*				parameters for selected device.
*				User can select this dialog from MCA->Acquire Setup... menu.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#include "stdafx.h"
#include "WinGAA.h"
#include "AcqSetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAcqSetupDlg dialog


CAcqSetupDlg::CAcqSetupDlg(DeviceAccess::IDeviceAccessPtr pIDevAcc, CWnd* pParent /*=NULL*/)
	: CDialog(CAcqSetupDlg::IDD, pParent)
{
	m_pIDevAcc = pIDevAcc;
	//{{AFX_DATA_INIT(CAcqSetupDlg)
	//}}AFX_DATA_INIT
}


void CAcqSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAcqSetupDlg)
	DDX_Control(pDX, IDC_EDIT_TIME, m_Preset);
	DDX_Control(pDX, IDC_EDIT_STOP, m_Stop);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_Value);
	DDX_Control(pDX, IDC_EDIT_START, m_Start);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAcqSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CAcqSetupDlg)
	ON_BN_CLICKED(IDC_BUTTON_HV, OnButtonHv)
	ON_BN_CLICKED(IDC_BUTTON_ROI, OnButtonRoi)
	ON_BN_CLICKED(IDC_RADIO_AREA, OnRadioEnabled)
	ON_BN_CLICKED(IDC_RADIO_COUNTS, OnRadioEnabled)
	ON_BN_CLICKED(IDC_RADIO_INTEGRAL, OnRadioEnabled)
	ON_BN_CLICKED(IDC_RADIO_NONE, OnRadioDisabled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAcqSetupDlg message handlers


//OnInitDialog - Init Acquition Setup Dialog - read values from device
BOOL CAcqSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (!SetupDevice ())
		return FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//SetupDevice - Read CAM values from device and set dialog controls
BOOL CAcqSetupDlg::SetupDevice ()
{
	_variant_t vVar;
	CString strString;
	BOOL bValid = FALSE;
    
    // Get Time Preset
	m_pIDevAcc->get_Param ((ParamCodes) DeviceAccess::CAM_L_PMLIVE, 0, 0, &vVar);
    if (vVar.lVal != 0)
	{
		m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_X_PLIVE, 0, 0, &vVar);
		strString.Format ("%f", vVar.dblVal);
		SetDlgItemText (IDC_EDIT_TIME, strString);
		CheckDlgButton (IDC_RADIO_LIVE, TRUE);
		bValid = TRUE;
	}
    else 
	{
		m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_L_PMREAL, 0, 0, &vVar);
		if (vVar.lVal != 0)
		{
			m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_X_PREAL, 0, 0, &vVar);
			strString.Format ("%f", vVar.dblVal);
			SetDlgItemText (IDC_EDIT_TIME, strString);
			CheckDlgButton (IDC_RADIO_REAL, TRUE);
			bValid = TRUE;
		}
	}

	if (!bValid)
	{
        AfxMessageBox ("Unsupported Preset Type", MB_OK | MB_ICONERROR);
        return FALSE;
	}
    
    // Get Comp Preset
	OnRadioEnabled ();

	m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_L_PTSCHAN, 0, 0, &vVar);
	strString.Format ("%d", vVar.lVal);
	SetDlgItemText (IDC_EDIT_STOP, strString);

	m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_L_PTECHAN, 0, 0, &vVar);
	strString.Format ("%d", vVar.lVal);
	SetDlgItemText (IDC_EDIT_START, strString);

	bValid = FALSE;
	m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_L_PMTOTALS, 0, 0, &vVar);
    if (vVar.lVal != 0)
	{
		m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_L_PTOTAL, 0, 0, &vVar);
		strString.Format ("%d", vVar.lVal);
		SetDlgItemText (IDC_EDIT_VALUE, strString);
		CheckDlgButton (IDC_RADIO_INTEGRAL, TRUE);
	}
	else
	{
		m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_L_PMLEVEL, 0, 0, &vVar);
		if (vVar.lVal != 0)
		{
			m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_L_PLEVEL, 0, 0, &vVar);
			strString.Format ("%d", vVar.lVal);
			SetDlgItemText (IDC_EDIT_VALUE, strString);
			CheckDlgButton (IDC_RADIO_COUNTS, TRUE);
		}
		else
		{
			m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_L_PMAREA, 0, 0, &vVar);
			if (vVar.lVal != 0)
			{
				m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_F_PAREA, 0, 0, &vVar);
				strString.Format ("%f", vVar.fltVal);
				SetDlgItemText (IDC_EDIT_VALUE, strString);
				CheckDlgButton (IDC_RADIO_AREA, TRUE);
			}
		}
	}

	if (!bValid)
	{
		SetDlgItemText (IDC_EDIT_VALUE, _T(""));
		CheckDlgButton (IDC_RADIO_NONE, TRUE);

		OnRadioDisabled ();
	}

	return TRUE;
}

//OnButtonHv - Click event on High Voltage button
void CAcqSetupDlg::OnButtonHv() 
{
	VARIANT vVar = (_variant_t) (long) 1L;
    m_pIDevAcc->put_Param ((ParamCodes) DeviceAccess::CAM_L_HVPSFSTAT, 0, 0, vVar);
}

//OnOK - Click on OK button - save the changes
void CAcqSetupDlg::OnOK() 
{	
	CString	strString;
	CString Value;
	CString Start;
	CString Stop;
    long lFlags = 0L;

    BOOL bComp = TRUE;
        
    // Get Time Preset
    if (IsDlgButtonChecked (IDC_RADIO_LIVE))
        lFlags = CanberraDataDisplayLib::aCountToLiveTime;
    else if (IsDlgButtonChecked (IDC_RADIO_REAL))
        lFlags = CanberraDataDisplayLib::aCountToRealTime;
    else
	{
		CDialog::OnOK();
        return;
	}
        
    // Get Comp Preset
    if (IsDlgButtonChecked (IDC_RADIO_INTEGRAL))
        lFlags = lFlags | CanberraDataDisplayLib::aCountToTotal;
    else if (IsDlgButtonChecked (IDC_RADIO_COUNTS))
        lFlags = lFlags | CanberraDataDisplayLib::aCountToLevel;
    else if (IsDlgButtonChecked (IDC_RADIO_AREA)) 
        lFlags = lFlags | CanberraDataDisplayLib::aCountToArea;
    else
        bComp = FALSE;

    // It is very important here to use Spectroscopy acquire setup
    // Setting the options as individual parameters is not suffucient to
    // set the preset in the device.
	m_Preset.GetWindowText (strString);
	m_Value.GetWindowText (Value);
	m_Start.GetWindowText (Start);
	m_Stop.GetWindowText (Stop);

    if (bComp)
        m_pIDevAcc->SpectroscopyAcquireSetup ((DeviceAccess::AcquisitionModes) lFlags, atof (Value), atol (Start), atol (Stop), atof (strString), 0.0);
	else
		m_pIDevAcc->SpectroscopyAcquireSetup ((DeviceAccess::AcquisitionModes) lFlags, atof (strString), 0, 0, 0.0, 0.0);

	CDialog::OnOK();
}

//OnButtonRoi - Use currnet Roi values
void CAcqSetupDlg::OnButtonRoi() 
{
	CString strString;
	VARIANT vVar;
	m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_L_LMARKCH, 0, 0, &vVar);
	strString.Format ("%d", vVar.lVal);
	SetDlgItemText (IDC_EDIT_START, strString);

	m_pIDevAcc->get_Param((ParamCodes) DeviceAccess::CAM_L_RMARKCH, 0, 0, &vVar);
	strString.Format ("%d", vVar.lVal);
	SetDlgItemText (IDC_EDIT_STOP, strString);
}


void CAcqSetupDlg::OnRadioEnabled () 
{
	m_Value.EnableWindow (TRUE);
	m_Start.EnableWindow (TRUE);
	m_Stop.EnableWindow (TRUE);
}

void CAcqSetupDlg::OnRadioDisabled () 
{
	m_Value.EnableWindow (FALSE);
	m_Start.EnableWindow (FALSE);
	m_Stop.EnableWindow (FALSE);	
}
