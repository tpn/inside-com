#ifndef WINTREE_H
#include "gen.h"
#include "exdisp.h"

//
// Definition for maximum size of output string in tree control incl. NULL
// and some other string oriented things
//
#define TV_MAXSTRLEN    513
#define TV_SZNONAME     "Unknown Name"
#define TV_SZNOCLASS    "No Class Info"
#define TV_MAXWINNAME   129
#define TV_SZLOCATION   "Unknown Location"
#define TV_SZNOCTN      "Control Information Unavailable"


//
// This is curious but there is no header file that contains this definition so
// I define it here
//
#define GUIDKIND_CLSID  6


//
// Macros for failure testing
//
#define IfFailBreak(x) if ( FAILED((hr = (x))) ) break;

//
// Class that manages a single frame in the document hierarchy
//
class CWindow;
class CWinTree;
class CWindow
{
	friend CWinTree;
public:
	// constructor/destructor
	//
	CWindow(IWebBrowser* pIWebBrowser) 
	{ 
		m_pIWebBrowser = pIWebBrowser; 
		m_rgpwindFrames = NULL;
		m_lFrameCount = 0;
		m_pIOleCtn = NULL;
		m_pIOmWindow = NULL;
		m_lidx = 0;
        m_pvParentTree = NULL;
        m_pvTree = NULL;
	}
	virtual ~CWindow()
    {
        ReleaseInterface(m_pIOleCtn);
        ReleaseInterface(m_pIOmWindow);
        if ( m_rgpwindFrames )
            delete [] m_rgpwindFrames;
    }

protected:
	// Private Data members
	//
	// List of frames for this window
	CWindow**		m_rgpwindFrames;

	// Count of frames
	LONG			m_lFrameCount;

    // frame index 
    LONG            m_lidx;

	// This window's associated IOleContainer interface
	IOleContainer*	m_pIOleCtn;

	// The window's associated IOmWindow interface
	LPDISPATCH		m_pIOmWindow;

    // The window's parent UI tree node
    LPVOID          m_pvParentTree;

    // The window's UI tree node
    LPVOID          m_pvTree;

	// IWebBrowser interface pointer
	IWebBrowser*	m_pIWebBrowser;
};


//
// Class to manage stack for tree manipulation, specifically deleting the tree
//
class CWinStack
{
public:
    CWinStack()
    {
        psnTop = NULL;
    }
    virtual ~CWinStack()
    {
        struct sn* psn;

        while ( psnTop )
        {
            psn = psnTop->pnext;
            delete psnTop;
            psnTop = psn;
        }
    }

    HRESULT Push(CWindow* pwin)
    {
        HRESULT hr = NOERROR;
        struct sn* psn = new struct sn;
        IfMemFailHRGoto(psn);
        psn->pwin = pwin;
        psn->pnext = psnTop;
        psnTop = psn;

    done:
        return hr;
    }

    CWindow* Pop()
    {
        CWindow* pwin;
        struct sn* psn;
        if ( Empty() )
            return NULL;
        pwin = psnTop->pwin;
        psn = psnTop->pnext;
        delete psnTop;
        psnTop = psn; 
        return pwin;
    }

    BOOL Empty()
    {
        return (psnTop?FALSE:TRUE);
    }

private:
    // stack node structure
    struct sn
    {
        CWindow*    pwin;
        struct sn*  pnext;
    } *psnTop;
};


// 
//
// Class to manage queue for tree manipulation
//
class CWinQueue
{
public:
	// constructor/destructor
	//
	CWinQueue() 
	{
		pqnHead = pqnTail = NULL;
	}
	virtual ~CWinQueue()
	{
		struct qn* pqn;
		pqn = pqnHead;
		while ( pqn )
		{
			pqn = pqn->pnext;
			delete pqnHead;
			pqnHead = pqn;
		}
		pqnTail = pqnHead;
	}

	// Put an element on the queue
	HRESULT Put(CWindow* pwin)
	{
		HRESULT	hr = NOERROR;
		if ( !pqnTail )		
		{
			pqnTail = new struct qn;
			IfMemFailHRGoto(pqnTail);
			pqnHead = pqnTail;
		}
		else
		{
			pqnTail->pnext = new struct qn;
			IfMemFailHRGoto(pqnTail->pnext);
			pqnTail = pqnTail->pnext;
		}
		pqnTail->pwin = pwin;
		pqnTail->pnext = NULL;
    done:
		return hr;
	}

	// Get an element from the queue
	CWindow* Get()
	{
		CWindow* pwin; 
		struct qn*	pqn;
		pqn = pqnHead;
		pwin = pqnHead->pwin;
		if ( pqnHead )
		{
			pqn = pqnHead->pnext;
			delete pqnHead;
			pqnHead = pqn;
			if ( !pqnHead )
				pqnTail = pqnHead;
		}
		return pwin;
	}

	BOOL Empty()
	{
		return (!pqnHead);
	}

private:
	// private members
	//
	// Queue structure
	struct qn
	{
		CWindow*	pwin;
		struct qn*  pnext;
	}*pqnHead, *pqnTail;
};

//
// Class that manages a tree of windows that represent the document structure of the 
// current HTML document
//
class CWinTree
{
public:
	// constructor/destructor
	//
	CWinTree();
	virtual ~CWinTree();

	// Builds a document tree
	//
	HRESULT BuildTree(IWebBrowser*, CTreeUI*);

    // Add actual UI node
    //
    HRESULT AddUIParentNode(CWindow*);

    // Determione if the tree has been build once or not
    BOOL AlreadyCreated() { return (m_pwindRoot?TRUE:FALSE); }

    // Reset the tree
    void Reset();

private:
	// Private data
	//
	// Root of document tree
	CWindow*	m_pwindRoot;

	// pointer to UI class
	CTreeUI*	m_pTreeUI;

	// queue
	CWinQueue*	m_pwinqueue;

    // count of total windows from root document down
    LONG        m_cWin;

	// Helper functions
	//
	// Get ole container and scripting window interface of browser document if they exist
	HRESULT GetOleContainerAndWindow(CWindow*);

	// Enumerate frames from the current window
	HRESULT EnumerateFrames(CWindow*);

    // Enumerate controls
    HRESULT CWinTree::EnumerateControls(CWindow*);

    // Set no name string
    void SetNoName(LPSTR);

    // Set no class info string
    void SetNoClassInfo(LPSTR);

    // Set class info from registry
    void SetControlInfoFromReg(CLSID, LPSTR);

    // Get info about the control
    HRESULT GetControlInfo(LPUNKNOWN,LPSTR);

    // Set name from dispatch property
    HRESULT SetName(VARIANT*, LPSTR);
};

#define WINTREE_H
#endif