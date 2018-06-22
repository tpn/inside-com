# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=SuperPad - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SuperPad - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SuperPad - Win32 Release" && "$(CFG)" !=\
 "SuperPad - Win32 Debug" && "$(CFG)" != "SuperPad - Win32 Unicode Debug" &&\
 "$(CFG)" != "SuperPad - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "superpad.mak" CFG="SuperPad - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SuperPad - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SuperPad - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SuperPad - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "SuperPad - Win32 Unicode Release" (based on\
 "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "SuperPad - Win32 Unicode Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "SuperPad - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\urlpad.exe"

CLEAN : 
	-@erase ".\Release\urlpad.exe"
	-@erase ".\Release\pageset.obj"
	-@erase ".\Release\superpad.pch"
	-@erase ".\Release\padframe.obj"
	-@erase ".\Release\superpad.obj"
	-@erase ".\Release\download.obj"
	-@erase ".\Release\mainfrm.obj"
	-@erase ".\Release\padview.obj"
	-@erase ".\Release\paddoc.obj"
	-@erase ".\Release\stdafx.obj"
	-@erase ".\Release\paditem.obj"
	-@erase ".\Release\linkitem.obj"
	-@erase ".\Release\ipframe.obj"
	-@erase ".\Release\Fileopen.obj"
	-@erase ".\Release\tabstop.obj"
	-@erase ".\Release\aboutbox.obj"
	-@erase ".\Release\urlpad.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/urlpad.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 webpost.lib urlmon.lib wininet.lib uuid3.lib /nologo /subsystem:windows /machine:I386 /out:"Release/urlpad.exe"
# SUBTRACT LINK32 /map
LINK32_FLAGS=webpost.lib urlmon.lib wininet.lib uuid3.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/urlpad.pdb" /machine:I386\
 /out:"$(OUTDIR)/urlpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)/pageset.obj" \
	"$(INTDIR)/padframe.obj" \
	"$(INTDIR)/superpad.obj" \
	"$(INTDIR)/download.obj" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/padview.obj" \
	"$(INTDIR)/paddoc.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/paditem.obj" \
	"$(INTDIR)/linkitem.obj" \
	"$(INTDIR)/ipframe.obj" \
	"$(INTDIR)/Fileopen.obj" \
	"$(INTDIR)/tabstop.obj" \
	"$(INTDIR)/aboutbox.obj" \
	"$(INTDIR)/urlpad.res"

"$(OUTDIR)\urlpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\urlpad.exe" "$(OUTDIR)\superpad.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\superpad.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\superpad.bsc"
	-@erase ".\Debug\pageset.sbr"
	-@erase ".\Debug\ipframe.sbr"
	-@erase ".\Debug\padframe.sbr"
	-@erase ".\Debug\superpad.sbr"
	-@erase ".\Debug\mainfrm.sbr"
	-@erase ".\Debug\padview.sbr"
	-@erase ".\Debug\paddoc.sbr"
	-@erase ".\Debug\stdafx.sbr"
	-@erase ".\Debug\paditem.sbr"
	-@erase ".\Debug\linkitem.sbr"
	-@erase ".\Debug\download.sbr"
	-@erase ".\Debug\Fileopen.sbr"
	-@erase ".\Debug\tabstop.sbr"
	-@erase ".\Debug\aboutbox.sbr"
	-@erase ".\Debug\urlpad.exe"
	-@erase ".\Debug\tabstop.obj"
	-@erase ".\Debug\aboutbox.obj"
	-@erase ".\Debug\pageset.obj"
	-@erase ".\Debug\ipframe.obj"
	-@erase ".\Debug\padframe.obj"
	-@erase ".\Debug\superpad.obj"
	-@erase ".\Debug\mainfrm.obj"
	-@erase ".\Debug\padview.obj"
	-@erase ".\Debug\paddoc.obj"
	-@erase ".\Debug\stdafx.obj"
	-@erase ".\Debug\paditem.obj"
	-@erase ".\Debug\linkitem.obj"
	-@erase ".\Debug\download.obj"
	-@erase ".\Debug\Fileopen.obj"
	-@erase ".\Debug\urlpad.res"
	-@erase ".\Debug\urlpad.ilk"
	-@erase ".\Debug\urlpad.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/superpad.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/urlpad.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/pageset.sbr" \
	"$(INTDIR)/ipframe.sbr" \
	"$(INTDIR)/padframe.sbr" \
	"$(INTDIR)/superpad.sbr" \
	"$(INTDIR)/mainfrm.sbr" \
	"$(INTDIR)/padview.sbr" \
	"$(INTDIR)/paddoc.sbr" \
	"$(INTDIR)/stdafx.sbr" \
	"$(INTDIR)/paditem.sbr" \
	"$(INTDIR)/linkitem.sbr" \
	"$(INTDIR)/download.sbr" \
	"$(INTDIR)/Fileopen.sbr" \
	"$(INTDIR)/tabstop.sbr" \
	"$(INTDIR)/aboutbox.sbr"

