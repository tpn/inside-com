//----------------------------------------------------------------------
//       Copyright (C) 1993-1996 Microsoft Corporation.
//       All rights reserved.
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	WebPost API usage example
//
//  This example allows the user to post files to a web site.
//
//----------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <wpapi.h>
#include <wpspi.h>

#include "wbpost.h"


LONG
SimpleWebPost( LPTSTR lpszFileName )
{
	LONG 	lRet;
	DWORD   cFiles = 0;
	LPTSTR *ppszFiles = NULL;

	if (lpszFileName) {
		ppszFiles = &lpszFileName;
		cFiles = 1;
	}

	printf("Calling WpPost(...,%s,...)\n", lpszFileName);

	lRet = WpPost(	NULL,		// hWin
			cFiles,		// count of files
			ppszFiles,	// file list
			NULL,		// lpcbSiteName
			NULL,		// lpszSiteName
			NULL,		// lpcbURL
			NULL,		// lpszURL
			0 );		// flags
	
	printf("WpPost returned %d\n", (int)lRet);
	
	return lRet;
}

LONG
ListSites()
{
	static TCHAR	buffer[8192];
	LPWPSITEINFO	lpbSites;
	DWORD		cSites, cbSites, lRet, i;

	cbSites = sizeof( buffer );
	cSites = 0;
	lpbSites = (LPWPSITEINFO) buffer;

	printf("Calling WpListSites()\n");

	lRet = WpListSites( &cbSites, lpbSites, &cSites );

	printf("WpListSites() returned %d\n", lRet);

	if (lRet)
		return lRet;
	
	printf("Total Sites: %d\n", cSites);


	for (i = 0; i < cSites; i++, lpbSites++)
		printf("%d. SiteName=%s\n", i, lpbSites->lpszSiteName);
	
	return lRet;
}

//
// The next function illustrates getting a pointer to the web post
// provider's interface and calling the functions in that interface.
//

LONG
AdvancedWebPost( LPTSTR lpszSiteName, LPTSTR lpszFileName )
{
	DWORD	lRet;
	IWPSite	*lpSite = NULL;
	DWORD	cbURL = 0;

	printf("Calling WpBindToSite(..., %s, ...)\n", lpszSiteName);

	lRet = WpBindToSite(	NULL,		// hWin
				lpszSiteName,
				NULL,		// lpszURL
				0,		// fdwFlags
				0,		// dwReserved
				(PVOID *)&lpSite );	// Interface pointer
	
	printf("WpBindToSite returned %d\n", lRet);

	if (lRet)
		return lRet;

	lRet = lpSite->NetworkConnect(NULL, NULL);
	printf("NetworkConnect returned %d\n", HRESULT_CODE(lRet));
	if (lRet)
		goto cleanup;

	lRet = lpSite->ServerLogin(NULL, NULL);
	printf("ServerLogin returned %d\n", HRESULT_CODE(lRet));
	if (lRet)
		goto cleanup;
	
	printf("Calling PostFiles(...,%s,..)\n", lpszFileName);

	lRet = lpSite->PostFiles(	1,	// cLocalPaths
					&lpszFileName,
					&cbURL,	// lpcbURL
					NULL,	// lpszURL
					0 );	// fdwFlags
	
	printf("PostFiles returned %d\n", HRESULT_CODE(lRet));

	lRet = lpSite->ServerLogout();
	printf("ServerLogout returned %d\n", HRESULT_CODE(lRet));
	if (lRet)
		goto cleanup;

	lRet = lpSite->NetworkDisconnect();
	printf("NetworkDisconnect returned %d\n", HRESULT_CODE(lRet));

cleanup:
	lRet = lpSite->Release();
	printf("Release returned %d\n", HRESULT_CODE(lRet));

	return lRet;
}
void
usage(void)
{
	printf("Usage: wbpost [-s sitename] [filename]\n");
	printf("       wbpost -l\t\t: lists the web sites\n");
	exit(1);
}

int __cdecl
main(int argc, char *argv[])
{
	LPTSTR	lpszSiteName = NULL, lpszFileName = NULL;
	int	fList = 0;
	LONG	lRet;
	char	c;

	// parse the arguments

	while (--argc > 0 && (*++argv)[0] == '-')
		if (c = *++argv[0])
			switch (c) {
			case 'l':
				fList = 1;
				break;
			case 's':
				if (--argc)
				  lpszSiteName = *++argv;
				break;
			default:
				printf("Error: illegal option %c\n", c);
				usage();
				break;
			}
	if (argc == 1) {
		lpszFileName = *argv;
		argc--;
	}
	
	if (argc)
		usage();
	
	// call the apis

	if (fList)
		lRet = ListSites();
	else if (lpszSiteName)
		lRet = AdvancedWebPost(lpszSiteName, lpszFileName);
	else
		lRet = SimpleWebPost(lpszFileName);
	
	return lRet;
}
