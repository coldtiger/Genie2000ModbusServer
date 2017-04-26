/*
* ==========================================================================
* Name:         MAINDlg.cpp : Implementation of CMainDialog
* Project:      Example
* Purpose:      This file contains implementaion of Main App Dialog.
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
#include "AboutDlg.h"
#include <stack>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#import "ReportView.tlb" no_namespace raw_interfaces_only
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainDialog dialog

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDialog)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


CMainDialog::~CMainDialog ()
{
	delete m_pPrefs;

	if (m_pAdjustDlg->GetSafeHwnd ())
		m_pAdjustDlg->DestroyWindow ();
	delete m_pAdjustDlg;
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDialog)
	DDX_Control(pDX, IDC_MVC1, m_cIMvc);
	DDX_Control(pDX, IDC_REPORTVIEWER1, m_cIReportWin);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainDialog, CDialog)
	//{{AFX_MSG_MAP(CMainDialog)
	ON_WM_COPYDATA()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_FILE_OPEN, OnOpen)
	ON_COMMAND(IDM_FILE_SAVE, OnSave)
	ON_COMMAND(IDM_FILE_SAVEAS, OnSaveAs)
	ON_COMMAND(IDM_FILE_CLOSE, OnFileClose)
	ON_COMMAND(IDM_FILE_CLOSEALL, OnCloseall)
	ON_COMMAND(IDM_FILE_PRINT, OnPrint)
	ON_COMMAND(IDM_FILE_COPY, OnCopy)
	ON_COMMAND(IDM_FILE_EXPORT, OnExport)
	ON_COMMAND(IDM_FILE_EXIT, OnExit)
	ON_COMMAND(IDM_MCA_ACQCLEAR, OnAcqclear)
	ON_COMMAND(IDM_MCA_ACQSETUP, OnAcqsetup)
	ON_COMMAND(IDM_MCA_ACQSTART, OnAcqstart)
	ON_COMMAND(IDM_MCA_ACQSTOP, OnAcqstop)
	ON_COMMAND(IDM_MCA_ADJUST, OnAdjust)
	ON_COMMAND(IDM_DISPLAY_EXPAND, OnExpand)
	ON_COMMAND(IDM_DISPLAY_NUCLINES_NLINE, OnNuclinesNextNucline)
	ON_COMMAND(IDM_DISPLAY_NUCLINES_NNUC, OnNuclinesNext)
	ON_COMMAND(IDM_DISPLAY_NUCLINES_PLINE, OnNuclinesPrevNucline)
	ON_COMMAND(IDM_DISPLAY_NUCLINES_PNUC, OnNuclinesPrev)
	ON_COMMAND(IDM_DISPLAY_ZOOM_MODE, OnZoomMode)
	ON_COMMAND(IDM_DISPLAY_ZOOM_OUT, OnZoomOut)
	ON_COMMAND(IDM_DISPLAY_SCALE_AUTO, OnScaleAuto)
	ON_COMMAND(IDM_DISPLAY_SCALE_LINEAR, OnScaleLinear)
	ON_COMMAND(IDM_DISPLAY_SCALE_LOG, OnScaleLog)
	ON_COMMAND(IDM_DISPLAY_RIOS_ADD, OnRiosAdd)
	ON_COMMAND(IDM_DISPLAY_RIOS_CLEAR, OnRiosClear)
	ON_COMMAND(IDM_DISPLAY_RIOS_LOAD, OnRiosLoad)
	ON_COMMAND(IDM_DISPLAY_RIOS_NEXT, OnRiosNext)
	ON_COMMAND(IDM_DISPLAY_RIOS_PREV, OnRiosPrev)
	ON_COMMAND(IDM_DISPLAY_RIOS_STORE, OnRiosStore)
	ON_COMMAND(IDM_DISPLAY_ROIS_DEL, OnRoisDel)
	ON_COMMAND(IDM_DISPLAY_NUCLINES_SHOW, OnNuclinesShow)
	ON_WM_CLOSE()
	ON_COMMAND(IDM_DISPLAY_PREF, OnPrefence)
	ON_COMMAND(IDM_ANALYSIS_EDITSEQ, OnEditseq)
	ON_COMMAND(IDM_ANALYSIS_Test, OnAutoExecute)
	ON_COMMAND(IDM_ANALYSIS_EXECUTE, OnExecute)
	ON_COMMAND(IDM_ANALYSIS_EXECURR, OnExecuteCurrent)
	ON_COMMAND(IDM_ANALYSIS_SHOWREPORT, OnShowReportWinodow)
	ON_COMMAND(IDM_ANALYSIS_PRINTREPORT, OnPrintReport)
	ON_COMMAND(IDM_ANALYSIS_SAVEREPORT, OnSaveReport)
	ON_COMMAND(IDM_ANALYSYS_COPYSELECTED, OnCopySelectedReport)
	ON_COMMAND(IDM_ANALYSIS_COPYREPORT, OnCopyReport)
	ON_COMMAND(IDM_DATASOURCE_NEXT, OnNextDatasource)
	ON_COMMAND(IDM_DATASOURCE_PREV, OnPrevDatasource)
	ON_COMMAND(IDM_EDIT_CFE, OnCertificateFileEditor)
	ON_COMMAND(IDM_EDIT_SAMPLEEDITOR, OnSampleEditor)
	ON_COMMAND(IDM_EDIT_SHOWCALIB, OnShowCalibrations)
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDialog message handlers

BOOL CMainDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Init COM Library...
	if (FAILED (CoInitialize (NULL)))
		return FALSE;

	// Initialize all genie components...
	m_pAdjustDlg = new CAdjustDlg ();
	m_pAdjustDlg->Create (CAdjustDlg::IDD);
	m_pAdjustDlg->ShowWindow (SW_HIDE);
	

	m_pPrefs = new Preference;
    LoadPrefs ();
	SetPrefs ();

	UpdateMenus ();

	// get different windows rectangles
	WINDOWPLACEMENT WndPlacement;

	GetWindowPlacement (&WndPlacement);
	m_rectMainWnd = WndPlacement.rcNormalPosition;

	m_cIMvc.GetWindowPlacement (&WndPlacement);
	m_rectMvc = WndPlacement.rcNormalPosition;
/*	m_rectMvc.left = 5;
	m_rectMvc.right = m_rectMainWnd.right - 5;
	m_rectMvc.top = 5;
	m_rectMvc.bottom = (long) ((m_rectMainWnd.bottom - m_rectMainWnd.top) * 0.75);
	WndPlacement.rcNormalPosition = m_rectMvc;
	WndPlacement.length = sizeof (WINDOWPLACEMENT);
	m_cIMvc.SetWindowPlacement (&WndPlacement);
	m_cIMvc.GetWindowPlacement (&WndPlacement);*/

	m_cIReportWin.GetWindowPlacement (&WndPlacement);
	m_rectReport = WndPlacement.rcNormalPosition;
