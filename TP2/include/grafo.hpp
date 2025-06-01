#ifndef grafo_H
#define grafo_H
#include "template.hpp"
#include <string>

class grafo {

    private:
        int numVertices;
        Vetor<Vetor<int>> adjLista; // Array de listas de adjacência

    public:
        grafo(int v);
        ~grafo();

        void adicionarAresta(int u, int v);
        void removerAresta(int u, int v);
        bool verificaAresta(int u, int v);
        void imprimeGrafo();
        void limpa();

};

#endif