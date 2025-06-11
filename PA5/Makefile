CC=g++
CFLAGS=-std=c++11 -Wall
SRC_DIR=src
INCLUDE_DIR=include
OBJ_DIR=obj
BIN_DIR=bin

greetings:
	@echo "Compilação realizada com sucesso!"

$(OBJ_DIR)/Set.o: $(INCLUDE_DIR)/Set.hpp $(SRC_DIR)/Set.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Set.cpp -I$(INCLUDE_DIR) -o $@

$(OBJ_DIR)/main.o: $(INCLUDE_DIR)/Set.hpp $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I$(INCLUDE_DIR) -o $@

pa5.out: $(OBJ_DIR)/Set.o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

all: pa5.out

build: pa5.out greetings

clean: $(OBJ_DIR)/main.o $(OBJ_DIR)/Set.o
	rm $^