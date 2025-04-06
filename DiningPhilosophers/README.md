#  Problem jedzących filozofów
**📌 Opis projektu**
--------------------

Projekt implementuje **problem jedzących filozofów** w języku **C++**, wykorzystując **wielowątkowość (`std::thread`)** oraz mechanizmy synchronizacji **(`std::mutex`)**. Problem ten jest **klasycznym zagadnieniem synchronizacji procesów**, stosowanym do badania **konkurencji** oraz **zarządzania zasobami współdzielonymi**.

Każdy filozof **myśli 🧠, je 🍝 i czeka na sztućce 🥢**, ale nie może jeść bez podniesienia **dwóch widelców** (mutexów). Program implementuje rozwiązanie, które **zapobiega zakleszczeniom (deadlock)** i umożliwia efektywną współpracę filozofów.

* * * * *

**🚀 Instrukcja uruchomienia**
------------------------------

### **1️⃣ Kompilacja w terminalu**

Aby skompilować program, użyj:

```
g++ -std=c++11 main.cpp DiningPhilosophers.cpp -o dining_philosophers -pthread

```

### **2️⃣ Uruchomienie programu**

```
./dining_philosophers <liczba_filozofów>

```

Przykładowo, dla **5 filozofów**:

```
./dining_philosophers 5

```

### **3️⃣ Alternatywna metoda: Makefile**

Jeśli masz **Makefile**, wystarczy:

```
make
make run

```

* * * * *

**🎯 Opis problemu**
--------------------

Problem jedzących filozofów został zaproponowany przez **Edsgera Dijkstrę** i jest często używany jako **przykład synchronizacji procesów** w systemach operacyjnych.

Pięciu filozofów siedzi wokół okrągłego stołu. Każdy filozof ma **jeden widelec po lewej stronie i drugi po prawej** (widelce są współdzielone z sąsiadami). Aby filozof mógł **jeść**, musi podnieść **oba widelce jednocześnie**. Po zakończeniu jedzenia odkłada widelce i wraca do myślenia.

**Potencjalne problemy, które muszą być rozwiązane w kodzie:**

1.  **Zakleszczenie (deadlock)** -- gdy wszyscy filozofowie podniosą **po jednym widelcu** i nikt nie będzie mógł dokończyć jedzenia.
2.  **Zagłodzenie (starvation)** -- gdy niektórzy filozofowie nigdy nie dostają szansy na jedzenie.
3.  **Przeplatane operacje na konsoli** -- wielowątkowość może powodować nieczytelne wyjście.

* * * * *

**🧵 Wątki i ich rola**
-----------------------

W programie istnieją dwa główne typy wątków:

| **Wątek** | **Rola** |
| --- | --- |
| **Główny (`main`)** | Tworzy wątki filozofów i czeka na ich zakończenie. |
| **Filozof (`philosopher`)** | Każdy filozof działa w osobnym wątku. Jego zadania to: **myślenie → czekanie na sztućce → jedzenie → myślenie**. |

* * * * *

**🔒 Sekcje krytyczne i ich rozwiązanie**
-----------------------------------------

**Sekcja krytyczna** to moment, w którym filozof próbuje podnieść **dwa widelce** (mutexy). Problem polega na tym, że jeśli wszyscy filozofowie spróbują to zrobić jednocześnie, może dojść do **zakleszczenia (deadlock)**.

### **✔ Rozwiązanie deadlocka**

Aby uniknąć deadlocka, wprowadzamy **zasadę kolejności podnoszenia widelców**:

-   **Filozofowie o parzystych numerach** najpierw podnoszą **lewy widelec**, a potem **prawy**.
-   **Filozofowie o nieparzystych numerach** najpierw podnoszą **prawy widelec**, a potem **lewy**.

Dzięki temu **zawsze zostaje dostępny przynajmniej jeden widelec**, co zapobiega blokadzie.

Dodatkowo używamy:

-   **`std::mutex` dla każdego widelca** -- aby tylko **jeden filozof mógł go podnieść na raz**.
-   **`std::lock_guard<mutex>` dla `std::cout`** -- aby uniknąć przeplatania tekstu w konsoli.

* * * * *

**📌 Struktura kodu**
---------------------

Projekt składa się z trzech plików:

1.  **`main.cpp`** -- Funkcja główna, inicjalizuje wątki filozofów.
2.  **`DiningPhilosophers.h`** -- Deklaracja klasy `DiningPhilosophers`.
3.  **`DiningPhilosophers.cpp`** -- Implementacja filozofów i zarządzanie widelcami.

* * * * *

**📌 Implementacja**
--------------------

Przykładowe kluczowe fragmenty kodu:

✔ **Tworzenie wątków filozofów**:

```
for (int i = 0; i < num_philosophers; i++) {
    philosophers.emplace_back(&DiningPhilosophers::philosopher, this, i);
}

```

✔ **Sekcja krytyczna -- podnoszenie widelców**:

```
if (id % 2 == 0) { // Parzysty filozof
    forks[left_fork].lock();
    forks[right_fork].lock();
} else { // Nieparzysty filozof
    forks[right_fork].lock();
    forks[left_fork].lock();
}

```

✔ **Ochrona `std::cout` przed przeplataniem tekstu**:

```
{
    lock_guard<mutex> lock(cout_mutex);
    cout << "Philosopher " << id << " is eating..." << std::endl;
}

```

* * * * *

**📌 Przykładowe wyjście programu**
-----------------------------------

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

Filozofowie **nie blokują się** i **kolejno jedzą oraz myślą**.

* * * * *

**📝 Autor**
------------

👨‍💻 *Yustyna Sukhorab*\
🔗 **Repozytorium:** *https://github.com/defnotjustine/SO2Projekt* 🚀
