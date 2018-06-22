#include "stdafx.h"
#include "xsink.h"

// local class for doing async monitoring. It's not really all that
// general purpose, but it does the job...


CxrtDownloadSink::CxrtDownloadSink
(
        IUnknown *              punkOuter,
		CTickCtrl *				control, 
        DISPID                  propId
)
{
//	CHECK_POINTER(control);

	m_control = control;
//	m_control->AddRef();

	m_propId  = propId;
	m_next    = 0;
	m_binding = 0;
	m_ref     = 0;
	m_stream  = 0;
}

CxrtDownloadSink::~CxrtDownloadSink()
{
//	if( m_control )
//		m_control->Release();
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
    *grfBINDF = BINDF_ASYNCHRONOUS | BINDF_NOWRITECACHE |BINDF_ASYNCSTORAGE | BINDF_GETNEWESTVERSION;
	
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

  //  if( !m_stream )
//		m_stream = pstgmed->pstm;

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
	// BUGBUG: really should have this kind of harsh policy on this ...
	m_binding->Abort();
	return(S_OK);
}

STDMETHODIMP 
CxrtDownloadSink::OnStopBinding(HRESULT hrError, LPCWSTR szError) 
{
	m_binding->Release();
	m_binding = 0;
//	m_control->Release();
	m_control = 0;

	return(NOERROR);
}




