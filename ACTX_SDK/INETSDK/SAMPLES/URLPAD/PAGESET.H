//=------------------------------------------------------------------------=
// PageSet.h
//=------------------------------------------------------------------------=
// Copyright 1992-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// Definition of the CPageSetupDlg class
//

#ifndef _PAGESET_H_
#define _PAGESET_H_

/////////////////////////////////////////////////////////////////////////////
// CPageSetupDlg dialog

class CPageSetupDlg : public CDialog
{
	DECLARE_DYNAMIC(CPageSetupDlg)
// Construction
public:
	CPageSetupDlg(CWnd* pParent = NULL);    // standard constructor
	void Initialize();
	void Terminate();

// Dialog Data
	//{{AFX_DATA(CPageSetupDlg)
	enum { IDD = IDD_PAGE_SETUP };
	CString m_strFooter;
	CString m_strHeader;
	int     m_iFooterTime;
	int     m_iHeaderTime;
	//}}AFX_DATA

	CString m_strFooterOld;
	CString m_strHeaderOld;
	int     m_iFooterTimeOld;
	int     m_iHeaderTimeOld;

// Operations
	void FormatHeader(CString& strHeader, CTime& time,
		LPCTSTR pszFileName, UINT nPage);
	void FormatFooter(CString& strFooter, CTime& time,
		LPCTSTR pszFileName, UINT nPage);

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	static void FormatFilePage(
		CString& strFormat, LPCTSTR pszFileName, UINT nPage);

	// Generated message map functions
	//{{AFX_MSG(CPageSetupDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // _PAGESET_H_

/////////////////////////////////////////////////////////////////////////////
