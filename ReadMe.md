# 3 laboratorinis darbas: Priemimo komisija

## Naudoti ADT
- [`Dekas`](1beva2327/) Paimtas Iš destytojo [puslapio](https://klevas.mif.vu.lt/~zagunas/ADS2026//StudWrk/)
- [`Ilgas sveikas skaicius`](1vlsa2150/) Paimtas Iš destytojo [puslapio](https://klevas.mif.vu.lt/~zagunas/ADS2026/StudWrk/)

Rasti defektai: 3.
- [`BigInteger`](#naudoti-adt) ir [`deque`](#naudoti-adt) turi besikertancius viešu funkciju.

## Varianto salyga

Priemimo komisijoje dirba dvi darbuotojos. Abi vienodai ilgai priima stojanciojo prasyma, taciau skirtingai ilgai ji sutvarko. Priimtas prasymas dedamas i lentyna is skirtingu deko pusiu. Kai nera laukianciu stojanciuju arba pasibaigia darbo diena, darbuotojos ima prasymus is savo puses ir juos tvarko. Reikia nustatyti papildoma darbo laika po priemimo ir darbuotoju uzimtuma procentais.

## Realizacija

Pagrindines programos failai:
- [main.c](/home/m1y/Projects/C/ADS/main.c)
- [params.c](/home/m1y/Projects/C/ADS/params.c)
- [simulation.c](/home/m1y/Projects/C/ADS/simulation.c)
- [Makefile](/home/m1y/Projects/C/ADS/Makefile)
- [Go.cmd](/home/m1y/Projects/C/ADS/Go.cmd)

[`Dekas`](#naudoti-adt) ir [`BigInteger`](#naudoti-adt) naudojami kaip atskiri moduliai is ju originaliu vietu. Kadangi ju višsu funkciju vardai kertasi, integracijai naudojamas [`bigint_compat.h`](/home/m1y/Projects/C/ADS/bigint_compat.h) ir [`Makefile`](#realizacija) kompiliavimo parametrai, nekeiciant paciu moduliu šaltiniu.

Kiekvienu modeliavimo laiko vienetu:
- pagal tikimybe sugeneruojamas naujas stojantysis;
- laisva darbuotoja pirmiausia priima laukianti stojantiji;
- jei laukianciu nera, darbuotoja tvarko prašyma iš savo deko puses;
- kaupiama statistika apie atejusius, priimtus, sutvarkytus prašymus, lentynos apkrova, uzimtuma ir poilsio laika.
