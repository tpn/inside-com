//=------------------------------------------------------------------------=
// PadDoc.h
//=------------------------------------------------------------------------=
// Copyright 1992-1996 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// Definition of the CPadDoc class
//

#ifndef __PADDOC_H__
#define __PADDOC_H__

class CEmbeddedItem;

class CPadDoc : public COleServerDoc
{
	DECLARE_DYNCREATE(CPadDoc)

// Constructors
public:
	CPadDoc();

//Operations
public:
	void SetSelection(int nBeg, int nEnd);

// Implementation
public:
	virtual COleServerItem* OnGetEmbeddedItem();
	virtual COleServerItem* OnGetLinkedItem(LPCTSTR lpszItemName);

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void DeleteContents();
	virtual ~CPadDoc();

	//{{AFX_MSG(CPadDoc)
	afx_msg void OnViewUpdatenow();
	afx_msg void OnCancelInplace();
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CEmbeddedItem;

public:
	BOOL m_urlflag;
	CString m_urlfile;
};

#endif  // __PADDOC_H__

/////////////////////////////////////////////////////////////////////////////
