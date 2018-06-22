# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "framer.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : .\framer.exe $(OUTDIR)/framer.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /W3 /GX /YX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /FR /c
CPP_PROJ=/nologo /W3 /GX /YX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "UNICODE" /D "_UNICODE" /FR$(INTDIR)/ /Fp$(OUTDIR)/"framer.pch" /Fo$(INTDIR)/\
 /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"framer.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"framer.bsc" 
BSC32_SBRS= \
	$(INTDIR)/framer.sbr \
	$(INTDIR)/iadvsink.sbr \
	$(INTDIR)/iipsite.sbr \
	$(INTDIR)/iclisite.sbr \
	$(INTDIR)/site.sbr \
	$(INTDIR)/idocsite.sbr

$(OUTDIR)/framer.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib uuid3.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386 /OUT:"framer.exe"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib uuid3.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:no /PDB:$(OUTDIR)/"framer.pdb" /MACHINE:I386\
 /DEF:".\win32.def" /OUT:"framer.exe" 
DEF_FILE=.\win32.def
LINK32_OBJS= \
	$(INTDIR)/framer.obj \
	$(INTDIR)/framer.res \
	$(INTDIR)/iadvsink.obj \
	$(INTDIR)/iipsite.obj \
	$(INTDIR)/iclisite.obj \
	$(INTDIR)/site.obj \
	$(INTDIR)/idocsite.obj

.\framer.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : .\framer.exe $(OUTDIR)/framer.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /W3 /GX /Zi /YX /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /FR /c
CPP_PROJ=/nologo /W3 /GX /Zi /YX /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "UNICODE" /D "_UNICODE" /FR$(INTDIR)/ /Fp$(OUTDIR)/"framer.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"framer.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"framer.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"framer.bsc" 
BSC32_SBRS= \
	$(INTDIR)/framer.sbr \
	$(INTDIR)/iadvsink.sbr \
	$(INTDIR)/iipsite.sbr \
	$(INTDIR)/iclisite.sbr \
	$(INTDIR)/site.sbr \
	$(INTDIR)/idocsite.sbr

$(OUTDIR)/framer.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib uuid3.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386 /OUT:"framer.exe"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib uuid3.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:yes /PDB:$(OUTDIR)/"framer.pdb" /DEBUG\
 /MACHINE:I386 /DEF:".\win32.def" /OUT:"framer.exe" 
DEF_FILE=.\win32.def
LINK32_OBJS= \
	$(INTDIR)/framer.obj \
	$(INTDIR)/framer.res \
	$(INTDIR)/iadvsink.obj \
	$(INTDIR)/iipsite.obj \
	$(INTDIR)/iclisite.obj \
	$(INTDIR)/site.obj \
	$(INTDIR)/idocsite.obj

.\framer.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\framer.cpp
DEP_FRAME=\
	.\framer.h\
	\sweeper\include\docobj.h\
	.\resource.h\
	.\site.h

$(INTDIR)/framer.obj :  $(SOURCE)  $(DEP_FRAME) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\framer.rc
DEP_FRAMER=\
	.\resource.h

$(INTDIR)/framer.res :  $(SOURCE)  $(DEP_FRAMER) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\win32.def
# End Source File
################################################################################
# Begin Source File

SOURCE=.\iadvsink.cpp
DEP_IADVS=\
	.\framer.h\
	\sweeper\include\docobj.h\
	.\resource.h\
	.\site.h

$(INTDIR)/iadvsink.obj :  $(SOURCE)  $(DEP_IADVS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\iipsite.cpp
DEP_IIPSI=\
	.\framer.h\
	\sweeper\include\docobj.h\
	.\resource.h\
	.\site.h

$(INTDIR)/iipsite.obj :  $(SOURCE)  $(DEP_IIPSI) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\iclisite.cpp
DEP_ICLIS=\
	.\framer.h\
	\sweeper\include\docobj.h\
	.\resource.h\
	.\site.h

$(INTDIR)/iclisite.obj :  $(SOURCE)  $(DEP_ICLIS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\site.cpp
DEP_SITE_=\
	.\framer.h\
	\sweeper\include\docobj.h\
	.\resource.h\
	.\site.h

$(INTDIR)/site.obj :  $(SOURCE)  $(DEP_SITE_) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\idocsite.cpp
DEP_IDOCS=\
	.\framer.h\
	\sweeper\include\docobj.h\
	.\resource.h\
	.\site.h

$(INTDIR)/idocsite.obj :  $(SOURCE)  $(DEP_IDOCS) $(INTDIR)

# End Source File
# End Group
# End Project
################################################################################
