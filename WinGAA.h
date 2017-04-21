/*
* ==========================================================================
* Name:         WinGAA.h : Header file for the CMainApp
* Project:      Example
* Purpose:      This file contains declaration of Main Application Class
*				which defines the class behaviors for the application.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#if !defined(AFX_WINGAA_H__36CDDB9D_7C7D_46CB_8C7F_22FAF0784371__INCLUDED_)
#define AFX_WINGAA_H__36CDDB9D_7C7D_46CB_8C7F_22FAF0784371__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#pragma warning ( disable : 4146 )

#import "DataAccess.tlb"	no_namespace, raw_interfaces_only, exclude("ClassCodes","ParamCodes","MessageCodes")
#import "Devaccess.tlb"		 raw_interfaces_only, raw_native_types, named_guids, rename_namespace("DeviceAccess")
#import "Displayer.tlb"		raw_interfaces_only, raw_native_types, named_guids
#import "Analyze.tlb"		no_namespace, raw_interfaces_only

#ifndef _MY_DEFINES
#define	_MY_DEFINES

#define		vbYellow	RGB (255, 255, 0)
#define		vbBlack		RGB (0, 0, 0)
#define		vbRed		RGB (255, 0, 0)
#define		vbBlue		RGB (0, 0, 255)
#define		vbCyan		RGB (0, 255, 255)
#define		vbGreen		RGB (0, 255, 0)
#define		vbMagenta	RGB (255, 0, 255)

#endif // _MY_DEFINES

/////////////////////////////////////////////////////////////////////////////
// CMainApp:
// See WinGAA.cpp for the implementation of this class
//

class CMainApp : public CWinApp
{
public:
	CMainApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMainApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINGAA_H__36CDDB9D_7C7D_46CB_8C7F_22FAF0784371__INCLUDED_)
