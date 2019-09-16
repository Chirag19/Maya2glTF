@echo off
echo Copying "%~dp0\maya" to "%userprofile%\Documents\maya\"...
xcopy /y /s "%~dp0\maya" "%userprofile%\Documents\maya\"
if errorlevel 1 goto :error

color 2F
echo Done. Press ENTER to exit.
goto :exit

:error
color 4E
echo Failed to deploy maya2glTF!
echo Press ENTER to exit.
goto :exit

:exit
pause
color