"$(OUTDIR)\superpad.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 webpost.lib urlmon.lib wininet.lib uuid3.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/urlpad.exe"
# SUBTRACT LINK32 /map
LINK32_FLAGS=webpost.lib urlmon.lib wininet.lib uuid3.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/urlpad.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/urlpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)/tabstop.obj" \
	"$(INTDIR)/aboutbox.obj" \
	"$(INTDIR)/pageset.obj" \
	"$(INTDIR)/ipframe.obj" \
	"$(INTDIR)/padframe.obj" \
	"$(INTDIR)/superpad.obj" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/padview.obj" \
	"$(INTDIR)/paddoc.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/paditem.obj" \
	"$(INTDIR)/linkitem.obj" \
	"$(INTDIR)/download.obj" \
	"$(INTDIR)/Fileopen.obj" \
	"$(INTDIR)/urlpad.res"

"$(OUTDIR)\urlpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "UniDebug"
# PROP Intermediate_Dir "UniDebug"
# PROP Target_Dir ""
OUTDIR=.\UniDebug
INTDIR=.\UniDebug

ALL : "$(OUTDIR)\superpad.exe"

CLEAN : 
	-@erase ".\UniDebug\vc40.pdb"
	-@erase ".\UniDebug\superpad.pch"
	-@erase ".\UniDebug\vc40.idb"
	-@erase ".\UniDebug\superpad.exe"
	-@erase ".\UniDebug\ipframe.obj"
	-@erase ".\UniDebug\tabstop.obj"
	-@erase ".\UniDebug\linkitem.obj"
	-@erase ".\UniDebug\download.obj"
	-@erase ".\UniDebug\pageset.obj"
	-@erase ".\UniDebug\mainfrm.obj"
	-@erase ".\UniDebug\padview.obj"
	-@erase ".\UniDebug\aboutbox.obj"
	-@erase ".\UniDebug\paditem.obj"
	-@erase ".\UniDebug\paddoc.obj"
	-@erase ".\UniDebug\stdafx.obj"
	-@erase ".\UniDebug\Fileopen.obj"
	-@erase ".\UniDebug\padframe.obj"
	-@erase ".\UniDebug\superpad.obj"
	-@erase ".\UniDebug\urlpad.res"
	-@erase ".\UniDebug\superpad.ilk"
	-@erase ".\UniDebug\superpad.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Include" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/superpad.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\UniDebug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/urlpad.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 urlmon.lib wininet.lib uuid3.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /map
LINK32_FLAGS=urlmon.lib wininet.lib uuid3.lib /nologo\
 /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/superpad.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/superpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ipframe.obj" \
	"$(INTDIR)/tabstop.obj" \
	"$(INTDIR)/linkitem.obj" \
	"$(INTDIR)/download.obj" \
	"$(INTDIR)/pageset.obj" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/padview.obj" \
	"$(INTDIR)/aboutbox.obj" \
	"$(INTDIR)/paditem.obj" \
	"$(INTDIR)/paddoc.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/Fileopen.obj" \
	"$(INTDIR)/padframe.obj" \
	"$(INTDIR)/superpad.obj" \
	"$(INTDIR)/urlpad.res"

