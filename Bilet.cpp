#include "Bilet.h"
#include <cstring>

int Bilet::contor       = 0;
int Bilet::urmatorul_id = 1;

float Bilet::procentReducere() const {
    if (std::strcmp(tip_bilet, "copil")   == 0) return 0.30f;
    if (std::strcmp(tip_bilet, "senior")  == 0) return 0.20f;
    if (std::strcmp(tip_bilet, "student") == 0) return 0.15f;
    return 0.0f;
}

Bilet::Bilet() {
    id_bilet  = urmatorul_id++;
    nr_loc    = 0;
    pret_baza = 30.0f;
    tip_bilet = new char[6]; std::strcpy(tip_bilet, "adult");
    contor++;
}

Bilet::Bilet(int loc, const char* tip, float pret) {
    id_bilet  = urmatorul_id++;
    nr_loc    = loc;
    pret_baza = (pret > 0) ? pret : 30.0f;
    tip_bilet = new char[std::strlen(tip) + 1]; std::strcpy(tip_bilet, tip);
    contor++;
}

Bilet::Bilet(const Bilet& b) {
    id_bilet  = urmatorul_id++;   // bilet nou => ID nou
    nr_loc    = b.nr_loc;
    pret_baza = b.pret_baza;
    tip_bilet = new char[std::strlen(b.tip_bilet) + 1];
    std::strcpy(tip_bilet, b.tip_bilet);
    contor++;
}

Bilet::~Bilet() {
    delete[] tip_bilet;
    contor--;
}

Bilet& Bilet::operator=(const Bilet& b) {
    if (this == &b) return *this;
    delete[] tip_bilet;
    // id_bilet ramane al obiectului curent (nu se copiaza)
    nr_loc    = b.nr_loc;
    pret_baza = b.pret_baza;
    tip_bilet = new char[std::strlen(b.tip_bilet) + 1];
    std::strcpy(tip_bilet, b.tip_bilet);
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Bilet& b) {
    out << "[Bilet #" << b.id_bilet << "]"
        << "  Loc:" << b.nr_loc + 1
        << "  Tip:" << b.tip_bilet
        << "  Pret baza:" << b.pret_baza << " RON";
    if (b.areReducere())
        out << "  => Pret final:" << b.pretFinal() << " RON"
            << " (-" << b.procentReducere() * 100 << "%)";
    else
        out << "  => Pret final:" << b.pretFinal() << " RON";
    return out;
}

void Bilet::setTipBilet(const char* tip) {
    delete[] tip_bilet;
    tip_bilet = new char[std::strlen(tip) + 1]; std::strcpy(tip_bilet, tip);
}
void Bilet::setPretBaza(float p) { if (p > 0) pret_baza = p; }

float Bilet::pretFinal()       const { return pret_baza * (1.0f - procentReducere()); }
float Bilet::valoareReducere() const { return pret_baza * procentReducere(); }
bool  Bilet::areReducere()     const { return procentReducere() > 0.0f; }

void Bilet::afiseazaChitanta(const char* titlu_film,
                              int id_sala,
                              const char* data) const {
    std::cout << "  +--------------------------------------+\n";
    std::cout << "  |        CINEMATOGRAF  -  BILET        |\n";
    std::cout << "  +--------------------------------------+\n";
    std::cout << "  | Bilet #" << id_bilet << "\n";
    std::cout << "  | Film   : " << titlu_film << "\n";
    std::cout << "  | Data   : " << data << "\n";
    std::cout << "  | Sala   : " << id_sala << "\n";
    std::cout << "  | Loc    : " << nr_loc + 1 << "\n";
    std::cout << "  | Tip    : " << tip_bilet << "\n";
    std::cout << "  | Baza   : " << pret_baza << " RON\n";
    if (areReducere())
        std::cout << "  | Reduc. : -" << valoareReducere()
                  << " RON (" << procentReducere() * 100 << "%)\n";
    std::cout << "  +--------------------------------------+\n";
    std::cout << "  | TOTAL  : " << pretFinal() << " RON\n";
    std::cout << "  +--------------------------------------+\n";
}
