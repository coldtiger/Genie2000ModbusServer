#include "stdafx.h"
//#include "ModbusClient.h"

#include "ServerSocket.h"
#include "ClientSocket.h"
#include "ComData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket(CWnd* pMainFrame)
{
	ASSERT(pMainFrame);
	m_pMainFrame = pMainFrame;
	m_nMaxClients = -1;
	m_ClientstList.RemoveAll();

	memset(Coils,0,4000);
	memset(Inputs,0,4000);
	memset(Registers,0,4000);
	memset(InputRegisters,0,4000);
}

CServerSocket::~CServerSocket()
{
	CloseClients();
	//UpdateClientsList();
	Close();
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListeningSocket member functions

BOOL CServerSocket::BeginListening(UINT uPort, int nMaxClients)
{

	m_nMaxClients = nMaxClients;
	
	if(!m_ClientstList.IsEmpty())
		CloseClients();


	if (!Create(uPort))
		return FALSE;

	if (!Listen())
		return FALSE;

	return TRUE;
}

BOOL CServerSocket::BeginListening(LPCTSTR addr,UINT uPort, int nMaxClients)
{

	m_nMaxClients = nMaxClients;
	
	if(!m_ClientstList.IsEmpty())
		CloseClients();


	if (!Create(uPort,SOCK_STREAM,addr))
		return FALSE;

	if (!Listen())
		return FALSE;

	return TRUE;
}

void CServerSocket::OnAccept(int nErrorCode) 
{
	CSocket::OnAccept(nErrorCode);

	ProcessAccept();
}

//when got a connection message from a client
void CServerSocket::ProcessAccept()
{
	
	//client number exceeds maxclient
	if (m_nMaxClients != -1) 
	{
		if (m_nMaxClients <= m_ClientstList.GetCount())
		{
			try {
				//send the connection confirmation to the client,add to the list - yh
				CComData ComData;
				ComData.szFrom	  =CString("Maximum clients reached. Try loggin again an other time.");

				ComData.szMessage = CString("Maximum clients reached. Try loggin again an other time.");
				ComData.uMessage  = CComData::COM_CLOSE;

				/*
	 		     m_pMainFrame->AddServerCom(CTime::GetCurrentTime(),
											ComData.szFrom,
											3,
											CString("Client connection refused. Max clients reached.");
				*/							 
		 		return;
				}
			catch(CFileException* e){
				TCHAR csError[CHAR_BUFFER_SIZE];
				e->GetErrorMessage(csError, CHAR_BUFFER_SIZE);
				AfxMessageBox(csError);
				}
		}
	}
 



	CClientSocket* pClientSocket = new CClientSocket(this);
	ASSERT(pClientSocket);

	if (!Accept(*pClientSocket)) {
		delete pClientSocket;
		return;
	}
	pClientSocket->Init(); 

	CString szIPAddress;
	UINT	uPort;
	pClientSocket->GetPeerName(szIPAddress, uPort);	
	CString szBuf;
	szBuf.Format(":%d",uPort);
//	itoa(uPort,StringuPort+1,10);
	sClientComInfos* pClientCom = new sClientComInfos;
	ASSERT(pClientCom);
	pClientCom->ComData.szIPAddress = szIPAddress;
	pClientCom->ComData.uPort = uPort;
	pClientCom->ComData.pSocket = (DWORD)pClientSocket;
	pClientCom->TimeStarted = CTime::GetCurrentTime();

 
	try {
		//send the connection confirmation to the client,add to the list - yh
		CComData ComData;
		ComData.szFrom	  =pClientCom->ComData.szIPAddress+szBuf;
		ComData.uSignIcon = 9;
		ComData.szMessage = CString("Connected to server. Please Sign in now ...");
		ComData.uMessage  = CComData::COM_SIGN_IN;

		/*
		m_pMainFrame->AddServerCom(CTime::GetCurrentTime(),
										ComData.szFrom,
										ComData.uSignIcon,
										CString("Connected to server. (Sign in)"));
		*/
	}
	catch(CFileException* e){
		TCHAR csError[CHAR_BUFFER_SIZE];
		e->GetErrorMessage(csError, CHAR_BUFFER_SIZE);
		AfxMessageBox(csError);
	}

	if(m_ClientstList.IsEmpty()){
		m_ClientstList.AddHead(pClientCom);
	}
	else{
		m_ClientstList.AddTail(pClientCom);
	}

	//UpdateClientsList();
}


void CServerSocket::ProcessClientCom(CClientSocket* pClientSocket)
{
	//	pClientSocket->ReceiveCom(&ComData);
//	unsigned char *pBuf=new unsigned char[1025];
	unsigned char pBuf[250];
	int nBufSize=1024;
	int nReceived;
	
	char Command[200];
	CString strReceived;
	int ReceiveCommandLength;
	int SendCommandLength;
    int i,j;
	int FunctionCode;
	int Size;
	int NOofBytes,count;
	int Address;
	bool CorrectResPonse;
    CString szBuf;  
	//receive the message
	nReceived=pClientSocket->Receive(pBuf,nBufSize);
	if (nReceived!=SOCKET_ERROR)
	{
		//truncate the end of the message
		pBuf[nReceived]=NULL;
		//copy the message to a CString
		strReceived=pBuf;
		//add the message to the received list box
	//	m_listReceived.AddString(strReceived);
		//Update the dialog
	
		//		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox("Communication Error!",MB_OK|MB_ICONSTOP);
	}



	int nCount = m_ClientstList.GetCount();
	for (  i = 0; i < nCount; i++) 
	{
		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		szBuf.Format(":%d",pComDataTmp->uPort);
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);
		CorrectResPonse=false;
		if (pClientSocketTmp== pClientSocket)
		{
			//YWP ADD
			 for(j=0;j<50000;j++);
				
			  if(nReceived>6)
				//if(pBuf[0]==0x30||pBuf[1]==0x30)
				 {
						ReceiveCommandLength=(pBuf[4]<<8)+pBuf[5];
						CorrectResPonse=true;
						FunctionCode=pBuf[7];
						Address=(pBuf[8]<<8)+pBuf[9];
						Size=(pBuf[10]<<8)+pBuf[11];
						if(Size==0)Size=1;

					    Command[0]=pBuf[0]; 
					    Command[1]=pBuf[1]; 

					    Command[2]=pBuf[2]; 
					    Command[3]=pBuf[3]; 

					    Command[4]=pBuf[4];  

					    Command[6]=pBuf[6]; //ID

						CorrectResPonse=true;

						switch(FunctionCode)
						{
						case 1://read coils
							  Command[7]=1;

							  Command[8]=(Size-1)/8+1;
							  for(i=0;i<Command[8];i++)
							  {
                                  Command[9+i]=0;  
								  for(j=7;j>=0;j--)
									{
										  Command[9+i]=Command[9+i]*2+Coils[Address+i*8+j];
									}
							  }
							  Command[5]=3+Command[8];
							  SendCommandLength=9+Command[8];
							  pClientSocket->Send(Command,SendCommandLength);
							  break;	

						case 2://read inputs
							  Command[7]=2;

							  Command[8]=(Size-1)/8+1;
							  for(i=0;i<Command[8];i++)
							  {
                                  Command[9+i]=0;  
								  for(j=7;j>=0;j--)
									{
										   Command[9+i]=Command[9+i]*2+Inputs[Address+i*8+j];
									}
							  }
							  Command[5]=3+Command[8];
							  SendCommandLength=9+Command[8];
							  pClientSocket->Send(Command,SendCommandLength);
							  break;

						case 4://read input registers
							Command[7]=4;

							Command[8]=Size*2;
							for(i=0;i<Size;i++)
								{
								   Command[9+i*2]=(InputRegisters[Address+i]>>8)&0xff;
								   Command[9+i*2+1]=InputRegisters[Address+i]&0xff;
								}
							  Command[5]=3+Command[8];
						      SendCommandLength=9+Command[8];
							  pClientSocket->Send(Command,SendCommandLength);
							  break;			
							  
						case 3://read holding registers

							  Command[7]=3;

							  Command[8]=Size*2;
							  for(i=0;i<Size;i++)
								{
								   Command[9+i*2]=(Registers[Address+i]>>8)&0xff;
								   Command[9+i*2+1]=Registers[Address+i]&0xff;
								}
							   Command[5]=3+Command[8];
						       SendCommandLength=9+Command[8];
							   pClientSocket->Send(Command,SendCommandLength);
							   break;	

						case 5://write single coil
							    Command[5]=6;

								Command[7]=5;
								Command[8]=pBuf[8];
								Command[9]=pBuf[9];
								Command[10]=pBuf[10];
								Command[11]=pBuf[11];

								if(Command[10]==0)	
									Coils[Address]=0;
								else
									Coils[Address]=1;


								SendCommandLength=12;
							    pClientSocket->Send(Command,SendCommandLength);
						        break;

						case 15://write multiple coils
							Command[5]=6;

							Command[7]=15;
							Command[8]=pBuf[8];//address
							Command[9]=pBuf[9];
							Command[10]=pBuf[10];//NO of Coils
							Command[11]=pBuf[11];

							NOofBytes=pBuf[12];//NO of bytes
							
							count=0;
							for(i=0;i<NOofBytes;i++)
							{
								for(j=0;j<8;j++)
								{
									if(pBuf[13+i]&1)
										Coils[Address+i*8+j]=1;
									else
										Coils[Address+i*8+j]=0;

									pBuf[13+i]=pBuf[13+i]>>1;
									count++;
									if(count==Size)goto A;
								}

							}
							A:
							SendCommandLength=12;
							pClientSocket->Send(Command,SendCommandLength);

							break;

						case 6://write single register
							Command[5]=6;

							Command[7]=6;
							Command[8]=pBuf[8];//address
							Command[9]=pBuf[9];
							Command[10]=pBuf[10];//value
							Command[11]=pBuf[11];

							Registers[Address]=((unsigned int)(pBuf[10])<<8);
							Registers[Address]+=(unsigned int)pBuf[11];

							SendCommandLength=12;
							pClientSocket->Send(Command,SendCommandLength);

							break;

						case 16://write multiple registers
						
							    Command[5]=6;

								Command[7]=16;
								Command[8]=pBuf[8];//address
								Command[9]=pBuf[9];
								Command[10]=pBuf[10];//NO of registers
								Command[11]=pBuf[11];
								
								NOofBytes=pBuf[12];//NO of bytes

								for(i=0;i<Size;i++)
								{
                					Registers[Address+i]=((unsigned int)(pBuf[13+i*2])<<8);
									Registers[Address+i]+=(unsigned int)pBuf[14+i*2];
								}

	     				        SendCommandLength=12;
							    pClientSocket->Send(Command,SendCommandLength);
								break;
						default:
								CorrectResPonse=false;
			   		            break;
						}
				

				


	/*
	char Ascii[300];
   if(CorrectResPonse){
		j=0;
   }
	else
		{
		   Ascii[0]='E';
		   Ascii[1]='r';
		   Ascii[2]='r';
		   Ascii[3]='o';
		   Ascii[4]='r';
		   Ascii[5]=':';
		   j=6;
		}

								k=0;
								for(i=0;i<pBuf[5]+6;i++)
									{  
									    k=(pBuf[i]>>4)&0x0f;
										k=k+0x30;
										if(k>0x39)  k=k+7;
										Ascii[j]=k;
										j++;
										k=pBuf[i]&0x0F;
										k=k+0x30;
										if(k>0x39)  k=k+7;
										Ascii[j]=k;
										j++;

										Ascii[j]=0x20;
										j++;
								}
								Ascii[j]=0x00;
								szBuf.Format(":%d",pComDataTmp->uPort);
								
								m_pMainFrame->AddServerCom(CTime::GetCurrentTime(),
										pComDataTmp->szIPAddress+szBuf,
										9,
										Ascii);
											
								
								
								
        if(CorrectResPonse)
		{								
								
								j=0;
								k=0;
								for(i=0;i<Command[5]+6;i++)
									{  
									    k=(Command[i]>>4)&0x0f;
										k=k+0x30;
										if(k>0x39)  k=k+7;
										Ascii[j]=k;
										j++;
										k=Command[i]&0x0F;
										k=k+0x30;
										if(k>0x39)  k=k+7;
										Ascii[j]=k;
										j++;

										Ascii[j]=0x20;
										j++;
								}
									Ascii[j]=0x00;
									
									m_pMainFrame->AddServerCom(CTime::GetCurrentTime(),
										"Server response",
										SERVER_ICON,
										Ascii);
									
							
		}
*/
       return;


			 }//if

		}//if

     
	}//For


}

