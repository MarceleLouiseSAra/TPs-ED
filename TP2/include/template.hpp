#ifndef Vetor_H
#define Vetor_H

#include <iostream>
#include <string>

using namespace std;

template<typename T>

class Vetor {

    public:
    int i;
    int n;
    T *p;

    Vetor(){

        this->n = 0;
        this->i = 0;
        this->p = nullptr;
    }

    Vetor(int n){

        this->n = n;
        this->i = 0;
        this->p = new T[this->n];
    }

    void SetElemento(int i, T x) {
        if(i < this->n){
            p[i] = x;
        }
    }

    T GetElemento(int i){
        if(i < this->n){
            return this->p[i];
        }

        return 0;
    }

    void AdicionaElemento(T x){
        if(this->i < n){
            this->p[i] = x;
            this->i++;
        }
    }

    void removeUltimoElemento() {
        if(this->i < n){
            int *auxPointer;
            auxPointer = &p[i];
            delete auxPointer;
            this->i--;
        }
    }

    void Imprime(){

        for(int i = 0; i < this->n; i++){
            cout << this->p[i] << " ";
        }

        cout << "\n";
    }


};

#endif