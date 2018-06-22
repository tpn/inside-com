/****************************************************************************
 *
 *  CUSTPOST.C
 *
 *  Microsoft Confidential
 *  Copyright (c) Microsoft Corporation 1995-1996
 *  All rights reserved
 *
 ***************************************************************************/

#include "wbprov.h"
#include <prsht.h>
#include <commdlg.h>
#include <shlobj.h>
#include "resource.h"

// Global variables
extern "C" HINSTANCE g_hInstance;

#define NUM_PAGES 			3

#define SetPropSheetResult(hwnd, result) SetWindowLong(hwnd, DWL_MSGRESULT, result);

WORD gIDD_WEBPOST_WPPREV;
WORD gIDD_WEBPOST_WPNEXT;

// Local Function Prototype


//****************************************************************************
//
// ExtPageDlg
//
//****************************************************************************

BOOL CALLBACK ExtPageDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPPROPSHEETPAGE lpsp;
	UINT			i;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		lpsp = (LPPROPSHEETPAGE) lParam;
		SetWindowLong(hDlg,DWL_USER,(LPARAM) lpsp->lParam);
		break;
		
	case WM_COMMAND:
		break;
		
	case WM_NOTIFY:
		switch (((NMHDR FAR *)lParam)->code)
		{
		case PSN_SETACTIVE:
			//OutputDebugString("ExtPageDlg get called setactive\r\n");
			if (!gIDD_WEBPOST_WPPREV &&
				((i = GetWindowLong(hDlg,DWL_USER)) == 0))
			{
				// we are the first page
				PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_NEXT);
			}
			else if (!gIDD_WEBPOST_WPNEXT &&
				((i = GetWindowLong(hDlg,DWL_USER)) == NUM_PAGES-1))
			{
				// we are the last page
				PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_FINISH);
			}
			else
			{
				PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_NEXT);
			}
			SetPropSheetResult(hDlg,0);
			break;
		case PSN_WIZBACK:
			//OutputDebugString("ExtPageDlg get called wizback\r\n");
			if ((i = GetWindowLong(hDlg,DWL_USER)) == 0)
			{
				SetPropSheetResult(hDlg,gIDD_WEBPOST_WPPREV);
			}
			else
			{
				SetPropSheetResult(hDlg,IDD_PAGE_TEST+i-1);
			}
			break;
		case PSN_WIZNEXT:
			// OutputDebugString("ExtPageDlg get called wiznext\r\n");
			if ((i = GetWindowLong(hDlg,DWL_USER)) == NUM_PAGES-1)
			{
				SetPropSheetResult(hDlg,gIDD_WEBPOST_WPNEXT);
			}
			else if (i == NUM_PAGES -2)
			{
				SetPropSheetResult(hDlg,IDD_WEBPOST_PROVIDER_LAST);
			}
			else
			{
				SetPropSheetResult(hDlg,IDD_PAGE_TEST+i+1);
			}
			break;
		default:
			return FALSE;
		}
		break;
		
	default:
		return FALSE;
	}
	return TRUE;
}


//****************************************************************************
//
// WPPSiteA::AddWizardPages
//
//****************************************************************************

STDMETHODIMP
WPPSiteA::AddWizardPages (
	LPVOID			lpv,
	LPFNADDPROPSHEETPAGE	lpfnAdd,
	LPARAM			lParam
)
{
	HPROPSHEETPAGE	page[NUM_PAGES];
	PROPSHEETPAGE 	psp[NUM_PAGES];
	BOOL			fOkay = TRUE;
	UINT			i, j;
	UINT *			PageID;


	//DEBUGPRINTF(("WebPostCustomPageProc get called"));

	for (i=0; i<NUM_PAGES && fOkay; i++)
	{
		psp[i].dwSize = sizeof(PROPSHEETPAGE);
		psp[i].dwFlags = PSP_DEFAULT;
		psp[i].hInstance = g_hInstance;
		if (i == NUM_PAGES-1)
			// the last page
			psp[i].pszTemplate = MAKEINTRESOURCE(IDD_WEBPOST_PROVIDER_LAST);
		else
			psp[i].pszTemplate = MAKEINTRESOURCE(IDD_PAGE_TEST+i);
		psp[i].pszIcon = NULL;
		psp[i].pfnDlgProc = (DLGPROC)ExtPageDlg;
		psp[i].lParam = i;
		if ((page[i] = CreatePropertySheetPage(&psp[i])) == 0)
		{
			fOkay = FALSE;
		}
		else
		{
			if (!lpfnAdd( page[i], lParam))
				fOkay = FALSE;
		}
	}

	if (!fOkay)
	{
		for (j=0; j<=i; j++)
			DestroyPropertySheetPage(page[j]);
	}

	PageID = (UINT *)lParam;
	gIDD_WEBPOST_WPPREV = HIWORD(*PageID);
	gIDD_WEBPOST_WPNEXT = LOWORD(*PageID);
	*PageID = (IDD_WEBPOST_PROVIDER_FIRST << 16) + IDD_WEBPOST_PROVIDER_LAST;

	return (HRESULT_FROM_WIN32(0));
}


STDMETHODIMP
WPPSiteW::AddWizardPages (
	LPVOID			lpv,
	LPFNADDPROPSHEETPAGE	lpfnAdd,
	LPARAM			lParam
)
{
	OutputDebugString("WPPSiteW: AddWizardPages");
	OutputDebugString("\r\n");
	// Convert to Ansi and call the corresponding A functions
    return ResultFromScode(E_NOTIMPL);
}
