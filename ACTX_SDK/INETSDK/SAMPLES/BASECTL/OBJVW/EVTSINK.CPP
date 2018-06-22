//=--------------------------------------------------------------------------=
// EvtSink.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// Generic class for sinking control events
//

#include "ipserver.h"
#include "evtsink.h"
#include "gen.h"


SZTHISFILE

//=--------------------------------------------------------------------------=
// CEvtSink::CEvtSink
//=--------------------------------------------------------------------------=
// Event sink constructor
//
// Parameters:
//
// Output:
//
// Notes:
//
CEvtSink::CEvtSink()
{
	m_pIConnPtCtn = NULL;
	m_pIConnPt = NULL;
	m_dwConnCookie = 0;
	m_rgEvtMap = NULL;
	m_cFuncs = 0;
	m_cref = 0;
}


//=--------------------------------------------------------------------------=
// CEvtSink::~CEvtSink
//=--------------------------------------------------------------------------=
// Event sink destructor
//
// Parameters:
//
// Output:
//
// Notes:
//
CEvtSink::~CEvtSink()
{
	// delete any event map stuff
	if ( m_rgEvtMap )
	{
		for ( UINT i = 0; i < m_cFuncs; i++ )
		{
			if ( m_rgEvtMap[i].pszFuncName )
			{
				delete [] m_rgEvtMap[i].pszFuncName;
				m_rgEvtMap[i].pszFuncName = NULL;
			}
		}

		delete [] m_rgEvtMap;
		m_rgEvtMap = NULL;
	}
}


//=--------------------------------------------------------------------------=
// CEvtSink::AddRef [IUnknown]
//=--------------------------------------------------------------------------=
// Add to reference count
//
// Parameters:
//
// Output:
//
// Notes:
//
ULONG CEvtSink::AddRef()
{
	m_cref++;
	return m_cref;
}


//=--------------------------------------------------------------------------=
// CEvtSink::Release [IUnknown]
//=--------------------------------------------------------------------------=
// Decrement reference count
//
// Parameters:
//
// Output:
//
// Notes:
//
ULONG CEvtSink::Release()
{
	if ( 0 == --m_cref )
	{
		delete this;
		return 0;
	}

	return m_cref;
}


//=--------------------------------------------------------------------------=
// CEvtSink::QueryInterface [IUnknown]
//=--------------------------------------------------------------------------=
// QueryInterface
//
// Parameters:
//		standard
//
// Output:
//
// Notes:
//
HRESULT CEvtSink::QueryInterface
(
	REFIID		riid,
	void **		ppvObj
)
{
	(*ppvObj) = NULL;

	// make sure to check for the real event interface not just IDispatch
	if ( 
		IsEqualIID(IID_IUnknown, riid) || 
		IsEqualIID(IID_IDispatch, riid) ||
		IsEqualIID(m_iid, riid)
	   )
	{
		(*ppvObj) = this;
		AddRef();
		return NOERROR;
	}

	return ResultFromScode(E_NOINTERFACE);
}


//=--------------------------------------------------------------------------=
// CEvtSink::GetTypeInfoCount [IDispatch]
//=--------------------------------------------------------------------------=
// Get count of type info
//
// Parameters:
//		standard
//
// Output:
//
// Notes:
//		No type info
//
HRESULT CEvtSink::GetTypeInfoCount
(
	UINT*	pctinfo
)
{
	(*pctinfo) = 0;
	return NOERROR;
}


//=--------------------------------------------------------------------------=
// CEvtSink::GetTypeInfo [IDispatch]
//=--------------------------------------------------------------------------=
// Get type information
//
// Parameters:
//		standard
//
// Output:
//
// Notes:
//		No type info
//
HRESULT CEvtSink::GetTypeInfo
(
	UINT		itinfo,
	LCID		lcid,
	ITypeInfo**	pptinfo
)
{
	(*pptinfo) = NULL;
	return ResultFromScode(DISP_E_BADINDEX);
}


//=--------------------------------------------------------------------------=
// CEvtSink::GetIDsOfNames [IDispatch]
//=--------------------------------------------------------------------------=
// Get IDs of names
//
// Parameters:
//		standard
//
// Output:
//
// Notes:
//		Should never be called
//
HRESULT CEvtSink::GetIDsOfNames
(
	REFIID		riid,
    OLECHAR**	rgszNames,
    UINT		cNames,
    LCID		lcid,
    DISPID*		rgdispid		
)
{
	return ResultFromScode(E_NOTIMPL);
}


