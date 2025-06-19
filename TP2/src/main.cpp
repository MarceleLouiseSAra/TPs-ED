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
    oss << "1"; // Tipo de Evento: Pacote para armazenamento inicial
    return oss.str();
}

string criaChaveEventoTransporte (int tempo, int armazemInicial, int armazemFinal) {

    ostringstream oss;
    oss << setw(6) << setfill('0') << tempo; // tempo de início do transporte n (6 dígitos) // como corresponde às primeiras dezenas, seta a ordem no escalonamento
    oss << setw(3) << setfill('0') << armazemInicial; // armazém de origem (3 dígitos)
    oss << setw(3) << setfill('0') << armazemFinal; // armazém de destino (3 dígitos)
    oss << "2"; // tipo de evento: transporte (remoção e trânsito)

    return oss.str();
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

    // Certifica-se de que o pacote ainda tem uma rota para seguir
    if (pacotes.GetElemento(indicePacote).rota.size() > 0) {
        // O armazém atual do pacote é o próximo da rota
        pacotes.GetElemento(indicePacote).armazemAtual = pacotes.GetElemento(indicePacote).rota.removeFirstOne();

        // Se ainda há elementos na rota após remover o primeiro, define o próximo armazém
        if (pacotes.GetElemento(indicePacote).rota.size() > 0) {
            pacotes.GetElemento(indicePacote).proximoArmazem = pacotes.GetElemento(indicePacote).rota.getItem(0); 
        } else {
            // Se não há mais elementos na rota, o pacote chegou ao destino final
            pacotes.GetElemento(indicePacote).proximoArmazem = -1;
        }
    } else {
        // Se a rota já está vazia, o pacote já chegou ou não tem rota
        return;
    }

    // Procura a seção correta para empilhar o pacote
    for (int i = 0; i < numeroSecoes; i++) {   
        if (pacotes.GetElemento(indicePacote).armazemAtual == secoes.GetElemento(i).armazem 
            && secoes.GetElemento(i).secao == pacotes.GetElemento(indicePacote).proximoArmazem) { 

            secoes.GetElemento(i).empilha(pacotes.GetElemento(indicePacote).idpac);

            ostringstream tempoSS;
            tempoSS << setw(6) << setfill('0') << atualizaRelogio(tempoAtual);

            ostringstream pacoteSS;
            pacoteSS << setw(3) << setfill('0') << procuraPacote(pacotes.GetElemento(indicePacote).idpac, pacotes, numeroPacotes);

            ostringstream armazemSS;
            armazemSS << setw(3) << setfill('0') << secoes.GetElemento(i).armazem;

            ostringstream secaoSS;
            secaoSS << setw(3) << setfill('0') << secoes.GetElemento(i).secao;

            cout << tempoSS.str() << " pacote " << pacoteSS.str() << " armazenado em " << armazemSS.str() << " na secao " << secaoSS.str() << endl;
            return; // Pacote empilhado, sair da função
        }
    }
}

void registraEventoRemocao (int indicePacote, int numeroPacotes, int numeroSecoes, int tempoAtual, Vetor<pacote> &pacotes) { // Removido secoes, não é usado aqui

    ostringstream tempoSS;
    tempoSS << setw(6) << setfill('0') << atualizaRelogio(tempoAtual);

    ostringstream pacoteSS;
    pacoteSS << setw(3) << setfill('0') << procuraPacote(pacotes.GetElemento(indicePacote).idpac, pacotes, numeroPacotes);

    ostringstream armazemSS;
    armazemSS << setw(3) << setfill('0') << pacotes.GetElemento(indicePacote).armazemAtual;

    ostringstream secaoSS;
    secaoSS << setw(3) << setfill('0') << pacotes.GetElemento(indicePacote).proximoArmazem;

    cout << tempoSS.str() << " pacote " << pacoteSS.str() << " removido de " << armazemSS.str() << " na secao " << secaoSS.str() << endl;
}

