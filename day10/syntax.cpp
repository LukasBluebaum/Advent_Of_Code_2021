#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>


int main(int argc, char** argv) {
    std::unordered_map<char, int> m = {{'}', 1197}, {')', 3}, {'>', 25137}, {']', 57}};
    std::unordered_map<char, char> m2 = {{'{', '}'}, {'(', ')'}, {'<', '>'}, {'[', ']'}};
    std::unordered_map<char, int> m3 = {{'}', 3}, {')', 1}, {'>', 4}, {']', 2}};

    std::ifstream file(argv[1]);
    std::string line;
    std::vector<std::vector<char>> lines;
    while(std::getline(file, line)) {
        std::vector<char> temp;
        for(const auto& c: line) temp.push_back(c);
        lines.push_back(temp);
    }

    int sumPart1 = 0;
    std::vector<long> scores;
    for(const auto& l: lines) {
        std::stack<char> current;
        int sumTemp = 0;
        for(const auto& c: l) {
            if (c == '{' || c == '(' || c == '<' || c == '[') {
                current.push(c);
            } else {
                char temp = current.top();
                current.pop();
                if (m2[temp] != c) {
                    sumTemp += m[c];
                    break;
                }
            }
        }

        long sum = 0;
        while(!current.empty() && sumTemp == 0) {
            char temp = current.top();
            current.pop();
            sum = sum*5 + m3[m2[temp]];
        }
        if(current.empty()) scores.push_back(sum);
        sumPart1 += sumTemp;
    }
    int n = scores.size() / 2;
    std::nth_element(scores.begin(), scores.begin() + n, scores.end());
    std::cout << "Part1: " << sumPart1 << std::endl;
    std::cout << "Part2: " << scores[n] << std::endl;
}
