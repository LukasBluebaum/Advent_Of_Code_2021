#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <numeric>

using std::string;
using std::ifstream;
using std::bitset;
using std::vector;
using std::multiplies;


long handlePacket(string& bits, int *currentPos, int *countVes);


string toBinaryStr(const string& line) {
    string bits;
    for(auto i = 0; i<line.size(); i++) {
        int current = std::stoul(line.substr(i, 1), nullptr, 16);
        bitset<4> b(current);
        bits += b.to_string();
    }
    return bits;
}

long calcResult(vector<long>& results, int type) {
    switch(type) {
        case 0:
            return accumulate(results.begin(), results.end(), 0l);
        case 1:
            return accumulate(results.begin(), results.end(), 1l, multiplies<long>());
        case 2:
            return *min_element(results.begin(), results.end());
        case 3:
            return *max_element(results.begin(), results.end());
        case 5:
            return results[0] > results[1];
        case 6:
            return results[0] < results[1];
        case 7:
            return results[0] == results[1];
        default:
            return 0l;
    }
}

long handleOperator(string bits, int *currentPos, int *countVes, int type) {
    vector<long> results;
    if (bits[(*currentPos)++] == '0') {
        int temp = *currentPos;
        int lengthBits = std::stoul(bits.substr(*currentPos, 15), nullptr, 2);
        std::cout << "Parsing: " << lengthBits << " bits" << std::endl;
        *currentPos += 15;
        while(*currentPos < temp + 15 + lengthBits) {
            results.push_back(handlePacket(bits, currentPos, countVes));
        }
    } else {
        int numPackets = std::stoul(bits.substr(*currentPos, 11), nullptr, 2);
        std::cout << "Parsing: " << numPackets << std::endl;
        *currentPos += 11;
        while(numPackets-- > 0) {
            results.push_back(handlePacket(bits, currentPos, countVes));
        }
    }

    return calcResult(results, type);
}

long handleLiteral(string& bits, int *currentPos) {
    string result;
    while(bits[*currentPos] != '0') {
        result += bits.substr(*currentPos+1, 4);
        *currentPos += 5;
    }
    result += bits.substr(*currentPos+1, 4);
    *currentPos += 5;
    std::cout << "Literal Value: " << std::stoul(result, nullptr, 2) << std::endl;
    return std::stoul(result, nullptr, 2);
}

long handlePacket(string& bits, int *currentPos, int *countVes) {
    int version = std::stoul(bits.substr(*currentPos, 3), nullptr, 2);
    *countVes += version;
    int type = std::stoul(bits.substr(*currentPos+3, 3), nullptr, 2);
    std::cout << "\nPackage Version: " << version << std::endl;

    *currentPos += 6;
    if (type == 4) {
        std::cout << "Handling Literal Package" << std::endl;
        return handleLiteral(bits, currentPos);
    } else {
        std::cout << "Handling Operator Package" << std::endl;
        return handleOperator(bits, currentPos, countVes, type);
    }
}

int main(int argc, char** argv) {
    ifstream file(argv[1]);
    string line;
    std::getline(file, line);

    string bits = toBinaryStr(line);
    std::cout << bits << "\n";

    int currentPos = 0;
    int countVes = 0;
    long result = handlePacket(bits, &currentPos, &countVes);
    std::cout << "\nVersion Sum: " << countVes << std::endl;
    std::cout << "Result: " << result << std::endl;
}
