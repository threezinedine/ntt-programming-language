@echo off

set current_dir=%cd%
set project_dir=%current_dir%\..\..\..\..
set build_dir=%project_dir%\build\Windows\MinGW\Release

cd %build_dir%
NTTLanguage_test.exe
cd %current_dir%

