// ===========================================================================
// File: P R O G R E S S . C P P
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Description:
//
//  This sample demonstrates using a URL moniker to download information.
// The key routines include the implementation of IBindStatusCallback
// and the CDownload::DoDownload routine, which creates and binds to the
// URL moniker.
//
// Instructions:
//
//  To use this sample:
//   * build it using the NMAKE command. NMAKE will create PROGRESS.EXE.
//   * run PROGRESS.EXE. specify the resource to download by passing an
//     URL on the command-line. use no command-line argument to default to
//     downloading "http://www.msn.com".
//  * The program displays a dialog box containing information about the
//    download:
//     - a status message, describing the current status of the download
//     - a progress message, describing the amount of information that
//       has been downloaded.
//     - a text box, which displays chunks of the download information as
//       it arrives.
//  * Press the "GO" button to begin the download.
//
// Sample update:-
//   * New feature include Progress Bar to indicated progress of the download
//	 * Edit box replaces the old text box. Also the whole file can be viewed. 
//     If the file exceeds 32KB then only the first 32 KB from the last data
//	   pull will be displayed.  If the pull exceeds 32 KB, then only the first
//     32 KB of the last Read will be displayed.
// 
///
// File updated by Jobi George 19-June-1996
// File updated by Ramesha Gopalakrishna 28-June-1996
// File updated by Oliver Wallace 9-July-1996
// Copyright 1995-1996 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================
#include "urlmon.h"
#include "wininet.h"
#include "resource.h"
#include "commctrl.h"

#define EDIT_BOX_LIMIT 0x7FFF    //  The Edit box limit

// %%Classes: ----------------------------------------------------------------
class CDownload {
  public:
    CDownload(LPCWSTR szURL);
    ~CDownload();
    HRESULT DoDownload(HWND,HWND,HWND,HWND);
    LPCWSTR              m_url;

  private:
    IMoniker*            m_pmk;
    IBindCtx*            m_pbc;
    IBindStatusCallback* m_pbsc;
};

class CBindStatusCallback : public IBindStatusCallback {
  public:
    // IUnknown methods
    STDMETHODIMP    QueryInterface(REFIID riid,void ** ppv);
    STDMETHODIMP_(ULONG)    AddRef()    { return m_cRef++; }
    STDMETHODIMP_(ULONG)    Release()   { if (--m_cRef == 0) { delete this; return 0; } return m_cRef; }

    // IBindStatusCallback methods
    STDMETHODIMP    OnStartBinding(DWORD dwReserved, IBinding* pbinding);
    STDMETHODIMP    GetPriority(LONG* pnPriority);
    STDMETHODIMP    OnLowResource(DWORD dwReserved);
    STDMETHODIMP    OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode,
                        LPCWSTR pwzStatusText);
    STDMETHODIMP    OnStopBinding(HRESULT hrResult, LPCWSTR szError);
    STDMETHODIMP    GetBindInfo(DWORD* pgrfBINDF, BINDINFO* pbindinfo);
    STDMETHODIMP    OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC *pfmtetc,
                        STGMEDIUM* pstgmed);
    STDMETHODIMP    OnObjectAvailable(REFIID riid, IUnknown* punk);

    // constructors/destructors
    CBindStatusCallback(HWND hwndStatus, HWND hwndProgress, HWND hwndText, HWND hwndProgressBar);
    ~CBindStatusCallback();

    inline void SetStatus(LPCWSTR szStatus)     { SetWndText(m_hwndStatus, szStatus); }
    void SetProgress(LPCWSTR szProgress)        { SetWndText(m_hwndProgress, szProgress); }
	void SetProgressBar(ULONG cProgress, ULONG maxProgress) 
	{
		// Set the range and increment of the progress bar. 
		SendMessage(m_hwndProgressBar, PBM_SETRANGE, 0, 100); 
        SendMessage(m_hwndProgressBar, PBM_SETPOS, (WPARAM) (maxProgress ? cProgress * 100 / maxProgress : 0), 0);
	}
    void SetWndText(HWND hwnd, LPCWSTR szText);

    // data members
    DWORD           m_cRef;
    IBinding*       m_pbinding;
    IStream*        m_pstm;
    HWND            m_hwndStatus;
    HWND            m_hwndProgress;
    HWND            m_hwndText;
	HWND			m_hwndProgressBar;
    DWORD           m_cbOld;
};


