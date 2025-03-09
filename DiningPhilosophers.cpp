#include "DiningPhilosophers.h"

DiningPhilosophers::DiningPhilosophers(int n) : num_philosophers(n), forks(n) {}

void DiningPhilosophers::philosopher(int id) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(100, 500);

    int left_fork = id;
    int right_fork = (id + 1) % num_philosophers;

    while (true) {

        //Thinking
        cout << "Philosopher " << id << " is thinking..." << endl;
        this_thread::sleep_for(chrono::milliseconds(dist(gen)));


        //Picking uo the forks
        if (id % 2 == 0) { // Even philosophers pick up left fork first
            forks[left_fork].lock();
            forks[right_fork].lock();
        } else { // Odd philosophers pick up right fork first
            forks[right_fork].lock();
            forks[left_fork].lock();
        }

        cout << "Philosopher " << id << " is eating..." << std::endl;
        this_thread::sleep_for(chrono::milliseconds(dist(gen)));


        //Putting down the forks (unlocks mutexes)
        forks[left_fork].unlock();
        forks[right_fork].unlock();
    }
}

void DiningPhilosophers::start() {
        // Create philosopher threads
    for (int i = 0; i < num_philosophers; i++) {
        philosophers.emplace_back(&DiningPhilosophers::philosopher, this, i);
    }

    // Wait for threads to finish
    for (auto& phil : philosophers) {
        phil.join();
    }
}