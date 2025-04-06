# Dining Philosophers Problem

## 📌 Project Overview

This project implements the **Dining Philosophers Problem** in **C++**, utilizing **multithreading (`std::thread`)** and synchronization mechanisms like **`std::mutex`**. The problem is a classic **concurrency problem** used to study **process synchronization** and **shared resource management**.

Each philosopher **thinks 🧠, eats 🍝, and waits for utensils 🥢**, but cannot eat without picking up **two forks** (mutexes). The program provides a solution that **prevents deadlocks** and allows efficient collaboration among philosophers.

* * * * *

## 🚀 Running Instructions

### **1️⃣ Compilation via Terminal**

To compile the program, run:

```
g++ -std=c++11 main.cpp DiningPhilosophers.cpp -o dining_philosophers -pthread
```

### **2️⃣ Running the Program**

To run the program, execute:

```
./dining_philosophers <number_of_philosophers>
```

For example, for **5 philosophers**:

```
./dining_philosophers 5
```

### **3️⃣ Alternative Method: Makefile**

If you have a **Makefile**, simply run:

```
make
make run
```

* * * * *

## 🎯 Problem Description

The **Dining Philosophers Problem** was proposed by **Edsger Dijkstra** and is frequently used as an example of **process synchronization** in operating systems.

Five philosophers are sitting around a circular table. Each philosopher has **one fork to their left and one fork to their right** (the forks are shared with neighbors). To **eat**, the philosopher must pick up **both forks simultaneously**. After eating, they put the forks down and return to thinking.

**Potential problems that need to be addressed in the code:**

1. **Deadlock** — when all philosophers pick up **one fork** and no one can finish eating.
2. **Starvation** — when some philosophers never get a chance to eat.
3. **Mixed output on console** — multithreading can cause garbled output.

* * * * *

## 🧵 Threads and Their Roles

There are two main types of threads in the program:

| **Thread** | **Role** |
| --- | --- |
| **Main (`main`)** | Creates philosopher threads and waits for them to finish. |
| **Philosopher (`philosopher`)** | Each philosopher runs in a separate thread. Their tasks are: **thinking → waiting for utensils → eating → thinking**. |

* * * * *

## 🔒 Critical Sections and Their Resolution

A **critical section** occurs when a philosopher tries to pick up **two forks** (mutexes). The issue is that if all philosophers attempt to do this simultaneously, it can result in a **deadlock**.

### **✔ Deadlock Solution**

To prevent deadlock, we introduce the **rule of fork pickup order**:

- **Even-numbered philosophers** pick up the **left fork** first, followed by the **right fork**.
- **Odd-numbered philosophers** pick up the **right fork** first, followed by the **left fork**.

This ensures that **at least one fork is always available**, preventing a deadlock.

Additionally, we use:

- **`std::mutex` for each fork** — to ensure that only **one philosopher** can pick up a fork at a time.
- **`std::lock_guard<mutex>` for `std::cout`** — to prevent garbled output when multiple threads print to the console simultaneously.

* * * * *

## 📌 Code Structure

The project consists of three files:

1. **`main.cpp`** — Main function, initializes philosopher threads.
2. **`DiningPhilosophers.h`** — Declaration of the `DiningPhilosophers` class.
3. **`DiningPhilosophers.cpp`** — Implementation of philosophers and fork management.

* * * * *

## 📌 Implementation

Sample key code snippets:

✔ **Creating philosopher threads**:

```cpp
for (int i = 0; i < num_philosophers; i++) {
    philosophers.emplace_back(&DiningPhilosophers::philosopher, this, i);
}
```

✔ **Critical section — picking up forks**:

```cpp
if (id % 2 == 0) { // Even philosopher
    forks[left_fork].lock();
    forks[right_fork].lock();
} else { // Odd philosopher
    forks[right_fork].lock();
    forks[left_fork].lock();
}
```

✔ **Protecting `std::cout` from mixed output**:

```cpp
{
    lock_guard<mutex> lock(cout_mutex);
    cout << "Philosopher " << id << " is eating..." << std::endl;
}
```

* * * * *

## 📌 Sample Program Output

```
Philosopher 0 is thinking...
Philosopher 1 is thinking...
Philosopher 2 is thinking...
Philosopher 3 is thinking...
Philosopher 4 is thinking...
Philosopher 0 is eating...
Philosopher 1 is eating...
Philosopher 2 is eating...
Philosopher 3 is eating...
Philosopher 4 is eating...
```

The philosophers **do not block** and **take turns eating and thinking**.

* * * * *

## 📝 Author

👨‍💻 *Yustyna Sukhorab*  
🔗 **Repository:** [GitHub Link](https://github.com/defnotjustine/SO2Projekt/tree/main/DiningPhilosophers) 🚀
