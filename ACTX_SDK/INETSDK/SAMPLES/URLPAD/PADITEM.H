//=------------------------------------------------------------------------=
// PadItem.h
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

#ifndef __PADITEM_H__
#define __PADITEM_H__

class CPadDoc;
class CPadView;

class CEmbeddedItem : public COleServerItem
{
	DECLARE_DYNAMIC(CEmbeddedItem)

// Constructors
public:
	CEmbeddedItem(CPadDoc* pContainerDoc);

// Attributes
	UINT m_nBeg, m_nEnd;
	CPadDoc* GetDocument() const
		{ return (CPadDoc*) COleServerItem::GetDocument(); }
	CPadView* GetView() const;

// Implementation
public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);

protected:
	virtual BOOL OnRenderFileData(LPFORMATETC lpFormatEtc, CFile* pFile);
	virtual void Serialize(CArchive& ar);   // overridden for document i/o

	void SaveToFile(CFile* pFile);
};

#endif  // __PADITEM_H__
