#ifndef heap_H
#define heap_H
#include "template.hpp"
#include <string>

class heap {

    private:

        Vetor<int> maxHeap; // maxHeap
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