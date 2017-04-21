#if !defined(AFX_CLIENTSOCKET_H__B0B7697A_2305_4458_A31F_313766C23F25__INCLUDED_)
#define AFX_CLIENTSOCKET_H__B0B7697A_2305_4458_A31F_313766C23F25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//


class CServerSocket;
class CComData;

/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CClientSocket : public CSocket
{
// Attributes
public:

private:
	CServerSocket*	m_pServerSocket;
	CSocketFile*	m_pSocketFile;
	CArchive*		m_pArchiveIn;
	CArchive*		m_pArchiveOut;

// Operations
public:
	CClientSocket(CServerSocket* pServerSocket);
	virtual ~CClientSocket();
	
	void Init();
	void SendCom(CComData* pComData);
	void ReceiveCom(CComData* pComData);

private:
	void Finalize();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__EC927DD3_D49B_4AAB_A675_2E5CE2BDB9AA__INCLUDED_)
