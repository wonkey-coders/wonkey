
echo off

call rebuildmods
if %errorlevel% neq 0 exit /b %errorlevel%

call rebuildwake
if %errorlevel% neq 0 exit /b %errorlevel%

call rebuildwide
if %errorlevel% neq 0 exit /b %errorlevel%

call rebuildlauncher
if %errorlevel% neq 0 exit /b %errorlevel%

call makedocs
if %errorlevel% neq 0 exit /b %errorlevel%
