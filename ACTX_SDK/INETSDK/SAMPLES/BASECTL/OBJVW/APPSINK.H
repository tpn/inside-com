//=--------------------------------------------------------------------------=
// AppSink.h
//=--------------------------------------------------------------------------=
// Copyright 1995-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// Definitions for app event sink class
//

#ifndef APPSINK_H

#include "exdisp.h"
#include "evtsink.h"
#include "treeui.h"
#include "wintree.h"

class CAppSink : public CEvtSink
{
public:
	CAppSink();
	virtual ~CAppSink();

	virtual HRESULT Create(LPOLECLIENTSITE, CTreeUI*, CWinTree*);

	static HRESULT ProgressChange(LPVOID, VARIANTARG*, UINT);
	static HRESULT DownloadComplete(LPVOID, VARIANTARG*, UINT) {return NOERROR;}

public:
	// pointer to object tree class, the control worries about freeing this
	// so we don't have to here
	CTreeUI*		m_pObjTree;

	// Pointer to top level scripting object (window)
	IWebBrowserApp*	m_pIWebBrowserApp;

	// pointer to the win tree class we don't have to worry about this
	CWinTree*		m_pWinTree;
};
#define APPSINK_H
#endif