void CServerSocket::CloseClient(CClientSocket* Client)
{
	//AfxMessageBox("CloseClient");	

	CString szBuf;


	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {

		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		szBuf.Format(":%d",pComDataTmp->uPort);
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);

		if (pClientSocketTmp== Client)
				{
						m_ClientstList.RemoveAt(m_ClientstList.FindIndex(i));
						delete pClientSocketTmp;
						pClientSocketTmp = NULL;
						/*	
						m_pMainFrame->AddServerCom(CTime::GetCurrentTime(),
										pComDataTmp->szIPAddress+szBuf,
										pComDataTmp->uSignIcon,
										CString((LPCTSTR)IDS_CLIENT_SIGN_OUT));
						*/
						//UpdateClientsList();
						return;
				}

	}
	//UpdateClientsList();

}


BOOL CServerSocket::IsThisLoginBeingUsed(CComData& ComData, CClientSocket* pClientSocket)
{
	AfxMessageBox("IsThisLoginBeingUsed");

	ASSERT(pClientSocket);

	if(ComData.szFrom == CString("Server"))
		return TRUE; // this name is used by server only!
	
	if(m_ClientstList.IsEmpty()) return TRUE;
	

	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {
		
		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);

		if(ComData.szFrom == pComDataTmp->szFrom &&
		   pClientSocket != pClientSocketTmp)
		    return TRUE;
	}

	return FALSE;
}

