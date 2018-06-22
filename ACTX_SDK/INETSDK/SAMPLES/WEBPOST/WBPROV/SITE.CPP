/*****************************************************************/
/**               Microsoft Windows 4.00                        **/
/**           Copyright (C) Microsoft Corp., 1995-1996          **/
/*****************************************************************/

/* SITE.CPP - Methods for SITE class
 *
 * History:
 *  02/20/96    vlads   Created
 *
 */

#include "wbprov.h"

WPPSiteA::WPPSiteA(LPCSTR lpszSiteName, LPCSTR lpszURL)
    : m_cRef(1),
      m_fValid(FALSE),
      m_pDefaultSite(NULL)
{
    // Constructor logic
    m_fValid = TRUE;

	 // Get default site object
    //m_pDefaultSite = WPPCreateDefaultSite(lpszSiteName, lpszURL);
}

WPPSiteA::~WPPSiteA(void)
{

	 // If default pointer was obtained - release it
   	if (m_pDefaultSite) {
	 	m_pDefaultSite->Release();
	 }

    // Destructor and clean up
    m_fValid = FALSE;
}


WPPSiteW::WPPSiteW(LPCWSTR lpszSiteName, LPCWSTR lpszURL)
    : m_cRef(1),
      m_fValid(FALSE),
      m_pDefaultSite(NULL)
{
    // Constructor logic
    m_fValid = TRUE;

	// Should create a WPPSiteA object
	
	 // Get default site object
    //m_pDefaultSite = WPPCreateDefaultSite(lpszSiteName, lpszURL);
}

WPPSiteW::~WPPSiteW(void)
{

	 // If default pointer was obtained - release it
   	if (m_pDefaultSite) {
	 	m_pDefaultSite->Release();
	 }

    // Destructor and clean up
    m_fValid = FALSE;
}


//
// GLobal object generator function
//
dllexp
HRESULT
WINAPI
WppBindToSiteA(
	HWND	hwnd,
	LPCSTR	lpszSiteName,
    LPCSTR lpszURL,
    REFIID 	riid,
	DWORD	dwFlag,
	DWORD	dwReserved,
    PVOID * ppvObj)
{

    WPPSiteA *pSite = NULL;

    // Check requested interface ID
    if (!IsEqualIID(riid, IID_IUnknown) &&
        !IsEqualIID(riid, IID_IWPSite)) {
        return ResultFromScode(E_NOINTERFACE);
    }

	// This sample provider will handle URL 
	// http://wbprov
	if (!(dwFlag & WPF_FORCE_BIND))
	{
		if (!(lpszURL && !lstrcmpi(lpszURL, "http://wbprov")))
        	return ResultFromScode(E_INVALIDARG);
	}
		
    // Create instance of object
    pSite = new WPPSiteA(NULL,lpszURL);

    // Was it sucessful ?
    if (!pSite || !pSite->IsValid()) {
        return ResultFromScode(E_OUTOFMEMORY);
    }

    *ppvObj = pSite;
    return NOERROR;
}


dllexp
HRESULT
WINAPI
WppListSitesA(
	LPDWORD			lpcbSites,
	LPWPSITEINFOA	lpSiteInfo,
	LPDWORD			lpcSites)
{
    return ResultFromScode(E_NOTIMPL);
}


dllexp 
HRESULT 
WINAPI
WppDeleteSiteA(
	LPCSTR	lpszSiteName)
{
    return ResultFromScode(E_NOTIMPL);
}


//
// GLobal object generator function
//
dllexp
HRESULT
WINAPI
WppBindToSiteW(
	HWND	hwnd,
	LPCWSTR	lpszSiteName,
    LPCWSTR lpszURL,
    REFIID 	riid,
	DWORD	dwFlag,
	DWORD	dwReserved,
    PVOID * ppvObj)
{
    return ResultFromScode(E_NOTIMPL);
}


dllexp
HRESULT
WINAPI
WppListSitesW(
	LPDWORD			lpcbSites,
	LPWPSITEINFOW	lpSiteInfo,
	LPDWORD			lpcSites)
{
    return ResultFromScode(E_NOTIMPL);
}


dllexp 
HRESULT 
WINAPI
WppDeleteSiteW(
	LPCWSTR	lpszSiteName)
{
    return ResultFromScode(E_NOTIMPL);
}


//
// *** IUnknown methods ***
//

STDMETHODIMP WPPSiteA::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
    if (!IsEqualIID(riid, IID_IUnknown) &&
        !IsEqualIID(riid, IID_IWPSite)) {
        return ResultFromScode(E_NOINTERFACE);
    }

    *ppvObj = this;
    AddRef();
    return NOERROR;
}

