
echo off

call common.bat

echo.
echo ***** Updating modules *****
echo.

%wake% mods -config=release %*
if %errorlevel% neq 0 exit /b %errorlevel%

%wake% mods -config=debug %*
if %errorlevel% neq 0 exit /b %errorlevel%