void CServerSocket::UpdateClientInfo(CComData* pComData, CClientSocket* pClientSocket)
{
	AfxMessageBox("UpdateClientInfo");

	ASSERT(pComData);
	ASSERT(pClientSocket);
/*
	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {

		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);

		if(pClientSocket == pClientSocketTmp) {

			pComDataTmp->szFrom    = pComData->szFrom;
			pComDataTmp->uSignIcon = pComData->uSignIcon;

			try {
				//send the connection confirmation to the client,add to the list - yh
				CComData ComDataTmp;
				CString szBuf;
				szBuf.Format(IDS_COM_SIGN_IN_ACCEPTED, pComDataTmp->szFrom);
				ComDataTmp.szFrom	 = CString((LPCTSTR)IDS_COM_SERVER);
				ComDataTmp.uSignIcon = SERVER_ICON;
				ComDataTmp.szMessage = szBuf;
				ComDataTmp.uMessage  = CComData::COM_MESSAGE;
				pClientSocket->SendCom(&ComDataTmp);
				Sleep(10);

				CComData ComDataTmp2;
				szBuf.Format(IDS_COM_NEW_CLIENT, pComDataTmp->szFrom);
				ComDataTmp2.szFrom	 = CString((LPCTSTR)IDS_COM_SERVER);
				ComDataTmp2.uSignIcon = pComDataTmp->uSignIcon;
				ComDataTmp2.szMessage = szBuf;
				ComDataTmp2.uMessage  = CComData::COM_MESSAGE;
				UpdateClientsInfo(CTime::GetCurrentTime(), &ComDataTmp2, pClientSocket);

			}
			catch(CFileException* e) {
				TCHAR csError[CHAR_BUFFER_SIZE];
				e->GetErrorMessage(csError, CHAR_BUFFER_SIZE);
				AfxMessageBox(csError);
			}
			return;
		}
	}
*/
  }


