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

    teste.adicionarAresta(4, 1);

    teste.adicionarAresta(4, 2);

    teste.adicionarAresta(4, 3);

    teste.adicionarAresta(4, 4);

    teste.adicionarAresta(4, 5);

    teste.imprimeGrafo();

}


int main () {

    grafo teste(6);

    testGrafo(teste);

    return 0;
}