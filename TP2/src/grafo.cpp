#include "grafo.hpp"
#include "template.hpp"
#include <iostream>
#include <string>

using namespace std;

grafo::grafo(int v) {

    this->numVertices = v;
    adjLista = Vetor<Vetor<int>>(numVertices); // Matriz de numVertices linhas

    for (int i = 0; i < this->numVertices; i++) {
        Vetor<int> vetorInterno(0); // Vértice 0 vizinhos inicialmente
        this->adjLista.SetElemento(i, vetorInterno);
    }
}

grafo::~grafo() {
    this->limpa();
}

void grafo::adicionarAresta(int u, int v) {

    Vetor<int> aux;

    aux = this->adjLista.GetElemento(v);

    aux.n++;

    aux.AdicionaElemento(u);

    this->adjLista.SetElemento(v, aux);

    aux = this->adjLista.GetElemento(u);

    aux.n++;

    aux.AdicionaElemento(v);

    this->adjLista.SetElemento(u, aux);

}

void grafo::removerAresta(int u, int v) {
    return;
}

bool grafo::verificaAresta(int u, int v) {
    return false;
}

void grafo::imprimeGrafo() {

    Vetor<int> aux;

    for (int i = 0; i < numVertices; ++i) {
        aux = this->adjLista.GetElemento(i);
        aux.Imprime();
    }

}

void grafo::limpa() {
    return;
}