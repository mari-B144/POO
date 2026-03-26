#include "Rezervare.h"
#include <cstring>
#include <cstdlib>

int Rezervare::contor       = 0;
int Rezervare::urmatorul_id = 1;

// ─── helper privat ────────────────────────────────────────────────────────────

void Rezervare::extindBilete() {
    cap_bilete *= 2;
    Bilet* nou = new Bilet[cap_bilete];
    for (int i = 0; i < nr_bilete; i++) nou[i] = bilete[i];
    delete[] bilete;
    bilete = nou;
}

// ─── constructori / destructor ────────────────────────────────────────────────

Rezervare::Rezervare() : film(), sala() {
    id_rezervare = urmatorul_id++;
    data_ora     = new char[17]; std::strcpy(data_ora, "01/01/2025 20:00");
    cap_bilete   = 8;
    nr_bilete    = 0;
    bilete       = new Bilet[cap_bilete];
    contor++;
}

Rezervare::Rezervare(const Film& f, const Sala& s, const char* d)
    : film(f), sala(s) {
    id_rezervare = urmatorul_id++;
    data_ora     = new char[std::strlen(d) + 1]; std::strcpy(data_ora, d);
    cap_bilete   = 8;
    nr_bilete    = 0;
    bilete       = new Bilet[cap_bilete];
    contor++;
}

Rezervare::Rezervare(const Rezervare& r) : film(r.film), sala(r.sala) {
    id_rezervare = urmatorul_id++;
    data_ora     = new char[std::strlen(r.data_ora) + 1];
    std::strcpy(data_ora, r.data_ora);
    cap_bilete   = r.cap_bilete;
    nr_bilete    = r.nr_bilete;
    bilete       = new Bilet[cap_bilete];
    for (int i = 0; i < nr_bilete; i++) bilete[i] = r.bilete[i];
    contor++;
}

Rezervare::~Rezervare() {
    delete[] data_ora;
    delete[] bilete;
    contor--;
}

Rezervare& Rezervare::operator=(const Rezervare& r) {
    if (this == &r) return *this;
    delete[] data_ora;
    delete[] bilete;
    film       = r.film;
    sala       = r.sala;
    data_ora   = new char[std::strlen(r.data_ora) + 1];
    std::strcpy(data_ora, r.data_ora);
    cap_bilete = r.cap_bilete;
    nr_bilete  = r.nr_bilete;
    bilete     = new Bilet[cap_bilete];
    for (int i = 0; i < nr_bilete; i++) bilete[i] = r.bilete[i];
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Rezervare& r) {
    out << "[Rezervare #" << r.id_rezervare << "]"
        << "  Film: \""  << r.film.getTitlu() << "\""
        << "  Sala: "    << r.sala.getIdSala()
        << " (" << r.sala.getNume() << ")"
        << "  Data: "    << r.data_ora
        << "  Bilete: "  << r.nr_bilete
        << "  Incasare: " << r.incasareTotala() << " RON";
    return out;
}

// ─── metode publice ───────────────────────────────────────────────────────────

bool Rezervare::adaugaBilet(int nr_loc, const char* tip, float pret_baza) {
    if (!sala.esteDisponibil(nr_loc)) {
        std::cout << "  [EROARE] Locul " << nr_loc + 1
                  << " din sala " << sala.getIdSala()
                  << " este deja ocupat sau invalid.\n";
        return false;
    }
    sala.ocupaLoc(nr_loc);
    if (nr_bilete == cap_bilete) extindBilete();
    Bilet b(nr_loc, tip, pret_baza);
    bilete[nr_bilete++] = b;
    std::cout << "  [OK] Bilet vandut - Loc " << nr_loc + 1
              << "  Tip: " << tip
              << "  Pret final: " << b.pretFinal() << " RON\n";
    return true;
}

bool Rezervare::anuleazaBilet(int id_bilet) {
    for (int i = 0; i < nr_bilete; i++) {
        if (bilete[i].getIdBilet() == id_bilet) {
            sala.elibereazaLoc(bilete[i].getNrLoc());
            bilete[i] = bilete[nr_bilete - 1];
            nr_bilete--;
            std::cout << "  [OK] Bilet #" << id_bilet << " anulat.\n";
            return true;
        }
    }
    std::cout << "  [EROARE] Bilet #" << id_bilet << " negasit.\n";
    return false;
}

