#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char** argv) {
    std::ifstream file(argv[1]);

    int days = std::stoi(argv[2]);
    std::string input;
    std::getline(file, input);
    std::vector<long> fish(9, 0);
    for(int i = 0; i<input.size(); i+=2) fish[std::atoi(&input[i])]++;

    for(size_t i = 0; i<days; i++) {
        long temp = fish[0];
        for(size_t j = 1; j<fish.size(); j++) fish[j-1] = fish[j];
        fish[6] += temp;
        fish[8] = temp;
    }
    long count = 0;
    for(size_t i = 0; i<fish.size(); i++) count += fish[i];
    std::cout << count << std::endl;
}
