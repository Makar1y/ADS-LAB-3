# 3 laboratorinis darbas: Priemimo komisija

Naudoti ADT:
- [`Dekas`](1beva2327/) Paimtas Iš destytojo [puslapio](https://klevas.mif.vu.lt/~zagunas/ADS2026//StudWrk/)
- [`Ilgas sveikas skaicius`](1vlsa2150/) Paimtas Iš destytojo [puslapio](https://klevas.mif.vu.lt/~zagunas/ADS2026/StudWrk/)

Rasti defektai: 3.
- `BigInteger` ir `deque` turi besikertancius viesu funkciju vardus: `isEmpty`, `isFull`, `makeEmpty`, `clone`, `count`.
- `deque` realizacija neturi dinamines talpos didinimo ir prisipildzius tik isveda klaidos pranesima.
- `deque` funkcija `toString` naudoja fiksuoto dydzio buferi.

## Varianto salyga

Priemimo komisijoje dirba dvi darbuotojos. Abi vienodai ilgai priima stojanciojo prasyma, taciau skirtingai ilgai ji sutvarko. Priimtas prasymas dedamas i lentyna is skirtingu deko pusiu. Kai nera laukianciu stojanciuju arba pasibaigia darbo diena, darbuotojos ima prasymus is savo puses ir juos tvarko. Reikia nustatyti papildoma darbo laika po priemimo ir darbuotoju uzimtuma procentais.

## Realizacija

Programa parasyta root kataloge:
- [main.c](/home/m1y/Projects/C/ADS/main.c)
- [params.c](/home/m1y/Projects/C/ADS/params.c)
- [simulation.c](/home/m1y/Projects/C/ADS/simulation.c)
- [Makefile](/home/m1y/Projects/C/ADS/Makefile)
- [Go.cmd](/home/m1y/Projects/C/ADS/Go.cmd)

`Dekas` ir `BigInteger` naudojami kaip atskiri moduliai is ju originaliu vietu. Kadangi ju viesu funkciju vardai kertasi, integracijai naudojamas [bigint_compat.h](/home/m1y/Projects/C/ADS/bigint_compat.h) ir `Makefile` kompiliavimo parametrai, nekeiciant paciu moduliu saltiniu.

Kiekvienu modeliavimo laiko vienetu:
- pagal tikimybe sugeneruojamas naujas stojantysis;
- laisva darbuotoja pirmiausia priima laukianti stojantiji;
- jei laukianciu nera, darbuotoja tvarko prasyma is savo deko puses;
- kaupiama statistika apie atejusius, priimtus, sutvarkytus prasymus, lentynos apkrova, uzimtuma ir poilsio laika.

## Bendravimas ir bendradarbiavimas

Bendroji kompetencija **bendravimas ir bendradarbiavimas** realizuota taip:
- sprendimas suskaidytas i modulius, kad prie skirtingu daliu butu galima dirbti atskirai;
- `Makefile` atskirai transliuoja bendrai panaudojamus modulius;
- `Go.cmd` leidzia vienodai paleisti darba skirtingose aplinkose;
- `ReadMe.md` apraso priimtus sprendimus, kad kita komandos nare ar narys galetu lengvai perimti darba.
