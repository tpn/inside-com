//=------------------------------------------------------------------------=
// PadDoc.Cpp
//=------------------------------------------------------------------------=
// Copyright 1992-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// implementation of the CPadDoc class
//

#include "stdafx.h"
#include "superpad.h"
#include "paddoc.h"
#include "paditem.h"
#include "linkitem.h"

#include <wpapi.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPadDoc

IMPLEMENT_DYNCREATE(CPadDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CPadDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CPadDoc)
	ON_COMMAND(ID_VIEW_UPDATENOW, OnViewUpdatenow)
	ON_COMMAND(ID_CANCEL_INPLACE, OnCancelInplace)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPadDoc delegation to CEditView

CPadDoc::CPadDoc()
{
	m_urlflag=FALSE;
}

CPadDoc::~CPadDoc()
{
	if (m_urlflag!=FALSE)	
		DeleteFile(GetPathName());
}

void CPadDoc::DeleteContents()
{
	COleServerDoc::DeleteContents();
	if (m_viewList.IsEmpty())
		return;
	CEditView* pView = (CEditView*)m_viewList.GetHead();
	ASSERT_KINDOF(CEditView, pView);
	pView->DeleteContents();
}

void CPadDoc::Serialize(CArchive& ar)
{
	CEditView* pView = (CEditView*)m_viewList.GetHead();
	ASSERT_KINDOF(CEditView, pView);
	pView->SerializeRaw(ar);
}

COleServerItem* CPadDoc::OnGetEmbeddedItem()
{
	CEmbeddedItem* pItem = new CEmbeddedItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

COleServerItem* CPadDoc::OnGetLinkedItem(LPCTSTR lpszItemName)
{
	CPadLinkItem *pItem =
		(CPadLinkItem*)COleServerDoc::OnGetLinkedItem(lpszItemName);
	if (pItem == NULL)
		pItem = new CPadLinkItem(this, lpszItemName);

	ASSERT_VALID(pItem);
	return pItem;
}

/////////////////////////////////////////////////////////////////////////////

void CPadDoc::OnViewUpdatenow()
{
	UpdateAllItems(NULL);
}

// Note: both the server and the container should have a keyboard method
//  of deactivating an active in-place item.

void CPadDoc::OnCancelInplace()
{
	if (IsInPlaceActive())
		OnDeactivateUI(FALSE);
}

void CPadDoc::SetSelection(int nBeg, int nEnd)
{
	CEditView* pView = (CEditView*)m_viewList.GetHead();
	ASSERT_KINDOF(CEditView, pView);
	pView->GetEditCtrl().SetSel(nBeg, nEnd);
}

void CPadDoc::OnFileSave() 
{
	// If the file being saved is not URL file then call standard save
	if (m_urlflag==FALSE)
	{
		CDocument::OnFileSave();
		return;
	}

	// Make a local copy of the file so that you can post by the same name
	// as that of URL and not the temporary file name.
	LONG lRet;
	LPTSTR lpszFileName=m_urlfile.GetBuffer(MAX_PATH);
	LPTSTR tempPath= new CHAR[MAX_PATH];
	::GetTempPath(MAX_PATH,tempPath);
	strcat(tempPath,lpszFileName);
	CDocument::OnSaveDocument(tempPath);

	// Call WebPost Wizard
	lRet = WpPost(	NULL,		// hWin
					1,		// count of files
					&tempPath,	// file list
					NULL,		// lpcbSiteName
					NULL,		// lpszSiteName
					NULL,		// lpcbURL
					NULL,		// lpszURL
					0 );		// flags
	DeleteFile(tempPath);  // Delete the temporary file which holds the HTM file
	return;
}
