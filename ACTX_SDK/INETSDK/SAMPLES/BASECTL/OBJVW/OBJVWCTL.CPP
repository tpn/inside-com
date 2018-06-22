//=--------------------------------------------------------------------------=
// ObjVwCtl.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
//
//
#include "IPServer.H"

#include "LocalObj.H"
#include "Util.H"
#include "Globals.H"
#include "Resource.H"
#include "ObjVwctl.H"
#include "appsink.h"

// for ASSERT and FAIL
//
SZTHISFILE




//=--------------------------------------------------------------------------=
// all the events in this control
//
// TODO: add events here ...
//

//=--------------------------------------------------------------------------=
// array describing all of our property pages.  these clsids are typically
// in guids.h
//
// TODO: add any additional property page guids here ...
//

//=--------------------------------------------------------------------------=
// Custum Verb information
//
// TODO: add any custom verbs here in an array, using the VERBINFO structure.
//       then mark the controld def'n in LinkTCtl.H with
//       this verb array
//


//=--------------------------------------------------------------------------=
// CObjVwControl::Create
//=--------------------------------------------------------------------------=
// global static function that creates an instance of the control an returns
// an IUnknown pointer for it.
//
// Parameters:
//    IUnknown *        - [in] controlling unknown for aggregation
//
// Output:
//    IUnknown *        - new object.
//
// Notes:
//
IUnknown *CObjVwControl::Create
(
    IUnknown *pUnkOuter
)
{
    // make sure we return the private unknown so that we support aggegation
    // correctly!
    //
    CObjVwControl *pNew = new CObjVwControl(pUnkOuter);
    return pNew->PrivateUnknown();
}

//=--------------------------------------------------------------------------=
// CObjVwControl::CObjVwControl
//=--------------------------------------------------------------------------=
// "Being born is like being kidnapped.  And then sold into slavery."
//    - andy warhol (1928 - 87)
//
// Parameters:
//    IUnknown *        - [in]
//
// Notes:
//
#pragma warning(disable:4355)  // using 'this' in constructor
CObjVwControl::CObjVwControl
(
    IUnknown *pUnkOuter
)
: COleControl(pUnkOuter, OBJECT_TYPE_CTLOBJVW, (IDispatch *)this)
{
	m_pAppSink = NULL;
	m_pTreeUI = NULL;
	m_pWinTree = NULL;
}
#pragma warning(default:4355)  // using 'this' in constructor

//=--------------------------------------------------------------------------=
// CObjVwControl::~CObjVwControl
//=--------------------------------------------------------------------------=
// "We all labour against our own cure, for death is the cure of all diseases"
//    - Sir Thomas Browne (1605 - 82)
//
// Notes:
//
CObjVwControl::~CObjVwControl ()
{
	KillPtr(m_pWinTree);
	KillPtr(m_pTreeUI);

	if ( m_pAppSink )
	{
		m_pAppSink->DisconnectEvents();
		m_pAppSink = NULL;
	}

    // delete the window tree
    KillPtr(m_pWinTree);

    // Delete the ui object
    KillPtr(m_pTreeUI);
}

//=--------------------------------------------------------------------------=
// CObjVwControl:RegisterClassData
//=--------------------------------------------------------------------------=
// register the window class information for your control here.
// this information will automatically get cleaned up for you on DLL shutdown.
//
// Output:
//    BOOL            - FALSE means fatal error.
//
// Notes:
//
BOOL CObjVwControl::RegisterClassData()
{
    WNDCLASS wndclass;

    // TODO: register any additional information you find interesting here.
    //       this method is only called once for each type of control
    //

    memset(&wndclass, 0, sizeof(WNDCLASS));
    wndclass.style          = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_OWNDC;
    wndclass.lpfnWndProc    = COleControl::ControlWindowProc;
    wndclass.hInstance      = g_hInstance;
    wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszClassName  = WNDCLASSNAMEOFCONTROL(OBJECT_TYPE_CTLOBJVW);

    return RegisterClass(&wndclass);
}

//=--------------------------------------------------------------------------=
// CObjVwControl::BeforeCreateWindow
//=--------------------------------------------------------------------------=
// called just before the window is created.  Great place to set up the
// window title, etc, so that they're passed in to the call to CreateWindowEx.
// speeds things up slightly.
//
// Notes:
//
void CObjVwControl::BeforeCreateWindow()
{
}

BOOL CObjVwControl::AfterCreateWindow()
{
	RECT			rc;
	HRESULT			hr = NOERROR;
	LPOLECLIENTSITE	pClientSite;

	// Get client coordinates of our control window
	GetClientRect(m_hwnd, &rc);

	// Initialize the tree UI
	m_pTreeUI = new CTreeUI;
	IfMemFailHRGoto(m_pTreeUI);
	IfComFailGoto(m_pTreeUI->Create(&rc, m_hwnd, g_hInstance));

	// Initialize window tree
	m_pWinTree = new CWinTree;
	IfMemFailHRGoto(m_pWinTree);

	// Create and initialize the window event sink
	m_pAppSink = new CAppSink;
	IfMemFailHRGoto(m_pAppSink);
	GetClientSite(&pClientSite);
	ASSERT(pClientSite, "Must have valid client site pointer");
	IfComFailGoto(m_pAppSink->Create(
		pClientSite, m_pTreeUI, m_pWinTree));

done:
	if ( FAILED(hr) )
		return FALSE;
	return TRUE;
}