//=--------------------------------------------------------------------------=
// CEvtSink::Invoke [IDispatch]
//=--------------------------------------------------------------------------=
// Fire event handlers
//
// Parameters:
//		standard
//
// Output:
//
// Notes:
//
HRESULT CEvtSink::Invoke
(
	DISPID dispidMember,
    REFIID riid,
    LCID lcid,
    WORD wFlags,
    DISPPARAMS FAR* pdispparams,
    VARIANT FAR* pvarResult,
    EXCEPINFO FAR* pexcepinfo,
    UINT FAR* puArgErr		
)
{
	// find the event in the event map based on dispid
	for( UINT i = 0; i < m_cFuncs; i++ )
	{
		if ( m_rgEvtMap[i].dispid == dispidMember )
		{
			// if we have a handler, call it
			if ( m_rgEvtMap[i].pfnhandler )
			{
				HRESULT	hr;
				hr = (*m_rgEvtMap[i].pfnhandler)(m_rgEvtMap[i].pvData, 
					pdispparams->rgvarg, pdispparams->cArgs);
				if ( FAILED(hr) )
				{
					return hr;
				}
			}

			break;
		}
	}
	return NOERROR;
}


//=--------------------------------------------------------------------------=
// CEvtSink::Create
//=--------------------------------------------------------------------------=
// Create new event sink
//
// Parameters:
//		REFIID riid		-	[in] Interface ID of event interface we are sinking
//							if this is IID_NULL then sink the default source
//		LPUNKNOWN pUnk	-	[in] interface on source object
//
// Output:
//		HRESULT
//			NOERROR	everything OK
//			E_FAIL no default source interface or riid interface found
//
// Notes:
//		Throws exceptions on unexpected OLE API error
//
//		I decided not to sort the event map based on name or dispid since there will
//		usually be very few elements in it.  Thus we are restricted to straight linear
//		searches in the lookup routines for events.	
//
HRESULT CEvtSink::Create
(
	REFIID		riid,
	LPUNKNOWN	pUnk
)
{
	CLocal				clocal;
	UINT				uidx;
	UINT				ucName;
	int					nlenName;
	int					i;
	HRESULT				hr = NOERROR;
	
	// Get connection point container interface
	IfComFailRet(pUnk->QueryInterface(IID_IConnectionPointContainer,
		(void**)&m_pIConnPtCtn));

	// is id non null, if so then find the interface
	if ( !IsEqualIID(IID_NULL, riid) )
	{
		// Get type info of this interface
		IfComFailGoto(pUnk->QueryInterface(IID_IDispatch, 
			(void**)&clocal.pIDisp));
		IfComFailGoto(clocal.pIDisp->GetTypeInfo(0, LOCALE_SYSTEM_DEFAULT, 
			&clocal.pDefITypeInfo));
		IfComFailGoto(clocal.pDefITypeInfo->GetContainingTypeLib(&clocal.pITypeLib, &uidx));
		clocal.pDefITypeInfo->GetTypeAttr(&clocal.ptypeattr);

		// If guid not found then return E_FAIL
		hr = clocal.pITypeLib->GetTypeInfoOfGuid(riid, &clocal.pITypeInfo);
		if ( FAILED(hr) )
		{
			if ( TYPE_E_ELEMENTNOTFOUND == hr )
				hr = E_FAIL;
			goto done;
		}
	}

	// otherwise find the default source
	else
	{
		// Get class info so we can get the type info for the coclass
		IfComFailGoto(pUnk->QueryInterface(IID_IProvideClassInfo, 
			(void **)&clocal.pIProvideClassInfo));
		IfComFailGoto(clocal.pIProvideClassInfo->GetClassInfo(&clocal.pDefITypeInfo));

		// From the coclass find the default source interface
		// Get the type attributes
		IfComFailGoto(clocal.pDefITypeInfo->GetTypeAttr(&clocal.ptypeattr));

		// search the implemented types for the default source interface
		for(int i = 0; i < clocal.ptypeattr->cImplTypes; i++)
		{
			HREFTYPE	hreftype;
			int			memidFlags;

			// get type flags
			IfComFailGoto(clocal.pDefITypeInfo->GetImplTypeFlags(
				i, &memidFlags));

			// check for default source interface that is not restricted
			if ( 
				(memidFlags & (IMPLTYPEFLAG_FDEFAULT | IMPLTYPEFLAG_FSOURCE | 
					IMPLTYPEFLAG_FRESTRICTED)) ==
				(IMPLTYPEFLAG_FDEFAULT | IMPLTYPEFLAG_FSOURCE)
			   )
			{
				// Get handle of interface
				IfComFailGoto(clocal.pDefITypeInfo->GetRefTypeOfImplType(
					i, &hreftype));

				// Get pointer to interface
				IfComFailGoto(clocal.pDefITypeInfo->GetRefTypeInfo(
					hreftype, &(clocal.pITypeInfo)));

				break;
			}
		}

		// if we still don't have our interface then return E_FAIL
		if ( !clocal.pITypeInfo )
			return ResultFromScode(E_FAIL);
	}

	// Get type attributes
	IfComFailGoto(clocal.pITypeInfo->GetTypeAttr(&clocal.ptypeattr));
		
	// save off iid of interface
	m_iid = clocal.ptypeattr->guid;

	// Get IConnectionPoint interface
	IfComFailGoto(m_pIConnPtCtn->FindConnectionPoint(
		m_iid, &m_pIConnPt));		

	// Allocate event map structure
	m_rgEvtMap = new EVT_MAP[clocal.ptypeattr->cFuncs];
	if ( !m_rgEvtMap )
	{
		hr = E_OUTOFMEMORY;
		goto done;
	}
	ZeroMemory(m_rgEvtMap, sizeof(EVT_MAP)*clocal.ptypeattr->cFuncs);
	m_cFuncs = clocal.ptypeattr->cFuncs;

	// walk through funcdescs and get the names and dispids
	for(i = 0; i < clocal.ptypeattr->cFuncs; i++)
	{
		// Get function description
		IfComFailGoto(clocal.pITypeInfo->GetFuncDesc(i, &clocal.pfuncdesc));

		// set dispid
		m_rgEvtMap[i].dispid = clocal.pfuncdesc->memid;
				
		// Get name of function
		clocal.bstrName = SysAllocString(OLESTR(""));
		IfComFailGoto(clocal.pITypeInfo->GetNames(
			clocal.pfuncdesc->memid, &clocal.bstrName, 1, &ucName));

		// Get length of ascii string
		nlenName = WideCharToMultiByte(
			CP_ACP, 0, clocal.bstrName, -1, NULL, 0, NULL, NULL);

		// Allocate ascii string and do conversion again
		m_rgEvtMap[i].pszFuncName = new char[nlenName+1];
		WideCharToMultiByte(
			CP_ACP, 0, clocal.bstrName, -1, m_rgEvtMap[i].pszFuncName, nlenName+1, NULL, NULL);

		// release name string
		SysFreeString(clocal.bstrName);
		clocal.bstrName = NULL;

		// Release function description
		clocal.pITypeInfo->ReleaseFuncDesc(clocal.pfuncdesc);
		clocal.pfuncdesc = NULL;
	}

done:
	return hr;
}


