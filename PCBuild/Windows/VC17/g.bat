@echo off

set current_dir=%cd%
set project_dir=%current_dir%\..\..\..
set build_dir=%project_dir%\build\Windows\VC17

cd %project_dir%
cmake -B %build_dir% -G "Visual Studio 17 2022"
cd %current_dir%