void registraEventoTransito (int indicePacote, int numeroPacotes, int tempoAtual, Vetor<pacote> &pacotes) {

    ostringstream tempoSS;
    tempoSS << setw(6) << setfill('0') << atualizaRelogio(tempoAtual);

    ostringstream pacoteSS;
    pacoteSS << setw(3) << setfill('0') << indicePacote;

    ostringstream armazemInicialSS; 
    armazemInicialSS << setw(3) << setfill('0') << pacotes.GetElemento(indicePacote).armazemAtual; // Agora é o armazém de onde ele está saindo

    ostringstream proximoArmazemSS;
    proximoArmazemSS << setw(3) << setfill('0') << pacotes.GetElemento(indicePacote).proximoArmazem;

    cout << tempoSS.str() << " pacote " << pacoteSS.str() << " em transito de " << armazemInicialSS.str() << " para " << proximoArmazemSS.str() << endl;

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

    getline(in, aux, '\n');
    int latenciaTransporte = stoi(aux);

    getline(in, aux, '\n');
    int intervaloTransporte = stoi(aux);

    getline(in, aux, '\n');
    int custoRemocao = stoi(aux);
    
    getline(in, aux, '\n');
    int numeroArmazens = stoi(aux);

    grafo grafo(numeroArmazens);

    int numeroSecoes = 0;

    for (int i = 0; i < numeroArmazens; i++) {

        getline(in, aux, '\n');

        int j = -1;

        for (int k = 0; k < aux.size(); k++) {

            if (aux[k] != ' ') {
                j++;
            }
            
            if (aux[k] == '1') {
                
                grafo.adicionarAresta(i, j);
                numeroSecoes++;
            }
        }
    }

    getline(in, aux, '\n');
    int numeroPacotes = stoi(aux);

    int tempochegada_n = 0;
    int idpac_n = 0;
    int armazeminicial_n = 0;
    int armazemfinal_n = 0;

    Vetor<pacote> pacotes(numeroPacotes);

    while(getline(in, aux, '\n')) {

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
        
        pacote pacoteAuxiliar;

        pacoteAuxiliar.tempochegada = tempochegada_n;
        pacoteAuxiliar.idpac = idpac_n;
        pacoteAuxiliar.armazemInicial = armazeminicial_n;
        pacoteAuxiliar.armazemFinal = armazemfinal_n;

        pacotes.AdicionaElemento(pacoteAuxiliar);
        
    }

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

    heap minHeap;
    long long int tempoAtual = 0;

    // Escalona os eventos de postagem iniciais
    for (int i = 0; i < numeroPacotes; i++) {
        grafo.buscaEmLargura(pacotes.GetElemento(i).armazemInicial, 
                             pacotes.GetElemento(i).armazemFinal,
                             pacotes.GetElemento(i).rota);
        
        string chave_str = criaChaveEventoPacote(pacotes.GetElemento(i).tempochegada, pacotes.GetElemento(i).idpac);
        long long int chave = stoll(chave_str);
        minHeap.insert(chave);
    }
        
    bool fimEventos = false;
    long long int chaveProxEvento = 0;

    while(!fimEventos) {

        chaveProxEvento = minHeap.extractMin(); 

        if (chaveProxEvento == 0) { 
            fimEventos = true; 
            continue; 
        }

        tempoAtual = chaveProxEvento/10000000;

        // Se evento é de transporte (remoção e trânsito)
        if (chaveProxEvento%10 == 2) {

            chaveProxEvento/=10;
            int armazemDestino = chaveProxEvento % (1000); 
            long long tempParaArmazemOrigem = chaveProxEvento / 1000; 
            int armazemOrigem = tempParaArmazemOrigem % (1000); 

            // Simula a remoção e trânsito para os pacotes nessa seção
            for (int i = 0; i < numeroSecoes; i++) {
                if (secoes.GetElemento(i).armazem == armazemOrigem &&
                    secoes.GetElemento(i).secao == armazemDestino) {
                    
                    int pacotesTransportados = 0;
                    while (!secoes.GetElemento(i).isEmpty() && pacotesTransportados < capacidadeDeTransporte) {
                        
                        int pacote_id = secoes.GetElemento(i).desempilha();
                        int indicePacote = procuraPacote(pacote_id, pacotes, numeroPacotes);
                        
                        // Registra a remoção
                        registraEventoRemocao(indicePacote, numeroPacotes, numeroSecoes, tempoAtual, pacotes);
                        
                        // Registra o trânsito
                        registraEventoTransito(indicePacote, numeroPacotes, tempoAtual, pacotes);

                        // Agora, o pacote chegou ao seu destino intermediário ou final
                        pacotes.GetElemento(indicePacote).armazemAtual = armazemDestino;
                        
                        // Escalona a chegada para armazenamento (tipo 1) no próximo tempo para simular bloco
                        long long int chave_chegada_para_armazenamento;
                        if (pacotes.GetElemento(indicePacote).armazemAtual == pacotes.GetElemento(indicePacote).armazemFinal) {
                            // Se chegou ao destino final, o "próximo armazém" é -1, mas ainda é um evento de "chegada" para entrega
                            chave_chegada_para_armazenamento = stoll(criaChaveEventoPacote(tempoAtual + latenciaTransporte, pacote_id));
                        } else {
                            // Se não, o próximo armazém é o próximo da rota
                            pacotes.GetElemento(indicePacote).proximoArmazem = pacotes.GetElemento(indicePacote).rota.getItem(0);
                            chave_chegada_para_armazenamento = stoll(criaChaveEventoPacote(tempoAtual + latenciaTransporte, pacote_id));
                        }
                        minHeap.insert(chave_chegada_para_armazenamento);
                        
                        pacotesTransportados++;
                    }
                }
            }
        }

        // Se evento é de pacote postado ou chegada para armazenamento
        else if (chaveProxEvento%10 == 1) {

            chaveProxEvento/=10;
            int pacote_id = chaveProxEvento % (1000000); 
            int indicePacote = procuraPacote(pacote_id, pacotes, numeroPacotes);
            
            // Se o pacote chegou ao destino final
            if (pacotes.GetElemento(indicePacote).armazemAtual == pacotes.GetElemento(indicePacote).armazemFinal) {
                
                ostringstream tempoSS;
                tempoSS << setw(6) << setfill('0') << atualizaRelogio(tempoAtual);

                ostringstream indicePacoteSS;
                indicePacoteSS << setw(3) << setfill('0') << indicePacote;

                ostringstream indiceArmazemFinalSS;
                indiceArmazemFinalSS << setw(3) << setfill('0') << pacotes.GetElemento(indicePacote).armazemFinal;

                cout << tempoSS.str() << " pacote " << indicePacoteSS.str() << " " << "entregue em " << indiceArmazemFinalSS.str() << endl;
            
            } else {
                // Armazena o pacote na respectiva seção
                empilhando(indicePacote, numeroPacotes, numeroSecoes, tempoAtual, pacotes, secoes);

                // Escalona o próximo evento de transporte para este pacote
                long long int proximoTempoTransporte = tempoAtual + intervaloTransporte;
                string chave_str = criaChaveEventoTransporte(proximoTempoTransporte, 
                                                             pacotes.GetElemento(indicePacote).armazemAtual, 
                                                             pacotes.GetElemento(indicePacote).proximoArmazem);
                long long int chave_long_long = stoll(chave_str);
                minHeap.insert(chave_long_long);
            }
        }
    }

    return 0;
}