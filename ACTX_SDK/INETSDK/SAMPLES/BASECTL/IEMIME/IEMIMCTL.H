//=--------------------------------------------------------------------------=
// iemimCtl.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the iemim control.
//
#ifndef _IEMIMCONTROL_H_

#include "IPServer.H"
#include "CtrlObj.H"
#include "iemimIfc.H"
#include "Dispids.H"
#include "mimeinet.H"

//=--------------------------------------------------------------------------=
// CiemimControl
//=--------------------------------------------------------------------------=
// our control.
//
class CiemimControl : public CmimeInternetControl, public Iiemim, public ISupportErrorInfo, public
 IPersistMoniker {

  public:
    // IUnknown methods
    //
    DECLARE_STANDARD_UNKNOWN();

    // IDispatch methods
    //
    DECLARE_STANDARD_DISPATCH();

    // ISupportErrorInfo methods
    //
    DECLARE_STANDARD_SUPPORTERRORINFO();

    // Iiemim methods
    //
    // TODO: copy over the method declarations from iemimIfc.H
    //       don't forget to remove the PURE from them.
    //
    STDMETHOD(get_URL)(THIS_ BSTR FAR* val);
    STDMETHOD(put_URL)(THIS_ BSTR val);
    STDMETHOD(get_Media)(THIS_ BSTR FAR* val);
    STDMETHOD(put_Media)(THIS_ BSTR val);
    STDMETHOD(get_Cfformat)(THIS_ BSTR FAR* val);
    STDMETHOD(put_Cfformat)(THIS_ BSTR val);
    STDMETHOD_(void, AboutBox)(THIS);
    STDMETHOD_(void, Reload)(THIS);

	// IPersistMoniker
	STDMETHOD(GetClassID)(CLSID *clsid);
	STDMETHOD(IsDirty)(void);
	STDMETHOD(Load)(BOOL fFullyAvailable, IMoniker* pmkSrc, IBindCtx* pbc, DWORD grfMode);
	STDMETHOD(Save)(IMoniker* pmkDst, IBindCtx* pbc, BOOL fRemember);
	STDMETHOD(SaveCompleted)(IMoniker* pmkNew, IBindCtx* pbc);
	STDMETHOD(GetCurMoniker)(IMoniker** ppmkCur);

    // OLE Control stuff follows:
    //
    CiemimControl(IUnknown *pUnkOuter);
    virtual ~CiemimControl();
	virtual HRESULT OnData( DISPID id, DWORD grfBSCF,
		FORMATETC *pformatetc, STGMEDIUM *pstgmed, 
		DWORD amount );
    // static creation function.  all controls must have one of these!
    //
    static IUnknown *Create(IUnknown *);

  private:
    // overridables that the control must implement.
    //
    STDMETHOD(LoadBinaryState)(IStream *pStream);
    STDMETHOD(SaveBinaryState)(IStream *pStream);
    STDMETHOD(LoadTextState)(IPropertyBag *pPropertyBag, IErrorLog *pErrorLog);
    STDMETHOD(SaveTextState)(IPropertyBag *pPropertyBag, BOOL fWriteDefault);
    STDMETHOD(OnDraw)(DWORD dvAspect, HDC hdcDraw, LPCRECTL prcBounds, LPCRECTL prcWBounds, HDC hicTargetDev, BOOL fOptimize);
    virtual LRESULT WindowProc(UINT msg, WPARAM wParam, LPARAM lParam);
    virtual BOOL    RegisterClassData(void);
    STDMETHOD(SetObjectRects)(LPCRECT lprcPosRect,LPCRECT lprcClipRect);
    virtual HRESULT InternalQueryInterface(REFIID, void **);
    virtual BOOL BeforeCreateWindow(DWORD *pdwWindowStyle, DWORD *pdwExWindowStyle, LPSTR pszWindowTitle);
    virtual BOOL AfterCreateWindow();

  private:
	char *data;
	long readTillNow;
    // private state information.
    //
};


// TODO: if you have an array of verbs, then add an extern here with the name
//       of it, so that you can include it in the DEFINE_CONTROLOBJECT.
//       ie.  extern VERBINFO m_iemimCustomVerbs [];
//
extern const GUID    *rgiemimPropPages [];
DEFINE_CONTROLOBJECT(iemim,
    &CLSID_iemim,
    "iemimCtl",
    CiemimControl::Create,
    1,
    &IID_Iiemim,
    "iemim.HLP",
    &DIID_DiemimEvents,
    OLEMISC_SETCLIENTSITEFIRST|OLEMISC_ACTIVATEWHENVISIBLE|OLEMISC_RECOMPOSEONRESIZE|OLEMISC_CANTLINKINSIDE|OLEMISC_INSIDEOUT,
    0,
	RESID_TOOLBOX_BITMAP,
    "iemimWndClass",
    1,
    rgiemimPropPages,
    0,
    NULL);



#define _IEMIMCONTROL_H_
#endif // _IEMIMCONTROL_H_
