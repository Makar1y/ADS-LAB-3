if .%USERDOMAIN% == .DESKTOP-41MR8N8 goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
make

:toliau
test.exe > test.txt