/*	m_rectReport.left = 5;
	m_rectReport.right = m_rectMainWnd.right - 5;
	m_rectReport.bottom = m_rectMainWnd.bottom - 5;
	m_rectReport.top = (long) ((m_rectMainWnd.bottom - m_rectMainWnd.top) * 0.75) + 5;	
	WndPlacement.rcNormalPosition = m_rectReport;
	WndPlacement.length = sizeof (WINDOWPLACEMENT);
	m_cIReportWin.SetWindowPlacement (&WndPlacement);
	m_cIReportWin.GetWindowPlacement (&WndPlacement);*/

	OnShowReportWinodow();

	m_cIReportWin.EnableAutomation ();
	status=0;//0,未探测状态；1,探测状态
	OutputName="test";//输出文件名

	StartServer();//开启服务端点
	SetTimer(IDTIMER1,1000,0);//打开定时器

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDialog::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}



// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDialog::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CMainDialog::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{	
	BOOL bRet = CDialog::Create(IDD, pParentWnd);
	m_cIMvc.SetShowPlotBorders(TRUE);
	return bRet;
}

void CMainDialog::OnClose() 
{
	OnCloseall ();
	CDialog::OnClose();
}





void CMainDialog::ResizeWindow (UINT unState)
{
    if (unState == MF_CHECKED)
		{
		WINDOWPLACEMENT WndPlacement;
		m_cIMvc.GetWindowPlacement (&WndPlacement);
		WndPlacement.rcNormalPosition = m_rectMvc;
		m_cIMvc.SetWindowPlacement (&WndPlacement);

		m_cIReportWin.GetWindowPlacement (&WndPlacement);
		WndPlacement.rcNormalPosition = m_rectReport;
		m_cIReportWin.SetWindowPlacement (&WndPlacement);

		m_cIReportWin.ShowWindow (SW_SHOW);
		}
    else
		{
		m_cIReportWin.ShowWindow (SW_HIDE);

		WINDOWPLACEMENT WndPlacement;
		m_cIMvc.GetWindowPlacement (&WndPlacement);
		WndPlacement.rcNormalPosition = m_rectMvc;
		WndPlacement.rcNormalPosition.bottom = m_rectReport.bottom;
		m_cIMvc.SetWindowPlacement (&WndPlacement);
		}
}

