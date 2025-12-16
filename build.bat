@echo off
set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja
chcp 65001 > nul

set BUILD_FOLDER=build_%BUILD_SUFFIX%\
set SOURCE_FOLDER=projects

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%
cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
if errorlevel 1 (
    echo CMake ошибка!
    pause
    exit /b 1
)

cmake --build .
if errorlevel 1 (
    echo Сборка ошибка!
    pause
    exit /b 1
)


set arr[0].file=build_sort.bat
set arr[1].file=build_obuchaika.bat

set arr[0].folder=obuchaika
set arr[1].folder=src

for /L %%i in (0,1) do (
    copy ..\%SOURCE_FOLDER%\!arr[%%i].folder!\!arr[%%i].file! .\!arr[%%i].folder!
)

copy ..\run_tests.bat .

pause