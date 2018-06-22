#ifndef EVTSINK_H
#include "gen.h"

// event handler function prototype
// Args:
//	LPVOID pvData			-	[in] application defined pointer
//	VARIANTARG* rgvtArgs	-	[in] variant arguments
//	UINT cArgs				-	[in] count of arguments
typedef HRESULT (*PFNHANDLER)(LPVOID pvData, VARIANTARG* rgvtArgs, UINT cArgs);


// event map structure
typedef struct _EVT_MAP
{
	DISPID		dispid;			// dispid of event function
	LPSTR		pszFuncName;	// function name	
	PFNHANDLER	pfnhandler;		// function handler
	LPVOID		pvData;			// user defined data that gets passed to the event handler
} EVT_MAP, *LPEVT_MAP;


// Event sink class
class CEvtSink : public IDispatch
{
public:
// public member functions
	// Standard IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(THIS);
    STDMETHOD_(ULONG, Release)(THIS);

	// Standard IDispatch
    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo);

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo);

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid);

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr);	

	// constructor/destructor
	CEvtSink();
	virtual ~CEvtSink();

	// Creation function creates new event sink instance
	virtual HRESULT Create(REFIID, LPUNKNOWN);

	// Map event
	HRESULT MapEvent(LPCSTR, PFNHANDLER, LPVOID);

	// Connect events
	HRESULT ConnectEvents();

	// Disconnect events
	void DisconnectEvents();

private:
// private data
	// event source's connection point container interface
	IConnectionPointContainer*	m_pIConnPtCtn;

	// event source's connection point interface for the desired event IID
	IConnectionPoint*			m_pIConnPt;

	// cookie for the advise
	DWORD						m_dwConnCookie;

	// event map structure array
	LPEVT_MAP					m_rgEvtMap;

	// number of functions in event map
	UINT						m_cFuncs;

	// reference count
	ULONG						m_cref;

	// event interface IID that this event sink sinks
	IID							m_iid;
};


// class for pointer local variables for all methods of CEvtSink so that the 
// destructor gets called properly if an exception occurs
class CLocal
{
public:
	CLocal()
	{
		pIDisp = NULL;
		pDefITypeInfo = NULL;
		pITypeLib = NULL;
		pIProvideClassInfo = NULL;
		pITypeInfo = NULL;
		ptypeattr = NULL;
		pfuncdesc = NULL;
		bstrName = NULL;
	}

	virtual ~CLocal()
	{
		if ( bstrName )
			SysFreeString(bstrName);

		if ( pfuncdesc )
			pITypeInfo->ReleaseFuncDesc(pfuncdesc);

		if ( ptypeattr )
			pITypeInfo->ReleaseTypeAttr(ptypeattr);

		if ( pITypeInfo )
			ReleaseInterface(pITypeInfo);

		if ( pIProvideClassInfo )
			ReleaseInterface(pIProvideClassInfo);

		if ( pITypeLib )
			ReleaseInterface(pITypeLib);

		if ( pDefITypeInfo )
			ReleaseInterface(pDefITypeInfo);

		if ( pIDisp )
			ReleaseInterface(pIDisp);
	}

// variables
	IDispatch*			pIDisp;
	ITypeInfo*			pDefITypeInfo;
	ITypeLib*			pITypeLib;
	IProvideClassInfo*	pIProvideClassInfo;
	ITypeInfo*			pITypeInfo;
	TYPEATTR*			ptypeattr;
	FUNCDESC*			pfuncdesc;
	BSTR				bstrName;
};

#define EVTSINK_H
#endif
