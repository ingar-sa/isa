@echo off
setlocal

set ORIGINAL_DIR=%CD%
set SCRIPT_DIR=%~dp0
cd /D %SCRIPT_DIR%
IF NOT EXIST build mkdir build

set BuildFolder=build
set FileOutputs=/Fe%BuildFolder%\main.exe /Fo%BuildFolder%\ /Fd%BuildFolder%\
set Libs=user32.lib kernel32.lib gdi32.lib

set Includes=/I"."
set CommonCompilerFlags=/MTd /nologo /GL /GR- /Od /Oi /W4 /wd4200 /wd4201 /wd4100 /wd4189 /wd4505 /Zi /DUNICODE /std:c17 %Includes% %FileOutputs%
set CommonLinkerFlags=/Fm%BuildFolder%\ /link %Libs%

del *.pdb > NUL 2> NUL
cl %CommonCompilerFlags% test_isa.c %CommonLinkerFlags%

cd /D %ORIGINAL_DIR%
endlocal
exit
