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

typedef struct pacote {

    int tempochegada;
    int idpac;
    int armazeminicial;
    int armazemfinal;
    listaEncadeada rota;

} pacote;

void empilhaPacote(pacote pacote, Vetor<pilhaEncadeada> &secoes) {

}

int main () {

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

    // grafo.imprimeGrafo();

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
        
        // cout << "pacotes.GetElemento(j).idpac: " << pacotes.GetElemento(j).idpac << endl;

        // cout << "pacotes.GetElemento(j).armazeminicial: " << pacotes.GetElemento(j).armazeminicial << endl;

        // cout << "pacotes.GetElemento(j).armazemfinal: " << pacotes.GetElemento(j).armazemfinal << endl;

        grafo.buscaEmLargura(pacotes.GetElemento(j).armazeminicial, 
                             pacotes.GetElemento(j).armazemfinal,
                             pacotes.GetElemento(j).rota);

        // cout << "pacotes.GetElemento(j).rota.size(): " << pacotes.GetElemento(j).rota.size() << endl;

        cout << "rota do pacote " << j << ": ";

        pacotes.GetElemento(j).rota.print();

        cout << endl;
    }

    // empilhando

    // para cada armazém para cada rota de cada pacote, empilhar o pacote na seção referente ao próximo armazém no armazém atual

    // simulação de eventos discretos 

    // Inicializa Condição de Término para FALSO
    // Inicializa as variáveis de estado do sistema
    // Inicializa o Relógio (usualmente zero)
    // Para cada ligação entre dois armazéns
        // Escalona evento de transporte
    // Para cada pacote a ser transportado
        // Calcula e armazena a rota do pacote
        // Escalona a chegada de pacotes nos armazéns de postagem
    // Enquanto houver eventos ou seções não vazias
        // Remove o próximo evento do escalonador
        // Avança o relógio para o instante do próximo evento
        // Se evento é transporte
            // Se há pacotes na seção associada
                // Remove os pacotes mais antigos até a capacidade do transporte
                // Escalona a chegada dos pacotes removidos no próximo armazém
            // Escalona o próximo evento de transporte
        // Se evento é chegada de pacotes
            // Se pacote chegou ao destino final
                // Registra entrega de pacote
            // Senão chegou ao destino final
                // Armazena o pacote na respectiva seção
        // Atualizar as estatísticas
    // Fim
    // Gerar relatórios de estatísticas

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