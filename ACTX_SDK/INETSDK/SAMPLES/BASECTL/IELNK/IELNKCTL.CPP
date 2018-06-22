//=--------------------------------------------------------------------------=
// ielnkCtl.Cpp
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
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

#include "Guids.H"
#include "ielnkCtl.H"
#include "LocalObj.H"
#include "Util.H"
#include "Globals.H"
#include "Resource.H"
#include "urlhlink.h"
//#include "hlinkez.H"
//#include "urlmon.h"

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
const GUID *rgielnkPropPages [] = {
    &CLSID_ielnkGeneralPage
};

//=--------------------------------------------------------------------------=
// Custum Verb information
//
// TODO: add any custom verbs here in an array, using the VERBINFO structure.
//       then mark the controld def'n in ielnkCtl.H with
//       this verb array
//


//=--------------------------------------------------------------------------=
// CielnkControl::Create
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
IUnknown *CielnkControl::Create
(
    IUnknown *pUnkOuter
)
{
    // make sure we return the private unknown so that we support aggegation
    // correctly!
    //
    CielnkControl *pNew = new CielnkControl(pUnkOuter);
    return pNew->PrivateUnknown();
}

//=--------------------------------------------------------------------------=
// CielnkControl::CielnkControl
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
CielnkControl::CielnkControl
(
    IUnknown *pUnkOuter
)
: COleControl(pUnkOuter, OBJECT_TYPE_CTLIELNK, (IDispatch *)this)
{
    // initialize anything here ...
    //
    memset(&m_state, 0, sizeof(IELNKCTLSTATE));
	m_state.m_hlink = new char[1];
	lstrcpy(m_state.m_hlink,"");
}
#pragma warning(default:4355)  // using 'this' in constructor

//=--------------------------------------------------------------------------=
// CielnkControl::~CielnkControl
//=--------------------------------------------------------------------------=
// "We all labour against our own cure, for death is the cure of all diseases"
//    - Sir Thomas Browne (1605 - 82)
//
// Notes:
//
CielnkControl::~CielnkControl ()
{
    // TODO: clean up anything here.
	if (m_state.m_hlink)
		delete [] m_state.m_hlink;

	if (m_state.m_location)
		delete [] m_state.m_location;

	if (m_state.m_targetframe)
		delete [] m_state.m_targetframe;

}

//=--------------------------------------------------------------------------=
// CielnkControl:RegisterClassData
//=--------------------------------------------------------------------------=
// register the window class information for your control here.
// this information will automatically get cleaned up for you on DLL shutdown.
//
// Output:
//    BOOL            - FALSE means fatal error.
//
// Notes:
//
BOOL CielnkControl::RegisterClassData
(
    void
)
{
    WNDCLASS wndclass;

    // TODO: register any additional information you find interesting here.
    //       this method is only called once for each type of control
    //
    memset(&wndclass, 0, sizeof(WNDCLASS));
    wndclass.style          = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
    wndclass.lpfnWndProc    = COleControl::ControlWindowProc;
    wndclass.hInstance      = g_hInstance;
    wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszClassName  = WNDCLASSNAMEOFCONTROL(OBJECT_TYPE_CTLIELNK);

    return RegisterClass(&wndclass);
}

//=--------------------------------------------------------------------------=
// CielnkControl::BeforeCreateWindow
//=--------------------------------------------------------------------------=
// called just before the window is created.  Great place to set up the
// window title, etc, so that they're passed in to the call to CreateWindowEx.
// speeds things up slightly.
//
// Parameters:
//    DWORD *            - [out] dwWindowFlags
//    DWORD *            - [out] dwExWindowFlags
//    LPSTR              - [out] name of window to create
//
// Output:
//    BOOL               - false means fatal error
//
// Notes:
//
BOOL CielnkControl::BeforeCreateWindow
(
    DWORD *pdwWindowStyle,
    DWORD *pdwExWindowStyle,
    LPSTR  pszWindowTitle
)
{
    // TODO: users should set the values of *pdwWindowStyle, *pdwExWindowStyle,
    // and pszWindowTitle so that the call to CreateWindowEx can use them. setting
    // them here instead of calling SetWindowStyle in WM_CREATE is a huge perf win
    // if you don't use this function, then you can probably just remove it.
    //
	return TRUE;
}



//=--------------------------------------------------------------------------=
// CielnkControl::AfterCreateWindow
//=--------------------------------------------------------------------------=
// called just after the window is created.

BOOL CielnkControl::AfterCreateWindow
(
)

