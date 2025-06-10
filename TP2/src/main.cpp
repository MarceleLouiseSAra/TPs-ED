#include "node.hpp"
#include "listaEncadeada.hpp"
#include "pilhaEncadeada.hpp"
#include "grafo.hpp"
#include "heap.hpp"
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void testListaEncadeada(listaEncadeada &teste) {

    teste.insertInTheBeginning(2);

    teste.insertInTheBeginning(1);

    teste.insertInTheEnd(9);

    teste.print(); // 1, 2, 9

    int x;
    x = teste.getItem(0); // 1
    cout << x << endl;

    teste.setItem(8, 1);

    teste.insertAtPosition(7, 0);

    teste.print(); // 7, 8, 9

    teste.removeFirstOne();

    teste.removeLastOne();

    teste.print(); // 8

    teste.insertInTheEnd(2);

    teste.insertInTheBeginning(1);

    teste.print(); // 1, 8, 2

    teste.removePosition(1);

    teste.print(); // 1, 2

}

void testPilhaEncadeada(pilhaEncadeada &teste) {
    
    teste.empilha(1);

    teste.empilha(2);

    teste.desempilha();

    teste.empilha(3);

    teste.imprime();
    
}

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

void testaHeap(heap &teste) {

    teste.insert(13);
    teste.insert(15);
    teste.insert(8);
    teste.insert(23);
    teste.insert(21);
    teste.insert(9);
    teste.insert(2);

    teste.printHeap();
}

int main () {

    listaEncadeada listaEncadeada;

    // testListaEncadeada(listaEncadeada);

    pilhaEncadeada pilhaEncadeada;

    // testPilhaEncadeada(pilhaEncadeada);

    grafo grafo(6); // Grafo com 6 vértices

    // testGrafo(grafo);

    heap heap;

    testaHeap(heap);

    return 0;
}