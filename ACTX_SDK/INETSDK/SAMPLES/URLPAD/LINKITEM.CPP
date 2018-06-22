//=------------------------------------------------------------------------=
// LinkItem.Cpp
//=------------------------------------------------------------------------=
// Copyright 1992-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// implementation of the CPadLinkItem class
//

#include "stdafx.h"
#include "padview.h"
#include "paddoc.h"
#include "paditem.h"
#include "linkitem.h"
#include <limits.h>

IMPLEMENT_DYNAMIC(CPadLinkItem, CEmbeddedItem)

CPadLinkItem::CPadLinkItem(CPadDoc* pContainerDoc, LPCTSTR pszItemName)
	: CEmbeddedItem(pContainerDoc)
{
	CString strItemName(pszItemName);
	SetItemName(strItemName);
	_stscanf(strItemName, _T("%d %d"), &m_nBeg, &m_nEnd);
}

CPadLinkItem::CPadLinkItem(CPadDoc* pContainerDoc, int nFrom, int nTo)
	: CEmbeddedItem(pContainerDoc)
{
	m_nBeg = nFrom;
	m_nEnd = nTo;
	TCHAR buf[30];
	wsprintf(buf, _T("%d %d"), m_nBeg, m_nEnd);
	SetItemName(buf);
}

void CPadLinkItem::OnShow()
{
	CPadDoc* pDoc = (CPadDoc*)GetDocument();
	ASSERT(pDoc != NULL);
	ASSERT_VALID(pDoc);
	ASSERT_KINDOF(CPadDoc, pDoc);
	pDoc->SetSelection(m_nBeg, m_nEnd);

	CEmbeddedItem::OnShow();
}

/////////////////////////////////////////////////////////////////////////////
