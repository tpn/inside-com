//=------------------------------------------------------------------------=
// FileOpen.Cpp
//=------------------------------------------------------------------------=
// Copyright 1992-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// CModFileDialog implementation
//

#include "stdafx.h"
#include "resource.h"
#include "Fileopen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModFileDialog

IMPLEMENT_DYNAMIC(CModFileDialog, CFileDialog)

CModFileDialog::CModFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
			m_urlflag=FALSE;
}


BEGIN_MESSAGE_MAP(CModFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CModFileDialog)
	ON_BN_CLICKED(url, Onurl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// OnUrl
// This function enables and disables the various controls on the FileOpen
// Dialog box depending on the type of file to be opened.

void CModFileDialog::Onurl() 
{
	m_urlflag=!m_urlflag;

	// URL FILE
	if (m_urlflag)
	{
		SetDlgItemText(stc3,"URL");
		SetDlgItemText(edt1,"http://www.microsoft.com/default.htm");
		GetDlgItem(lst1)->EnableWindow(FALSE);
		GetDlgItem(lst2)->EnableWindow(FALSE);
		GetDlgItem(cmb1)->EnableWindow(FALSE);
		GetDlgItem(cmb2)->EnableWindow(FALSE);
		GetDlgItem(psh14)->EnableWindow(FALSE);
	}
	// Ordinary File
	else
	{
		SetDlgItemText(stc3,"FileName");
		SetDlgItemText(edt1,"*.*");
		GetDlgItem(lst1)->EnableWindow(TRUE);
		GetDlgItem(lst2)->EnableWindow(TRUE);
		GetDlgItem(cmb1)->EnableWindow(TRUE);
		GetDlgItem(cmb2)->EnableWindow(TRUE);
		GetDlgItem(psh14)->EnableWindow(TRUE);
	}
}
