/*
 * ============================================================
 * PROIECT POO  -  Sistem de Management Cinematograf
 * ============================================================
 *
 * DESCRIEREA PROBLEMEI:
 * ─────────────────────
 * Se modeleaza sistemul informatic al unui cinematograf care
 * gestioneaza filme, sali de proiectie, rezervari si bilete.
 *
 * Date de intrare (un singur fisier: date.txt):
 *   Sectiunea [FILME]     : titlu|gen|durata|rating|an
 *   Sectiunea [SALI]      : id|nume|capacitate|tip
 *   Sectiunea [REZERVARI] : antet (sala + film + data) urmat de
 *                           linii de bilete (loc|tip|pret_baza),
 *                           rezervarile sunt separate prin "---"
 *
 * Operatii posibile (meniu interactiv):
 *   1.  Afisare toate rezervarile
 *   2.  Raport detaliat rezervare
 *   3.  Harta locuri sala
 *   4.  Vanzare bilet manual
 *   5.  Anulare bilet
 *   6.  Incasari per tip bilet
 *   7.  Cautare rezervari dupa gen film
 *   8.  Cautare filme cu rating minim
 *   9.  Top N rezervari dupa incasare
 *   10. Incasare totala globala
 *   11. Afisare chitanta bilet
 *   0.  Iesire
 *
 * CLASE DEFINITE:
 *   Film      : titlu, gen, durata, rating, an_aparitie
 *   Sala      : id, capacitate, locuri[] (bool, dinamic), tip
 *   Bilet     : loc, tip, pret_baza, reducere automata
 *   Rezervare : Film + Sala + vector<Bilet> + data_ora
 *
 * Toate clasele: constructor cu parametri, constructor de
 * copiere, operator=, destructor, operator<<, contor static,
 * atribute private, getteri/setteri, metode private. Fara STL.
 * ============================================================
 */

#include <iostream>
#include <limits>
#include "Film.h"
#include "Sala.h"
#include "Bilet.h"
#include "Rezervare.h"

// ─── utilitare I/O ────────────────────────────────────────────────────────────

static void linie(char c = '-', int n = 52) {
    for (int i = 0; i < n; i++) std::cout << c;
    std::cout << "\n";
}

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

// ─── afisare lista rezervari (cu index) ──────────────────────────────────────

static void listeazaRezervari(const Rezervare* rez, int nr) {
    if (nr == 0) {
        std::cout << "  (nu exista rezervari incarcate)\n";
        return;
    }
    for (int i = 0; i < nr; i++)
        std::cout << "  [" << i << "] " << rez[i] << "\n";
}

// cere un index valid; returneaza -1 daca e invalid
static int citesteIndex(int nr) {
    if (nr == 0) { std::cout << "  (nicio rezervare disponibila)\n"; return -1; }
    listeazaRezervari(nullptr, 0); // nu afisam nimic, doar prompt
    int idx = citesteInt("  Selectati indexul rezervarii: ");
    if (idx < 0 || idx >= nr) {
        std::cout << "  [!] Index invalid. Trebuie intre 0 si " << nr - 1 << ".\n";
        return -1;
    }
    return idx;
}

// ─── meniu ───────────────────────────────────────────────────────────────────

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

// ─── main ────────────────────────────────────────────────────────────────────

int main() {

    linie('*');
    std::cout << "   SISTEM MANAGEMENT CINEMATOGRAF  -  v1.0\n";
    linie('*');
    std::cout << "\n  Incarcare date din date.txt ...\n\n";

    Rezervare* rezervari = nullptr;
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

        // ── 0. Iesire ────────────────────────────────────────────────────────
        case 0: {
            std::cout << "  La revedere!\n";
            delete[] rezervari;
            return 0;
        }

        // ── 1. Afisare toate rezervarile ─────────────────────────────────────
        case 1: {
            linie();
            std::cout << "  TOATE REZERVARILE (" << nr_rez << ")\n";
            linie();
            listeazaRezervari(rezervari, nr_rez);
            break;
        }


        // ── 2. Harta locuri ───────────────────────────────────────────────────
        case 2: {
            linie();
            std::cout << "  HARTA LOCURI SALA\n";
            linie();
            listeazaRezervari(rezervari, nr_rez);
            int idx = citesteIndex(nr_rez);
            if (idx >= 0) {
                std::cout << "  " << rezervari[idx].getSala() << "\n";
                rezervari[idx].afiseazaHartaSala();
            }
            break;
        }

        // ── 3. Vanzare bilet manual ───────────────────────────────────────────
        case 3: {
            linie();
            std::cout << "  VANZARE BILET MANUAL\n";
            linie();
            listeazaRezervari(rezervari, nr_rez);
            int idx = citesteIndex(nr_rez);
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

        // ── 4. Anulare bilet ──────────────────────────────────────────────────
        case 4: {
            linie();
            std::cout << "  ANULARE BILET\n";
            linie();
            listeazaRezervari(rezervari, nr_rez);
            int idx = citesteIndex(nr_rez);
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

        // ── 5. Incasari per tip bilet ─────────────────────────────────────────
        case 5: {
            linie();
            std::cout << "  INCASARI PER TIP BILET\n";
            linie();
            listeazaRezervari(rezervari, nr_rez);
            int idx = citesteIndex(nr_rez);
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

        // ── 6. Incasare totala globala ───────────────────────────────────────
        case 6: {
            linie();
            std::cout << "  INCASARE TOTALA GLOBALA\n";
            linie();
            float total = incasareTotalaGlobala(rezervari, nr_rez);
            std::cout << "  Rezervari active : " << nr_rez << "\n";
            std::cout << "  Total incasat    : " << total << " RON\n";
            break;
        }

        // ── 7. Chitanta bilet ────────────────────────────────────────────────
        case 7: {
            linie();
            std::cout << "  AFISARE CHITANTA BILET\n";
            linie();
            listeazaRezervari(rezervari, nr_rez);
            int idx = citesteIndex(nr_rez);
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
            std::cout << "  [!] Optiune invalida. Alegeti intre 0 si 11.\n";
            break;
        }

        } 

    } 

    delete[] rezervari;
    return 0;
}