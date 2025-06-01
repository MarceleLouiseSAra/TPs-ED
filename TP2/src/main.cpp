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

    teste.adicionarAresta(2, 0);
    teste.adicionarAresta(5, 0);
    // Vértice 0 tem 3 vizinhos: 2 e 5

    teste.adicionarAresta(2, 1);
    teste.adicionarAresta(4, 1);
    teste.adicionarAresta(5, 1);
    // Vértice 1 tem 2 vizinhos: 2, 4 e 5

    teste.adicionarAresta(4, 2);
    // Vértice 2 tem 3 vizinhos: 0, 1 e 4

    teste.adicionarAresta(5, 3);
    // Vértice 3 tem 1 vizinho: 5

    // Vértice 4 tem 3 vizinhos: 1 e 2
    
    // Vértice 5 tem 3 vizinhos: 0, 1 e 3

    teste.imprimeGrafo();

}

int main () {

    grafo teste(6); // Grafo com 6 vértices

    testGrafo(teste);

    return 0;
}