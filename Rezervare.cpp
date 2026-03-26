#include "Rezervare.h"
#include <cstring>
#include <cstdlib>   // atoi, atof

int Rezervare::contor       = 0;
int Rezervare::urmatorul_id = 1;

// ─── helper privat ───────────────────────────────────────────────────────────

void Rezervare::extindBilete() {
    cap_bilete *= 2;
    Bilet* nou = new Bilet[cap_bilete];
    for (int i = 0; i < nr_bilete; i++) nou[i] = bilete[i];
    delete[] bilete;
    bilete = nou;
}

// ─── constructori / destructor ───────────────────────────────────────────────

Rezervare::Rezervare()
    : film(), sala() {
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

Rezervare::Rezervare(const Rezervare& r)
    : film(r.film), sala(r.sala) {
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

    film = r.film;
    sala = r.sala;
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

// ─── setter ──────────────────────────────────────────────────────────────────

void Rezervare::setDataOra(const char* d) {
    delete[] data_ora;
    data_ora = new char[std::strlen(d) + 1]; std::strcpy(data_ora, d);
}

// ─── functionalitati complexe ────────────────────────────────────────────────

// 1. Adaugare bilet cu verificare disponibilitate
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

// 2. Anulare bilet dupa ID
bool Rezervare::anuleazaBilet(int id_bilet) {
    for (int i = 0; i < nr_bilete; i++) {
        if (bilete[i].getIdBilet() == id_bilet) {
            sala.elibereazaLoc(bilete[i].getNrLoc());
            // suprascriem cu ultimul si scadem contorul
            bilete[i] = bilete[nr_bilete - 1];
            nr_bilete--;
            std::cout << "  [OK] Bilet #" << id_bilet << " anulat.\n";
            return true;
        }
    }
    std::cout << "  [EROARE] Bilet #" << id_bilet << " negasit in aceasta rezervare.\n";
    return false;
}

// 3. Incasare totala rezervare
float Rezervare::incasareTotala() const {
    float total = 0.0f;
    for (int i = 0; i < nr_bilete; i++) total += bilete[i].pretFinal();
    return total;
}

// 4. Incasare per tip
void Rezervare::incasarePerTip(float& adult, float& copil,
                                float& senior, float& student) const {
    adult = copil = senior = student = 0.0f;
    for (int i = 0; i < nr_bilete; i++) {
        float pf = bilete[i].pretFinal();
        const char* tip = bilete[i].getTipBilet();
        if (std::strcmp(tip, "adult")   == 0) adult   += pf;
        else if (std::strcmp(tip, "copil")   == 0) copil   += pf;
        else if (std::strcmp(tip, "senior")  == 0) senior  += pf;
        else if (std::strcmp(tip, "student") == 0) student += pf;
    }
}

// 5. Verifica locuri libere
bool Rezervare::areLocuriDisponibile() const {
    return sala.locuriDisponibile() > 0;
}

// 6. Raport detaliat
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

    float a, c, s, st;
    incasarePerTip(a, c, s, st);
    std::cout << "--------------------------------------------\n";
    std::cout << "  Incasari per tip:\n";
    std::cout << "    Adult  : " << a  << " RON\n";
    std::cout << "    Copil  : " << c  << " RON\n";
    std::cout << "    Senior : " << s  << " RON\n";
    std::cout << "    Student: " << st << " RON\n";
    std::cout << "============================================\n";
    std::cout << "  TOTAL INCASAT: " << incasareTotala() << " RON\n";
    std::cout << "============================================\n";
}

// ─── helper parsare camp din linie delimitata cu '|' ─────────────────────────
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
 * ...
 *
 * [SALI]
 * id|nume|capacitate|tip
 * ...
 *
 * [REZERVARI]
 * id_sala|titlu_film|data_ora
 * nr_loc|tip_bilet|pret_baza
 * nr_loc|tip_bilet|pret_baza
 * ---
 * id_sala|titlu_film|data_ora
 * ...
 *
 * Liniile care incep cu '#' sunt comentarii.
 * Rezervarile sunt separate de linia "---".
 * Fisierul contine TOATE datele intr-un singur loc.
 *
 * Metoda returneaza numarul de rezervari incarcate.
 * Rezervarile sunt stocate in rezervari_out (alocat dinamic).
 */
int Rezervare::incarcaDinFisier(const char* cale,
                                 Rezervare*& rezervari_out,
                                 int& cap_out) {
    std::ifstream fin(cale);
    if (!fin.is_open()) {
        std::cout << "[EROARE] Nu pot deschide: " << cale << "\n";
        return 0;
    }

    // ── pas 1: citim filmele si salile disponibile ──────────────────────────
    const int MAX_F = 50, MAX_S = 20;
    Film filme_disp[MAX_F];  int nr_filme = 0;
    Sala sali_disp[MAX_S];   int nr_sali  = 0;

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

    // ── pas 2: citim rezervarile ────────────────────────────────────────────
    cap_out = 16;
    int nr_rez = 0;
    rezervari_out = new Rezervare[cap_out];

    bool in_rezervare = false;
    int  rez_idx      = -1;

    while (fin.getline(linie, 256)) {
        // curatam \r (fisiere Windows)
        int len = (int)std::strlen(linie);
        if (len > 0 && linie[len - 1] == '\r') linie[--len] = '\0';

        if (linie[0] == '#') continue;

        // linie goala sau "---" => incheie biletele rezervarii curente
        if (linie[0] == '\0' || std::strcmp(linie, "---") == 0) {
            in_rezervare = false;
            continue;
        }

        if (!in_rezervare) {
            // linie antet rezervare: id_sala|titlu_film|data_ora
            char s_id[8], titlu[64], data[20];
            const char* p = linie;
            p = parseCamp(p, s_id,  8);
            p = parseCamp(p, titlu, 64);
            p = parseCamp(p, data,  20);

            int id_sala = std::atoi(s_id);

            // gasim sala si filmul
            Sala*  sala_ptr  = nullptr;
            Film*  film_ptr  = nullptr;
            for (int i = 0; i < nr_sali;  i++)
                if (sali_disp[i].getIdSala() == id_sala) { sala_ptr = &sali_disp[i]; break; }
            for (int i = 0; i < nr_filme; i++)
                if (std::strcmp(filme_disp[i].getTitlu(), titlu) == 0) { film_ptr = &filme_disp[i]; break; }

            if (!sala_ptr || !film_ptr) {
                std::cout << "[ATENTIE] Sala " << id_sala
                          << " sau film '" << titlu << "' negasite. Linie ignorata.\n";
                continue;
            }

            // extinde vectorul daca e nevoie
            if (nr_rez == cap_out) {
                cap_out *= 2;
                Rezervare* nou = new Rezervare[cap_out];
                for (int i = 0; i < nr_rez; i++) nou[i] = rezervari_out[i];
                delete[] rezervari_out;
                rezervari_out = nou;
            }

            rezervari_out[nr_rez] = Rezervare(*film_ptr, *sala_ptr, data);
            rez_idx      = nr_rez;
            nr_rez++;
            in_rezervare = true;
        } else {
            // linie bilet: nr_loc|tip|pret_baza
            char s_loc[8], tip[16], s_pret[12];
            const char* p = linie;
            p = parseCamp(p, s_loc,  8);
            p = parseCamp(p, tip,   16);
            p = parseCamp(p, s_pret, 12);

            rezervari_out[rez_idx].adaugaBilet(
                std::atoi(s_loc),
                tip,
                (float)std::atof(s_pret)
            );
        }
    }

    fin.close();
    std::cout << "[OK] Incarcate " << nr_rez << " rezervari din '" << cale << "'.\n";
    return nr_rez;
}

// ─── functii globale de analiza ──────────────────────────────────────────────

void cautaFilmeRatingMinim(const Rezervare* rezervari, int nr, float min) {
    std::cout << "\n-- Filme cu rating >= " << min << " --\n";
    bool gasit = false;
    // evitam duplicate
    const int MAX = 50;
    char afisate[MAX][64];
    int  nr_afisate = 0;

    for (int i = 0; i < nr; i++) {
        const Film& f = rezervari[i].getFilm();
        if (!f.areRatingMinim(min)) continue;
        // verificam sa nu fi afisat deja
        bool dup = false;
        for (int j = 0; j < nr_afisate; j++)
            if (std::strcmp(afisate[j], f.getTitlu()) == 0) { dup = true; break; }
        if (!dup && nr_afisate < MAX) {
            std::cout << "  " << f << "\n";
            std::strcpy(afisate[nr_afisate++], f.getTitlu());
            gasit = true;
        }
    }
    if (!gasit) std::cout << "  (niciun film gasit)\n";
}

void cautaRezervariDeGen(const Rezervare* rezervari, int nr, const char* gen) {
    std::cout << "\n-- Rezervari cu film de gen [" << gen << "] --\n";
    bool gasit = false;
    for (int i = 0; i < nr; i++) {
        if (rezervari[i].getFilm().esteDeGen(gen)) {
            std::cout << "  " << rezervari[i] << "\n";
            gasit = true;
        }
    }
    if (!gasit) std::cout << "  (nicio rezervare gasita)\n";
}

void topRezervariIncasari(const Rezervare* rezervari, int nr, int n) {
    if (nr == 0) { std::cout << "(nicio rezervare)\n"; return; }
    // copie locala pentru sortare
    Rezervare* copie = new Rezervare[nr];
    for (int i = 0; i < nr; i++) copie[i] = rezervari[i];

    // bubble sort descrescator dupa incasareTotala()
    for (int i = 0; i < nr - 1; i++)
        for (int j = 0; j < nr - i - 1; j++)
            if (copie[j].incasareTotala() < copie[j+1].incasareTotala()) {
                Rezervare tmp = copie[j];
                copie[j]     = copie[j+1];
                copie[j+1]   = tmp;
            }

    int afis = (n < nr) ? n : nr;
    std::cout << "\n====== TOP " << afis << " REZERVARI DUPA INCASARE ======\n";
    for (int i = 0; i < afis; i++)
        std::cout << "  " << (i+1) << ". " << copie[i] << "\n";

    delete[] copie;
}

float incasareTotalaGlobala(const Rezervare* rezervari, int nr) {
    float total = 0.0f;
    for (int i = 0; i < nr; i++) total += rezervari[i].incasareTotala();
    return total;
}

// afiseazaChitantaBilet - adaugat pentru meniu interactiv
void Rezervare::afiseazaChitantaBilet(int id_bilet) const {
    for (int i = 0; i < nr_bilete; i++) {
        if (bilete[i].getIdBilet() == id_bilet) {
            bilete[i].afiseazaChitanta(film.getTitlu(),
                                       sala.getIdSala(),
                                       data_ora);
            return;
        }
    }
    std::cout << "  [EROARE] Bilet #" << id_bilet
              << " negasit in aceasta rezervare.\n";
}