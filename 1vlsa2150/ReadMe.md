# 1-as laboratorinis darbas: Ilgas sveikas skaičius

ADT - Ilgas sveikas skaičius, kuris leidžia atlikti aritmetines operacijas su skaičiais, viršijančiais standartinių C duomenų tipų (long long) ribas.

## Realizuotos funkcijos

- createBigInteger() – inicializuoja naują skaičiaus struktūrą.

- stringToBigInteger(char* str, BigInteger* BI) – konvertuoja tekstą į vidinę sąrašo struktūrą (base 256).

- bigIntegerToStringDec(BigInteger* BI) – konvertuoja skaičių iš vidinės bazės atgal į dešimtainę eilutę išvedimui.

- addBigInteger(BI1, BI2) – sudėtis su perkėlimo (carry) valdymu.

- subBigInteger(BI1, BI2) – atimtis su skolinimusi (borrow).

- mulBigInteger(BI1, BI2) – daugyba "stulpeliu" naudojant pagalbinę sudėtį.

- divBigInteger(BI1, BI2) – sveikoji dalyba atimties/palyginimo būdu.

- compareBigInteger(BI1, BI2) – palyginimo funkcija, reikalinga atimties ir dalybos logikai.

- Done(BigInteger** BI) – saugus atminties atlaisvinimas (destruktorius).

### Go.cmd
Paleidžia programą
```
$ ./Go.cmd
```