{
	return TRUE;
}

//=--------------------------------------------------------------------------=
// CielnkControl::InternalQueryInterface
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
HRESULT CielnkControl::InternalQueryInterface
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
    if (DO_GUIDS_MATCH(riid, IID_Iielnk)) {
        pUnk = (IUnknown *)(Iielnk *)this;
    } else{
        return COleControl::InternalQueryInterface(riid, ppvObjOut);
    }

    pUnk->AddRef();
    *ppvObjOut = (void *)pUnk;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CielnkControl::LoadTextState
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
STDMETHODIMP CielnkControl::LoadTextState
(
    IPropertyBag *pPropertyBag,
    IErrorLog    *pErrorLog
)
{
	VARIANT v;
	HRESULT hr;

	VariantInit(&v);
	v.vt = VT_BSTR;
	v.bstrVal = ::SysAllocString(L"");
    hr = pPropertyBag->Read(L"Hlink", &v, pErrorLog);
	if (!FAILED(hr))
	{
		MAKE_ANSIPTR_FROMWIDE(tempVal, v.bstrVal);
		DWORD dw = lstrlen(tempVal);
		if (m_state.m_hlink)
			delete [] m_state.m_hlink;
		m_state.m_hlink = new char[dw + 1];

		if( !(m_state.m_hlink) )
		{
			FAIL("No memory");
			return(E_OUTOFMEMORY);
		}
		lstrcpy(m_state.m_hlink, tempVal);
	}

	VariantClear(&v);
	v.vt = VT_BSTR;
	v.bstrVal = ::SysAllocString(L"");
    hr = pPropertyBag->Read(L"Location", &v, pErrorLog);
	if (!FAILED(hr))
	{
		MAKE_ANSIPTR_FROMWIDE(tempVal, v.bstrVal);
		DWORD dw = lstrlen(tempVal);
		if (m_state.m_location)
			delete [] m_state.m_location;
		m_state.m_location = new char[dw + 1];

		if( !(m_state.m_location) )
		{
			FAIL("No memory");
			return(E_OUTOFMEMORY);
		}
		lstrcpy(m_state.m_location, tempVal);
	}

	VariantClear(&v);
	v.vt = VT_BSTR;
	v.bstrVal = ::SysAllocString(L"");
    hr = pPropertyBag->Read(L"TargetFrame", &v, pErrorLog);
	if (!FAILED(hr))
	{
		MAKE_ANSIPTR_FROMWIDE(tempVal, v.bstrVal);
		DWORD dw = lstrlen(tempVal);
		if (m_state.m_targetframe)
			delete [] m_state.m_targetframe;
		m_state.m_targetframe = new char[dw + 1];

		if( !(m_state.m_targetframe) )
		{
			FAIL("No memory");
			return(E_OUTOFMEMORY);
		}
		lstrcpy(m_state.m_targetframe, tempVal);
	}

	VariantClear(&v);
	v.vt = VT_I4;
	hr = pPropertyBag->Read(L"Flags",&v,pErrorLog);
	if (SUCCEEDED(hr))
		m_state.m_flags = v.lVal;

    return S_OK;
}


