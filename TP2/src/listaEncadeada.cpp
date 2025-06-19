#include "node.hpp"
#include "listaEncadeada.hpp"
#include <iostream>

using namespace std;

listaEncadeada::listaEncadeada() {
    this->tam = 0;
    this->firstOne = new node(); // item = -1 e next = nullptr
    this->lastOne = this->firstOne;
};

listaEncadeada::listaEncadeada(const listaEncadeada& other) {
    // Inicializa a nova lista como vazia
    this->firstOne = new node(); // Cria um novo nó sentinela
    this->firstOne->item = 0; // Se firstOne armazena um valor irrelevante (sentinela)
    this->firstOne->next = NULL;
    this->lastOne = this->firstOne;
    this->tam = 0;

    // Percorre a lista 'other' e copia cada elemento para 'this'
    node* currentOther = other.firstOne->next; // Começa do primeiro nó de dados da outra lista
    while (currentOther != NULL) {
        this->insertInTheEnd(currentOther->item); // Usa seu método existente para adicionar elementos
        currentOther = currentOther->next;
    }
}

listaEncadeada& listaEncadeada::operator=(const listaEncadeada& other) {
    // 1. Lidar com autoatribuição (a = a)
    if (this == &other) {
        return *this;
    }

    // 2. Liberar recursos antigos da lista atual
    this->clean(); // Reutiliza seu método clean para liberar os nós existentes
    // Se clean() não deleta 'firstOne', então 'firstOne' ainda está válido, mas aponta para NULL

    // 3. Copiar os elementos da lista 'other' (cópia profunda)
    node* currentOther = other.firstOne->next; // Começa do primeiro nó de dados da outra lista
    while (currentOther != NULL) {
        this->insertInTheEnd(currentOther->item); // Usa seu método existente para adicionar elementos
        currentOther = currentOther->next;
    }

    return *this;
}

listaEncadeada::~listaEncadeada() {

    this->clean();
    delete this->firstOne;

    // cout << "Destrutor foi chamado." << endl;

};

int listaEncadeada::size() {
    return this->tam;
}

node* listaEncadeada::position(int pos, bool previous) { // Melhor caso: O(1); pior caso: O(n)


    if (pos > this->tam) {
        cout << "ERRO: posição inválida!";
    }

    node* p;
    int i;

    p = this->firstOne;

    // posiciona o apontador na célula anterior à desejada
    for (i=1; i<pos; i++) {
        p = (*p).next;
    }

    if (!previous) {
        p = (*p).next;
    }

    return p;

};

long long int listaEncadeada::getItem(int pos) {
    node* p;


    p = this->position(pos, false);

    return (*p).item;

};

void listaEncadeada::setItem(long long int item, int pos) {
    node* p;

    p = this->position(pos, false);

    (*p).item = item;
};


void listaEncadeada::insertInTheBeginning(int item) {

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

void listaEncadeada::insertInTheEnd(long long int item) {

    node* newNode;
    newNode = new node;
    (*newNode).item = item;

    (*lastOne).next = newNode;
    lastOne = newNode;
    
    this->tam++;
};

void listaEncadeada::insertAtPosition(long long int item, int pos) {

    node* newNode;
    newNode = new node;
    (*newNode).item = item;

    node* p;
    p = position(pos, true);

    (*newNode).next = (*p).next;
    (*p).next = newNode;

    if ((*newNode).next == NULL) {
        lastOne = newNode;
    }

    this->tam++;

};

int listaEncadeada::removeFirstOne() {
    
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

int listaEncadeada::removeLastOne() {

    int aux;
    node* p;

    if (this->tam == 0) {
        throw "ERROR: Lista vazia!";
    }

    p = position(this->tam, true);
    
    (*p).next = NULL;
    aux = (*lastOne).item;
    lastOne = p;

    this->tam--;
    return aux;
};

int listaEncadeada::removePosition(int pos) {
    
    int aux;
    node *p, *q;

    // cout << "antes de throw" << endl;

    if (this->tam == 0) {
        throw "ERROR: Lista vazia!";
    }

    // cout << "depois de throw" << endl;

    p = position(pos, true);

    q = (*p).next;
    (*p).next = (*q).next;
    
    aux = (*q).item;

    if ((*p).next == NULL) {
        lastOne = p;
    }

    this->tam--;
    return aux;
};

int listaEncadeada::search(int key) {
    return 0;
};

void listaEncadeada::print() {

    node* p;

    p = (*firstOne).next;

    while (p != NULL) {
        // cout << "(*p).item: " << (*p).item << " ";
        cout <<  (*p).item << " ";
        p = (*p).next;
    }

    cout << endl;

};

void listaEncadeada::clean() {

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