STDMETHODIMP_(ULONG) WPPSiteA::AddRef(void)
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) WPPSiteA::Release(void)
{
    ULONG cRef;

    cRef = --m_cRef;

    if (0L == m_cRef) {
        delete this;
    }

    return cRef;
}


STDMETHODIMP WPPSiteW::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
    if (!IsEqualIID(riid, IID_IUnknown) &&
        !IsEqualIID(riid, IID_IWPSite)) {
        return ResultFromScode(E_NOINTERFACE);
    }

    *ppvObj = this;
    AddRef();
    return NOERROR;
}

STDMETHODIMP_(ULONG) WPPSiteW::AddRef(void)
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) WPPSiteW::Release(void)
{
    ULONG cRef;

    cRef = --m_cRef;

    if (0L == m_cRef) {
        delete this;
    }

    return cRef;
}


//
// *** IWPSite methods ***
//

STDMETHODIMP WPPSiteA::NetworkConnect (LPCSTR lpszUserName,
						      LPCSTR lpszPassword)
{
	OutputDebugString("WBPROV: NetworkConnect");
	OutputDebugString("\r\n");
	return NOERROR;

#if 0
   if (m_pDefaultSite) {
	   return(m_pDefaultSite->NetworkConnect(lpszUserName,lpszPassword));
	}

   return ResultFromScode(E_NOTIMPL);
#endif
}

STDMETHODIMP WPPSiteA::NetworkDisconnect ()
{
	OutputDebugString("WBPROV: NetworkDisconnect");
	OutputDebugString("\r\n");
	return NOERROR;

#if 0
   if (m_pDefaultSite) {
	   return(m_pDefaultSite->NetworkDisconnect());
	}

    return ResultFromScode(E_NOTIMPL);
#endif
}

STDMETHODIMP WPPSiteA::ServerLogin (LPCSTR lpszUserName,
						      LPCSTR lpszPassword)
{
	OutputDebugString("WBPROV: ServerLogin");
	OutputDebugString("\r\n");
	return NOERROR;

#if 0
   if (m_pDefaultSite) {
	   return(m_pDefaultSite->ServerLogin(lpszUserName,lpszPassword));
	}

   return ResultFromScode(E_NOTIMPL);
#endif
}

STDMETHODIMP WPPSiteA::ServerLogout ()
{
	OutputDebugString("WBPROV: ServerLogout");
	OutputDebugString("\r\n");
	return NOERROR;

#if 0
   if (m_pDefaultSite) {
	   return(m_pDefaultSite->ServerLogout());
	}

   return ResultFromScode(E_NOTIMPL);
#endif
}

STDMETHODIMP WPPSiteA::GetSiteInfo (
						LPWPSITEINFOA lpSiteInfo,
						LPDWORD lpcbSiteInfo)

