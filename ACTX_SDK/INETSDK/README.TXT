=======================================================================

Release notes for the Microsoft ActiveX Development Kit:

Copyright (c) Microsoft Corporation, 1996
=======================================================================


Note: If you did not access this document from \INetSDK\Help\Default.htm, 
that is probably a better place to begin reading documentation.  This 
readme.txt is the second URL in that document's right hand frame.

-----------------------------------------------------
WELCOME TO THE ACTIVEX SDK:
-----------------------------------------------------
Welcome to the Microsoft ActiveX Software Development Kit. These are the 
release notes of the November'96 release of the ActiveX SDK.  It 
is intended to be installed with the Internet Explorer 3.01 (final
version) and the latest release of the  Win32 SDK (dated Aug. 96).  The 
operating system for this release of the SDK is intended to 
be Windows 95 or Windows NT 4.0 SUR (final version).

Here's a brief description of the contents of this folder, followed
by release notes.

BIN       SDK Tools, Redistributables, DLLs and self extracting .exe's
HELP      HTML reference files for all SDK components
INCLUDE   Include files for Win32 Internet Services and OLE Interfaces
LIB       Libraries for the ActiveX SDK
LICENSE	  License for ActiveX SDK and Redistributable components.
SAMPLES   ActiveX SDK Samples
SPECS     Additional SDK documentation not yet in HTML references.

-----------------------------------------------------
PREREQUISITE OF THIS RELEASE OF THE ACTIVEX SDK:
-----------------------------------------------------
Notes on which VC++, MFC, Internet Explorer, and Win32 SDK are required.

