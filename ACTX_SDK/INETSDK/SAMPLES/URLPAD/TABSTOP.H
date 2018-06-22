//=------------------------------------------------------------------------=
// TabStop.h
//=------------------------------------------------------------------------=
// Copyright 1992-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// Definition of the CSetTabStops class
//

/////////////////////////////////////////////////////////////////////////////
// CSetTabStops dialog

class CSetTabStops : public CDialog
{
	DECLARE_DYNAMIC(CSetTabStops)
// Construction
public:
	CSetTabStops(CWnd* pParent = NULL); // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetTabStops)
	enum { IDD = IDD_SET_TABSTOPS };
	UINT    m_nTabStops;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//{{AFX_MSG(CSetTabStops)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
