#ifndef GEN_H

// general definitions, handy macros and such

// Macros for covering COM functions

// Release a com interface and set pointer to null
#define ReleaseInterface(pi) if (pi) { (pi)->Release(); (pi) = NULL; }

// delete and null a pointer
#define KillPtr(p) { delete (p); (p) = NULL; }

// Goto label if failed, must have done label and hr defined to use this macro
#define IfComFailGoto(x) hr = x; if ( FAILED(hr) ) goto done;

// Return hresult from function if failed 
#define IfComFailRet(x) hr = x; if( FAILED(hr) ) return hr;

// memory allocation failure with hr goto
#define IfMemFailHRGoto(x) if (!x) { hr = ResultFromScode(E_OUTOFMEMORY); goto done; }

// If 0 and we want to set hr to efail and break
#define IfFailZeroBreak(x) if (!(x)){ hr = E_FAIL;  break; }

// WIN32 return with hresult must have done label
#define IfWin32FailHRGoto(x) if (!x) { hr = ResultFromScode(0x80070000 | GetLastError()); goto done; }

#define GEN_H
#endif
