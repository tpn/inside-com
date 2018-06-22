# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Spruuids - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Spruuids - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Spruuids - Win32 Release" && "$(CFG)" !=\
 "Spruuids - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "spruuids.mak" CFG="Spruuids - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Spruuids - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Spruuids - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Spruuids - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Spruuids - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Spruuids_"
# PROP BASE Intermediate_Dir "Spruuids_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\spruuids.exe" "$(OUTDIR)\spruuids.tlb"

CLEAN : 
	-@erase "$(INTDIR)\App.obj"
	-@erase "$(INTDIR)\Game.obj"
	-@erase "$(INTDIR)\GameOA.obj"
	-@erase "$(INTDIR)\Guids.obj"
	-@erase "$(INTDIR)\MsgLoop.obj"
	-@erase "$(INTDIR)\OleAuto.obj"
	-@erase "$(INTDIR)\Score.obj"
	-@erase "$(INTDIR)\Spr.obj"
	-@erase "$(INTDIR)\SprOA.obj"
	-@erase "$(INTDIR)\spruuids.res"
	-@erase "$(INTDIR)\spruuids.tlb"
	-@erase "$(OUTDIR)\spruuids.exe"
	-@erase ".\Spruuids.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "inc_ext" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "inc_ext" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/spruuids.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/spruuids.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/spruuids.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib ole32.lib oleaut32.lib uuid.lib\
 uuid2.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/spruuids.pdb" /machine:I386 /out:"$(OUTDIR)/spruuids.exe" 
LINK32_OBJS= \
	"$(INTDIR)\App.obj" \
	"$(INTDIR)\Game.obj" \
	"$(INTDIR)\GameOA.obj" \
	"$(INTDIR)\Guids.obj" \
	"$(INTDIR)\MsgLoop.obj" \
	"$(INTDIR)\OleAuto.obj" \
	"$(INTDIR)\Score.obj" \
	"$(INTDIR)\Spr.obj" \
	"$(INTDIR)\SprOA.obj" \
	"$(INTDIR)\spruuids.res"

"$(OUTDIR)\spruuids.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"

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

ALL : "$(OUTDIR)\spruuids.exe" "$(OUTDIR)\spruuids.tlb"\
 "$(OUTDIR)\spruuids.bsc"

CLEAN : 
	-@erase "$(INTDIR)\App.obj"
	-@erase "$(INTDIR)\App.sbr"
	-@erase "$(INTDIR)\Game.obj"
	-@erase "$(INTDIR)\Game.sbr"
	-@erase "$(INTDIR)\GameOA.obj"
	-@erase "$(INTDIR)\GameOA.sbr"
	-@erase "$(INTDIR)\Guids.obj"
	-@erase "$(INTDIR)\Guids.sbr"
	-@erase "$(INTDIR)\MsgLoop.obj"
	-@erase "$(INTDIR)\MsgLoop.sbr"
	-@erase "$(INTDIR)\OleAuto.obj"
	-@erase "$(INTDIR)\OleAuto.sbr"
	-@erase "$(INTDIR)\Score.obj"
	-@erase "$(INTDIR)\Score.sbr"
	-@erase "$(INTDIR)\Spr.obj"
	-@erase "$(INTDIR)\Spr.sbr"
	-@erase "$(INTDIR)\SprOA.obj"
	-@erase "$(INTDIR)\SprOA.sbr"
	-@erase "$(INTDIR)\spruuids.res"
	-@erase "$(INTDIR)\spruuids.tlb"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\spruuids.bsc"
	-@erase "$(OUTDIR)\spruuids.exe"
	-@erase "$(OUTDIR)\spruuids.ilk"
	-@erase "$(OUTDIR)\spruuids.pdb"
	-@erase ".\Spruuids.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "inc_ext" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "inc_ext" /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/spruuids.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/spruuids.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/spruuids.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\App.sbr" \
	"$(INTDIR)\Game.sbr" \
	"$(INTDIR)\GameOA.sbr" \
	"$(INTDIR)\Guids.sbr" \
	"$(INTDIR)\MsgLoop.sbr" \
	"$(INTDIR)\OleAuto.sbr" \
	"$(INTDIR)\Score.sbr" \
	"$(INTDIR)\Spr.sbr" \
	"$(INTDIR)\SprOA.sbr"

"$(OUTDIR)\spruuids.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib ole32.lib oleaut32.lib uuid.lib\
 uuid2.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/spruuids.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/spruuids.exe" 
LINK32_OBJS= \
	"$(INTDIR)\App.obj" \
	"$(INTDIR)\Game.obj" \
	"$(INTDIR)\GameOA.obj" \
	"$(INTDIR)\Guids.obj" \
	"$(INTDIR)\MsgLoop.obj" \
	"$(INTDIR)\OleAuto.obj" \
	"$(INTDIR)\Score.obj" \
	"$(INTDIR)\Spr.obj" \
	"$(INTDIR)\SprOA.obj" \
	"$(INTDIR)\spruuids.res"

