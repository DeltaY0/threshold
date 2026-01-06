@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Usage: %~nx0 [directory1] [directory2] ...
    exit /b 1
)

set /a totalLines=0

:: Loop through each directory provided as an argument
for %%D in (%*) do (
    if exist "%%~D" (
        echo Counting lines in: %%~D
        
        :: Find all files recursively in this directory
        for /f "delims=" %%A in ('dir "%%~D" /s /b /a-d') do (
            :: Pipe file content to find so it returns ONLY a number
            for /f %%C in ('type "%%~A" ^| find /v /c ""') do (
                set /a totalLines+=%%C
            )
        )
    ) else (
        echo Directory not found: %%~D
    )
)

echo.
echo ----------------------------------------
echo TOTAL LINES ACROSS ALL DIRECTORIES: %totalLines%
echo ----------------------------------------
pause
