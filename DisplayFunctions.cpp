/*
* ==========================================================================
* Name:         DisplayFunctions.cpp : Implementation of CMainDialog
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

//Close up any open adjust windows
void CMainDialog::CloseAdjust ()
{
	m_pAdjustDlg->ShowWindow (SW_HIDE);
}


//Utility to handle displaying a source
void CMainDialog::DisplaySource(LPDISPATCH lpNewVal)
{
	if (lpNewVal)
		m_cIMvc.SetCurrentDataSource (lpNewVal);

    UpdateMenus ();
}

//UpdateMenus - Update menus after changing each selection. Enable/disable sub-menus
void CMainDialog::UpdateMenus ()
{
    BOOL bEnabled = (m_cIMvc.GetNumberOfSources () != 0);
	UINT unState = bEnabled ? MF_ENABLED : MF_DISABLED | MF_GRAYED;

	// Enable / Disable File menu options...
	CMenu* pSubMenu = GetMenu ()->GetSubMenu (0);
	pSubMenu->EnableMenuItem (IDM_FILE_SAVE,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_FILE_SAVEAS,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_FILE_CLOSE,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_FILE_CLOSEALL,MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_FILE_PRINT,MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_FILE_COPY,MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_FILE_EXPORT,MF_BYCOMMAND | unState);

	// Enable / Disable MCA menu options...
    // Allow Mca stuff only on detectors
	if (bEnabled)
		unState = IsDetector () ? MF_ENABLED : MF_DISABLED | MF_GRAYED;

	pSubMenu = GetMenu ()->GetSubMenu (1);
	pSubMenu->EnableMenuItem (IDM_MCA_ACQSETUP, MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_MCA_ACQSTART, MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_MCA_ACQSTOP,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_MCA_ACQCLEAR, MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_MCA_ADJUST,	MF_BYCOMMAND | unState);

	// Enable / Disable Display menu options...
	unState = bEnabled ? MF_ENABLED : MF_DISABLED | MF_GRAYED;

	pSubMenu = GetMenu ()->GetSubMenu (2);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_EXPAND,		MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_ZOOM_MODE,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_ZOOM_OUT,		MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_SCALE_LOG,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_SCALE_LINEAR, MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_SCALE_AUTO,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_RIOS_NEXT,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_RIOS_PREV,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_RIOS_ADD,		MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_ROIS_DEL,		MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_RIOS_CLEAR,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_RIOS_LOAD,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_RIOS_STORE,	MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_NUCLINES_SHOW,MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_NUCLINES_NNUC,MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_NUCLINES_PNUC,MF_BYCOMMAND | unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_NUCLINES_NLINE,MF_BYCOMMAND| unState);
	pSubMenu->EnableMenuItem (IDM_DISPLAY_NUCLINES_PLINE,MF_BYCOMMAND| unState);

	// Check / Uncheck Display menus
	pSubMenu->CheckMenuItem (IDM_DISPLAY_EXPAND, MF_BYCOMMAND | (m_cIMvc.GetExpandMode () ? MF_CHECKED : MF_UNCHECKED));
	pSubMenu->CheckMenuItem (IDM_DISPLAY_ZOOM_MODE, MF_BYCOMMAND | (m_cIMvc.GetActivateZoom () ? MF_CHECKED : MF_UNCHECKED));
	pSubMenu->CheckMenuItem (IDM_DISPLAY_SCALE_LOG, MF_BYCOMMAND | (!m_pPrefs->Linear ? MF_CHECKED : MF_UNCHECKED));
	pSubMenu->CheckMenuItem (IDM_DISPLAY_SCALE_LINEAR, MF_BYCOMMAND | (m_pPrefs->Linear ? MF_CHECKED : MF_UNCHECKED));

	// Enable / Disable Analysis menu options...
	pSubMenu = GetMenu ()->GetSubMenu (3);
	pSubMenu->EnableMenuItem (IDM_ANALYSIS_EDITSEQ,MF_BYCOMMAND| unState);
	pSubMenu->EnableMenuItem (IDM_ANALYSIS_EXECUTE,MF_BYCOMMAND| unState);
	pSubMenu->EnableMenuItem (IDM_ANALYSIS_EXECURR,MF_BYCOMMAND| unState);
	pSubMenu->EnableMenuItem (IDM_ANALYSIS_PRINTREPORT,MF_BYCOMMAND| unState);
	pSubMenu->EnableMenuItem (IDM_ANALYSIS_COPYREPORT,MF_BYCOMMAND| unState);
	pSubMenu->EnableMenuItem (IDM_ANALYSYS_COPYSELECTED,MF_BYCOMMAND| unState);
	pSubMenu->EnableMenuItem (IDM_ANALYSIS_SAVEREPORT,MF_BYCOMMAND| unState);

	// Enable / Disable Datasource menu options...
    // Allow datasource only if more than one open
	pSubMenu = GetMenu ()->GetSubMenu (4);
	if (m_cIMvc.GetNumberOfSources () > 1)
	{
		pSubMenu->EnableMenuItem (IDM_DATASOURCE_NEXT,MF_BYCOMMAND| unState);
		pSubMenu->EnableMenuItem (IDM_DATASOURCE_PREV,MF_BYCOMMAND| unState);
	}
	else
	{
		pSubMenu->EnableMenuItem (IDM_DATASOURCE_NEXT,MF_BYCOMMAND| MF_DISABLED | MF_GRAYED);
		pSubMenu->EnableMenuItem (IDM_DATASOURCE_PREV,MF_BYCOMMAND| MF_DISABLED | MF_GRAYED);
	}

	// Enable / Disable Edit menu options...
	// Allow view calibrations on a file only
	pSubMenu = GetMenu ()->GetSubMenu (5);
   	if (bEnabled && m_cIMvc.GetCurrentDataSourceType () == CanberraDataDisplayLib::SpectroscopyFile)
		pSubMenu->EnableMenuItem (IDM_EDIT_SHOWCALIB,MF_BYCOMMAND| unState);
	else
		pSubMenu->EnableMenuItem (IDM_EDIT_SHOWCALIB,MF_BYCOMMAND| MF_DISABLED | MF_GRAYED);
	pSubMenu->EnableMenuItem (IDM_EDIT_SAMPLEEDITOR,MF_BYCOMMAND| unState);

	// Add name to title bar
	
		CString strBuffer;
		strBuffer.Format (_T("Canberra"));
		SetWindowText (strBuffer);
	
}