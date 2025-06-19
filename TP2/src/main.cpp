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
    int armazemInicial;
    int armazemAtual;
    int proximoArmazem;
    int armazemFinal;
    listaEncadeada rota;

} pacote;

typedef struct evento {

    long long int chave;

} evento;

string atualizaRelogio (int tempo) {

    ostringstream oss;
    oss << std::setw(7) << std::setfill('0') << tempo;

    return oss.str();
}

string criaChaveEventoPacote (int tempoChegada, int idpac) {

    ostringstream oss;
    oss << setw(6) << setfill('0') << tempoChegada; // tempo de chegade de pacote (6 dígitos) // como corresponde às primeiras dezenas, seta a ordem no escalonamento
    oss << setw(6) << setfill('0') << idpac; // id do pacote (6 dígitos)
    oss << "1"; // Tipo de Evento: Pacote
    return oss.str();
}

void escalonaEventoPostagemPacote (int numeroPacotes, Vetor<pacote> &pacotes, grafo &grafo, heap &minHeap) {

    // Para cada pacote a ser transportado
    // Calcula e armazena a rota do pacote

    for (int i = 0; i < numeroPacotes; i++) { // atribui rota a cada pacote

        grafo.buscaEmLargura(pacotes.GetElemento(i).armazemInicial, 
                             pacotes.GetElemento(i).armazemFinal,
                             pacotes.GetElemento(i).rota);

        // cout << "rota do pacote " << i << ": ";
        // pacotes.GetElemento(i).rota.print();
        // cout << endl;

        string chave = criaChaveEventoPacote(pacotes.GetElemento(i).tempochegada, pacotes.GetElemento(i).idpac);

        // Escalona a chegada de pacotes nos armazéns de postagem
        minHeap.insert(stoi(chave));
    }

}

int procuraPacote(int chave, Vetor<pacote> &pacotes, int numeroPacotes) {

    for (int i = 0; i < numeroPacotes; ++i) {
        if (pacotes.GetElemento(i).idpac == chave) {
            return i;
        }
    }

    return -1;
}

void empilhando (int indicePacote, int numeroPacotes, int numeroSecoes, int tempoAtual, Vetor<pacote> &pacotes, Vetor<pilhaEncadeada> &secoes) {

    // para cada armazém para cada rota de cada pacote, empilhar o pacote na seção referente ao próximo armazém no armazém atual

    pacotes.GetElemento(indicePacote).armazemAtual = pacotes.GetElemento(indicePacote).rota.removeFirstOne();

    for (int i = 0; i < numeroSecoes; i++) {   

        if (pacotes.GetElemento(indicePacote).armazemAtual == secoes.GetElemento(i).armazem 
            && secoes.GetElemento(i).secao == pacotes.GetElemento(indicePacote).rota.getItem(1)) {

            pacotes.GetElemento(indicePacote).proximoArmazem = pacotes.GetElemento(indicePacote).rota.getItem(1);

            secoes.GetElemento(indicePacote).empilha(pacotes.GetElemento(indicePacote).idpac);

            ostringstream tempoSS;
            tempoSS << setw(6) << setfill('0') << atualizaRelogio(tempoAtual);

            ostringstream pacoteSS;
            pacoteSS << setw(3) << setfill('0') << procuraPacote(pacotes.GetElemento(indicePacote).idpac, pacotes, numeroPacotes);

            ostringstream armazemSS;
            armazemSS << setw(3) << setfill('0') << secoes.GetElemento(i).armazem;

            ostringstream secaoSS;
            secaoSS << setw(3) << setfill('0') << secoes.GetElemento(i).secao;

            cout << tempoSS.str() << " pacote " << pacoteSS.str() << " armazenado em " << armazemSS.str() << " na secao " << secaoSS.str() << endl;
        }
    }
}

string criaChaveEventoTransporte (int tempo, int armazemInicial, int armazemFinal) {

    ostringstream oss;
    oss << setw(6) << setfill('0') << tempo; // tempo de início do transporte n (6 dígitos) // como corresponde às primeiras dezenas, seta a ordem no escalonamento
    oss << setw(3) << setfill('0') << armazemInicial; // armazém de origem (3 dígitos)
    oss << setw(3) << setfill('0') << armazemFinal; // armazém de destino (3 dígitos)
    oss << "2"; // tipo de evento: transporte

    return oss.str();
}

void registraEventoChegadaPacote (int numeroPacotes, int numeroSecoes, Vetor<pacote> &pacotes, Vetor<pilhaEncadeada> &secoes, int &tempoAtual, int latenciaTransporte, int indicePacote) {

    tempoAtual += latenciaTransporte;

    empilhando(indicePacote, numeroPacotes, numeroSecoes, tempoAtual, pacotes, secoes);

}

