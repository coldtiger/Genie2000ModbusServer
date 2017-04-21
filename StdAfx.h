/*
* ==========================================================================
* Name:         Stdafx.h : Include file  that includes just the standard includes
* Project:      Example
* Purpose:      List of standard system include files, or project specific include
*				files that are used frequently, but are changed infrequently
*
* Notes:
* Copyright (c) 2002 Canberra Inc, All Right Reserved
*
* Edits:        12/26/01          Created
* ==========================================================================
*/

#if !defined(AFX_STDAFX_H__D2B5082A_7A5F_4120_9E09_353AD156EE27__INCLUDED_)
#define AFX_STDAFX_H__D2B5082A_7A5F_4120_9E09_353AD156EE27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.h>

#include <afxsock.h>		// MFC socket extensions

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D2B5082A_7A5F_4120_9E09_353AD156EE27__INCLUDED_)
