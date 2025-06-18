#include "node.hpp"
#include "listaEncadeada.hpp"
#include "pilhaEncadeada.hpp"
#include "grafo.hpp"
#include "heap.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

using namespace std;

void testListaEncadeada(listaEncadeada &teste) {

    teste.insertInTheBeginning(2);

    teste.insertInTheBeginning(1);

    teste.insertInTheEnd(9);

    // teste.print(); // 1, 2, 9

    int x;
    x = teste.getItem(1); // 1
    // cout << x << endl;
    x = teste.getItem(2); // 2
    // cout << x << endl;
    x = teste.getItem(3); // 9
    // cout << x << endl;

    teste.setItem(8, 1);

    // teste.print(); // 8, 2, 9

    x = teste.getItem(1); // 8
    // cout << x << endl;

    teste.insertAtPosition(7, 1);

    teste.print(); // 7, 8, 2, 9

    x = teste.getItem(1); // 7
    cout << x << endl;

    teste.removeFirstOne();

    teste.print(); // 8, 2, 9

    teste.removeLastOne();

    teste.print(); // 8, 2

    teste.insertInTheEnd(3);

    teste.insertInTheBeginning(1);

    teste.print(); // 1, 8, 2, 3

    teste.removePosition(1); // 1

    teste.print(); // 8, 2, 3

}

void testPilhaEncadeada(pilhaEncadeada &teste) {
    
    teste.empilha(1);

    teste.empilha(2);

    teste.desempilha();

    teste.empilha(3);

    teste.imprime();
    
}

void testGrafo(grafo &teste){

    teste.adicionarAresta(2, 0);
    teste.adicionarAresta(5, 0);
    // Vértice 0 tem 2 vizinhos: 2 e 5

    teste.adicionarAresta(2, 1);
    teste.adicionarAresta(4, 1);
    teste.adicionarAresta(5, 1);
    // Vértice 1 tem 2 vizinhos: 2, 4 e 5

    teste.adicionarAresta(4, 2);
    // Vértice 2 tem 3 vizinhos: 0, 1 e 4

    teste.adicionarAresta(5, 3);
    // Vértice 3 tem 1 vizinho: 5

    // Vértice 4 tem 3 vizinhos: 1 e 2

    // Vértice 5 tem 3 vizinhos: 0, 1 e 3

    teste.imprimeGrafo();

}

void testaHeap(heap &teste) {

    teste.insert(13);
    teste.insert(15);
    teste.insert(8);
    teste.insert(23);
    teste.insert(21);
    teste.insert(9);
    teste.insert(2);

    teste.printHeap();
}

typedef struct pacote {

    int tempochegada;
    int idpac;
    int armazeminicial;
    int armazemfinal;
    listaEncadeada rota;

} pacote;

