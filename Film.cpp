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
    durata      = (dur > 0) ? dur  : 90;
    rating      = (rat >= 0.0f && rat <= 10.0f) ? rat : 0.0f;
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
        << "  Gen: "    << f.gen
        << "  Durata: " << f.durata  << " min"
        << "  Rating: " << f.rating
        << "  An: "     << f.an_aparitie;
    return out;
}