float Rezervare::incasareTotala() const {
    float total = 0.0f;
    for (int i = 0; i < nr_bilete; i++) total += bilete[i].pretFinal();
    return total;
}

void Rezervare::incasarePerTip(float& adult, float& copil,
                                float& senior, float& student) const {
    adult = copil = senior = student = 0.0f;
    for (int i = 0; i < nr_bilete; i++) {
        float pf        = bilete[i].pretFinal();
        const char* tip = bilete[i].getTipBilet();
        if      (std::strcmp(tip, "adult")   == 0) adult   += pf;
        else if (std::strcmp(tip, "copil")   == 0) copil   += pf;
        else if (std::strcmp(tip, "senior")  == 0) senior  += pf;
        else if (std::strcmp(tip, "student") == 0) student += pf;
    }
}

bool Rezervare::areLocuriDisponibile() const {
    return sala.locuriDisponibile() > 0;
}

void Rezervare::afiseazaRaport() const {
    std::cout << "\n============================================\n";
    std::cout << "  RAPORT REZERVARE #" << id_rezervare << "\n";
    std::cout << "============================================\n";
    std::cout << "  Film  : " << film.getTitlu()
              << "  (Gen: " << film.getGen()
              << ", Rating: " << film.getRating() << ")\n";
    std::cout << "  Sala  : " << sala.getNume()
              << " [" << sala.getTipSala() << "]"
              << "  Cap: " << sala.getCapacitate() << "\n";
    std::cout << "  Data  : " << data_ora << "\n";
    std::cout << "  Locuri disponibile: " << sala.locuriDisponibile()
              << " / " << sala.getCapacitate()
              << "  (" << sala.procentOcupare() << "% ocupat)\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "  Bilete vandute (" << nr_bilete << "):\n";
    for (int i = 0; i < nr_bilete; i++)
        std::cout << "    " << bilete[i] << "\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "  TOTAL INCASAT: " << incasareTotala() << " RON\n";
    std::cout << "============================================\n";
}

void Rezervare::afiseazaChitantaBilet(int id_bilet) const {
    for (int i = 0; i < nr_bilete; i++) {
        if (bilete[i].getIdBilet() == id_bilet) {
            bilete[i].afiseazaChitanta(film.getTitlu(),
                                       sala.getIdSala(),
                                       data_ora);
            return;
        }
    }
    std::cout << "  [EROARE] Bilet #" << id_bilet << " negasit.\n";
}

// ─── parsare camp din linie delimitata cu '|' ─────────────────────────────────

static const char* parseCamp(const char* ptr, char* buf, int maxlen) {
    int i = 0;
    while (*ptr && *ptr != '|' && *ptr != '\n' && *ptr != '\r' && i < maxlen - 1)
        buf[i++] = *ptr++;
    buf[i] = '\0';
    if (*ptr == '|') ptr++;
    return ptr;
}

// ─── citire din fisier ────────────────────────────────────────────────────────
/*
 * FORMAT date.txt:
 *
 * [FILME]
 * titlu|gen|durata|rating|an
 *
 * [SALI]
 * id|nume|capacitate|tip
 *
 * [REZERVARI]
 * id_sala|titlu_film|data_ora
 * nr_loc|tip_bilet|pret_baza
 * ---
 *
 * Liniile cu '#' sunt comentarii. Rezervarile se separa cu "---".
 */
