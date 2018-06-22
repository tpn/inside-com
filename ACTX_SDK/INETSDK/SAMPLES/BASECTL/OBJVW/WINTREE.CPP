#include "ipserver.h"
#include "treeui.h"
#include "exdisp.h"
#include "wintree.h"


SZTHISFILE

//=--------------------------------------------------------------------------=
// CWinTree::CWinTree
//=--------------------------------------------------------------------------=
// Windows tree contructor
//
// Parameters:
//
// Output:
//
// Notes:
//
CWinTree::CWinTree()
{
	m_pwindRoot = NULL;
	m_pTreeUI = NULL;
    m_cWin = 1; // one for main document
}


//=--------------------------------------------------------------------------=
// CWinTree::~CWinTree
//=--------------------------------------------------------------------------=
// Windows tree destructor
//
// Parameters:
//
// Output:
//
// Notes:
//		BUGBUG free stuff up
//
CWinTree::~CWinTree()
{
    // Reset first
    Reset();

    KillPtr(m_pwinqueue);

}


//=--------------------------------------------------------------------------=
// CWinTree::Reset
//=--------------------------------------------------------------------------=
// Reset the tree, in other words delete all the nodes and such
//
// Parameters:
//		IWebBrowser* pIWebBrowser	-	[in] pointer to top level IWebBrowser from the 
//										browser
//		CTreeUI* pTreeUI			-	[in] pointer to tree ui class	
//
// Output:
//		HRESULT NOERROR, E_FAIL, E_OUTOFMEMORY, E_NOINTERFACE
//
// Notes:
//      This calls CTreeUI::KillTreeItems to get rid of the visual display as well
//
void CWinTree::Reset()
{
    CWinStack   stack;
    LONG        i;

    // Walk the tree deleting the window structures
    stack.Push(m_pwindRoot);
    while ( !stack.Empty() )
    {
        CWindow* pwin;

        pwin = stack.Pop();
        ASSERT(pwin, "Must have valid window on stack");

        if ( !pwin->m_lFrameCount )
            delete pwin;
        else
        {
            for(i = 0; i < pwin->m_lFrameCount; i++)
            {
                stack.Push(pwin->m_rgpwindFrames[i]);
            }
            delete pwin;
        }
    }

    // Reset the variables
    m_pwindRoot = NULL;
    m_cWin = 1;

    // Get rid of the UI tree items
    m_pTreeUI->KillTreeItems();
}


//=--------------------------------------------------------------------------=
// CWinTree::BuildTree
//=--------------------------------------------------------------------------=
// Build window tree
//
// Parameters:
//		IWebBrowser* pIWebBrowser	-	[in] pointer to top level IWebBrowser from the 
//										browser
//		CTreeUI* pTreeUI			-	[in] pointer to tree ui class	
//
// Output:
//		HRESULT NOERROR, E_FAIL, E_OUTOFMEMORY, E_NOINTERFACE
//
// Notes:
//
HRESULT CWinTree::BuildTree
(
	IWebBrowser*	pIWebBrowser,
	CTreeUI*		pTreeUI
)
{
	HRESULT			hr = NOERROR;

	ASSERT(pIWebBrowser, "Must have valid IWebBrowser");

    // Set UI tree member
    m_pTreeUI = pTreeUI;

	// Create CWindow wrapper
	m_pwindRoot = new CWindow(pIWebBrowser);
	IfMemFailHRGoto(m_pwindRoot);

	// Create queue and put on first element
	m_pwinqueue = new CWinQueue;
	IfMemFailHRGoto(m_pwinqueue);
	IfComFailGoto(m_pwinqueue->Put(m_pwindRoot));

    // Add root UI node
    IfComFailGoto(AddUIParentNode(m_pwindRoot));

	// while the queue is not empty 
	while ( !m_pwinqueue->Empty() )
	{
		CWindow*	pwin;

		// Get element from queue
		pwin = m_pwinqueue->Get();
		ASSERT(pwin, "Should be valid window");

		// Get OleContainer and IOmWindow pointer if they exist
		IfComFailGoto(GetOleContainerAndWindow(pwin));

		// Enumerate frames
		IfComFailGoto(EnumerateFrames(pwin));

		// Enumerate controls
		IfComFailGoto(EnumerateControls(pwin));
	}
	
done:
	KillPtr(m_pwinqueue);
	return hr;
}


