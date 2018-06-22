# Nmake macros for building Windows 32-Bit apps

TARGETOS=BOTH
APPVER=4.0



all:ftpjr.exe

!include <win32.mak>

lflags= /INCREMENTAL:NO /PDB:NONE /RELEASE /NOLOGO -subsystem:console,$(APPVER) -entry:mainCRTStartup
ftpjr.obj: ftpjr.cpp
    $(cc) $(cflags) $(cvars) $(cdebug) ftpjr.cpp

ftpjr.exe: ftpjr.obj
    $(link) $(lflags)  -out:ftpjr.exe ftpjr.obj wininet.lib  user32.lib kernel32.lib

clean:
    del *.exe
    del *.obj

