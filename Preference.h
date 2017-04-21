/*
* ==========================================================================
* Name:         Preference.h : Header file of CPreferences Dialog.
* Project:      Example
* Purpose:      This file contains declaration of CPreferences Dialog.
*				This dialog is responsible for setting different properties of Displayer
*				component.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#if !defined(AFX_PREFERENCE_H__0DD72275_17AE_4B39_B138_C6FAF5E1CB3A__INCLUDED_)
#define AFX_PREFERENCE_H__0DD72275_17AE_4B39_B138_C6FAF5E1CB3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct Preference
{
	int Linear;
	long SpecColor;
	long BackColor;
	long Roi1Color;
	long Roi2Color;
	long Roi3Color;
	long Roi4Color;
	long NuclColor;
	long NuclKeyColor;
	int PlotMethod;		// 1=Normal, 2=Full, 3=Env, 4=Fill
	int PointSize;		// 1=Def, 2=Micro, 3=Small, 4=Medium, 5=Large
	int XGrid;
	int XGridAsEnergy;
	int YGrid;
	int Borders;
	int Ticks;
	int ShowBar;
	int ShowPages;
	int StatusPage;		// 1=Roi/Cursor, 2=Spectral
	int UpdateRate;
	BOOL DisplayPeakLabels;
	BOOL LabelsAscending;
	BOOL PeakInfoBubble;
	BOOL PeakInfoLibrary;
	BOOL PeakActivityInfo;
};

/////////////////////////////////////////////////////////////////////////////
// CPreferences dialog

class CPreferences : public CDialog
{
// Construction
public:
	CPreferences(Preference* pStruct, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPreferences)
	enum { IDD = IDD_DIALOG_PREFERENCE };
	CComboBox	m_PtList;
	CString	m_LibraryName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreferences)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPreferences)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSpec();
	afx_msg void OnButtonBkgnd();
	afx_msg void OnButtonRoi1();
	afx_msg void OnButtonRoi2();
	afx_msg void OnButtonRoi3();
	afx_msg void OnButtonRoi4();
	afx_msg void OnButtonNlines();
	afx_msg void OnButtonNkeyline();
	afx_msg void OnButtonDefault();
	virtual void OnOK();
	afx_msg void OnRadioNormal_Full();
	afx_msg void OnRadioEnvelop_Fill();
	afx_msg void OnCheckLabels();
	afx_msg void OnCheckInfo();
	afx_msg void OnRadioLiblines();
	afx_msg void OnRadioAnalysis();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	void DefaultPrefs ();
	void SetPrefs ();
	void OnSelectetColor (long& clrColor);

private:
	Preference*		m_pPref;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFERENCE_H__0DD72275_17AE_4B39_B138_C6FAF5E1CB3A__INCLUDED_)