//=--------------------------------------------------------------------------=
// CWinTree::GetOleContainerAndWindow [helper]
//=--------------------------------------------------------------------------=
// Get the IOleContainer and IOmWindow of the current browser document
// if they exist and associate them with the window class
//
// Parameters:
//		CWindow* pwin	-	[in] pointer to window class that will have its members set
//
// Output:
//		HRESULT NOERROR, E_NOINTERFACE, E_FAIL
//
// Notes:
//		The way this works is there are 3 levels of Automation objects.  The IOmWindow interface
//		represents the lowest level and is the root of the scripting model.  The next level is
//		the browser document level.  This is the Automation model on the current doc object 
//		within the IE doc object container if there is one.  In the case of the mshtml doc object
//		that is used for most mime types, this is a control container as well and you can get the
//		IOleContainer interface to enumerate its controls.  The top level is the Automation 
//		interface for the doc object container (the webbrowser control). 
//
//		The IWebBrowser member of the CWindow class must be set before this is called
//
HRESULT CWinTree::GetOleContainerAndWindow
(
	CWindow* pwin
)
{
	HRESULT				hr = NOERROR;
	LPDISPATCH			pIDisp = NULL;
    OLECHAR*            rgwzScript[] = {OLESTR("Script")};
    DISPID              rgdispidScript[1];
    DISPPARAMS          dp;
    VARIANT             vtres;

	// Get document Automation model
	ASSERT(pwin->m_pIWebBrowser, "Must have valid webbrowser interface");
	IfComFailRet(pwin->m_pIWebBrowser->get_Document(&pIDisp));

	// Ask for IOleContainer, if its not there that's okay we just have something like a word
	// document
	hr = pIDisp->QueryInterface(IID_IOleContainer, (void **)&pwin->m_pIOleCtn);
	if ( ResultFromScode(E_NOINTERFACE) == hr )
		hr = NOERROR;
	else if ( FAILED(hr) )
		goto done;

	// We can ask for IOmWindow
    hr = pIDisp->GetIDsOfNames(
        IID_NULL, rgwzScript, 1, LOCALE_SYSTEM_DEFAULT, rgdispidScript);
    if ( FAILED(hr) )
    {
        hr = NOERROR;
        goto done;
    }
    ZeroMemory(&dp, sizeof(DISPPARAMS));
    VariantInit(&vtres);
    hr = pIDisp->Invoke(
        rgdispidScript[0], IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vtres, 
        NULL, NULL);
    if ( FAILED(hr) )
    {
        hr = NOERROR;
        goto done;
    }
    pwin->m_pIOmWindow = V_DISPATCH(&vtres);
    pwin->m_pIOmWindow->AddRef();
    VariantClear(&vtres);

done:
	ReleaseInterface(pIDisp);

	return hr;
}


