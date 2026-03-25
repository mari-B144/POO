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
 * Operatii posibile:
 *   1. Verificare disponibilitate locuri in sala inainte de
 *      vanzare bilet (eroare daca locul e ocupat/invalid)
 *   2. Calculare pret total cu reduceri per categorie:
 *        copil -30% | senior -20% | student -15% | adult 0%
 *   3. Raport incasari per film / per rezervare / global
 *   4. Cautare rezervari dupa gen film
 *   5. Cautare filme dupa rating minim
 *   6. Top N rezervari dupa incasare totala
 *   7. Afisare harta vizuala a locurilor dintr-o sala
 *   8. Anulare bilet cu eliberarea automata a locului
 *   9. Afisare chitanta individuala
 *
 * CLASE DEFINITE:
 *   Film      : titlu, gen, durata, rating, an_aparitie
 *   Sala      : id, capacitate, locuri[] (bool, dinamic), tip
 *   Bilet     : loc, tip, pret_baza, reducere automata
 *   Rezervare : Film + Sala + vector<Bilet> + data_ora
 *               (leaga toate clasele, gestioneaza logica)
 *
 * Toate clasele: constructor cu parametri, constructor de
 * copiere, operator=, destructor, operator<<, contor static,
 * atribute private, getteri/setteri, metode private. Fara STL.
 * ============================================================
 */

#include <iostream>
#include "Film.h"
#include "Sala.h"
#include "Bilet.h"
#include "Rezervare.h"

