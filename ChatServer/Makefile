# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LIBS = -lws2_32 -pthread

# Paths
SRC = .
OBJ = ./obj
BIN = ./bin

# Files
SERVER_SRC = $(SRC)/server.cpp
CLIENT_SRC = $(SRC)/client.cpp
SERVER_OBJ = $(OBJ)/server.o
CLIENT_OBJ = $(OBJ)/client.o
SERVER_BIN = $(BIN)/server
CLIENT_BIN = $(BIN)/client

# Targets
all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(CLIENT_BIN): $(CLIENT_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(SERVER_OBJ): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -c -o $@ $^

$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -c -o $@ $^

# Clean object and binary files
clean:
	rm -rf $(OBJ)/*.o $(BIN)/*

# Create directories for objects and binaries
$(OBJ):
	mkdir -p $(OBJ)

$(BIN):
	mkdir -p $(BIN)

.PHONY: all clean