void CMainDialog::OnSize(UINT nType, int cx, int cy) 
{
	if (::IsWindowVisible (m_cIMvc.m_hWnd))
		{
		WINDOWPLACEMENT WndPlacement;
		GetWindowPlacement (&WndPlacement);
		m_rectMainWnd = WndPlacement.rcNormalPosition;

		m_cIMvc.GetWindowPlacement (&WndPlacement);
		m_rectMvc = WndPlacement.rcNormalPosition;
		m_rectMvc.left = 5;
		m_rectMvc.right = cx - 5;
		m_rectMvc.top = 5;

		if (!::IsWindowVisible (m_cIReportWin.m_hWnd))
			m_rectMvc.bottom = cy - 5;
		else
			m_rectMvc.bottom = (long) ((m_rectMvc.top + cy) * 0.75);

		WndPlacement.rcNormalPosition = m_rectMvc;
		WndPlacement.length = sizeof (WINDOWPLACEMENT);
		m_cIMvc.SetWindowPlacement (&WndPlacement);

		if (::IsWindowVisible (m_cIReportWin.m_hWnd))
			{
			m_cIReportWin.GetWindowPlacement (&WndPlacement);
			m_rectReport = WndPlacement.rcNormalPosition;

			m_rectReport.left = 5;
			m_rectReport.right = cx - 5;
			m_rectReport.bottom = cy - 5;
			m_rectReport.top = m_rectMvc.bottom + 5;
			WndPlacement.rcNormalPosition = m_rectReport;
			WndPlacement.length = sizeof (WINDOWPLACEMENT);
			m_cIReportWin.SetWindowPlacement (&WndPlacement);
			m_cIReportWin.InvalidateRect (NULL);
			}

		if (nType == SIZE_MAXIMIZED)
			m_cIMvc.InvalidateRect (NULL);
		}

	CDialog::OnSize(nType, cx, cy);	
}

// This routine returns Current data source that is opened/active
// depending on datassource type - file or detector
// NOTE: Make sure to call "Release" for this dispatch pointer explicitely.
LPDISPATCH CMainDialog::GetCurrentDataSource ()
{
	IDataAccessPtr m_pIDataAcc = m_cIMvc.GetCurrentDataSource ();
	DeviceAccess::IDeviceAccessPtr m_pIDevAcc = m_cIMvc.GetCurrentDataSource ();

	if (IsDetector ())
		return m_pIDevAcc;
	else
		return m_pIDataAcc;
}

// Trap "Excape" and "Return" keys before processing...
// We need to do that because, otherwize, after receiving these key strokes
// dialog gets terminated which we had to prevent.
BOOL CMainDialog::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


