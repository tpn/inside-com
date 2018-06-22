//=--------------------------------------------------------------------------=
// AppSink.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// Provides event sink implementation for application events
//

#include "ipserver.h"
#include "objvwctl.h"
#include "appsink.h"
#include "exdisp.h"
#include "docobj.h"
#include "gen.h"
#include "treeui.h"


SZTHISFILE


//=--------------------------------------------------------------------------=
// CAppSink::CAppSink
//=--------------------------------------------------------------------------=
// Constructor
//
// Parameters:
//
// Output:
//
// Notes:
//
CAppSink::CAppSink()
{
	m_pIWebBrowserApp = NULL;
	m_pWinTree = NULL;
	m_pObjTree = NULL;
}


//=--------------------------------------------------------------------------=
// CAppSink::~CAppSink
//=--------------------------------------------------------------------------=
// Destructor
//
// Parameters:
//
// Output:
//
// Notes:
//
CAppSink::~CAppSink()
{
	ReleaseInterface(m_pIWebBrowserApp);
}


//=--------------------------------------------------------------------------=
// CAppSink::Create
//=--------------------------------------------------------------------------=
// One time control initialization
//
// Parameters:
//		LPOLECLIENTSITE pClientSite	-	[in] control's client site pointer for
//										navigation in the Automation space
//		CObjTree* pObjTree			-	[in] pointer to  object tree class	
//		WinTree* pWinTree			-	[in] pointer to wintree class
//
// Output:
//		HRESULT 
//
// Notes:
//
HRESULT CAppSink::Create
(
	LPOLECLIENTSITE	pClientSite,
	CTreeUI*		pObjTree,
	CWinTree*		pWinTree
)
{
	HRESULT				hr = NOERROR;
	IServiceProvider*	pISP = NULL;
	IWebBrowserApp*		pIWebBrowserApp = NULL;
	LPUNKNOWN			punk = NULL;

	ASSERT(pClientSite, "Must have non NULL client site");
	ASSERT(pObjTree, "Must have non NULL object tree class pointer");
	ASSERT(pWinTree, "Must have non NULL window tree class pointer");

	// Save off pointer to object tree class
	m_pObjTree = pObjTree;
	m_pWinTree = pWinTree;

	// Get the IOmWindow interface from the container
	IfComFailRet(pClientSite->QueryInterface(
		IID_IServiceProvider,(void **)&pISP));
	IfComFailGoto(pISP->QueryService(IID_IWebBrowserApp, IID_IWebBrowserApp, 
		(void **)&pIWebBrowserApp));
	IfComFailGoto(pIWebBrowserApp->QueryInterface(IID_IUnknown, (void **)&punk));

	// Sink that interface's onLoad 
	IfComFailGoto(CEvtSink::Create(DIID_DWebBrowserEvents, punk));
	IfComFailGoto(MapEvent("ProgressChange", ProgressChange, (LPVOID)this));
	IfComFailGoto(ConnectEvents());

	// save off webbrowser app interface
	m_pIWebBrowserApp = pIWebBrowserApp;

done:
	if ( punk )
		ReleaseInterface(punk);

	if ( pISP )
		ReleaseInterface(pISP);

	return hr;
}


//=--------------------------------------------------------------------------=
// CAppSink::ProgressChange
//=--------------------------------------------------------------------------=
// The webbrowser download complete event
//
// Parameters:
//		LPVOID pvData			-	[in] data for the handler it is actually the pointer
//									to our class instance		
//		VARIANTARG* rgvtArgs	-	[in/out] arguments, byval arguments can change
//		UINT cArgs				-	[in] count of arguments
//
// Output:
//		HRESULT NOERROR, DISP_E_TYPEMISMATCH
//
// Notes:
//		We don't have to worry about cleaning things up here because it is taken
//		care of by th event sinking code after this function is called
//
HRESULT CAppSink::ProgressChange
(
	LPVOID		pvData,
	VARIANTARG*	rgvtArgs,
	UINT		cArgs
)
{
	HRESULT				hr = NOERROR;
	CAppSink*			pAppSink = (CAppSink*)pvData;

	// Check the numer of arguments and our class pointer
    ASSERT(2 == cArgs, "Bad number of arguments in event");
	ASSERT(pAppSink, "Bad app sink class pointer value");

	// Build tree if ready
    if ( -1 == V_I4(&rgvtArgs[1]) )
    {
        // if there is a tree already, delete it
        if ( pAppSink->m_pWinTree->AlreadyCreated() )
        {
            pAppSink->m_pWinTree->Reset();
        }
		IfComFailGoto(pAppSink->m_pWinTree->BuildTree(
			pAppSink->m_pIWebBrowserApp, pAppSink->m_pObjTree));
    }

done:
	return hr;
}
