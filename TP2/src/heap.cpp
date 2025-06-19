#include "heap.hpp"
#include "listaEncadeada.hpp"
#include <iostream>
#include <string>

using namespace std;

void heap::swap (int i, int j) {

    long long int aux = Heap.getItem(i);
    Heap.setItem(Heap.getItem(j), i);
    Heap.setItem(aux, j);

}

bool heap::isEmpty() {

    return Heap.size() == 0;
}

heap::heap() {}

int heap::getAncestralIndex (int i) {
    
    // return (i-1)/2; // 0-based

    if (i <= 1) return 0;
    return i / 2; // 1-based
}

int heap::getSucessorEsqIndex (int i) {
    return 2*i;
}

int heap::getSucessorDirIndex (int i) {
    return (2*i)+1;
}

bool heap::existeAncestral (int i) {
    return getAncestralIndex(i) >= 1;
}

bool heap::existeSucessorEsq (int i) {
    return getSucessorEsqIndex(i) <= Heap.size();
}

bool heap::existeSucessorDir (int i) {
    return getSucessorDirIndex(i) <= Heap.size();
}

// ajusta o heap para cima após inserção

void heap::heapifyUp() {

    int indexAtual = (Heap.size()); // Index do último elemento adicionado
    
    while (this->existeAncestral(indexAtual) && Heap.getItem(getAncestralIndex(indexAtual)) > Heap.getItem(indexAtual)) {
        
        swap(indexAtual, getAncestralIndex(indexAtual));
        indexAtual = getAncestralIndex(indexAtual);
        
    }

}

// ajusta o heap para baixo após uma remoção

void heap::heapifyDown () {

    int index = 1; // Começa da raiz
        int heapSize = Heap.size();

        while (true) {
            int leftChild = 2 * index;
            int rightChild = 2 * index + 1;
            int smallest = index;

            // Encontra o menor entre o pai e seus filhos
            if (leftChild <= heapSize && Heap.getItem(leftChild) < Heap.getItem(smallest)) {
                smallest = leftChild;
            }
            if (rightChild <= heapSize && Heap.getItem(rightChild) < Heap.getItem(smallest)) {
                smallest = rightChild;
            }

            // Se o menor não for o pai, troca e continua a descer
            if (smallest != index) {
                swap(index, smallest);
                index = smallest;
            } else {
                break; // A propriedade do heap foi restaurada
            }
        }
}

void heap::insert(long long int key) {

    Heap.insertInTheEnd(key);
    this->heapifyUp();
}

// sempre removemos a raiz
long long int heap::extractMin() {

    if (this->isEmpty()) {
            // cout << "Heap vazio!" << endl;
            return 0; // Ou lance uma exceção apropriada
        }

    long long int raiz = Heap.getItem(1); // O menor elemento é a raiz (índice 1)

    // Se há mais de um elemento real no heap (além da raiz que será removida)
    if (Heap.size() > 1) {
        // Passo 1: Mover o último elemento para a posição da raiz (índice 1)
        swap(1, Heap.size());

    Heap.removeLastOne();

        heapifyDown();
    } else {
        Heap.removeLastOne();
    }

    return raiz;

}

void heap::printHeap() {

    Heap.print();
}