/*
* ==========================================================================
* Name:         Preference.cpp : Implementation of CPreferences Dialog.
* Project:      Example
* Purpose:      This file contains implementation functions of CPreferences Dialog.
*				This dialog is responsible for setting different properties of Displayer
*				component.
*				User can select this dialog from Display->Preferences... menu.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#include "stdafx.h"
#include "WinGAA.h"
#include "Preference.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreferences dialog


CPreferences::CPreferences(Preference* pStruct, CWnd* pParent /*=NULL*/)
	: CDialog(CPreferences::IDD, pParent)
{
	m_pPref = pStruct;

	//{{AFX_DATA_INIT(CPreferences)
	m_LibraryName = _T("");
	//}}AFX_DATA_INIT
}


void CPreferences::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreferences)
	DDX_Control(pDX, IDC_COMBO_PTSIZ, m_PtList);
	DDX_Text(pDX, IDC_EDIT_LIBNAME, m_LibraryName);
	DDV_MaxChars(pDX, m_LibraryName, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreferences, CDialog)
	//{{AFX_MSG_MAP(CPreferences)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON_SPEC, OnButtonSpec)
	ON_BN_CLICKED(IDC_BUTTON_BKGND, OnButtonBkgnd)
	ON_BN_CLICKED(IDC_BUTTON_ROI1, OnButtonRoi1)
	ON_BN_CLICKED(IDC_BUTTON_ROI2, OnButtonRoi2)
	ON_BN_CLICKED(IDC_BUTTON_ROI3, OnButtonRoi3)
	ON_BN_CLICKED(IDC_BUTTON_ROI4, OnButtonRoi4)
	ON_BN_CLICKED(IDC_BUTTON_NLINES, OnButtonNlines)
	ON_BN_CLICKED(IDC_BUTTON_NKEYLINE, OnButtonNkeyline)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT, OnButtonDefault)
	ON_BN_CLICKED(IDC_RADIO_NORMAL, OnRadioNormal_Full)
	ON_BN_CLICKED(IDC_RADIO_ENVELOP, OnRadioEnvelop_Fill)
	ON_BN_CLICKED(IDC_CHECK_LABELS, OnCheckLabels)
	ON_BN_CLICKED(IDC_CHECK_INFO, OnCheckInfo)
	ON_BN_CLICKED(IDC_RADIO_LIBLINES, OnRadioLiblines)
	ON_BN_CLICKED(IDC_RADIO_FULL, OnRadioNormal_Full)
	ON_BN_CLICKED(IDC_RADIO_FILL, OnRadioEnvelop_Fill)
	ON_BN_CLICKED(IDC_RADIO_ANALYSIS, OnRadioAnalysis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreferences message handlers

BOOL CPreferences::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_PtList.AddString (_T("Default"));		// 1
	m_PtList.AddString (_T("Micro"));
	m_PtList.AddString (_T("Small"));
	m_PtList.AddString (_T("Medium"));
	m_PtList.AddString (_T("Large"));		//5

	
	m_LibraryName = _T("C:\\GENIE2K\\CAMFILES\\STDLIB.NLB");
	SetDlgItemText (IDC_EDIT_LIBNAME, m_LibraryName);
	SetPrefs ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//SetPrefs - Utility to set up the dialog
void CPreferences::SetPrefs ()
{    
	CString strString;

    switch (m_pPref->PlotMethod)
		{
		case 2:
			CheckDlgButton (IDC_RADIO_FULL, TRUE);
			m_PtList.EnableWindow (TRUE);
			break;
		case 3:
			CheckDlgButton (IDC_RADIO_ENVELOP, TRUE);
			m_PtList.EnableWindow (FALSE);
			break;
		case 4:
			CheckDlgButton (IDC_RADIO_FILL, TRUE);
			m_PtList.EnableWindow (FALSE);
			break;
		default:
			CheckDlgButton (IDC_RADIO_NORMAL, TRUE);
			m_PtList.EnableWindow (TRUE);
			break;
		}

	m_PtList.SetCurSel (m_pPref->PointSize - 1);	// List box is 0 based

	CheckDlgButton (IDC_CHECK_SHOWBORDER, m_pPref->Borders);
	CheckDlgButton (IDC_CHECK_SHOWXGRID, m_pPref->XGrid);
	CheckDlgButton (IDC_CHECK_SHOWXENG, m_pPref->XGridAsEnergy);
	CheckDlgButton (IDC_CHECK_SHOWYGRID, m_pPref->YGrid);
	strString.Format (_T("%d"), m_pPref->Ticks);
	SetDlgItemText (IDC_EDIT_NUMGRIDLIN, strString);

	CheckDlgButton (IDC_CHECK_SHOWSTATBAR, m_pPref->ShowBar);
	CheckDlgButton (IDC_CHECK_SHOWSTATPAGE, m_pPref->ShowPages);

    switch (m_pPref->StatusPage)
		{
		case 2:
			CheckDlgButton (IDC_RADIO_ROICURINFO, TRUE);
			break;
		default:
			CheckDlgButton (IDC_RADIO_SPECINFO, TRUE);
			break;
		}

	strString.Format (_T("%d"), m_pPref->UpdateRate);
	SetDlgItemText (IDC_EDIT_UPDATERATE, strString);


	CheckDlgButton (IDC_CHECK_LABELS, m_pPref->DisplayPeakLabels);
	CheckDlgButton (IDC_CHECK_INFO, m_pPref->PeakInfoBubble);
	CheckDlgButton (IDC_CHECK_ACTIVITY, m_pPref->PeakActivityInfo);
	CheckRadioButton (IDC_RADIO_ASCEND, IDC_RADIO_DESCD, 
					m_pPref->LabelsAscending ? IDC_RADIO_ASCEND : IDC_RADIO_DESCD);
	CheckRadioButton (IDC_RADIO_LIBLINES, IDC_RADIO_ANALYSIS, 
						m_pPref->PeakInfoLibrary ? IDC_RADIO_LIBLINES : IDC_RADIO_ANALYSIS);

	OnCheckLabels ();
	OnCheckInfo ();
}

//OnDrawItem - User defined drawing of color buttons
void CPreferences::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (!nIDCtl)
		return;

	HDC hDC = lpDrawItemStruct->hDC;
    COLORREF clrCurrColor, clrPrevText, clrPrevBkgnd; 
	char strText [20] = {0};

	if (nIDCtl == IDC_BUTTON_SPEC)
	{
		_tcscpy (strText, _T("Spectrum"));
		clrCurrColor = m_pPref->SpecColor;
	}
	else if (nIDCtl == IDC_BUTTON_BKGND)
	{
		_tcscpy (strText, _T("Background"));
		clrCurrColor = m_pPref->BackColor;
	}
	else if (nIDCtl == IDC_BUTTON_ROI1)
	{
		_tcscpy (strText, _T("Roi1"));
		clrCurrColor = m_pPref->Roi1Color;
	}
	else if (nIDCtl == IDC_BUTTON_ROI2)
	{
		_tcscpy (strText, _T("Roi2"));
		clrCurrColor = m_pPref->Roi2Color;
	}
	else if (nIDCtl == IDC_BUTTON_ROI3)
	{
		_tcscpy (strText, _T("Roi3"));
		clrCurrColor = m_pPref->Roi3Color;
	}
	else if (nIDCtl == IDC_BUTTON_ROI4)
	{
		_tcscpy (strText, _T("Roi4"));
		clrCurrColor = m_pPref->Roi4Color;
	}
	else if (nIDCtl == IDC_BUTTON_NLINES)
	{
		_tcscpy (strText, _T("Nuclide Lines"));
		clrCurrColor = m_pPref->NuclColor;
	}
	else if (nIDCtl == IDC_BUTTON_NKEYLINE)
	{
		_tcscpy (strText, _T("Nuclide Key Line"));
		clrCurrColor = m_pPref->NuclKeyColor;
	}

    // Draw the text...
	clrPrevText = SetTextColor (hDC, (clrCurrColor - 0x00FFFFFF) + 1);	// inverted color
	clrPrevBkgnd = SetBkColor (hDC, clrCurrColor);

	ExtTextOut(hDC, lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top, 
					ETO_OPAQUE, &lpDrawItemStruct->rcItem, 
					strText, _tcslen (strText), NULL); 
	
    // Restore the original colors. 
	SetTextColor (hDC, clrPrevText);
	SetBkColor (hDC, clrPrevBkgnd);

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

//OnButtonSpec - Set Spectrum color
void CPreferences::OnButtonSpec() 
{
	OnSelectetColor (m_pPref->SpecColor);
}

//OnButtonBkgnd - Set Background color
void CPreferences::OnButtonBkgnd() 
{
	OnSelectetColor (m_pPref->BackColor);
}

//OnButtonRoi1 - Set Roi1 Color
void CPreferences::OnButtonRoi1() 
{
	OnSelectetColor (m_pPref->Roi1Color);
}

//OnButtonRoi2 - Set Roi2 Color
void CPreferences::OnButtonRoi2() 
{
	OnSelectetColor (m_pPref->Roi2Color);
}

//OnButtonRoi3 - Set Roi3 Color
void CPreferences::OnButtonRoi3() 
{
	OnSelectetColor (m_pPref->Roi3Color);
}

//OnButtonRoi4 - Set Roi4 Color
void CPreferences::OnButtonRoi4() 
{
	OnSelectetColor (m_pPref->Roi4Color);
}

//OnButtonRoi1 - Set Nuclide Line Color
void CPreferences::OnButtonNlines() 
{
	OnSelectetColor (m_pPref->NuclColor);
}

//OnButtonNkeyline - Set Nuclide Key Line Color
void CPreferences::OnButtonNkeyline() 
{
	OnSelectetColor (m_pPref->NuclKeyColor);
}

//OnSelectetColor - pop up color dialog and set user specified color
void CPreferences::OnSelectetColor (long& clrColor)
{
	CColorDialog Dlg (clrColor, CC_RGBINIT);
	if (Dlg.DoModal () == IDOK)
		{
		clrColor = Dlg.GetColor ();
		InvalidateRect (NULL);
		}
}

//OnButtonDefault - set default values and update controls
void CPreferences::OnButtonDefault() 
{
	DefaultPrefs ();
	SetPrefs ();
}

//DefaultPrefs - Update the MCA display with preference settings
void CPreferences::DefaultPrefs ()
{  
    m_pPref->Linear = TRUE;
    m_pPref->SpecColor = vbYellow;
    m_pPref->BackColor = vbBlack;
    m_pPref->Roi1Color = vbRed;
    m_pPref->Roi2Color = vbCyan;
    m_pPref->Roi3Color = vbGreen;
    m_pPref->Roi4Color = vbMagenta;
    m_pPref->NuclColor = vbGreen;
    m_pPref->NuclKeyColor = vbCyan;
    m_pPref->PlotMethod = 1;  //1=Normal
    m_pPref->PointSize = 1; //1=Default
    m_pPref->XGrid = 0;
    m_pPref->XGridAsEnergy = 1;
    m_pPref->YGrid = 0;
    m_pPref->Borders = 0;
    m_pPref->Ticks = 3;
    m_pPref->ShowBar = 1;
    m_pPref->ShowPages = 1;
    m_pPref->StatusPage = 1; //1=Roi/Cursor
    m_pPref->UpdateRate = 0;
    m_pPref->DisplayPeakLabels = 0;
    m_pPref->LabelsAscending = 0;
    m_pPref->PeakInfoBubble = 0;
    m_pPref->PeakInfoLibrary = 0;
    m_pPref->PeakActivityInfo = 0;
}

// save current settings to data structure
void CPreferences::OnOK() 
{
	CString strString;

	UpdateData ();// retrive data from dialog

	if (IsDlgButtonChecked (IDC_RADIO_FULL))
		m_pPref->PlotMethod = 2;
	else if (IsDlgButtonChecked (IDC_RADIO_ENVELOP))
		m_pPref->PlotMethod = 3;
	else if (IsDlgButtonChecked (IDC_RADIO_FILL))
		m_pPref->PlotMethod = 4;
	else
		m_pPref->PlotMethod = 1;

	m_pPref->PointSize		= m_PtList.GetCurSel () + 1; 	// List box is 0 based
	m_pPref->Borders		= IsDlgButtonChecked (IDC_CHECK_SHOWBORDER);
	m_pPref->XGrid			= IsDlgButtonChecked (IDC_CHECK_SHOWXGRID);
	m_pPref->XGridAsEnergy	= IsDlgButtonChecked (IDC_CHECK_SHOWXENG);
	m_pPref->YGrid			= IsDlgButtonChecked (IDC_CHECK_SHOWYGRID);
	m_pPref->Ticks			= GetDlgItemInt (IDC_EDIT_NUMGRIDLIN);
	m_pPref->ShowBar		= IsDlgButtonChecked (IDC_CHECK_SHOWSTATBAR);
	m_pPref->ShowPages		= IsDlgButtonChecked (IDC_CHECK_SHOWSTATPAGE);
	m_pPref->StatusPage		= (IsDlgButtonChecked (IDC_RADIO_ROICURINFO) ? 2 : 1);
	m_pPref->UpdateRate		= GetDlgItemInt (IDC_EDIT_UPDATERATE);
    m_pPref->DisplayPeakLabels = IsDlgButtonChecked (IDC_CHECK_LABELS);
    m_pPref->LabelsAscending = IsDlgButtonChecked (IDC_RADIO_ASCEND);
    m_pPref->PeakInfoBubble = IsDlgButtonChecked (IDC_CHECK_INFO);
    m_pPref->PeakInfoLibrary = IsDlgButtonChecked (IDC_RADIO_LIBLINES);
    m_pPref->PeakActivityInfo = IsDlgButtonChecked (IDC_CHECK_ACTIVITY);
	
	CDialog::OnOK();
}

void CPreferences::OnRadioNormal_Full() 
{	
	m_PtList.EnableWindow (TRUE);
}


void CPreferences::OnRadioEnvelop_Fill() 
{
	m_PtList.EnableWindow (FALSE);
}

void CPreferences::OnCheckLabels() 
{
	if (IsDlgButtonChecked (IDC_CHECK_LABELS))
	{
		GetDlgItem (IDC_RADIO_LIBLINES)->EnableWindow ();
		GetDlgItem (IDC_RADIO_ANALYSIS)->EnableWindow ();
		GetDlgItem (IDC_RADIO_ASCEND)->EnableWindow ();
		GetDlgItem (IDC_RADIO_DESCD)->EnableWindow ();
		if (m_pPref->PeakInfoLibrary)
			OnRadioLiblines ();
		else
			OnRadioAnalysis ();
	}
	else
	{
		GetDlgItem (IDC_RADIO_ASCEND)->EnableWindow (FALSE);
		GetDlgItem (IDC_RADIO_DESCD)->EnableWindow (FALSE);
		if (!IsDlgButtonChecked (IDC_CHECK_INFO))
		{
			GetDlgItem (IDC_RADIO_LIBLINES)->EnableWindow (FALSE);
			GetDlgItem (IDC_RADIO_ANALYSIS)->EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_LIBNAME)->EnableWindow (FALSE);
		}
	}
}