int Rezervare::incarcaDinFisier(const char* cale,
                                 Rezervare*& rezervari_out,
                                 int& cap_out) {
    std::ifstream fin(cale);
    if (!fin.is_open()) {
        std::cout << "[EROARE] Nu pot deschide: " << cale << "\n";
        return 0;
    }

    const int MAX_F = 50, MAX_S = 20;
    Film filme_disp[MAX_F]; int nr_filme = 0;
    Sala sali_disp[MAX_S];  int nr_sali  = 0;

    char linie[256];
    enum Sectiune { NIMIC, FILME, SALI, REZERVARI } sec = NIMIC;

    // prima trecere: filme + sali
    while (fin.getline(linie, 256)) {
        if (linie[0] == '#' || linie[0] == '\0' || linie[0] == '\r') continue;
        if (std::strcmp(linie, "[FILME]")     == 0) { sec = FILME;     continue; }
        if (std::strcmp(linie, "[SALI]")      == 0) { sec = SALI;      continue; }
        if (std::strcmp(linie, "[REZERVARI]") == 0) { sec = REZERVARI; break; }

        if (sec == FILME && nr_filme < MAX_F) {
            char titlu[64], gen[32], s_dur[8], s_rat[8], s_an[8];
            const char* p = linie;
            p = parseCamp(p, titlu, 64);
            p = parseCamp(p, gen,   32);
            p = parseCamp(p, s_dur, 8);
            p = parseCamp(p, s_rat, 8);
            p = parseCamp(p, s_an,  8);
            filme_disp[nr_filme++] = Film(titlu, gen,
                                          std::atoi(s_dur),
                                          (float)std::atof(s_rat),
                                          std::atoi(s_an));
        }
        if (sec == SALI && nr_sali < MAX_S) {
            char s_id[8], nm[64], s_cap[8], tip[8];
            const char* p = linie;
            p = parseCamp(p, s_id,  8);
            p = parseCamp(p, nm,   64);
            p = parseCamp(p, s_cap, 8);
            p = parseCamp(p, tip,   8);
            sali_disp[nr_sali++] = Sala(std::atoi(s_id), nm,
                                        std::atoi(s_cap), tip);
        }
    }
    std::cout << "[OK] Citit " << nr_filme << " filme si "
              << nr_sali << " sali din '" << cale << "'.\n";

    // a doua trecere: rezervari
    cap_out = 16;
    int nr_rez = 0;
    rezervari_out = new Rezervare[cap_out];

    bool in_rezervare = false;
    int  rez_idx      = -1;

    while (fin.getline(linie, 256)) {
        int len = (int)std::strlen(linie);
        if (len > 0 && linie[len - 1] == '\r') linie[--len] = '\0';
        if (linie[0] == '#') continue;

        if (linie[0] == '\0' || std::strcmp(linie, "---") == 0) {
            in_rezervare = false;
            continue;
        }

        if (!in_rezervare) {
            // antet rezervare: id_sala|titlu_film|data_ora
            char s_id[8], titlu[64], data[20];
            const char* p = linie;
            p = parseCamp(p, s_id,  8);
            p = parseCamp(p, titlu, 64);
            p = parseCamp(p, data,  20);

            int id_sala = std::atoi(s_id);

            Sala* sala_ptr = 0;
            Film* film_ptr = 0;
            for (int i = 0; i < nr_sali;  i++)
                if (sali_disp[i].getIdSala() == id_sala)
                    { sala_ptr = &sali_disp[i]; break; }
            for (int i = 0; i < nr_filme; i++)
                if (std::strcmp(filme_disp[i].getTitlu(), titlu) == 0)
                    { film_ptr = &filme_disp[i]; break; }

            if (!sala_ptr || !film_ptr) {
                std::cout << "[ATENTIE] Sala " << id_sala
                          << " sau film '" << titlu << "' negasite.\n";
                continue;
            }

            if (nr_rez == cap_out) {
                cap_out *= 2;
                Rezervare* nou = new Rezervare[cap_out];
                for (int i = 0; i < nr_rez; i++) nou[i] = rezervari_out[i];
                delete[] rezervari_out;
                rezervari_out = nou;
            }

            rezervari_out[nr_rez] = Rezervare(*film_ptr, *sala_ptr, data);
            rez_idx = nr_rez++;
            in_rezervare = true;

        } else {
            // bilet: nr_loc|tip|pret_baza
            char s_loc[8], tip[16], s_pret[12];
            const char* p = linie;
            p = parseCamp(p, s_loc,  8);
            p = parseCamp(p, tip,   16);
            p = parseCamp(p, s_pret, 12);
            rezervari_out[rez_idx].adaugaBilet(std::atoi(s_loc), tip,
                                               (float)std::atof(s_pret));
        }
    }

    fin.close();
    std::cout << "[OK] Incarcate " << nr_rez
              << " rezervari din '" << cale << "'.\n";
    return nr_rez;
}


float incasareTotalaGlobala(const Rezervare* rezervari, int nr) {
    float total = 0.0f;
    for (int i = 0; i < nr; i++) total += rezervari[i].incasareTotala();
    return total;
}