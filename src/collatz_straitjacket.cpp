#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <iomanip>

typedef unsigned long long u64;

// Counts trailing zeros (number of times divisible by 2)
int countTrailingZeros(u64 n) {
    if (n == 0) return 64;
    return __builtin_ctzll(n);
}

int main() {
    u64 scan_limit = 100000000; // Scan 100 million numbers
    int max_survival_steps = 0;
    u64 record_holder = 0;

    std::cout << "Searching for the 'perfect monster' (numbers that NEVER crash deep)...\n";
    std::cout << "Condition: after 3n+1, division by 2 may occur EXACTLY ONCE.\n";
    std::cout << "Scanning up to " << scan_limit << "...\n\n";
    std::cout << "Record (Steps) | Number (Start) | Trailing-Zero History\n";
    std::cout << "---------------------------------------------------------\n";

    for (u64 i = 1; i < scan_limit; i += 2) {
        u64 curr = i;
        int steps_survived = 0;
        std::vector<int> cliff_history;
        bool monster_alive = true;

        while (monster_alive) {
            // 3n + 1
            if (__builtin_mul_overflow(curr, 3, &curr)) break; // Overflow protection
            curr += 1;

            int zeros = countTrailingZeros(curr);
            cliff_history.push_back(zeros);

            // Monster check: survives only with exactly 1 trailing zero (div by 2).
            // Two or more trailing zeros (div by 4, 8, ...) means the monster dies.
            if (zeros > 1) {
                monster_alive = false;
            } else {
                steps_survived++;
curr >>= 1;
                
                // Safety break if we enter a cycle (4-2-1)
                if (curr == 1 || curr == i) monster_alive = false; 
            }
        }

        if (steps_survived > max_survival_steps) {
            max_survival_steps = steps_survived;
            record_holder = i;

            std::cout << std::setw(13) << steps_survived << " | " 
                      << std::setw(12) << i << " | ";
            
            // Trailing-zero history (1 = survived, higher = death)
            for (int z : cliff_history) {
                std::cout << z << " "; 
            }
            std::cout << "\n";
        }
    }

    std::cout << "\n---------------------------------------------------------\n";
    std::cout << "Monster hunt result:\n";
    std::cout << "Below " << scan_limit << ", no number survived longer than\n";
    std::cout << ">>> " << max_survival_steps << " steps <<<\n";
    std::cout << "without being divided by 4 or more.\n";
    
    return 0;
}