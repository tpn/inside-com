/*****************************************************************/
/**               Microsoft Windows 4.00                        **/
/**           Copyright (C) Microsoft Corp., 1995-1996          **/
/*****************************************************************/

/* WPTEST.CPP - Test provider with COM interface
 *
 */

#include "wbprov.h"

#pragma data_seg(DATASEG_PERINSTANCE)

HANDLE g_hmtxShell = 0;              // Note: Handle is per-instance.

#ifdef DEBUG
BOOL g_fCritical=FALSE;
#endif

extern "C" HANDLE g_hInstance = NULL;
#pragma data_seg(DATASEG_DEFAULT)

const char szMutexName[] = "WPtestProviderMutex";

UINT g_cRefThisDll = 0;     // Reference count of this DLL.
UINT g_cLocks = 0;          // Number of locks on this server.

//
// Shared Global data (32-bit only)
//
BOOL g_cProcesses = 0;


void LockThisDLL(BOOL fLock)
{
    ENTERCRITICAL
    {
        if (fLock)
            g_cLocks++;
        else
            g_cLocks--;
    }
    LEAVECRITICAL
}


void RefThisDLL(BOOL fRef)
{
    ENTERCRITICAL
    {
        if (fRef)
            g_cRefThisDll++;
        else
            g_cRefThisDll--;
    }
    LEAVECRITICAL
}


void Netlib_EnterCriticalSection(void)
{
    WaitForSingleObject(g_hmtxShell, INFINITE);
#ifdef DEBUG
    g_fCritical=TRUE;
#endif
}

void Netlib_LeaveCriticalSection(void)
{
#ifdef DEBUG
    g_fCritical=FALSE;
#endif
    ReleaseMutex(g_hmtxShell);
}

//
// Initializes shared data (16-bit/32-bit common: once per DLL)
//
BOOL WINAPI _Initialize_SharedData(void)
{
    return TRUE;
}

//
// Clean up shared data (16-bit/32-bit common : once per-DLL)
//
BOOL WINAPI _Terminate_SharedData(void)
{
    return TRUE;
}


BOOL _ProcessAttach(HINSTANCE hDll)
{
    BOOL fSuccess = TRUE;

    //
    // All the per-instance initialization code should come here.
    //
    //
    g_hmtxShell = CreateMutex(NULL, FALSE, ::szMutexName);  // per-instance

    ::g_hInstance = hDll;

    ENTERCRITICAL
    {
        if (g_cProcesses++==0)
        {
            fSuccess = _Initialize_SharedData();
        }
    }
    LEAVECRITICAL

    return fSuccess;
}

BOOL _ProcessDetach(HINSTANCE hDll) // 32-bit
{

    BOOL fSuccess = TRUE;

    ENTERCRITICAL
    {
        if (--g_cProcesses==0)
        {
            fSuccess=_Terminate_SharedData();
        }
    }
    LEAVECRITICAL

    CloseHandle(g_hmtxShell);

    return fSuccess;
}


//
// Class factory object
//
//

STDMETHODIMP WPPClassFactory::QueryInterface(
    /* [in] */ REFIID riid,
    /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
{
    *ppvObject = NULL;

    if (IsEqualIID(riid, IID_IUnknown) ||
        IsEqualIID(riid, IID_IClassFactory)) {
        *ppvObject = (LPVOID)this;
        AddRef();
        return NOERROR;
    }
    return ResultFromScode(E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) WPPClassFactory::AddRef(void)
{
    RefThisDLL(TRUE);

    return 1;
}


STDMETHODIMP_(ULONG) WPPClassFactory::Release(void)
{
    RefThisDLL(FALSE);

    return 1;
}


HRESULT CreateProvider(REFIID riid, void **ppOut)
{
    return ResultFromScode(E_NOTIMPL);
}


STDMETHODIMP WPPClassFactory::CreateInstance(
    /* [unique][in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
{
    if (NULL != pUnkOuter)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    return CreateProvider (riid, ppvObject);
}


STDMETHODIMP WPPClassFactory::LockServer(
    /* [in] */ BOOL fLock)
{
    LockThisDLL(fLock);

    return NOERROR;
}


//
// Following are standard global functions, needed for DLL initialization
// and OLE infrastructure support. THey are exported by name , thus should be declared
// as undecorated
//

extern "C" {

BOOL
_stdcall
DllEntryPoint(
    HINSTANCE hInstDll,
    DWORD fdwReason,
    LPVOID reserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
        return _ProcessAttach(hInstDll);
    else if (fdwReason == DLL_PROCESS_DETACH) {
        return _ProcessDetach(hInstDll);
    }

    g_hInstance = hInstDll;

    return TRUE;
}

BOOL
_stdcall
DllMain(
    HINSTANCE hInstDll,
    DWORD fdwReason,
    LPVOID reserved)
{
    return DllEntryPoint(hInstDll,fdwReason,reserved);
}

STDAPI DllCanUnloadNow(void)
{
    SCODE sc;

    sc = (0 == g_cRefThisDll && 0 == g_cLocks) ? S_OK : S_FALSE;
    return ResultFromScode(sc);
}


STDAPI DllGetClassObject(
    REFCLSID rclsid,
    REFIID riid,
    LPVOID FAR *ppv)
{
    if (!IsEqualCLSID(rclsid, CLSID_WPProvider)) {
        return ResultFromScode(E_FAIL);
    }

    if (!IsEqualIID(riid, IID_IUnknown) &&
        !IsEqualIID(riid, IID_IClassFactory)) {
        return ResultFromScode(E_NOINTERFACE);
    }

    static WPPClassFactory cf;

    *ppv = (LPVOID)&cf;

    cf.AddRef();

    return NOERROR;
}

};  /* extern "C" */


