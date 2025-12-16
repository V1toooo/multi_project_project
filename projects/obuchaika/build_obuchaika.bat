@echo off
chcp 65001 > nul

set CPP_FILES=main.cpp menu_functions.cpp menu_items.cpp
set EXE=menu.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

g++ -finput-charset=utf-8 -fexec-charset=windows-1251 %CPP_FILES% -o %EXE%

if exist %EXE% (
    echo Программа успешно скомпилирована!
    %EXE%
) else (
    echo Ошибка компиляции!
    pause
)

pause