/*
void CServerSocket::UpdateClientsList()
{
	m_pMainFrame->UpdateClientsList(&m_ClientstList);
}
*/
void CServerSocket::UpdateClientsInfo(CTime Time, CComData* pComData, CClientSocket* pClientSocket)
{
	AfxMessageBox("UpdateClientInfo");

	ASSERT(pComData);	
	
	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {

		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);

		if (pClientSocket == pClientSocketTmp) {

			CString szBuf;
			szBuf.Format("%s;%s", Time.Format("%m/%d/%Y %H:%M:%S"), pComData->szMessage); 
			if (pClientCom->szMessagesList.IsEmpty())
				pClientCom->szMessagesList.AddHead(szBuf);
			else
				pClientCom->szMessagesList.AddTail(szBuf);
		}
		else {
			try {
				pClientSocketTmp->SendCom(pComData);
			}
			catch(CFileException* e) {
				TCHAR csError[CHAR_BUFFER_SIZE];
				e->GetErrorMessage(csError, CHAR_BUFFER_SIZE);
				AfxMessageBox(csError);
			}		
		}
	}
}

void CServerSocket::RemoveClient(CComData* pComData, CClientSocket* pClientSocket)
{
	AfxMessageBox("RemoveClient");

	ASSERT(pComData);
	
	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {

		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);
		
		if(pClientSocket == pClientSocketTmp) {

			m_ClientstList.RemoveAt(m_ClientstList.FindIndex(i));

			pClientSocketTmp->Close();
			delete pClientSocketTmp;
			pClientSocketTmp = NULL;

			if (!pComDataTmp->szFrom.IsEmpty()) {
				CComData ComDataTmp;
				CString szBuf;
			/*	szBuf.Format(IDS_COM_CLIENT_QUIT, pComDataTmp->szFrom);
				ComDataTmp.szFrom	 = CString((LPCTSTR)IDS_COM_SERVER);
				ComDataTmp.uSignIcon = SERVER_ICON;
				ComDataTmp.szMessage = szBuf;
				ComDataTmp.uMessage  = CComData::COM_MESSAGE;
				UpdateClientsInfo(CTime::GetCurrentTime(), &ComDataTmp, pClientSocket);
				*/
			}

			pClientCom->szMessagesList.RemoveAll();  
			delete pClientCom;
			pClientCom = NULL;
			return;
		}
	}
}

