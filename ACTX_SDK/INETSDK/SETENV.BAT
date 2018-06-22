@echo off

if "%1" == "" goto usage
if "%mstools%" == "" goto warning

set Path=%1\bin;%mstools%\bin;%path%
set Lib=%1\lib;%mstools%\lib;%lib%
set Include=%1\include;%mstools%\include;%include%
set INETSDK=%1

goto end

:usage
echo.
echo Usage: SETENV sdkroot
echo Where: sdkroot specifies where the toolkit was installed
echo Example: SETENV C:\INETSDK
echo.
goto end


:warning
echo.
echo Warning: Some samples will not build without the most recent Win32 SDK.
echo.

set Path=%1\bin;%path%
set Lib=%1\lib;%lib%
set Include=%1\include;%include%
set INETSDK=%1


:end
