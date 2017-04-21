// ClientSocket.cpp : implementation file
//

#include "stdafx.h"

#include "ClientSocket.h"
#include "ServerSocket.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket(CServerSocket* pServerSocket)
{
	ASSERT(pServerSocket);
	m_pServerSocket = pServerSocket;
	m_pSocketFile = NULL;
	m_pArchiveIn  = NULL;
	m_pArchiveOut = NULL;
}

void CClientSocket::Init()
{
	m_pSocketFile = new CSocketFile(this);
	m_pArchiveIn  = new CArchive(m_pSocketFile,CArchive::load);
	m_pArchiveOut = new CArchive(m_pSocketFile,CArchive::store);
}

CClientSocket::~CClientSocket()
{
	Close();
	
	m_pServerSocket = NULL;

}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions


void CClientSocket::OnReceive(int nErrorCode) 
{
	CSocket::OnReceive(nErrorCode);

	ASSERT(m_pServerSocket);
	m_pServerSocket->ProcessClientCom(this);
}


void CClientSocket::SendCom(CComData* pComData)
{
	ASSERT(pComData);

}

void CClientSocket::ReceiveCom(CComData* pComData)
{

}



void CClientSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
//     m_pServerSocket->OnClose(this);
	m_pServerSocket->CloseClient(this);
//	CSocket::OnClose(nErrorCode);
}
