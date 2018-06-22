#include "IPServer.H"
#include "mimeinet.H"
#include "Util.H"

/* Initialize _szThisFile for ASSERT macro */

SZTHISFILE

static VARTYPE rgI4[] = { VT_I4 }; 

typedef enum {
    InternetEvent_Progress = 0,
    InternetEvent_ReadyStateChange = 1
} INTERNETEVENTS;

static EVENTINFO rgEvents [] = {
    { DISPID_PROGRESS, 1, rgI4 },           // (long percentDone)
    { DISPID_READYSTATECHANGE, 1, rgI4 },	// (OLE_READYSTATE newState)
};


// local class for doing async monitoring. It's not really all that
// general purpose, but it does the job...


class CxrtDownloadSink : public IBindStatusCallback
{
public:
    CxrtDownloadSink(IUnknown *punkOuter,CmimeInternetControl *,DISPID );
    ~CxrtDownloadSink();

    STDMETHOD(QueryInterface)(REFIID riid, void **ppvObjOut);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

        STDMETHOD(OnStartBinding)( 
            /* [in] */ DWORD grfBSCOption,
            /* [in] */ IBinding *pib);
        
        STDMETHOD(GetPriority)( 
            /* [out] */ LONG *pnPriority);
        
        STDMETHOD(OnLowResource)( 
            /* [in] */ DWORD reserved);
        
        STDMETHOD(OnProgress)( 
            /* [in] */ ULONG ulProgress,
            /* [in] */ ULONG ulProgressMax,
            /* [in] */ ULONG ulStatusCode,
            /* [in] */ LPCWSTR szStatusText);
        
        STDMETHOD(OnStopBinding)( 
            /* [in] */ HRESULT hresult,
            /* [in] */ LPCWSTR szError);
        
        STDMETHOD(GetBindInfo)( 
            /* [out] */ DWORD *grfBINDINFOF,
            /* [unique][out][in] */ BINDINFO *pbindinfo);
        
        STDMETHOD(OnDataAvailable)( 
            /* [in] */ DWORD grfBSCF,
            /* [in] */ DWORD dwSize,
            /* [in] */ FORMATETC *pformatetc,
            /* [in] */ STGMEDIUM *pstgmed);
        
        STDMETHOD(OnObjectAvailable)( 
            /* [in] */ REFIID riid,
            /* [iid_is][in] */ IUnknown *punk);



        CxrtDownloadSink * Next()                  { return(m_next); }
        void            Next(CxrtDownloadSink *n)  { m_next = n; }

        DISPID          DispId()  { return(m_propId); }
        IBinding *      Binding() { return(m_binding); }

private:

	CxrtDownloadSink *		m_next;
	CmimeInternetControl *	m_control;
        DISPID                  m_propId;
        IBinding *              m_binding;
        DWORD                   m_ref;
		IStream *				m_stream;

};


CxrtDownloadSink::CxrtDownloadSink
(
        IUnknown *              punkOuter,
		CmimeInternetControl *	control, 
        DISPID                  propId
)
{
//	CHECK_POINTER(control);

	m_control = control;
	m_control->AddRef();

	m_propId  = propId;
	m_next    = 0;
	m_binding = 0;
	m_ref     = 0;
	m_stream  = 0;
}

CxrtDownloadSink::~CxrtDownloadSink()
{
	if( m_control )
		m_control->Release();
	if( m_binding )
		m_binding->Release();
	if( m_stream )
		m_stream->Release();
}

STDMETHODIMP
CxrtDownloadSink::QueryInterface(const GUID &iid,void **ppv )
{ 
	if( IsEqualGUID(iid,IID_IUnknown) || IsEqualGUID(iid,IID_IBindStatusCallback) )
	{
		*ppv = this;
		AddRef();
		return(NOERROR);
	}
	return( E_NOINTERFACE );
}

STDMETHODIMP_(ULONG)
CxrtDownloadSink::AddRef()
{
	return(++m_ref);
}

STDMETHODIMP_(ULONG)
CxrtDownloadSink::Release()
{
	if(!--m_ref)
	{
		delete this;
		return(0);
	}
	return( m_ref );
}
	

