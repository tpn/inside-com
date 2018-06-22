PURPOSE:

The httpauth sample demonstrates how to handle HTTP authentication using 
either the InternetErrorDlg function or a custom user interface.  The sample 
accepts an optional flag and a server address.  If authentication is needed and the 
flag was not set, a dialog box that requests a username and password will 
appear.  If authentication is needed and the flag was set, the custom user 
interface, NeedAuth, will be used by the sample code.  After the authentication 
is accepted (or if there was no authentication required), the sample returns the 
default HTML document.  


COMMENTS:

The sample utilizes the Internet settings from the registry to determine whether 
to use a direct connection or a proxy connection.  HttpOpenRequest uses the 
INTERNET_FLAG_KEEP_CONNECTION flag, which is required by 
Microsoft Network (MSN), NT LAN Manager (NTLM), and other types of 
authentication.  The custom user interface, NeedAuth,  prompts for the 
username and password on the command line.


USAGE:

To use InternetErrorDlg to perform authentication:
	C:>httpauth.exe www.server.name

To use the custom user interface (NeedAuth):
	C:>httpauth -c www.server.name


