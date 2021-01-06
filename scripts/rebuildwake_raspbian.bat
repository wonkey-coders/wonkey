echo off

call common.bat

echo.
echo ***** Rebuilding wake *****
echo.

%wake% mods -clean -config=release -target=raspbian wonkey libc miniz stb-image stb-image-write stb-vorbis std
if %errorlevel% neq 0 exit /b %errorlevel%

%wake% app -build -clean -apptype=console -config=release -target=raspbian ../src/wake/wake.wx
if %errorlevel% neq 0 exit /b %errorlevel%

copy %wake_raspbian_new% ..\bin\raspbian\wake
if %errorlevel% neq 0 exit /b %errorlevel%