// ===========================================================================
//                     CBindStatusCallback Implementation
// ===========================================================================

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::CBindStatusCallback
// ---------------------------------------------------------------------------
CBindStatusCallback::CBindStatusCallback(HWND hwndStatus, HWND hwndProgress, HWND hwndText, HWND hwndProgressBar)
{
    m_hwndStatus = hwndStatus;
    m_hwndProgress = hwndProgress;
    m_hwndText = hwndText;
	m_hwndProgressBar = hwndProgressBar;
    m_pbinding = NULL;
    m_pstm = NULL;
    m_cRef = 1;
    m_cbOld = 0;
}  // CBindStatusCallback

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::~CBindStatusCallback
// ---------------------------------------------------------------------------
CBindStatusCallback::~CBindStatusCallback()
{
}  // ~CBindStatusCallback

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::SetWndText
// ---------------------------------------------------------------------------
 inline void
CBindStatusCallback::SetWndText(HWND hwnd,LPCWSTR szText)
{
    if (IsWindow(hwnd))
        {
        char    rgchBuf[INTERNET_MAX_PATH_LENGTH];
        WideCharToMultiByte(CP_ACP, 0, szText, -1, rgchBuf, INTERNET_MAX_PATH_LENGTH, 0, 0);
	SetWindowText(hwnd, rgchBuf);
	}
}  // CBindStatusCallback::SetWndText

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
CBindStatusCallback::OnStartBinding(DWORD dwReserved, IBinding* pbinding)
{
    if (m_pbinding != NULL)
        m_pbinding->Release();
    m_pbinding = pbinding;
    if (m_pbinding != NULL)
        {
        m_pbinding->AddRef();
        SetStatus(L"Status: Starting to bind...");
        }
    return S_OK;
}  // CBindStatusCallback::OnStartBinding

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::GetPriority
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::GetPriority(LONG* pnPriority)
{
	return E_NOTIMPL;
}  // CBindStatusCallback::GetPriority

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnLowResource
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::OnLowResource(DWORD dwReserved)
{
    return E_NOTIMPL;
}  // CBindStatusCallback::OnLowResource

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnProgress
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
{
    char    sz[255];

	if(szStatusText!=NULL)
	    WideCharToMultiByte(CP_ACP, 0, szStatusText,-1, sz, 255, 0,0);

    char    msg[100];
    WCHAR   out[200];

    wsprintf(msg,"Progress: %s %d of %d ", sz, ulProgress, (ulProgress>ulProgressMax)?ulProgress:ulProgressMax);
    MultiByteToWideChar(CP_ACP, 0, msg, -1, out, sizeof(out));

    SetProgress(out);
	SetProgressBar(ulProgress, ulProgressMax);
    return(NOERROR);
}  // CBindStatusCallback::OnProgress

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnStopBinding
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::OnStopBinding(HRESULT hrStatus, LPCWSTR pszError)
{
    if (hrStatus)
        SetStatus(L"Status: File download Failed.");

	if (m_pbinding)
	{
		m_pbinding->Release();
		m_pbinding = NULL;
	}

    return S_OK;
}  // CBindStatusCallback::OnStopBinding

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::GetBindInfo
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::GetBindInfo(DWORD* pgrfBINDF, BINDINFO* pbindInfo)
{
    *pgrfBINDF = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA;
    *pgrfBINDF |= BINDF_GETNEWESTVERSION | BINDF_NOWRITECACHE;
    pbindInfo->cbSize = sizeof(BINDINFO);
    pbindInfo->szExtraInfo = NULL;
    memset(&pbindInfo->stgmedData, 0, sizeof(STGMEDIUM));
    pbindInfo->grfBindInfoF = 0;
    pbindInfo->dwBindVerb = BINDVERB_GET;
    pbindInfo->szCustomVerb = NULL;
    return S_OK;
}  // CBindStatusCallback::GetBindInfo

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnDataAvailable
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pfmtetc, STGMEDIUM* pstgmed)
{
	 HRESULT hr=S_OK;
	 DWORD dStrlength=0;

	// Get the Stream passed
    if (BSCF_FIRSTDATANOTIFICATION & grfBSCF)
    {
        if (!m_pstm && pstgmed->tymed == TYMED_ISTREAM)
	    {
		    m_pstm = pstgmed->pstm;
            if (m_pstm)
                m_pstm->AddRef();
    	}
    }

    // If there is some data to be read then go ahead and read them
    if (m_pstm && dwSize > m_cbOld)
	{
        DWORD dwRead = dwSize - m_cbOld; // Minimum amount available that hasn't been read
        DWORD dwActuallyRead = 0;            // Placeholder for amount read during this pull

		if (dwRead > 0)
		do
		{
	        char * pNewstr = new char[dwRead + 1];
			if (pNewstr==NULL)
				return S_FALSE;
			hr=m_pstm->Read(pNewstr,dwRead,&dwActuallyRead);
		    pNewstr[dwActuallyRead] = 0;
			// If we really read something then lets add it to the Edit box
			if (dwActuallyRead>0)
			{
				dStrlength=GetWindowTextLength(m_hwndText);

				char *pOldstr=NULL;
				if (dwActuallyRead>=EDIT_BOX_LIMIT)  // Read exceeded Edit box size
				{
					pOldstr= new char[EDIT_BOX_LIMIT];
					if (pOldstr==NULL)
					{
						delete[] pNewstr;	
						return S_FALSE;
					}
					lstrcpyn(pOldstr,pNewstr,EDIT_BOX_LIMIT-1);
				}
                else if (dStrlength + dwActuallyRead >= EDIT_BOX_LIMIT)
                {
                    // This pull exceeded the edit box size.  Only copy the last read.
                    pOldstr = new char[dwActuallyRead+1];
                    if (pOldstr==NULL)
                    {
                        delete[] pNewstr;
                        return S_FALSE;
                    }
                    lstrcpyn(pOldstr,pNewstr,dwActuallyRead);
                }
  				else
				{
					pOldstr= new char[dStrlength+dwActuallyRead+1];
					if (pOldstr==NULL)
					{
						delete[] pNewstr;
						return S_FALSE;
	 				}
					GetWindowText(m_hwndText,pOldstr,(dStrlength+dwActuallyRead+1));
					lstrcat(pOldstr,pNewstr);
				}
		        SetWindowText(m_hwndText,pOldstr);
				m_cbOld += dwActuallyRead;
				delete[] pOldstr;
			}
			delete[] pNewstr;

                } while (!(hr == E_PENDING || hr == S_FALSE) && SUCCEEDED(hr));
	}//     if (m_pstm && dwSize > m_cbOld)

	if (BSCF_LASTDATANOTIFICATION & grfBSCF)
	{
        if (m_pstm)
            m_pstm->Release();
		hr=S_OK;  // If it was the last data then we should return S_OK as we just finished reading everything
        SetStatus(L"Status: File downloaded.");
	}

    return hr;
}  // CBindStatusCallback::OnDataAvailable