STDMETHODIMP 
CxrtDownloadSink::GetBindInfo( DWORD *grfBINDF, BINDINFO *pbindInfo)
{
    *grfBINDF = BINDF_ASYNCHRONOUS | BINDF_GETNEWESTVERSION | BINDF_NOWRITECACHE |
		BINDF_ASYNCSTORAGE | BINDF_NOCOPYDATA;
	
	return(NOERROR);
}


STDMETHODIMP
CxrtDownloadSink::OnStartBinding(DWORD /*grfBSCOption*/,IBinding *pib) 
{
	// BUGBUG: should check to see options are what we think they are
	m_binding = pib;
	pib->AddRef();
	return(NOERROR);
}


STDMETHODIMP 
CxrtDownloadSink::GetPriority( LONG *pnPriority) 
{
	return(E_NOTIMPL);
}

STDMETHODIMP 
CxrtDownloadSink::OnProgress
( 
     ULONG ulProgress,
     ULONG ulProgressMax,
     ULONG ulStatusCode,
     LPCWSTR pwzStatusText
) 
{
	return(m_control->OnProgress(m_propId,ulProgress,
							ulProgressMax,ulStatusCode,pwzStatusText) );
}

STDMETHODIMP 
CxrtDownloadSink::OnDataAvailable
( 
     DWORD			grfBSCF,
     DWORD			dwSize,
     FORMATETC *	pFmtetc,
	 STGMEDIUM *	pstgmed
) 
{
#ifdef DEBUG
	char msg[200];
	wsprintf(msg,"::OnDataAvailable(%0xd,%d,%s,%s)\n",grfBSCF,dwSize,
		pFmtetc ? "pFmtetc" : "NULL", pstgmed ? "pstgmed" : "NULL" );
	OutputDebugString(msg);
#endif

	return(m_control->OnData(	m_propId,
								grfBSCF,
								pFmtetc,
								pstgmed,
								dwSize) );
}
        
STDMETHODIMP 
CxrtDownloadSink::OnObjectAvailable
(
	REFIID riid,
    IUnknown *punk
)
{
	return(E_NOTIMPL);
}


STDMETHODIMP 
CxrtDownloadSink::OnLowResource( DWORD reserved) 
{
	m_binding->Abort();
	return(S_OK);
}

STDMETHODIMP 
CxrtDownloadSink::OnStopBinding(HRESULT hrError, LPCWSTR szError) 
{
	if (FAILED(hrError))
	{
		if (m_control->m_state.m_cfformat)
			delete [] m_control->m_state.m_cfformat;
		m_control->m_state.m_cfformat = new char [lstrlen("URL Not Found.")+1];
		lstrcpy(m_control->m_state.m_cfformat,"URL Not Found.");
	}
	m_control->Invalidate();

	m_binding->Release();
	m_binding = 0;
	m_control->Release();
	m_control = 0;

	return(NOERROR);
}



//------------------------------------------------------
//
// class CmimeInternetControl
//
//
CmimeInternetControl::CmimeInternetControl
(
	IUnknown *	pUnkOuter, 
	int			iPrimaryDispatch, 
	void *		pMainInterface
)
	: COleControl(pUnkOuter,iPrimaryDispatch,pMainInterface)
{
	m_host = 0;
	m_readyState = 1;
}

CmimeInternetControl::~CmimeInternetControl()
{
	if( m_host )
		m_host->Release();
}


HRESULT CmimeInternetControl::InternalQueryInterface
(
    REFIID  riid,
    void  **ppvObjOut
)
{
    *ppvObjOut = NULL;
     return COleControl::InternalQueryInterface(riid, ppvObjOut);
}



HRESULT 
CmimeInternetControl::GetBindHost()
{

	if( m_host )
		return(NOERROR);

    // Try service provider first...

	IServiceProvider * serviceProvider = 0;

	HRESULT hr = m_pClientSite->QueryInterface
									(
										IID_IServiceProvider,
										(void**)&serviceProvider
									);

	if( SUCCEEDED(hr) )
    {
		hr = serviceProvider->QueryService
                                    (
                                        SID_IBindHost,
                                        IID_IBindHost,
                                        (void**)&m_host
                                    );
		serviceProvider->Release();
    }

    if( FAILED(hr) )
    {
        // Some containers put IBindHost directly on the client site

        hr = m_pClientSite->QueryInterface
									(
                                        IID_IBindHost,
                                        (void**)&m_host
									);


    }

	return(hr);

}


