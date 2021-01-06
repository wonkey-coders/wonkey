
echo off

call common.bat

echo.
echo ***** Rebuilding wake *****
echo.

%wake% mods -clean -config=release wonkey libc miniz stb-image stb-image-write stb-vorbis zlib std
if %errorlevel% neq 0 exit /b %errorlevel%

%wake% app -clean -apptype=console -config=release -product=scripts/wake.products/wake_windows.exe ../src/wake/wake.wx
if %errorlevel% neq 0 exit /b %errorlevel%

copy wake.products\wake_windows.exe %wake%
if %errorlevel% neq 0 exit /b %errorlevel%