"$(OUTDIR)\spruuids.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Spruuids - Win32 Release"
# Name "Spruuids - Win32 Debug"

!IF  "$(CFG)" == "Spruuids - Win32 Release"

!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SprOA.cpp
DEP_CPP_SPROA=\
	".\Debug.h"\
	".\DispIDs.h"\
	".\Helpers.h"\
	".\inc_ext\ActivScp.h"\
	".\inc_ext\CompMgr.h"\
	".\inc_ext\MultInfo.h"\
	".\inc_ext\VBSGuids.h"\
	".\Main.h"\
	".\OleAuto.h"\
	".\Spr.h"\
	
NODEP_CPP_SPROA=\
	".\Spruuids.h"\
	

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\SprOA.obj" : $(SOURCE) $(DEP_CPP_SPROA) "$(INTDIR)" ".\Spruuids.h"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\SprOA.obj" : $(SOURCE) $(DEP_CPP_SPROA) "$(INTDIR)" ".\Spruuids.h"

"$(INTDIR)\SprOA.sbr" : $(SOURCE) $(DEP_CPP_SPROA) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Spr.cpp
DEP_CPP_SPR_C=\
	".\Debug.h"\
	".\Helpers.h"\
	".\inc_ext\ActivScp.h"\
	".\inc_ext\CompMgr.h"\
	".\inc_ext\MultInfo.h"\
	".\inc_ext\VBSGuids.h"\
	".\Main.h"\
	".\OleAuto.h"\
	".\Spr.h"\
	
NODEP_CPP_SPR_C=\
	".\Spruuids.h"\
	

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\Spr.obj" : $(SOURCE) $(DEP_CPP_SPR_C) "$(INTDIR)" ".\Spruuids.h"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\Spr.obj" : $(SOURCE) $(DEP_CPP_SPR_C) "$(INTDIR)" ".\Spruuids.h"

"$(INTDIR)\Spr.sbr" : $(SOURCE) $(DEP_CPP_SPR_C) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Score.cpp
DEP_CPP_SCORE=\
	".\Debug.h"\
	".\Game.h"\
	".\Helpers.h"\
	".\inc_ext\ActivScp.h"\
	".\inc_ext\CompMgr.h"\
	".\inc_ext\MultInfo.h"\
	".\inc_ext\VBSGuids.h"\
	".\Main.h"\
	".\OleAuto.h"\
	".\Score.h"\
	".\Spr.h"\
	".\Spruuids.h"\
	

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\Score.obj" : $(SOURCE) $(DEP_CPP_SCORE) "$(INTDIR)" ".\Spruuids.h"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\Score.obj" : $(SOURCE) $(DEP_CPP_SCORE) "$(INTDIR)" ".\Spruuids.h"

"$(INTDIR)\Score.sbr" : $(SOURCE) $(DEP_CPP_SCORE) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OleAuto.cpp
DEP_CPP_OLEAU=\
	".\Debug.h"\
	".\Helpers.h"\
	".\inc_ext\ActivScp.h"\
	".\inc_ext\CompMgr.h"\
	".\inc_ext\MultInfo.h"\
	".\inc_ext\VBSGuids.h"\
	".\Main.h"\
	".\OleAuto.h"\
	".\Spruuids.h"\
	

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\OleAuto.obj" : $(SOURCE) $(DEP_CPP_OLEAU) "$(INTDIR)" ".\Spruuids.h"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\OleAuto.obj" : $(SOURCE) $(DEP_CPP_OLEAU) "$(INTDIR)" ".\Spruuids.h"

"$(INTDIR)\OleAuto.sbr" : $(SOURCE) $(DEP_CPP_OLEAU) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsgLoop.cpp
DEP_CPP_MSGLO=\
	".\Debug.h"\
	".\Helpers.h"\
	".\inc_ext\ActivScp.h"\
	".\inc_ext\CompMgr.h"\
	".\inc_ext\MultInfo.h"\
	".\inc_ext\VBSGuids.h"\
	".\Main.h"\
	".\MsgLoop.h"\
	".\OleAuto.h"\
	".\Spruuids.h"\
	

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\MsgLoop.obj" : $(SOURCE) $(DEP_CPP_MSGLO) "$(INTDIR)" ".\Spruuids.h"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\MsgLoop.obj" : $(SOURCE) $(DEP_CPP_MSGLO) "$(INTDIR)" ".\Spruuids.h"

"$(INTDIR)\MsgLoop.sbr" : $(SOURCE) $(DEP_CPP_MSGLO) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Guids.cpp
DEP_CPP_GUIDS=\
	".\Debug.h"\
	".\Game.h"\
	".\Helpers.h"\
	".\inc_ext\ActivScp.h"\
	".\inc_ext\CompMgr.h"\
	".\inc_ext\MultInfo.h"\
	".\inc_ext\VBSGuids.h"\
	".\Main.h"\
	".\OleAuto.h"\
	".\Spruuids.h"\
	

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\Guids.obj" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)" ".\Spruuids.h"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\Guids.obj" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)" ".\Spruuids.h"

