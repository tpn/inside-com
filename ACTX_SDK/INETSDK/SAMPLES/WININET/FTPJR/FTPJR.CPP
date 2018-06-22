//////////////////////////////////////////////////////////
//
//         FTP Jr  -- A Poor Man's FTP Client
//         Sample WinInet Application to demonstrate
//         The FTP APIs
//         Microsoft Corporation (C)
//
//////////////////////////////////////////////////////////

#include <iostream.h>
#include <windows.h>
#include <direct.h>
#include <wininet.h>

#define PROMPT  "FTP Jr>"

BOOL ParseCommand(char *, char *, char *);
BOOL Open (CHAR *);
BOOL Close ();
BOOL ErrorOut ( DWORD, CHAR *);
void FtpEnumDirectory ();
void lcd (char *);
void rcd (char *);
void type (char *);
void DisplayHelp();
void ShowUsage();

char arg1[256], arg2[256], arg3[256];
char szProxy[256] = "";
char szServer[256] = "";
char szCmdLine[256] = "";
HINTERNET hOpen, hConnect;
BOOL bActiveSession = FALSE;
DWORD dwType = FTP_TRANSFER_TYPE_BINARY;

void main(int argc, char *argv[])
{
	
	// Display our banner
	cout << "FTP Jr. WinInet FTP Sample Application" << endl;
	cout << "Microsoft Corporation" << endl << endl;
	
	// Do they want the display syntax?
	if ((lstrcmp(argv[1], "/?") == 0) ||
        (lstrcmp(argv[1], "?") == 0) ||
		(lstrcmp(argv[1], "-?") == 0) ||
		(lstrcmp(argv[1], "help") == 0) ||
        (lstrcmp(argv[1], "/help") == 0) ||
		(lstrcmp(argv[1], "/HELP") == 0) ||
		(lstrcmp(argv[1], "HELP") == 0))
	{
		ShowUsage();
		return;
	}

	switch (argc)
	{
	case 2:
		// Specified proxy, Open WININET.DLL w/ Proxy
		lstrcpy(szProxy, argv[1]);
        if ( !(hOpen = InternetOpen ( "FTP Jr (C)",  CERN_PROXY_INTERNET_ACCESS, szProxy, NULL, 0) ) )
        {
            ErrorOut ( GetLastError(), "InternetOpen");
           return ;
        }
        break;
    case 1:
		// No proxy specified.  Open WININET.DLL w/ local access
        if ( !(hOpen = InternetOpen ( "FTP Jr (C)",  LOCAL_INTERNET_ACCESS , NULL, 0, 0) ) )
        {
            ErrorOut ( GetLastError(), "InternetOpen");
            return ;
        }
        break;    
    default:
		ShowUsage();
		return;
	}

	cout << PROMPT;

	// Parse commands 1 line at a time
	while(TRUE)
	{
		char *pszArg1, *pszArg2, *pszArg3, *pszTemp;

		// Read line
		cin.getline(szCmdLine, 256);
		pszArg1 = szCmdLine;

		//Remove white space before 1st arg
		while((*pszArg1 != 0) &&
			  (*pszArg1 == ' ')) pszArg1++;

		pszArg2 = pszArg1;
		
		//Find end of 1st arg and zero terminate
		while ((*pszArg2 != 0) &&
			   (*pszArg2 != ' ')) pszArg2++;
		
		if (*pszArg2 != 0) *pszArg2++ = 0;

		//Remove white space before 2nd arg
		while ((*pszArg2 !=0) &&
			   (*pszArg2 == ' ')) pszArg2++;

		pszArg3 = pszArg2;

		//Find end of 2nd arg and zero terminate
		while ((*pszArg3 != 0) &&
			   (*pszArg3 != ' ')) pszArg3++;

		if (*pszArg3 != 0) *pszArg3++ = 0;

		//Remove white space before 3rd Arg
		while ((*pszArg3 !=0) &&
			   (*pszArg3 == ' ')) pszArg3++;

		pszTemp = pszArg3;

		//Find end of 3rd arg and zero terminate
		while((*pszTemp != 0) &&
			  (*pszTemp != ' ')) pszTemp++;

		if (*pszTemp != 0) *pszTemp = 0;

		//Loop indefintely until ParseCommand returns false
		if (ParseCommand(pszArg1, pszArg2, pszArg3) == FALSE)
			return;

	}
}

