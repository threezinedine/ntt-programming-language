@echo off

set current_dir=%cd%
set project_dir=%current_dir%\..\..\..\..
set build_dir=%project_dir%\build\Windows\MinGW\Debug

cd %build_dir%
cmake --build . --config Debug
cd %current_dir%
