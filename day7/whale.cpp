#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


int main(int argc , char** argv) {
    std::ifstream file(argv[1]);
    std::string line;
    std::vector<int> nums;
    while(std::getline(file, line, ',')) nums.push_back(std::stoi(line));

    /*int n = nums.size() / 2;
    std::cout << n << std::endl;
    std::nth_element(nums.begin(), nums.begin() + n, nums.end());
    int median = nums[n];
    std::cout << median << std::endl;

    int fuel = 0;
    for(size_t i = 0; i<nums.size(); i++) fuel += std::abs(int(nums[i] - median));*/

    double sum = 0;
    for(size_t i = 0; i<nums.size(); i++) sum += nums[i];
    int mean = std::round(sum / nums.size());
    int fuel = 0;
    for(size_t i = 0; i<nums.size(); i++) {
        int steps = std::abs(int(nums[i] - mean));
        fuel += steps*(steps+1)/2;
    }
    std::cout << fuel << std::endl;
}