//=--------------------------------------------------------------------------=
// CWinTree::EnumerateFrames [helper]
//=--------------------------------------------------------------------------=
// Get the window's frames and create an array of window objects for them
//
// Parameters:
//		CWindow* pwin	-	[in] pointer to window class that will have its members set
//
// Output:
//		HRESULT NOERROR, E_NOINTERFACE, E_FAIL
//
// Notes:
//		This uses the IOmFramesCollection to enumerate all this window's immediate frames 
//
//		Of course there will only be frames if the current browser document is a mshtml doc
//		this is defined by there being a valid IOmWindow interface pointer to it.
//
HRESULT CWinTree::EnumerateFrames
(
	CWindow*	pwin
)
{
	HRESULT					hr = NOERROR;
	LPDISPATCH	            pIOmFrames = NULL;
	LPDISPATCH				pIOmWindow = NULL;
	IDispatch*				pIDisp = NULL;
	IWebBrowserApp*			pIWebBrowserApp = NULL;
	long					i;
    DISPPARAMS              dp;
    OLECHAR*                rgwzFrames[] = {OLESTR("frames")};
    OLECHAR*                rgwzCount[] = {OLESTR("Count")};
    OLECHAR*                rgwzItem[] = {OLESTR("Item")};
    OLECHAR*                rgwzExplorer[] = {OLESTR("explorer")};
    DISPID                  rgdispidFrames[1];
    DISPID                  rgdispidCount[1];
    DISPID                  rgdispidItem[1];
    DISPID                  rgdispidExplorer[1];
    VARIANT                 vtres;

	// If no script window then no frames
	if ( !pwin->m_pIOmWindow )
		return NOERROR;

	// Get the frames collection and count of frames
    IfComFailRet(pwin->m_pIOmWindow->GetIDsOfNames(
        IID_NULL, rgwzFrames, 1, LOCALE_SYSTEM_DEFAULT, rgdispidFrames));
    ZeroMemory(&dp, sizeof(DISPPARAMS));
    VariantInit(&vtres);
    IfComFailGoto(pwin->m_pIOmWindow->Invoke(
        rgdispidFrames[0], IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, 
        &dp, &vtres, NULL, NULL));
    pIOmFrames = V_DISPATCH(&vtres);
    pIOmFrames->AddRef();
    VariantClear(&vtres);

    IfComFailGoto(pIOmFrames->GetIDsOfNames(
        IID_NULL, rgwzCount, 1, LOCALE_SYSTEM_DEFAULT, rgdispidCount));
    VariantInit(&vtres);
    IfComFailGoto(pIOmFrames->Invoke(
        rgdispidCount[0], IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, 
        &dp, &vtres, NULL, NULL));
    pwin->m_lFrameCount = V_I4(&vtres);
    VariantClear(&vtres);


	// Allocate array of frame window pointers on the window object
	pwin->m_rgpwindFrames = new CWindow*[pwin->m_lFrameCount];
	IfMemFailHRGoto(pwin->m_rgpwindFrames);

	// enumerate frames
	for (i = 0; i < pwin->m_lFrameCount; i++)
	{
		// Get pointer to sub window IWebBrowser
		VARIANT	vt;
		V_VT(&vt) = VT_I4;
		V_I4(&vt) = i;
        IfComFailGoto(pIOmFrames->GetIDsOfNames(
            IID_NULL, rgwzItem, 1, LOCALE_SYSTEM_DEFAULT, rgdispidItem));
        dp.rgvarg = &vt;
        dp.cArgs = 1;
        dp.cNamedArgs = 0;
        dp.rgdispidNamedArgs = 0;
        VariantInit(&vtres);
        IfComFailGoto(pIOmFrames->Invoke(
            rgdispidItem[0], IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD,
            &dp, &vtres, NULL, NULL));
        pIOmWindow = V_DISPATCH(&vtres);
        pIOmWindow->AddRef();
        VariantClear(&vtres);

        IfComFailGoto(pIOmWindow->GetIDsOfNames(
            IID_NULL, rgwzExplorer, 1, LOCALE_SYSTEM_DEFAULT, rgdispidExplorer));
        VariantInit(&vtres);
        ZeroMemory(&dp, sizeof(DISPPARAMS));
        IfComFailGoto(pIOmWindow->Invoke(
            rgdispidExplorer[0], IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET,
            &dp, &vtres, NULL, NULL));
        pIDisp = V_DISPATCH(&vtres);
        pIDisp->AddRef();
        VariantClear(&vtres);

		IfComFailGoto(pIDisp->QueryInterface(IID_IWebBrowserApp, 
			(void **)&pIWebBrowserApp));
		ReleaseInterface(pIDisp);

		// Allocate new sub window
		pwin->m_rgpwindFrames[i] = new CWindow(pIWebBrowserApp);
		IfMemFailHRGoto(pwin->m_rgpwindFrames[i]);
        
        // Fill in frame index
        pwin->m_rgpwindFrames[i]->m_lidx = m_cWin;

        // Fill in window parent UI tree node
        pwin->m_rgpwindFrames[i]->m_pvParentTree = pwin->m_pvTree;

        // Add UI node for frame
        IfComFailGoto(AddUIParentNode(pwin->m_rgpwindFrames[i]));

		// Add the window to the queue so that it gets processed as well
		IfComFailGoto(m_pwinqueue->Put(pwin->m_rgpwindFrames[i]));

        // increment total frame count
        m_cWin++;
	}

done:
	ReleaseInterface(pIOmWindow);
	ReleaseInterface(pIOmFrames);
	ReleaseInterface(pIDisp);
	return hr;
}


