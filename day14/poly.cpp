#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <unordered_map>

using std::string;
using std::vector;
using std::array;
using std::ifstream;
using std::unordered_map;


int main(int argc, char** argv) {
    ifstream file(argv[1]);
    int steps = std::stoi(argv[2]);
    string line;
    unordered_map<string, char> rules;
    string templ;

    std::getline(file, templ);
    std::getline(file, line);
    while(std::getline(file, line)) {
        rules[line.substr(0, 2)] = line[line.size() - 1];
    }

    unordered_map<string, long> patternCount;
    unordered_map<char, long> charCount;
    for(auto i = 0; i<templ.size()-1; i++) {
        patternCount[templ.substr(i, 2)]++;
        charCount[templ[i]]++;
    }
    charCount[templ[templ.size()-1]]++;

    for(auto j = 0; j<steps; j++) {
        unordered_map<string, long> newMap;
        for(const auto& p: patternCount) {
            if(rules.find(p.first) != rules.end()) {
                newMap[string() + p.first[0]+rules[p.first]] += p.second;
                newMap[string() + rules[p.first]+p.first[1]] += p.second;
                charCount[rules[p.first]] += p.second;
            } else {
                newMap[p.first] = p.second;
            }
        }
        patternCount = std::move(newMap);
    }

    auto max = *std::max_element(charCount.begin(), charCount.end(),
                                 [](const auto& p, const auto& p2) {return p.second < p2.second;});
    auto min = *std::min_element(charCount.begin(), charCount.end(),
                                 [](const auto& p, const auto& p2) {return p.second < p2.second;});
    std::cout << max.second << std::endl;
    std::cout << min.second << std::endl;
    std::cout << max.second-min.second << std::endl;
}
