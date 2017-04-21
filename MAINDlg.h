/*
* ==========================================================================
* Name:         MAINDlg.cpp : Declaration of CMainDialog
* Project:      Example
* Purpose:      This file contains declaration of Main App Dialog.
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

//{{AFX_INCLUDES()
#include "mvc.h"
#include "reportviewer.h"
//}}AFX_INCLUDES

#if !defined(AFX_MAINDLG_H__37C3B309_6C9C_4AD3_B88F_E57CE9C4D475__INCLUDED_)
#define AFX_MAINDLG_H__37C3B309_6C9C_4AD3_B88F_E57CE9C4D475__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "adjustdlg.h"
#include "Preference.h"
#include "SeqAnalyzer.h"

#include "ServerSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CMainDialog dialog

class CMainDialog : public CDialog
{
// Construction
public:
	CString OutputName;
	CMainDialog(CWnd* pParent = NULL);	// standard constructor
	~CMainDialog();	// standard desstructor
	int status;

	CServerSocket * m_pServerSocket;
	bool m_bServerStarted;

	void StartServer();
	void StopServer();
	BOOL DisconnectServer();

	void StartDetection(BOOL LiveOrReal,int t,CString Name);

// Dialog Data
	//{{AFX_DATA(CMainDialog)
	enum { IDD = IDD_DIALOG_WINGAA };
	CMvc	m_cIMvc;
	CReportViewer	m_cIReportWin;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDialog)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMainDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnSave();
	afx_msg void OnSaveAs();
	afx_msg void OnFileClose();
	afx_msg void OnCloseall();
	afx_msg void OnPrint();
	afx_msg void OnCopy();
	afx_msg void OnExport();
	afx_msg void OnExit();
	afx_msg void OnAcqclear();
	afx_msg void OnAcqsetup();
	afx_msg void OnAcqstart();
	afx_msg void OnAcqstop();
	afx_msg void OnAdjust();
	afx_msg void OnExpand();
	afx_msg void OnNuclinesNextNucline();
	afx_msg void OnNuclinesNext();
	afx_msg void OnNuclinesPrevNucline();
	afx_msg void OnNuclinesPrev();
	afx_msg void OnZoomMode();
	afx_msg void OnZoomOut();
	afx_msg void OnScaleAuto();
	afx_msg void OnScaleLinear();
	afx_msg void OnScaleLog();
	afx_msg void OnRiosAdd();
	afx_msg void OnRiosClear();
	afx_msg void OnRiosLoad();
	afx_msg void OnRiosNext();
	afx_msg void OnRiosPrev();
	afx_msg void OnRiosStore();
	afx_msg void OnRoisDel();
	afx_msg void OnNuclinesShow();
	afx_msg void OnClose();
	afx_msg void OnPrefence();
	afx_msg void OnEditseq();
	afx_msg void OnExecute();
	afx_msg void OnExecuteCurrent();
	afx_msg void OnShowReportWinodow();
	afx_msg void OnPrintReport();
	afx_msg void OnSaveReport();
	afx_msg void OnCopySelectedReport();
	afx_msg void OnCopyReport();
	afx_msg void OnNextDatasource();
	afx_msg void OnPrevDatasource();
	afx_msg void OnCertificateFileEditor();
	afx_msg void OnSampleEditor();
	afx_msg void OnShowCalibrations();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Implementation
private:
	void OpenFile (LPCTSTR lpszFile, long lOptions);
	void OpenDetector (LPCTSTR lpszDet, long lOptions, long lType);
	void SendOK(); 
	void CloseAdjust ();
	void DisplaySource (LPDISPATCH lpNewVal);
	void UpdateMenus ();
   void OnAutoExecute(); 
	inline BOOL IsDetector () { return (m_cIMvc.GetCurrentDataSourceType () == CanberraDataDisplayLib::SpectroscopyDetector); }
	void AutoSaveReport();
	void SetPrefs (LPCTSTR lpszLib = NULL);
	void LoadPrefs ();
	void StorePrefs ();

	void ResizeWindow (UINT unState);
	LPDISPATCH GetCurrentDataSource ();
	void SetPeakProperties (LPCTSTR lpszLib);

private:
	CAdjustDlg*		m_pAdjustDlg;
	Preference*		m_pPrefs;
	CSeqAnalyzer*	m_pdlgEditSeq;

	RECT	m_rectMainWnd;
	RECT	m_rectMvc;
	RECT	m_rectReport;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__37C3B309_6C9C_4AD3_B88F_E57CE9C4D475__INCLUDED_)
