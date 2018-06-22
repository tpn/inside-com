/****************************************************************************
*
* HeadDump: requests the default HTML document from the server and prints 
*			along with HTTP headers.
*			Microsoft Corporation (C). Leon Braginski.
*	
* PURPOSE: 
* This sample demonstrates how to create and submit HTTP 
* request. Sample requests the default HTML document from the
* server and then display it along with the HTTP transaction headers.
* This sample also allows to access password protected pages. It 
* checks for HTTP server response code and it is "401 Access Denied"
* it asks password and user name and then resubmit request.
* Note that is only works with the Basic authentication scheme, since 
* this scheme is built into WinInet APIs. Please see documentation for
* WinInet APIs for more details.
*
* COMMENTS: 
* This sample can either work with the direct access to the Internet or
* via proxy server.
* 
* USAGE:
* With direct connection to the Internet:
*	C:> headdump.exe www.server.name
* Via proxy server:
*	C:> headdump.exe www.server.name http://MyProxyServer:ProxyPort
*
* Note that sample continuously output information on the screen, so use like
* this:
* 	C:> headdump.exe www.server.name | more
*
* This sample has been tested under Windows NT 4.0 Beta and Windows 95.
* 
****************************************************************************/



#include <windows.h>
#include <wininet.h>
#include <iostream.h>

BOOL ErrorOut  ( DWORD dError, TCHAR * szCallingFunc);

int main (int argc, char *argv[])
{
 HINTERNET hOpen, hConnect, hReq;
 DWORD  dwSize, dwCode;
 CHAR *lpBuffer, szData[51];


switch (argc)
{
    case 1:
    {
        cerr << "Usage: " << argv[0] <<" host [proxy]" << endl;
        cerr << "\twhere host is a HTTP server such as www.server.com" << endl;
        cerr << "\tand proxy is optional proxy in form: http://proxy:80" << endl;
        return 0;
    }
    case 2:
    {
        if ( !(hOpen = InternetOpen ( "HeadDump",  LOCAL_INTERNET_ACCESS , NULL, 0, 0) ) )
        {
            ErrorOut ( GetLastError(), "InternetOpen");
            return 0;
        }
        break;
    }
    case 3:
    {
       if ( !(hOpen = InternetOpen ( "HeadDump",  CERN_PROXY_INTERNET_ACCESS, argv[2], NULL, 0) ) )
       {
            ErrorOut ( GetLastError(), "InternetOpen");
           return 0;
       }
       break;
    }
 }   
        

if ( !(hConnect = InternetConnect ( hOpen, argv[1] , INTERNET_INVALID_PORT_NUMBER, "",  "", INTERNET_SERVICE_HTTP, 0  , 0) ) )
{
    ErrorOut (GetLastError(), "InternetConnect");
    return 0;
}

if ( !(hReq = HttpOpenRequest (hConnect, "GET", "", HTTP_VERSION, "", NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE ,0 )))
{
    ErrorOut (GetLastError(), "HttpOpenRequest");
    return 0;
}


again:
if (!HttpSendRequest (hReq, NULL, 0, NULL, 0) )
{
    ErrorOut (GetLastError(), "HttpSend");
    return 0;
}

dwSize = sizeof (DWORD) ;  
if ( !HttpQueryInfo (hReq, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwCode, &dwSize, NULL))
{
	ErrorOut (GetLastError(), "HttpQueryInfo");
	return FALSE;
}

if ( dwCode == HTTP_STATUS_DENIED || dwCode == HTTP_STATUS_PROXY_AUTH_REQ)
{  
    // This is a secure page.
    cerr << "This page is password protected. " << endl;
	CHAR szUser[50]="";
	CHAR szPass[50]="";

	cerr << "User: ";
	cin  >> szUser;
	cerr << "Pass: ";
	cin  >> szPass;


    // We have to read all outstanding data on the Internet handle
    // before we can resubmit request. Just discard the data.
    do
	{
		InternetReadFile (hReq, (LPVOID)szData, 50, &dwSize);
	}
	while (dwSize != 0);

 
    if ( !InternetSetOption (hConnect, INTERNET_OPTION_USERNAME, (LPVOID) szUser, lstrlen (szUser) ))
    {
        cerr << "InternetSetOptionFailed: " << GetLastError() << endl;
        return FALSE;
    }
    
    if ( !InternetSetOption (hConnect, INTERNET_OPTION_PASSWORD, (LPVOID) szPass, lstrlen (szPass) ))
    {
        cerr << "InternetSetOptionFailed: " << GetLastError() << endl;
        return FALSE;
    }
	goto again;
}




// First time we will find out the size of the headers.
HttpQueryInfo (hReq,HTTP_QUERY_RAW_HEADERS_CRLF,  NULL, &dwSize, NULL);
lpBuffer =  new char [dwSize + 1 ];

// Now we call HttpQueryInfo again to get the headers.
if (!HttpQueryInfo (hReq,HTTP_QUERY_RAW_HEADERS_CRLF, (LPVOID) lpBuffer,
    &dwSize, NULL))
{
	ErrorOut (GetLastError(), "HttpQueryInfo");
	return FALSE;
}
*(lpBuffer + dwSize) = '\0';
cout << lpBuffer << endl;

// We can relay on the CONTENTS_LENGTH header to find the size of the 
// HTML file, since this header may not exist (it is optional for HTTP/1.0
do
{
	if (!InternetReadFile (hReq, (LPVOID)szData, 50, &dwSize) )
	{
	 	ErrorOut (GetLastError (), "InternetReadFile");
		return FALSE;
	}
	if ( !dwSize)
		break;
	else
	{
		szData [dwSize] = '\0'; 
		cout << szData;
	}
}
while (TRUE);
cout << endl;

if (!InternetCloseHandle (hReq) )
{
    ErrorOut (GetLastError (), "CloseHandle on hReq");
    return FALSE;
}
if (!InternetCloseHandle (hConnect) )
{
    ErrorOut (GetLastError (), "CloseHandle on hConnect");
    return FALSE;
}
if (!InternetCloseHandle (hOpen) )
{
    ErrorOut (GetLastError (), "CloseHandle on hOpen");
    return FALSE;
}


free (lpBuffer);
return TRUE;
}

