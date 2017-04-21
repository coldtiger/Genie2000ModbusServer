#if !defined(AFX_SERVERSOCKET_H__B23B4D6D_E7F8_4DAB_ACC4_E7E8C444446A__INCLUDED_)
#define AFX_SERVERSOCKET_H__B23B4D6D_E7F8_4DAB_ACC4_E7E8C444446A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSocket.h : header file
//

class CClientSocket;
class CComData;
class CWnd;

/////////////////////////////////////////////////////////////////////////////
// CServerSocket command target

class CServerSocket : public CSocket
{

// Attributes
public:

private:
	CWnd*	m_pMainFrame;
	int         m_nMaxClients;
public:
	CPtrList    m_ClientstList;
	unsigned int         Coils[1000];
	unsigned int         Inputs[1000];
	unsigned int         Registers[1000];
	unsigned int         InputRegisters[1000];

// Operations
public:
	CServerSocket(CWnd* pMainFrame);
	virtual ~CServerSocket();

	void ProcessClientCom(CClientSocket* pClientSocket);
	BOOL BeginListening(UINT uPort, int nMaxClients);
	BOOL BeginListening(LPCTSTR addr,UINT uPort, int nMaxClients);
	int GetClientsConnectedCount();
	int GetTotalMessagesCount();
	CPtrList* GetClientsList();
	void KickUser(CString szClient);
	void SendMessageTo(CString szClient, CString szMessage);

private:
	void ProcessAccept();		
	BOOL IsThisLoginBeingUsed(CComData& pComData, CClientSocket* pClientSocket);
	void UpdateClientInfo(CComData* pComData, CClientSocket* pClientSocket);
	//void UpdateClientsList();
	void UpdateClientsInfo(CTime Time, CComData* pComData, CClientSocket* pClientSocket);
	void RemoveClient(CComData* pComData, CClientSocket* pClientSocket);
	void CloseClients();
	void AddToRemoteClientsList();
	void RemoveFromClientsList(CString szClient);
	void RedirectPrivateMessageTo(CComData* pComData);
	
// Overrides
public:
	void CloseClient(CClientSocket* Client);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCKET_H__B23B4D6D_E7F8_4DAB_ACC4_E7E8C444446A__INCLUDED_)