int main() {

    std::cout << "╔══════════════════════════════════════════════╗\n";
    std::cout << "║     SISTEM MANAGEMENT CINEMATOGRAF           ║\n";
    std::cout << "╚══════════════════════════════════════════════╝\n\n";

    // ── 1. Demonstrare clase individuale ───────────────────────────────────
    std::cout << ">>> [1] Demonstrare clase individuale\n\n";

    // Film: constructor cu parametri + constructor de copiere + operator=
    Film f1("Gladiator II", "Actiune", 148, 7.5f, 2024);
    Film f2(f1);                        // constructor de copiere
    f2.setTitlu("Gladiator II (copie)");
    Film f3;
    f3 = f1;                            // operator=
    f3.setRating(8.0f);

    std::cout << f1 << "\n";
    std::cout << f2 << "\n";
    std::cout << f3 << "\n\n";

    // Sala: constructor cu parametri + operator=
    Sala s1(5, "Sala VIP", 12, "IMAX");
    Sala s2(s1);                        // constructor de copiere
    s2.setNume("Sala VIP (copie)");
    s1.ocupaLoc(0); s1.ocupaLoc(2); s1.ocupaLoc(5);

    std::cout << s1 << "\n";
    std::cout << s2 << "\n\n";

    // Bilet: toate tipurile + afisare chitanta
    Bilet b_adult  (0,  "adult",   45.0f);
    Bilet b_copil  (1,  "copil",   45.0f);
    Bilet b_senior (2,  "senior",  45.0f);
    Bilet b_student(3,  "student", 45.0f);
    Bilet b_copiat (b_adult);           // constructor de copiere

    std::cout << b_adult   << "\n";
    std::cout << b_copil   << "\n";
    std::cout << b_senior  << "\n";
    std::cout << b_student << "\n";
    std::cout << b_copiat  << "\n\n";

    // Chitanta pentru biletul senior
    b_senior.afiseazaChitanta("Gladiator II", 5, "28/03/2025 20:00");

    // Rezervare manuala
    Rezervare rez1(f1, s1, "28/03/2025 20:00");
    std::cout << "\n" << rez1 << "\n\n";

    // ── 2. Contoare statice ─────────────────────────────────────────────────
    std::cout << ">>> [2] Contoare statice\n";
    std::cout << "  Film::contor      = " << Film::getContor()       << "\n";
    std::cout << "  Sala::contor      = " << Sala::getContor()       << "\n";
    std::cout << "  Bilet::contor     = " << Bilet::getContor()      << "\n";
    std::cout << "  Rezervare::contor = " << Rezervare::getContor()  << "\n\n";

    // ── 3. Incarcare automata din date.txt ──────────────────────────────────
    std::cout << ">>> [3] Incarcare date din date.txt\n";
    Rezervare* rezervari = nullptr;
    int cap_rez = 0;
    int nr_rez  = Rezervare::incarcaDinFisier("date.txt", rezervari, cap_rez);
    std::cout << "\n";

    // ── 4. Afisare sumara a tuturor rezervarilor incarcate ──────────────────
    std::cout << ">>> [4] Rezervari incarcate (" << nr_rez << " total)\n";
    for (int i = 0; i < nr_rez; i++)
        std::cout << "  " << rezervari[i] << "\n";
    std::cout << "\n";

    // ── 5. Raport detaliat per rezervare ────────────────────────────────────
    std::cout << ">>> [5] Raport detaliat rezervare #1 (Inception)\n";
    rezervari[0].afiseazaRaport();

    std::cout << "\n>>> [5b] Raport detaliat rezervare #3 (Oppenheimer)\n";
    rezervari[2].afiseazaRaport();

    // ── 6. Harta locuri ─────────────────────────────────────────────────────
    std::cout << "\n>>> [6] Harta locuri sala rezervare Oppenheimer\n";
    rezervari[2].afiseazaHartaSala();

    // ── 7. Vanzare bilet manual cu verificare disponibilitate ──────────────
    std::cout << ">>> [7] Vanzare bilete manuale (cazuri limita)\n";

    // caz normal - loc liber
    rezervari[0].adaugaBilet(10, "adult", 35.0f);

    // eroare - loc deja ocupat (locul 0 a fost vandut din fisier)
    rezervari[0].adaugaBilet(0,  "adult", 35.0f);

    // loc invalid (depaseste capacitatea salii)
    rezervari[0].adaugaBilet(999, "adult", 35.0f);
    std::cout << "\n";

    // ── 8. Anulare bilet ────────────────────────────────────────────────────
    std::cout << ">>> [8] Anulare bilet\n";
    // anulam un bilet existent (ID cunoscut din run - al 13-lea bilet emis)
    rezervari[3].anuleazaBilet(13);   // bilet Interstellar, loc 5
    rezervari[3].anuleazaBilet(9999); // ID inexistent => eroare
    std::cout << "\n";

    // ── 9. Calcul pret cu reduceri ──────────────────────────────────────────
    std::cout << ">>> [9] Calcul preturi cu reduceri (rezervare Inception)\n";
    float a, c, s, st;
    rezervari[0].incasarePerTip(a, c, s, st);
    std::cout << "  Adult  : " << a  << " RON\n";
    std::cout << "  Copil  : " << c  << " RON  (-30%)\n";
    std::cout << "  Senior : " << s  << " RON  (-20%)\n";
    std::cout << "  Student: " << st << " RON  (-15%)\n";
    std::cout << "  TOTAL  : " << rezervari[0].incasareTotala() << " RON\n\n";

    // ── 10. Cautare filme dupa rating minim ─────────────────────────────────
    std::cout << ">>> [10] Cautare filme cu rating >= 8.5\n";
    cautaFilmeRatingMinim(rezervari, nr_rez, 8.5f);

    std::cout << "\n>>> [10b] Cautare filme cu rating >= 9.0\n";
    cautaFilmeRatingMinim(rezervari, nr_rez, 9.0f);

    // ── 11. Cautare rezervari dupa gen ──────────────────────────────────────
    std::cout << "\n>>> [11] Cautare rezervari gen Sci-Fi\n";
    cautaRezervariDeGen(rezervari, nr_rez, "Sci-Fi");

    std::cout << "\n>>> [11b] Cautare rezervari gen Horror (inexistent)\n";
    cautaRezervariDeGen(rezervari, nr_rez, "Horror");

    // ── 12. Top rezervari dupa incasare ─────────────────────────────────────
    std::cout << "\n>>> [12] Top 3 rezervari dupa incasare\n";
    topRezervariIncasari(rezervari, nr_rez, 3);

    // ── 13. Incasare globala ─────────────────────────────────────────────────
    std::cout << "\n>>> [13] Incasare totala globala\n";
    std::cout << "  Total incasat de cinematograf: "
              << incasareTotalaGlobala(rezervari, nr_rez) << " RON\n\n";

    // ── 14. Test operator= Rezervare ────────────────────────────────────────
    std::cout << ">>> [14] Test operator= Rezervare\n";
    Rezervare rez_copie = rezervari[2];   // operator=
    std::cout << "  Original: " << rezervari[2]  << "\n";
    std::cout << "  Copie   : " << rez_copie      << "\n\n";

    // ── cleanup ──────────────────────────────────────────────────────────────
    delete[] rezervari;

    std::cout << "╔══════════════════════════════════════════════╗\n";
    std::cout << "║        PROGRAM INCHEIAT CU SUCCES            ║\n";
    std::cout << "╚══════════════════════════════════════════════╝\n";

    return 0;
}