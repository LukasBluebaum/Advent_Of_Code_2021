#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <iterator>

typedef std::pair<std::vector<std::string>, std::vector<std::string>> inputs;

std::map<int,std::set<int>> create_map() {
    std::map<int,std::set<int>> m;
    m[0] = {0, 1, 2, 4, 5, 6};
    m[1] = {2, 5};
    m[2] = {0, 2, 3, 4, 6};
    m[3] = {0, 2, 3, 5, 6};
    m[4] = {1, 2, 3, 5};
    m[5] = {0, 1, 3, 5, 6};
    m[6] = {0, 1, 3, 4, 5, 6};
    m[7] = {0, 2, 5};
    m[8] = {0, 1, 2, 3, 4, 5, 6};
    m[9] = {0, 1, 2, 3, 5, 6};
    return m;
}

void printMap(std::map<char, std::set<int>>& current) {
    for(const auto& pair: current) {
        std::cout << pair.first << " -> { ";
        for(int i: pair.second) std::cout << i << ", ";
        std::cout << "}" << std::endl;
    }
}

std::set<int> getValues(std::map<char, std::set<int>>& current) {
    std::set<int> used;
    for(const auto& p: current) {
        for(const auto& i: p.second) used.insert(i);
    }
    return used;
}

bool updateSet(std::map<char, std::set<int>>& current, std::map<int, std::set<int>>& m, std::string& letters, int number) {
    std::set<int> used = getValues(current);
    for(const char& c: letters) {
        std::set<int> temp;
        if (current.find(c) != current.end()) {
            std::set_intersection(current[c].begin(), current[c].end(),
                                    m[number].begin(), m[number].end(),
                                    std::inserter(temp, temp.begin()));
        } else {
            std::set_difference(m[number].begin(), m[number].end(),
                                    used.begin(), used.end(),
                                    std::inserter(temp, temp.begin()));
        }
        if(temp.size() == 0) return false;
        current[c] = temp;
    }
    for(const auto& p: current) {
        if(p.second.size() == 1) {
            for(const auto& x: current) {
                if (x.second == p.second && x != p) {
                    return false;
                }
            }
        }
    }
    return true;
}

int handleLine(inputs& line, std::map<int, std::set<int>>& m) {
    std::string one, four, seven, eight;
    std::vector<std::string> fiveLen;
    std::vector<std::string> sixLen;
    for(std::string s: line.first) {
        size_t sLen = s.size();
        if (sLen == 2)  one = s;
        if (sLen == 3)  seven = s;
        if (sLen == 4)  four = s;
        if (sLen == 7)  eight = s;
        if (sLen == 5)  fiveLen.push_back(s);
        if (sLen == 6)  sixLen.push_back(s);
    }

    std::map<char,std::set<int>> current;
    bool success;
    success = updateSet(current, m, one, 1);
    success = updateSet(current, m, seven, 7);
    success = updateSet(current, m, four, 4);

    std::vector<int> sixes{0, 6, 9};
    for(const auto& i: sixes) {
        size_t found = 0;
        for(size_t j = 0; j<sixLen.size(); j++) {
            std::map<char, std::set<int>> temp(current);
            success = updateSet(temp, m, sixLen[j], i);
            if (success) {
                //std::cout << sixLen[j] << std::endl;
                current = temp;
                found = j;
                break;
            }
        }
        sixLen.erase(sixLen.begin() + found);
    }

    std::vector<int> fives{2, 3,5};
    for(const auto& i: fives) {
        size_t found = 0;
        for(size_t j = 0; j<fiveLen.size(); j++) {
            std::map<char, std::set<int>> temp(current);
            success = updateSet(temp, m, fiveLen[j], i);
            if (success) {
                //std::cout << fiveLen[j] << std::endl;
                current = temp;
                found = j;
                break;
            }
        }
        fiveLen.erase(fiveLen.begin() + found);
    }

    for(const auto& p: current) {
        if(p.second.size() > 1) {
            for(const auto& x: current) {
                if (x != p) {
                    std::set<int> temp;
                    std::set_difference(p.second.begin(), p.second.end(),
                                                x.second.begin(), x.second.end(),
                                                std::inserter(temp, temp.begin()));
                    current[p.first] = temp;
                }
            }
        }
    }
    //printMap(current);

    int i = 3;
    int sum = 0;
    for(std::string s: line.second) {
        std::set<int> temp;
        for(char c: s) {
            temp.insert(*current[c].begin());
        }
        int num = 0;
        for(auto p: m) {
            if (p.second == temp) num = p.first;
        }
        sum += num * pow(10, i);
        i--;
    }
    std::cout << sum << std::endl;
    return sum;
}

int main(int argc, char** argv) {
    std::ifstream file(argv[1]);
    std::string line;
    std::vector<inputs> lines;
    while(std::getline(file, line)) {
        std::istringstream stringStream(line);
        std::vector<std::string> patterns;
        std::string in;
        while(true) {
            stringStream >> in;
            if (!in.compare("|")) break;
            patterns.push_back(in);
        }
        std::vector<std::string> digits;
        while(stringStream >> in) digits.push_back(in);
        lines.push_back({patterns, digits});
    }

    std::map<int,std::set<int>> m = create_map();
    int sum = 0;
    for(inputs& p: lines) {
        sum += handleLine(p, m);
    }

    std::cout << sum << std::endl;
    /*int count = 0;
    for(const inputs& p: lines) {
        for(const std::string& digit: p.second) {
            //std::cout << digit << std::endl;
            size_t s = digit.size();
            if (s == 2 || s == 4 || s == 3 || s == 7) count++;
        }
    }*/
    //std::cout << count << std::endl;
}