//=--------------------------------------------------------------------------=
// CWinTree::EnumerateControls [helper]
//=--------------------------------------------------------------------------=
// Use the control container pointer to walk through all of the controls
//
// Parameters:
//      CWindow* pwin   -   [in] pointer to window class
//
// Output:
//		HRESULT NOERROR
//
// Notes:
//      BUGBUG
//      It turns out that frames on the page are instances of the shdocvw control.  Thus the
//      frames will be enumerated here as controls as well.  To get around this I query the 
//      control for IWebBrowserApp.  If its there I pretend it is a frame. This has the 
//      limitation that if someone embeds a control that implements IWebBrowserApp on the page, 
//      I will erroneously think it is a frame and not include it in the list.
//
HRESULT CWinTree::EnumerateControls
(
    CWindow*    pwind
)
{
    HRESULT         hr = NOERROR;
    LPDISPATCH      pdisp = NULL;
    IEnumUnknown*   pIEnumUnk = NULL;
    LPUNKNOWN       pIUnk = NULL;
    UINT            cControls = 0;
    IWebBrowser*    pIWebBrowser = NULL;
    char            szControlInfo[TV_MAXSTRLEN];

    // check that we have an IOleCtn, if we don't then leave
    if ( !pwind->m_pIOleCtn )
        return NOERROR;

    // Use container to enumerate controls
	IfComFailGoto(pwind->m_pIOleCtn->EnumObjects(
		OLECONTF_EMBEDDINGS | OLECONTF_ONLYIFRUNNING | OLECONTF_OTHERS, &pIEnumUnk));
	while ( TRUE )
	{
		IfComFailGoto(pIEnumUnk->Next(1, &pIUnk, NULL));
		if ( S_FALSE == hr )
		{
			hr = NOERROR;
			break;
		}
		if ( SUCCEEDED(pIUnk->QueryInterface(IID_IWebBrowser, (void **)&pIWebBrowser)) )
        {
            ReleaseInterface(pIWebBrowser);
        }
		else
        {
            // Get control info
            IfComFailGoto(GetControlInfo(pIUnk, szControlInfo));

            // Add to the tree view control
            IfComFailGoto(m_pTreeUI->InsertItem(szControlInfo, pwind->m_pvTree, NULL));
        }
        ReleaseInterface(pIUnk);
	}
done:
    ReleaseInterface(pIWebBrowser);
    ReleaseInterface(pIEnumUnk);
    ReleaseInterface(pIUnk);
    ReleaseInterface(pdisp);
    if ( FAILED(hr) && (ResultFromScode(E_UNEXPECTED) != hr))
    {
        strcpy(szControlInfo, TV_SZNOCTN);
        m_pTreeUI->InsertItem(szControlInfo, pwind->m_pvTree, NULL);
    }
    return NOERROR;
}


