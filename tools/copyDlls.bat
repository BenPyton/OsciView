@echo off

set DllDebugList=openal32.dll sfml-audio-d-2.dll sfml-graphics-d-2.dll sfml-system-d-2.dll sfml-window-d-2.dll
set DllReleaseList=openal32.dll sfml-audio-2.dll sfml-graphics-2.dll sfml-system-2.dll sfml-window-2.dll
set SFML32Dir=D:\SFML-2.5.1\bin
set SFML64Dir=D:\SFML-2.5.1-x64\bin

set SFMLDir=%SFML32Dir%
set DllList=%DllReleaseList%

set OutputDir=%~1
shift

:parse
if /I ""=="%~1" goto :endparse
if /I "x64"=="%~1" set SFMLDir=%SFML64Dir%
if /I "debug"=="%~1" set DllList=%DllDebugList%
shift
goto :parse
:endparse

echo Copy dlls to the output directory.
for %%f in (%DllList%) do cp "%SFMLDir%\%%f" "%OutputDir%\%%f"

echo Copy data folder to the output directory.
robocopy "..\data" "%OutputDir%\data" /E /NP /NJH /NJS /NDL

rem robocopy can send a non-zero even in success (to get additional info on the copy)
rem this test convert the only critical return code to a non-zero exit code
if ErrorLevel 8 exit /B 1

exit /B 0