/*
* ==========================================================================
* Name:         AnalzerMenu.cpp : Implementation of CMainDialog
* Project:      Example
* Purpose:      This file contains different routines related to "Analysis and Reporting" menu.
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

#import "ReportView.tlb" no_namespace raw_interfaces_only

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//OnEditseq - Add/Delete sequence of automatic execution
void CMainDialog::OnEditseq () 
{
	LPDISPATCH lpDisp = GetCurrentDataSource ();

    // Create an editor
	CSeqAnalyzer dlgEditSeq (lpDisp);
	if (dlgEditSeq.DoModal () == IDOK)
		UpdateMenus ();
	lpDisp->Release ();
}

//OnExecute - Execute series of steps perform as specified in selected ASF file
void CMainDialog::OnExecute() 
{
    char strCurrentDir [255];
    char strAsfFiles [255];
           
    // Change current drive
	GetCurrentDirectory (255, strCurrentDir);
    GetEnvironmentVariable (_T("ASEQFILES"), strAsfFiles, 255);
	SetCurrentDirectory (strAsfFiles);
    
 	// Use the MFC Common Dialog to get a filename
	CFileDialog OpenDialog (TRUE, 
					 _T("*.ASF"), 
					 _T("*.ASF"), 
					 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
					 _T("Sequence Files|*.ASF||"));

    if (OpenDialog.DoModal () != IDOK)
		return;

	ISequenceAnalyzerPtr m_pISeqAnalyzer;
	HRESULT hRes = m_pISeqAnalyzer.CreateInstance(__uuidof(SequenceAnalyzer)); 
	if (FAILED(hRes))
	{
		if (IDCANCEL == AfxMessageBox (_T("Failed to initialize Sequence Analyzer Component. Do you wish to continue?"), MB_ICONQUESTION | MB_YESNO))
			return;
	}

	LPDISPATCH lpDisp = GetCurrentDataSource ();

	try
	{
		CComPtr<IReportViewer> pIReportViewer;
		IUnknown *pUnknown = m_cIReportWin.GetControlUnknown(); 
		LPDISPATCH pTemp = NULL; 
		short sStart = 0;
		if (pUnknown)
		{
			pUnknown->QueryInterface(&pTemp); 
			pTemp->QueryInterface( __uuidof(IReportViewer), (void**)&pIReportViewer);
			if (pIReportViewer)
			{
// TO display output in reporter window
				m_pISeqAnalyzer->Analyze (lpDisp, &sStart, 
										  (_bstr_t) OpenDialog.GetPathName (), 
										  VARIANT_TRUE, VARIANT_FALSE, VARIANT_FALSE, VARIANT_FALSE, 
										  NULL, pIReportViewer);
// TO display output in text file
//			m_pISeqAnalyzer->Analyze (lpDisp, &sStart, 
//									  (_bstr_t) OpenDialog.GetPathName (), 
//									  VARIANT_TRUE, VARIANT_FALSE, VARIANT_FALSE, VARIANT_FALSE, 
//									  (_bstr_t) _T("c:\\Output.txt"), NULL);
			}
		}
	}
	catch (COleDispatchException* pException)
	{
		char chStr [255];
		pException->GetErrorMessage (chStr, 255);
		AfxMessageBox (chStr);
	}
   
    // Restore current Dir
	SetCurrentDirectory (strCurrentDir);

	lpDisp->Release ();
	m_pISeqAnalyzer.Release ();
}


//OnExecuteCurrent - Execute series of steps perform as previously selected step
void CMainDialog::OnExecuteCurrent () 
{
	ISequenceAnalyzerPtr m_pISeqAnalyzer;
	HRESULT hRes = m_pISeqAnalyzer.CreateInstance(__uuidof(SequenceAnalyzer)); 
	if (FAILED(hRes))
	{
		if (IDCANCEL == AfxMessageBox (_T("Failed to initialize Sequence Analyzer Component. Do you wish to continue?"), MB_ICONQUESTION | MB_YESNO))
			return;
	}

	LPDISPATCH lpDisp = GetCurrentDataSource ();

	try
	{
		CComPtr<IReportViewer> pIReportViewer;
		IUnknown *pUnknown = m_cIReportWin.GetControlUnknown(); 
		LPDISPATCH pTemp = NULL; 
		short sStart = 0;
		if (pUnknown)
		{
			pUnknown->QueryInterface(&pTemp); 
			pTemp->QueryInterface( __uuidof(IReportViewer), (void**)&pIReportViewer);
			if (pIReportViewer)
				m_pISeqAnalyzer->Analyze (lpDisp, &sStart, NULL, 
										  VARIANT_TRUE, VARIANT_FALSE, VARIANT_FALSE, VARIANT_FALSE, 
										  NULL, pIReportViewer);
		}
	}
	catch (COleDispatchException* pException)
	{
		char chStr [255];
		pException->GetErrorMessage (chStr, 255);
		AfxMessageBox (chStr);
	}

	lpDisp->Release ();
	m_pISeqAnalyzer.Release ();
}

//OnShowReportWinodow - Show / Hide Report Window
void CMainDialog::OnShowReportWinodow () 
{
	CMenu* pSubMenu = GetMenu ()->GetSubMenu (3);
	UINT unState = pSubMenu->GetMenuState (IDM_ANALYSIS_SHOWREPORT, MF_BYCOMMAND);
	if (unState == MF_CHECKED)
		unState = MF_UNCHECKED;
	else
		unState = MF_CHECKED;

	pSubMenu->CheckMenuItem (IDM_ANALYSIS_SHOWREPORT, MF_BYCOMMAND | unState);
	ResizeWindow (unState);
}

//OnPrintReport - Print text from Report Window
void CMainDialog::OnPrintReport () 
{
    // You could show the MS common print dlg and then pass in the
    // printer name to print out
	m_cIReportWin.PrintOut (_T(""));
}

//OnCopyReport - Copy Text from report window
void CMainDialog::OnCopyReport () 
{
    m_cIReportWin.CopyAll ();
}

//OnCopySelectedReport - Copy selected text from Report window
void CMainDialog::OnCopySelectedReport () 
{
    m_cIReportWin.Copy ();
}

//OnSaveReport - Save text of the report window to *.Rpt file
void CMainDialog::OnSaveReport () 
{
    // Get a default file name
	CString strFile; 

    if (m_cIMvc.GetNumberOfSources () > 0)
	{
        // Remove extension
        strFile = m_cIMvc.GetCurrentDataSourceName ();
        if (m_cIMvc.GetCurrentDataSourceType () == CanberraDataDisplayLib::SpectroscopyFile)
			{
            int i = strFile.Find (_T("."), 0);
            if (i > 0)
                strFile = strFile.Left (i);
			}
	}

    strFile = strFile + _T(".rpt");
    
	// Use the MFC Common Dialog to get a filename
	CFileDialog OpenDialog (FALSE, 
					 _T("*.rpt"), 
					 strFile, 
					 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
					 _T("Text Report Files | *.rpt||"));

    if (OpenDialog.DoModal () == IDOK)
		m_cIReportWin.SaveText (OpenDialog.GetPathName (), TRUE);
}
