// ===========================================================================
// File: DOWNLOAD.Cpp
// Defines the class behaviour for CBindStatusCallback. 


#include "stdafx.h"
#include "Mainfrm.h"
#include "download.h"
#include "winnls.h"
#include "Util.H"

// ===========================================================================
//                     CBindStatusCallback Implementation
// ===========================================================================

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::CBindStatusCallback
// ---------------------------------------------------------------------------
CBindStatusCallback::CBindStatusCallback(CMainFrame * pMDIframewnd)
{
    m_pbinding = NULL;
    m_pstm = NULL;
    m_cRef = 1;
    m_cbOld = 0;
	m_pMDIframwnd=pMDIframewnd;
}  // CBindStatusCallback

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::~CBindStatusCallback
// ---------------------------------------------------------------------------
CBindStatusCallback::~CBindStatusCallback()
{
    if (m_pstm)
        m_pstm->Release();
    if (m_pbinding)
        m_pbinding->Release();
}  // ~CBindStatusCallback


// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::QueryInterface
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::QueryInterface(REFIID riid, void** ppv)
{ 
    *ppv = NULL;
    
    if (riid==IID_IUnknown || riid==IID_IBindStatusCallback)
        {
        *ppv = this;
        AddRef();
        return S_OK;
        }
    return E_NOINTERFACE;
}  // CBindStatusCallback::QueryInterface

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnStartBinding
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::OnStartBinding(DWORD grfBSCOption, IBinding* pbinding)
{
	m_pMDIframwnd->MyShowPane("Starting to Download File ");
	return(NOERROR);
}  // CBindStatusCallback::OnStartBinding

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::GetPriority
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::GetPriority(LONG* pnPriority) 
{
	 return(NOERROR);
}  // CBindStatusCallback::GetPriority

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnLowResource
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::OnLowResource(DWORD dwReserved)
{
 	 return(NOERROR);
}  // CBindStatusCallback::OnLowResource

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnStopBinding
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::OnStopBinding(HRESULT hrStatus, LPCWSTR pszError) 
{
	if (hrStatus)
		m_pMDIframwnd->MyShowPane("File download Failed.");
	else
		m_pMDIframwnd->MyShowPane("File Downloaded");
	return(NOERROR);
}  // CBindStatusCallback::OnStopBinding

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::GetBindInfo
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::GetBindInfo(DWORD* pgrfBINDF, BINDINFO* pbindInfo)
{
	 return (NOERROR);
}  // CBindStatusCallback::GetBindInfo

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnDataAvailable
// This function is called whenever data starts arriving. When the file download is
// complete then the BSCF_LASTDATANOTIFICATION comes and you can get the local cached
// File Name.
// ---------------------------------------------------------------------------
 STDMETHODIMP
 CBindStatusCallback::OnDataAvailable
 (
 DWORD grfBSCF, 
 DWORD dwSize, 
 FORMATETC* pfmtetc, 
 STGMEDIUM* pstgmed
 ) 
 {
	 	 return(NOERROR);
 }  // CBindStatusCallback::OnDataAvailable


// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnObjectAvailable
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::OnObjectAvailable(REFIID riid, IUnknown* punk) 
{
	 return(NOERROR);
}  // CBindStatusCallback::OnObjectAvailable

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnProgress
// ---------------------------------------------------------------------------
STDMETHODIMP 
CBindStatusCallback::OnProgress
( 
     ULONG ulProgress,
     ULONG ulProgressMax,
     ULONG ulStatusCode,
     LPCWSTR pwzStatusText
) 
{
    char    msg[100];
    wsprintf(msg,"Downloaded : %d bytes of %d ", ulProgress, (ulProgress>ulProgressMax)?ulProgress:ulProgressMax);
	m_pMDIframwnd->MyShowPane(msg);

 	return(NOERROR);
}// CBindStatusCallback::OnProgress
