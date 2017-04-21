/*
* ==========================================================================
* Name:         FileMenu.cpp : Implementation of CMainDialog
* Project:      Example
* Purpose:      This file contains different routines related to "File" menu.
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

#import "camdialog.tlb" no_namespace raw_interfaces_only

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// OnOpen - Open Cam File / Detector
void CMainDialog::OnOpen() 
{
	CComPtr<ICamDlg> pCamDlg;
	if (FAILED(pCamDlg.CoCreateInstance(__uuidof(CamDlg))))
		return;

	try {
		VARIANT_BOOL bCancelled;
		BSTR szFile;
		VARIANT_BOOL bReadOnly;
		OpenDataSourceType lDataSource;
		LPCTSTR Title = _T("");
		LPCTSTR Dir = _T("");
		LPCTSTR Extension = _T("*.CNF");
		long Type = 0;
		long ConfigRec = 0;

		pCamDlg->OpenDataSource(&bCancelled, &szFile, &bReadOnly, &lDataSource, (DataSourceOpenMask) camdlgOpenDefault, 
								(bstr_t) Title, (bstr_t) Dir, (bstr_t) Extension, (bstr_t) _T(""), &Type, &ConfigRec, (bstr_t) _T(""));

		if (!bCancelled)
		{
			if (lDataSource == camdlgDetector)
			{
				OpenDetector ((char*) (_bstr_t) szFile, CanberraDataDisplayLib::ReadWrite,
							  camdlgDetector);
			}
			else
				OpenFile ((char*) (_bstr_t) szFile, CanberraDataDisplayLib::ReadWrite);

// NOTE (For Canberra Genie Component Users Only):
//------------------------------------------------
//If you plan to use the Spectral Data spreadsheet, the
//Extended Cursor Information Display or the
//Nuclide Annotation lines then you might want to try opening
//the file with DirectAccess:
//
//	bReadOnly ? CanberraDataDisplayLib::ReadOnly  | CanberraDataDisplayLib::DirectAccess : 
//				CanberraDataDisplayLib::ReadWrite | CanberraDataDisplayLib::DirectAccess
//
//This might have some side effects :
//Since direct access bypasses the server (VDM) not all
//clients of the same file will not be notified of updates
//to the file. This may or may not be relevant depending on your
//application. Consider running a peak-area analysis on the
//currently displayed datasource. Had the file been open
//directaccess, then the MVC will not update the ROIs because it
//does not know the file changed
			}
		}
	catch (COleDispatchException* pException)
		{
		char chStr [255];
		pException->GetErrorMessage (chStr, 255);
		AfxMessageBox (chStr);
		}

	pCamDlg.Release ();
}

// OnSave - Save Current opened datasource
void CMainDialog::OnSave() 
{
    m_cIMvc.Save (m_cIMvc.GetCurrentDataSourceName (), FALSE);
    UpdateMenus ();
}


// OnSaveAs - Save Current opened datasource with different name
void CMainDialog::OnSaveAs() 
{   
// Use the MFC Common Dialog to get a filename
	CFileDialog OpenDialog (FALSE, 
					 _T("*.txt"), 
					 NULL, 
					 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
					 _T("CAM File (*.cnf) |*.cnf|All Files (*.*)|*.*||"));

    if (OpenDialog.DoModal () == IDOK)
		m_cIMvc.Save (OpenDialog.GetPathName (), FALSE);
}

// OnFileClose - Close opened data source
void CMainDialog::OnFileClose () 
{	
	CString strMsg;
	strMsg.Format (_T("%s is modified. Do you want to save it?"), m_cIMvc.GetCurrentDataSourceName ());
	if (m_cIMvc.GetIsModified () && AfxMessageBox (strMsg, MB_ICONQUESTION | MB_YESNO) == IDYES)
		m_cIMvc.Close (CanberraDataDisplayLib::Update);
	else
		m_cIMvc.Close (CanberraDataDisplayLib::NoUpdate);

	// clear report window on close
	m_cIReportWin.Clear ();
    CloseAdjust ();
    UpdateMenus ();
}

// OnCloseAll - Close all opened data sources
void CMainDialog::OnCloseall() 
{
	// user can call this function directly too...
    //m_cIMvc.CloseAll ();

	// traverse thro' all opened data sources
	while (m_cIMvc.GetNumberOfSources () > 0)
	{
		CString strMsg;
		strMsg.Format (_T("%s is modified. Do you want to save it?"), m_cIMvc.GetCurrentDataSourceName ());
		if (m_cIMvc.GetIsModified () && AfxMessageBox (strMsg, MB_ICONQUESTION | MB_YESNO) == IDYES)
			m_cIMvc.Close (CanberraDataDisplayLib::Update);
		else
			m_cIMvc.Close (CanberraDataDisplayLib::NoUpdate);

		m_cIMvc.NextSource ();
	}

    CloseAdjust ();
    UpdateMenus ();
}

// OnPrint - Print request
void CMainDialog::OnPrint () 
{
    m_cIMvc.PrintPlotDialog	();
}


// OnCopy - Copy to clip board buffer
void CMainDialog::OnCopy() 
{
	m_cIMvc.CopyToClipBoard ();
}


// OnExport - Export data
void CMainDialog::OnExport() 
{
    // Remove extension
    CString strFile = m_cIMvc.GetCurrentDataSourceName ();

    if (m_cIMvc.GetCurrentDataSourceType () == CanberraDataDisplayLib::SpectroscopyFile)
	{
        int i = strFile.Find (_T("."), 0);
        if (i > 0)
            strFile = strFile.Left (i);
	}

    strFile.Format (_T("%s.txt"), strFile);

 	// Use the MFC Common Dialog to get a filename
	CFileDialog OpenDialog (FALSE, 
					 _T("*.txt"), 
					 _T("*.txt"), 
					 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
					 _T("Text Files | *.txt||"));

    if (OpenDialog.DoModal () == IDOK)
		m_cIMvc.ExportData (OpenDialog.GetPathName ());
}


// OnExit - Exit Window
void CMainDialog::OnExit() 
{
	// first close open source
	OnCloseall ();

	// end dialog
	CDialog::OnOK ();	
}

