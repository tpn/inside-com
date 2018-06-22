//=------------------------------------------------------------------------=
// SuperPad.h
//=------------------------------------------------------------------------=
// Copyright 1992-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// main header file for the SuperPad application
//

#include "resource.h"
#include "pageset.h"
#include "aboutbox.h"

/////////////////////////////////////////////////////////////////////////////
// CTheApp

class CTheApp : public CWinApp
{
// Constructors
public:
	CTheApp();
	~CTheApp();
	UINT PromptForFileName(CString& fileName, UINT nIDSTitle, DWORD dwFlags,BOOL bOpenFileDialog);

// Implementation
private:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DWORD m_dwSplashTime;
	CSplashWnd m_splash;

	COleTemplateServer m_server;

	//{{AFX_MSG(CTheApp)
	afx_msg void OnAppAbout();
	afx_msg void OnPageSetup();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CPageSetupDlg NEAR dlgPageSetup;
extern CTheApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
