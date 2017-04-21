/*
* ==========================================================================
* Name:         AdjustDlg.cpp : Implementation of CAdjustDlg Dialog.
* Project:      Example
* Purpose:      This file contains implementation functions of CAdjustDlg Dialog.
*				This dialog is responsible for Adjusting detector 
*				parameters (eg. Adjust Pole Zero).
*				User can select this dialog from MCA->Adjust... menu.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#include "stdafx.h"
#include "WinGAA.h"
#include "AdjustDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjustDlg dialog


CAdjustDlg::CAdjustDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdjustDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdjustDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAdjustDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjustDlg)
	DDX_Control(pDX, IDC_ADJUSTCONTROL1, m_cIAdjustCtl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjustDlg, CDialog)
	//{{AFX_MSG_MAP(CAdjustDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjustDlg message handlers


void CAdjustDlg::SetDevice (LPDISPATCH lpNewVal)
{
	m_cIAdjustCtl.SetDevice (lpNewVal, -1);	// -1 = adjAll
}

void CAdjustDlg::OnClose() 
{
	ShowWindow (SW_HIDE);	
}
