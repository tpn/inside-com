 PURPOSE: 
 This sample demonstrates how to create and submit HTTP 
 request. Sample requests the default HTML document from the
 server and then display it along with the HTTP transition headers.
 This sample also allows to access password protected pages. It 
 checks for HTTP server response code and it is "401 Access Denied"
 it asks password and user name and then resubmit request.
 Note that is only works with the Basic authentication scheme, since 
 this scheme is built into WinInet APIs. Please see documentation for
 WinInet APIs for more details.

 COMMENTS: 
 This sample can either work with the direct access to the Internet or
 via proxy server.
 
 USAGE:
 With direct connection to the Internet:
	C:> headdump.exe www.server.name
 Via proxy server:
	C:> headdump.exe www.server.name http://MyProxyServer:ProxyPort

 Note that sample continuously output information on the screen, so use like
 this:
 	C:> headdump.exe www.server.name | more

 This sample has been tested under Windows NT 4.0 Beta and Windows 95.


To build the HeadDump sample from the command line, first run 
setenv.bat to be  sure the Internet SDK include, bin, and lib directories 
are included in  your environment. Type  "nmake" at the command line 
to compile the  sample (using the default makefile supplied).
