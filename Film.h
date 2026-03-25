#ifndef FILM_H
#define FILM_H

#include <iostream>
#include <cstring>

/*
 * Clasa Film retine informatiile despre un film din repertoriul cinematografului.
 *
 * Atribute:
 *   - titlu       : numele filmului (sir de caractere alocat dinamic)
 *   - gen         : genul filmului - "Actiune", "Drama", "Sci-Fi" etc.
 *   - durata      : durata in minute (> 0)
 *   - rating      : nota IMDb-like intre 0.0 si 10.0
 *   - an_aparitie : anul lansarii
 *
 * Operatii posibile:
 *   - verificare gen, rating minim, daca filmul este recent
 *   - cautare in colectii externe
 */
class Film {
private:
    char*  titlu;
    char*  gen;
    int    durata;
    float  rating;
    int    an_aparitie;

    static int contor;

    bool ratingValid(float r) const { return r >= 0.0f && r <= 10.0f; }
    bool durataValida(int d)  const { return d > 0; }

public:
    Film();
    Film(const char* titlu, const char* gen, int durata, float rating, int an);
    Film(const Film& f);
    ~Film();

    Film& operator=(const Film& f);
    friend std::ostream& operator<<(std::ostream& out, const Film& f);

    // Getteri
    const char* getTitlu()      const { return titlu; }
    const char* getGen()        const { return gen; }
    int         getDurata()     const { return durata; }
    float       getRating()     const { return rating; }
    int         getAnAparitie() const { return an_aparitie; }

    // Setteri
    void setTitlu(const char* t);
    void setGen(const char* g);
    void setDurata(int d);
    void setRating(float r);
    void setAnAparitie(int a);

    // Metode functionale
    bool esteDeGen(const char* g)    const;
    bool areRatingMinim(float min)   const;
    bool esteRecent(int an_curent)   const; // aparut in ultimii 2 ani

    static int getContor() { return contor; }
};

#endif // FILM_H
