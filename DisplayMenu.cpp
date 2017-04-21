/*
* ==========================================================================
* Name:         DisplayMenu.cpp : Implementation of CMainDialog
* Project:      Example
* Purpose:      This file contains different routines related to "Display" menu.
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//OnExpand - Turn On / Off Expand Window
void CMainDialog::OnExpand() 
{
	m_cIMvc.SetExpandMode (!m_cIMvc.GetExpandMode ());
    UpdateMenus	();
}


// OnZoomMode - Turn On / Off Zoom Mode
void CMainDialog::OnZoomMode() 
{
    m_cIMvc.SetActivateZoom (!m_cIMvc.GetActivateZoom ());
    UpdateMenus	();
}

// OnZoomOut - Start Zoom Out
void CMainDialog::OnZoomOut() 
{
    m_cIMvc.ZoomOut ();
}

//OnScaleLog - Set to Log Scale
void CMainDialog::OnScaleLog() 
{
    m_cIMvc.SetLinearScale (FALSE);
    m_pPrefs->Linear = FALSE;
    UpdateMenus ();
	
}

//OnScaleLinear - Set to Linear Scale
void CMainDialog::OnScaleLinear() 
{
    m_cIMvc.SetLinearScale (TRUE);
    m_pPrefs->Linear = TRUE;
    UpdateMenus ();	
}

//OnScaleAuto - Set to Automatic Scale
void CMainDialog::OnScaleAuto() 
{
	CMenu* pSubMenu = GetMenu ()->GetSubMenu (2);
	UINT unState = pSubMenu->GetMenuState (IDM_DISPLAY_SCALE_AUTO, MF_BYCOMMAND);
	pSubMenu->CheckMenuItem (IDM_DISPLAY_SCALE_AUTO, MF_BYCOMMAND | (unState == MF_CHECKED ? MF_UNCHECKED : MF_CHECKED));

    m_cIMvc.SetAutoScale (!m_cIMvc.GetAutoScale ());
    UpdateMenus ();
}

//OnRiosNext - Set to Next Roi
void CMainDialog::OnRiosNext() 
{
   m_cIMvc.NextRoi ();	
}

//OnRiosPrev - Set to Previous Roi
void CMainDialog::OnRiosPrev() 
{
    m_cIMvc.PreviousRoi ();
}

//OnRiosAdd - Add Roi
void CMainDialog::OnRiosAdd() 
{
    m_cIMvc.AddRoi ();
}

//OnRoisDel - Delete Roi
void CMainDialog::OnRoisDel() 
{
	m_cIMvc.DeleteRoi ();
}

//OnRiosClear - Clear Rois
void CMainDialog::OnRiosClear() 
{
	m_cIMvc.DeleteAllRois ();	
}

//OnRiosLoad - Load Roi from Roi/Cnf file
void CMainDialog::OnRiosLoad() 
{
	// Use the MFC Common Dialog to get a filename
	CFileDialog OpenDialog (TRUE, 
					 _T("*.ROI"), 
					 _T("*.ROI"), 
					 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
					 _T("Roi Files|*.ROI|Cam Files|*.CNF||"));

    if (OpenDialog.DoModal () == IDOK)
		{
		if (AfxMessageBox (_T("Would you like attempt to load Rois by Energy?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			m_cIMvc.LoadRois (OpenDialog.GetPathName (), TRUE);
		else
			m_cIMvc.LoadRois (OpenDialog.GetPathName (), FALSE);
		}	
}

//OnRiosStore - Store Roi to Roi/Cnf file
void CMainDialog::OnRiosStore() 
{
	// Use the MFC Common Dialog to get a filename
	CFileDialog OpenDialog (FALSE, 
					 _T("*.ROI"), 
					 _T("*.ROI"), 
					 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
					 _T("Roi Files|*.ROI|Cam Files|*.CNF||"));

    if (OpenDialog.DoModal () == IDOK)
		m_cIMvc.SaveRois (OpenDialog.GetPathName (), TRUE);
}

//OnNuclinesShow - Show Nuclide
void CMainDialog::OnNuclinesShow() 
{
	CMenu* pSubMenu = GetMenu ()->GetSubMenu (2);
	UINT unState = pSubMenu->GetMenuState (IDM_DISPLAY_NUCLINES_SHOW, MF_BYCOMMAND);
	pSubMenu->CheckMenuItem (IDM_DISPLAY_NUCLINES_SHOW, MF_BYCOMMAND | (unState == MF_CHECKED ? MF_UNCHECKED : MF_CHECKED));

	unState = pSubMenu->GetMenuState (IDM_DISPLAY_NUCLINES_SHOW, MF_BYCOMMAND);
	pSubMenu->CheckMenuItem (IDM_DISPLAY_NUCLINES_SHOW, MF_BYCOMMAND | (unState == MF_CHECKED ? MF_UNCHECKED : MF_CHECKED));

//	if (unState == MF_CHECKED)

	BOOL bShowPeak = m_cIMvc.GetShowSpectralPeakInformation ();
	m_cIMvc.SetShowSpectralPeakInformation (!bShowPeak);
	m_cIMvc.SetShowSpectralNuclideAnnotationsLines (!bShowPeak);
}

//OnNuclinesNext - Go to Next Nuclide
void CMainDialog::OnNuclinesNext() 
{
    if (m_cIMvc.GetShowSpectralNuclideAnnotationsLines ())
		m_cIMvc.NextNuclide ();
}

//OnNuclinesPrev - Go to Previous Nuclide
void CMainDialog::OnNuclinesPrev() 
{
    if (m_cIMvc.GetShowSpectralNuclideAnnotationsLines ())
		m_cIMvc.PreviousNuclide ();
}

//OnNuclinesNextNucline - Go to Next Nuclide Line
void CMainDialog::OnNuclinesNextNucline() 
{
    if (m_cIMvc.GetShowSpectralNuclideAnnotationsLines ())
		m_cIMvc.NextNuclideLine ();	
}

//OnNuclinesPrevNucline - Go to Previous Nuclide Line
void CMainDialog::OnNuclinesPrevNucline() 
{
    if (m_cIMvc.GetShowSpectralNuclideAnnotationsLines ())
		m_cIMvc.PreviousNuclideLine ();
}

//OnPrefence - Set Plot/Display preferences
void CMainDialog::OnPrefence() 
{
	CPreferences Prefs (m_pPrefs);
	if (Prefs.DoModal () == IDOK)
	{
		SetPrefs (Prefs.m_LibraryName);	// Update Screen
		StorePrefs ();	// Store to Registry
		UpdateMenus ();	// Update menus
	}
}