void CServerSocket::CloseClients()
{
	AfxMessageBox("CloseClients");

	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {

		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);

 

		pClientSocketTmp->Close();
		delete pClientSocketTmp;
		pClientSocketTmp = NULL;

		CString szBuf;
		szBuf.Format("%s: %s", pComDataTmp->szFrom, CString("Connection closed by server."));
		/*
		m_pMainFrame->AddServerCom(CTime::GetCurrentTime(),
									CString((LPCTSTR)IDS_COM_SERVER),
									SERVER_ICON,
									szBuf);	
									*/
		pClientCom->szMessagesList.RemoveAll();  
		

		delete pClientCom;
		pClientCom = NULL;
	}
	m_ClientstList.RemoveAll();

	//UpdateClientsList();

}


int CServerSocket::GetClientsConnectedCount()
{
	//AfxMessageBox("GetClientsConnectedCount");
//if(m_ClientstList.IsEmpty())
//		 return 0;
	return m_ClientstList.GetCount(); 
}

int CServerSocket::GetTotalMessagesCount()
{
	AfxMessageBox("GetTotalMessagesCount");
	int nMessageCount = 0;
	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {

		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);

		nMessageCount += pClientCom->szMessagesList.GetCount();  
	}

	return nMessageCount;
}

CPtrList* CServerSocket::GetClientsList()
{
	AfxMessageBox("GetClientsList");

	if (m_ClientstList.IsEmpty())
		return NULL;
	
	return &m_ClientstList;
}

void CServerSocket::AddToRemoteClientsList()
{
	AfxMessageBox("AddToRemoteClientsList");

	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {

		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);

		for (int j = 0; j < nCount; j++) {
		
			sClientComInfos* pClientCom2 = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(j));
			ASSERT(pClientCom2);
			CComData* pComDataTmp2 = (CComData*)&pClientCom2->ComData;
			ASSERT(pComDataTmp2);
			CClientSocket* pClientSocketTmp2 = (CClientSocket*)pComDataTmp2->pSocket;
			ASSERT(pClientSocketTmp2);
		
			if (pClientSocketTmp != pClientSocketTmp2) {
				try {
					CComData ComDataTmp;
					ComDataTmp.szFrom	 = CString("Server");
					ComDataTmp.uSignIcon = pComDataTmp2->uSignIcon;
					ComDataTmp.szMessage = pComDataTmp2->szFrom;
					ComDataTmp.uMessage  = CComData::COM_ADD_CLIENT;
					pClientSocketTmp->SendCom(&ComDataTmp);
				}
				catch(CFileException* e) {
					TCHAR csError[CHAR_BUFFER_SIZE];
					e->GetErrorMessage(csError, CHAR_BUFFER_SIZE);
					AfxMessageBox(csError);
				}			
			}
		}
	}
}

void CServerSocket::RemoveFromClientsList(CString szClient)
{
	AfxMessageBox("RemoveFromClientsList");

	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {

		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);

		/*if (pComDataTmp->szFrom != szClient) {
			try {
				CComData ComDataTmp;
				ComDataTmp.szFrom	 = CString((LPCTSTR)IDS_COM_SERVER);
				ComDataTmp.uSignIcon = SERVER_ICON;
				ComDataTmp.szMessage = szClient;
				ComDataTmp.uMessage  = CComData::COM_REMOVE_CLIENT;
				pClientSocketTmp->SendCom(&ComDataTmp);	
			}
			catch(CFileException* e) {
				TCHAR csError[CHAR_BUFFER_SIZE];
				e->GetErrorMessage(csError, CHAR_BUFFER_SIZE);
				AfxMessageBox(csError);
				
			}			
		}*/
	}	
}

