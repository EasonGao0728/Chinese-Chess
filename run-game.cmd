@echo off
setlocal
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0run-game.ps1"
set "RC=%ERRORLEVEL%"
if not "%RC%"=="0" (
  echo.
  echo Script exited with code %RC%.
)
endlocal & exit /b %RC%
