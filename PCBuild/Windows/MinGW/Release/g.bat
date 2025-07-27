@echo off

set current_dir=%cd%
set project_dir=%current_dir%\..\..\..\..
set build_dir=%project_dir%\build\Windows\MinGW\Release

cd %project_dir%
cmake -B %build_dir% -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cd %current_dir%