void escalonaEventoTransporte (int indicePacote, int numeroPacotes, Vetor<pacote> &pacotes, grafo &grafo, int &tempoAtual, int intervaloTransporte) {

    // intervaloTransporte (tempo entre o início de um transporte e o início de outro)
    tempoAtual += intervaloTransporte;

    // Para cada ligação entre dois armazéns
    for (int i = 0; i < numeroPacotes; i++) {

        for (int j = 2; j <= pacotes.GetElemento(i).rota.size(); j++ ) {

            if (grafo.verificaAresta(pacotes.GetElemento(i).rota.getItem(j-1), pacotes.GetElemento(i).rota.getItem(j))) {

                // Escalona evento de transporte // !!!!!! não necessariamente passa por todas as arestas, só por aquelas das rotas
                // minHeap.insert(stoi(criaChaveEventoTransporte(stoi(atualizaRelogio(tempoAtual)), pacotes.GetElemento(j).armazeminicial, pacotes.GetElemento(j).armazemfinal)));
                // stoi garrando!!!!!!!!!!!!

                // ostringstream tempoSS;
                // tempoSS << setw(6) << setfill('0') << atualizaRelogio(tempoAtual);

                // ostringstream pacoteSS;
                // pacoteSS << setw(3) << setfill('0') << i;

                // ostringstream armazemInicialSS;
                // armazemInicialSS << setw(3) << setfill('0') << pacotes.GetElemento(i).armazemInicial;

                // ostringstream proximoArmazemSS;
                // proximoArmazemSS << setw(3) << setfill('0') << pacotes.GetElemento(i).proximoArmazem;

                // cout << tempoSS.str() << " pacote " << pacoteSS.str() << " em transito de " << armazemInicialSS.str() << " para " << proximoArmazemSS.str() << endl;
            }
        }
    }
}

int escalonaEventoRemoção () {

    return 0;

}

void escalonaEventoArmazenamento () {



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
        pacoteAuxiliar.armazemInicial = armazeminicial_n;
        pacoteAuxiliar.armazemFinal = armazemfinal_n;

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

    // cria os eventos iniciais (armazenamentos)
    escalonaEventoPostagemPacote(numeroPacotes, pacotes, grafo, minHeap);
        
    // minHeap.printHeap();

    // Inicializa Condição de Término para FALSO
    bool fimEventos = false;
    long long int chaveProxEvento = 0;

    // Enquanto houver eventos ou seções não vazias
    while(!fimEventos) {

        // Remove o próximo evento do escalonador
        chaveProxEvento = minHeap.extractMin(); // extrai a raiz (evento há mais tempo no escalonador [chave do evento])

        // cout << "chaveProxEvento: " << chaveProxEvento << endl;

        if (chaveProxEvento == 0) { // "Heap está vazio!"
            fimEventos = true; // break while
        }

        // Avança o relógio para o instante do próximo evento
        tempoAtual = chaveProxEvento/10000000;

        // cout << "tempoAtual: " << tempoAtual << endl;

        // Se evento é transporte
        if (chaveProxEvento%10 == 2) {

            chaveProxEvento/=10;
    
            int primeroArmazem = chaveProxEvento % (1000);

            long long tempParaSegundoArmazem = chaveProxEvento / 1000;
            int segundoArmazem = tempParaSegundoArmazem % (1000);

            int tempo = chaveProxEvento/1000000;  

            // Se há pacotes na seção associada
            // if () {
                // Remove os pacotes mais antigos até a capacidade do transporte // 2
                for (int i = 0; i < 2; i++) {

                    // Escalona a chegada dos pacotes removidos no próximo armazém
                    // registraEventoChegadaPacote();
                }
            // }

            // Escalona o próximo evento de transporte
            // escalonaEventoTransporte(numeroPacotes, pacotes, grafo, tempoAtual, intervaloTransporte);
        }

        // Se evento é chegada de pacotes
        if (chaveProxEvento%10 == 1) {

            chaveProxEvento/=10;
            
            int pacote = chaveProxEvento % (1000000);
            int indicePacote = procuraPacote(pacote, pacotes, numeroPacotes);

            int tempo = chaveProxEvento/1000000;
            
            // Se pacote chegou ao destino final
            if (pacotes.GetElemento(indicePacote).rota.size() == 0) {
                
            // Registra entrega de pacote
                ostringstream tempoSS;
                tempoSS << setw(3) << setfill('0') << tempo;

                ostringstream indicePacoteSS;
                indicePacoteSS << setw(3) << setfill('0') << indicePacote;

                ostringstream indiceArmazemFinalSS;
                indiceArmazemFinalSS << setw(3) << setfill('0') << pacotes.GetElemento(indicePacote).armazemFinal;

                cout << tempoSS.str() << " pacote " << indicePacoteSS.str() << " " << "entregue em " << indiceArmazemFinalSS.str() << endl;
            
                // Senão chegou ao destino final
            } else {
                // Armazena o pacote na respectiva seção
                empilhando(indicePacote, numeroPacotes, numeroSecoes, tempoAtual, pacotes, secoes);

                // Escalona evento de transporte  
                escalonaEventoTransporte(indicePacote, numeroPacotes, pacotes, grafo, tempoAtual, intervaloTransporte);
            }

        }

        // Atualizar as estatísticas
    }

    // Fim
    // Gerar relatórios de estatísticas

    return 0;
}