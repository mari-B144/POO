#include "Sala.h"
#include <cstring>

int Sala::contor = 0;

Sala::Sala() {
    id_sala    = 0;
    capacitate = 50;
    locuri     = new bool[capacitate];
    for (int i = 0; i < capacitate; i++) locuri[i] = false;
    nume     = new char[13]; std::strcpy(nume,     "Sala Default");
    tip_sala = new char[3];  std::strcpy(tip_sala, "2D");
    contor++;
}

Sala::Sala(int id, const char* n, int cap, const char* tip) {
    id_sala    = id;
    capacitate = (cap > 0) ? cap : 50;
    locuri     = new bool[capacitate];
    for (int i = 0; i < capacitate; i++) locuri[i] = false;
    nume     = new char[std::strlen(n)   + 1]; std::strcpy(nume,     n);
    tip_sala = new char[std::strlen(tip) + 1]; std::strcpy(tip_sala, tip);
    contor++;
}

Sala::Sala(const Sala& s) {
    id_sala    = s.id_sala;
    capacitate = s.capacitate;
    locuri     = new bool[capacitate];
    for (int i = 0; i < capacitate; i++) locuri[i] = s.locuri[i];
    nume     = new char[std::strlen(s.nume)     + 1]; std::strcpy(nume,     s.nume);
    tip_sala = new char[std::strlen(s.tip_sala) + 1]; std::strcpy(tip_sala, s.tip_sala);
    contor++;
}

Sala::~Sala() {
    delete[] locuri;
    delete[] nume;
    delete[] tip_sala;
    contor--;
}

Sala& Sala::operator=(const Sala& s) {
    if (this == &s) return *this;
    delete[] locuri; delete[] nume; delete[] tip_sala;
    id_sala    = s.id_sala;
    capacitate = s.capacitate;
    locuri     = new bool[capacitate];
    for (int i = 0; i < capacitate; i++) locuri[i] = s.locuri[i];
    nume     = new char[std::strlen(s.nume)     + 1]; std::strcpy(nume,     s.nume);
    tip_sala = new char[std::strlen(s.tip_sala) + 1]; std::strcpy(tip_sala, s.tip_sala);
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Sala& s) {
    out << "[Sala] ID:" << s.id_sala
        << "  " << s.nume
        << "  Tip:" << s.tip_sala
        << "  Cap:" << s.capacitate
        << "  Libere:" << s.locuriDisponibile()
        << "  Ocupare:" << s.procentOcupare() << "%";
    return out;
}

bool Sala::ocupaLoc(int idx) {
    if (!idxValid(idx) || locuri[idx]) return false;
    locuri[idx] = true;
    return true;
}

bool Sala::elibereazaLoc(int idx) {
    if (!idxValid(idx) || !locuri[idx]) return false;
    locuri[idx] = false;
    return true;
}

bool Sala::esteDisponibil(int idx) const {
    if (!idxValid(idx)) return false;
    return !locuri[idx];
}

int Sala::locuriDisponibile() const {
    int n = 0;
    for (int i = 0; i < capacitate; i++) if (!locuri[i]) n++;
    return n;
}

void Sala::afiseazaHartaLocuri() const {
    const int PE_RAND = 10;
    std::cout << "\n  Harta \"" << nume << "\" [O=ocupat  L=liber]\n  ";
    for (int i = 0; i < capacitate; i++) {
        std::cout << (locuri[i] ? " O" : " L");
        if ((i + 1) % PE_RAND == 0) std::cout << "\n  ";
    }
    std::cout << "\n";
}

float Sala::procentOcupare() const {
    if (capacitate == 0) return 0.0f;
    int ocupate = capacitate - locuriDisponibile();
    return (float)ocupate / capacitate * 100.0f;
}