//START
//开启服务端
void CMainDialog::StartServer(){
	CString szIPAdress;

	CString szBuf;

	UINT uPort = 502;
	/*
	if (uPort < DEFAULT_MIN_PORT_NUMBER || uPort > DEFAULT_MAX_PORT_NUMBER) {
		szBuf.Format(IDS_INVALID_PORT_NUMBER, DEFAULT_MIN_PORT_NUMBER,
											  DEFAULT_MAX_PORT_NUMBER); 
		AfxMessageBox("beyond the port range");
		return;
	}*/

	//ClearAllViews();

	m_pServerSocket = new CServerSocket(this);
	if (m_pServerSocket->BeginListening(uPort, -1)) {
		szBuf.Format("Server started and online on port %d!", uPort);
		
		/*
	 	AddServerCom(CTime::GetCurrentTime(),
					CString("Server"),
					SERVER_ICON,
					szBuf);	
		*/
		//m_DlgBarUtil.BlockConrols();
		m_bServerStarted = TRUE;
	}
	else {
	//	DisconnectServer();
	}
}
//停止服务端
void CMainDialog::StopServer(){

	DisconnectServer();
}
BOOL CMainDialog::DisconnectServer()
{
	if (!m_pServerSocket)
		return TRUE;
	
	int nClients = m_pServerSocket->GetClientsConnectedCount();
	if (nClients > 0) {
		CString szBuf;
		szBuf.Format("%d client's are currently connected to server.\nAre you sure that you want to stop server?", nClients);
		int nRet = MessageBox(szBuf, CString((LPCTSTR)IDR_MAINFRAME), MB_ICONQUESTION|MB_YESNO);
		if (nRet == IDNO)
			return FALSE;
	}

/*
	AddServerCom(CTime::GetCurrentTime(),
				CString((LPCTSTR)IDS_COM_SERVER),
				SERVER_ICON,
				CString((LPCTSTR)IDS_COM_SERVER_DISCONNECTED));	
*/
	if (m_pServerSocket) {
		delete m_pServerSocket;
		m_pServerSocket = NULL;
	}

	m_bServerStarted = FALSE;

	return TRUE;
}
//开始测量：第一个参数，选择测量模式1=Live/0=Real;第二个参数，设置测量结果文件名
void CMainDialog::StartDetection(BOOL LiveOrReal,int t,CString Name){
	DeviceAccess::IDeviceAccessPtr m_pIDevAcc = m_cIMvc.GetCurrentDataSource ();
	
	if(LiveOrReal)
		m_pIDevAcc->SpectroscopyAcquireSetup ((DeviceAccess::AcquisitionModes)CanberraDataDisplayLib::aCountToLiveTime, t, 0, 0, 0.0, 0.0);
	else
		m_pIDevAcc->SpectroscopyAcquireSetup ((DeviceAccess::AcquisitionModes)CanberraDataDisplayLib::aCountToRealTime, t, 0, 0, 0.0, 0.0);
	
	m_pIDevAcc.Release ();
	OutputName=Name;
	OnAcqstart();
	SetTimer(IDTIMER1,t*1000+2000,0);
	status=1;
}

//计时器
void CMainDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(status)
	{
		case 0:
		{
			if(m_pServerSocket->Coils[0]==1){//开始探测
				int len=m_pServerSocket->Registers[1];
				CString name="";
				for(int i=0;i<len;i++)
					name=name +(char)m_pServerSocket->Registers[i+2];

				StartDetection(m_pServerSocket->Coils[1],m_pServerSocket->Registers[0],name);
			}
			break;
		}
		case 1:
		{
			if(m_pAdjustDlg->m_cIAdjustCtl.Busy())//未探测完成
			{
				SetTimer(IDTIMER1,3000,0);
			}
			else
			{
				//探测完成
				SetTimer(IDTIMER1,1000,0);
				status=0;
				OnAutoExecute();
				AutoSaveReport();
				SendOK();		
			}
			break;
		}
		
		default:break;
	}
	CDialog::OnTimer(nIDEvent);
}



