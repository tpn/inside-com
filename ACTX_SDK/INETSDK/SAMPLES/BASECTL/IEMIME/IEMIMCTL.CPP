//=--------------------------------------------------------------------------=
// iemimCtl.Cpp
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
#include "iemimCtl.H"
#include "LocalObj.H"
#include "Util.H"
#include "Globals.H"
#include "Resource.H"

// for ASSERT and FAIL
//
SZTHISFILE


//=--------------------------------------------------------------------------=
// all the events in this control
//
// TODO: add events here ...
//
VARTYPE rgI4 [] = {VT_I4 };

typedef enum {
    Event_Complete = 0,
} EVENTS;

EVENTINFO m_rgEvents [] = {
    { DISPID_COMPLETE, 0, NULL},
};
/*
		FireEvent(&(m_rgEvents[0]));
*/

//=--------------------------------------------------------------------------=
// array describing all of our property pages.  these clsids are typically
// in guids.h
//
// TODO: add any additional property page guids here ...
//
const GUID *rgiemimPropPages [] = {
    &CLSID_iemimGeneralPage
};

//=--------------------------------------------------------------------------=
// Custum Verb information
//
// TODO: add any custom verbs here in an array, using the VERBINFO structure.
//       then mark the controld def'n in iemimCtl.H with
//       this verb array
//


//=--------------------------------------------------------------------------=
// CiemimControl::Create
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
IUnknown *CiemimControl::Create
(
    IUnknown *pUnkOuter
)
{
    // make sure we return the private unknown so that we support aggegation
    // correctly!
    //
    CiemimControl *pNew = new CiemimControl(pUnkOuter);
    return pNew->PrivateUnknown();
}

//=--------------------------------------------------------------------------=
// CiemimControl::CiemimControl
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
CiemimControl::CiemimControl
(
    IUnknown *pUnkOuter
)
: CmimeInternetControl(pUnkOuter, OBJECT_TYPE_CTLIEMIM, (IDispatch *)this)
{
    // initialize anything here ...
    //
    memset(&m_state, 0, sizeof(IEMIMCTLSTATE));
	m_state.m_cfformat = new char[lstrlen("Media Type Control")+1];
	lstrcpy(m_state.m_cfformat,"Media Type Control");
	data = NULL;
	readTillNow = 0;

}
#pragma warning(default:4355)  // using 'this' in constructor

//=--------------------------------------------------------------------------=
// CiemimControl::~CiemimControl
//=--------------------------------------------------------------------------=
// "We all labour against our own cure, for death is the cure of all diseases"
//    - Sir Thomas Browne (1605 - 82)
//
// Notes:
//
CiemimControl::~CiemimControl ()
{
    // TODO: clean up anything here.

	if (m_state.m_cfformat)
		delete [] m_state.m_cfformat;
	if (m_state.m_url)
		delete [] m_state.m_url;
	if (m_state.m_media)
		delete [] m_state.m_media;
}

//=--------------------------------------------------------------------------=
// CiemimControl:RegisterClassData
//=--------------------------------------------------------------------------=
// register the window class information for your control here.
// this information will automatically get cleaned up for you on DLL shutdown.
//
// Output:
//    BOOL            - FALSE means fatal error.
//
// Notes:
//
BOOL CiemimControl::RegisterClassData
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
    wndclass.lpfnWndProc    = CmimeInternetControl::ControlWindowProc;
    wndclass.hInstance      = g_hInstance;
    wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszClassName  = WNDCLASSNAMEOFCONTROL(OBJECT_TYPE_CTLIEMIM);

    return RegisterClass(&wndclass);
}

//=--------------------------------------------------------------------------=
// CiemimControl::BeforeCreateWindow
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
BOOL CiemimControl::BeforeCreateWindow
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
// CiemimControl::AfterCreateWindow
//=--------------------------------------------------------------------------=
// called just after the window is created.

BOOL CiemimControl::AfterCreateWindow
(
)

{
	return TRUE;
}

