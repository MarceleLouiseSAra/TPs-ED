#ifndef pilhaEncadeada_H
#define pilhaEncadeada_H
#include "node.hpp"
#include <string>

class pilhaEncadeada {
    private:
        int tam;
        node* top;
        
    public:
        int armazem;
        int secao;
        
        pilhaEncadeada();
        pilhaEncadeada(int armazem, int secao);
        virtual ~pilhaEncadeada();
        bool isEmpty();

        void empilha(int item);
        int desempilha();
        void imprime();
        void limpa();
};

#endif