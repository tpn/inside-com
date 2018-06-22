# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=objvw - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to objvw - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "objvw - Win32 Release" && "$(CFG)" != "objvw - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Objvw.mak" CFG="objvw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "objvw - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "objvw - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "objvw - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "objvw - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\objvw.ocx" ".\reg.out"

CLEAN : 
	-@erase "$(INTDIR)\appsink.obj"
	-@erase "$(INTDIR)\CATHELP.OBJ"
	-@erase "$(INTDIR)\evtsink.obj"
	-@erase "$(INTDIR)\GUIDS.OBJ"
	-@erase "$(INTDIR)\objvw.obj"
	-@erase "$(INTDIR)\objvw.res"
	-@erase "$(INTDIR)\objvw.tlb"
	-@erase "$(INTDIR)\objvwctl.obj"
	-@erase "$(INTDIR)\treeui.obj"
	-@erase "$(INTDIR)\wintree.obj"
	-@erase "$(OUTDIR)\objvw.exp"
	-@erase "$(OUTDIR)\objvw.lib"
	-@erase "$(OUTDIR)\objvw.ocx"
	-@erase ".\objvwint.H"
	-@erase ".\reg.out"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Objvw.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/objvw.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Objvw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ctlfwr32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib odbc32.lib odbccp32.lib comctl32.lib uuid.lib urlmon.lib wininet.lib hlink.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"libc.lib" /out:"Release/objvw.ocx"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=ctlfwr32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib odbc32.lib\
 odbccp32.lib comctl32.lib uuid.lib urlmon.lib wininet.lib hlink.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/objvw.pdb"\
 /machine:I386 /nodefaultlib:"libc.lib" /def:".\objvw.def"\
 /out:"$(OUTDIR)/objvw.ocx" /implib:"$(OUTDIR)/objvw.lib" 
DEF_FILE= \
	".\objvw.def"
LINK32_OBJS= \
	"$(INTDIR)\appsink.obj" \
	"$(INTDIR)\CATHELP.OBJ" \
	"$(INTDIR)\evtsink.obj" \
	"$(INTDIR)\GUIDS.OBJ" \
	"$(INTDIR)\objvw.obj" \
	"$(INTDIR)\objvw.res" \
	"$(INTDIR)\objvwctl.obj" \
	"$(INTDIR)\treeui.obj" \
	"$(INTDIR)\wintree.obj"

"$(OUTDIR)\objvw.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering Control
InputPath=.\Release\objvw.ocx
SOURCE=$(InputPath)

"reg.out" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c .\release\objvw.ocx

# End Custom Build

!ELSEIF  "$(CFG)" == "objvw - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\objvw.ocx" ".\reg.out"

CLEAN : 
	-@erase "$(INTDIR)\appsink.obj"
	-@erase "$(INTDIR)\CATHELP.OBJ"
	-@erase "$(INTDIR)\evtsink.obj"
	-@erase "$(INTDIR)\GUIDS.OBJ"
	-@erase "$(INTDIR)\objvw.obj"
	-@erase "$(INTDIR)\objvw.res"
	-@erase "$(INTDIR)\objvw.tlb"
	-@erase "$(INTDIR)\objvwctl.obj"
	-@erase "$(INTDIR)\treeui.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\wintree.obj"
	-@erase "$(OUTDIR)\objvw.exp"
	-@erase "$(OUTDIR)\objvw.ilk"
	-@erase "$(OUTDIR)\objvw.lib"
	-@erase "$(OUTDIR)\objvw.ocx"
	-@erase "$(OUTDIR)\objvw.pdb"
	-@erase ".\objvwint.H"
	-@erase ".\reg.out"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Objvw.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/objvw.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Objvw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ctlfwd32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib odbc32.lib odbccp32.lib comctl32.lib uuid.lib urlmon.lib wininet.lib hlink.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libc.lib" /out:"Debug/objvw.ocx"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=ctlfwd32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib odbc32.lib\
 odbccp32.lib comctl32.lib uuid.lib urlmon.lib wininet.lib hlink.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/objvw.pdb" /debug\
 /machine:I386 /nodefaultlib:"libc.lib" /def:".\objvw.def"\
 /out:"$(OUTDIR)/objvw.ocx" /implib:"$(OUTDIR)/objvw.lib" 
DEF_FILE= \
	".\objvw.def"
LINK32_OBJS= \
	"$(INTDIR)\appsink.obj" \
	"$(INTDIR)\CATHELP.OBJ" \
	"$(INTDIR)\evtsink.obj" \
	"$(INTDIR)\GUIDS.OBJ" \
	"$(INTDIR)\objvw.obj" \
	"$(INTDIR)\objvw.res" \
	"$(INTDIR)\objvwctl.obj" \
	"$(INTDIR)\treeui.obj" \
	"$(INTDIR)\wintree.obj"

"$(OUTDIR)\objvw.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering Control
InputPath=.\Debug\objvw.ocx
SOURCE=$(InputPath)

"reg.out" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c .\debug\objvw.ocx

# End Custom Build

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

# Name "objvw - Win32 Release"
# Name "objvw - Win32 Debug"

!IF  "$(CFG)" == "objvw - Win32 Release"

!ELSEIF  "$(CFG)" == "objvw - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\objvw.def

!IF  "$(CFG)" == "objvw - Win32 Release"

!ELSEIF  "$(CFG)" == "objvw - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\evtsink.cpp
DEP_CPP_EVTSI=\
	".\evtsink.h"\
	".\gen.h"\
	".\IPSERVER.H"\
	