This release introduces for the first time development support for RISC
(Alpha, MIPs, and PowerPC).  This is early beta level support for
RISC.  This release of the ActiveX SDK requires that you have downloaded 
and installed:
* Internet Explorer 3.01. (final version)
  (http://www.microsoft.com/ie/iedl.htm) 
* The latest Win32 SDK (dated Aug '96, available on 
  MSDN Level II.)
* Windows 95 or Windows NT 4.0 SUR (final version)
* A compiler: 
  for Intel, Microsoft Visual C++ 4.1 is the most tested.
  Do not use VC++ 4.2, unless you have obtained the VC++ 4.2b patch
  on the web at http://www.microsoft.com/visualc.  

  For RISC development you should use VC++ 4.0a.  (later versions of 
  MFC, which is needed for some of the samples, is not yet available 
  on all RISC platforms).

  If you are using VC++ 4.2b, you will need to modify the URLPad's
  MAKEFILE in order to get the sample to build.   You will need to
  uncomment (remove the "#" symbol from) the line that reads
    # _MFC_LIB_ = 42

  If you use MFC 4.2 in your sample development, you should include
  that line to your makefile if you include INetSDK.MAK. 

If you have Visual C++ 4.1 and the later release of the Win32 SDK,
you should set your environment variables by executing the following
commands on your command line (note, make exceptions to make sure 
you go the correct directories)

  cd c:\msdev\bin
  vcvars32 x86
  cd c:\mstools
  setenv c:\mstools
  cd c:\inetsdk
  setenv c:\inetsdk

Assuming the above file structure represents your installation, you
you can cut and paste the following into a batch file and execute it before
building samples.  This assumes you are building on an Intel machine; use 
the string "mips", "alpha", or "ppc" accordingly in place of "x86" below.

	REM Batch file starts here.
	set lib =
	set include=

	c:
	cd c:\msdev\bin
	call vcvars32 x86
	cd c:\mstools
	call setenv c:\mstools
	cd c:\inetsdk
	call setenv c:\inetsdk

	REM Batch file ends here.


-----------------------------------------------------
SOME NEW DOCUMENTATION:
-----------------------------------------------------
Cross Platform Downloading Issues:
Now that we have RISC support becoming available, how do you download 
controls to different kinds of client platforms.  Because the examples 
are better illustrated in HTML, you will find information on this in 
the SDK's Overview.  (the overview of ...\INetSDK\Help\Default.htm)

Installing Issues:
Because adding RISC support increased the size of the SDK significantly,
I've broken up some of the documentation into separate downloads.  I will
refer to the three doc sets as MVB, OLE Refs., and ActiveX Refs.  

The MVB doc set consist of the entire SDK doc set (OLE Refs., and 
ActiveX Refs.) in MVB format, and the InfoViewer for each of the 
supported NT platforms.  ISVs have asked me to be sure to include this 
doc set in the SDK because it offers string search capability 
and the ability to print "books".  They now account for about 13MB of 
the SDK however; so if you are getting the SDK on a CD, the MVB is 
probably included and installed by default; if you are downloading 
from the web, you are seeing it as a separate download that you 
can choose if you wish.  The setup of the MVB will allow you to 
install right into the SDK if you choose to.  See that download for 
more details.

The OLE Refs. (or ActiveX COM HTML References) integrates with the
ActiveX Refs. doc set.  It makes up less than 5MB of the SDK; however it 
consist of nearly 1500 individual files.  A limitation of the FAT file
system is that regardless of how small a file is, it takes up a full
cluster on the hard drive.  This means these files will take up considerable
space if installed, about 50MB on some machines.  If you are using NTFS,
or if disk space is not an issue for you, you can install these docs
in the SDK; or you can choose to browse the same information in the
MVB file.  I have included OLERefs.zip as a download
from the download site.  To install the OLE Refs. in your SDK, unzip it
in ..\INetSDK\Help\OLE.  Make sure to use the -d option of your
unzip utility so that the subdirectories are properly extracted.  You can
get unzipping utilities at http://www.winzip.com, or 
http://quest.jpl.nasa.gov/Info-Zip/

The ActiveX Refs. are what I refer to as the rest of the HTML documentation
found starting in your \Help directory.  They are downloaded and 
installed by default.  They contain all of the other ActiveX documentation
other than that found in the ActiveX COM references.

New Content: 
There is a difference in the way Internet Explorer 3.01 uses CSS1 
(Cascading Stylesheet Specifications)  properties which causes pages
formatted for version 3.01 to appear differently when viewed with 
Internet Explorer 3.0.   The problem is that stylesheet properties can 
be "inherited" at different object levels within the document.   
Version 3.01 correctly interprets inherited properties for margins 
and version 3.0 does not.    A "readme" chapter with a section 
regarding stylesheets was added to the HTML Reference to explain the 
issue, and it gives a solution for creating stylesheets compatible with 
both versions of Internet Explorer.

-----------------------------------------------------
REFRESHED SDKs: Conferencing and CAB Technology	
-----------------------------------------------------
The CabRscKit.exe has been added as a companion to CabDevKt.exe.  These
are self extracting .exe which provide you with everything you need
to add CAB support to your applications.  CabRscKt.exe adds support
for the compression and decompression API, with documentation and 
sample code.  To install this, drop it into a sub directory and 
execute.  Read the Readme.txt from there.


The ActiveX Conferencing Technology has now been made available in
a NetMeeting SDK 1.0a.  Because this is now available as a self extracting
.exe file in the \bin directory, I have pulled the \MSConf samples that
normally installed with the ActiveX SDK.  These are now in the self
extracting .exe MSCNF10a.exe.  You can visit their web site at  http://www.microsoft.com/intdev/msconf.

ActiveX SDK for the Macintosh:
See it at http://www.microsoft.com/intdev/SDK/Mac 


-----------------------------------------------------
SOME NEW SAMPLES:
-----------------------------------------------------
CARD:
Do you like to play Poker, or maybe Solitaire?  Well now you can do it
via your browser and ActiveX Controls.  See the sample 
...\INetSDK\Samples\BaseCtl\Card.

OBJVW:
Quite a few ISVs who have been using the WebBrowser Control have run
into similar issues.  A new sample has been added to address some of
these issues, like: how to access IE's Automation model and scripting
model from within a contained control, how to enumerate controls and
Java applets in a page, getting a controls ID or Name as specified in the
OBJECT tag, how to know when a page is completely loaded, how to make a 
generic class to sink events, marking controls "Safe for Scripting", etc.
This new sample is in ...\INetSDK\Samples\BaseCtl\ObjVw.

=======================================================================
REDISTRIBUTABLE DLLs.
=======================================================================
WINTDist.exe APRXDist.exe, WINT351.exe, and AXDist.exe
-----------------------
|New with this release: The Intel version of the Redistributables have
|been refreshed with the same bits as ships in IE3.01.  
|
|There are now RISC versions of the Redistributables.  Note however
|that the RISC versions contain prerelease code, and these 
|Redistributables should not be release with your finished product.
|These are beta only, and should be used for testing only.
|
|There are also 3 international versions of the Redistributables: 
|German, Japanese, and Taiwan.  These are prefixed with DE, JA, and TW.
|These are mapped out specifically in the Redist.txt file.
|
|Because of the size of the combined redistributables, and because
|the list of file will grow in the future, I have now seperated these
|out into a seperate download from the web.  You can download this
|file, AXReDist.exe, and extract it according to the download page's
|instructions.
|


The following executables install the following redistributable files.  
Note that these redistributable packages are targeted at Windows NT 4.0
final release and Windows 95, unless otherwise specified to be for Windows
NT 3.51.  The redistributables break out as follows:

WINTDIST.exe:
- WinInet.dll
- InLoader.dll
- SChannel.dll

WINT351.exe:
Note: SChannel.dll requires Windows NT 4.0 or Windows 95 system
components, so WINT351 does not install SChannel.dll.  WINT351.exe
will install WinInet functionality on Windows NT 3.51, but note,
it requires enhancements to WinInet for asynchronous operations
only available with Windows NT 3.51 Service Pack 4 (SP4).  WINT351.exe
will only work on Windows NT 3.51 with SP4.
- WinInet.dll
- InLoader.dll

AXDist.exe:
- WinInet.dll
- InLoader.dll
- SChannel.dll
- URLMon.dll
- HLink.dll
- HLinkPrx.dll
- OLEAut32.dll
- StdOLE2.tlb

CCDist.exe: (now available only in the Win32 SDK)
- ComCat.dll

CCDist35.exe: (now available only in the Win32 SDK)
- ComCat.dll

APRXDist.exe:
- ActXPrxy.dll

Please read redist.txt for more details.  

The purpose of making the redistributable is so ISVs can redistribute
ActiveX files and target systems that may not have Internet Explorer
3.0 installed on them; but also to know that the files will be 
installed; with file dependencies and registry settings set correctly.

These DLLs are ONLY redistributable through the use of the self
extracting executables listed above.  See details on redistribution 
rights in redist.txt (which has recently been moved into your 
ActiveX SDK installation to \InetSDK\License.) 

AXDist.exe, WINTDist.exe, APRXDist.exe, and CCDist.exe, work on 
Windows NT 4.0 and Windows 95.  WINT351.exe install WinInet.dll 
and dependencies on Windows NT 3.51 (note, it is not meant to work 
on Windows NT 4.0).  CCDist35.exe will soon be available for
Windows NT 3.5.

WINT351.exe is silent by default.  The other redistributable that
run on Windows 95 and Windows NT 4.0 are totally silent if executed
with the /Q switch i.e. "WINTDist.exe /Q".  Note, this does not
work on Windows NT 4.0 betas, only on the final release.  As part of
their default behavior, the redistributables will version check and
will not install older components over newer system files.  In silent
mode the user will not be prompted to make a choice.

If you have previously shipped earlier versions of these files, with
your product; your installed base should be upgraded with these releases.

To test your WinInet code with these redistributables:
* Start with a clean Windows 95 or Windows NT machine <without SDKs or
  Internet Explorer installed>.
* Run WINTDist.exe (or WINT351.exe)
* Run and test your code.

To test your URLMon code with these redistributables: 
* Start with a clean Windows 95 or Windows NT machine <without SDKs or
  Internet Explorer installed>.
* Run AXDist.exe
* Run and test your code.

Alternately, for testing your code, do the following:

To test these files: 
* Start with a clean Windows 95 or Windows NT machine.
* Install the Win32 SDK (a release dated May '96 or later).  
* Install the ActiveX SDK (dated August '96 or later).  
  <note, the Internet Explorer should not be installed>

then ... For WinInet only code:
* Run WINTDist.exe to install WinInet.dll and dependencies.
* Build and run your WinInet.dll dependent code.

or/then ... For URLMon code:
* Run AXDist.exe to install the rest of the files described
  above.
* Build and run your code.

All of the files in each of the redistributables has been classified
as a "Core Component".  This essentially means that once these files
are installed, they should not be uninstalled from a system.  Your 
setup applications can distribute and execute these files, and will
not have to be concerned with keeping usage count or uninstalling the
files.  

Note, if the redistributables don't meet your distribution needs, report
problems to AXDistB1@microsoft.com


==============









