#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {
    ifstream file(*(++argv));

    string line;
    string cmd;
    int val;
    int forward = 0;
    int depth = 0;
    int aim = 0;
    while(getline(file, line)) {
        istringstream l(line);
        l >> line >> val;
        if (line == "forward") {
            forward += val;
            depth += aim*val;
        } else if (line == "down") {
            aim += val;
        } else {
            aim -= val;
        }
    }
    cout << depth * forward;
}
