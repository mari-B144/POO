#ifndef REZERVARE_H
#define REZERVARE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include "Film.h"
#include "Sala.h"
#include "Bilet.h"

/*
 * Clasa Rezervare reprezinta o proiectie concreta:
 *   un film rulat intr-o sala la o data si ora specifice,
 *   cu un set de bilete vandute.
 *
 * Atribute:
 *   - id_rezervare : ID unic auto-incrementat
 *   - film         : obiect Film (copie)
 *   - sala         : obiect Sala (copie, gestioneaza locurile)
 *   - data_ora     : "DD/MM/YYYY HH:MM"
 *   - bilete       : vector dinamic de Bilet (fara STL)
 *   - nr_bilete    : numarul de bilete vandute
 *   - cap_bilete   : capacitatea vectorului dinamic
 *
 * Operatii posibile:
 *   - adaugare bilet cu verificare disponibilitate loc
 *   - calculare incasare totala a rezervarii
 *   - calculare incasare per tip bilet (adult/copil/senior/student)
 *   - afisare raport complet rezervare
 *   - cautare bilet dupa ID
 *   - stornare (anulare) bilet
 *
 * Citire date: sectiunea [REZERVARI] din date.txt
 *   FORMAT LINIE: id_sala|titlu_film|gen|durata|rating|an|data_ora
 *   FORMAT BILET: nr_loc|tip|pret_baza   (linii sub rezervare, pana la linie goala)
 */
class Rezervare {
private:
    int    id_rezervare;
    Film   film;
    Sala   sala;
    char*  data_ora;

    Bilet* bilete;
    int    nr_bilete;
    int    cap_bilete;

    static int contor;
    static int urmatorul_id;

    void extindBilete();

public:
    Rezervare();
    Rezervare(const Film& film, const Sala& sala, const char* data_ora);
    Rezervare(const Rezervare& r);
    ~Rezervare();

    Rezervare& operator=(const Rezervare& r);
    friend std::ostream& operator<<(std::ostream& out, const Rezervare& r);

    // Getteri
    int          getIdRezervare() const { return id_rezervare; }
    const Film&  getFilm()        const { return film; }
    const Sala&  getSala()        const { return sala; }
    const char*  getDataOra()     const { return data_ora; }
    int          getNrBilete()    const { return nr_bilete; }

    // Setteri
    void setDataOra(const char* d);

    // ── Functionalitati complexe ──────────────────────────────────────────

    // 1. Adauga bilet: verifica daca locul e disponibil in sala,
    //    ocupa locul si adauga biletul in vector. Returneaza true la succes.
    bool adaugaBilet(int nr_loc, const char* tip, float pret_baza);

    // 2. Anuleaza biletul cu id-ul dat: elibereaza locul si sterge biletul.
    bool anuleazaBilet(int id_bilet);

    // 3. Calcul incasare totala a rezervarii (suma preturilor finale)
    float incasareTotala() const;

    // 4. Calcul incasare per tip bilet (adult / copil / senior / student)
    //    Scrie in parametrii de iesire valorile pentru fiecare tip.
    void incasarePerTip(float& adult, float& copil,
                        float& senior, float& student) const;

    // 5. Verifica daca sala mai are locuri libere
    bool areLocuriDisponibile() const;

    // 6. Afisare raport detaliat al rezervarii
    void afiseazaRaport() const;

    // 7. Afisare harta locuri din sala
    void afiseazaHartaSala() const { sala.afiseazaHartaLocuri(); }

    // 8. Afisare chitanta pentru biletul cu id-ul dat (-1 => eroare)
    void afiseazaChitantaBilet(int id_bilet) const;

    // ── Citire din fisier ─────────────────────────────────────────────────
    // Incarca toate rezervarile din sectiunea [REZERVARI] a fisierului date.txt
    // Populeaza vectorul rezervari[] si actualizeaza nr_rez.
    // Metoda statica de fabrica: aloca si returneaza un vector de Rezervare*.
    static int incarcaDinFisier(const char* cale,
                                Rezervare*& rezervari_out,
                                int& cap_out);

    static int getContor()     { return contor; }
    static int getUrmatorulId(){ return urmatorul_id; }
};

// ── Functii globale de analiza (lucreaza pe un vector de rezervari) ───────────

// Afiseaza filmele cu rating >= min din vectorul dat
void cautaFilmeRatingMinim(const Rezervare* rezervari, int nr, float min);

// Afiseaza rezervarile al caror film e de genul cerut
void cautaRezervariDeGen(const Rezervare* rezervari, int nr, const char* gen);

// Afiseaza top N rezervari dupa incasare totala (bubble sort descrescator)
void topRezervariIncasari(const Rezervare* rezervari, int nr, int n);

// Raport global: incasare totala din toate rezervarile
float incasareTotalaGlobala(const Rezervare* rezervari, int nr);

#endif // REZERVARE_H
