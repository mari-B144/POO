#ifndef SALA_H
#define SALA_H

#include <iostream>
#include <cstring>

/*
 * Clasa Sala reprezinta o sala de proiectie.
 *
 * Atribute:
 *   - id_sala    : identificator numeric unic
 *   - nume       : eticheta salii ("Sala Albastra" etc.)
 *   - capacitate : numarul total de locuri
 *   - locuri     : vector bool alocat dinamic (true = ocupat)
 *   - tip_sala   : "2D", "3D" sau "IMAX"
 *
 * Operatii posibile:
 *   - ocupare / eliberare loc individual
 *   - verificare disponibilitate loc
 *   - afisare harta vizuala a salii
 *   - calcul procent ocupare
 */
class Sala {
private:
    int   id_sala;
    char* nume;
    int   capacitate;
    bool* locuri;
    char* tip_sala;

    static int contor;

    bool idxValid(int i) const { return i >= 0 && i < capacitate; }

public:
    Sala();
    Sala(int id, const char* nume, int capacitate, const char* tip);
    Sala(const Sala& s);
    ~Sala();

    Sala& operator=(const Sala& s);
    friend std::ostream& operator<<(std::ostream& out, const Sala& s);

    // Getteri
    int         getIdSala()     const { return id_sala; }
    const char* getNume()       const { return nume; }
    int         getCapacitate() const { return capacitate; }
    const char* getTipSala()    const { return tip_sala; }

    // Setteri
    void setNume(const char* n);
    void setTipSala(const char* t);

    // Metode functionale
    bool  ocupaLoc(int idx);
    bool  elibereazaLoc(int idx);
    bool  esteDisponibil(int idx) const;
    int   locuriDisponibile()     const;
    int   primulLocLiber()        const; // -1 daca sala e plina
    void  resetLocuri();
    void  afiseazaHartaLocuri()   const;
    float procentOcupare()        const;

    static int getContor() { return contor; }
};

#endif // SALA_H
