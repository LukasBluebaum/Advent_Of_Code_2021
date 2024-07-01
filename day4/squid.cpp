#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <set>

#define ROWS 5
#define COLS 5

typedef std::vector<std::vector<int>> matrix;

matrix readMatrix(std::ifstream& file) {
    matrix m;
    std::string line;
    for(size_t x = 0; x < ROWS; x++) {
        getline(file, line);
        std::istringstream str(line);
        std::vector<int> row;
        int temp;
        for(size_t i = 0; i<COLS; i++) {
            str >> temp;
            row.push_back(temp);
        }
        m.push_back(row);
    }
    getline(file, line);
    return m;
}

void printMatrix(const matrix& m) {
    for(const auto& row: m) {
        for(const auto& x: row) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
}

int sumUnmarked(const matrix &m, std::unordered_set<int>& nums, int last) {
    int sum = 0;
    std::cout << last << "\n";
    for(size_t i = 0; i<ROWS; i++) {
        for(size_t j = 0; j<COLS; j++) {
            if (nums.find(m[i][j]) == nums.end()) {
                sum += m[i][j];
                //std::cout << m[i][j] << " ";
            }
        }
        //std::cout << std::endl;
    }
    return sum*last;
}

std::set<int> checkMatrices(std::vector<matrix>& matrices, std::unordered_set<int>& nums, int last) {
    std::set<int> to_remove;
    for(int k = 0; k<matrices.size(); k++) {
    //for(const matrix& m: matrices) {
        // ROWS
        for(size_t i = 0; i<ROWS; i++) {
            bool found = true;
            for(size_t j = 0; j<COLS; j++) {
                if(nums.find(matrices[k][i][j]) == nums.end()){
                   found = false;
                   break;
                }
            }
            //if (found) return sumUnmarked(m, nums, last);
            if (found) to_remove.insert(k);
        }
        // COLS
        for(size_t j = 0; j<COLS; j++) {
            bool found = true;
            for(size_t i = 0; i<ROWS; i++) {
                if(nums.find(matrices[k][i][j]) == nums.end()){
                   found = false;
                   break;
                }
            }
            //if (found) return sumUnmarked(m, nums, last);
            if (found) to_remove.insert(k);
        }
    }
    return to_remove;
    //return -1;
}

int main(int argc, char** argv) {
    std::ifstream file(argv[1]);
    std::vector<matrix> matrices;

    std::vector<int> numbers;
    std::string line;
    getline(file, line);
    std::istringstream str(line);
    int temp;
    char ignore;
    while(str >> temp) {
        numbers.push_back(temp);
        str >> ignore;
    }
    /*for(const int& x: numbers) {
        std::cout << x << " ";
    }
    std::cout << std::endl;*/

    getline(file, line);
    for(size_t i = 0; i<100; i++) {
        matrices.push_back(readMatrix(file));
    }
    std::unordered_set<int> current;
    int result = -1;

    for(int i = 0; i<numbers.size(); i++) {
        std::set<int> to_remove;
        current.insert(numbers[i]);
        if (i >= ROWS && matrices.size() > 0) {
            to_remove = checkMatrices(matrices, current, numbers[i]);
            //result_current = checkMatrices(matrices, current, numbers[i]);
        }
        std::cout << matrices.size() << std::endl;
        int temp = 0;
        for(const int& x: to_remove) {
        //for(int j = 0; j<to_remove.size(); j++) {
            if (matrices.size() == 1) {
                result = sumUnmarked(matrices[0], current, numbers[i]);
                std::cout << result << std::endl;
            }
            matrices.erase(matrices.begin() + x - temp);
            temp++;
        }
        //std::cout << to_remove.size() << std::endl;
        //if (result > -1) break;
    }
    std::cout << result << std::endl;
    /*for(const matrix& m: matrices) {
        printMatrix(m);
        std::cout << std::endl;
    }*/
}
