#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <numeric>

typedef unsigned long long u64;

int main() {
    u64 scan_count = 1000000; // Wir scannen eine Million Zahlen
    
    double total_log_growth = 0.0;
    double total_log_shrink = 0.0;
    
    u64 total_odd_steps = 0;
    u64 total_divisions = 0;

    std::cout << "--- PAPER 2: DIGITALE SCHWERKRAFT ---\n";
    std::cout << "Wir messen den Kampf: log2(3) Wachstum vs. Divisionen.\n";
    std::cout << "Theoretisches Limit: Wir brauchen > 1.585 Divisionen pro Schritt, um zu schrumpfen.\n\n";

    for (u64 i = 3; i < scan_count; i += 2) { // Nur ungerade Startzahlen
        u64 curr = i;
        
        // Wir simulieren, bis die Zahl kleiner als der Startwert ist 
        // (denn ab da wissen wir per Induktion, dass sie zu 1 geht)
        while (curr >= i) {
            // Schritt 1: 3n + 1
            // Wir messen nur das Wachstum durch die 3 (die +1 ist Rauschen bei großen Zahlen)
            total_odd_steps++;
            
            // Check auf Overflow
            if (__builtin_mul_overflow(curr, 3, &curr)) {
                // Bei Overflow brechen wir diesen Lauf ab, um die Statistik nicht zu verfälschen
                curr = 1; 
                break; 
            }
            curr += 1;

            // Schritt 2: Divisionen zählen
            int divs = 0;
            while ((curr & 1) == 0) {
                curr >>= 1;
                divs++;
            }
            total_divisions += divs;
        }
    }

    // Auswertung
    double avg_divisions_per_odd = (double)total_divisions / total_odd_steps;
    double log3 = std::log2(3.0); // ca. 1.58496

    std::cout << "Analyse beendet fuer " << scan_count << " Zahlen.\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "Total Odd Steps (x3):   " << total_odd_steps << "\n";
    std::cout << "Total Divisions (/2):   " << total_divisions << "\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "Genoetigte Divisionen fuer Stillstand (log2(3)): " << log3 << "\n";
    std::cout << "Gemessene Divisionen pro Schritt (Durchschnitt): " << avg_divisions_per_odd << "\n";
    std::cout << "--------------------------------------------------\n";
    
    double drift = log3 - avg_divisions_per_odd;
    std::cout << "NETTO DRIFT (Bits pro Schritt): " << drift << "\n";
    
    if (drift < 0) {
        std::cout << "\n>>> ERGEBNIS: SCHWERKRAFT BESTAETIGT <<<\n";
        std::cout << "Die Zahlen verlieren schneller an Hoehe, als sie gewinnen koennen.\n";
        std::cout << "Das System ist dissipativ (energieverzehrend).\n";
    } else {
        std::cout << "\n>>> WARNUNG: Das Monster lebt noch! <<<\n";
    }

    return 0;
}