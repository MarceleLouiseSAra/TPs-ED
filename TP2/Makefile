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

$(OBJ_DIR)/listaEncadeada.o: $(INCLUDE_DIR)/node.hpp $(INCLUDE_DIR)/listaEncadeada.hpp $(SRC_DIR)/listaEncadeada.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/listaEncadeada.cpp -I$(INCLUDE_DIR) -o $@

$(OBJ_DIR)/pilha.o: $(INCLUDE_DIR)/node.hpp $(INCLUDE_DIR)/pilha.hpp $(SRC_DIR)/pilha.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pilha.cpp -I$(INCLUDE_DIR) -o $@

$(OBJ_DIR)/grafo.o:  $(INCLUDE_DIR)/template.hpp $(INCLUDE_DIR)/grafo.hpp $(SRC_DIR)/grafo.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/grafo.cpp -I$(INCLUDE_DIR) -o $@

$(OBJ_DIR)/heap.o: $(INCLUDE_DIR)/node.hpp $(INCLUDE_DIR)/heap.hpp $(SRC_DIR)/heap.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/heap.cpp -I$(INCLUDE_DIR) -o $@

$(OBJ_DIR)/main.o: $(INCLUDE_DIR)/template.hpp $(INCLUDE_DIR)/node.hpp $(INCLUDE_DIR)/listaEncadeada.hpp $(INCLUDE_DIR)/pilha.hpp $(INCLUDE_DIR)/grafo.hpp $(INCLUDE_DIR)/heap.hpp $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I$(INCLUDE_DIR) -o $@

vpl_execution: $(OBJ_DIR)/node.o $(OBJ_DIR)/listaEncadeada.o $(OBJ_DIR)/pilha.o $(OBJ_DIR)/grafo.o $(OBJ_DIR)/heap.o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

all: vpl_execution

build: vpl_execution greetings

clean: $(OBJ_DIR)/node.o $(OBJ_DIR)/listaEncadeada.o $(OBJ_DIR)/pilha.o $(OBJ_DIR)/grafo.o $(OBJ_DIR)/heap.o $(OBJ_DIR)/main.o $(BIN_DIR)/vpl_execution
	rm $^