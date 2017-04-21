/*
* ==========================================================================
* Name:         EditMenu.cpp : Implementation of CMainDialog
* Project:      Example
* Purpose:      This file contains different routines related to "Edit" menu.
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
#include "sampleinfo.h"
#include "calibration.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//OnCertificateFileEditor - Bring up certificate file editor
void CMainDialog::OnCertificateFileEditor() 
{
    CString strPath;
    char strExe [255] = {0};
	GetEnvironmentVariable (_T("EXEFILES"), strPath.GetBuffer (255), 255);
	_tcscpy (strExe, strPath);
	_tcscat (strExe, _T("\\CFED.EXE"));

    // Disable myself during the execute
	EnableWindow (FALSE);

	STARTUPINFO		startup_info;
	startup_info.cb = sizeof(startup_info);
	startup_info.lpReserved = NULL;
	startup_info.lpDesktop = NULL;
	startup_info.lpTitle = "Testing";
	startup_info.dwFlags = 0;
	startup_info.cbReserved2 = 0;
	startup_info.lpReserved2 = NULL;

	PROCESS_INFORMATION	process_info;

	CreateProcess (strExe, NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW,
				   NULL, NULL, &startup_info, &process_info);

	// wait until user closes the Editor window
    if (process_info.hProcess != 0)
	{
		// wait for the process to end in a message loop so we don't block COM messages
		long cObjects = 1;		// wait on one handle
		DWORD result;
		MSG msg;

		// loop until we get a quit message or the handle has signaled
		while (TRUE)
		{
			// pump through messages, note don't use MFCPeekAndPump here
			// since this routine can be called during shutdown and MFC
			// will assert if we pump during the shutdown 
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) 
					break;
				DispatchMessage(&msg); 
			}
			
			// Wait for any message sent or posted to this queue 
			// or for one of the passed handles be set to signaled.
			result = MsgWaitForMultipleObjects (cObjects, &process_info.hProcess, FALSE, INFINITE, QS_ALLINPUT);
			
			// the result tells us the type of event we have.
			if (result == (WAIT_OBJECT_0 + cObjects))// New messages have arrived.
				continue;// Continue to the top of the while loop to dispatch them and resume waiting.
			else if (result == WAIT_TIMEOUT)// the wait has timed out
				break;
			else // the handle has signalled, or abandoned
				break;
		}

		CloseHandle (process_info.hProcess);
	}

	EnableWindow (TRUE);
}


// OnShowCalibrations - Show calibration information window
void CMainDialog::OnShowCalibrations () 
{
	IDataAccessPtr	m_pIDataAcc = m_cIMvc.GetCurrentDataSource ();
	CCalibration Dlg (m_pIDataAcc);
	Dlg.DoModal ();
	UpdateMenus ();
    m_pIDataAcc->Close ((CloseMode) dNoUpdate);
	m_pIDataAcc.Release ();
}


//OnSampleEditor - Show Sample Information window
void CMainDialog::OnSampleEditor () 
{
	CSampleInfo Dlg (&m_cIMvc);
	Dlg.DoModal ();
	UpdateMenus ();
}