#include <iostream>
#include <fstream>


int main(int argc, char** argv) {
    std::ifstream file(argv[1]);
    std::string line;
    std::getline(file, line);

    int x = line.find("x=") + 2;
    int point = line.find(".");
    int comma = line.find(",");
    int xmin = std::stoi(line.substr(x, point-x));
    int xmax = std::stoi(line.substr(point+2, comma-point+2));

    int y = line.find("y=") + 2;
    point = line.find(".", point+3);
    int ymin = std::stoi(line.substr(y, point-y));
    int ymax = std::stoi(line.substr(point+2, line.size()-point+2));

    std::cout << (ymin+1) * (ymin) / 2 << std::endl;

    int count = 0;
    for(int i = 0; i<1000; i++) {
        for(int j = -1000; j<1000; j++) {
            int x = 0;
            int y = 0;
            int dx = i;
            int dy = j;
            for(int t = 0; t<1000; t++) {
                dx = dx - 1 > 0 ? dx - 1 : 0;
                x += dx;
                y += dy--;
                if ( x <= xmax && x >=xmin && y >= ymin && y <= ymax) {
                    count++;
                    break;
                }
            }
        }
    }
    std::cout << count << std::endl;
}
