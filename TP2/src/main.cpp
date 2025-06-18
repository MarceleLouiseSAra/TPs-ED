#include "node.hpp"
#include "listaEncadeada.hpp"
#include "pilhaEncadeada.hpp"
#include "grafo.hpp"
#include "heap.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <sstream>

using namespace std;

typedef struct pacote {

    int tempochegada;
    int idpac;
    int armazeminicial;
    int armazemfinal;
    listaEncadeada rota;

} pacote;

typedef struct evento {

    long long int chave;

} evento;

string criaChaveEventoPacote (int tempoChegada, int idpac) {
    ostringstream oss;
    oss << setw(6) << setfill('0') << tempoChegada; // tempo de chegade de pacote (6 dígitos) // como corresponde às primeiras dezenas, seta a ordem no escalonamento
    oss << setw(6) << setfill('0') << idpac; // id do pacote (6 dígitos)
    oss << "1"; // Tipo de Evento: Pacote
    return oss.str();
}

void escalonaEventoPacote (int numeroPacotes, Vetor<pacote> &pacotes, grafo &grafo, heap &minHeap) {

    for (int j = 0; j < numeroPacotes; j++) { // atribui rota a cada pacote

        grafo.buscaEmLargura(pacotes.GetElemento(j).armazeminicial, 
                             pacotes.GetElemento(j).armazemfinal,
                             pacotes.GetElemento(j).rota);

                             // cout << "pacotes.GetElemento(j).rota.size(): " << pacotes.GetElemento(j).rota.size() << endl;

        cout << "rota do pacote " << j << ": ";

        pacotes.GetElemento(j).rota.print();

        // cout << stoi(criaChaveEventoPacote(pacotes.GetElemento(j).tempochegada, pacotes.GetElemento(j).idpac)) << endl; // chave do evento de armazenamento

        // Escalona a chegada de pacotes nos armazéns de postagem // !!!!
        minHeap.insert(stoi(criaChaveEventoPacote(pacotes.GetElemento(j).tempochegada, pacotes.GetElemento(j).idpac)));

        cout << endl;
    }

}

string atualizaRelogio (int tempo) {
    ostringstream oss;
    oss << std::setw(7) << std::setfill('0') << tempo;
    return oss.str();
}

string criaChaveEventoTransporte (int tempo, int armazemInicial, int armazemFinal) {
    ostringstream oss;
    oss << setw(6) << setfill('0') << tempo; // tempo de início do transporte n (6 dígitos) // como corresponde às primeiras dezenas, seta a ordem no escalonamento
    oss << setw(3) << setfill('0') << armazemInicial; // armazém de origem (3 dígitos)
    oss << setw(3) << setfill('0') << armazemFinal; // armazém de destino (3 dígitos)
    oss << "2"; // Tipo de Evento: Transporte
    return oss.str();
}

void escalonaEventoTransporte (int numeroPacotes, Vetor<pacote> &pacotes, grafo &grafo, int tempoAtual, int intervaloTransporte) {

    // Para cada ligação entre dois armazéns // verificaAresta
    for (int j = 0; j < numeroPacotes; j++) {

        // tempoAtual = tempo de chegada do primeiro pacote
        tempoAtual = pacotes.GetElemento(0).tempochegada;

        for (int i = 2; i <= pacotes.GetElemento(j).rota.size(); i++ ) {

            if (grafo.verificaAresta(pacotes.GetElemento(j).rota.getItem(i-1), pacotes.GetElemento(j).rota.getItem(i))) {

                // cout << "entrei no if" << endl;

                // Escalona evento de transporte // !!!!!! não necessariamente passa por todas as arestas, só por aquelas das rotas
                // n pacotes são removidos de uma mesma seção de um mesmo armazém sequencialmente (98, 101)

                //latenciaTransporte (tempo transporte [20]) (soma 20 ao clock)
                tempoAtual += intervaloTransporte;

                cout << "tempo em que o pacote " << j << " sai no armazém " << pacotes.GetElemento(j).rota.getItem(i-1) << ": " << atualizaRelogio(tempoAtual) << endl;

                // minHeap.insert(stoi(criaChaveEventoTransporte(stoi(atualizaRelogio(tempoAtual)), pacotes.GetElemento(j).armazeminicial, pacotes.GetElemento(j).armazemfinal)));

                // intervaloTransporte (tempo entre o início de um transporte e o início de outro [110]) (soma 110 ao clock)
            }
        }
    }
}

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

    // simulação de eventos discretos 

    // Inicializa as variáveis de estado do sistema // leitura da entrada, criação dos vetores auxiliares de pacotes e secoes

    heap minHeap;
    
    // Inicializa o Relógio (usualmente zero)
    int tempoAtual = 0;
    
    // Para cada pacote a ser transportado
        // Calcula e armazena a rota do pacote

    escalonaEventoPacote(numeroPacotes, pacotes, grafo, minHeap);

    // Escalona evento de transporte    
    escalonaEventoTransporte (numeroPacotes, pacotes, grafo, tempoAtual, intervaloTransporte);

    // minHeap.printHeap();

    // Inicializa Condição de Término para FALSO
    bool fimEventos = false;

    // Enquanto houver eventos ou seções não vazias // !!!!!!!!!!!!
    // while(fimEventos) {

    //     // Remove o próximo evento do escalonador
    //     int chaveProxEvento = minHeap.extractMin(); // extrai a raiz (evento há mais tempo no escalonador [chave do evento])

    //     if (chaveProxEvento == 0) { // "Heap está vazio!"
    //         fimEventos = true; // break while
    //     }

        // Avança o relógio para o instante do próximo evento
        // clock = atualizaRelogio(0);

        // Se evento é transporte

            // Se há pacotes na seção associada
                // Remove os pacotes mais antigos até a capacidade do transporte // 2
                // Escalona a chegada dos pacotes removidos no próximo armazém
            // Escalona o próximo evento de transporte

        // Se evento é chegada de pacotes

            // Se pacote chegou ao destino final
                // Registra entrega de pacote
            // Senão chegou ao destino final
                // Armazena o pacote na respectiva seção

                // empilhando:
                // para cada armazém para cada rota de cada pacote, empilhar o pacote na seção referente ao próximo armazém no armazém atual

                // for (int i = 0, k = 0; i < numeroPacotes, k < numeroSecoes; i++) {
                //     for (int j = 2; j < pacotes.GetElemento(i).rota.size(); j++) {

                //         pacotes.GetElemento(i).rota.getItem(j); // retorna o próximo armazem a ser acessado

                //         if (pacotes.GetElemento(i).rota.getItem(j) == secoes.GetElemento(k).secao) {
                //             secoes.GetElemento(k).empilha(pacotes.GetElemento(i).idpac);
                //         }
                //     }

                // }

                // lógica do vetor auxiliar "secoes":
                // pilhas de 0 a n, cada pilha m é uma seção de um armazém k

                // for (int i = 0; i < numeroSecoes; i++) {
                //     cout << "pilha: " << i << endl;
                //     cout << "armazem da pilha: " << i << ": " << secoes.GetElemento(i).armazem << endl;
                //     cout << "secao da pilha " << i << ": " << secoes.GetElemento(i).secao << endl;

                //     secoes.GetElemento(i).imprime();

                //     cout << endl;
                // }

        // Atualizar as estatísticas
    // }

    // Fim
    // Gerar relatórios de estatísticas

    return 0;
}