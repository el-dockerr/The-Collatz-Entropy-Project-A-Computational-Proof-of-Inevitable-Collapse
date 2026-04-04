#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <iomanip>
#include <fstream>

typedef unsigned long long u64;

// Returns the last 'width' bits as a string
std::string getSuffix(u64 n, int width) {
    std::string s = "";
    for (int i = 0; i < width; ++i) {
        s = ((n >> (width - 1 - i)) & 1 ? "1" : "0") + s;
    }
    std::string full = std::bitset<64>(n).to_string();
    return full.substr(64 - width);
}

// Counts trailing ones (the cliff height)
int countTrailingOnes(u64 n) {
    int count = 0;
    while ((n & 1) == 1) {
        count++;
        n >>= 1;
    }
    return count;
}

int main() {
    u64 start_num = 27;
    u64 max_scan = 100000;
    
    std::ofstream csv("collatz_cliffs.csv");
    csv << "n_odd,3n_binary_suffix,Cliff_Height(TrailingOnes),Next_Drop(Divisor)\n";

    std::cout << "--- PART 1: Autopsy of number " << start_num << " ---\n";
    std::cout << "Inspecting 3n (before +1 is applied).\n";
    std::cout << "Watch the trailing ones!\n\n";
    
    std::cout << "Step | n (odd)     | 3n (decimal) | ...Suffix (last 8) | Cliff (Ones)  | Drop (2^k)\n";
    std::cout << "----------------------------------------------------------------------------------\n";

    u64 curr = start_num;
    int steps = 0;
    
    // Map: frequency of each cliff height
    std::map<int, int> cliff_stats;

    while (curr > 1 && steps < 1000) { // Limit to avoid infinite loops on overflow
        if (curr % 2 != 0) {
            u64 val_3n = curr * 3;
            int cliff_height = countTrailingOnes(val_3n);
            
            cliff_stats[cliff_height]++;
            
            std::cout << std::setw(4) << steps << " | " 
                      << std::setw(11) << curr << " | "
                      << std::setw(12) << val_3n << " | "
                      << "..." << getSuffix(val_3n, 8) << "       | "
                      << std::setw(13) << cliff_height << " | "
                      << "div by 2^" << cliff_height << "\n";
            
            csv << curr << "," << getSuffix(val_3n, 12) << "," << cliff_height << "," << (1 << cliff_height) << "\n";

            curr = (val_3n + 1); 
            while (curr % 2 == 0) {
                curr /= 2;
            }
        } else {
            curr /= 2;
        }
        steps++;
    }

    std::cout << "\n\n--- PART 2: Mass scan (1 to " << max_scan << ") ---\n";
    std::cout << "Checking: is the cliff height truly randomly distributed?\n";
    
    std::map<int, u64> global_stats;
    u64 total_odd_numbers = 0;

    for (u64 i = 1; i < max_scan; i += 2) {
        u64 val_3n = i * 3;
        int h = countTrailingOnes(val_3n);
        global_stats[h]++;
        total_odd_numbers++;
    }

    std::cout << "\nDistribution result:\n";
    std::cout << "Height (Ones) | Count            | Percent (Expected ~50% / 2^(k-1))\n";
    std::cout << "---------------------------------------------------------------\n";
    
    for (auto const& [height, count] : global_stats) {
        double percent = (count * 100.0) / total_odd_numbers;
        std::cout << " " << std::setw(2) << height << " Ones     | " 
                  << std::setw(14) << count << "   | " 
                  << std::fixed << std::setprecision(4) << percent << "%\n";
    }

    std::cout << "\nData saved to collatz_cliffs.csv\n";

    return 0;
}