#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <fstream>
#include <iomanip>

// Configuration
typedef unsigned long long u64;
const int BIT_WIDTH = 64;

// Helper: convert number to binary string
std::string toBinary(u64 n) {
    if (n == 0) return "0";
    std::string binary = std::bitset<BIT_WIDTH>(n).to_string();
    size_t firstOne = binary.find('1');
    if (firstOne == std::string::npos) return "0";
    return binary.substr(firstOne);
}

// Helper: binary string with fixed-width padding
std::string toBinaryPad(u64 n, int width) {
    std::string s = std::bitset<BIT_WIDTH>(n).to_string();
    if (s.length() > width) return s.substr(s.length() - width);
    return s.substr(BIT_WIDTH - width);
}

// Analyse eines einzelnen Schrittes
void analyzeStep(u64 n, std::ofstream &csvFile) {
    if (n % 2 == 0) {
        return;
    }

    u64 n_shifted = n << 1; // 2n
    u64 result_raw = (n * 3) + 1; // 3n+1
    
    // Count trailing zeros (divisions by 2)
    int trailing_zeros = 0;
    if (result_raw != 0) {
        trailing_zeros = __builtin_ctzll(result_raw); // GCC/Clang intrinsic. For MSVC: _BitScanForward64
    }
    u64 next_step = result_raw >> trailing_zeros;

    // --- VISUALIZATION ---
    int display_width = 20;
    if (n > 100000) display_width = 40;

    std::cout << "\n---------------------------------------------------\n";
    std::cout << "Analysis for n = " << n << " (decimal)" << "\n";
    std::cout << "---------------------------------------------------\n";
    
    // Binary column addition:
    //   00011 (n)
    // + 00110 (2n)
    // + 00001 (+1)
    
    std::cout << "   " << std::setw(display_width) << toBinaryPad(n, display_width) << " (n)\n";
    std::cout << " + " << std::setw(display_width) << toBinaryPad(n_shifted, display_width) << " (2n)\n";
    std::cout << " + " << std::setw(display_width) << toBinaryPad(1, display_width) << " (+1)\n";
    std::cout << "   " << std::string(display_width + 3, '-') << "\n";
    std::cout << " = " << std::setw(display_width) << toBinaryPad(result_raw, display_width) << " (3n+1 raw)\n";
    
    std::cout << "\n -> " << trailing_zeros << " times divisible by 2 (right shifts).\n";
    std::cout << " -> New n: " << next_step << " (" << toBinary(next_step) << ")\n";

    // CSV output
    csvFile << n << "," << result_raw << "," << trailing_zeros << "," << std::bitset<64>(n).count() << "," << std::bitset<64>(result_raw).count() << "\n";
}

int main() {
    // Experiment setup
    std::ofstream csvFile("collatz_experiment_1.csv");
    csvFile << "n,3n+1,TrailingZeros,PopCount_n,PopCount_Result\n";

    std::cout << "Starting Collatz binary analysis...\n";

    // Mode 1: trace a specific trajectory
    u64 start = 27;
    u64 current = start;
    
    std::cout << "Tracing trajectory for: " << start << "\n";
    
    while (current > 1) {
        if (current % 2 != 0) {
            analyzeStep(current, csvFile);
            current = (current * 3) + 1;
        }
        current = current / 2;
    }

    // Mode 2: mass scan (optional)
    /*
    for (u64 i = 1; i < 100; i += 2) {
        analyzeStep(i, csvFile);
    }
    */

    csvFile.close();
    std::cout << "\nExperiment finished. Data saved to collatz_experiment_1.csv\n";
    return 0;
}