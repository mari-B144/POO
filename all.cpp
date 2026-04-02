#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

// ═══════════════════════════════════════════════════════════════
//  CLASA FILM
// ═══════════════════════════════════════════════════════════════

class Film {
private:
    char*  titlu;
    char*  gen;
    int    durata;
    float  rating;
    int    an_aparitie;

    static int contor;

public:
    Film();//constructor default
    Film(const char* titlu, const char* gen, int durata, float rating, int an);
    Film(const Film& f);//constr de copiere
    ~Film();//destructor

    Film& operator=(const Film& f);
    friend std::ostream& operator<<(std::ostream& out, const Film& f);

    const char* getTitlu()      const { return titlu; }
    const char* getGen()        const { return gen; }
    int         getDurata()     const { return durata; }
    float       getRating()     const { return rating; }
    int         getAnAparitie() const { return an_aparitie; }

    static int getContor() { return contor; }
};

int Film::contor = 0;//var statica, comuna tuturor ob

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
    durata      = (dur > 0) ? dur : 90;
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

// ═══════════════════════════════════════════════════════════════
//  CLASA SALA
// ═══════════════════════════════════════════════════════════════

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

    int         getIdSala()     const { return id_sala; }
    const char* getNume()       const { return nume; }
    int         getCapacitate() const { return capacitate; }
    const char* getTipSala()    const { return tip_sala; }

    bool  ocupaLoc(int idx);
    bool  elibereazaLoc(int idx);
    bool  esteDisponibil(int idx) const;
    int   locuriDisponibile()     const;
    void  afiseazaHartaLocuri()   const;
    float procentOcupare()        const;

    static int getContor() { return contor; }
};

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

// ═══════════════════════════════════════════════════════════════
//  CLASA BILET
// ═══════════════════════════════════════════════════════════════

class Bilet {
private:
    int   id_bilet;
    int   nr_loc;
    char* tip_bilet;
    float pret_baza;

    static int contor;
    static int urmatorul_id;

    float procentReducere() const;

public:
    Bilet();
    Bilet(int nr_loc, const char* tip, float pret_baza);
    Bilet(const Bilet& b);
    ~Bilet();

    Bilet& operator=(const Bilet& b);
    friend std::ostream& operator<<(std::ostream& out, const Bilet& b);

    int         getIdBilet()  const { return id_bilet; }
    int         getNrLoc()    const { return nr_loc; }
    const char* getTipBilet() const { return tip_bilet; }
    float       getPretBaza() const { return pret_baza; }

    float pretFinal()  const;
    void  afiseazaChitanta(const char* titlu_film,
                           int id_sala,
                           const char* data) const;

    static int getContor()      { return contor; }
    static int getUrmatorulId() { return urmatorul_id; }
};

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
    id_bilet  = urmatorul_id++;
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
        << "  Pret baza:" << b.pret_baza << " RON"
        << "  => Final:" << b.pretFinal() << " RON";
    if (b.procentReducere() > 0.0f)
        out << " (-" << b.procentReducere() * 100 << "%)";
    return out;
}

float Bilet::pretFinal() const {
    return pret_baza * (1.0f - procentReducere());
}

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
    if (procentReducere() > 0.0f)
        std::cout << "  | Reduc. : -" << pret_baza * procentReducere()
                  << " RON (" << procentReducere() * 100 << "%)\n";
    std::cout << "  +--------------------------------------+\n";
    std::cout << "  | TOTAL  : " << pretFinal() << " RON\n";
    std::cout << "  +--------------------------------------+\n";
}

// ═══════════════════════════════════════════════════════════════
//  CLASA REZERVARE
// ═══════════════════════════════════════════════════════════════

class Rezervare {
private:
    int    id_rezervare;
    Film   film;
    Sala   sala;
    char*  data_ora;

    Bilet* bilete;
    int    nr_bilete;
    int    cap_bilete;

    static int contor;
    static int urmatorul_id;

    void extindBilete();

public:
    Rezervare();
    Rezervare(const Film& film, const Sala& sala, const char* data_ora);
    Rezervare(const Rezervare& r);
    ~Rezervare();

    Rezervare& operator=(const Rezervare& r);
    friend std::ostream& operator<<(std::ostream& out, const Rezervare& r);

    const Film& getFilm()     const { return film; }
    const Sala& getSala()     const { return sala; }
    const char* getDataOra()  const { return data_ora; }
    int         getNrBilete() const { return nr_bilete; }