"$(OUTDIR)\superpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "UniRelease"
# PROP Intermediate_Dir "UniRelease"
# PROP Target_Dir ""
OUTDIR=.\UniRelease
INTDIR=.\UniRelease

ALL : "$(OUTDIR)\superpad.exe"

CLEAN : 
	-@erase ".\UniRelease\superpad.exe"
	-@erase ".\UniRelease\superpad.obj"
	-@erase ".\UniRelease\superpad.pch"
	-@erase ".\UniRelease\paddoc.obj"
	-@erase ".\UniRelease\download.obj"
	-@erase ".\UniRelease\paditem.obj"
	-@erase ".\UniRelease\pageset.obj"
	-@erase ".\UniRelease\ipframe.obj"
	-@erase ".\UniRelease\linkitem.obj"
	-@erase ".\UniRelease\mainfrm.obj"
	-@erase ".\UniRelease\stdafx.obj"
	-@erase ".\UniRelease\Fileopen.obj"
	-@erase ".\UniRelease\tabstop.obj"
	-@erase ".\UniRelease\aboutbox.obj"
	-@erase ".\UniRelease\padview.obj"
	-@erase ".\UniRelease\padframe.obj"
	-@erase ".\UniRelease\urlpad.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\Include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Include" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\UniRelease/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/urlpad.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/superpad.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 urlmon.lib wininet.lib uuid3.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386
# SUBTRACT LINK32 /map
LINK32_FLAGS=urlmon.lib wininet.lib uuid3.lib /nologo\
 /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/superpad.pdb" /machine:I386 /out:"$(OUTDIR)/superpad.exe" 
LINK32_OBJS= \
	"$(INTDIR)/superpad.obj" \
	"$(INTDIR)/paddoc.obj" \
	"$(INTDIR)/download.obj" \
	"$(INTDIR)/paditem.obj" \
	"$(INTDIR)/pageset.obj" \
	"$(INTDIR)/ipframe.obj" \
	"$(INTDIR)/linkitem.obj" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/Fileopen.obj" \
	"$(INTDIR)/tabstop.obj" \
	"$(INTDIR)/aboutbox.obj" \
	"$(INTDIR)/padview.obj" \
	"$(INTDIR)/padframe.obj" \
	"$(INTDIR)/urlpad.res"

"$(OUTDIR)\superpad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "SuperPad - Win32 Release"
# Name "SuperPad - Win32 Debug"
# Name "SuperPad - Win32 Unicode Debug"
# Name "SuperPad - Win32 Unicode Release"

!IF  "$(CFG)" == "SuperPad - Win32 Release"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\aboutbox.cpp
DEP_CPP_ABOUT=\
	".\aboutbox.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\aboutbox.sbr" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\aboutbox.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ipframe.cpp
DEP_CPP_IPFRA=\
	".\aboutbox.h"\
	".\ipframe.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\ipframe.sbr" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\ipframe.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\linkitem.cpp
