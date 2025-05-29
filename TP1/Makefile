CC=g++
CFLAGS=-std=c++11 -Wall
SRC_DIR=src
INCLUDE_DIR=include
OBJ_DIR=obj
BIN_DIR=bin

greetings:
	@echo "Compilação realizada com sucesso!"

$(OBJ_DIR)/node.o: $(INCLUDE_DIR)/node.hpp $(SRC_DIR)/node.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/node.cpp -I$(INCLUDE_DIR) -o $@

$(OBJ_DIR)/TAD.o: $(INCLUDE_DIR)/node.hpp $(INCLUDE_DIR)/TAD.hpp $(SRC_DIR)/TAD.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/TAD.cpp -I$(INCLUDE_DIR) -o $@

$(OBJ_DIR)/main.o: $(INCLUDE_DIR)/node.hpp $(INCLUDE_DIR)/TAD.hpp $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I$(INCLUDE_DIR) -o $@

vpl_execution: $(OBJ_DIR)/node.o $(OBJ_DIR)/TAD.o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

all: vpl_execution

build: vpl_execution greetings

clean: $(OBJ_DIR)/node.o $(OBJ_DIR)/TAD.o $(OBJ_DIR)/main.o $(BIN_DIR)/vpl_execution
	rm $^