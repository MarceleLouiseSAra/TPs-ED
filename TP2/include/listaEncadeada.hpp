#ifndef listaEncadeada_H
#define listaEncadeada_H
#include "node.hpp"
#include <string>

class listaEncadeada {
    private:
        int tam;
        node* firstOne;
        node* lastOne;
        node* position(int pos, bool previous);


    public:
    
        listaEncadeada();
        ~listaEncadeada();

        int getItem(int pos);
        void setItem(int item, int pos);
        void insertInTheBeginning(int item);
        void insertInTheEnd(int item);
        void insertAtPosition(int item, int pos);

        int removeFirstOne();
        int removeLastOne();
        int removePosition(int pos);

        int search(int key);

        void print();
        void clean();

};

#endif