//=--------------------------------------------------------------------------=
// CiemimControl::InternalQueryInterface
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
HRESULT CiemimControl::InternalQueryInterface
(
    REFIID  riid,
    void  **ppvObjOut
)
{
    IUnknown *pUnk;

    *ppvObjOut = NULL;

    // TODO: if you want to support any additional interrfaces, then you should
    // indicate that here.  never forget to call CmimeInternetControl's version in the
    // case where you don't support the given interface.
    //
    if (DO_GUIDS_MATCH(riid, IID_Iiemim)) {
	pUnk = (IUnknown *)(Iiemim *)this;
    } else if (DO_GUIDS_MATCH(riid, IID_IPersistMoniker)){
	pUnk = (IUnknown *)(IPersistMoniker *)this;
	}
		else{
	return CmimeInternetControl::InternalQueryInterface(riid, ppvObjOut);
    }

    pUnk->AddRef();
    *ppvObjOut = (void *)pUnk;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CiemimControl::LoadTextState
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
STDMETHODIMP CiemimControl::LoadTextState
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
    hr = pPropertyBag->Read(L"URL", &v, pErrorLog);
	if (!FAILED(hr))
	{
		MAKE_ANSIPTR_FROMWIDE(tempVal, v.bstrVal);
		DWORD dw = lstrlen(tempVal);
		if (m_state.m_url)
			delete [] m_state.m_url;
		m_state.m_url = new char[dw + 1];

		if( !(m_state.m_url) )
		{
			FAIL("No memory");
			return(E_OUTOFMEMORY);
		}
		lstrcpy(m_state.m_url, tempVal);
	}

	VariantClear(&v);
	v.vt = VT_BSTR;
	v.bstrVal = ::SysAllocString(L"");
    hr = pPropertyBag->Read(L"Media", &v, pErrorLog);
	if (!FAILED(hr))
	{
		MAKE_ANSIPTR_FROMWIDE(tempVal, v.bstrVal);
		DWORD dw = lstrlen(tempVal);
		if (m_state.m_media)
			delete [] m_state.m_media;
		m_state.m_media = new char[dw + 1];

		if( !(m_state.m_media) )
		{
			FAIL("No memory");
			return(E_OUTOFMEMORY);
		}
		lstrcpy(m_state.m_media, tempVal);
	}

	VariantClear(&v);
	v.vt = VT_BSTR;
	v.bstrVal = ::SysAllocString(L"");
    hr = pPropertyBag->Read(L"Cfformat", &v, pErrorLog);
	if (!FAILED(hr))
	{
		MAKE_ANSIPTR_FROMWIDE(tempVal, v.bstrVal);
		DWORD dw = lstrlen(tempVal);
		if (m_state.m_cfformat)
			delete [] m_state.m_cfformat;
		m_state.m_cfformat = new char[dw + 1];

		if( !(m_state.m_cfformat) )
		{
			FAIL("No memory");
			return(E_OUTOFMEMORY);
		}
		lstrcpy(m_state.m_cfformat, tempVal);
	}
	VariantClear(&v);
	
	Reload();
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CiemimControl::LoadBinaryState
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
#define STREAMHDR_MAGIC 34322394

STDMETHODIMP CiemimControl::LoadBinaryState
(
    IStream *pStream
)
{
    HRESULT hr;
	DWORD sh = STREAMHDR_MAGIC;
	DWORD   dw;

	hr = pStream->Read(&sh, sizeof(sh), NULL);
    RETURN_ON_FAILURE(hr);

    if (sh != STREAMHDR_MAGIC )
		return E_UNEXPECTED;

	if( m_state.m_url )
		delete [] m_state.m_url;
	hr = pStream->Read(&dw,sizeof(dw),0);
	if( SUCCEEDED(hr) )
	{
		if( !dw )
			m_state.m_url = 0;
		else
		{
			m_state.m_url = new char[dw+1];
			if( m_state.m_url )
				hr = pStream->Read(m_state.m_url,dw+1,0);
		}
	}

	if( m_state.m_media )
		delete [] m_state.m_media;
	hr = pStream->Read(&dw,sizeof(dw),0);
	if( SUCCEEDED(hr) )
	{
		if( !dw )
			m_state.m_media = 0;
		else
		{
			m_state.m_media = new char[dw+1];
			if( m_state.m_media )
				hr = pStream->Read(m_state.m_media,dw+1,0);
		}
	}

	if( m_state.m_cfformat)
		delete [] m_state.m_cfformat;
	hr = pStream->Read(&dw,sizeof(dw),0);
	if( SUCCEEDED(hr) )
	{
		if( !dw )
			m_state.m_cfformat = 0;
		else
		{
			m_state.m_cfformat = new char[dw+1];
			if( m_state.m_cfformat )
				hr = pStream->Read(m_state.m_cfformat,dw+1,0);
		}
	}

	Reload();
	return S_OK;
}

//=--------------------------------------------------------------------------=
// CiemimControl::SaveTextState
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
STDMETHODIMP CiemimControl::SaveTextState
(
    IPropertyBag *pPropertyBag,
    BOOL          fWriteDefaults
)
{
	VARIANT v;
	HRESULT hr;

	VariantInit(&v);
	v.vt = VT_BSTR;
    v.bstrVal = BSTRFROMANSI(m_state.m_url);
    RETURN_ON_NULLALLOC(v.bstrVal);
    hr = pPropertyBag->Write(L"URL", &v);
    VariantClear(&v);
    
	VariantInit(&v);
	v.vt = VT_BSTR;
    v.bstrVal = BSTRFROMANSI(m_state.m_media);
    RETURN_ON_NULLALLOC(v.bstrVal);
    hr = pPropertyBag->Write(L"Media", &v);
    VariantClear(&v);

	VariantInit(&v);
	v.vt = VT_BSTR;
    v.bstrVal = BSTRFROMANSI(m_state.m_cfformat);
    RETURN_ON_NULLALLOC(v.bstrVal);
    hr = pPropertyBag->Write(L"Cfformat", &v);
    VariantClear(&v);

    return S_OK;
}

//=--------------------------------------------------------------------------=
// CiemimControl::SaveBinaryState
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
STDMETHODIMP CiemimControl::SaveBinaryState
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

	dw = m_state.m_url ? lstrlen(m_state.m_url) : 0;
	hr = pStream->Write(&dw,sizeof(dw),0);
	RETURN_ON_FAILURE(hr);
	if( dw )
		hr = pStream->Write(m_state.m_url,dw+1,0);    

	dw = m_state.m_media ? lstrlen(m_state.m_media) : 0;
	hr = pStream->Write(&dw,sizeof(dw),0);
	RETURN_ON_FAILURE(hr);
	if( dw )
		hr = pStream->Write(m_state.m_media,dw+1,0);    

	dw = m_state.m_cfformat ? lstrlen(m_state.m_cfformat) : 0;
	hr = pStream->Write(&dw,sizeof(dw),0);
	RETURN_ON_FAILURE(hr);
	if( dw )
		hr = pStream->Write(m_state.m_cfformat,dw+1,0);  
	
    return S_OK;
}


