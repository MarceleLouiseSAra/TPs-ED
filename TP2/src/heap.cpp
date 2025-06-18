#include "heap.hpp"
#include "listaEncadeada.hpp"
#include <iostream>
#include <string>

using namespace std;

void heap::swap (int i, int j) {

    int aux = Heap.getItem(i);
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

    int indexAtual = 1;
    // enquanto o nó tiver filhos à esquerda

    while (getSucessorEsqIndex(indexAtual) <= Heap.size()) { // Adicionado <= Heap.size() para garantir que o filho esquerdo existe

        int filhoMenorIndex = getSucessorEsqIndex(indexAtual); // Agora busca pelo menor filho

        // verifica se o filho direito existe e se é MENOR que o irmão

        if (existeSucessorDir(indexAtual) && Heap.getItem(getSucessorDirIndex(indexAtual)) < Heap.getItem(filhoMenorIndex)) {
            filhoMenorIndex = this->getSucessorDirIndex(indexAtual);
        }

        // Se o elemento atual for MENOR ou igual a filhoMenorIndex, o heap está correto

        if (Heap.getItem(indexAtual) <= Heap.getItem(filhoMenorIndex)) {

            break;
        } else { // caso contrário, trocam-se de lugar o elemento do index atual com o do index filhoMenorIndex
            swap(indexAtual, filhoMenorIndex);
            indexAtual = filhoMenorIndex;
        }
    }
}

void heap::insert(int key) {

    Heap.insertInTheEnd(key);
    this->heapifyUp();
}

// sempre removemos a raiz
int heap::extractMin() {

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