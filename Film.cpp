#include "Film.h"
#include <cstring>

int Film::contor = 0;

Film::Film() {
    titlu       = new char[10]; std::strcpy(titlu, "Necunoscut");
    gen         = new char[10]; std::strcpy(gen,   "Necunoscut");
    durata      = 90;
    rating      = 0.0f;
    an_aparitie = 2000;
    contor++;
}

Film::Film(const char* t, const char* g, int dur, float rat, int an) {
    titlu = new char[std::strlen(t) + 1]; std::strcpy(titlu, t);
    gen   = new char[std::strlen(g) + 1]; std::strcpy(gen,   g);
    durata      = durataValida(dur) ? dur  : 90;
    rating      = ratingValid(rat)  ? rat  : 0.0f;
    an_aparitie = an;
    contor++;
}

Film::Film(const Film& f) {
    titlu = new char[std::strlen(f.titlu) + 1]; std::strcpy(titlu, f.titlu);
    gen   = new char[std::strlen(f.gen)   + 1]; std::strcpy(gen,   f.gen);
    durata      = f.durata;
    rating      = f.rating;
    an_aparitie = f.an_aparitie;
    contor++;
}

Film::~Film() {
    delete[] titlu;
    delete[] gen;
    contor--;
}

Film& Film::operator=(const Film& f) {
    if (this == &f) return *this;
    delete[] titlu;
    delete[] gen;
    titlu = new char[std::strlen(f.titlu) + 1]; std::strcpy(titlu, f.titlu);
    gen   = new char[std::strlen(f.gen)   + 1]; std::strcpy(gen,   f.gen);
    durata      = f.durata;
    rating      = f.rating;
    an_aparitie = f.an_aparitie;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Film& f) {
    out << "[Film] \"" << f.titlu << "\""
        << "  Gen: "     << f.gen
        << "  Durata: "  << f.durata  << " min"
        << "  Rating: "  << f.rating
        << "  An: "      << f.an_aparitie;
    return out;
}

void Film::setTitlu(const char* t) {
    delete[] titlu;
    titlu = new char[std::strlen(t) + 1]; std::strcpy(titlu, t);
}
void Film::setGen(const char* g) {
    delete[] gen;
    gen = new char[std::strlen(g) + 1]; std::strcpy(gen, g);
}
void Film::setDurata(int d)   { if (durataValida(d)) durata = d; }
void Film::setRating(float r) { if (ratingValid(r))  rating = r; }
void Film::setAnAparitie(int a) { an_aparitie = a; }

bool Film::esteDeGen(const char* g)  const { return std::strcmp(gen, g) == 0; }
bool Film::areRatingMinim(float min) const { return rating >= min; }
bool Film::esteRecent(int an_curent) const { return (an_curent - an_aparitie) <= 2; }
