
echo off

..\bin\windows\wake docs %*
if %errorlevel% neq 0 exit /b %errorlevel%
