if .%USERDOMAIN% == .SavasPC goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
make

:toliau
echo 240 modeliavimo laikas > params.txt
echo 3   vieno prasymo priemimo laikas >> params.txt
echo 5   1 darbuotojos prasymo tvarkymo laikas >> params.txt
echo 8   2 darbuotojos prasymo tvarkymo laikas >> params.txt
echo 45  stojanciojo atejimo tikimybe (%%) >> params.txt
PriemimoKomisija.exe params.txt -rnd 50 > result1.txt
echo 360 modeliavimo laikas > PriemimoKomisija.cfg
echo 2   vieno prasymo priemimo laikas >> PriemimoKomisija.cfg
echo 4   1 darbuotojos prasymo tvarkymo laikas >> PriemimoKomisija.cfg
echo 7   2 darbuotojos prasymo tvarkymo laikas >> PriemimoKomisija.cfg
echo 55  stojanciojo atejimo tikimybe (%%) >> PriemimoKomisija.cfg
PriemimoKomisija.exe > result2.txt