void CServerSocket::SendMessageTo(CString szClient, CString szMessage)
{
	AfxMessageBox("SendMessageTo");


	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {

		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);

		if (pComDataTmp->szFrom == szClient) {

		/*	try {
				//send the connection confirmation to the client,add to the list - yh
				CComData ComDataTmp;
				ComDataTmp.szFrom	 = CString((LPCTSTR)IDS_COM_SERVER);
				ComDataTmp.uSignIcon = SERVER_ICON;
				ComDataTmp.szMessage = szMessage;
				ComDataTmp.uMessage  = CComData::COM_PRIVATE_MESSAGE;
				pClientSocketTmp->SendCom(&ComDataTmp);
			}
			catch(CFileException* e) {
				TCHAR csError[CHAR_BUFFER_SIZE];
				e->GetErrorMessage(csError, CHAR_BUFFER_SIZE);
				AfxMessageBox(csError);
			}
			*/

			return;
		}
	}
}

void CServerSocket::RedirectPrivateMessageTo(CComData* pComData)
{
	AfxMessageBox("RedirectPrivateMessageTo");

	CString szClient;
	szClient = pComData->szMessage.Mid(0, pComData->szMessage.Find(':'));  

	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {

		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);

		if (pComDataTmp->szFrom == szClient) {

			try {
				//send the connection confirmation to the client,add to the list - yh
				CComData ComDataTmp;
				ComDataTmp.szFrom	 = pComData->szFrom;
				ComDataTmp.uSignIcon = pComData->uSignIcon;
				ComDataTmp.szMessage = pComData->szMessage.Mid(pComData->szMessage.Find(':') + 2);
				ComDataTmp.uMessage  = CComData::COM_PRIVATE_MESSAGE;
				pClientSocketTmp->SendCom(&ComDataTmp);
			}
			catch(CFileException* e) {
				TCHAR csError[CHAR_BUFFER_SIZE];
				e->GetErrorMessage(csError, CHAR_BUFFER_SIZE);
				AfxMessageBox(csError);
			}

			return;
		}
	}
}





void CServerSocket::KickUser(CString szClient)
{
	AfxMessageBox("KickUser");	

	int nCount = m_ClientstList.GetCount();
	for (int i = 0; i < nCount; i++) {

		sClientComInfos* pClientCom = (sClientComInfos*)m_ClientstList.GetAt(m_ClientstList.FindIndex(i));
		ASSERT(pClientCom);
		CComData* pComDataTmp = (CComData*)&pClientCom->ComData;
		ASSERT(pComDataTmp);
		CClientSocket* pClientSocketTmp = (CClientSocket*)pComDataTmp->pSocket;
		ASSERT(pClientSocketTmp);

		if (pComDataTmp->szFrom == szClient) {

			m_ClientstList.RemoveAt(m_ClientstList.FindIndex(i));

		/*	try {
				//send the connection confirmation to the client,add to the list - yh
				CComData ComDataTmp;
				ComDataTmp.szFrom	 = CString((LPCTSTR)IDS_COM_SERVER);
				ComDataTmp.uSignIcon = SERVER_ICON;
				ComDataTmp.szMessage = CString((LPCTSTR)IDS_COM_CLOSE);
				ComDataTmp.uMessage  = CComData::COM_CLOSE;
				pClientSocketTmp->SendCom(&ComDataTmp);
			}
			catch(CFileException* e) {
				TCHAR csError[CHAR_BUFFER_SIZE];
				e->GetErrorMessage(csError, CHAR_BUFFER_SIZE);
				AfxMessageBox(csError);
			}
  */
			pClientSocketTmp->Close();
			delete pClientSocketTmp;
			pClientSocketTmp = NULL;
			CString szBuf;
			szBuf.Format("%s: %s", pComDataTmp->szFrom, CString("Connection closed by server.")); 
		/*	m_pMainFrame->AddServerCom(CTime::GetCurrentTime(),
										CString((LPCTSTR)IDS_COM_SERVER),
										SERVER_ICON,
										szBuf);	
			pClientCom->szMessagesList.RemoveAll();  
		*/
			delete pClientCom;
			pClientCom = NULL;

			//UpdateClientsList();
			RemoveFromClientsList(szClient);
			Sleep(10);

			CComData ComDataTmp;
		/*	szBuf.Format(IDS_COM_CLIENT_KICKED, szClient);
			ComDataTmp.szFrom	 = CString((LPCTSTR)IDS_COM_SERVER);
			ComDataTmp.uSignIcon = SERVER_ICON;
			ComDataTmp.szMessage = szBuf;
			ComDataTmp.uMessage  = CComData::COM_MESSAGE;
			UpdateClientsInfo(CTime::GetCurrentTime(), &ComDataTmp, NULL);
			*/

			return;
		}
	}
}


