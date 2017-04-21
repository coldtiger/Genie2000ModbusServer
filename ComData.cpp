// ComData.cpp : implementation file
//

#include "stdafx.h"
#include "ComData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComData

IMPLEMENT_DYNCREATE(CComData, CObject)

CComData::CComData()
{
	szFrom		= "";
	uSignIcon	= NONE;
	szMessage	= "";
	uMessage	= NONE;
	szIPAddress = "";
	uPort		= NONE;
	pSocket		= NONE;
}



CComData::~CComData()
{
}


/////////////////////////////////////////////////////////////////////////////
// CComData serialization

void CComData::Serialize(CArchive& ar)
{
	try {
		if (ar.IsStoring())
		{
			//ar << szFrom;		
		//	ar << uSignIcon;		
			ar << szMessage;	
		//	ar << uMessage;
		//	ar << szIPAddress; 
		//	ar << uPort;		
		//	ar << pSocket;		
		}
		else
		{
		//	ar >> szFrom;		
		//	ar >> uSignIcon;		
			ar >> szMessage;	
		//	ar >> uMessage;
		//	ar >> szIPAddress; 
		//	ar >> uPort;		
		//	ar >> pSocket;		
		}
	}
		catch(CArchiveException* e) {
		TCHAR csError[CHAR_BUFFER_SIZE];
		e->GetErrorMessage(csError, CHAR_BUFFER_SIZE);
		AfxMessageBox(csError);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CComData commands
