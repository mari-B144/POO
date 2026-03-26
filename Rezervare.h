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

    // Getteri folositi in meniu
    const Film& getFilm()     const { return film; }
    const Sala& getSala()     const { return sala; }
    const char* getDataOra()  const { return data_ora; }
    int         getNrBilete() const { return nr_bilete; }

    // Metode folosite in meniu
    bool  adaugaBilet(int nr_loc, const char* tip, float pret_baza);
    bool  anuleazaBilet(int id_bilet);
    float incasareTotala() const;
    void  incasarePerTip(float& adult, float& copil,
                         float& senior, float& student) const;
    bool  areLocuriDisponibile() const;
    void  afiseazaRaport()       const;
    void  afiseazaHartaSala()    const { sala.afiseazaHartaLocuri(); }
    void  afiseazaChitantaBilet(int id_bilet) const;

    // Citire din fisier date.txt
    static int incarcaDinFisier(const char* cale,
                                Rezervare*& rezervari_out,
                                int& cap_out);

    static int getContor()      { return contor; }
    static int getUrmatorulId() { return urmatorul_id; }
};

// Functie globala folosita in meniu (case 6)
float incasareTotalaGlobala(const Rezervare* rezervari, int nr);

#endif 