// ===========================================================================
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright 1996 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <wininet.h>

//==============================================================================
BOOL NeedAuth (HINTERNET hRequest)
{
    // Get status code.
    DWORD dwStatus;
    DWORD cbStatus = sizeof(dwStatus);
    HttpQueryInfo
    (
        hRequest,
        HTTP_QUERY_FLAG_NUMBER | HTTP_QUERY_STATUS_CODE,
        &dwStatus,
        &cbStatus,
        NULL
    );
    fprintf (stderr, "Status: %d\n", dwStatus);

    // Look for 401 or 407.
    DWORD dwFlags;
    switch (dwStatus)
    {
        case HTTP_STATUS_DENIED:
            dwFlags = HTTP_QUERY_WWW_AUTHENTICATE;
            break;
        case HTTP_STATUS_PROXY_AUTH_REQ:
            dwFlags = HTTP_QUERY_PROXY_AUTHENTICATE;
            break;            
        default:
            return FALSE;
    }

    // Enumerate the authentication types.
    BOOL fRet;
    char szScheme[64];
    DWORD dwIndex = 0;
    do
    {
        DWORD cbScheme = sizeof(szScheme);
        fRet = HttpQueryInfo
            (hRequest, dwFlags, szScheme, &cbScheme, &dwIndex);
        if (fRet)
            fprintf (stderr, "Found auth scheme: %s\n", szScheme);
    }
        while (fRet);

    return TRUE;
}


//==============================================================================
DWORD DoCustomUI (HINTERNET hConnect, HINTERNET hRequest)
{
    // Prompt for username and password.
    char  szUser[64], szPass[64];
    fprintf (stderr, "Enter Username: ");
    if (!fscanf (stdin, "%s", szUser))
        return ERROR_INTERNET_LOGIN_FAILURE;
    fprintf (stderr, "Enter Password: ");
    if (!fscanf (stdin, "%s", szPass))
        return ERROR_INTERNET_LOGIN_FAILURE;

    // Set the values in the handle.
    InternetSetOption
        (hConnect, INTERNET_OPTION_USERNAME, szUser, sizeof(szUser));
    InternetSetOption
        (hConnect, INTERNET_OPTION_PASSWORD, szPass, sizeof(szPass));

    // Drain the socket.
    BYTE bBuf[1000];
    DWORD cbBuf = sizeof(bBuf);
    DWORD cbRead;
    while (InternetReadFile (hRequest, bBuf, cbBuf, &cbRead) && cbRead);
    
    return ERROR_INTERNET_FORCE_RETRY;
}


//==============================================================================
int main (int argc, char **argv)
{
    HINTERNET hInternet = NULL;
    HINTERNET hConnect  = NULL;
    HINTERNET hRequest  = NULL;
    PSTR pszErr = NULL;
    BOOL fRet;
    
#define CHECK_ERROR(cond, err) if (!(cond)) {pszErr=(err); goto done;}

    // Check usage.
    if (argc < 2)
    {
        fprintf (stderr, "Usage:   httpauth [-c] <server> [<object> [<user> [<pass>]]]\n");
        fprintf (stderr, "  -c: Use custom UI to prompt for user/pass");
        exit (1);
    }

    // Parse arguments.
    BOOL fAllowCustomUI = FALSE;
    if (argc >= 2 && argv[1][0] == '-')
    {
        fAllowCustomUI = TRUE;
        argv++;
        argc--;
    }
    PSTR pszHost   = argv[1];
    PSTR pszObject = argc >= 3 ? argv[2] : "/";
    PSTR pszUser   = argc >= 4 ? argv[3] : NULL;
    PSTR pszPass   = argc >= 5 ? argv[4] : NULL;

    // Initialize wininet.
    hInternet = InternetOpen
    (
        "HttpAuth Sample",            // app name
        INTERNET_OPEN_TYPE_PRECONFIG, // access type
        NULL,                         // proxy server
        0,                            // proxy port
        0                             // flags
    );
    CHECK_ERROR (hInternet, "InternetOpen");

    // Connect to host.
    hConnect = InternetConnect
    (
        hInternet,                    // wininet handle,
        pszHost,                      // host
        0,                            // port
        pszUser,                      // user
        NULL,                         // pass
        INTERNET_SERVICE_HTTP,        // service
        0,                            // flags
        0                             // context
    );
    CHECK_ERROR (hConnect, "InternetConnect");

    // Work around InternetConnect disallowing empty passwords.
    InternetSetOption (hConnect, INTERNET_OPTION_PASSWORD,
        pszPass, lstrlen(pszPass)+1);
        
    // Create request.
    hRequest = HttpOpenRequest
    (
        hConnect,                     // connect handle
        "GET",                        // request method
        pszObject,                    // object name
        NULL,                         // version
        NULL,                         // referer
        NULL,                         // accept types
        INTERNET_FLAG_KEEP_CONNECTION // flags: keep-alive
             | INTERNET_FLAG_RELOAD,  // flags: bypass cache
        0                             // context
    );

resend:

    // Send request.
    fRet = HttpSendRequest
    (
        hRequest,                     // request handle
        "",                           // header string
        0,                            // header length
        NULL,                         // post data
        0                             // post length
    );

    // Handle any authentication dialogs.
    if (NeedAuth(hRequest) && fAllowCustomUI)
    {
        if (DoCustomUI (hConnect, hRequest) == ERROR_INTERNET_FORCE_RETRY)
            goto resend;
    }
    else
    {
        DWORD dwErr;
        dwErr = InternetErrorDlg
        (
            GetDesktopWindow(),                     
            hRequest,                               
            fRet ? ERROR_SUCCESS : GetLastError(),                         
            FLAGS_ERROR_UI_FILTER_FOR_ERRORS  |     
                FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS |
                FLAGS_ERROR_UI_FLAGS_GENERATE_DATA, 
            NULL
        );

        if (dwErr == ERROR_INTERNET_FORCE_RETRY)
            goto resend;
    }

    // Dump some bytes.
    BYTE bBuf[1024];
    DWORD cbBuf;
    DWORD cbRead;
    cbBuf = sizeof(bBuf);
    _setmode( _fileno( stdout ), _O_BINARY );
    while (InternetReadFile (hRequest, bBuf, cbBuf, &cbRead) && cbRead)
        fwrite (bBuf, 1, cbRead, stdout);
    
done: // Clean up.

    if (pszErr)
        fprintf (stderr, "Failed on %s, last error %d\n", pszErr, GetLastError());
    if (hRequest)
        InternetCloseHandle (hRequest);
    if (hConnect)
        InternetCloseHandle (hConnect);
    if (hInternet)
        InternetCloseHandle (hInternet);
    return 0;
}

