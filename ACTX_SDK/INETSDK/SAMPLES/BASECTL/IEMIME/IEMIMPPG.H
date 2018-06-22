//=--------------------------------------------------------------------------=
// iemimPPG.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for iemim's property pages.
//
#ifndef _IEMIMPROPPAGE_H_


// kinda need these
//
#include "PropPage.H"
#include "Resource.H"
#include "Guids.H"

class CiemimGeneralPage : public CPropertyPage {

  public:
    static IUnknown *Create(IUnknown *pUnkOuter);

    // constructor and destructor
    //
    CiemimGeneralPage(IUnknown *pUnkOuter);
    virtual ~CiemimGeneralPage();

  private:
    virtual BOOL DialogProc(HWND, UINT, WPARAM, LPARAM);

};

DEFINE_PROPERTYPAGEOBJECT(iemimGeneral,
    &CLSID_iemimGeneralPage,
    "iemim General Propery Page",
    CiemimGeneralPage::Create,
    IDD_PROPPAGE_IEMIMGENERAL,
    IDS_IEMIM_GENERALPAGETITLE,
    IDS_IEMIM_GENERALDOCSTRING,
    "vb.hlp",
    0);

#define _IEMIMPROPPAGE_H_
#endif // _IEMIMPROPPAGE_H_
