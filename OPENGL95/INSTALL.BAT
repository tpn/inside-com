@echo off
if "%OS%" == "Windows_NT" goto NT

echo Copying OpenGL DLLs to %windir%\system...
if exist %windir%\system\opengl32.dll goto glu
copy opengl32.dll %windir%\system
:glu
if exist %windir%\system\glu32.dll goto end
copy glu32.dll %windir%\system
goto end

:NT
echo Copying OpenGL DLLs to %systemroot%\system32...
if exist %systemroot%\system32\opengl32.dll goto NTglu
copy opengl32.dll %systemroot%\system32
:NTglu
if exist %systemroot%\system32\glu32.dll goto end
copy glu32.dll %systemroot%\system32

:end
echo Finished.