//=--------------------------------------------------------------------------=
// CWinTree::GetControlInfo [helper]
//=--------------------------------------------------------------------------=
// Gets control info and formats a string for display in the tv control
//
// Parameters:
//      LPUNKNOWN punk          -   [in] unknown pointer on the control
//      LPSTR szClassInfo       -   [out] control information buffer
//
// Output:
//		HRESULT NOERROR
//
// Notes:
//
HRESULT CWinTree::GetControlInfo
(
    LPUNKNOWN   punk,
    LPSTR       szClassInfo
)
{
    HRESULT             hr = NOERROR;
    CLSID               clsid;
    ITypeInfo*          pITypeInfo = NULL;
    IProvideClassInfo*  pIProvideClassInfo = NULL;
    TYPEATTR*           pTypeAttr = NULL;
    IProvideClassInfo2* pIProvideClassInfo2 = NULL;
    IDispatch*          pdisp = NULL;
    OLECHAR*            rgszNames[1] = {OLESTR("name")};
    DISPID              rgdispidNames[1];
    DISPPARAMS          dp;
    VARIANT             vtres;
	IOleClientSite*		pIOleClientSite = NULL;
	IOleObject*			pIOleObject = NULL;

    // Get IProvideClassInfo2 or IProvideClassInfo
    while (TRUE)
    {
        IfFailBreak(punk->QueryInterface(IID_IProvideClassInfo2, 
            (void **)&pIProvideClassInfo2));
        IfFailBreak(pIProvideClassInfo2->GetGUID(GUIDKIND_CLSID, &clsid));
        break;
    }

    while ( FAILED(hr) )
    {
        hr = NOERROR;
        IfFailBreak(punk->QueryInterface(IID_IProvideClassInfo, 
            (void **)&pIProvideClassInfo));
        IfFailBreak(pIProvideClassInfo->GetClassInfo(&pITypeInfo));
        IfFailBreak(pITypeInfo->GetTypeAttr(&pTypeAttr));
        clsid = pTypeAttr->guid;
        break;
    }

    // At this point if we've failed, we need to set no class info
    if ( FAILED(hr) )
    {
        SetNoClassInfo(szClassInfo);
        hr = NOERROR;
    }
    // otherwise use the registry to set the class info
    else
        SetControlInfoFromReg(clsid, szClassInfo);

    // Try to get ambient display name property from the container 
	// this is the ID or NAME in the object tag
    while (TRUE)
    {
        ZeroMemory(&dp, sizeof(DISPPARAMS));
        IfFailBreak(punk->QueryInterface(IID_IOleObject, (void **)&pIOleObject));
        IfFailBreak(pIOleObject->GetClientSite(&pIOleClientSite));
        IfFailBreak(pIOleClientSite->QueryInterface(IID_IDispatch, (void **)&pdisp));
        VariantInit(&vtres);
        V_VT(&vtres) = VT_BSTR;
        V_BSTR(&vtres) = SysAllocString(OLESTR(""));
        IfFailZeroBreak(V_BSTR(&vtres));
        IfFailBreak(pdisp->Invoke(
            DISPID_AMBIENT_DISPLAYNAME, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET,
            &dp, &vtres, NULL, NULL));
		hr = SetName(&vtres, szClassInfo);
		VariantClear(&vtres);
        break;
    }

    // Try to get dispatch interface and name property
    while ( FAILED(hr) )
    {
		ReleaseInterface(pdisp);
        IfFailBreak(punk->QueryInterface(IID_IDispatch, (void **)&pdisp));

        IfFailBreak(pdisp->GetIDsOfNames(
            IID_NULL, rgszNames, 1, LOCALE_SYSTEM_DEFAULT, rgdispidNames));
        VariantInit(&vtres);
        V_VT(&vtres) = VT_BSTR;
        V_BSTR(&vtres) = SysAllocString(OLESTR(""));
        IfFailZeroBreak(V_BSTR(&vtres));
        IfFailBreak(pdisp->Invoke(
            rgdispidNames[0], IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, 
            &dp, &vtres, NULL, NULL));
        hr = SetName(&vtres, szClassInfo);
        VariantClear(&vtres);

        break;
    }

    if ( FAILED(hr) )
        SetNoName(szClassInfo);

    if ( pTypeAttr )
    {
        pITypeInfo->ReleaseTypeAttr(pTypeAttr);
    }
    ReleaseInterface(pITypeInfo);
    ReleaseInterface(pIProvideClassInfo);
    ReleaseInterface(pIProvideClassInfo2);
    ReleaseInterface(pdisp);
	ReleaseInterface(pIOleObject);
	ReleaseInterface(pIOleClientSite);
    return NOERROR;
}


