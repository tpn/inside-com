#include "ipserver.h"
#include <commctrl.h>
#include "treeui.h"

//=--------------------------------------------------------------------------=
// CTreeUI::CTreeUI
//=--------------------------------------------------------------------------=
// Construct the tree UI class
//
// Parameters:
//
// Output:
//
// Notes:
//
CTreeUI::CTreeUI()
{
	InitCommonControls();
	m_hwndTV = (HWND)0;
    m_prc = NULL;
    m_hwndParent = NULL;
    m_hinst = NULL;
}


//=--------------------------------------------------------------------------=
// CTreeUI::InsertItem
//=--------------------------------------------------------------------------=
// Inserts an item in the tree view control
//
// Parameters:
//      LPSTR pszItemText   -   [in] item text
//      LPVOID pvTreeParent -   [in] HTREEITEM of parent tree node case to LPVOID
//      LPVOID* ppvTree     -   [out] pointer to HTREEITEM of outgoing node
//
// Output:
//      HRESULT NOERROR, E_FAIL
//
// Notes:
//
HRESULT CTreeUI::InsertItem
(
    LPSTR   pszItemText,
    LPVOID  pvTreeParent,
    LPVOID* ppvTree
)
{
    TV_ITEM         tvitem;
    TV_INSERTSTRUCT tvis;
    HTREEITEM*      ppTree = (HTREEITEM*)ppvTree;
    HTREEITEM       pTreeParent = (HTREEITEM)pvTreeParent;
    HTREEITEM       pretTree;

    tvitem.mask = TVIF_TEXT;
    tvitem.pszText = pszItemText;
    tvitem.cchTextMax = strlen(pszItemText);
    tvis.item = tvitem;
    tvis.hInsertAfter = (HTREEITEM)TVI_LAST;
    tvis.hParent = pTreeParent;
    pretTree = (HTREEITEM)SendMessage(m_hwndTV, TVM_INSERTITEM, 0, (LPARAM)&tvis);
    if ( !pretTree )
        return E_FAIL;
    
    if ( ppvTree )
        (*ppvTree) = (LPVOID)pretTree;

    return NOERROR;
}


//=--------------------------------------------------------------------------=
// CTreeUI::~CTreeUI
//=--------------------------------------------------------------------------=
// Destruct the object tree class
//
// Parameters:
//
// Output:
//
// Notes:
//
CTreeUI::~CTreeUI()
{
	if ( m_hwndTV ) 
	{
		DestroyWindow(m_hwndTV);
		m_hwndTV = (HWND)0;
	}
}


//=--------------------------------------------------------------------------=
// CTreeUI::Create
//=--------------------------------------------------------------------------=
// Initialize the object tree class
//
// Parameters:
//		RECT* prc	-		[in] pointer to rectangle that will bound the new 
//							control
//		HWND hwndParent	-	[in] handle to parent window for tree control
//		HINSTANCE hInst	-	[in] instance pointer
//
// Output:
//		HRESULT NOERROR, E_FAIL
//
// Notes:
//
HRESULT CTreeUI::Create
(
	RECT*		prc,
	HWND		hwndParent,
	HINSTANCE	hInst
)
{
    m_hinst = hInst;
    m_hwndParent = hwndParent;
    m_prc = prc;

	// Create the tree view control
	m_hwndTV = CreateWindowEx(
		0,
		WC_TREEVIEW,
		"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS,
		0,
		0,
		prc->right,
		prc->bottom,
		hwndParent,
		NULL,
		hInst,
		NULL);

	if ( !m_hwndTV )
		return ResultFromScode(E_FAIL);

	return NOERROR;
}


//=--------------------------------------------------------------------------=
// CTreeUI::KillTreeItems
//=--------------------------------------------------------------------------=
// Removes all items in the tree
//
// Parameters:
//
// Output:
//		HRESULT NOERROR, E_FAIL
//
// Notes:
//
HRESULT CTreeUI::KillTreeItems()
{
    return (TreeView_DeleteAllItems(m_hwndTV)?NOERROR:ResultFromScode(E_FAIL));
}