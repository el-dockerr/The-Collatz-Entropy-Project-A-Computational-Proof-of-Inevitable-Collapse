#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <numeric>

typedef unsigned long long u64;

int main() {
    u64 scan_count = 1000000; // Scan one million numbers
    
    double total_log_growth = 0.0;
    double total_log_shrink = 0.0;
    
    u64 total_odd_steps = 0;
    u64 total_divisions = 0;

    std::cout << "--- PAPER 2: DIGITAL GRAVITY ---\n";
    std::cout << "Measuring the contest: log2(3) growth vs. divisions.\n";
    std::cout << "Theoretical threshold: > 1.585 divisions per step required to shrink.\n\n";

    for (u64 i = 3; i < scan_count; i += 2) { // Odd starting numbers only
        u64 curr = i;
        
        // Simulate until the value drops below the starting number
        while (curr >= i) {
            // Step 1: 3n + 1
            total_odd_steps++;
            
            // Overflow check
            if (__builtin_mul_overflow(curr, 3, &curr)) {
                // Abort on overflow to avoid skewing statistics
                curr = 1; 
                break; 
            }
            curr += 1;

            // Step 2: count divisions by 2
            int divs = 0;
            while ((curr & 1) == 0) {
                curr >>= 1;
                divs++;
            }
            total_divisions += divs;
        }
    }

    // Analysis
    double avg_divisions_per_odd = (double)total_divisions / total_odd_steps;
    double log3 = std::log2(3.0); // ca. 1.58496

    std::cout << "Analysis complete for " << scan_count << " numbers.\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "Total Odd Steps (x3):   " << total_odd_steps << "\n";
    std::cout << "Total Divisions (/2):   " << total_divisions << "\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "Required divisions for equilibrium (log2(3)): " << log3 << "\n";
    std::cout << "Measured divisions per step (average):        " << avg_divisions_per_odd << "\n";
    std::cout << "--------------------------------------------------\n";
    
    double drift = log3 - avg_divisions_per_odd;
    std::cout << "NET DRIFT (bits per step): " << drift << "\n";
    
    if (drift < 0) {
        std::cout << "\n>>> RESULT: GRAVITY CONFIRMED <<<\n";
        std::cout << "Numbers lose height faster than they can gain it.\n";
        std::cout << "The system is dissipative.\n";
    } else {
        std::cout << "\n>>> WARNING: The monster still lives! <<<\n";
    }

    return 0;
}