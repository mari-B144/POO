#ifndef FILM_H
#define FILM_H

#include <iostream>
#include <cstring>

/*
 * Clasa Film retine informatiile despre un film.
 *
 * Atribute:
 *   - titlu       : numele filmului (alocat dinamic)
 *   - gen         : genul filmului
 *   - durata      : durata in minute
 *   - rating      : nota 0.0 - 10.0
 *   - an_aparitie : anul lansarii
 */
class Film {
private:
    char*  titlu;
    char*  gen;
    int    durata;
    float  rating;
    int    an_aparitie;

    static int contor;

public:
    // Constructori, destructor, operator=, operator<<
    Film();
    Film(const char* titlu, const char* gen, int durata, float rating, int an);
    Film(const Film& f);
    ~Film();

    Film& operator=(const Film& f);
    friend std::ostream& operator<<(std::ostream& out, const Film& f);

    // Getteri (folositi in meniu si in incarcaDinFisier)
    const char* getTitlu()      const { return titlu; }
    const char* getGen()        const { return gen; }
    int         getDurata()     const { return durata; }
    float       getRating()     const { return rating; }
    int         getAnAparitie() const { return an_aparitie; }

    static int getContor() { return contor; }
};

#endif 