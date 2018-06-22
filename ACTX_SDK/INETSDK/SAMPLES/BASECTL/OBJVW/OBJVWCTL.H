//=--------------------------------------------------------------------------=
// ObjVwCtl.H
//=--------------------------------------------------------------------------=
// Copyright 1995-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the LinkTrck control.
//
#ifndef _OBJVWCONTROL_H_

#include "IPServer.H"
#include "CtrlObj.H"
#include "ObjVwInt.H"
#include "Dispids.H"
#include "appsink.h"
#include "treeui.h"
#include "wintree.h"
	
typedef struct tagOBJVWCTLSTATE {

    // TOOD: put state variables here, and probably get rid of fGarbage, unless
    // you have a real need for it
    //
    VARIANT_BOOL fGarbage;

} OBJVWCTLSTATE;

//=--------------------------------------------------------------------------=
// CObjVwControl
//=--------------------------------------------------------------------------=
// our control.
//
class CObjVwControl :	public COleControl, 
                            public IObjVw, 
							public ISupportErrorInfo 
{
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

    // IObjVw methods
    //
    // TODO: copy over the method declarations from ObjVwInt.H
    //       don't forget to remove the PURE from them.
    //
    STDMETHOD_(void, AboutBox)(THIS) ;


	// Constructor/destructor
    CObjVwControl(IUnknown *pUnkOuter);
    virtual ~CObjVwControl();

    // static creation function.  all controls must have one of these!
    //
    static IUnknown *Create(IUnknown *);

	virtual BOOL OnGetPalette(HDC hdc, LOGPALETTE** ppPal) 
	{
		(*ppPal) = NULL;
		return FALSE;
	}

	void ChangeView() { ViewChanged(); }
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

    virtual HRESULT InternalQueryInterface(REFIID, void **);
    virtual void    BeforeCreateWindow(void);
	
    virtual BOOL    AfterCreateWindow(void);

// private state information.
//
	// sink for window events
	CAppSink*		m_pAppSink;

	// Tree UI class
	CTreeUI*		m_pTreeUI;

	// WIndow tree class pointer
	CWinTree*		m_pWinTree;
};


// TODO: if you have an array of verbs, then add an extern here with the name
//       of it, so that you can include it in the DEFINE_CONTROLOBJECT.
//       ie.  extern VERBINFO m_LinkTrckCustomVerbs [];
//
DEFINE_CONTROLOBJECT(ObjVw,
    &CLSID_ObjVw,
    "ObjVwCtl",
    CObjVwControl::Create,
    1,
    &IID_IObjVw,
    "ObjVw.HLP",
    &DIID_DObjVwEvents,
    OLEMISC_SETCLIENTSITEFIRST|OLEMISC_ACTIVATEWHENVISIBLE|OLEMISC_RECOMPOSEONRESIZE|OLEMISC_CANTLINKINSIDE|OLEMISC_INSIDEOUT,
    //OLEMISC_SETCLIENTSITEFIRST|OLEMISC_INVISIBLEATRUNTIME|OLEMISC_CANTLINKINSIDE,
    0,
    RESID_TOOLBOX_BITMAP,
    "ObjVwWndClass",
    0,
    NULL,
    0,
    NULL);



#define _OBJVWCONTROL_H_
#endif // _OBJVWCONTROL_H_
