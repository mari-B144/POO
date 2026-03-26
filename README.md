# ComplexCinema
Se modeleaza sistemul informatic al unui cinematograf care gestioneaza filme, sali de proiectie, rezervari si bilete.

# Clase
 *   Film      : titlu, gen, durata, rating, an_aparitie
 *   Sala      : id, capacitate, locuri[] (bool, dinamic), tip
 *   Bilet     : loc, tip, pret_baza, reducere automata
 *   Rezervare : Film + Sala + Bilet + data_ora