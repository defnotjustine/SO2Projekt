#ifndef DININGPHILOSOPHERS_H
#define DININGPHILOSOPHERS_H
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

class DiningPhilosophers {
private:
    int num_philosophers;  // Number of philosophers
    std::vector<std::mutex> forks;  // Mutex locks representing forks
    std::vector<std::thread> philosophers;  // Threads representing philosophers

    void philosopher(int id);

public:
    DiningPhilosophers(int n);
    void start();
};

#endif // DININGPHILOSOPHERS_H