    bool  adaugaBilet(int nr_loc, const char* tip, float pret_baza);
    bool  anuleazaBilet(int id_bilet);
    float incasareTotala() const;
    void  incasarePerTip(float& adult, float& copil,
                         float& senior, float& student) const;
    bool  areLocuriDisponibile() const;
    void  afiseazaRaport()       const;
    void  afiseazaHartaSala()    const { sala.afiseazaHartaLocuri(); }
    void  afiseazaChitantaBilet(int id_bilet) const;

    static int incarcaDinFisier(const char* cale,
                                Rezervare*& rezervari_out,
                                int& cap_out);

    static int getContor()      { return contor; }
    static int getUrmatorulId() { return urmatorul_id; }
};

int Rezervare::contor       = 0;
int Rezervare::urmatorul_id = 1;

void Rezervare::extindBilete() {
    cap_bilete *= 2;
    Bilet* nou = new Bilet[cap_bilete];
    for (int i = 0; i < nr_bilete; i++) nou[i] = bilete[i];
    delete[] bilete;
    bilete = nou;
}

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

static const char* parseCamp(const char* ptr, char* buf, int maxlen) {
    int i = 0;
    while (*ptr && *ptr != '|' && *ptr != '\n' && *ptr != '\r' && i < maxlen - 1)
        buf[i++] = *ptr++;
    buf[i] = '\0';
    if (*ptr == '|') ptr++;
    return ptr;
}

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
            char s_id[8], titlu[64], data[20];
            const char* p = linie;
            p = parseCamp(p, s_id,  8);
            p = parseCamp(p, titlu, 64);
            p = parseCamp(p, data,  20);

            int id_sala  = std::atoi(s_id);
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

// ═══════════════════════════════════════════════════════════════
//  MENIU SI MAIN
// ═══════════════════════════════════════════════════════════════

static void linie(char c = '-', int n = 52) {
    for (int i = 0; i < n; i++) std::cout << c;
    std::cout << "\n";
}

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
}

static int citesteInt(const char* prompt) {
    int val;
    std::cout << prompt;
    while (!(std::cin >> val)) {
        clearInput();
        std::cout << "  [!] Introduceti un numar intreg: ";
    }
    clearInput();
    return val;
}

static float citesteFloat(const char* prompt) {
    float val;
    std::cout << prompt;
    while (!(std::cin >> val)) {
        clearInput();
        std::cout << "  [!] Introduceti un numar real: ";
    }
    clearInput();
    return val;
}

static void citesteStr(const char* prompt, char* buf, int maxlen) {
    std::cout << prompt;
    std::cin.getline(buf, maxlen);
    if (!std::cin.good()) { clearInput(); buf[0] = '\0'; }
}

static void listeazaRezervari(const Rezervare* rez, int nr) {
    if (nr == 0) { std::cout << "  (nu exista rezervari incarcate)\n"; return; }
    for (int i = 0; i < nr; i++)
        std::cout << "  [" << i << "] " << rez[i] << "\n";
}

static int citesteIndex(const Rezervare* rez, int nr) {
    if (nr == 0) { std::cout << "  (nicio rezervare disponibila)\n"; return -1; }
    listeazaRezervari(rez, nr);
    int idx = citesteInt("  Selectati indexul rezervarii: ");
    if (idx < 0 || idx >= nr) {
        std::cout << "  [!] Index invalid. Trebuie intre 0 si " << nr - 1 << ".\n";
        return -1;
    }
    return idx;
}

static void afiseazaMeniu() {
    std::cout << "\n";
    linie('=');
    std::cout << "       MENIU  -  Cinematograf Bucuresti\n";
    linie('=');
    std::cout << "   1  Afisare toate rezervarile\n";
    std::cout << "   2  Harta locuri sala\n";
    std::cout << "   3  Vanzare bilet manual\n";
    std::cout << "   4  Anulare bilet\n";
    std::cout << "   5  Incasari per tip bilet\n";
    std::cout << "   6  Incasare totala globala\n";
    std::cout << "   7  Afisare chitanta bilet\n";
    std::cout << "   0  Iesire\n";
    linie('-');
    std::cout << "  Alegeti optiunea: ";
}