//=--------------------------------------------------------------------------=
// CiemimControl::OnDraw
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
HRESULT CiemimControl::OnDraw
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
	SetBkMode(hdcDraw,TRANSPARENT);
	SetTextColor(hdcDraw,RGB(0,0,255));
	TextOut(hdcDraw,prcBounds->left,prcBounds->top,
			 m_state.m_cfformat,lstrlen(m_state.m_cfformat));

    return S_OK;
}

//=--------------------------------------------------------------------------=
// CiemimControl::WindowProc
//=--------------------------------------------------------------------------=
// window procedure for this control.  nothing terribly exciting.
//
// Parameters:
//     see win32sdk on window procs [sans HWND -- it's in m_hwnd if you have one]
//
// Notes:
//
LRESULT CiemimControl::WindowProc
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
    return OcxDefWindowProc(msg, wParam, lParam);
}

//=--------------------------------------------------------------------------=
// CiemimControl::AboutBox
//=--------------------------------------------------------------------------=
// prints up an about box.  fweeeee.
//
// Notes:
//
void CiemimControl::AboutBox
(
    void
)
{
    // TODO: Ideally, one would use DialogBox, and some sort of Dialog Box here if
    // they wanted a slightly more interesting About Box ...  you should
    // still call ModalDialog first, however.
    //
    ModalDialog(TRUE);
    MessageBox(NULL, "This is My Control", "About iemim", MB_OK | MB_TASKMODAL);
    ModalDialog(FALSE);
}

void CiemimControl::Reload
(
    void
)
{
	if ((m_state.m_url) && (*m_state.m_url))
	   SetupDownload(OLESTRFROMANSI(m_state.m_url),DISPID_URL);
}

