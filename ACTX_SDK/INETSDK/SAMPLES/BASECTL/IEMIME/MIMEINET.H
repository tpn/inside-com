//=--------------------------------------------------------------------------=
// Cmimeinet.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the URLDib2 control.
//
#ifndef __MIMEINTERNETCONTROL_H_
#define __MIMEINTERNETCONTROL_H_

#define DISPID_PROGRESS	1958

#ifndef __MKTYPLIB__

#include "urlmon.H"

#include "docobj.h"   // for IServiceProvider

#include "servprov.h"
#include "IPServer.H"
#include "CtrlObj.H"

typedef struct tagIEMIMCTLSTATE {

    // TOOD: put state variables here, and probably get rid of fGarbage, unless
    // you have a real need for it
    //
	char *m_url;
	char *m_media;
	char *m_cfformat;

} IEMIMCTLSTATE;


class CmimeInternetControl : public COleControl
{
public:
	CmimeInternetControl(IUnknown *	pUnkOuter, 
					int			iPrimaryDispatch, 
					void *		pMainInterface);

	virtual ~CmimeInternetControl();

    // IUnknown methods
    //
    DECLARE_STANDARD_UNKNOWN();

	// Call this method to start the download of a URL. 'propId' will 
	//	be passed back to you OnData below.
	HRESULT SetupDownload( LPOLESTR url, DISPID propId);


	//	Derived classes implement this method. It will be called when
	//	data has arrived for a given dispid.
	virtual HRESULT OnData( DISPID id, DWORD grfBSCF,
		FORMATETC *pformatetc, STGMEDIUM *pstgmed, 
		DWORD amount );


	//	Derived classes can implement this method. It will be
	//	called at various times during the download.
	virtual HRESULT OnProgress( DISPID id, ULONG ulProgress,
                                        ULONG ulProgressMax,
                                        ULONG ulStatusCode,
                                        LPCWSTR pwzStatusText);

	//	Call this method to turn a URL into a Moniker.
	HRESULT GetAMoniker( LPOLESTR	url, IMoniker ** );


    HRESULT FireReadyStateChange( long newState );
	HRESULT FireProgress( ULONG dwAmount );


        // Override base class implementation...

    virtual HRESULT InternalQueryInterface(REFIID, void **);

protected:
	HRESULT GetBindHost();

    IBindHost *             m_host;
    long                    m_readyState;
public:
    IEMIMCTLSTATE m_state;
	void Invalidate();

};

#endif __MKTYPLIB__

#endif __MIMEINTERNETCONTROL_H_

