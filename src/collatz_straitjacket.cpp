#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <iomanip>

typedef unsigned long long u64;

// Zählt Trailing Zeros (Wie oft durch 2 teilbar?)
int countTrailingZeros(u64 n) {
    if (n == 0) return 64;
    return __builtin_ctzll(n);
}

int main() {
    u64 scan_limit = 100000000; // Wir scannen 100 Millionen Zahlen
    int max_survival_steps = 0;
    u64 record_holder = 0;

    std::cout << "Suche nach dem 'Perfekten Monster' (Zahlen, die NIE tief abstuerzen)...\n";
    std::cout << "Bedingung: Nach 3n+1 darf NUR EINMAL durch 2 geteilt werden.\n";
    std::cout << "Wir scannen bis " << scan_limit << "...\n\n";
    std::cout << "Rekord (Steps) | Zahl (Start) | Verlauf der Trailing Zeros\n";
    std::cout << "---------------------------------------------------------\n";

    for (u64 i = 1; i < scan_limit; i += 2) {
        u64 curr = i;
        int steps_survived = 0;
        std::vector<int> cliff_history;
        bool monster_alive = true;

        // Wir simulieren den "Monster-Lauf"
        while (monster_alive) {
            // 3n + 1
            if (__builtin_mul_overflow(curr, 3, &curr)) break; // Overflow Schutz
            curr += 1;

            int zeros = countTrailingZeros(curr);
            cliff_history.push_back(zeros);

            // MONSTER-CHECK:
            // Ein echtes Monster darf hier NICHT abstürzen.
            // Es darf nur genau 1 Trailing Zero haben (div durch 2).
            // Wenn es 2 oder mehr hat (div durch 4, 8...), stirbt das Monster.
            if (zeros > 1) {
                monster_alive = false;
            } else {
                steps_survived++;
                // Division durch 2 für den nächsten Schritt (wir wissen ja, es ist genau 1 Zero)
                curr >>= 1; 
                
                // Sicherheits-Break falls wir in einen Loop geraten (4-2-1)
                if (curr == 1 || curr == i) monster_alive = false; 
            }
        }

        // Haben wir einen neuen Rekord?
        if (steps_survived > max_survival_steps) {
            max_survival_steps = steps_survived;
            record_holder = i;

            std::cout << std::setw(13) << steps_survived << " | " 
                      << std::setw(12) << i << " | ";
            
            // Zeige die Geschichte (die Einsen sind das Überleben, die letzte Zahl ist der Tod)
            for (int z : cliff_history) {
                std::cout << z << " "; 
            }
            std::cout << "\n";
        }
    }

    std::cout << "\n---------------------------------------------------------\n";
    std::cout << "Ergebnis der Monster-Jagd:\n";
    std::cout << "Unter " << scan_limit << " Zahlen konnte KEINE laenger als\n";
    std::cout << ">>> " << max_survival_steps << " Schritte <<<\n";
    std::cout << "ueberleben, ohne durch 4 oder mehr geteilt zu werden.\n";
    
    return 0;
}