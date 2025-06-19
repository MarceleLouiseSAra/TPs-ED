#include "grafo.hpp"
#include "template.hpp"
#include "pilhaEncadeada.hpp"
#include "listaEncadeada.hpp"
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

void grafo::buscaEmLargura(int origem, int destino, listaEncadeada &rota) {

    // cout << "entrei em busca" << endl;

    if (origem < 0 || origem >= numVertices ||
        destino < 0 || destino >= numVertices) {

        return;
    }

    Vetor<bool> visitado(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        visitado.SetElemento(i, false);
    }

    Vetor<int> antecessor(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        antecessor.SetElemento(i, -1);
    }

    listaEncadeada aux;

    visitado.SetElemento(origem, true);
    aux.insertInTheEnd(origem);

    // cout << "rota.size(): " << rota.size() << endl;

    bool destinoEncontrado = false;

    while (!destinoEncontrado) {

        // cout << "rota.size(): " << rota.size() << endl;
        int u = aux.getItem(1); // pega o primeiro armazém (armazém de origem)
        aux.removeFirstOne();

        // cout << "rota.size(): " << rota.size() << endl;

        // cout << "u: " << u << endl;

        if (u == destino) {
            destinoEncontrado = true;
            break;
        }

        // cout << "adjLista.GetElemento(u).n: " << adjLista.GetElemento(u).n << endl;

        Vetor<int> vizinhosDeU = adjLista.GetElemento(u);

        for (int j = 0; j < vizinhosDeU.n; j++) {

            int v = vizinhosDeU.GetElemento(j);

            // cout << "v: " << v << endl;

            // cout << "visitado.GetElemento(v): " << visitado.GetElemento(v) << endl;

            if (!visitado.GetElemento(v)) {
                visitado.SetElemento(v, true);
                antecessor.SetElemento(v, u);
                aux.insertInTheEnd(v);
            }
        }

        // i++;
    }

    // cout << "aux: ";
    // aux.print();

    // cout << "antecessor: ";
    // antecessor.Imprime();

    listaEncadeada caminhoTemp; // Uma lista temporária para construir o caminho invertido

    if (destinoEncontrado) {
        
        // cout << "entrei do id de caminhoTemp" << endl;

        int atual = destino;

        // Percorre de volta do destino para a origem usando o array antecessor
        while (atual != -1) {
            caminhoTemp.insertInTheBeginning(atual); // Insere no início para obter a ordem correta
            atual = antecessor.GetElemento(atual);
        }

        // cout << "caminhoTemp.size(): ";
        // cout << caminhoTemp.size() << endl;

        // cout << "caminhoTemp: " << endl;
        // caminhoTemp.print();

        for (int i = 1; i <= caminhoTemp.size(); ++i) {
            rota.insertInTheEnd(caminhoTemp.getItem(i));
        }

        // cout << "saí do id de caminhoTemp" << endl;

    }

    // cout << "caminhoTemp: " << endl;
    // caminhoTemp.print();

    // cout << "rota: " << endl;
    // rota.print();

    // cout << "sai de busca" << endl;

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

    }
    
    return false; // 'v' não foi encontrado na lista de adjacência de 'u'
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