//=--------------------------------------------------------------------------=
// CEvtSink::MapEvent
//=--------------------------------------------------------------------------=
// Maps an event handler function to an event
//
// Parameters:
//		LPCSTR	pszEvtName		-	[in] event name to find
//		PFNHANDLER pfnhandler	-	[in] handler function
//		LPVOID pvEvtData		-	[in] pointer to some data that will get forwarded on 
//									to the handler if the event is called
//
// Output:
//		HRESULT
//			NOERROR	everything OK
//			E_FAIL no event with name pszEvtName found
//
// Notes:
//		The string comparision for event names is not case sensitive
//
HRESULT CEvtSink::MapEvent
(
	LPCSTR		pszEvtName,
	PFNHANDLER	pfnhandler,
	LPVOID		pvEvtData
)
{
	BOOL	fFound = FALSE;

	ASSERT(pszEvtName, "Cannot have NULL event name");

	// find event in map 
	for (UINT i = 0; i < m_cFuncs; i++)
	{
		// if we found the event, set up the handler function
		if ( !strcmpi(m_rgEvtMap[i].pszFuncName, pszEvtName) )
		{
			m_rgEvtMap[i].pfnhandler = pfnhandler;
			m_rgEvtMap[i].pvData = pvEvtData;
			fFound = TRUE;
			break;
		}
	}

	// if not found then return E_FAIL
	if ( !fFound )
		return ResultFromScode(E_FAIL);

	return NOERROR;
}


//=--------------------------------------------------------------------------=
// CEvtSink::ConnectEvents
//=--------------------------------------------------------------------------=
// Begin advise on our event interface
//
// Parameters:
//
// Output:
//
// Notes:
//		Call this when you are done setting event handlers with MapEvent
//
HRESULT CEvtSink::ConnectEvents()
{
	HRESULT	hr = NOERROR;
 	IfComFailRet(m_pIConnPt->Advise((LPUNKNOWN)this, &m_dwConnCookie));
	return hr;
}


//=--------------------------------------------------------------------------=
// CEvtSink::DisconnectEvents
//=--------------------------------------------------------------------------=
// Terminate advise on our event interface
//
// Parameters:
//
// Output:
//
// Notes:
//		Call this when you no longer want to handle events it is called automatically
//		in the destructor
//
void CEvtSink::DisconnectEvents()
{
	if ( m_pIConnPt )
		m_pIConnPt->Unadvise(m_dwConnCookie);
}