{
	OutputDebugString("WBPROV: GetSiteInfo");
	OutputDebugString("\r\n");

   if (m_pDefaultSite) {
	   return(m_pDefaultSite->GetSiteInfo (lpSiteInfo,lpcbSiteInfo));
	}

   return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteA::PostFiles(DWORD 	cLocalPaths,
						LPSTR 	*lppszLocalPaths,
						LPDWORD	lpcbURL,
						LPSTR	lpszURL,
						DWORD 	dwFlag)

{
	OutputDebugString("WBPROV: PostFiles");
	OutputDebugString("\r\n");
	return NOERROR;

#if 0
   if (m_pDefaultSite) {
	   return(m_pDefaultSite->PostFiles(cLocalPaths,
                                       lppszLocalPaths,
                                       lpcbURL,
                                       lpszURL,
                                       dwFlag));
	}

   return ResultFromScode(E_NOTIMPL);
#endif
}

STDMETHODIMP WPPSiteA::Commit ()
{
	OutputDebugString("WBPROV: Commit");
	OutputDebugString("\r\n");

   if (m_pDefaultSite) {
	   return(m_pDefaultSite->Commit());
	}

    return ResultFromScode(E_NOTIMPL);
	
}

STDMETHODIMP WPPSiteA::GetParam(LPCSTR 	lpszParameter,
					       LPDWORD	lpcchValue,
					       LPSTR	lpszValue)

{
	OutputDebugString("WBPROV: GetParam");
	OutputDebugString("\r\n");

   if (m_pDefaultSite) {
	   return(m_pDefaultSite->GetParam(lpszParameter,
                                      lpcchValue,
                                      lpszValue));
	}

   return ResultFromScode(E_NOTIMPL);
	
}

STDMETHODIMP WPPSiteA::SetParam(LPCSTR	lpszParameter,
					       LPCSTR  lpszValue)

{
	OutputDebugString("WBPROV: SetParam");
	OutputDebugString("\r\n");

   if (m_pDefaultSite) {
	   return(m_pDefaultSite->SetParam(lpszParameter,
                                      lpszValue));
	}

    return ResultFromScode(E_NOTIMPL);
	
}

STDMETHODIMP WPPSiteA::GetError (
							LPDWORD	lpdwErrorType,
							LPDWORD	lpdwErrorCode,
							LPDWORD	lpcbError,
							LPTSTR	lpszError) 
{
	OutputDebugString("WBPROV: GetError");
	OutputDebugString("\r\n");

    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteA::DeleteFile (
							LPCTSTR	lpszFile)
{
	OutputDebugString("WBPROV: DeleteFile");
	OutputDebugString("\r\n");
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteA::FindFirstFile (
								LPCTSTR lpszSearchFile,
								LPWIN32_FIND_DATA lpFindFileData,
								LPHANDLE lpSearchHandle)
{
	OutputDebugString("WBPROV: FindFirstFile");
	OutputDebugString("\r\n");
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteA::FindNextFile (
								HANDLE hSearchHandle,
								LPWIN32_FIND_DATA lpFindFileData)
{
	OutputDebugString("WBPROV: FindNextFile");
	OutputDebugString("\r\n");
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteA::FindClose (
							HANDLE hSearchHandle)
{
	OutputDebugString("WBPROV: FindClose");
	OutputDebugString("\r\n");
    return ResultFromScode(E_NOTIMPL);
}	


//
// *** IWPSite methods ***
//

STDMETHODIMP WPPSiteW::NetworkConnect (LPCWSTR lpszUserName,
						      LPCWSTR lpszPassword)
{
	OutputDebugString("WPPSiteW: NetworkConnect");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
	return ResultFromScode(E_NOTIMPL);

}

STDMETHODIMP WPPSiteW::NetworkDisconnect ()
{
	OutputDebugString("WPPSiteW: NetworkDisconnect");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
	return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteW::ServerLogin (LPCWSTR lpszUserName,
						      LPCWSTR lpszPassword)
{
	OutputDebugString("WPPSiteW: ServerLogin");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
	return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteW::ServerLogout ()
{
	OutputDebugString("WPPSiteW: ServerLogout");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
	return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteW::GetSiteInfo (
						LPWPSITEINFOW lpSiteInfo,
						LPDWORD lpcbSiteInfo)

{
	OutputDebugString("WPPSiteW: GetSiteInfo");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
   	return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteW::PostFiles(DWORD 	cLocalPaths,
						LPWSTR 	*lppszLocalPaths,
						LPDWORD	lpcbURL,
						LPWSTR	lpszURL,
						DWORD 	dwFlag)

{
	OutputDebugString("WPPSiteW: PostFiles");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
	return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteW::Commit ()
{
	OutputDebugString("WPPSiteW: Commit");
	OutputDebugString("\r\n");
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteW::GetParam(LPCWSTR 	lpszParameter,
					       LPDWORD	lpcchValue,
					       LPWSTR	lpszValue)

{
	OutputDebugString("WPPSiteW: GetParam");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
	return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteW::SetParam(LPCWSTR	lpszParameter,
					       LPCWSTR  lpszValue)

{
	OutputDebugString("WPPSiteW: SetParam");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
    return ResultFromScode(E_NOTIMPL);	
}

STDMETHODIMP WPPSiteW::GetError (
							LPDWORD	lpdwErrorType,
							LPDWORD	lpdwErrorCode,
							LPDWORD	lpcbError,
							LPWSTR	lpszError) 
{
	OutputDebugString("WPPSiteW: GetError");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteW::DeleteFile (
							LPCWSTR	lpszFile)
{
	OutputDebugString("WPPSiteW: DeleteFile");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteW::FindFirstFile (
								LPCWSTR lpszSearchFile,
								LPWIN32_FIND_DATAW lpFindFileData,
								LPHANDLE lpSearchHandle)
{
	OutputDebugString("WPPSiteW: FindFirstFile");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
    return ResultFromScode(E_NOTIMPL);
} 

STDMETHODIMP WPPSiteW::FindNextFile (
								HANDLE hSearchHandle,
								LPWIN32_FIND_DATAW lpFindFileData)
{
	OutputDebugString("WPPSiteW: FindNextFile");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP WPPSiteW::FindClose (
							HANDLE hSearchHandle)
{
	OutputDebugString("WPPSiteW: FindClose");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
    return ResultFromScode(E_NOTIMPL);
}	