"$(INTDIR)\evtsink.obj" : $(SOURCE) $(DEP_CPP_EVTSI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GUIDS.CPP
DEP_CPP_GUIDS=\
	".\IPSERVER.H"\
	".\objvwint.H"\
	{$(INCLUDE)}"\EXDISP.H"\
	

"$(INTDIR)\GUIDS.OBJ" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)" ".\objvwint.H"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\objvw.cpp
DEP_CPP_OBJVW=\
	".\APPSINK.H"\
	".\CATHELP.H"\
	".\CTRLOBJ.H"\
	".\DISPIDS.H"\
	".\evtsink.h"\
	".\gen.h"\
	".\GLOBALS.H"\
	".\IPSERVER.H"\
	".\LOCALOBJ.H"\
	".\LOCALSRV.H"\
	".\OBJVWCTL.H"\
	".\objvwint.H"\
	".\RESOURCE.H"\
	".\TREEUI.H"\
	".\UTIL.H"\
	".\WINTREE.H"\
	{$(INCLUDE)}"\EXDISP.H"\
	

"$(INTDIR)\objvw.obj" : $(SOURCE) $(DEP_CPP_OBJVW) "$(INTDIR)" ".\objvwint.H"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CATHELP.CPP

"$(INTDIR)\CATHELP.OBJ" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\objvw.odl
DEP_MTL_OBJVW_=\
	".\DISPIDS.H"\
	

!IF  "$(CFG)" == "objvw - Win32 Release"

# ADD MTL /h "objvwint.h"

BuildCmds= \
	$(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/objvw.tlb" /h "objvwint.h" /win32\
 $(SOURCE) \
	

"$(OUTDIR)\objvw.tlb" : $(SOURCE) $(DEP_MTL_OBJVW_) "$(OUTDIR)"
   $(BuildCmds)

".\objvwint.H" : $(SOURCE) $(DEP_MTL_OBJVW_) "$(OUTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "objvw - Win32 Debug"

# ADD MTL /h "objvwint.h"

BuildCmds= \
	$(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/objvw.tlb" /h "objvwint.h" /win32\
 $(SOURCE) \
	

"$(OUTDIR)\objvw.tlb" : $(SOURCE) $(DEP_MTL_OBJVW_) "$(OUTDIR)"
   $(BuildCmds)

".\objvwint.H" : $(SOURCE) $(DEP_MTL_OBJVW_) "$(OUTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\objvw.rc

!IF  "$(CFG)" == "objvw - Win32 Release"

DEP_RSC_OBJVW_R=\
	".\Dwinvers.h"\
	".\Objvwctl.bmp"\
	".\RESOURCE.H"\
	
NODEP_RSC_OBJVW_R=\
	".\Release\objvw.tlb"\
	

"$(INTDIR)\objvw.res" : $(SOURCE) $(DEP_RSC_OBJVW_R) "$(INTDIR)"\
 "$(INTDIR)\objvw.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/objvw.res" /i "Release" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "objvw - Win32 Debug"

DEP_RSC_OBJVW_R=\
	".\Debug\objvw.tlb"\
	".\Dwinvers.h"\
	".\Objvwctl.bmp"\
	".\RESOURCE.H"\
	

"$(INTDIR)\objvw.res" : $(SOURCE) $(DEP_RSC_OBJVW_R) "$(INTDIR)"\
 "$(INTDIR)\objvw.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/objvw.res" /i "Debug" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\objvwctl.cpp
DEP_CPP_OBJVWC=\
	".\APPSINK.H"\
	".\CTRLOBJ.H"\
	".\DISPIDS.H"\
	".\evtsink.h"\
	".\gen.h"\
	".\GLOBALS.H"\
	".\IPSERVER.H"\
	".\LOCALOBJ.H"\
	".\OBJVWCTL.H"\
	".\objvwint.H"\
	".\RESOURCE.H"\
	".\TREEUI.H"\
	".\UTIL.H"\
	".\WINTREE.H"\
	{$(INCLUDE)}"\EXDISP.H"\
	

"$(INTDIR)\objvwctl.obj" : $(SOURCE) $(DEP_CPP_OBJVWC) "$(INTDIR)"\
 ".\objvwint.H"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\treeui.cpp
DEP_CPP_TREEU=\
	".\IPSERVER.H"\
	".\TREEUI.H"\
	

"$(INTDIR)\treeui.obj" : $(SOURCE) $(DEP_CPP_TREEU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\wintree.cpp
DEP_CPP_WINTR=\
	".\gen.h"\
	".\IPSERVER.H"\
	".\TREEUI.H"\
	".\WINTREE.H"\
	{$(INCLUDE)}"\EXDISP.H"\
	

"$(INTDIR)\wintree.obj" : $(SOURCE) $(DEP_CPP_WINTR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\appsink.cpp
DEP_CPP_APPSI=\
	".\APPSINK.H"\
	".\CTRLOBJ.H"\
	".\DISPIDS.H"\
	".\evtsink.h"\
	".\gen.h"\
	".\IPSERVER.H"\
	".\OBJVWCTL.H"\
	".\objvwint.H"\
	".\TREEUI.H"\
	".\WINTREE.H"\
	{$(INCLUDE)}"\EXDISP.H"\
	

"$(INTDIR)\appsink.obj" : $(SOURCE) $(DEP_CPP_APPSI) "$(INTDIR)" ".\objvwint.H"


# End Source File
# End Target
# End Project
################################################################################
