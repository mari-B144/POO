# ComplexCinema
Se modeleaza sistemul informatic al unui cinematograf care gestioneaza filme, sali de proiectie, rezervari si bilete.

## Clase
 *   **Film**      : titlu, gen, durata, rating, an_aparitie
 *   **Sala**      : id, capacitate, locuri[] (bool, dinamic), tip
 *   **Bilet**     : loc, tip, pret_baza, reducere automata
 *   **Rezervare** : Film + Sala + Bilet + data ora

## Optiuni meniu
1. Afisare toate rezervarile
2. Harta locuri sala
3. Vanzare bilet manual
4. Anulare bilet
5. Incasari per tip bilet
6. Incasare totala globala
7. Afisare chitanta bilet