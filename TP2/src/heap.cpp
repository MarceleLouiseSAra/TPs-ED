#include "heap.hpp"
#include "template.hpp"
#include <iostream>
#include <string>

using namespace std;

void heap::swap (int i, int j) {
    
    int aux = Heap.getItem(i);
    Heap.setItem(i, Heap.getItem(j));
    Heap.setItem(j, aux);

}

bool heap::isEmpty() {

    return Heap.size() == 0;
}

heap::heap() {}

int heap::getAncestralIndex (int i) {
    return (i-1)/2;
}

int heap::getSucessorEsqIndex (int i) {
    return (2*i)+1;
}

int heap::getSucessorDirIndex (int i) {
    return (2*i)+2;
}

bool heap::existeAncestral (int i) {
    return getAncestralIndex(i) >= 0;
}

bool heap::existeSucessorEsq (int i) {
    return getSucessorEsqIndex(i) < Heap.size();
}

bool heap::existeSucessorDir (int i) {
    return getSucessorDirIndex(i) < Heap.size();
}

// ajusta o heap para cima após inserção

void heap::heapifyUp() {

    int indexAtual = (Heap.size()-1); // Index do último elemento adicionado

    while (this->existeAncestral(indexAtual) && Heap.getItem(getAncestralIndex(indexAtual)) < Heap.getItem(indexAtual)) {

        swap(indexAtual, getAncestralIndex(indexAtual));
        indexAtual = getAncestralIndex(indexAtual);

    }
}

// ajusta o heap para baixo após uma remoção

void heap::heapifyDown () {

    int indexAtual = 0;

    // enquanto o nó tiver filhos  à esquerda

    while (getSucessorEsqIndex(indexAtual)) {

        int filhoMaior = getSucessorEsqIndex(indexAtual); // filhoMaior é o index do elemento à esquerda

        // verifica se o filho direito existe e se é maior que o irmão
        if (existeSucessorDir(indexAtual) && Heap.getItem(getSucessorDirIndex(indexAtual)) > Heap.getItem(getSucessorEsqIndex(indexAtual))) {

            filhoMaior = Heap.getItem(getSucessorDirIndex(indexAtual));
        }

        // Se o elemento atual for maior ou igual a filhoMaior, o heap está correto 
        if (Heap.getItem(indexAtual) >= Heap.getItem(filhoMaior)) {

            break;
        } else { // caso contrário, trocam-se de lugar o elemento do index atual com o do index filhoMaior

            swap(indexAtual, filhoMaior);
            indexAtual = filhoMaior;
        }

    }

}

void heap::insert(int key) {

    Heap.insertInTheEnd(key);
    this->heapifyUp();
}

// sempre removemos a raiz
int heap::extractMax() {

    if (this->isEmpty()) {
        cout << "Heap vazio!" << endl;
        return 0;
    }

    int raiz = Heap.getItem(0);

    swap(0, (Heap.size()-1));

    Heap.removeFirstOne();

    heapifyDown();

    return raiz;
    
}

void heap::printHeap() {

    Heap.print();
}