
echo off

call common.bat

echo.
echo ***** Rebuilding launcher *****
echo.

%wake% app -clean -apptype=gui -build -config=release -product=scripts/launcher.products/windows/launcher.exe ../src/launcher/launcher.wx
if %errorlevel% neq 0 exit /b %errorlevel%

copy launcher.products\windows\launcher.exe "..\Wonkey (windows).exe"
if %errorlevel% neq 0 exit /b %errorlevel%