#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <iomanip>
#include <fstream>

// Typendefinition für sauberen Code
typedef unsigned long long u64;

// Funktion, um die letzten 'width' Bits als String zu bekommen
std::string getSuffix(u64 n, int width) {
    std::string s = "";
    for (int i = 0; i < width; ++i) {
        s = ((n >> (width - 1 - i)) & 1 ? "1" : "0") + s; // Achtung: Reihenfolge
    }
    // Korrektur: Wir wollen die Bits in Lesereihenfolge (MSB -> LSB)
    // Einfacher: std::bitset nutzen und abschneiden
    std::string full = std::bitset<64>(n).to_string();
    return full.substr(64 - width);
}

// Zählt, wie viele Einsen am Ende stehen (Die Klippenhöhe)
int countTrailingOnes(u64 n) {
    int count = 0;
    while ((n & 1) == 1) {
        count++;
        n >>= 1;
    }
    return count;
}

int main() {
    u64 start_num = 27; // Unsere Test-Zahl
    u64 max_scan = 100000; // Für die Statistik
    
    std::ofstream csv("collatz_cliffs.csv");
    csv << "n_odd,3n_binary_suffix,Cliff_Height(TrailingOnes),Next_Drop(Divisor)\n";

    std::cout << "--- TEIL 1: Die Autopsie der Zahl " << start_num << " ---\n";
    std::cout << "Wir betrachten 3n (bevor +1 gerechnet wird).\n";
    std::cout << "Achte auf die Einsen am Ende!\n\n";
    
    std::cout << "Step | n (odd)     | 3n (decimal) | ...Suffix (last 8) | Klippe (Ones) | Absturz (2^k)\n";
    std::cout << "----------------------------------------------------------------------------------\n";

    u64 curr = start_num;
    int steps = 0;
    
    // Karte für Statistik: Wie oft kommt welche Klippenhöhe vor?
    std::map<int, int> cliff_stats;

    while (curr > 1 && steps < 1000) { // Limit um Endlosschleifen bei Overflow zu meiden
        if (curr % 2 != 0) {
            u64 val_3n = curr * 3;
            int cliff_height = countTrailingOnes(val_3n);
            
            // Statistik speichern
            cliff_stats[cliff_height]++;
            
            // Visualisierung
            std::cout << std::setw(4) << steps << " | " 
                      << std::setw(11) << curr << " | "
                      << std::setw(12) << val_3n << " | "
                      << "..." << getSuffix(val_3n, 8) << "       | "
                      << std::setw(13) << cliff_height << " | "
                      << "div by 2^" << cliff_height << "\n";
            
            csv << curr << "," << getSuffix(val_3n, 12) << "," << cliff_height << "," << (1 << cliff_height) << "\n";

            // Collatz Schritt ausführen
            curr = (val_3n + 1); 
            // Jetzt die Divisionen durchführen, bis wieder ungerade (für den nächsten Schritt im Loop)
            while (curr % 2 == 0) {
                curr /= 2;
            }
        } else {
            // Sollte hier nicht passieren, da wir oben "while even" machen, aber sicherheitshalber:
            curr /= 2;
        }
        steps++;
    }

    std::cout << "\n\n--- TEIL 2: Massen-Scan (1 bis " << max_scan << ") ---\n";
    std::cout << "Wir pruefen: Ist die Klippenhoehe wirklich zufaellig verteilt?\n";
    
    std::map<int, u64> global_stats;
    u64 total_odd_numbers = 0;

    for (u64 i = 1; i < max_scan; i += 2) {
        u64 val_3n = i * 3;
        int h = countTrailingOnes(val_3n);
        global_stats[h]++;
        total_odd_numbers++;
    }

    std::cout << "\nErgebnis der Verteilung:\n";
    std::cout << "Hoehe (Ones) | Anzahl Vorkommen | Prozent (Sollte ~50% / 2^(k-1) sein)\n";
    std::cout << "---------------------------------------------------------------\n";
    
    for (auto const& [height, count] : global_stats) {
        double percent = (count * 100.0) / total_odd_numbers;
        std::cout << " " << std::setw(2) << height << " Ones     | " 
                  << std::setw(14) << count << "   | " 
                  << std::fixed << std::setprecision(4) << percent << "%\n";
    }

    std::cout << "\nDaten gespeichert in collatz_cliffs.csv\n";

    return 0;
}