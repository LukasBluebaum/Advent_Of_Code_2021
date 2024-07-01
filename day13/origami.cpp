#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using std::string;
using std::vector;
using std::pair;


void printMatrix(int* matrix, int maxX, int maxY) {
    std::ofstream myfile("solution.txt");
    for(auto i = 0; i<maxY; i++) {
        for(auto j = 0; j<maxX; j++) {
            if(matrix[i*maxX + j]) {
                myfile << "#";
            } else {
                myfile << ".";
            }
        }
        myfile << "\n";
    }
    myfile.close();
}

int* foldX(int* matrix, int maxX, int maxY, int fold) {
    int *matrix2 = new int[maxY*fold]();
    for(auto i = 0; i<maxY; i++) {
        for(auto j = 0; j<maxX; j++) {
            if ( j >= fold+1) {
                matrix2[i*fold + (fold - (j - fold))] += matrix[i*maxX + j];
            } else if (j < fold){
                matrix2[i*fold + j] += matrix[i*maxX + j];
            }
        }
    }
    delete[] matrix;
    return matrix2;
}

int* foldY(int* matrix, int maxX, int maxY, int fold) {
    int *matrix2 = new int[fold*maxX]();
    for(auto i = 0; i<maxY; i++) {
        for(auto j = 0; j<maxX; j++) {
            if ( i >= fold+1) {
                matrix2[(fold - (i - fold))*maxX + j] += matrix[i*maxX + j];
            } else if (i < fold) {
                matrix2[i*maxX + j] += matrix[i*maxX + j];
            }
        }
    }
    delete[] matrix;
    return matrix2;
}

int countMarked(int* matrix, int maxX, int maxY) {
    int count = 0;
    for(auto i = 0; i<maxY; i++) {
        for(auto j = 0; j<maxX; j++) {
            if (matrix[i*maxX + j] > 0) count++;
        }
    }
    return count;
}

int main(int argc, char** argv) {
    std::ifstream file(argv[1]);
    int numFolds = std::stoi(argv[2]);
    string line;
    vector<pair<int, int>> inputs;
    vector<string> folds;
    while(std::getline(file, line)) {
        int comma = line.find(",");
        if (comma > 0) {
            inputs.push_back({std::stoi(line.substr(0, comma)), std::stoi(line.substr(comma+1))});
        } else {
            if (line.size() > 1) {
                folds.push_back(line);
            }
        }
    }
    if (numFolds > folds.size()) numFolds = folds.size();

    pair<int,int> tempX = *std::max_element(inputs.begin(), inputs.end(),
                                [](pair<int,int> p1, pair<int,int> p2) {return p1.first < p2.first;} );
    int maxX = tempX.first + 1;
    pair<int,int> tempY = *std::max_element(inputs.begin(), inputs.end(),
                                [](pair<int,int> p1, pair<int,int> p2) {return p1.second < p2.second;} );
    int maxY = tempY.second + 1;
    int *matrix = new int[maxY*maxX]();
    for(const auto& pair: inputs) {
        matrix[maxX*pair.second + pair.first] = 1;
    }

    int count = 0;
    for(auto i = 0; i<numFolds; i++) {
        int testX = folds[i].find("x=");
        int temp = 0;
        if (testX > 0) {
            temp = std::stoi(folds[i].substr(testX+2));
            matrix = foldX(matrix, maxX, maxY, temp);
            maxX = temp;
            count += countMarked(matrix, maxX, maxY);
        } else {
            temp = std::stoi(folds[i].substr(folds[i].find("y=")+2));
            matrix = foldY(matrix, maxX, maxY, temp);
            maxY = temp;
            count += countMarked(matrix, maxX, maxY);
        }
    }
    printMatrix(matrix, maxX, maxY);
    delete[] matrix;
    std::cout << count << std::endl;
}
