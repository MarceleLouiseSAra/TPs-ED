#ifndef node_H
#define node_H
#include <string>

class node {
    private:
        long long int item;
        node *next;


    public:
        node();

    friend class listaEncadeada;
    friend class pilhaEncadeada;
};

#endif