/****************************************************************************
*
*    FUNCTION: ErrorOut
*
*    PURPOSE: This function is used to get extended Internet error.
*
*    COMMENTS:  Function returns TRUE on success and FALSE on failure.
*
****************************************************************************/

BOOL ErrorOut ( DWORD dError, TCHAR * szCallFunc)
{
    TCHAR szTemp[100] = "", *szBuffer=NULL, *szBufferFinal = NULL;
    DWORD  dwIntError , dwLength = 0; 
    wsprintf (szTemp,  "%s error %d\n ", szCallFunc, dError );
	if (dError == ERROR_INTERNET_EXTENDED_ERROR)
	{
		InternetGetLastResponseInfo (&dwIntError, NULL, &dwLength);
		if (dwLength)
		{
			if ( !(szBuffer = (TCHAR *) LocalAlloc ( LPTR,  dwLength) ) )
			{
				lstrcat (szTemp, TEXT ( "Unable to allocate memory to display Internet error code. Error code: ") );
				lstrcat (szTemp, TEXT (_itoa (GetLastError(), szBuffer, 10)  ) );
				lstrcat (szTemp, TEXT ("\n") );
				cerr << szTemp << endl;
				return FALSE;
			}
			if (!InternetGetLastResponseInfo (&dwIntError, (LPTSTR) szBuffer, &dwLength))
			{
				lstrcat (szTemp, TEXT ( "Unable to get Intrnet error. Error code: ") );
				lstrcat (szTemp, TEXT (_itoa (GetLastError(), szBuffer, 10)  ) );
				lstrcat (szTemp, TEXT ("\n") );
				cerr << szTemp << endl;
				return FALSE;
			}
			if ( !(szBufferFinal = (TCHAR *) LocalAlloc ( LPTR,  (strlen (szBuffer) +strlen (szTemp) + 1)  ) )  )
			{
				lstrcat (szTemp, TEXT ( "Unable to allocate memory. Error code: ") );
				lstrcat (szTemp, TEXT (_itoa (GetLastError(), szBuffer, 10)  ) );
				lstrcat (szTemp, TEXT ("\n") );
				cerr << szTemp << endl;
				return FALSE;
			}
			lstrcpy (szBufferFinal, szTemp);
			lstrcat (szBufferFinal, szBuffer);
			LocalFree (szBuffer);
			cerr <<  szBufferFinal  << endl;
			LocalFree (szBufferFinal);
		}
	}
	else
        cerr << szTemp << endl;
    return TRUE;
}
