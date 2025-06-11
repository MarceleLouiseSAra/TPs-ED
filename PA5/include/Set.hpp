#ifndef Set_HPP
#define Set_HPP

#include <bits/stdc++.h>
using namespace std;

typedef struct s_table_elem {
    string dado;
    bool vazio;
    bool retirada;

} ElementoTabela;

class StringSet {

    private:
        int tamanhoOriginal;
        int tamanhoTabela;
        int tamanhoConjunto;
        ElementoTabela* tabela;

        int Hash(string s);
        static int proximoPrimo(int n);
        void Resize(size_t novoTamanho);

    public:
        StringSet(int tamanho);
        ~StringSet();

        void Inserir(string s);
        void Remover(string s);
        bool Pertence(string s);
        
        StringSet* Intersecao(StringSet* S);
        StringSet* Uniao(StringSet* S);
        StringSet* DiferencaSimetrica(StringSet* S);

        void Imprimir();
};

#endif