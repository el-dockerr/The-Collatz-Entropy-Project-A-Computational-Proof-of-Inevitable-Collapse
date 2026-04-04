#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <fstream>
#include <iomanip>

// Konfiguration
typedef unsigned long long u64;
const int BIT_WIDTH = 64; // Wir schauen uns 64-bit an

// Hilfsfunktion: Zahl zu Binärstring
std::string toBinary(u64 n) {
    if (n == 0) return "0";
    std::string binary = std::bitset<BIT_WIDTH>(n).to_string();
    // Führende Nullen entfernen für bessere Lesbarkeit (optional, hier lassen wir sie weg für Alignment)
    size_t firstOne = binary.find('1');
    if (firstOne == std::string::npos) return "0";
    return binary.substr(firstOne);
}

// Hilfsfunktion: Binärstring mit festem Padding für die visuelle Ausrichtung
std::string toBinaryPad(u64 n, int width) {
    std::string s = std::bitset<BIT_WIDTH>(n).to_string();
    if (s.length() > width) return s.substr(s.length() - width);
    return s.substr(BIT_WIDTH - width);
}

// Analyse eines einzelnen Schrittes
void analyzeStep(u64 n, std::ofstream &csvFile) {
    if (n % 2 == 0) {
        // Gerade Zahlen sind langweilig für unsere "Monster"-Suche, aber wir loggen sie kurz
        // csvFile << n << ",EVEN," << n/2 << ",0\n"; 
        return; 
    }

    u64 n_shifted = n << 1; // Das ist 2n
    u64 result_raw = (n * 3) + 1; // Das ist 3n+1
    
    // Wie viele Divisionen durch 2 (Trailing Zeros) erlaubt das Ergebnis?
    int trailing_zeros = 0;
    if (result_raw != 0) {
        trailing_zeros = __builtin_ctzll(result_raw); // GCC/Clang intrinsic. Für MSVC: _BitScanForward64
    }
    u64 next_step = result_raw >> trailing_zeros;

    // --- VISUALISIERUNG ---
    int display_width = 20; // Breite für die Konsole anpassen je nach Zahlengröße
    if (n > 100000) display_width = 40;

    std::cout << "\n---------------------------------------------------\n";
    std::cout << "Analyse fuer n = " << n << " (Dezimal)" << "\n";
    std::cout << "---------------------------------------------------\n";
    
    // Wir simulieren die schriftliche Addition binär:
    //   00011 (n)
    // + 00110 (2n)
    // + 00001 (+1)
    
    std::cout << "   " << std::setw(display_width) << toBinaryPad(n, display_width) << " (n)\n";
    std::cout << " + " << std::setw(display_width) << toBinaryPad(n_shifted, display_width) << " (2n)\n";
    std::cout << " + " << std::setw(display_width) << toBinaryPad(1, display_width) << " (+1)\n";
    std::cout << "   " << std::string(display_width + 3, '-') << "\n";
    std::cout << " = " << std::setw(display_width) << toBinaryPad(result_raw, display_width) << " (3n+1 raw)\n";
    
    std::cout << "\n -> " << trailing_zeros << " mal durch 2 teilbar (Right Shifts).\n";
    std::cout << " -> Neues n: " << next_step << " (" << toBinary(next_step) << ")\n";

    // CSV Output: Startzahl, TrailingZeros, Bits_Before, Bits_After
    csvFile << n << "," << result_raw << "," << trailing_zeros << "," << std::bitset<64>(n).count() << "," << std::bitset<64>(result_raw).count() << "\n";
}

int main() {
    // Experiment Setup
    std::ofstream csvFile("collatz_experiment_1.csv");
    csvFile << "n,3n+1,TrailingZeros,PopCount_n,PopCount_Result\n";

    std::cout << "Starte Collatz Binär-Analyse...\n";

    // MODUS 1: Eine spezifische Trajektorie verfolgen (z.B. die 27)
    u64 start = 27;
    u64 current = start;
    
    std::cout << "Verfolge Trajektorie fuer: " << start << "\n";
    
    while (current > 1) {
        if (current % 2 != 0) {
            analyzeStep(current, csvFile);
            current = (current * 3) + 1;
        }
        current = current / 2; // Wir führen die Divisionen aus, um zum nächsten Schritt zu kommen
    }

    // MODUS 2: Massen-Scan (optional, auskommentiert)
    /*
    for (u64 i = 1; i < 100; i += 2) {
        analyzeStep(i, csvFile);
    }
    */

    csvFile.close();
    std::cout << "\nExperiment beendet. Daten in collatz_experiment_1.csv gespeichert.\n";
    return 0;
}