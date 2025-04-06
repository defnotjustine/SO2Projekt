#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>

#include "DiningPhilosophers.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <number_of_philosophers>" << endl;
        return 1;
    }

    int num_philosophers = stoi(argv[1]);
    DiningPhilosophers dp(num_philosophers);
    dp.start();

    return 0;
}