int main () {

    // listaEncadeada listaEncadeada;

    // testListaEncadeada(listaEncadeada);

    // pilhaEncadeada pilhaEncadeada1;

    // testPilhaEncadeada(pilhaEncadeada1);

    // grafo grafo1(6); // Grafo com 6 vértices

    // testGrafo(grafo1);

    // heap heap;

    // testaHeap(heap);

    string arq;
    cin >> arq;

    ifstream in(arq, fstream::in);
    if (!in.is_open()){
        return 1;
    }

    string aux;

    getline(in, aux, '\n');
    int capacidadeDeTransporte = stoi(aux);

    // cout << capacidadeDeTransporte << endl;

    getline(in, aux, '\n');
    int latenciaTransporte = stoi(aux);

    // cout << latenciaTransporte << endl;

    getline(in, aux, '\n');
    int intervaloTransporte = stoi(aux);

    // cout << intervaloTransporte << endl;

    getline(in, aux, '\n');
    int custoRemocao = stoi(aux);

    // cout << custoRemocao << endl;
    
    getline(in, aux, '\n');
    int numeroArmazens = stoi(aux);

    // cout << numeroArmazens << endl;

    grafo grafo(numeroArmazens);

    int numeroSecoes = 0;

    for (int i = 0; i < numeroArmazens; i++) {

        getline(in, aux, '\n');

        // cout << aux << endl;

        int j = -1;

        for (int k = 0; k < aux.size(); k++) {

            if (aux[k] != ' ') {
                j++;
            }
            
            if (aux[k] == '1') {
                
                // cout << "i: " << i << " j: " << j << endl;
                
                grafo.adicionarAresta(i, j);
                numeroSecoes++;
            }
        }
    }

    grafo.imprimeGrafo();

    getline(in, aux, '\n');
    int numeroPacotes = stoi(aux);

    // cout << numeroPacotes << endl;

    int tempochegada_n = 0;
    int idpac_n = 0;
    int armazeminicial_n = 0;
    int armazemfinal_n = 0;

    Vetor<pacote> pacotes(numeroPacotes);

    while(getline(in, aux, '\n')) {

        // cout << aux << endl;

        string dump;

        stringstream ss(aux);

        ss >> tempochegada_n;
        ss >> dump;
        ss >> idpac_n;
        ss >> dump;
        ss >> armazeminicial_n;
        ss >> dump;
        ss >> armazemfinal_n;
        ss >> dump;
        
        // cout << tempochegada_n << endl;
        // cout << idpac_n << endl;
        // cout << armazeminicial_n << endl;
        // cout << armazemfinal_n << endl;

        pacote pacoteAuxiliar;

        pacoteAuxiliar.tempochegada = tempochegada_n;
        pacoteAuxiliar.idpac = idpac_n;
        pacoteAuxiliar.armazeminicial = armazeminicial_n;
        pacoteAuxiliar.armazemfinal = armazemfinal_n;

        pacotes.AdicionaElemento(pacoteAuxiliar);
        
    }

    // pacote pacaux = pacotes.GetElemento(2);

    // cout << pacaux.idpac << endl;

    // cout << numeroSecoes << endl;

    Vetor<pilhaEncadeada> secoes(numeroSecoes);

    for (int i = 0; i < numeroArmazens; i++) {
        for (int j = 0; j < numeroArmazens; j++) {

            if (grafo.verificaAresta(i, j)) {
                
                pilhaEncadeada aux;
                aux.armazem = i;
                aux.secao = j;
                secoes.AdicionaElemento(aux);
            }

        }
    }

    
    for (int j = 0; j < numeroPacotes; j++) { // atribui rota a cada pacote
        
        cout << "pacotes.GetElemento(j).idpac: " << pacotes.GetElemento(j).idpac << endl;

        cout << "pacotes.GetElemento(j).armazeminicial: " << pacotes.GetElemento(j).armazeminicial << endl;

        cout << "pacotes.GetElemento(j).armazemfinal: " << pacotes.GetElemento(j).armazemfinal << endl;

        grafo.buscaEmLargura(pacotes.GetElemento(j).armazeminicial, 
                             pacotes.GetElemento(j).armazemfinal,
                             pacotes.GetElemento(j).rota);

        cout << "pacotes.GetElemento(j).rota.size(): " << pacotes.GetElemento(j).rota.size() << endl;

        cout << "rota deste pacote: ";

        pacotes.GetElemento(j).rota.print();

        cout << endl;
    }

    // for (int i = 0, k = 0; i < numeroPacotes, k < numeroSecoes; i++) {
    //     for (int j = 2; j < pacotes.GetElemento(i).rota.size(); j++) {

    //         pacotes.GetElemento(i).rota.getItem(j); // retorna o próximo armazem a ser acessado

    //         if (pacotes.GetElemento(i).rota.getItem(j) == secoes.GetElemento(k).secao) {
    //             secoes.GetElemento(k).empilha(pacotes.GetElemento(i).idpac);
    //         }
    //     }

    // }

    // for (int i = 0; i < numeroSecoes; i++) {
    //     cout << "pilha: " << i << endl;
    //     cout << "armazem da pilha: " << i << ": " << secoes.GetElemento(i).armazem<< endl;
    //     cout << "secao da pilha " << i << ": " << secoes.GetElemento(i).secao << endl;

    //     secoes.GetElemento(i).imprime();

    //     cout << endl;
    // }

    return 0;
}