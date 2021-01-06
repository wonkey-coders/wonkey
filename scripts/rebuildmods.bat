
echo off

echo.
echo ***** Rebuilding modules *****
echo.

..\bin\wake_windows mods -clean -config=release -target=desktop
if %errorlevel% neq 0 exit /b %errorlevel%

..\bin\wake_windows mods -clean -config=debug -target=desktop
if %errorlevel% neq 0 exit /b %errorlevel%