// ---------------------------------------------------------------------------
// %%Function: CBindStatusCallback::OnObjectAvailable
// ---------------------------------------------------------------------------
 STDMETHODIMP
CBindStatusCallback::OnObjectAvailable(REFIID riid, IUnknown* punk)
{
    return E_NOTIMPL;
}  // CBindStatusCallback::OnObjectAvailable


// ===========================================================================
//                           CDownload Implementation
// ===========================================================================

// ---------------------------------------------------------------------------
// %%Function: CDownload::CDownload
// ---------------------------------------------------------------------------
CDownload::CDownload(LPCWSTR szURL)
{
    m_url = szURL;
    m_pmk = 0;
    m_pbc = 0;
    m_pbsc = 0;
}  // CDownload

// ---------------------------------------------------------------------------
// %%Function: CDownload::~CDownload
// ---------------------------------------------------------------------------
CDownload::~CDownload()
{
    if (m_pmk)
        m_pmk->Release();
    if (m_pbc)
        m_pbc->Release();
    if (m_pbsc)
        m_pbsc->Release();
}  // ~CDownload

// ---------------------------------------------------------------------------
// %%Function: CDownload::DoDownload
// ---------------------------------------------------------------------------
 HRESULT
CDownload::DoDownload(HWND hwndStatus, HWND hwndProgress, HWND hwndText, HWND hwndProgressBar)
{
    IStream* pstm = NULL;
    HRESULT hr;

    hr = CreateURLMoniker(NULL, m_url, &m_pmk);
    if (FAILED(hr))
        goto LErrExit;

    m_pbsc = new CBindStatusCallback(hwndStatus, hwndProgress, hwndText, hwndProgressBar);
    if (m_pbsc == NULL)
        {
        hr = E_OUTOFMEMORY;
        goto LErrExit;
        }

    hr = CreateBindCtx(0, &m_pbc);
    if (FAILED(hr))
        goto LErrExit;

    hr = RegisterBindStatusCallback(m_pbc,
            m_pbsc,
            0,
            0L);
    if (FAILED(hr))
        goto LErrExit;

    hr = m_pmk->BindToStorage(m_pbc, 0, IID_IStream, (void**)&pstm);
    if (FAILED(hr))
        goto LErrExit;

    return hr;

LErrExit:
    if (m_pbc != NULL)
        {
        m_pbc->Release();
        m_pbc = NULL;
        }
    if (m_pbsc != NULL)
        {
        m_pbsc->Release();
        m_pbsc = NULL;
        }
    if (m_pmk != NULL)
        {
        m_pmk->Release();
        m_pmk = NULL;
        }
	if (pstm)
		{
		pstm->Release();
		pstm = NULL;
		}
    return hr;
}  // CDownload::DoDownload


