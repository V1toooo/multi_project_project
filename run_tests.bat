@echo off
chcp 65001
cd build_ninja
ctest --output-on-failure
pause