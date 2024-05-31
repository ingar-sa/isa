@echo off
setlocal

IF NOT EXIST Build mkdir Build

cd build
main.exe

endlocal
exit