// ===========================================================================
//                  User Interface and Initialization Routines
// ===========================================================================

// ---------------------------------------------------------------------------
// %%Function: DialogProc
// ---------------------------------------------------------------------------
 BOOL CALLBACK
DialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static CDownload* pcdl = NULL;

    switch(message)
        {
        case WM_INITDIALOG:
            EnableWindow(GetDlgItem(hwndDlg, IDOK), TRUE);
            EnableWindow(GetDlgItem(hwndDlg, IDCANCEL), TRUE);
            pcdl = (CDownload*)(LPVOID)(lParam);
            break;

        case WM_COMMAND:
            {
            switch (LOWORD(wParam))
                {
                case IDOK:
                    {
                    char rgchBuf[INTERNET_MAX_PATH_LENGTH];
                    HWND hwndStatus = GetDlgItem(hwndDlg, IDC_DISPLAY);
                    HWND hwndProgress = GetDlgItem(hwndDlg, IDC_PROGRESS);
                    HWND hwndText = GetDlgItem(hwndDlg, IDC_EDIT);
					HWND hwndProgressBar = GetDlgItem(hwndDlg, IDC_PROGRESSBAR);

                    EnableWindow(GetDlgItem(hwndDlg, IDOK), FALSE);
                    EnableWindow(GetDlgItem(hwndDlg, IDCANCEL), FALSE);

                    WideCharToMultiByte(CP_ACP, 0, pcdl->m_url, -1, rgchBuf, MAX_PATH, 0, 0);
		            SetWindowText(hwndDlg, rgchBuf);

                    SetWindowText(hwndStatus, TEXT("Status: Initiating Bind..."));
                    pcdl->DoDownload(hwndStatus, hwndProgress, hwndText, hwndProgressBar);
                    EnableWindow(GetDlgItem(hwndDlg, IDCANCEL), TRUE);
                    break;
                    }

                case IDCANCEL:
                    EndDialog(hwndDlg,0);
                    return 1;
                }
            break;
            }
        }

    return 0;
}  // DialogProc

// ---------------------------------------------------------------------------
// %%Function: WinMain
// ---------------------------------------------------------------------------
 int WINAPI
WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR szCmdLine, int nCmdShow)
{
    static WCHAR    szDefaultURL[] = L"http://www.msn.com";
    WCHAR           rgwchCmdLine[MAX_PATH];
    HRESULT         hr;

	InitCommonControls();

    hr = CoInitialize(NULL);
    if (FAILED(hr))
        return hr;

    MultiByteToWideChar(CP_ACP, 0, szCmdLine, -1, rgwchCmdLine, MAX_PATH);

    CDownload download(rgwchCmdLine[0] ? rgwchCmdLine : szDefaultURL);

    int x = DialogBoxParam(hinst, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP,
        (FARPROC)&DialogProc, (LPARAM)(LPVOID)&download);

    CoUninitialize();

    return 0;
}  // WinMain

// EOF =======================================================================

