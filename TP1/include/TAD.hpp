#ifndef TAD_H
#define TAD_H
#include "node.hpp"
#include <string>

class TAD {
    private:
        int tam;
        node* firstOne;
        node* lastOne;
        node* position(int pos, bool previous);


    public:
    
        TAD();
        ~TAD();

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