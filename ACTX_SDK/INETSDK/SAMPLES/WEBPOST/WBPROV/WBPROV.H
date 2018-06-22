/*****************************************************************/
/**               Microsoft Windows 4.00                        **/
/**           Copyright (C) Microsoft Corp., 1995-1996          **/
/*****************************************************************/

/* WPTEST.H - Test provider with COM interface
 *
 */

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <regstr.h>

#include <wpapi.h>
#include  <wpspi.h>

//
// Important defines
//

#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))

#define DATASEG_PERINSTANCE     ".instance"
#define DATASEG_SHARED          ".data"
#define DATASEG_READONLY         ".code"
#define DATASEG_DEFAULT     DATASEG_SHARED

#pragma data_seg(DATASEG_PERINSTANCE)

extern HANDLE hInstance;

// Set the default data segment
#pragma data_seg(DATASEG_DEFAULT)

//
// Module ref counting
//
extern UINT g_cRefThisDll;
extern UINT g_cLocks;

extern void LockThisDLL(BOOL fLock);
extern void RefThisDLL(BOOL fRef);

//
// Class definition for factory.
// Nb: This is not needed for first release, but will be needed as
// more COM functionality will be packaged inside provider
//
class WPPClassFactory : public IClassFactory
{
public:
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    STDMETHODIMP CreateInstance(
            /* [unique][in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

    STDMETHODIMP LockServer(
            /* [in] */ BOOL fLock);
};


//
// Class definition for provider object
// Nb: This is not needed for first release, but will be needed as
// more COM functionality will be packaged inside provider
//

class WPProvider : public IWPProvider
{

private:
    ULONG m_cRef;

    WPProvider();
    ~WPProvider();

public:
    // *** IUnknown methods ***
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID * ppvObj);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    // *** Specific functions ***
};


//
// Class definition for site object
//

class WPPSiteA : public IWPSiteA
{
friend dllexp HRESULT WINAPI WppBindToSiteA(HWND hwnd1,
						LPCSTR   lpszSiteName,
						LPCSTR   lpszURL,
						REFIID riid,
						DWORD	dwFlag,
						DWORD	dwReserved,
						PVOID * ppvObj);

friend dllexp HRESULT WINAPI WppListSitesA(
						LPDWORD			lpcbSites,
						LPWPSITEINFOA	lpSiteInfo,
						LPDWORD			lpcSites);

friend dllexp HRESULT WINAPI WppDeleteSiteA(
						LPCSTR	lpszSiteName);		

private:
    ULONG   m_cRef;
    BOOL    m_fValid;
    WPPSiteA *m_pDefaultSite;

    WPPSiteA(LPCSTR lpszSiteName, LPCSTR lpszURL);
    ~WPPSiteA();

    BOOL inline IsValid(VOID) {
        return m_fValid;
    }

public:
    // *** IUnknown methods ***
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID * ppvObj);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    // *** Specific functions ***
	STDMETHOD(GetSiteInfo) (THIS_ 
							LPWPSITEINFOA lpSiteInfo, 
							LPDWORD lpcbSiteInfo) ;
    STDMETHOD(NetworkConnect) (THIS_ 
								LPCSTR lpszUserName, 
								LPCSTR lpszPassword) ;
    STDMETHOD(NetworkDisconnect) (THIS_ ) ;
    STDMETHOD(ServerLogin) (THIS_ 
							LPCSTR lpszUserName, 
							LPCSTR lpszPassword) ;
    STDMETHOD(ServerLogout) (THIS_ ) ;
    STDMETHOD(PostFiles) (THIS_ 
							DWORD 	cLocalPaths, 
							LPSTR 	*lppszLocalPaths, 
							LPDWORD	lpcbURL,
							LPSTR	lpszURL,
							DWORD 	dwFlag) ;
	STDMETHOD(DeleteFile) (THIS_
							LPCSTR	lpszFile) ;
	STDMETHOD(FindFirstFile) (THIS_
								LPCSTR lpszSearchFile,
								LPWIN32_FIND_DATAA lpFindFileData,
								LPHANDLE lpSearchHandle) ;
	STDMETHOD(FindNextFile) (THIS_
								HANDLE hSearchHandle,
								LPWIN32_FIND_DATA lpFindFileData) ;
	STDMETHOD(FindClose) (THIS_
							HANDLE hSearchHandle) ;	
    STDMETHOD(Commit) (THIS_ ) ;
    STDMETHOD(GetParam) (THIS_ 
							LPCSTR 	lpszParameter,
							LPDWORD	lpcchValue,
							LPSTR	lpszValue) ;
    STDMETHOD(SetParam) (THIS_ 
							LPCSTR	lpszParameter,
							LPCSTR	lpszValue) ;
	STDMETHOD(GetError) (THIS_
							LPDWORD	lpdwErrorType,
							LPDWORD	lpdwErrorCode,
							LPDWORD	lpcbError,
							LPSTR	lpszError) ;
    STDMETHOD(AddWizardPages) (THIS_ 
    							LPVOID lpv,
								LPFNADDPROPSHEETPAGE lpfnAdd, 
								LPARAM lParam) ;
};

