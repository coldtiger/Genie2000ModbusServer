/*
* ==========================================================================
* Name:         DataSourceMenu.cpp : Implementation of CMainDialog
* Project:      Example
* Purpose:      This file contains different routines related to "DataSource" menu.
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


//OnNextDatasource - On Next open data source window
void CMainDialog::OnNextDatasource () 
{
	CloseAdjust ();
	m_cIMvc.NextSource ();
	UpdateMenus ();
}

//OnPrevDatasource - On Previous opened data source window
void CMainDialog::OnPrevDatasource () 
{
	CloseAdjust ();
	m_cIMvc.PreviousSource ();
	UpdateMenus ();
}
