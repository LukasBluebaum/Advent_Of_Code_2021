#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

namespace std {
    template <> struct hash<std::pair<int, int>> {
        inline size_t operator()(const std::pair<int, int> &v) const {
            std::hash<int> int_hasher;
            return int_hasher(v.first) ^ int_hasher(v.second);
        }
    };
}

std::unordered_set<std::pair<int, int>> findBasingSize(std::vector<std::vector<int>>& matrix, int x, int y) {
    if (x < 0 || y < 0 || x >= matrix.size() || y >= matrix[0].size() || matrix[x][y] == 9) return {};
    std::unordered_set<std::pair<int, int>> visited{{x, y}};
    std::unordered_set<std::pair<int, int>> temp;
    if(x > 0 && matrix[x-1][y] > matrix[x][y]) {
        temp = findBasingSize(matrix, x-1, y);
        visited.insert(temp.begin(), temp.end());
    }
    if(x < matrix.size()-1 && matrix[x+1][y] > matrix[x][y]) {
        temp = findBasingSize(matrix, x+1, y);
        visited.insert(temp.begin(), temp.end());
    }
    if(y > 0 && matrix[x][y-1] > matrix[x][y]) {
        temp = findBasingSize(matrix, x, y-1);
        visited.insert(temp.begin(), temp.end());
    }
    if(y < matrix[0].size()-1 && matrix[x][y+1] > matrix[x][y]) {
        temp = findBasingSize(matrix, x, y+1);
        visited.insert(temp.begin(), temp.end());
    }
    return visited;
}

int main(int argc, char** argv) {
    std::ifstream file(argv[1]);
    std::string line;
    std::vector<std::vector<int>> matrix;
    while(std::getline(file, line)) {
        std::vector<int> row;
        for(const char& c: line) row.push_back(c - '0');
        matrix.push_back(row);
    }
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    for(auto i = 0; i<matrix.size(); i++) {
        for(auto j = 0; j<matrix[0].size(); j++) {
            int up = i > 0 ? matrix[i-1][j] : INT_MAX;
            int down = i < matrix.size() - 1 ? matrix[i+1][j] : INT_MAX;
            int left = j > 0 ? matrix[i][j-1] : INT_MAX;
            int right = j < matrix[0].size() - 1 ? matrix[i][j+1] : INT_MAX;
            int current = matrix[i][j];
            if(current < up and current < down and current < left and current < right) {
                int size = findBasingSize(matrix, i, j).size();
                if (size > sum1) {
                    sum3 = sum2;
                    sum2 = sum1;
                    sum1 = size;
                } else if (size > sum2) {
                    sum3 = sum2;
                    sum2 = size;
                } else if (size > sum3) sum3 = size;
            }
        }
    }
    std::cout << sum1*sum2*sum3 << std::endl;
}