class WPPSiteW : public IWPSiteW
{
friend dllexp HRESULT WINAPI WppBindToSiteW(HWND hwnd1,
						LPCWSTR   lpszSiteName,
						LPCWSTR   lpszURL,
						REFIID riid,
						DWORD	dwFlag,
						DWORD	dwReserved,
						PVOID * ppvObj);

friend dllexp HRESULT WINAPI WppListSitesW(
						LPDWORD			lpcbSites,
						LPWPSITEINFOW	lpSiteInfo,
						LPDWORD			lpcSites);

friend dllexp HRESULT WINAPI WppDeleteSiteW(
						LPCWSTR	lpszSiteName);		

private:
    ULONG   m_cRef;
    BOOL    m_fValid;
    WPPSiteW *m_pDefaultSite;

    WPPSiteW(LPCWSTR lpszSiteName, LPCWSTR lpszURL);
    ~WPPSiteW();

    BOOL inline IsValid(VOID) {
        return m_fValid;
    }

public:
    // *** IUnknown methods ***
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID * ppvObj);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    // *** Specific functions ***
	STDMETHOD(GetSiteInfo) (THIS_ 
							LPWPSITEINFOW lpSiteInfo, 
							LPDWORD lpcbSiteInfo) ;
    STDMETHOD(NetworkConnect) (THIS_ 
								LPCWSTR lpszUserName, 
								LPCWSTR lpszPassword) ;
    STDMETHOD(NetworkDisconnect) (THIS_ ) ;
    STDMETHOD(ServerLogin) (THIS_ 
							LPCWSTR lpszUserName, 
							LPCWSTR lpszPassword) ;
    STDMETHOD(ServerLogout) (THIS_ ) ;
    STDMETHOD(PostFiles) (THIS_ 
							DWORD 	cLocalPaths, 
							LPWSTR 	*lppszLocalPaths, 
							LPDWORD	lpcbURL,
							LPWSTR	lpszURL,
							DWORD 	dwFlag) ;
	STDMETHOD(DeleteFile) (THIS_
							LPCWSTR	lpszFile) ;
	STDMETHOD(FindFirstFile) (THIS_
								LPCWSTR lpszSearchFile,
								LPWIN32_FIND_DATAW lpFindFileData,
								LPHANDLE lpSearchHandle) ;
	STDMETHOD(FindNextFile) (THIS_
								HANDLE hSearchHandle,
								LPWIN32_FIND_DATAW lpFindFileData) ;
	STDMETHOD(FindClose) (THIS_
							HANDLE hSearchHandle) ;	
    STDMETHOD(Commit) (THIS_ ) ;
    STDMETHOD(GetParam) (THIS_ 
							LPCWSTR 	lpszParameter,
							LPDWORD	lpcchValue,
							LPWSTR	lpszValue) ;
    STDMETHOD(SetParam) (THIS_ 
							LPCWSTR	lpszParameter,
							LPCWSTR	lpszValue) ;
	STDMETHOD(GetError) (THIS_
							LPDWORD	lpdwErrorType,
							LPDWORD	lpdwErrorCode,
							LPDWORD	lpcbError,
							LPWSTR	lpszError) ;
    STDMETHOD(AddWizardPages) (THIS_ 
    							LPVOID lpv,
								LPFNADDPROPSHEETPAGE lpfnAdd, 
								LPARAM lParam) ;
};


//
// Syncronization mechanisms
//
void Netlib_EnterCriticalSection(void);
void Netlib_LeaveCriticalSection(void);
#ifdef DEBUG
extern BOOL g_fCritical;
#endif
#define ENTERCRITICAL   Netlib_EnterCriticalSection();
#define LEAVECRITICAL   Netlib_LeaveCriticalSection();
#define ASSERTCRITICAL  ASSERT(g_fCritical);

