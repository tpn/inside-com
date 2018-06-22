//=--------------------------------------------------------------------------=
// ielnkPPG.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for ielnk's property pages.
//
#ifndef _IELNKPROPPAGE_H_


// kinda need these
//
#include "PropPage.H"
#include "Resource.H"
#include "Guids.H"

class CielnkGeneralPage : public CPropertyPage {

  public:
    static IUnknown *Create(IUnknown *pUnkOuter);

    // constructor and destructor
    //
    CielnkGeneralPage(IUnknown *pUnkOuter);
    virtual ~CielnkGeneralPage();

  private:
    virtual BOOL DialogProc(HWND, UINT, WPARAM, LPARAM);

};

DEFINE_PROPERTYPAGEOBJECT(ielnkGeneral,
    &CLSID_ielnkGeneralPage,
    "ielnk General Propery Page",
    CielnkGeneralPage::Create,
    IDD_PROPPAGE_IELNKGENERAL,
    IDS_IELNK_GENERALPAGETITLE,
    IDS_IELNK_GENERALDOCSTRING,
    "vb.hlp",
    0);

#define _IELNKPROPPAGE_H_
#endif // _IELNKPROPPAGE_H_
