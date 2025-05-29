#include "node.hpp"
#include "TAD.hpp"
#include <iostream>

using namespace std;

TAD::TAD() {
    this->tam = 0;
    this->firstOne = new node(); // item = -1 e next = nullptr
    this->lastOne = this->firstOne;
};

TAD::~TAD() {
    this->clean();
    delete this->firstOne;

    cout << "Destrutor foi chamado." << endl;

};

node* TAD::position(int pos, bool previous) { // Melhor caso: O(1); pior caso: O(n)

    if (pos > this->tam) {
        throw "ERRO: posição inválida!";
    }

    node* p;
    int i;

    p = this->firstOne->next;

    // posiciona o apontador na célula anterior à desejada
    for (i=1; i<pos; i++) {
        p = (*p).next;
    }

    // posiciona o apontador na célula propriamente dita se previous for true
    // e na célula anterior se previous for false
    if (!previous) {
        p = (*p).next;
    }

    return p;

};

int TAD::getItem(int pos) {
    node* p;

    p = this->position(pos, true);

    return (*p).item;

};

void TAD::setItem(int item, int pos) {
    node* p;

    p = this->position(pos, true);

    (*p).item = item;
};


void TAD::insertInTheBeginning(int item) {

    node* newNode;
    newNode = new node;
    (*newNode).item = item;

    (*newNode).next = (*firstOne).next;
    (*firstOne).next = newNode;

    if ((*newNode).next == NULL) {
        lastOne = newNode;
    }
    
    this->tam++;
};

void TAD::insertInTheEnd(int item) {

    node* newNode;
    newNode = new node;
    (*newNode).item = item;

    (*lastOne).next = newNode;
    lastOne = newNode;
    
    this->tam++;
};

void TAD::insertAtPosition(int item, int pos) {

    node* newNode;
    newNode = new node;
    (*newNode).item = item;

    node* p;
    p = position(pos-1, true);

    (*newNode).next = (*p).next;
    (*p).next = newNode;

    if ((*newNode).next == NULL) {
        lastOne = newNode;
    }

    this->tam++;

};

int TAD::removeFirstOne() {
    
    int aux;
    node* p;

    if (this->tam == 0) {
        throw "ERROR: Lista vazia!";
    }

    p = (*firstOne).next;
    (*firstOne).next = (*p).next;
    this->tam--;

    if ((*firstOne).next == NULL) {
        lastOne = firstOne;
    }

    aux = (*p).item;
    delete p;
    
    return aux;
};

int TAD::removeLastOne() {

    int aux;
    node* p;

    if (this->tam == 0) {
        throw "ERROR: Lista vazia!";
    }

    p = position(this->tam-2, true);
    
    (*p).next = NULL;
    aux = (*lastOne).item;
    lastOne = p;

    this->tam--;
    return aux;
};

int TAD::removePosition(int pos) {
    
    int aux;
    node *p, *q;

    if (this->tam == 0) {
        throw "ERROR: Lista vazia!";
    }

    p = position(pos-1, true);

    q = (*p).next;
    (*p).next = (*q).next;
    
    aux = (*q).item;

    if ((*p).next == NULL) {
        lastOne = p;
    }

    this->tam--;
    return aux;
};

int TAD::search(int key) {
    return 0;
};

void TAD::print() {

    node* p;

    p = (*firstOne).next;

    while (p != NULL) {
        // cout << "(*p).item: " << (*p).item << " ";
        cout <<  (*p).item << " ";
        p = (*p).next;
    }

    cout << endl;

};

void TAD::clean() {

    node* p;

    p = (*firstOne).next;

    while (p != NULL) {
        (*firstOne).next = (*p).next;
        delete p;
        p = (*firstOne).next;
    }

    lastOne = firstOne;
    this->tam = 0;

};