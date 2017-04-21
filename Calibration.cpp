/*
* ==========================================================================
* Name:         Calibration.cpp : Implementation of CCalibration Dialog.
* Project:      Example
* Purpose:      This file contains implementation functions of CCalibration Dialog.
*				This dialog is responsible for displaying different calibration 
*				information for selected datasource.
*				User can display this info from Edit->Show Calibrations menu.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#include "stdafx.h"
#include "WinGAA.h"
#include "Calibration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalibration dialog


CCalibration::CCalibration(IDataAccessPtr lpDispatch, CWnd* pParent /*=NULL*/)
	: CDialog(CCalibration::IDD, pParent)
{
	m_lpDataAccess = lpDispatch;

	//{{AFX_DATA_INIT(CCalibration)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCalibration::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalibration)
	DDX_Control(pDX, IDC_STATIC_LOTAILCAL, m_LowTailTxt);
	DDX_Control(pDX, IDC_STATIC_FWHMCAL, m_FwhmTxt);
	DDX_Control(pDX, IDC_STATIC_ENGCAL, m_ECalTxt);
	DDX_Control(pDX, IDC_LIST1, m_EnegryCal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalibration, CDialog)
	//{{AFX_MSG_MAP(CCalibration)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalibration message handlers

BOOL CCalibration::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    CString strFormat;
    
    // This is just an example of how to use the calibrations property of
    // DataAccess. This allows easy access to the calibration info. This
    // could all be done for efficiency as well. It uses an error handling
    // scheme to determine how large the arrays are. If a violation of the
    // array size takes place the code caries through to the next
    // calibration
    
    // Get the Calibrations
	ICalibrationPtr lpIFace;
	IEnergyPtr pIEnergy;
	IFwhmPtr pIFwhm;
	ILowTailPtr pILowTail;

	m_lpDataAccess->get_Calibrations (&lpIFace);
	lpIFace->get_Energy (&pIEnergy);
	lpIFace->get_Fwhm (&pIFwhm);
	lpIFace->get_LowTail (&pILowTail);

    int i = 0;
	COleSafeArray oleSafeArr1;
	pIEnergy->get_Points (&oleSafeArr1);
	COleSafeArray oleSafeArr2;
	pIFwhm->get_Points (&oleSafeArr2);
	COleSafeArray oleSafeArr3;
	pILowTail->get_Points (&oleSafeArr3);

	long lIndex [2];
	float fChannel, fEnergy, fUncertainty, fFWHM, fLowTail;

    // Add the points to the list box
//Determine upper bounds for both dimensions
	long lNumCols;
	oleSafeArr1.GetUBound(2, &lNumCols);

    while (i < lNumCols)
		{
		lIndex [0] = 0;
		lIndex [1] = i;
		oleSafeArr1.GetElement(lIndex, &fChannel);
		lIndex [0] = 1;
		oleSafeArr1.GetElement(lIndex, &fEnergy);
		lIndex [0] = 2;
		oleSafeArr1.GetElement(lIndex, &fUncertainty);

		lIndex [0] = 1;
		lIndex [1] = i;
		oleSafeArr2.GetElement(lIndex, &fFWHM);
		oleSafeArr3.GetElement(lIndex, &fLowTail);

		strFormat.Format (_T("%12.3f  %12.3f     %12.6f   %12.6f     %12.6f"), fChannel, fEnergy, fUncertainty, fFWHM, fLowTail);
		m_EnegryCal.AddString (strFormat);
        i = i + 1;
		}

    // get the Energy eq
	COleSafeArray oleSafeArr4;
	pIEnergy->get_Curve (&oleSafeArr4);

	float fOffset, fTemp1, fTemp2;
	lIndex [0] = 0;
	lIndex [1] = 0;
	oleSafeArr4.GetElement(lIndex, &fOffset);
	lIndex [0] = 1;
	oleSafeArr4.GetElement(lIndex, &fTemp1);
	lIndex [0] = 2;
	oleSafeArr4.GetElement(lIndex, &fTemp2);

    strFormat.Format (_T("Energy = %f keV "), fOffset);
    if (fTemp1 > 0)
        strFormat.Format (_T("%s + %f *Ch"), strFormat, fTemp1);
    if (fTemp2 > 0)
        strFormat.Format (_T("%s + %f *Ch^2"), strFormat, fTemp2);    
    m_ECalTxt.SetWindowText (strFormat);

    // get the FWHM eq
	COleSafeArray oleSafeArr5;
	pIFwhm->get_Curve (&oleSafeArr5);

	lIndex [0] = 0;
	lIndex [1] = 0;
	oleSafeArr5.GetElement(lIndex, &fOffset);

    strFormat.Format (_T("FWHM = %f keV "), fOffset);
    if (fTemp1 > 0)
		{
		lIndex [0] = 1;
		oleSafeArr5.GetElement(lIndex, &fTemp2);
        strFormat.Format (_T("%s + %f *E^1/2"), strFormat, fTemp2);
		}
    m_FwhmTxt.SetWindowText (strFormat);

    // get the LOTAIL eq
	COleSafeArray oleSafeArr6;
	pILowTail->get_Curve (&oleSafeArr6);

	lIndex [0] = 0;
	lIndex [1] = 0;
	oleSafeArr6.GetElement(lIndex, &fOffset);

    strFormat.Format (_T("Low Tail = %f keV "), fOffset);
    if (fTemp1 > 0)
		{
		lIndex [0] = 1;
		oleSafeArr6.GetElement(lIndex, &fTemp2);
        strFormat.Format (_T("%s + %f *E"), strFormat, fTemp2);
		}
    m_LowTailTxt.SetWindowText (strFormat);

    // You could make this into a calibration editor but currently
    // we only allow setting the calibration points. Generating the
    // curve must be done through our software, or by setting the
    // appropriate CAM parameters individually.
    //

	lpIFace.Release ();
	pIEnergy.Release ();
	pIFwhm.Release ();
	pILowTail.Release ();

/*
	if (lpIFace->m_lpDispatch)	lpIFace->ReleaseDispatch ();
	if (pIEnergy->m_lpDispatch)	pIEnergy->ReleaseDispatch ();
	if (pIFwhm->m_lpDispatch)	pIFwhm->ReleaseDispatch ();
	if (pILowTail->m_lpDispatch)	pILowTail->ReleaseDispatch ();

	delete lpIFace;
	delete pIEnergy;
	delete pIFwhm;
	delete pILowTail;
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