void CPreferences::OnCheckInfo() 
{
	if (IsDlgButtonChecked (IDC_CHECK_INFO))
	{
		GetDlgItem (IDC_RADIO_LIBLINES)->EnableWindow ();
		GetDlgItem (IDC_RADIO_ANALYSIS)->EnableWindow ();
		GetDlgItem (IDC_CHECK_ACTIVITY)->EnableWindow ();
		if (m_pPref->PeakInfoLibrary)
			OnRadioLiblines ();
		else
			OnRadioAnalysis ();
	}
	else
	{
		GetDlgItem (IDC_CHECK_ACTIVITY)->EnableWindow (FALSE);
		if (!IsDlgButtonChecked (IDC_CHECK_LABELS))
		{
			GetDlgItem (IDC_RADIO_LIBLINES)->EnableWindow (FALSE);
			GetDlgItem (IDC_RADIO_ANALYSIS)->EnableWindow (FALSE);
			GetDlgItem (IDC_EDIT_LIBNAME)->EnableWindow (FALSE);
		}
	}
}

void CPreferences::OnRadioLiblines() 
{
	GetDlgItem (IDC_EDIT_LIBNAME)->EnableWindow ();
}

void CPreferences::OnRadioAnalysis() 
{
	GetDlgItem (IDC_EDIT_LIBNAME)->EnableWindow (FALSE);
}
