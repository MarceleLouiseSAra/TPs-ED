#include "node.hpp"
#include "listaEncadeada.hpp"
#include "pilha.hpp"
#include "grafo.hpp"
#include "heap.hpp"
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void testListaEncadeada() {}

void testGrafo(grafo &teste){

    teste.adicionarAresta(4, 0);
    teste.adicionarAresta(5, 0);
    teste.adicionarAresta(6, 0);
    // Vértice 0 tem 3 vizinhos: 4, 5 e 6

    teste.adicionarAresta(1, 1);
    teste.adicionarAresta(2, 1);
    // Vértice 1 tem 2 vizinhos: 1 e 2

    teste.adicionarAresta(7, 2);
    teste.adicionarAresta(8, 2);
    // Vértice 2 tem 2 vizinhos: 7 e 8

    teste.adicionarAresta(1, 3);
    teste.adicionarAresta(2, 3);
    // Vértice 3 tem 2 vizinhos: 1 e 2

    teste.adicionarAresta(1, 4);
    teste.adicionarAresta(2, 4);
    teste.adicionarAresta(3, 4);
    // Vértice 4 tem 3 vizinhos: 1,2 e 3

    teste.adicionarAresta(4, 5);
    teste.adicionarAresta(5, 5);
    teste.adicionarAresta(6, 5);
    // Vértice 5 tem 3 vizinhos: 4, 5 e 6

    teste.imprimeGrafo();

}

int main () {

    grafo teste(6); // Grafo com 6 vértices

    testGrafo(teste);

    return 0;
}