HRESULT CmimeInternetControl::GetAMoniker( LPOLESTR url, IMoniker ** ppmkr )
{
	HRESULT hr = GetBindHost();

	if( SUCCEEDED(hr) )
		hr = m_host->CreateMoniker(url,NULL,ppmkr,0);

	if( FAILED(hr) )
    { 
       hr = ::CreateURLMoniker(0,url,ppmkr); 
    }

	return( hr );
}


HRESULT CmimeInternetControl::SetupDownload( LPOLESTR url, DISPID propId )
{
	CHECK_POINTER(url);

	IMoniker * pmkr;

	HRESULT hr = GetAMoniker( url, &pmkr );

	IBindCtx * pBindCtx = 0;

	if( SUCCEEDED(hr) )
    {
		hr = ::CreateBindCtx(0,&pBindCtx);
    }

	
    FORMATETC		rgfmtetc[2] = 
               { {CF_NULL, NULL, DVASPECT_CONTENT, -1, TYMED_ISTREAM}, 
                 {CF_NULL, NULL, DVASPECT_CONTENT, -1, TYMED_ISTREAM} };

	if ((m_state.m_media) && (*m_state.m_media))
	{
		rgfmtetc[0].cfFormat = 
			RegisterClipboardFormat (m_state.m_media);
	}
	

	IEnumFORMATETC *myEtc;
	
	HRESULT h1;
	h1 = CreateFormatEnumerator (2, (FORMATETC *)&rgfmtetc, &myEtc);

    if (SUCCEEDED(h1) && &myEtc)
    {
        h1 = RegisterFormatEnumerator (pBindCtx, myEtc, 0);
        ASSERT (SUCCEEDED(h1), "RegisterFormatEnumerator failed.");
    }
	
	HRESULT hres;
	const char * const rgszTypes[] = {""};
	CLIPFORMAT cfFormats[1];
	cfFormats[0] = CF_NULL;
	hres = RegisterMediaTypes(1,rgszTypes, cfFormats);
	
	CxrtDownloadSink * sink = 0;

	if( SUCCEEDED(hr) )
	{
		sink = new CxrtDownloadSink(0,this,propId);
		if( sink )
			sink->AddRef();
	}

	if( SUCCEEDED(hr) && !sink )
		hr = E_OUTOFMEMORY;
	
	if( SUCCEEDED(hr) )
	{
		hr = ::RegisterBindStatusCallback(pBindCtx, sink, 
                       NULL, 0) ; // BINDF_ASYNCHRONOUS, 0);
	}
		
	IStream * strm = 0;

	if( SUCCEEDED(hr) )
		hr = pmkr->BindToStorage( pBindCtx, 0, IID_IStream, (void**)&strm );

	if( strm )
		strm->Release();

	if( pBindCtx )
		pBindCtx->Release();

	if( FAILED(hr) && sink )
		sink->Release();

	return(hr);

}


void CmimeInternetControl::Invalidate()
{
	InvalidateControl(NULL);
}

HRESULT CmimeInternetControl::OnData( DISPID, DWORD,FORMATETC *pformatetc, STGMEDIUM *pstgmed, DWORD)
{
	return(NOERROR);
}

HRESULT CmimeInternetControl::OnProgress( DISPID, ULONG progress, ULONG themax, ULONG, LPCWSTR)
{
	return(NOERROR);
}


HRESULT	CmimeInternetControl::FireReadyStateChange( long newState )
{
	FireEvent( &::rgEvents[InternetEvent_ReadyStateChange], m_readyState = newState );
	return(S_OK);
}

HRESULT CmimeInternetControl::FireProgress( ULONG dwAmount )
{
	FireEvent( &::rgEvents[InternetEvent_Progress], dwAmount );
	return(S_OK);
}
