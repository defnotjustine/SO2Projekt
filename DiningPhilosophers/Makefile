# Nazwa pliku wykonywalnego
TARGET = philosophers

# Kompilator
CXX = g++

# Flagi kompilacji
CXXFLAGS = -Wall -std=c++17 -pthread

# Pliki źródłowe i nagłówkowe
SRCS = main.cpp DiningPhilosophers.cpp
HEADERS = DiningPhilosophers.h

# Pliki obiektowe
OBJS = $(SRCS:.cpp=.o)

# Domyślna reguła (kompilacja projektu)
all: $(TARGET)

# Kompilacja programu
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Kompilacja plików .cpp na .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Usunięcie plików obiektowych i pliku wykonywalnego
clean:
	rm -f $(OBJS) $(TARGET)

# Uruchamianie programu z domyślną liczbą filozofów (np. 5)
run: all
	./$(TARGET) 5