//=--------------------------------------------------------------------------=
// CWinTree::SetNoClassInfo [helper]
//=--------------------------------------------------------------------------=
// Copies over no class info string
//
// Parameters:
//      LPSTR  szClassInfo  -   [out] class info
//
// Output:
//
// Notes:
//
void CWinTree::SetNoClassInfo
(
    LPSTR  szClassInfo
)
{
    wsprintf(szClassInfo, "%s,", TV_SZNOCLASS);
}


//=--------------------------------------------------------------------------=
// CWinTree::SetNoName [helper]
//=--------------------------------------------------------------------------=
// Copies over no class name string
//
// Parameters:
//      LPSTR szClassInfo   -   [out] class info
//
// Output:
//
// Notes:
//
void CWinTree::SetNoName
(
    LPSTR   szClassInfo
)
{
    strcat(szClassInfo, TV_SZNONAME);
}


//=--------------------------------------------------------------------------=
// CWinTree::SetControlInfoFromReg [helper]
//=--------------------------------------------------------------------------=
// Looks up class id and gets description of control
//
// Parameters:
//      CLSID clsid - 
//      LPSTR szClassInfo  -   [out] class info
//
// Output:
//
// Notes:
//
void CWinTree::SetControlInfoFromReg
(
    CLSID   clsid,
    LPSTR   szClassInfo
)
{
    HRESULT     hr = NOERROR;
    HKEY        hkeyCLSID;
    LPOLESTR    bstrCLSID = NULL;
    UINT        cchCLSID;
    LPSTR       pszCLSID = NULL;
    const char* pszCLSIDKey = "CLSID\\";
    UINT        cchKey = strlen(pszCLSIDKey);
    LPSTR       pszInfo = NULL;
    LONG        cchVal;

    // Convert the clsid id into a string
    IfComFailGoto(StringFromCLSID(clsid, &bstrCLSID));
    cchCLSID = WideCharToMultiByte(
        CP_ACP, 0, bstrCLSID, -1, NULL, 0, NULL, NULL);
    pszCLSID = new char[cchCLSID+cchKey+1];
    strcpy(pszCLSID, pszCLSIDKey);
    IfMemFailHRGoto(pszCLSID);
    WideCharToMultiByte(
        CP_ACP, 0, bstrCLSID, -1, pszCLSID+cchKey, cchCLSID, NULL, NULL);

    // Find that key in the registry
    if  ( 
        !(ERROR_SUCCESS == 
            RegOpenKeyEx(HKEY_CLASSES_ROOT, pszCLSID, 0, KEY_ALL_ACCESS, &hkeyCLSID))
        )
    {
        goto done;
    }

    // Ask for its default value
    if ( ERROR_SUCCESS != (RegQueryValue(hkeyCLSID, NULL, NULL, &cchVal)) )
        goto done;
    pszInfo = new char[cchVal + 1];
    IfMemFailHRGoto(pszInfo);
    if ( ERROR_SUCCESS != (RegQueryValue(hkeyCLSID, NULL, pszInfo, &cchVal)) )
        goto done;

done:
    KillPtr(pszCLSID);

    if ( FAILED(hr) )
        SetNoClassInfo(szClassInfo);
    else
        wsprintf((LPSTR)szClassInfo, "%s,", pszInfo);

    KillPtr(pszInfo);
}


