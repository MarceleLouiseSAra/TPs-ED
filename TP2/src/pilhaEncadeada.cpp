#include "node.hpp"
#include "pilhaEncadeada.hpp"
#include <iostream>

using namespace std;

pilhaEncadeada::pilhaEncadeada() {
    this->top = nullptr;
};

pilhaEncadeada::pilhaEncadeada(int armazem, int secao) {
    this->armazem = armazem;
    this->secao = secao;
}

pilhaEncadeada::~pilhaEncadeada() {
    this->limpa();
};

int pilhaEncadeada::size() {
    return this->tam;
}

bool pilhaEncadeada::isEmpty() {
    return (this->top == NULL); // se o ponteiro para node "top" apontar para NULL, retorna true
}

void pilhaEncadeada::empilha(int item) {
    
    node* newNode;
    
    newNode = new node;
    
    (*newNode).item = item;
    (*newNode).next = top;
    this->top = newNode;
    
    this->tam++;
};

int pilhaEncadeada::desempilha() {
    int aux;
    node* p;

    if (this->tam == 0) {
        throw "A pilha está vazia!";
    }

    aux = (*top).item;
    p = top;
    top = (*top).next;
    delete p;
    this->tam--;

    return aux;

};

void pilhaEncadeada::imprime() {
    if (isEmpty()) {
        cout << "A pilha está vazia!" << endl;
    }

    node* aux;
    aux = top;

    while (aux != NULL) {
        cout << (*aux).item << " ";
        aux = (*aux).next;
    }

    cout << endl;

}

void pilhaEncadeada::limpa() {
    while(!isEmpty()) {
        this->desempilha();
    }
};