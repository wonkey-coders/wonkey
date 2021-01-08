
echo off

call common.bat

echo.
echo ***** Updating wide *****
echo.

%wake% app -apptype=gui -build -config=release -product=scripts/wide.products/windows/wide.exe ../src/wide/wide.wx
if %errorlevel% neq 0 exit /b %errorlevel%

xcopy wide.products\windows\assets ..\bin\windows\wide\assets /Q /I /S /Y
if %errorlevel% neq 0 exit /b %errorlevel%

xcopy wide.products\windows\*.dll ..\bin\windows\wide /Q /I /S /Y
if %errorlevel% neq 0 exit /b %errorlevel%

xcopy wide.products\windows\*.exe ..\bin\windows\wide /Q /I /S /Y
if %errorlevel% neq 0 exit /b %errorlevel%

%wake% app -apptype=gui -build -config=release -product=scripts/launcher.products/windows/launcher.exe ../src/launcher/launcher.wx
if %errorlevel% neq 0 exit /b %errorlevel%

copy launcher.products\windows\launcher.exe "..\Wonkey (windows).exe"
if %errorlevel% neq 0 exit /b %errorlevel%