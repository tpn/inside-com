//=------------------------------------------------------------------------=
// FileOpen.h
//=------------------------------------------------------------------------=
// Copyright 1992-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// Definition of the CModFileDialog class
//

/////////////////////////////////////////////////////////////////////////////
// CModFileDialog dialog

class CModFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CModFileDialog)

public:
	CModFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(CModFileDialog)
	afx_msg void Onurl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL m_urlflag;
};