DEP_CPP_LINKI=\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\linkitem.sbr" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\linkitem.obj" : $(SOURCE) $(DEP_CPP_LINKI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_CPP_MAINF=\
	".\aboutbox.h"\
	".\mainfrm.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\mainfrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\paddoc.cpp
DEP_CPP_PADDO=\
	".\aboutbox.h"\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	{$(INCLUDE)}"\Wpapi.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\paddoc.sbr" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\paddoc.obj" : $(SOURCE) $(DEP_CPP_PADDO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\padframe.cpp
DEP_CPP_PADFR=\
	".\aboutbox.h"\
	".\padframe.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\padframe.sbr" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\padframe.obj" : $(SOURCE) $(DEP_CPP_PADFR) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\paditem.cpp
DEP_CPP_PADIT=\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\paditem.sbr" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\paditem.obj" : $(SOURCE) $(DEP_CPP_PADIT) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\padview.cpp
DEP_CPP_PADVI=\
	".\aboutbox.h"\
	".\linkitem.h"\
	".\paddoc.h"\
	".\paditem.h"\
	".\padview.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	".\tabstop.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\padview.sbr" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\padview.obj" : $(SOURCE) $(DEP_CPP_PADVI) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pageset.cpp
DEP_CPP_PAGES=\
	".\aboutbox.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\pageset.sbr" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\pageset.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "..\Include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Include" /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/superpad.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Include" /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "..\Include" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/superpad.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\superpad.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\superpad.cpp
DEP_CPP_SUPER=\
	".\stdafx.h"\
	".\superpad.h"\
	".\mainfrm.h"\
	".\padview.h"\
	".\paddoc.h"\
	".\padframe.h"\
	".\ipframe.h"\
	".\download.h"\
	{$(INCLUDE)}"\Urlmon.h"\
	".\fileopen.h"\
	".\pageset.h"\
	".\aboutbox.h"\
	{$(INCLUDE)}"\Servprov.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\superpad.sbr" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\superpad.obj" : $(SOURCE) $(DEP_CPP_SUPER) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tabstop.cpp
DEP_CPP_TABST=\
	".\aboutbox.h"\
	".\pageset.h"\
	".\stdafx.h"\
	".\superpad.h"\
	".\tabstop.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\tabstop.sbr" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\tabstop.obj" : $(SOURCE) $(DEP_CPP_TABST) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\spadmac.r

!IF  "$(CFG)" == "SuperPad - Win32 Release"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\download.cpp
DEP_CPP_DOWNL=\
	".\stdafx.h"\
	".\mainfrm.h"\
	".\download.h"\
	{$(INCLUDE)}"\Util.H"\
	{$(INCLUDE)}"\Urlmon.h"\
	{$(INCLUDE)}"\Servprov.h"\
	"F:\include\Globals.H"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\download.obj" : $(SOURCE) $(DEP_CPP_DOWNL) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\download.obj" : $(SOURCE) $(DEP_CPP_DOWNL) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\download.sbr" : $(SOURCE) $(DEP_CPP_DOWNL) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\download.obj" : $(SOURCE) $(DEP_CPP_DOWNL) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\download.obj" : $(SOURCE) $(DEP_CPP_DOWNL) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fileopen.cpp
DEP_CPP_FILEO=\
	".\fileopen.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\Fileopen.obj" : $(SOURCE) $(DEP_CPP_FILEO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\Fileopen.obj" : $(SOURCE) $(DEP_CPP_FILEO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"

"$(INTDIR)\Fileopen.sbr" : $(SOURCE) $(DEP_CPP_FILEO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\Fileopen.obj" : $(SOURCE) $(DEP_CPP_FILEO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\Fileopen.obj" : $(SOURCE) $(DEP_CPP_FILEO) "$(INTDIR)"\
 "$(INTDIR)\superpad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\urlpad.rc
DEP_RSC_URLPA=\
	".\itoolbar.bmp"\
	".\paddoc.ico"\
	".\superpad.ico"\
	".\toolbar.bmp"\
	

!IF  "$(CFG)" == "SuperPad - Win32 Release"


"$(INTDIR)\urlpad.res" : $(SOURCE) $(DEP_RSC_URLPA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Debug"


"$(INTDIR)\urlpad.res" : $(SOURCE) $(DEP_RSC_URLPA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Debug"


"$(INTDIR)\urlpad.res" : $(SOURCE) $(DEP_RSC_URLPA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SuperPad - Win32 Unicode Release"


"$(INTDIR)\urlpad.res" : $(SOURCE) $(DEP_RSC_URLPA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