///////////////////////////////////////////////////////////
//
//      ParseCommand Function
//
//      Input:   FTP command arguments
//      Returns: TRUE if any command called but quit
//               FALSE if command is quit
//
//////////////////////////////////////////////////////////
BOOL ParseCommand(char *pszArg1, char *pszArg2, char *pszArg3)
{
	_strupr(pszArg1);
    CHAR szFile1[256] ="", szFile2[256] ="", szTemp[256];

	// Quit Command
	if (lstrcmp(pszArg1, "QUIT") == 0)
		return FALSE;
	
	// Get Command
	else if (lstrcmp(pszArg1, "GET") == 0)
	{
	    if (bActiveSession)
        {
            cout << "Enter RemoteFile LocalFile: ";
            cin >> szFile1 >> szFile2;
            cin.getline(szTemp, 256);
            if (!FtpGetFile (hConnect,szFile1, szFile2, FALSE,INTERNET_FLAG_RELOAD, dwType, 0 ) )
                ErrorOut (GetLastError(), "FtpGetFile");
        }
        else
            cout << "No active session" ;
        cout << endl << PROMPT;		
	}
	
	// Put Command
	else if (lstrcmp(pszArg1, "PUT") == 0)
	{
	    if (bActiveSession)
        {
            cout << "Enter LocalFile RemoteFile : ";
            cin >> szFile1 >> szFile2;
            cin.getline(szTemp, 256);
            if (!FtpPutFile (hConnect,szFile1, szFile2, dwType, 0 ) )
                ErrorOut (GetLastError(), "FtpPutFile");
        }
        else
            cout << "No active session" ;
        cout << endl << PROMPT;		
	}
	
	// Del Command
	else if (lstrcmp(pszArg1, "DEL") == 0)
	{
	    if (bActiveSession)
        {
            cout << "Enter RemoteFile : ";
            cin >> szFile1;
            cin.getline(szTemp, 256);
            if (!FtpDeleteFile (hConnect,szFile1 ) )
                ErrorOut (GetLastError(), "FtpDelFile");
        }
        else
            cout << "No active session" ;
        cout << endl << PROMPT;		
	}
	
	// Ren Command
	else if (lstrcmp(pszArg1, "REN") == 0)
	{
	    if (bActiveSession)
        {
            cout << "Enter ExistingFile NewFile : ";
            cin >> szFile1 >> szFile2;
            cin.getline(szTemp, 256);
            if (!FtpRenameFile (hConnect,szFile1, szFile2 ) )
                ErrorOut (GetLastError(), "FtpRenameFile");
        }
        else
            cout << "No active session" ;
        cout << endl << PROMPT;		
	
	}
	
	// ls command
	else if (lstrcmp(pszArg1, "LS") == 0)
	{
	    if (bActiveSession)
            FtpEnumDirectory();
        else
            cout << "No active session" ;
        cout << endl << PROMPT;
	}
	
	// md command
	else if (lstrcmp(pszArg1, "MD") == 0)
	{
	    if (bActiveSession)
        {
            cout << "Enter Directory : ";
            cin >> szFile1;
            cin.getline(szTemp, 256);
            if (!FtpCreateDirectory (hConnect,szFile1 ) )
                ErrorOut (GetLastError(), "FtpCreateDirectory");
        }
        else
            cout << "No active session" ;
        cout << endl << PROMPT;		
	}

	// rd command
	else if (lstrcmp(pszArg1, "RD") == 0)
	{
	    if (bActiveSession)
        {
            cout << "Enter Directory : ";
            cin >> szFile1;
            cin.getline(szTemp, 256);
            if (!FtpRemoveDirectory (hConnect,szFile1 ) )
                ErrorOut (GetLastError(), "FtpRemoveDirectory");
        }
        else
            cout << "No active session" ;
        cout << endl << PROMPT;		
	}

	// type command
	else if (lstrcmp(pszArg1, "TYPE") == 0)
	{
        if (bActiveSession)
            type (pszArg2);
        else
            cout << "No active session" << endl << PROMPT;
	}   
    
	// cd command
	else if (lstrcmp(pszArg1, "CD") == 0)
	{
        if (bActiveSession)
            rcd (pszArg2);
        else
            cout << "No active session" << endl << PROMPT;
	}

	// lcd command
	else if (lstrcmp(pszArg1, "LCD") == 0)
	{
		lcd(pszArg2);
	}
	
	// open command
	else if (lstrcmp(pszArg1, "OPEN") == 0)
	{
        if (!bActiveSession)
        {
    	    if (Open (pszArg2))
                cout << "Connected to " << pszArg2 << endl << PROMPT;
            else
                cout << "Session closed" << endl << PROMPT;    
        } 
        else
            cout << "Already connected to " << szServer << endl << PROMPT;
           
	}

	// close command
	else if (lstrcmp(pszArg1, "CLOSE") == 0)
	{
        if (bActiveSession)
        {
    	    Close();
            cout << "Session closed" << endl << PROMPT;
        }
        else
            cout << "No active session" << endl << PROMPT;
	}
	
	// help command
	else if (lstrcmp(pszArg1, "HELP") == 0)
	{
		DisplayHelp();
	}
	
	// error Unknown command
	else
	{
		cout << "?Unknown Command" << endl << PROMPT;
	}
	return TRUE;
}

