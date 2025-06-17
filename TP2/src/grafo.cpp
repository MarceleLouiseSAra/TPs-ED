#include "grafo.hpp"
#include "template.hpp"
#include "pilhaEncadeada.hpp"
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

}

void grafo::removerAresta(int u, int v) {
    return;
}

bool grafo::verificaAresta(int u, int v) {

    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {

        Vetor<int> aux = this->adjLista.GetElemento(u);

        for (int i = 0; i < adjLista.n; i++) {
            
            if (aux.GetElemento(i) == v) {
                // cout << "A aresta " << u << " e " << v << " existe!" << endl;
                return true;
            }
        }

        return false; // 'v' não foi encontrado na lista de adjacência de 'u'
    }
}

void grafo::imprimeGrafo() {

    Vetor<int> aux;

    for (int i = 0; i < numVertices; i++) {
        aux = this->adjLista.GetElemento(i);
        aux.Imprime();
    }

}

void grafo::limpa() {
    return;
}