void CMainDialog::OnAutoExecute() 
{

    char strAsfFiles [255];
           
    // Change current drive
    GetEnvironmentVariable (_T("ASEQFILES"), strAsfFiles, 255);
    CString filepath;
	filepath.Format(_T("%s"), strAsfFiles);
	filepath=filepath+"\\TGS.asf";

 	// Use the MFC Common Dialog to get a filename

	ISequenceAnalyzerPtr m_pISeqAnalyzer;
	HRESULT hRes = m_pISeqAnalyzer.CreateInstance(__uuidof(SequenceAnalyzer)); 
	if (FAILED(hRes))
	{
		if (IDCANCEL == AfxMessageBox (_T("Failed to initialize Sequence Analyzer Component. Do you wish to continue?"), MB_ICONQUESTION | MB_YESNO))
			return;
	}

	LPDISPATCH lpDisp = GetCurrentDataSource ();

	try
	{
		

		CComPtr<IReportViewer> pIReportViewer;
		IUnknown *pUnknown = m_cIReportWin.GetControlUnknown(); 
		LPDISPATCH pTemp = NULL; 
		short sStart = 0;
		if (pUnknown)
		{
			pUnknown->QueryInterface(&pTemp); 
			pTemp->QueryInterface( __uuidof(IReportViewer), (void**)&pIReportViewer);
			if (pIReportViewer)
			{
				pIReportViewer->Clear();
// TO display output in reporter window
				m_pISeqAnalyzer->Analyze (lpDisp, &sStart, 
										  (_bstr_t) filepath, 
										  VARIANT_TRUE, VARIANT_FALSE, VARIANT_FALSE, VARIANT_FALSE, 
										  NULL, pIReportViewer);
// TO display output in text file
//			m_pISeqAnalyzer->Analyze (lpDisp, &sStart, 
//									  (_bstr_t) OpenDialog.GetPathName (), 
//									  VARIANT_TRUE, VARIANT_FALSE, VARIANT_FALSE, VARIANT_FALSE, 
//									  (_bstr_t) _T("c:\\Output.txt"), NULL);
			}
		}
	}
	catch (COleDispatchException* pException)
	{
		char chStr [255];
		pException->GetErrorMessage (chStr, 255);
		AfxMessageBox (chStr);
	}
   


	lpDisp->Release ();
	m_pISeqAnalyzer.Release ();
	//AutoSaveReport ();
}
//存储文件
void CMainDialog::AutoSaveReport () 
{
	
    // Get a default file name
	
	CHAR pathbuf[255];   //存储当前应用程序全路径
	int pathlen=::GetModuleFileName (NULL,pathbuf,255);
	while(1)
	{
		 if(pathbuf[pathlen--]=='\\') 
		 break;
	}
	pathbuf[++pathlen]=0x0;
	
	CString fpath=pathbuf;
	CString cnfname=pathbuf;

	fpath=fpath+"\\report";

	if(!PathIsDirectory(fpath))
		::CreateDirectory(fpath,NULL);

	cnfname=cnfname+"\\report\\"+OutputName + _T(".cnf");
    fpath=fpath+"\\"+OutputName + _T(".rpt");
   
	
	
	
	m_cIMvc.Save (cnfname, TRUE);
	m_cIReportWin.SaveText (fpath, TRUE);
}
//探测完成，反馈信息
void CMainDialog::SendOK() 
{
	m_pServerSocket->Coils[0]=0;

	/*
	CWnd *pWnd=CWnd::FindWindow(NULL,_T("SendMessage"));    // 查找进程
	if(pWnd==NULL){
		MessageBox("Unable to find Gamma Scanning Detection.");
		return;
	} 
	COPYDATASTRUCT cpd;
	cpd.dwData = 0;
	cpd.cbData = 17;
	cpd.lpData = "DetectionFinished";
	pWnd->SendMessage(WM_COPYDATA,NULL,(LPARAM)&cpd);   // 发送
	*/
}
//重写的设置参数输入函数(失效)
BOOL CMainDialog::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)  
{
	CString temp=(LPSTR)pCopyDataStruct->lpData;
	temp=temp.Left(pCopyDataStruct->cbData);
	CString temp2;
	//MessageBox(temp);

	if(status==0)
	{
		if(temp.Left(2)=="DE")
		{
			temp.Delete(0,3);
			DeviceAccess::IDeviceAccessPtr m_pIDevAcc = m_cIMvc.GetCurrentDataSource ();			
			m_pIDevAcc->SpectroscopyAcquireSetup ((DeviceAccess::AcquisitionModes)CanberraDataDisplayLib::aCountToLiveTime, atof (temp.Left(4)), 0, 0, 0.0, 0.0);
			m_pIDevAcc.Release ();
			int i=atoi(temp.Left(4));
			temp2.Format("%d",i);
			//MessageBox(temp2+"second");
			temp.Delete(0,4);
			OutputName=temp;
			OnAcqstart();
			SetTimer(IDTIMER1,i*1000+2000,0);
			status=1;
		}else if(temp.Left(2)=="MD")
		{
			temp.Delete(0,3);
			DeviceAccess::IDeviceAccessPtr m_pIDevAcc = m_cIMvc.GetCurrentDataSource ();			
			m_pIDevAcc->SpectroscopyAcquireSetup ((DeviceAccess::AcquisitionModes)CanberraDataDisplayLib::aCountToRealTime, atof (temp.Left(4)), 0, 0, 0.0, 0.0);
			m_pIDevAcc.Release ();
			int i=atoi(temp.Left(4));
			temp2.Format("%d",i);
			temp.Delete(0,4);
			OutputName=temp;
			OnAcqstart();
			SetTimer(IDTIMER1,i*1000+2000,0);
			status=1;
		}
	}
  return CWnd::OnCopyData(pWnd, pCopyDataStruct);  
}