void DisplayHelp()
{
	cout << "Commands are:" << endl;
	cout << "   cd" << endl;
	cout << "   close" << endl;
	cout << "   del" << endl;
	cout << "   get" << endl;
	cout << "   help" << endl;
	cout << "   lcd" << endl;
	cout << "   ls" << endl;
	cout << "   md" << endl;
	cout << "   open" << endl;
	cout << "   put" << endl;
	cout << "   quit" << endl;
	cout << "   rd" << endl;
	cout << "   ren" << endl;
	cout << "   type" << endl;
    ShowUsage ();
	cout << endl << PROMPT;
}

void lcd(char *pszDir)
{
	if ((*pszDir != 0) && (_chdir(pszDir) == -1))
		cout << "?Invalid Local Directory" << endl << PROMPT;
	else
	{
		char dir[256];
		GetCurrentDirectory(256, dir);
		cout << "Local Directory is " << dir << endl << PROMPT;
	}
}

void rcd(char *pszDir)
{
    char dir[256];
	if (*pszDir != 0)
    {
		if (!FtpSetCurrentDirectory (hConnect, pszDir))
        {
            ErrorOut (GetLastError(), "FtpSetCurrentDirectory");
            cout <<  PROMPT;
        }
        else    
    		cout << "Remote Directory is " << pszDir << endl << PROMPT;
    }    
	else
	{
        DWORD dwSize = sizeof(dir);
		if (!FtpGetCurrentDirectory (hConnect, dir, &dwSize))
            cout << "Can not determine current remote directory " << endl << PROMPT;
        else    
    		cout << "Remote Directory is " << dir << endl << PROMPT;
	}
}

void type (char *szType)
{
    
	_strupr(szType);    
	if (*szType != 0)
    {
	    if (lstrcmp(szType, "BIN") == 0)
        {
		    dwType = FTP_TRANSFER_TYPE_BINARY;
            cout << "BIN mode selected";
        }
    	else if (lstrcmp(szType, "ASCII") == 0)
        {
		    dwType = FTP_TRANSFER_TYPE_ASCII;
            cout << "ASCII mode selected";
        }
        else
            cout << "Invalid mode";
        cout << endl << PROMPT;    
    }    
	else
	{
		if ( dwType == FTP_TRANSFER_TYPE_BINARY)
            cout << "BIN ";
        else    
    		cout << "ASCII ";
        cout << "mode selected " << endl << PROMPT;    
	}
}


void ShowUsage()
{
	cout << "Syntax:" << endl << "  FTPJR <proxy>" << endl ;
    cout << "Note: a CERN style proxy will not work. You will need to "<< endl;
    cout << "specify a TIS style FTP proxy in the form:" << endl << endl;
	cout << "     FTPJR ftp-gw" << endl << endl;
	cout << "where ftp-gw is the name of the host that is running the gateway" << endl;
}

BOOL Open (CHAR * szHost)
{
    CHAR szUser[256], szPass[256];
    if ( *szHost == 0)
    {
        cout << "Enter host, user, pass: ";
        cin >> szHost >> szUser >> szPass;
    }
    else
    {
        cout << "Enter user, pass: ";
        cin >> szUser >> szPass;
    }
    CHAR szTemp[256];
    cin.getline(szTemp, 256);
    if ( !(hConnect = InternetConnect ( hOpen, szHost , INTERNET_INVALID_PORT_NUMBER, szUser,  szPass, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE , 0) ) )
    {
    	ErrorOut (GetLastError(), "InternetConnect");
        return FALSE;
    }
    bActiveSession = TRUE;
    lstrcpy (szServer, szHost);
    return TRUE;
}

BOOL Close ()
{
    if (!InternetCloseHandle (hConnect) )
    {
        ErrorOut (GetLastError(), "InternetCloseHandle");
        return FALSE;
    }
    bActiveSession = FALSE;
    return TRUE;
}
    
void FtpEnumDirectory ()
{
	WIN32_FIND_DATA pData;
	HINTERNET hFind;
	DWORD dError;

	// Start enumeration and get file handle
	if ( !(hFind = FtpFindFirstFile (hConnect, TEXT ("*.*"), &pData, 0, 0) ))
		if (GetLastError()  == ERROR_NO_MORE_FILES) 
		{
			cout << "This directory is empty" << endl;
			return ;
		}
		else
		{
			ErrorOut (GetLastError (), "FindFirst error: ");
			return ;
		}

	cout << pData.cFileName;
	if (pData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		// Entry is a directory, mark it as such
		cout << " <DIR> " << endl;
	else
		cout << endl;

	dError = NO_ERROR;
	do
	{
		 if (!InternetFindNextFile (hFind, &pData))
		 {
			 dError = GetLastError();
			 if ( dError == ERROR_NO_MORE_FILES ) 
				break;
			 else
			 {
				 ErrorOut (dError, "InternetFindNextFile");
				 return ;
			 }
		 }
		 else
		 {
				cout << pData.cFileName;
				if (pData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
					cout << " <DIR> " << endl;
				else
					cout << endl;
			 }
	}
	while ( TRUE);
	if (!InternetCloseHandle (hFind) )
	{
		ErrorOut (GetLastError(), "InternetCloseHandle error");
		return ;
	}
	return ;
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
 