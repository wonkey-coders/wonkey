
echo off

echo.
echo ***** Rebuilding modules *****
echo.

..\bin\windows\wake mods -clean -config=release -target=desktop
if %errorlevel% neq 0 exit /b %errorlevel%

..\bin\windows\wake mods -clean -config=debug -target=desktop
if %errorlevel% neq 0 exit /b %errorlevel%
