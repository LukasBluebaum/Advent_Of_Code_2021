#include <iostream>
#include <fstream>
#include <vector>

#define SIZE 10
#define STEPS 1000


int propagateFlash(int (&matrix)[SIZE][SIZE], int x, int y, bool (&flashed)[SIZE][SIZE]) {
    if(x < 0 || y < 0 || x >= SIZE || y >= SIZE || flashed[x][y]) return 0;
    matrix[x][y]++;
    if(matrix[x][y] > 9) {
        matrix[x][y] = 0;
        flashed[x][y] = true;
        int flashes = 1;
        for(auto i = -1; i<=1; i++) {
            for(auto j = -1; j<=1; j++) {
                flashes += propagateFlash(matrix, x + i, y + j, flashed);
            }
        }
        return flashes;
    }
    return 0;
}

void printMatrix(int (&matrix)[SIZE][SIZE]) {
    for(auto i = 0; i<SIZE; i++) {
        for(auto j = 0; j<SIZE; j++) {
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    std::ifstream file(argv[1]);
    std::string line;
    int matrix[SIZE][SIZE];
    int i = 0;
    while(std::getline(file, line)) {
        for(auto j = 0; j<line.size(); j++) matrix[i][j] = line[j] - '0';
        i++;
    }

    int flashes = 0;
    int all_flash = -1;
    for(auto step = 0; step < STEPS; step++) {
        for(auto i = 0; i< SIZE; i++) {
            for(auto j = 0; j< SIZE; j++) {
                matrix[i][j]++;
            }
        }
        bool flashed[SIZE][SIZE] = {{false}};
        for(int i = 0; i< SIZE; i++) {
            for(int j = 0; j< SIZE; j++) {
                auto current = matrix[i][j];
                if (current > 9) {
                    int temp = propagateFlash(matrix, i, j, flashed);
                    flashes += temp;
                    if (temp == SIZE*SIZE && all_flash == -1) all_flash = step + 1;
                }
            }
        }
    }
    printMatrix(matrix);
    std::cout << flashes << std::endl;
    std::cout << all_flash << std::endl;
}

