#ifndef _XSINK_H_
#define _XSINK_H_

#include "tickctl.h"


// local class for doing async monitoring. It's not really all that
// general purpose, but it does the job...


class CxrtDownloadSink : public IBindStatusCallback
{
public:
    CxrtDownloadSink(IUnknown *punkOuter,CTickCtrl *,DISPID );
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
		CTickCtrl *				m_control;
        DISPID                  m_propId;
        IBinding *              m_binding;
        DWORD                   m_ref;
		IStream *				m_stream;

};


#endif