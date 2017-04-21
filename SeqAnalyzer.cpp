/*
* ==========================================================================
* Name:         SeqAnalyzer.cpp : Implementation of CSeqAnalyzer Dialog.
* Project:      Example
* Purpose:      This file contains implementation functions of CSeqAnalyzer Dialog.
*				This dialog is responsible for selecting / displaying seq step.
*				User can select this dialog from Analysis and Reporting->Edit Analysis Sequence... menu.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#include "stdafx.h"
#include "WinGAA.h"
#include "SeqAnalyzer.h"

#import  "displayer.tlb" raw_interfaces_only, raw_native_types, named_guids  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeqAnalyzer dialog


CSeqAnalyzer::CSeqAnalyzer(LPDISPATCH	pDatasource, CWnd* pParent /*=NULL*/)
	: CDialog(CSeqAnalyzer::IDD, pParent)
{
	m_pDatasource = pDatasource;
	//{{AFX_DATA_INIT(CSeqAnalyzer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSeqAnalyzer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeqAnalyzer)
	DDX_Control(pDX, IDC_ANALYSISEDITOR1, m_cIAnalysisEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSeqAnalyzer, CDialog)
	//{{AFX_MSG_MAP(CSeqAnalyzer)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_COMMAND(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeqAnalyzer message handlers

BOOL CSeqAnalyzer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_cIAnalysisEdit.SetSequence (m_pDatasource, FALSE, FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//OnButtonLoad - Load sequence from file
void CSeqAnalyzer::OnButtonLoad() 
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

    // Open the file
	CComPtr <IDataAccess> pIDataAcc;
	if (FAILED(pIDataAcc.CoCreateInstance(__uuidof(DataAccess))))
		return;

	if (FAILED(pIDataAcc->Open ((bstr_t) OpenDialog.GetPathName (), (OpenMode) CanberraDataDisplayLib::ReadWrite, 0)))
	{
		pIDataAcc.Release(); 
		return;
	}

	m_cIAnalysisEdit.SetSequence (pIDataAcc, FALSE, FALSE);
    pIDataAcc->Close ((CloseMode) CanberraDataDisplayLib::NoUpdate);
	SetCurrentDirectory (strCurrentDir);
	pIDataAcc.Release ();
}

//OnOK
void CSeqAnalyzer::OnOK() 
{
	m_cIAnalysisEdit.GetSequenceChanges (m_pDatasource);
	CDialog::OnOK();
}
