@echo off

set current_dir=%cd%
set project_dir=%current_dir%\..\..\..\..
set build_dir=%project_dir%\build\Windows\MinGW\Debug
set example_dir=%build_dir%\examples

cd %example_dir%
echo %cd%
for %%f in (%example_dir%\*.exe) do (
    echo %%f
    %%f
)
cd %current_dir%