//=--------------------------------------------------------------------------=
// CObjVwControl::InternalQueryInterface
//=--------------------------------------------------------------------------=
// qi for things only we support.
//
// Parameters:
// Parameters:
//    REFIID        - [in]  interface they want
//    void **       - [out] where they want to put the resulting object ptr.
//
// Output:
//    HRESULT       - S_OK, E_NOINTERFACE
//
// Notes:
//
HRESULT CObjVwControl::InternalQueryInterface
(
    REFIID  riid,
    void  **ppvObjOut
)
{
    IUnknown *pUnk;

    *ppvObjOut = NULL;

    // TODO: if you want to support any additional interrfaces, then you should
    // indicate that here.  never forget to call COleControl's version in the
    // case where you don't support the given interface.
    //
    if (DO_GUIDS_MATCH(riid, IID_IObjVw)) {
        pUnk = (IUnknown *)(IObjVw *)this;
    } else{
        return COleControl::InternalQueryInterface(riid, ppvObjOut);
    }

    pUnk->AddRef();
    *ppvObjOut = (void *)pUnk;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CObjVwControl::LoadTextState
//=--------------------------------------------------------------------------=
// load in our text state for this control.
//
// Parameters:
//    IPropertyBag *        - [in] property bag to read from
//    IErrorLog *           - [in] errorlog object to use with proeprty bag
//
// Output:
//    HRESULT
//
// Notes:
//    - NOTE: if you have a binary object, then you should pass an unknown
//      pointer to the property bag, and it will QI it for IPersistStream, and
//      get said object to do a Load()
//
STDMETHODIMP CObjVwControl::LoadTextState
(
    IPropertyBag *pPropertyBag,
    IErrorLog    *pErrorLog
)
{
	HRESULT	hr = NOERROR;

    return hr;
}

//=--------------------------------------------------------------------------=
// CObjVwControl::LoadBinaryState
//=--------------------------------------------------------------------------=
// loads in our binary state using streams.
//
// Parameters:
//    IStream *            - [in] stream to write to.
//
// Output:
//    HRESULT
//
// Notes:
//

STDMETHODIMP CObjVwControl::LoadBinaryState
(
    IStream *pStream
)
{
	HRESULT	hr = NOERROR;

	return hr;
}

//=--------------------------------------------------------------------------=
// CObjVwControl::SaveTextState
//=--------------------------------------------------------------------------=
// saves out the text state for this control using a property bag.
//
// Parameters:
//    IPropertyBag *        - [in] the property bag with which to work.
//    BOOL                  - [in] if TRUE, then write out ALL properties, even
//                            if they're their the default value ...
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CObjVwControl::SaveTextState
(
    IPropertyBag *pPropertyBag,
    BOOL          fWriteDefaults
)
{
	HRESULT	hr = NOERROR;

	return hr;
}

//=--------------------------------------------------------------------------=
// CObjVwControl::SaveBinaryState
//=--------------------------------------------------------------------------=
// save out the binary state for this control, using the given IStream object.
//
// Parameters:
//    IStream  *             - [in] save to which you should save.
//
// Output:
//    HRESULT
//
// Notes:
//    - it is important that you seek to the end of where you saved your
//      properties when you're done with the IStream.
//
STDMETHODIMP CObjVwControl::SaveBinaryState
(
    IStream *pStream
)
{
	HRESULT	hr = NOERROR;

	return hr;
}


//=--------------------------------------------------------------------------=
// CObjVwControl::OnDraw
//=--------------------------------------------------------------------------=
// "I don't very much enjoy looking at paintings in general.  i know too
//  much about them.  i take them apart."
//    - georgia o'keeffe (1887-1986)
//
// Parameters:
//    DWORD              - [in]  drawing aspect
//    HDC                - [in]  HDC to draw to
//    LPCRECTL           - [in]  rect we're drawing to
//    LPCRECTL           - [in]  window extent and origin for meta-files
//    HDC                - [in]  HIC for target device
//    BOOL               - [in]  can we optimize dc handling?
//
// Output:
//    HRESULT
//
// Notes:
//
HRESULT CObjVwControl::OnDraw
(
    DWORD    dvAspect,
    HDC      hdcDraw,
    LPCRECTL prcBounds,
    LPCRECTL prcWBounds,
    HDC      hicTargetDevice,
    BOOL     fOptimize
)
{
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CObjVwControl::WindowProc
//=--------------------------------------------------------------------------=
// window procedure for this control.  nothing terribly exciting.
//
// Parameters:
//     see win32sdk on window procs.
//
// Notes:
//
LRESULT CObjVwControl::WindowProc
(
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam
)
{
    // TODO: handle any messages here, like in a normal window
    // proc.  note that for special keys, you'll want to override and
    // implement OnSpecialKey.
    //
	switch( msg )
	{
	case WM_ERASEBKGND:
		// This is needed for transparency and the correct drawing...
		HWND    hWndParent;       // handle of our parent window
		POINT   pt;

		hWndParent = GetParent(m_hwnd);
		pt.x       = 0;
		pt.y       = 0;

		MapWindowPoints(m_hwnd, hWndParent, &pt, 1);
		OffsetWindowOrgEx((HDC)wParam, pt.x, pt.y, &pt);
		SendMessage(hWndParent, msg, wParam, lParam);
		SetWindowOrgEx((HDC)wParam, pt.x, pt.y, NULL);
		return FALSE;
		break;
	}
    return OcxDefWindowProc(msg, wParam, lParam);
}

//=--------------------------------------------------------------------------=
// CObjVwControl::AboutBox
//=--------------------------------------------------------------------------=
// prints up an about box.  fweeeee.
//
// Notes:
//
void CObjVwControl::AboutBox
(
    void
)
{
    // TODO: Ideally, one would use DialogBox, and some sort of Dialog Box here if
    // they wanted a slightly more interesting About Box ...  you should
    // still call ModalDialog first, however.
    //
    ModalDialog(TRUE);
    MessageBox(NULL, "This is My Control", "About ObjVw", MB_OK | MB_TASKMODAL);
    ModalDialog(FALSE);
}


