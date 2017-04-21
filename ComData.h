#ifndef _COMDATA_H
#define _COMDATA_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define CHAR_BUFFER_SIZE 255


/////////////////////////////////////////////////////////////////////////////
// CComData

class CComData : public CObject
{
protected:
	DECLARE_DYNCREATE(CComData)

// Enumerator
public:
	enum eComData {
		NONE = 0,
		COM_SIGN_IN,
		COM_SIGN_OUT,
		COM_MESSAGE,
		COM_CLOSE,
		COM_ADD_CLIENT,
		COM_REMOVE_CLIENT,
		COM_PRIVATE_MESSAGE,
	};

// Attributes
public:
	CString szFrom;
	UINT	uSignIcon;
	CString szMessage;
	UINT	uMessage;
	CString szIPAddress;
	UINT	uPort;
	DWORD	pSocket;

// Operations
public:
	CComData(); 
	virtual ~CComData();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComData)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CComData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // _COMDATA_H

struct sClientComInfos {
	CComData ComData;
	CTime TimeStarted;
	CStringList szMessagesList;
};