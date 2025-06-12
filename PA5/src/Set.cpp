#include "Set.hpp"
#include <iostream>
#include <string>

using namespace std;

StringSet::StringSet(int tamanho) : 
    tamanhoOriginal(tamanho),
    tamanhoTabela(tamanho),
    tamanhoConjunto(0) {

    if (tamanho <= 0) {
        throw "O tamanho da tabela deve ser maior ou igual a 1 (um).";
    }

    this->tabela = new ElementoTabela[tamanhoTabela];

    for (int i = 0; i < tamanhoTabela; i++) {
        tabela[i].vazio = true;
        tabela[i].retirada = false;
        tabela[i].dado = "";
    }

}

StringSet::~StringSet() {
    delete[] tabela;
}

int StringSet::Hash(string s) {

    long long hashVal = 0;
    const int primo = 31;

    for (char ch : s) {
        hashVal = (hashVal * primo + ch) % tamanhoTabela;
    }

    return static_cast<int>(hashVal);
}

int StringSet::proximoPrimo(int n) {

    if (n <= 1) {
        return 2;
    }

    int novoPrimo = n;

    bool found = false;

    while (!found) {

        novoPrimo++;

        for (int i = 2; i * i <= novoPrimo; ++i) {

            if (novoPrimo % i == 0) {

                break;
            }
        }

        if (novoPrimo) {
            
            found = true;
        }
    }

    return novoPrimo;

}

void StringSet::Resize(size_t novoTamanho) { // contém a lógica de rehash (encontrar o próximo slot em caso de colisão)

    novoTamanho = proximoPrimo(static_cast<int>(novoTamanho));

    ElementoTabela* antigaTabela = tabela;
    int antigoTamanho = tamanhoTabela;

    tamanhoTabela = static_cast<int>(novoTamanho);

    tabela = new ElementoTabela[tamanhoTabela];
    tamanhoConjunto = 0;

    for (int i = 0; i < tamanhoTabela; ++i) {
        tabela[i].vazio = true;
        tabela[i].retirada = false;
        tabela[i].dado = "";
    }

    // Reinserir todos os elementos da tabela antiga na nova tabela
    for (int i = 0; i < antigoTamanho; ++i) {
        if (!antigaTabela[i].vazio && !antigaTabela[i].retirada) {
            Inserir(antigaTabela[i].dado); // Usar a função Inserir para re-hashear
        }
    }

    delete[] antigaTabela;

}

void StringSet::Inserir(string s) {

    // Verificação do fator de carga para redimensionamento
    // Um fator de carga de 0.7 é um bom ponto de partida para endereçamento aberto
    // Indica o quão "cheia" a tabela está

    if (static_cast<double>(tamanhoConjunto) / tamanhoTabela >= 0.7) {
        Resize(tamanhoTabela * 2);
    }

    int indiceInicial = Hash(s);
    int indiceAtual = indiceInicial;
    int i = 0;

    do {
        
        if (tabela[indiceAtual].vazio || tabela[indiceAtual].retirada) {

            tabela[indiceAtual].dado = s;
            tabela[indiceAtual].vazio = false;
            tabela[indiceAtual].retirada = false;
            tamanhoConjunto++;
            return;
        }
    
        else if (tabela[indiceAtual].dado == s) {
            return;
        }

        i++;
        indiceAtual = (indiceInicial + i) % tamanhoTabela;

    } while (indiceAtual != indiceInicial);

}

void StringSet::Remover(string s) {

    int indiceInicial = Hash(s);
    int indiceAtual = indiceInicial;
    int i = 0;

    do {
        // Se houverem slots vazios, significa que a string não está na tabela
        if (tabela[indiceAtual].vazio) {
            return;
        }

        // Se encontrou a string e ela não foi retirada, marque retirada como true
        else if (tabela[indiceAtual].dado == s && !tabela[indiceAtual].retirada) {
            tabela[indiceAtual].retirada = true;
            tabela[indiceAtual].dado = "";
            tamanhoConjunto--;

            return;
        }

        i++;
        indiceAtual = (indiceInicial + i) % tamanhoTabela;

    } while (indiceAtual != indiceInicial);

}

bool StringSet::Pertence(string s) {

    int indiceInicial = Hash(s);
    int indiceAtual = indiceInicial;
    int i = 0;

    do {

        if (tabela[indiceAtual].vazio) {
            return false;
        }

        else if (tabela[indiceAtual].dado == s && !tabela[indiceAtual].retirada) {
            return true;
        }

        i++;
        indiceAtual = (indiceInicial + i) % tamanhoTabela;

    } while (indiceAtual != indiceInicial);

    return false;
}

StringSet* StringSet::Intersecao(StringSet* S) {

    StringSet* resultado = new StringSet(max(tamanhoConjunto, S->tamanhoConjunto));

    for (int i = 0; i < tamanhoTabela; ++i) {

        if (!tabela[i].vazio && !tabela[i].retirada) {

            if (S->Pertence(tabela[i].dado)) {
                resultado->Inserir(tabela[i].dado);
            }
        }
    }
    return resultado;
}

StringSet* StringSet::Uniao(StringSet* S) {

    StringSet* resultado = new StringSet(tamanhoConjunto + (*S).tamanhoConjunto);

    for (int i = 0; i < tamanhoTabela; ++i) {

        if (!tabela[i].vazio && !tabela[i].retirada) {
            resultado->Inserir(tabela[i].dado);
        }
    }
    
    for (int i = 0; i < S->tamanhoTabela; ++i) {

        if (!S->tabela[i].vazio && !S->tabela[i].retirada) {

            resultado->Inserir(S->tabela[i].dado);
        }
    }

    return resultado;

}

StringSet* StringSet::DiferencaSimetrica(StringSet* S) {

    StringSet* uniao = this->Uniao(S);
    StringSet* intersecao = this->Intersecao(S);
    StringSet* resultado = new StringSet((*uniao).tamanhoConjunto);

    for (int i = 0; i < uniao->tamanhoTabela; ++i) {
        if (!uniao->tabela[i].vazio && !uniao->tabela[i].retirada) {
            if (!intersecao->Pertence(uniao->tabela[i].dado)) {
                resultado->Inserir(uniao->tabela[i].dado);
            }
        }
    }

    delete uniao;
    delete intersecao;
    return resultado;
}

void StringSet::Imprimir() {

    bool controle = false;

    cout << "{ ";

    for (int i = 0; i < tamanhoTabela; ++i) {

        if (tabela[i].vazio) {

            cout << "";

        } else {

            if (controle) {
                cout << ", ";
            }

            cout << tabela[i].dado;

            controle = true;
        }

    }

    cout << " }" << endl;

}