STDMETHODIMP  CiemimControl::get_URL(BSTR * val)
{
	CHECK_POINTER(val);

	BSTR * tempVal = val;
    
    *tempVal = m_state.m_url && *(m_state.m_url) ? BSTRFROMANSI(m_state.m_url) : SysAllocString(L"");
    return (*tempVal) ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP  CiemimControl::put_URL(BSTR val)
{
    MAKE_ANSIPTR_FROMWIDE(tempVal, val);

	DWORD dw = lstrlen(tempVal);
	if (m_state.m_url)
		delete [] m_state.m_url;
	m_state.m_url = new char[dw + 1];

	if( !(m_state.m_url) )
	{
		FAIL("No memory");
		return(E_OUTOFMEMORY);
	}

	lstrcpy(m_state.m_url, tempVal);

	PropertyChanged(DISPID_URL);
	if (*(m_state.m_url))
	{
		Reload();
	}
	m_fDirty = TRUE;
    return S_OK;
}

STDMETHODIMP  CiemimControl::get_Media(BSTR * val)
{
	CHECK_POINTER(val);

	BSTR * tempVal = val;
    
    *tempVal = m_state.m_media && *(m_state.m_media) ? BSTRFROMANSI(m_state.m_media) : SysAllocString(L"");
    return (*tempVal) ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP  CiemimControl::put_Media(BSTR val)
{
    MAKE_ANSIPTR_FROMWIDE(tempVal, val);

	DWORD dw = lstrlen(tempVal);
	if (m_state.m_media)
		delete [] m_state.m_media;
	m_state.m_media = new char[dw + 1];

	if( !(m_state.m_media) )
	{
		FAIL("No memory");
		return(E_OUTOFMEMORY);
	}

	lstrcpy(m_state.m_media, tempVal);

	PropertyChanged(DISPID_MEDIA);
    return S_OK;
}


STDMETHODIMP  CiemimControl::get_Cfformat(BSTR * val)
{
	CHECK_POINTER(val);

	BSTR * tempVal = val;
    
    *tempVal = m_state.m_cfformat && *(m_state.m_cfformat) ? BSTRFROMANSI(m_state.m_cfformat) : SysAllocString(L"");
    return (*tempVal) ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP  CiemimControl::put_Cfformat(BSTR val)
{
    MAKE_ANSIPTR_FROMWIDE(tempVal, val);

	DWORD dw = lstrlen(tempVal);
	if (m_state.m_cfformat)
		delete [] m_state.m_cfformat;
	m_state.m_cfformat = new char[dw + 1];

	if( !(m_state.m_cfformat) )
	{
		FAIL("No memory");
		return(E_OUTOFMEMORY);
	}

	lstrcpy(m_state.m_cfformat, tempVal);

	PropertyChanged(DISPID_CFFORMAT);
    return S_OK;
}


//#define               _HRESULT_TYPEDEF_(x)    x

HRESULT CiemimControl::OnData( DISPID id, DWORD grfBSCF,
		FORMATETC *pformatetc, STGMEDIUM *pstgmed, 
		DWORD amount )

{
	HRESULT         hr              = NOERROR;

	static char formatname[MAX_PATH];

	GetClipboardFormatName(pformatetc->cfFormat,
		formatname,MAX_PATH);
	
	if (m_state.m_cfformat)
		delete [] m_state.m_cfformat;
	m_state.m_cfformat = new char [lstrlen(formatname)+1];
	lstrcpy(m_state.m_cfformat,formatname);

	if (grfBSCF & BSCF_FIRSTDATANOTIFICATION)
	{
		if (data)
			delete [] data;
		data = 0;
		readTillNow = 0;
	}
	amount -= readTillNow; // the amount tobe read

	DWORD    dwRead      = 0;
	DWORD    dwReadTotal = 0;
	char * m_current;

	if (readTillNow)
	{
		char *temp = new char[readTillNow];
		memcpy( temp, data, readTillNow );
		delete [] data;
		data = new char [readTillNow+amount+1];
		memcpy(data,temp,readTillNow);
		m_current = data + readTillNow;
		delete [] temp;
	}
	else
	{
		//first time
		data = new char [amount+1];
		m_current = data;
	}
	if (amount > 0)
		do
		{
			hr = pstgmed->pstm->Read(m_current,amount,&dwRead);
 
			if( SUCCEEDED(hr) || hr == E_PENDING )
			{
				m_current += amount;
				dwReadTotal += dwRead;
			}
		}
		while ( (hr != S_FALSE) && (hr != E_PENDING) && SUCCEEDED(hr) );

	readTillNow += amount;

	if ((grfBSCF & BSCF_LASTDATANOTIFICATION) && readTillNow)
	{
		data[readTillNow] = '\0';
		FireEvent(&(m_rgEvents[0]));
		InvalidateControl(NULL); // Repaint media type
		if (data)
			delete [] data;
		data = 0;
	}
    return (hr);
}

STDMETHODIMP CiemimControl::GetClassID(CLSID * clsid)
{
	return E_NOTIMPL;
}


STDMETHODIMP CiemimControl::IsDirty(void)
{
	return E_NOTIMPL;
}

STDMETHODIMP CiemimControl::Load(BOOL fFullyAvailable, 
		IMoniker* pmkSrc,  IBindCtx* pbc,  DWORD grfMode)
{
	return E_NOTIMPL;
}

STDMETHODIMP CiemimControl::Save(IMoniker* pmkDst,  IBindCtx* pbc,  BOOL fRemember)
{
	return E_NOTIMPL;
}

STDMETHODIMP CiemimControl::SaveCompleted(IMoniker* pmkNew, IBindCtx* pbc)
{
	return E_NOTIMPL;
}
	
STDMETHODIMP CiemimControl::GetCurMoniker(IMoniker** ppmkCur)
{
	return E_NOTIMPL;
}

STDMETHODIMP CiemimControl::SetObjectRects
(
    LPCRECT prcPos,
    LPCRECT prcClip
)
{
    m_Size.cx = prcPos->right - prcPos->left;
	m_Size.cy = prcPos->bottom - prcPos->top;
	return COleControl::SetObjectRects(prcPos, prcClip);
}

