/*
* ==========================================================================
* Name:         PrefFunctions.cpp : Implementation of CMainDialog
* Project:      Example
* Purpose:      This file contains different helper routines related to 
*				Preferece settings for Display menu.
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


LPCTSTR INIFILE = _T("CIExample.INI");
LPCTSTR INISECT = _T("DisplaySettings");


//SetPrefs - Update the MCA display with preference settings
void CMainDialog::SetPrefs (LPCTSTR lpszLib)
{  
    m_cIMvc.SetLinearScale (m_pPrefs->Linear);
    m_cIMvc.SetSpectrumColor (m_pPrefs->SpecColor);
    m_cIMvc.SetBackColor (m_pPrefs->BackColor);
    m_cIMvc.SetRoiType1Color (m_pPrefs->Roi1Color);
    m_cIMvc.SetRoiType2Color (m_pPrefs->Roi2Color);
    m_cIMvc.SetRoiType3Color (m_pPrefs->Roi3Color);
    m_cIMvc.SetRoiType4Color (m_pPrefs->Roi4Color);
    m_cIMvc.SetNuclineColor (m_pPrefs->NuclColor);
    m_cIMvc.SetKeylineColor (m_pPrefs->NuclKeyColor);

    switch (m_pPrefs->PlotMethod)
		{
		case 2:
			m_cIMvc.SetDisplayPoints (TRUE);
			m_cIMvc.SetShowCompressedData (FALSE);
			m_cIMvc.SetFillSpectralRois (FALSE);
			break;
		case 3:
			m_cIMvc.SetDisplayPoints (FALSE);
			m_cIMvc.SetShowCompressedData (TRUE);
			m_cIMvc.SetFillSpectralRois (FALSE);
			break;
		case 4:
			m_cIMvc.SetDisplayPoints (TRUE);
			m_cIMvc.SetShowCompressedData (TRUE);
			m_cIMvc.SetFillSpectralRois (TRUE);
			break;
		default:
			m_cIMvc.SetDisplayPoints (TRUE);
			m_cIMvc.SetShowCompressedData (TRUE);
			m_cIMvc.SetFillSpectralRois (FALSE);
			break;
		}
   
    switch (m_pPrefs->PointSize)
		{
		case 2:
			m_cIMvc.SetPlotPointSize (CanberraDataDisplayLib::Micro);
			break;
		case 3:
			m_cIMvc.SetPlotPointSize (CanberraDataDisplayLib::Small);
			break;
		case 4:
			m_cIMvc.SetPlotPointSize (CanberraDataDisplayLib::Medium);
			break;
		case 5:
			m_cIMvc.SetPlotPointSize (CanberraDataDisplayLib::Large);
		default:
			m_cIMvc.SetPlotPointSize (CanberraDataDisplayLib::BestFit);
			break;
		}
 
    m_cIMvc.SetShowXAxisGridLines ((m_pPrefs->XGrid == 1));
    m_cIMvc.SetXAxisAsEnergy ((m_pPrefs->XGridAsEnergy == 1));
    m_cIMvc.SetShowYAxisGridLines ((m_pPrefs->YGrid == 1));
    m_cIMvc.SetShowPlotBorders ((m_pPrefs->Borders == 1));
    m_cIMvc.SetNumberOfTicks (m_pPrefs->Ticks);
    m_cIMvc.SetShowStatus ((m_pPrefs->ShowBar == 1));

    switch (m_pPrefs->StatusPage)
		{
		case 2:
			m_cIMvc.SetShowSpectralDataSpreadSheet (TRUE);
			break;
		default:
			m_cIMvc.SetShowCalculationSpreadSheet (TRUE);
			break;
		}

    m_cIMvc.SetShowInfo ((m_pPrefs->ShowPages == 1));
    m_cIMvc.SetDisplayUpdateRate (m_pPrefs->UpdateRate * 1000);
	SetPeakProperties(lpszLib);
}

//LoadPrefs - Update local data structure with preference settings
void CMainDialog::LoadPrefs ()
{  
    m_pPrefs->Linear = GetPrivateProfileInt(INISECT, "Linear", 1, INIFILE);
    m_pPrefs->SpecColor = GetPrivateProfileInt(INISECT, "SpecColor", vbYellow, INIFILE);
    m_pPrefs->BackColor = GetPrivateProfileInt(INISECT, "BackColor", vbBlack, INIFILE);
    m_pPrefs->Roi1Color = GetPrivateProfileInt(INISECT, "Roi1Color", vbRed, INIFILE);
    m_pPrefs->Roi2Color = GetPrivateProfileInt(INISECT, "Roi2Color", vbBlue, INIFILE);
    m_pPrefs->Roi3Color = GetPrivateProfileInt(INISECT, "Roi3Color", vbCyan, INIFILE);
    m_pPrefs->Roi4Color = GetPrivateProfileInt(INISECT, "Roi4Color", vbMagenta, INIFILE);
    m_pPrefs->NuclColor = GetPrivateProfileInt(INISECT, "NuclColor", vbGreen, INIFILE);
    m_pPrefs->NuclKeyColor = GetPrivateProfileInt(INISECT, "NuclKeyColor", vbCyan, INIFILE);
    m_pPrefs->PlotMethod = GetPrivateProfileInt(INISECT, "PlotMethod", 1, INIFILE);
    m_pPrefs->PointSize = GetPrivateProfileInt(INISECT, "PointSize", 1, INIFILE);
    m_pPrefs->XGrid = GetPrivateProfileInt(INISECT, "XGrid", 0, INIFILE);
    m_pPrefs->XGridAsEnergy = GetPrivateProfileInt(INISECT, "XGridAsEnergy", 1, INIFILE);
    m_pPrefs->YGrid = GetPrivateProfileInt(INISECT, "YGrid", 0, INIFILE);
    m_pPrefs->Borders = GetPrivateProfileInt(INISECT, "Borders", 0, INIFILE);
    m_pPrefs->Ticks = GetPrivateProfileInt(INISECT, "Ticks", 3, INIFILE);
    m_pPrefs->ShowBar = GetPrivateProfileInt(INISECT, "ShowBar", 1, INIFILE);
    m_pPrefs->ShowPages = GetPrivateProfileInt(INISECT, "ShowPages", 1, INIFILE);
    m_pPrefs->StatusPage = GetPrivateProfileInt(INISECT, "Page", 1, INIFILE);
    m_pPrefs->UpdateRate = GetPrivateProfileInt(INISECT, "UpdateRate", 0, INIFILE);
    m_pPrefs->DisplayPeakLabels = GetPrivateProfileInt(INISECT, "ShowPeakLabels", 0, INIFILE);
    m_pPrefs->LabelsAscending = GetPrivateProfileInt(INISECT, "AscendingLabels", 0, INIFILE);
    m_pPrefs->PeakInfoBubble = GetPrivateProfileInt(INISECT, "ShowInfoBubble", 0, INIFILE);
    m_pPrefs->PeakInfoLibrary = GetPrivateProfileInt(INISECT, "LibraryLines", 0, INIFILE);
    m_pPrefs->PeakActivityInfo = GetPrivateProfileInt(INISECT, "ShowActivity", 0, INIFILE);
}

//LoadPrefs - Update local data structure with preference settings
void CMainDialog::StorePrefs ()
{  
	char szBuffer [100] = {0};
	itoa (m_pPrefs->Linear, szBuffer, 10);
    WritePrivateProfileString (INISECT, "Linear", szBuffer, INIFILE);
	ltoa (m_pPrefs->SpecColor, szBuffer, 10);
    WritePrivateProfileString (INISECT, "SpecColor", szBuffer, INIFILE);
	ltoa (m_pPrefs->BackColor, szBuffer, 10);
    WritePrivateProfileString (INISECT, "BackColor", szBuffer, INIFILE);
	ltoa (m_pPrefs->Roi1Color, szBuffer, 10);
    WritePrivateProfileString (INISECT, "Roi1Color", szBuffer, INIFILE);
	ltoa (m_pPrefs->Roi2Color, szBuffer, 10);
    WritePrivateProfileString (INISECT, "Roi2Color", szBuffer, INIFILE);
	ltoa (m_pPrefs->Roi3Color, szBuffer, 10);
    WritePrivateProfileString (INISECT, "Roi3Color", szBuffer, INIFILE);
	ltoa (m_pPrefs->Roi4Color, szBuffer, 10);
    WritePrivateProfileString (INISECT, "Roi4Color", szBuffer, INIFILE);
	ltoa (m_pPrefs->NuclColor, szBuffer, 10);
    WritePrivateProfileString (INISECT, "NuclColor", szBuffer, INIFILE);
	ltoa (m_pPrefs->NuclKeyColor, szBuffer, 10);
    WritePrivateProfileString (INISECT, "NuclKeyColor", szBuffer, INIFILE);
	itoa (m_pPrefs->PlotMethod, szBuffer, 10);
    WritePrivateProfileString (INISECT, "PlotMethod", szBuffer, INIFILE);
	itoa (m_pPrefs->PointSize, szBuffer, 10);
    WritePrivateProfileString (INISECT, "PointSize", szBuffer, INIFILE);
	itoa (m_pPrefs->XGrid, szBuffer, 10);
    WritePrivateProfileString (INISECT, "XGrid", szBuffer, INIFILE);
	itoa (m_pPrefs->XGridAsEnergy, szBuffer, 10);
    WritePrivateProfileString (INISECT, "XGridAsEnergy", szBuffer, INIFILE);
	itoa (m_pPrefs->YGrid, szBuffer, 10);
    WritePrivateProfileString (INISECT, "YGrid", szBuffer, INIFILE);
	itoa (m_pPrefs->Borders, szBuffer, 10);
    WritePrivateProfileString (INISECT, "Borders", szBuffer, INIFILE);
	itoa (m_pPrefs->Ticks, szBuffer, 10);
    WritePrivateProfileString (INISECT, "Ticks", szBuffer, INIFILE);
	itoa (m_pPrefs->ShowBar, szBuffer, 10);
    WritePrivateProfileString (INISECT, "ShowBar", szBuffer, INIFILE);
	itoa (m_pPrefs->ShowPages, szBuffer, 10);
    WritePrivateProfileString (INISECT, "ShowPages", szBuffer, INIFILE);
	itoa (m_pPrefs->StatusPage, szBuffer, 10);
    WritePrivateProfileString (INISECT, "Page", szBuffer, INIFILE);
	itoa (m_pPrefs->UpdateRate, szBuffer, 10);
    WritePrivateProfileString (INISECT, "UpdateRate", szBuffer, INIFILE);
	itoa (m_pPrefs->DisplayPeakLabels, szBuffer, 10);
    WritePrivateProfileString (INISECT, "ShowPeakLabels", szBuffer, INIFILE);
	itoa (m_pPrefs->LabelsAscending, szBuffer, 10);
    WritePrivateProfileString (INISECT, "AscendingLabels", szBuffer, INIFILE);
	itoa (m_pPrefs->PeakInfoBubble, szBuffer, 10);
    WritePrivateProfileString (INISECT, "ShowInfoBubble", szBuffer, INIFILE);
	itoa (m_pPrefs->PeakInfoLibrary, szBuffer, 10);
    WritePrivateProfileString (INISECT, "LibraryLines", szBuffer, INIFILE);
	itoa (m_pPrefs->PeakActivityInfo, szBuffer, 10);
    WritePrivateProfileString (INISECT, "ShowActivity", szBuffer, INIFILE);
}


//SetPeakProperties - Set Peak Labeling property
void CMainDialog::SetPeakProperties (LPCTSTR lpszLib)
{
	CanberraDataDisplayLib::PeakLabelingOptions PeakMask = (CanberraDataDisplayLib::PeakLabelingOptions) 0;

    if (m_pPrefs->DisplayPeakLabels == TRUE)
	{
        PeakMask = (CanberraDataDisplayLib::PeakLabelingOptions) (PeakMask | CanberraDataDisplayLib::spShowPeakLabels);
        if (m_pPrefs->LabelsAscending == TRUE)
            PeakMask = (CanberraDataDisplayLib::PeakLabelingOptions) (PeakMask | CanberraDataDisplayLib::spUseAscendingLabels);
    }
    
    if (m_pPrefs->PeakInfoBubble == TRUE)
	{
        PeakMask = (CanberraDataDisplayLib::PeakLabelingOptions) (PeakMask | CanberraDataDisplayLib::spShowInfoBubble);
        if (m_pPrefs->PeakActivityInfo == TRUE)
            PeakMask = (CanberraDataDisplayLib::PeakLabelingOptions) (PeakMask | CanberraDataDisplayLib::spShowPeakActivity);
	}
    
    if (m_pPrefs->DisplayPeakLabels == TRUE || m_pPrefs->PeakInfoBubble == TRUE)
	{
        if (m_pPrefs->PeakInfoLibrary == TRUE)
		{
            PeakMask = (CanberraDataDisplayLib::PeakLabelingOptions) (PeakMask | CanberraDataDisplayLib::spSelectLibraryLines);
            m_cIMvc.SetProperties ((variant_t) (_bstr_t) ("NuclideLibraryName"), (variant_t) (lpszLib));
		}
	}
	m_cIMvc.SetProperties ((variant_t) (_bstr_t) ("PeakLabelProperties"), (variant_t) ((LONG) PeakMask));
}