#define		STREAMHDR_MAGIC		98898
//=--------------------------------------------------------------------------=
// CielnkControl::LoadBinaryState
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
STDMETHODIMP CielnkControl::LoadBinaryState
(
    IStream *pStream
)
{
    HRESULT hr;
	DWORD sh = STREAMHDR_MAGIC;
	DWORD	dw;

	hr = pStream->Read(&sh, sizeof(sh), NULL);
    RETURN_ON_FAILURE(hr);

    if (sh != STREAMHDR_MAGIC )
		return E_UNEXPECTED;

	hr = pStream->Read(&(m_state.m_flags),sizeof(m_state.m_flags),NULL);

	if( m_state.m_hlink )
		delete [] m_state.m_hlink;
	hr = pStream->Read(&dw,sizeof(dw),0);
	if( SUCCEEDED(hr) )
	{
		if( !dw )
			m_state.m_hlink = 0;
		else
		{
			m_state.m_hlink = new char[dw+1];
			if( m_state.m_hlink )
				hr = pStream->Read(m_state.m_hlink,dw+1,0);
		}
	}

	if( m_state.m_location )
		delete [] m_state.m_location;
	hr = pStream->Read(&dw,sizeof(dw),0);
	if( SUCCEEDED(hr) )
	{
		if( !dw )
			m_state.m_location = 0;
		else
		{
			m_state.m_location = new char[dw+1];
			if( m_state.m_location )
				hr = pStream->Read(m_state.m_location,dw+1,0);
		}
	}

	if( m_state.m_targetframe )
		delete []  m_state.m_targetframe;
	hr = pStream->Read(&dw,sizeof(dw),0);
	if( SUCCEEDED(hr) )
	{
		if( !dw )
			m_state.m_targetframe = 0;
		else
		{
			m_state.m_targetframe = new char[dw+1];
			if( m_state.m_targetframe )
				hr = pStream->Read(m_state.m_targetframe,dw+1,0);
		}
	}
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CielnkControl::SaveTextState
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
STDMETHODIMP CielnkControl::SaveTextState
(
    IPropertyBag *pPropertyBag,
    BOOL          fWriteDefaults
)
{
	VARIANT v;
	HRESULT hr;

	VariantInit(&v);
	v.vt = VT_BSTR;
    v.bstrVal = BSTRFROMANSI(m_state.m_hlink);
    RETURN_ON_NULLALLOC(v.bstrVal);
    hr = pPropertyBag->Write(L"Hlink", &v);
    VariantClear(&v); 

	VariantInit(&v);
	v.vt = VT_BSTR;
    v.bstrVal = BSTRFROMANSI(m_state.m_location);
    RETURN_ON_NULLALLOC(v.bstrVal);
    hr = pPropertyBag->Write(L"Location", &v);
    VariantClear(&v); 

	
	VariantInit(&v);
	v.vt = VT_BSTR;
    v.bstrVal = BSTRFROMANSI(m_state.m_targetframe);
    RETURN_ON_NULLALLOC(v.bstrVal);
    hr = pPropertyBag->Write(L"TargetFrame", &v);
    VariantClear(&v); 

	v.vt = VT_I4;
    v.lVal = m_state.m_flags;
    hr = pPropertyBag->Write(L"Flags", &v);

    return S_OK;
}

//=--------------------------------------------------------------------------=
// CielnkControl::SaveBinaryState
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
STDMETHODIMP CielnkControl::SaveBinaryState
(
    IStream *pStream
)
{
    HRESULT hr;
	DWORD sh = STREAMHDR_MAGIC;    
	DWORD dw;
	// write out the stream hdr.
    //
    hr = pStream->Write(&sh, sizeof(sh), NULL);
    RETURN_ON_FAILURE(hr);

    // write out he control state information
    //
	hr = pStream->Write(&(m_state.m_flags),sizeof(m_state.m_flags),NULL);

	dw = m_state.m_hlink? lstrlen(m_state.m_hlink) : 0;
	hr = pStream->Write(&dw,sizeof(dw),0);
	RETURN_ON_FAILURE(hr);
	if( dw )
		hr = pStream->Write(m_state.m_hlink,dw+1,0);    

	dw = m_state.m_location? lstrlen(m_state.m_location) : 0;
	hr = pStream->Write(&dw,sizeof(dw),0);
	RETURN_ON_FAILURE(hr);
	if( dw )
		hr = pStream->Write(m_state.m_location,dw+1,0);    

	
	dw = m_state.m_targetframe? lstrlen(m_state.m_targetframe) : 0;
	hr = pStream->Write(&dw,sizeof(dw),0);
	RETURN_ON_FAILURE(hr);
	if( dw )
		hr = pStream->Write(m_state.m_targetframe,dw+1,0);    

	return S_OK;
}


//=--------------------------------------------------------------------------=
// CielnkControl::OnDraw
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
HRESULT CielnkControl::OnDraw
(
    DWORD    dvAspect,
    HDC      hdcDraw,
    LPCRECTL prcBounds,
    LPCRECTL prcWBounds,
    HDC      hicTargetDevice,
    BOOL     fOptimize
)
{
    // TODO: put your drawing code here ...
    //
	SetBkMode(hdcDraw, TRANSPARENT);
	SetTextColor(hdcDraw,RGB(0, 0, 255));
	RECT rc;
	rc.left = prcBounds->left;
	rc.top = prcBounds->top;
	rc.right = prcBounds->right;
	rc.bottom = prcBounds->bottom;

	DrawText(hdcDraw,m_state.m_hlink,lstrlen(m_state.m_hlink),
		&rc,DT_CENTER | DT_VCENTER);
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CielnkControl::WindowProc
//=--------------------------------------------------------------------------=
// window procedure for this control.  nothing terribly exciting.
//
// Parameters:
//     see win32sdk on window procs [sans HWND -- it's in m_hwnd if you have one]
//
// Notes:
//
LRESULT CielnkControl::WindowProc
(
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam
)
{
    // TODO: handle any messages here, like in a normal window
    // proc.  note that for special keys, you'll want to override and
    // implement OnSpecialKey.
    // if you're a windowed OCX, you should be able to use any of the
    // win32 API routines except for SetFocus.  you should always use
    // OcxSetFocus()
    //
	/*
	switch (msg)
	{
		case WM_LBUTTONDOWN :
			Go();
			break;
		case WM_RBUTTONDOWN :
			if (MK_SHIFT & wParam)
				Back();
			else
				Forward();
			break;
	}
	*/
    return OcxDefWindowProc(msg, wParam, lParam);
}

//=--------------------------------------------------------------------------=
// CielnkControl::AboutBox
//=--------------------------------------------------------------------------=
// prints up an about box.  fweeeee.
//
// Notes:
//
void CielnkControl::AboutBox
(
    void
)
{
    ModalDialog(TRUE);
    MessageBox(NULL, "This is ielnk", "About ielnk- v 1.0.0", MB_OK | MB_TASKMODAL);
    ModalDialog(FALSE);
}

void CielnkControl::Forward
(
    void
)
{
    HlinkGoForward(m_pUnkOuter);
}

void CielnkControl::Back
(
    void
)
{
    HlinkGoBack(m_pUnkOuter);
}


void CielnkControl::Go
(
    void
)
{
	switch (m_state.m_mode)
	{
	case 0 :
		HlinkSimpleNavigateToString(
			(m_state.m_hlink == NULL) ? NULL : BSTRFROMANSI(m_state.m_hlink),
			(m_state.m_location == NULL) ? NULL :BSTRFROMANSI(m_state.m_location) ,
			(m_state.m_targetframe == NULL) ? NULL :BSTRFROMANSI(m_state.m_targetframe) ,
			m_pUnkOuter,
			NULL,
			NULL,
			m_state.m_flags,
			0);
	break;
	case 1 :
		HlinkSimpleNavigateToString(
			(m_state.m_hlink == NULL) ? NULL : BSTRFROMANSI(m_state.m_hlink),
			(m_state.m_location == NULL) ? NULL :BSTRFROMANSI(m_state.m_location) ,
			(m_state.m_targetframe == NULL) ? NULL :BSTRFROMANSI(m_state.m_targetframe) ,
			NULL, 
			NULL,
			NULL,
			m_state.m_flags,
			0);
	break;
	case 2 :
		HlinkNavigateString(
			m_pUnkOuter,
			(m_state.m_hlink == NULL) ? NULL : BSTRFROMANSI(m_state.m_hlink));
	break;
	case 3 :
		HlinkNavigateString(
			NULL,
			(m_state.m_hlink == NULL) ? NULL : BSTRFROMANSI(m_state.m_hlink));
	break;
	case 4 :
	{
		IMoniker *pmTarget;
		::CreateURLMoniker(
			0,
			(m_state.m_hlink == NULL) ? NULL : BSTRFROMANSI(m_state.m_hlink),
			&pmTarget);

		HlinkSimpleNavigateToMoniker(
			pmTarget,
			(m_state.m_location == NULL) ? NULL :BSTRFROMANSI(m_state.m_location) ,
			(m_state.m_targetframe == NULL) ? NULL :BSTRFROMANSI(m_state.m_targetframe) ,
			m_pUnkOuter, 
			NULL,
			NULL,
			m_state.m_flags,
			0);
	
	}
	break;
	case 5 :
	{
		IMoniker *pmTarget;
		::CreateURLMoniker(
			0,
			(m_state.m_hlink == NULL) ? NULL : BSTRFROMANSI(m_state.m_hlink),
			&pmTarget);

		HlinkSimpleNavigateToMoniker(
			pmTarget,
			(m_state.m_location == NULL) ? NULL :BSTRFROMANSI(m_state.m_location) ,
			(m_state.m_targetframe == NULL) ? NULL :BSTRFROMANSI(m_state.m_targetframe) ,
			NULL, 
			NULL,
			NULL,
			m_state.m_flags,
			0);
	
	}
	break;
	case 6 :
	{
		IMoniker *pmTarget;
		::CreateURLMoniker(
			0,
			(m_state.m_hlink == NULL) ? NULL : BSTRFROMANSI(m_state.m_hlink),
			&pmTarget);

		HlinkNavigateMoniker(
			m_pUnkOuter,
			pmTarget);

	}
	break;
	case 7 :
	{
		IMoniker *pmTarget;
		::CreateURLMoniker(
			0,
			(m_state.m_hlink == NULL) ? NULL : BSTRFROMANSI(m_state.m_hlink),
			&pmTarget);

		HlinkNavigateMoniker(
			NULL,
			pmTarget);

	}
	}
}


STDMETHODIMP  CielnkControl::get_Hlink(BSTR * val)
{
	CHECK_POINTER(val);

	BSTR * tempVal = val;
    
    *tempVal = m_state.m_hlink && *(m_state.m_hlink) ? BSTRFROMANSI(m_state.m_hlink) : SysAllocString(L"");
    return (*tempVal) ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP  CielnkControl::put_Hlink(BSTR val)
{
    MAKE_ANSIPTR_FROMWIDE(tempVal, val);

	DWORD dw = lstrlen(tempVal);
	if (m_state.m_hlink)
		m_state.m_hlink = new char[dw + 1];

	if( !(m_state.m_hlink) )
	{
		FAIL("No memory");
		return(E_OUTOFMEMORY);
	}

	lstrcpy(m_state.m_hlink, tempVal);

	PropertyChanged(DISPID_HLINK);
	if (*(m_state.m_hlink))
	{
		InvalidateControl(NULL);
	}
	m_fDirty = TRUE;
    return S_OK;
}

STDMETHODIMP  CielnkControl::get_Location(BSTR * val)
{
	CHECK_POINTER(val);

	BSTR * tempVal = val;
    
    *tempVal = m_state.m_location && *(m_state.m_location) ? BSTRFROMANSI(m_state.m_location) : SysAllocString(L"");
    return (*tempVal) ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP  CielnkControl::put_Location(BSTR val)
{
    MAKE_ANSIPTR_FROMWIDE(tempVal, val);

	DWORD dw = lstrlen(tempVal);
	if (m_state.m_location)
		delete [] m_state.m_location;
	m_state.m_location= new char[dw + 1];

	if( !(m_state.m_location) )
	{
		FAIL("No memory");
		return(E_OUTOFMEMORY);
	}

	lstrcpy(m_state.m_location, tempVal);

	PropertyChanged(DISPID_LOCATION);
	if (*(m_state.m_location))
	{

	}
	m_fDirty = TRUE;
    return S_OK;
}

STDMETHODIMP  CielnkControl::get_TargetFrame(BSTR * val)
{
	CHECK_POINTER(val);

	BSTR * tempVal = val;
    
    *tempVal = m_state.m_targetframe && *(m_state.m_targetframe) ? 
		BSTRFROMANSI(m_state.m_targetframe) : SysAllocString(L"");
    return (*tempVal) ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP  CielnkControl::put_TargetFrame(BSTR val)
{
    MAKE_ANSIPTR_FROMWIDE(tempVal, val);

	DWORD dw = lstrlen(tempVal);
	if (m_state.m_targetframe)
		delete [] m_state.m_targetframe;
	m_state.m_targetframe= new char[dw + 1];

	if( !(m_state.m_targetframe) )
	{
		FAIL("No memory");
		return(E_OUTOFMEMORY);
	}

	lstrcpy(m_state.m_targetframe, tempVal);

	PropertyChanged(DISPID_TARGETFRAME);
	if (*(m_state.m_targetframe))
	{

	}
	m_fDirty = TRUE;
    return S_OK;
}

STDMETHODIMP  CielnkControl::get_Flags(long * val)
{
	CHECK_POINTER(val);

	*val = m_state.m_flags;
    
    return S_OK;
}

STDMETHODIMP  CielnkControl::put_Flags(long val)
{
	m_state.m_flags = val;
	PropertyChanged(DISPID_FLAGS);
	m_fDirty = TRUE;
    return S_OK;
}


STDMETHODIMP  CielnkControl::get_Mode(long * val)
{
	CHECK_POINTER(val);

	*val = m_state.m_mode;
    
    return S_OK;
}

STDMETHODIMP  CielnkControl::put_Mode(long val)
{
	m_state.m_mode = val;
	PropertyChanged(DISPID_MODE);
	m_fDirty = TRUE;
    return S_OK;
}


STDMETHODIMP CielnkControl::SetObjectRects(LPCRECT prcPos, LPCRECT prcClip)
{
	// Take the hint and size ourselves
	m_Size.cx = prcPos->right - prcPos->left;
	m_Size.cy = prcPos->bottom - prcPos->top;

	// Let the framework do its thing
	return COleControl::SetObjectRects(prcPos, prcClip);
}
