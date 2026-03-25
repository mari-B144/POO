#ifndef BILET_H
#define BILET_H

#include <iostream>
#include <cstring>

/*
 * Clasa Bilet reprezinta un bilet emis pentru un loc dintr-o rezervare.
 *
 * Atribute:
 *   - id_bilet   : numar unic auto-incrementat (static)
 *   - nr_loc     : indexul locului in sala (0-based)
 *   - tip_bilet  : "adult" | "copil" | "senior" | "student"
 *   - pret_baza  : pretul inainte de reducere (RON)
 *
 * Reduceri aplicate automat:
 *   - copil   : -30%
 *   - senior  : -20%
 *   - student : -15%
 *   - adult   :   0%
 *
 * Operatii posibile:
 *   - calcul pret final cu reducere
 *   - afisare chitanta formatata
 */
class Bilet {
private:
    int   id_bilet;
    int   nr_loc;
    char* tip_bilet;
    float pret_baza;

    static int contor;
    static int urmatorul_id;

    float procentReducere() const;   // returneaza 0.30, 0.20, 0.15 sau 0.0

public:
    Bilet();
    Bilet(int nr_loc, const char* tip, float pret_baza);
    Bilet(const Bilet& b);
    ~Bilet();

    Bilet& operator=(const Bilet& b);
    friend std::ostream& operator<<(std::ostream& out, const Bilet& b);

    // Getteri
    int         getIdBilet()  const { return id_bilet; }
    int         getNrLoc()    const { return nr_loc; }
    const char* getTipBilet() const { return tip_bilet; }
    float       getPretBaza() const { return pret_baza; }

    // Setteri
    void setTipBilet(const char* tip);
    void setPretBaza(float p);

    // Metode functionale
    float pretFinal()        const;  // pret_baza * (1 - reducere)
    float valoareReducere()  const;  // suma scazuta in RON
    bool  areReducere()      const;  // true daca tip != "adult"
    void  afiseazaChitanta(const char* titlu_film,
                           int id_sala,
                           const char* data) const;

    static int getContor()    { return contor; }
    static int getUrmatorulId() { return urmatorul_id; }
};

#endif // BILET_H
