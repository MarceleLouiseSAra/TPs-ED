#ifndef heap_H
#define heap_H
#include "listaEncadeada.hpp"
#include "template.hpp"
#include <string>

class heap {

    private:

        listaEncadeada Heap; // maxHeap
        void swap(int i, int j);
        bool existeAncestral(int i);
        bool existeSucessorEsq(int i);
        bool existeSucessorDir(int i);
        int getAncestralIndex(int i);
        int getSucessorEsqIndex(int i);
        int getSucessorDirIndex(int i);
        void heapifyDown();
        void heapifyUp();

    public:

        heap();
        bool isEmpty();
        int size();
        void insert(int key);
        int extractMax();
        void printHeap();
    
};

#endif