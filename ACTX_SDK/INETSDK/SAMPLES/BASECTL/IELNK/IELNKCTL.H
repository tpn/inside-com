//=--------------------------------------------------------------------------=
// ielnkCtl.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the ielnk control.
//
#ifndef _IELNKCONTROL_H_

#include "IPServer.H"
#include "CtrlObj.H"
#include "ielnkIfc.H"
#include "Dispids.H"

typedef struct tagIELNKCTLSTATE {

    // TOOD: put state variables here, and probably get rid of fGarbage, unless
    // you have a real need for it
    //
    char *m_hlink;
	char *m_location;
	char *m_targetframe;
	long  m_flags;
	long  m_mode;

} IELNKCTLSTATE;

//=--------------------------------------------------------------------------=
// CielnkControl
//=--------------------------------------------------------------------------=
// our control.
//
class CielnkControl : public COleControl, public Iielnk, public ISupportErrorInfo {

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

    // Iielnk methods
    //
    // TODO: copy over the method declarations from ielnkIfc.H
    //       don't forget to remove the PURE from them.
    //
    STDMETHOD(get_Hlink)(THIS_ BSTR FAR* val) ;
    STDMETHOD(put_Hlink)(THIS_ BSTR val) ;
    STDMETHOD(get_Location)(THIS_ BSTR FAR* val) ;
    STDMETHOD(put_Location)(THIS_ BSTR val) ;
    STDMETHOD(get_TargetFrame)(THIS_ BSTR FAR* val) ;
    STDMETHOD(put_TargetFrame)(THIS_ BSTR val) ;
    STDMETHOD(get_Flags)(THIS_ long FAR* val) ;
    STDMETHOD(put_Flags)(THIS_ long val) ;
    STDMETHOD(get_Mode)(THIS_ long FAR* val) ;
    STDMETHOD(put_Mode)(THIS_ long val) ;	
	STDMETHOD_(void, AboutBox)(THIS) ;
    STDMETHOD_(void, Forward)(THIS) ;
    STDMETHOD_(void, Back)(THIS) ;
    STDMETHOD_(void, Go)(THIS) ;
    // OLE Control stuff follows:
    //
    CielnkControl(IUnknown *pUnkOuter);
    virtual ~CielnkControl();

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
    STDMETHOD(OnDraw)(DWORD dvaspect, HDC hdcDraw, LPCRECTL prcBounds, LPCRECTL prcWBounds, HDC hicTargetDev, BOOL fOptimize);
    virtual LRESULT WindowProc( UINT msg, WPARAM wParam, LPARAM lParam);
    virtual BOOL    RegisterClassData(void);

    virtual HRESULT InternalQueryInterface(REFIID, void **);
    virtual BOOL BeforeCreateWindow(DWORD *pdwWindowStyle, DWORD *pdwExWindowStyle, LPSTR pszWindowTitle);
    virtual BOOL AfterCreateWindow();
    STDMETHOD(SetObjectRects)(LPCRECT prcPos, LPCRECT prcClip);


    // private state information.
    //
    IELNKCTLSTATE m_state;
};


// TODO: if you have an array of verbs, then add an extern here with the name
//       of it, so that you can include it in the DEFINE_CONTROLOBJECT.
//       ie.  extern VERBINFO m_ielnkCustomVerbs [];
//
extern const GUID    *rgielnkPropPages [];
DEFINE_CONTROLOBJECT(ielnk,
    &CLSID_ielnk,
    "ielnkCtl",
    CielnkControl::Create,
    1,
    &IID_Iielnk,
    "ielnk.HLP",
    &DIID_DielnkEvents,
    OLEMISC_SETCLIENTSITEFIRST|OLEMISC_ACTIVATEWHENVISIBLE|OLEMISC_RECOMPOSEONRESIZE|OLEMISC_CANTLINKINSIDE|OLEMISC_INSIDEOUT,
    0,
	RESID_TOOLBOX_BITMAP,
    "ielnkWndClass",
    1,
    rgielnkPropPages,
    0,
    NULL);



#define _IELNKCONTROL_H_
#endif // _IELNKCONTROL_H_