"$(INTDIR)\Guids.sbr" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GameOA.cpp
DEP_CPP_GAMEO=\
	".\App.h"\
	".\Debug.h"\
	".\DispIDs.h"\
	".\Game.h"\
	".\Helpers.h"\
	".\inc_ext\ActivScp.h"\
	".\inc_ext\CompMgr.h"\
	".\inc_ext\MultInfo.h"\
	".\inc_ext\VBSGuids.h"\
	".\Main.h"\
	".\OleAuto.h"\
	".\Score.h"\
	".\Spr.h"\
	
NODEP_CPP_GAMEO=\
	".\Spruuids.h"\
	

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\GameOA.obj" : $(SOURCE) $(DEP_CPP_GAMEO) "$(INTDIR)" ".\Spruuids.h"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\GameOA.obj" : $(SOURCE) $(DEP_CPP_GAMEO) "$(INTDIR)" ".\Spruuids.h"

"$(INTDIR)\GameOA.sbr" : $(SOURCE) $(DEP_CPP_GAMEO) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Game.cpp
DEP_CPP_GAME_=\
	".\App.h"\
	".\Debug.h"\
	".\Game.h"\
	".\Helpers.h"\
	".\inc_ext\ActivScp.h"\
	".\inc_ext\CompMgr.h"\
	".\inc_ext\MultInfo.h"\
	".\inc_ext\VBSGuids.h"\
	".\Main.h"\
	".\OleAuto.h"\
	".\Score.h"\
	".\Spr.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	
NODEP_CPP_GAME_=\
	".\SpruuidP.h"\
	".\SpruuidP.pix"\
	".\Spruuids.h"\
	

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\Game.obj" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)" ".\Spruuids.h"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\Game.obj" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)" ".\Spruuids.h"

"$(INTDIR)\Game.sbr" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\App.cpp
DEP_CPP_APP_C=\
	".\App.h"\
	".\Debug.h"\
	".\Game.h"\
	".\Helpers.h"\
	".\inc_ext\ActivScp.h"\
	".\inc_ext\CompMgr.h"\
	".\inc_ext\MultInfo.h"\
	".\inc_ext\VBSGuids.h"\
	".\Main.h"\
	".\MsgLoop.h"\
	".\OleAuto.h"\
	".\Spruuids.h"\
	

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\App.obj" : $(SOURCE) $(DEP_CPP_APP_C) "$(INTDIR)" ".\Spruuids.h"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\App.obj" : $(SOURCE) $(DEP_CPP_APP_C) "$(INTDIR)" ".\Spruuids.h"

"$(INTDIR)\App.sbr" : $(SOURCE) $(DEP_CPP_APP_C) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\spruuids.odl
DEP_MTL_SPRUU=\
	".\DispIDs.h"\
	

!IF  "$(CFG)" == "Spruuids - Win32 Release"

# ADD MTL /h "Spruuids.h"

BuildCmds= \
	$(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/spruuids.tlb" /h "Spruuids.h"\
 /win32 $(SOURCE) \
	

"$(OUTDIR)\spruuids.tlb" : $(SOURCE) $(DEP_MTL_SPRUU) "$(OUTDIR)"
   $(BuildCmds)

".\Spruuids.h" : $(SOURCE) $(DEP_MTL_SPRUU) "$(OUTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"

# ADD MTL /h "Spruuids.h"

BuildCmds= \
	$(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/spruuids.tlb" /h "Spruuids.h"\
 /win32 $(SOURCE) \
	

"$(OUTDIR)\spruuids.tlb" : $(SOURCE) $(DEP_MTL_SPRUU) "$(OUTDIR)"
   $(BuildCmds)

".\Spruuids.h" : $(SOURCE) $(DEP_MTL_SPRUU) "$(OUTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\spruuids.rc

!IF  "$(CFG)" == "Spruuids - Win32 Release"

DEP_RSC_SPRUUI=\
	".\plus.bmp"\
	".\ship.bmp"\
	".\spruuids.bmp"\
	".\spruuids.cur"\
	".\spruuids.ico"\
	
NODEP_RSC_SPRUUI=\
	".\Release\debug\Spruuids.tlb"\
	

"$(INTDIR)\spruuids.res" : $(SOURCE) $(DEP_RSC_SPRUUI) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/spruuids.res" /i "Release" /d "NDEBUG"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"

DEP_RSC_SPRUUI=\
	".\plus.bmp"\
	".\ship.bmp"\
	".\spruuids.bmp"\
	".\spruuids.cur"\
	".\spruuids.ico"\
	
NODEP_RSC_SPRUUI=\
	".\Debug\debug\Spruuids.tlb"\
	

"$(INTDIR)\spruuids.res" : $(SOURCE) $(DEP_RSC_SPRUUI) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/spruuids.res" /i "Debug" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
