ActiveX SDK Beta 1 Samples Readme.Txt
=====================================

 BaseCtl   Internet enabled OCX framework and samples
    Framewrk  Internet enabled OCX framewrk
    Ielnk     Sample Control which demonstrates Simple Hyperlink Navigation API
    Iemime    Sample Control which demonstrates custom mime type registration.
    ToDoSvr   Sample DocObject Control
    WebImage  Sample Control which demonstrates downloading and displaying a BMP file.
 Framer    Demonstrates in-place activation of a DocObject.
 OLEScript Sample of an ActiveX Scripting host
 Progress  Sample that uses an URL Moniker, demonstrates IBindStatusCallBack
 Range     Demonstrates simple http GET request with optional read ranges.
 UrlPad    Enhances SUPERPAD that demonstrates getting an URL
           using urlostream API (from urlhlink.lib) and posting
           it back to the server using WebPost API (sample below).
 VBScript  Sample VBScript pages, pointers to JScript pages
 WebPost   Demonstrates the use of the Web Post APIs to update 
           content on Web Sites.
 WinINet   Samples that demonstrate use of the WinInet APIs.
    AsyncFtp  Demonstrates use of Wininet asynchronous API for ftp.
    HttpAuth  Demonstrates use of Wininet for HTTP authentication.

Instructions
==============
Please run SetEnv.Bat to set up your environment.  This SDK requires the
most recent (May 96 or later) Win32 SDK and a recent compiler (all
testing was done with VC++ 4.1)  The INCLUDE, LIB and PATH environment
variables should first look in \INetSDK (from this SDK), then in \MSTools
(from the Win32 SDK) and then in \MSDev (or equivalent compiler.)

The samples in this tree generally use the Win32 SDK conventions for makefiles.
'nmake' will build a debug binary and 'nmake nodebug=1' will build a
retail binary.  The debug binaries will link with the debug variants of the
C Runtimes and class libraries, and the retail binaries will link with the
retail variants of these libraries.  Please remember that machines without
VC++ installed may not have mfc40.dll, msvcrt40.dll, etc. (for retail),
mfc40d.dll, msvcr40d.dll, etc. (for debug) DLLs installed.  Please make
sure that any such required DLLs are properly installed on your test
machines.  Some samples also have VC++ makefiles (project.mak) for use
in the IDE.

To figure out what DLLs your project is using use
    "link -dump -imports <filename>"
And look for <file>.Dll lines.  There are often DLLs referenced that are not
installed on test machines, particularly for debug builds.  You need to make
sure that any such DLLs referenced are properly installed where they will be
loaded when the app or control is loaded,  This is typically the directory
returned by the GetSystemDirectory API call (system on Windows 95,  System32
on Windows NT.)

Creating Microsoft Visual C++ Project Files.
============================================

To build the samples from within the Microsoft Visual C++ 4.0
Developer Studio environment for samples that do not come with
VC++ makefiles (.mak files), you must add appropriate paths to
the Developer Studio's include and library paths, and create a 
Visual C++ project file. The general steps to follow are outlined 
below, although the exact steps vary from sample to sample.

1) Click "Options..." on the "Tools" menu, and on the 
"Directories" tab add the full path to your installed 
INetSDK\Include directory to the includes directories, the full 
path to INetSDK\Lib to the library directories, and the full path 
to the INetSDK\Bin directory to the executable files directories. 
These entries should be moved to the top of the search list. 
Several samples also require the Beta NT-SUR version (or later) of 
the Win32 SDK. The corresponding include, lib, and bin directories 
should also be added and moved up just below the INetSDK entries.

2) Create project and make files as follows:
a) Close any open workspace from the File menu.
b) Click "New" on the "File" menu and choose "Project Workspace".
c) In the "New Project Workspace" dialog type the root name for 
the output file into the "Name:" edit control (for example, type 
"Framer" for the Framer sample).
d) Choose "Application" in the "Type:" if you are building an 
application, "Dynamic-Link Library" for an ActiveX(tm) Control, or 
"Static Library" for a library (such as BaseCtl\FrameWrk).
e) "Browse..." to the INetSDK\Samples directory on your system. 
From there move to the directory holding the sample's sources and 
click "OK" to close the "Choose Directory" dialog. Make sure the 
"Location:" edit control reflects the directory holding the 
sample's sources and not a new subdirectory under this root.
f) Click "Create".
g) Click "Files into Project..." on the "Insert" menu.
h) Multiple select *.Cpp, *.c, *.def, and *.Rc and click "Add". If the
project contains an .Odl file add this to the project also.
i) Click "Settings..." on the "Build" menu and select the "Link" 
tab. Add any appropriate libraries from the INetSDK or Win32 SDK 
to the list of Object/library modules for both debug and release. 
You can search the SDK makefile in the source's directory for 
".lib" to find out which additional libraries are needed by a 
particular sample (such as uuic2.lib, uuid3.lib, urlmon.lib, 
etc.). Note that some samples need to link to separate debug or 
release libraries.
j) If the sample you are building uses MFC, choose which type of 
library to use in the "Microsoft Foundation Classes:" list box on 
the "General" tab of the "Project Settings" dialog.

3) Build the project from within the IDE. Note that some samples 
are dependent on libraries build by other samples. These 
dependencies are noted in the ReadMe.Txt files.

4) If necessary, copy and/or rename the output file appropriately, 
using the provided makefile as a guide.

5) If the output is an ActiveX(tm) Control, run RegSvr32 from the 
command line to register the .ocx on your system. You can probably 
finesse the "Register Control" option on the "Tools" menu to do 
this without dropping to the command line, but it is set up to 
work with projects created using the OLE ControlWizard.
