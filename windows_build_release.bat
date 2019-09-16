@echo off

echo Creating Visual Studio project...

call "%~dp0windows_create_vs_project.bat" %*
if errorlevel 1 goto :error

if exist "%~dp0build\release" (
    rd /s /q "%~dp0build\release"
    if errorlevel 1 goto :error
)

echo Updating version numbers...
msbuild "%~dp0UpdateVersionNumbers.vcxproj" 
if errorlevel 1 goto :error

echo Building Visual Studio project...
msbuild /v:q /p:Configuration=Release /p:Platform=x64 "%~dp0build\maya2glTF.vcxproj" 
if errorlevel 1 goto :error

echo Copying deployable files...
if exist "%~dp0build\release\Maya2glTF" (
    rd /s /q "%~dp0build\release\Maya2glTF"
    if errorlevel 1 goto :error
)   

mkdir "%~dp0build\release\Maya2glTF"
if errorlevel 1 goto :error

xcopy /y "%~dp0Maya\deploy.bat" "%~dp0build\release\Maya2glTF\"
if errorlevel 1 goto :error

xcopy /y "%~dp0build\release\*.mll"            "%~dp0build\release\Maya2glTF\Maya\Documents\maya\%1\plug-ins\"
if errorlevel 1 goto :error

xcopy /y /i "%~dp0maya\scripts\maya2glTF*.mel"  "%~dp0build\release\Maya2glTF\Maya\Documents\maya\%1\scripts\"
if errorlevel 1 goto :error

xcopy /y /s /i "%~dp0maya\renderData\*.*"       "%~dp0build\release\Maya2glTF\Maya\Documents\maya\maya2glTF\PBR\"
if errorlevel 1 goto :error

if exist "C:\Program Files\7-Zip\7z.exe" (
    echo Zipping deployable files...
    "C:\Program Files\7-Zip\7z.exe" a -tzip -r "%~dp0build\release\Maya2glTF_V1.0.0.zip" "%~dp0build\release\Maya2glTF\*"
    if errorlevel 1 goto :error
) else (
    echo 7-zip is not installed, not creating ZIP file.
)

%SystemRoot%\explorer.exe "%~dp0build\release"

echo ### SUCCESS ###
pause
goto :exit

:error
echo *** FAILED ***
pause

:exit
cd /d "%~dp0"