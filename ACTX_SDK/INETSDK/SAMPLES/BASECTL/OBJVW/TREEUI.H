#ifndef TREEUI_H

class CTreeUI
{
public:
	// Constructor/Destructor
	CTreeUI();
	~CTreeUI();

	// Creation function
	HRESULT Create(RECT*, HWND, HINSTANCE);

	// Kills all items
	HRESULT KillTreeItems();

    // Insert an item
    HRESULT InsertItem(LPSTR, LPVOID, LPVOID*);

private:
	//
	// Internal data members
	//
	// Tree view handle
	HWND		m_hwndTV;

    // bound rect
    RECT*       m_prc;

    // handle to parent window
    HWND        m_hwndParent;

    // module instance
    HINSTANCE   m_hinst;
};

#define TREEUI_H
#endif