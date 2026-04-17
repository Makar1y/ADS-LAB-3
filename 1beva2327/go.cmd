if .%USERDOMAIN% == .BENAS goto :BENAS
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:BENAS
make

:toliau
main.exe > main.txt
make clean
pause