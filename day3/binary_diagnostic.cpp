#include <fstream>
#include <iostream>
#include <math.h>
#include <array>
#include <unordered_set>
#include <vector>

int main(int argc, char** argv) {
    std::ifstream f(argv[1]);
    std::string line;
    std::vector<std::string> lines;

    std::unordered_set<int> gamma;
    std::unordered_set<int> epsilon;
    int i = 0;
    while(getline(f, line)) {
        lines.push_back(line);
        gamma.insert(i);
        epsilon.insert(i);
        i++;
    }

    for(size_t j = 0; j<12; j++) {
        std::unordered_set<int> gamma_1;
        std::unordered_set<int> epsilon_1;
        std::unordered_set<int> gamma_0;
        std::unordered_set<int> epsilon_0;
        int gamma_count = 0;
        int epsilon_count = 0;
        for(size_t i = 0; i < lines.size(); i++) {
           if (gamma.size() > 1 && gamma.find(i) != gamma.end()) {
               if (lines[i][j] == '1') {
                   gamma_count++;
                   gamma_1.insert(i);
               } else {
                   gamma_count--;
                   gamma_0.insert(i);
               }
           }
           if (epsilon.size() > 1 && epsilon.find(i) != epsilon.end()) {
               if (lines[i][j] == '1') {
                   epsilon_count++;
                   epsilon_1.insert(i);
               } else {
                   epsilon_count--;
                   epsilon_0.insert(i);
               }
           }
        }
        if (gamma_count >= 0) {
            for(const int& x: gamma_0) gamma.erase(x);
        } else {
            for(const int& x: gamma_1) gamma.erase(x);
        }
        if (epsilon_count < 0) {
            for(const int& x: epsilon_0) epsilon.erase(x);
        } else {
            for(const int& x: epsilon_1) epsilon.erase(x);
        }
    }

    int gamma_bin = *gamma.begin();
    int epsilon_bin = *epsilon.begin();
    int gamma_val = std::stoi(lines[gamma_bin], nullptr, 2);
    int epsilon_val = std::stoi(lines[epsilon_bin], nullptr, 2);

    std::cout << gamma_val  << std::endl;
    std::cout << epsilon_val  << std::endl;
    std::cout << gamma_val * epsilon_val << std::endl;
}
