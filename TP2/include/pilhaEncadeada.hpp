#ifndef pilhaEncadeada_H
#define pilhaEncadeada_H
#include "node.hpp"
#include <string>

class pilhaEncadeada {
    private:
        int tam;
        node* top;

    public:
        pilhaEncadeada();
        virtual ~pilhaEncadeada();
        bool isEmpty();

        void empilha(int item);
        int desempilha();
        void imprime();
        void limpa();
};

#endif