int main() {
    linie('*');
    std::cout << "       CINEMATOGRAF BUCURESTI\n";
    linie('*');
    std::cout << "\n  Incarcare date din date.txt ...\n\n";

    Rezervare* rezervari = 0;
    int cap_rez = 0;
    int nr_rez  = Rezervare::incarcaDinFisier("date.txt", rezervari, cap_rez);

    std::cout << "\n  " << nr_rez << " rezervari incarcate cu succes.\n";

    int optiune = -1;

    while (true) {
        afiseazaMeniu();
        std::cin >> optiune;
        clearInput();
        std::cout << "\n";

        switch (optiune) {
        case 0: {
            std::cout << "  La revedere!\n";
            delete[] rezervari;
            return 0;
        }
        case 1: {
            linie();
            std::cout << "  TOATE REZERVARILE (" << nr_rez << ")\n";
            linie();
            listeazaRezervari(rezervari, nr_rez);
            break;
        }
        case 2: {
            linie();
            std::cout << "  HARTA LOCURI SALA\n";
            linie();
            int idx = citesteIndex(rezervari, nr_rez);
            if (idx >= 0) {
                std::cout << "  " << rezervari[idx].getSala() << "\n";
                rezervari[idx].afiseazaHartaSala();
            }
            break;
        }
        case 3: {
            linie();
            std::cout << "  VANZARE BILET MANUAL\n";
            linie();
            int idx = citesteIndex(rezervari, nr_rez);
            if (idx < 0) break;
            if (!rezervari[idx].areLocuriDisponibile()) {
                std::cout << "  [!] Sala este complet ocupata!\n";
                break;
            }
            rezervari[idx].afiseazaHartaSala();
            std::cout << "  Locuri disponibile: "
                      << rezervari[idx].getSala().locuriDisponibile()
                      << " / " << rezervari[idx].getSala().getCapacitate() << "\n\n";
            int loc = citesteInt("  Numarul locului dorit (1-based): ") - 1;
            char tip[16];
            citesteStr("  Tip bilet [adult / copil / senior / student]: ", tip, 16);
            float pret = citesteFloat("  Pret baza (RON): ");
            rezervari[idx].adaugaBilet(loc, tip, pret);
            break;
        }
        case 4: {
            linie();
            std::cout << "  ANULARE BILET\n";
            linie();
            int idx = citesteIndex(rezervari, nr_rez);
            if (idx < 0) break;
            if (rezervari[idx].getNrBilete() == 0) {
                std::cout << "  (niciun bilet vandut in aceasta rezervare)\n";
                break;
            }
            rezervari[idx].afiseazaRaport();
            int id_bilet = citesteInt("  ID-ul biletului de anulat: ");
            rezervari[idx].anuleazaBilet(id_bilet);
            break;
        }
        case 5: {
            linie();
            std::cout << "  INCASARI PER TIP BILET\n";
            linie();
            int idx = citesteIndex(rezervari, nr_rez);
            if (idx < 0) break;
            float a, c, s, st;
            rezervari[idx].incasarePerTip(a, c, s, st);
            std::cout << "\n  Film  : " << rezervari[idx].getFilm().getTitlu() << "\n";
            std::cout << "  Data  : " << rezervari[idx].getDataOra() << "\n";
            linie('-', 40);
            std::cout << "  Adult   (  0%) : " << a  << " RON\n";
            std::cout << "  Copil   (-30%) : " << c  << " RON\n";
            std::cout << "  Senior  (-20%) : " << s  << " RON\n";
            std::cout << "  Student (-15%) : " << st << " RON\n";
            linie('-', 40);
            std::cout << "  TOTAL          : "
                      << rezervari[idx].incasareTotala() << " RON\n";
            break;
        }
        case 6: {
            linie();
            std::cout << "  INCASARE TOTALA GLOBALA\n";
            linie();
            std::cout << "  Rezervari active : " << nr_rez << "\n";
            std::cout << "  Total incasat    : "
                      << incasareTotalaGlobala(rezervari, nr_rez) << " RON\n";
            break;
        }
        case 7: {
            linie();
            std::cout << "  AFISARE CHITANTA BILET\n";
            linie();
            int idx = citesteIndex(rezervari, nr_rez);
            if (idx < 0) break;
            if (rezervari[idx].getNrBilete() == 0) {
                std::cout << "  (niciun bilet in aceasta rezervare)\n";
                break;
            }
            rezervari[idx].afiseazaRaport();
            int id_b = citesteInt("  ID bilet pentru chitanta: ");
            rezervari[idx].afiseazaChitantaBilet(id_b);
            break;
        }
        default: {
            std::cout << "  [!] Optiune invalida. Alegeti intre 0 si 7.\n";
            break;
        }
        }
    }

    delete[] rezervari;
    return 0;
}