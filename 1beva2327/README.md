# ADS Laboratorinis darbas - Dekas

**Deko duomenų struktūros realizavimas naudojant dinaminius masyvus C kalboje**
## Trumpai apie veikimą
Dekas – tai toks sąrašas, į kurį elementus galima įdėti ir iš jo išimti tiek iš pradžios, tiek iš galo. 
Kadangi naudojame dinaminį masyvą, pritaikytas žiedinio masyvo (circular buffer) principas.

## Failai
Projektą sudaro 3 failai:
1. **`deque.h`** – Čia aprašyta `Deque` struktūra (masyvas, talpa, elementų skaičius ir pradžios/galo indeksai) bei visų funkcijų pavadinimai.
2. **`deque.c`** – Failas, kuriame parašytas pats kodas (kaip visos funkcijos veikia ir kaip valdoma atmintis).
3. **`main.c`** – Pagrindinė programa, kurioje sukuriamas dekas ir ištestuojamos visos parašytos funkcijos.

## Realizuotos funkcijos
* **Sukūrimas / Sunaikinimas:**
  * `createDeque(talpa)` – sukuria tuščią deką su nurodytu maksimaliu elementų skaičiumi.
  * `destroyDeque(dq)` – atlaisvina išskirtą atmintį.
* **Būsenos patikrinimo funkcijos:**
  * `isEmpty(dq)` – grąžina 1, jei dekas tuščias, ir 0, jei ne.
  * `isFull(dq)` – grąžina 1, jei masyvas pilnas.
  * `getCount(dq)` – pasako, kiek šiuo metu deke yra elementų.
* **Įdėjimas / Išėmimas:**
  * `insertFront` ir `insertBack` – prideda skaičių į deko priekį arba galą.
  * `removeFront` ir `removeBack` – išima skaičių iš priekio arba galo ir jį grąžina.
  * `getFront` ir `getBack` – tik parodo, koks elementas yra priekyje/gale, bet jo neišima.
* **Papildomos (pagal užduotį):**
  * `clone(dq)` – padaro deko kopiją kitoje atminties vietoje.
  * `makeEmpty(dq)` – „išvalo“ deką, kad visi kintamieji būtų lyg naujo.
  * `toString(dq)` – sugeneruoja tekstą su deko elementais (pvz., `[5, 10, 20]`), kad būtų lengva jį atspausdinti ekrane su `printf`.