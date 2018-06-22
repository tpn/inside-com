//=------------------------------------------------------------------------=
// LinkItem.h
//=------------------------------------------------------------------------=
// Copyright 1992-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// Definition of the CEmbeddedItem class
//

#ifndef __LINKITEM_H__
#define __LINKITEM_H__

class CPadDoc;
class CPadView;

class CPadLinkItem : public CEmbeddedItem
{
	DECLARE_DYNAMIC(CPadLinkItem)

// Constructors
public:
	CPadLinkItem(CPadDoc* pContainerDoc, LPCTSTR pszItemName);
	CPadLinkItem(CPadDoc* pContainerDoc, int nFrom, int nTo);

protected:
	virtual void OnShow();
};

#endif  // __LINKITEM_H__