//=--------------------------------------------------------------------------=
// CWinTree::SetName [helper]
//=--------------------------------------------------------------------------=
// Sets name based on bstr value from controls name property
//
// Parameters:
//      VARIANT* pvt        -   [in] variant containing name
//      LPSTR szClassInfo   -   [out] class info string
//
// Output:
//      HRESULT NOERROR, E_FAIL, DISP_E_TYPEMISMATCH
//
// Notes:
//
HRESULT CWinTree::SetName
(
    VARIANT*    pvt,
    LPSTR       szClassInfo
)
{
    HRESULT hr = NOERROR;
    VARIANT vt;
    LPSTR   pszName = NULL;
    int     cchName;

    // Make sure we have a string
    VariantInit(&vt);
    IfComFailGoto(VariantChangeType(&vt, pvt, 0, VT_BSTR));

    cchName = WideCharToMultiByte(
        CP_ACP, 0, V_BSTR(&vt), -1, NULL, 0, NULL, NULL);
    pszName = new char[cchName+1];
    IfMemFailHRGoto(pszName);
    if ( !WideCharToMultiByte(CP_ACP, 0, V_BSTR(&vt), -1, pszName, cchName, NULL, NULL) )
    {
        hr = E_FAIL;
        goto done;
    }

    strcat((LPSTR)szClassInfo, pszName);

done:
    if ( V_BSTR(&vt) )
    {
        VariantClear(&vt);
    }
    KillPtr(pszName);

    return hr;
}


//=--------------------------------------------------------------------------=
// CWinTree::AddUIParentNode [callable]
//=--------------------------------------------------------------------------=
// Creates UI node for frame or main document window
//
// Parameters:
//      CWindow* pwin   -   [in] window associated with UI node
//
// Output:
//      HRESULT NOERROR, E_FAIL
//
// Notes:
//
HRESULT CWinTree::AddUIParentNode
(
    CWindow*    pwin
)
{
    HRESULT         hr = NOERROR;
    BSTR            bstrName = NULL;
    BSTR            bstrHref = NULL;
    char            szName[TV_MAXSTRLEN];
    char            szHref[MAX_PATH+1];
    char            szDefName[TV_MAXWINNAME];
    char            szUIStr[TV_MAXSTRLEN];
    OLECHAR*        rgwzName[] = {OLESTR("name")};
    DISPID          rgdispidName[1];
    VARIANT         vtres;
    DISPPARAMS      dp;

    // Try to get the name of the window
    if ( pwin->m_pIOmWindow )
    {
        while ( TRUE )
        {
            IfFailBreak(pwin->m_pIOmWindow->GetIDsOfNames(
                IID_NULL, rgwzName, 1, LOCALE_SYSTEM_DEFAULT, rgdispidName));
            VariantInit(&vtres);
            ZeroMemory(&dp, sizeof(DISPPARAMS));
            IfFailBreak(pwin->m_pIOmWindow->Invoke(
                rgdispidName[0], IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, 
                &dp, &vtres, NULL, NULL));
            bstrName = SysAllocString(V_BSTR(&vtres));
            VariantClear(&vtres);
            IfFailZeroBreak(WideCharToMultiByte(
                CP_ACP, 0, bstrName, -1, szName, TV_MAXSTRLEN, NULL, NULL));
            if ( !szName[0] )
                hr = E_FAIL;
            break;
        }
    }
    else
        hr = E_FAIL;

    if ( FAILED(hr) )
    {
        wsprintf(szDefName, "Frame %ld", pwin->m_lidx);
        strcpy(szName, szDefName);
        hr = NOERROR;
    }

    while ( TRUE )
    {
        IfFailBreak(pwin->m_pIWebBrowser->get_LocationURL(&bstrHref));
        IfFailZeroBreak(WideCharToMultiByte(
            CP_ACP, 0, bstrHref, -1, szHref, MAX_PATH, NULL, NULL));
        break;
    }

    if ( FAILED(hr) )
    {
        strcpy(szHref, TV_SZLOCATION);
        hr = NOERROR;
    }

    // copy strings together to make UI string
    wsprintf(szUIStr, "%s,%s", szName, szHref);
       
    // Add to tree view
    IfComFailGoto(m_pTreeUI->InsertItem(szUIStr, pwin->m_pvParentTree, &pwin->m_pvTree));

done:
    if ( bstrName )
        SysFreeString(bstrName);

    if ( bstrHref )
        SysFreeString(bstrHref);

    return hr;
}
 