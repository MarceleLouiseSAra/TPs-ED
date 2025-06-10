#include "heap.hpp"
#include "template.hpp"
#include <iostream>
#include <string>

using namespace std;

void heap::swap (int i, int j) {
    
    int aux = maxHeap.GetElemento(i);
    maxHeap.SetElemento(i, maxHeap.GetElemento(j));
    maxHeap.SetElemento(j, aux);

}

int heap::size() {

    return maxHeap.i;
}

bool heap::isEmpty() {

    return this->size() == 0;
}

heap::heap() {

    maxHeap = Vetor<int>(7);

}

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
    return getSucessorEsqIndex(i) < this->size();
}

bool heap::existeSucessorDir (int i) {
    return getSucessorDirIndex(i) < this->size();
}

// ajusta o heap para cima após inserção

void heap::heapifyUp() {

    int indexAtual = (this->size()-1); // Index do último elemento adicionado

    while (this->existeAncestral(indexAtual) && maxHeap.GetElemento(getAncestralIndex(indexAtual)) < maxHeap.GetElemento(indexAtual)) {

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
        if (existeSucessorDir(indexAtual) && maxHeap.GetElemento(getSucessorDirIndex(indexAtual)) > maxHeap.GetElemento(getSucessorEsqIndex(indexAtual))) {

            filhoMaior = maxHeap.GetElemento(getSucessorDirIndex(indexAtual));
        }

        // Se o elemento atual for maior ou igual a filhoMaior, o heap está correto 
        if (maxHeap.GetElemento(indexAtual) >= maxHeap.GetElemento(filhoMaior)) {

            break;
        } else { // caso contrário, trocam-se de lugar o elemento do index atual com o do index filhoMaior

            swap(indexAtual, filhoMaior);
            indexAtual = filhoMaior;
        }

    }

}

void heap::insert(int key) {

    maxHeap.AdicionaElemento(key);
    this->heapifyUp();
}

// sempre removemos a raiz
int heap::extractMax() {

    if (this->isEmpty()) {
        throw "Heap vazio!";
    }

    int raiz = maxHeap.GetElemento(0);

    swap(0, (this->size()-1));

    maxHeap.removeUltimoElemento();

    heapifyDown();

    return raiz;
    
}

void heap::printHeap() {

    maxHeap.Imprime();
}