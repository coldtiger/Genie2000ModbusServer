/*
* ==========================================================================
* Name:         FileFunctions.cpp : Implementation of CMainDialog
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//OpenFile - Opens the CAM File
void CMainDialog::OpenFile (LPCTSTR lpszFile, long lOptions)
{
	CComPtr <IDataAccess> m_pIDataAcc;
	if (FAILED(m_pIDataAcc.CoCreateInstance(__uuidof(DataAccess))))
	{
		AfxMessageBox (_T("Failed to initialize Canberra Data Access Component."), MB_ICONERROR | MB_OK);
		return;
	}
	
	if (FAILED(m_pIDataAcc->Open ((bstr_t) lpszFile, (OpenMode) lOptions, 0)))
	{
		AfxMessageBox (_T("Failed to open CAM file."), MB_ICONERROR | MB_OK);
		m_pIDataAcc.Release(); 
		return;
	}

	CloseAdjust ();
	DisplaySource ((LPDISPATCH) m_pIDataAcc);

	m_pIDataAcc->Close ((CloseMode) dNoUpdate);
	m_pIDataAcc.Release ();
}


//OpenDetector - Opens the detector
void CMainDialog::OpenDetector (LPCTSTR lpszDet, long lOptions, long lType)
{
	CComPtr <DeviceAccess::IDeviceAccess> m_pIDevAcc;

	if (FAILED(m_pIDevAcc.CoCreateInstance(__uuidof(DeviceAccess::DeviceAccess))))
	{
		AfxMessageBox (_T("Failed to initialize Canberra Device Access Component."), MB_ICONERROR | MB_OK);
		return;
	}
	
	if (FAILED (m_pIDevAcc->Connect ((bstr_t) lpszDet, (DeviceAccess::ConnectOptions) lOptions, 
									 (DeviceAccess::AnalyzerType) lType, (bstr_t) _T(""), 
									 (DeviceAccess::BaudRate) DeviceAccess::aUseSystemSettings)))
	{
		AfxMessageBox (_T("Failed to open selected hardware."), MB_ICONERROR | MB_OK);
		m_pIDevAcc.Release(); 
		return;
	}

    CloseAdjust ();
	DisplaySource (m_pIDevAcc);
	m_pIDevAcc.Release ();
}