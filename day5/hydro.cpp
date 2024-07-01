#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

#define SIZE 1000

typedef std::pair<int, int> coord;

int main(int argc, char** argv) {
    std::ifstream file(argv[1]);
    std::string line;

    int *grid = new int[SIZE*SIZE]();
    int count = 0;
    while(std::getline(file, line)) {
        size_t comma = line.find(',');
        size_t white = line.find(' ');
        std::string first = line.substr(0, comma);
        std::string second = line.substr(comma+1, white);
        coord pair1{std::stoi(first), std::stoi(second)};

        size_t arrow = line.find('>');
        comma = line.find(',', arrow);
        first = line.substr(arrow+2, comma);
        second = line.substr(comma+1);
        coord pair2{std::stoi(first), std::stoi(second)};

        if (pair1.first == pair2.first) {
            int start = pair1.second < pair2.second ? pair1.second: pair2.second;
            int end = pair1.second > pair2.second ? pair1.second: pair2.second;
            for(int i = start; i<=end; i++) {
                grid[i*SIZE+pair1.first]++;
                if (grid[i*SIZE+pair1.first] == 2) count++;
            }
        } else if (pair1.second == pair2.second) {
            int start = pair1.first < pair2.first ? pair1.first: pair2.first;
            int end = pair1.first > pair2.first ? pair1.first: pair2.first;
            for(int i = start; i<=end; i++) {
                grid[pair1.second*SIZE+i]++;
                if (grid[pair1.second*SIZE+i] == 2) count++;
            }
        } else {
            int hor = pair1.first > pair2.first ? -1 : 1;
            int ver = pair1.second > pair2.second ? -1 : 1;
            while(pair1.first != pair2.first) {
                grid[pair1.second*SIZE+pair1.first]++;
                if (grid[pair1.second*SIZE+pair1.first] == 2) count++;
                pair1.first += hor;
                pair1.second += ver;
            }
            grid[pair1.second*SIZE+pair1.first]++;
            if (grid[pair1.second*SIZE+pair1.first] == 2) count++;
        }
    }
    /*for(int i = 0; i<SIZE; i++) {
        for(int j = 0; j<SIZE; j++) {
            std::cout << grid[i*SIZE+j] << " ";
        }
        std::cout << std::endl;
    }*/

    //std::cout << std::endl;
    std::cout << count << std::endl;
}
