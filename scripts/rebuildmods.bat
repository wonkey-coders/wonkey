
echo off

call common.bat

echo.
echo ***** Rebuilding modules *****
echo.

%wake% mods -clean -time -config=release -target=desktop
if %errorlevel% neq 0 exit /b %errorlevel%

%wake% mods -clean -time -config=debug -target=desktop
if %errorlevel% neq 0 exit /b %errorlevel%
