/*
* ==========================================================================
* Name:         MCAMenu.cpp : Implementation of CMainDialog
* Project:      Example
* Purpose:      This file contains different routines related to "Mca" menu.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#include "stdafx.h"
#include "WinGAA.h"
#include "MAINDlg.h"

#include "AcqSetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace DeviceAccess;


//OnAcqsetup - Setup Acquation
void CMainDialog::OnAcqsetup () 
{
	IDeviceAccessPtr m_pIDevAcc = m_cIMvc.GetCurrentDataSource ();
	CAcqSetupDlg Dlg (m_pIDevAcc);
	Dlg.DoModal ();
	m_pIDevAcc.Release ();
}


//OnAcqstart - Start Acq.
void CMainDialog::OnAcqstart () 
{
	OnAcqclear ();

	IDeviceAccessPtr m_pIDevAcc = m_cIMvc.GetCurrentDataSource ();
	m_pIDevAcc->AcquireStart ();
	m_pIDevAcc.Release ();
}


//OnAcqstop - Stop Acq.
void CMainDialog::OnAcqstop () 
{
	IDeviceAccessPtr m_pIDevAcc = m_cIMvc.GetCurrentDataSource ();
	m_pIDevAcc->AcquirePause (aNormalStop);
	m_pIDevAcc.Release ();
}

//OnAcqclear - Clear acquition
void CMainDialog::OnAcqclear() 
{
	IDeviceAccessPtr m_pIDevAcc = m_cIMvc.GetCurrentDataSource ();

	// You could also call m_cIMvc.Clear ()
	m_pIDevAcc->Clear ();
	m_pIDevAcc.Release ();
}

// OnAdjust - Pop up adjust control
void CMainDialog::OnAdjust() 
{
	IDeviceAccessPtr m_pIDevAcc = m_cIMvc.GetCurrentDataSource ();
	m_pAdjustDlg->SetDevice (m_pIDevAcc);
	m_pAdjustDlg->ShowWindow (SW_SHOW);
	m_pIDevAcc.Release ();
}