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
#include <map>

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

// Tipo de evento 1: Postagem de Pacote / Chegada para Armazenamento
string criaChaveEventoPacote (int tempo, int idpac) {
    ostringstream oss;
    oss << setw(6) << setfill('0') << tempo; 
    oss << setw(6) << setfill('0') << idpac; 
    oss << "1"; // Tipo de Evento: Pacote para armazenamento
    return oss.str();
}

// Tipo de evento 2: Início de Despacho de uma Seção
string criaChaveEventoDespachoSecao (int tempo, int armazemOrigem, int armazemDestino) {
    ostringstream oss;
    oss << setw(6) << setfill('0') << tempo;
    oss << setw(3) << setfill('0') << armazemOrigem;
    oss << setw(3) << setfill('0') << armazemDestino;
    oss << "2"; // Tipo de Evento: Despacho de seção (remoção e trânsito)
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

// Mapa para controlar o próximo tempo de despacho agendado para cada seção
// Chave: pair<armazemOrigem, armazemDestino>, Valor: tempo agendado
map<pair<int, int>, long long int> proximoDespachoAgendado;

void empilhando (int indicePacote, int numeroPacotes, int numeroSecoes, int tempoAtualEvento, Vetor<pacote> &pacotes, Vetor<pilhaEncadeada> &secoes, heap &minHeap, int intervaloTransporte) {
    
    // Atualiza a rota e o próximo armazém do pacote
    if (pacotes.GetElemento(indicePacote).rota.size() > 0) {
        pacotes.GetElemento(indicePacote).armazemAtual = pacotes.GetElemento(indicePacote).rota.removeFirstOne();

        if (pacotes.GetElemento(indicePacote).rota.size() > 0) {
            pacotes.GetElemento(indicePacote).proximoArmazem = pacotes.GetElemento(indicePacote).rota.getItem(0); 
        } else {
            pacotes.GetElemento(indicePacote).proximoArmazem = -1; // Chegou ao destino final
        }
    } else {
        return; // Rota vazia, pacote já deveria estar no destino final
    }

    // Procura a seção correta para empilhar o pacote
    for (int i = 0; i < numeroSecoes; i++) {   
        if (pacotes.GetElemento(indicePacote).armazemAtual == secoes.GetElemento(i).armazem 
            && secoes.GetElemento(i).secao == pacotes.GetElemento(indicePacote).proximoArmazem) { 

            secoes.GetElemento(i).empilha(pacotes.GetElemento(indicePacote).idpac);

            // Imprime o evento de armazenamento
            ostringstream tempoSS;
            tempoSS << setw(6) << setfill('0') << atualizaRelogio(tempoAtualEvento);

            ostringstream pacoteSS;
            pacoteSS << setw(3) << setfill('0') << indicePacote; // Usa o índice do vetor de pacotes

            ostringstream armazemSS;
            armazemSS << setw(3) << setfill('0') << secoes.GetElemento(i).armazem;

            ostringstream secaoSS;
            secaoSS << setw(3) << setfill('0') << secoes.GetElemento(i).secao;

            cout << tempoSS.str() << " pacote " << pacoteSS.str() << " armazenado em " << armazemSS.str() << " na secao " << secaoSS.str() << endl;

            // Lógica para agendar o despacho da seção:
            // Acontece 'intervaloTransporte' (110) unidades de tempo após o armazenamento do primeiro pacote naquela seção
            pair<int, int> secaoKey = {secoes.GetElemento(i).armazem, secoes.GetElemento(i).secao};
            long long int tempoParaAgendar = (long long)tempoAtualEvento + intervaloTransporte;

            // Se ainda não há agendamento para esta seção ou o agendamento existente é para um tempo anterior
            // (ou seja, um novo ciclo de despacho precisa ser agendado)
            if (proximoDespachoAgendado.find(secaoKey) == proximoDespachoAgendado.end() || proximoDespachoAgendado[secaoKey] < tempoParaAgendar) {
                string chave_despacho_str = criaChaveEventoDespachoSecao(tempoParaAgendar, secaoKey.first, secaoKey.second);
                minHeap.insert(stoll(chave_despacho_str));
                proximoDespachoAgendado[secaoKey] = tempoParaAgendar;
            }
            return; // Pacote empilhado e despacho agendado/verificado, sair da função
        }
    }
}

void registraEventoRemocao (int indicePacote, int tempoEvento, Vetor<pacote> &pacotes) {
    ostringstream tempoSS;
    tempoSS << setw(6) << setfill('0') << atualizaRelogio(tempoEvento);

    ostringstream pacoteSS;
    pacoteSS << setw(3) << setfill('0') << indicePacote;

    ostringstream armazemSS;
    armazemSS << setw(3) << setfill('0') << pacotes.GetElemento(indicePacote).armazemAtual;

    ostringstream secaoSS; 
    secaoSS << setw(3) << setfill('0') << pacotes.GetElemento(indicePacote).proximoArmazem;

    cout << tempoSS.str() << " pacote " << pacoteSS.str() << " removido de " << armazemSS.str() << " na secao " << secaoSS.str() << endl;
}

void registraEventoTransito (int indicePacote, int tempoEvento, Vetor<pacote> &pacotes) {
    ostringstream tempoSS;
    tempoSS << setw(6) << setfill('0') << atualizaRelogio(tempoEvento);

    ostringstream pacoteSS;
    pacoteSS << setw(3) << setfill('0') << indicePacote;

    ostringstream armazemInicialSS; 
    armazemInicialSS << setw(3) << setfill('0') << pacotes.GetElemento(indicePacote).armazemAtual; 

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
    int intervaloTransporte = stoi(aux); // Este será o "110 unidades de tempo"

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

    Vetor<pacote> pacotes(numeroPacotes);
    for (int k = 0; k < numeroPacotes; ++k) {
        getline(in, aux, '\n');
        stringstream ss(aux);
        string dump;
        int tempochegada_n, idpac_n, armazeminicial_n, armazemfinal_n;
        ss >> tempochegada_n >> dump >> idpac_n >> dump >> armazeminicial_n >> dump >> armazemfinal_n >> dump;
        
        pacote pacoteAuxiliar;
        pacoteAuxiliar.tempochegada = tempochegada_n;
        pacoteAuxiliar.idpac = idpac_n;
        pacoteAuxiliar.armazemInicial = armazeminicial_n;
        pacoteAuxiliar.armazemAtual = armazeminicial_n; // Inicializa armazemAtual
        pacoteAuxiliar.armazemFinal = armazemfinal_n;
        pacotes.AdicionaElemento(pacoteAuxiliar);
    }
    
    Vetor<pilhaEncadeada> secoes(numeroSecoes);
    int secao_idx = 0; 
    for (int i = 0; i < numeroArmazens; i++) {
        for (int j = 0; j < numeroArmazens; j++) {
            if (grafo.verificaAresta(i, j)) {
                pilhaEncadeada aux;
                aux.armazem = i;
                aux.secao = j;
                secoes.AdicionaElemento(aux);
                secao_idx++;
            }
        }
    }

    heap minHeap;
    long long int tempoAtual = 0; // Tempo global da simulação

    // Escalona os eventos de postagem iniciais
    for (int i = 0; i < numeroPacotes; i++) {
        grafo.buscaEmLargura(pacotes.GetElemento(i).armazemInicial, 
                             pacotes.GetElemento(i).armazemFinal,
                             pacotes.GetElemento(i).rota);
        
        // Se o pacote já está no destino final na postagem, ele não precisa de transporte
        if (pacotes.GetElemento(i).armazemInicial == pacotes.GetElemento(i).armazemFinal) {
            ostringstream tempoSS;
            tempoSS << setw(6) << setfill('0') << atualizaRelogio(pacotes.GetElemento(i).tempochegada);

            ostringstream indicePacoteSS;
            indicePacoteSS << setw(3) << setfill('0') << i;

            ostringstream indiceArmazemFinalSS;
            indiceArmazemFinalSS << setw(3) << setfill('0') << pacotes.GetElemento(i).armazemFinal;

            cout << tempoSS.str() << " pacote " << indicePacoteSS.str() << " " << "entregue em " << indiceArmazemFinalSS.str() << endl;
        } else {
            string chave_str = criaChaveEventoPacote(pacotes.GetElemento(i).tempochegada, pacotes.GetElemento(i).idpac);
            minHeap.insert(stoll(chave_str));
        }
    }
        
    bool fimEventos = false;
    long long int chaveProxEvento = 0;

    while(!fimEventos) {

        minHeap.printHeap();

        chaveProxEvento = minHeap.extractMin(); 

        cout << "chaveProxEvento: " << chaveProxEvento << endl;

        if (chaveProxEvento == 0) { 
            fimEventos = true; 
            continue; 
        }

        // O tempo do evento que acabou de ser extraído é o tempo para processar este evento e seus logs
        long long int tempoDoEventoAtual = chaveProxEvento / 10000000;

        // --- Evento Tipo 2: Início de Despacho de uma Seção (Remoção e Trânsito) ---
        if (chaveProxEvento % 10 == 2) {
            chaveProxEvento /= 10;
            int armazemDestino = chaveProxEvento % (1000); 
            long long tempParaArmazemOrigem = chaveProxEvento / 1000; 
            int armazemOrigem = tempParaArmazemOrigem % (1000); 

            // Para que o próximo despacho possa ser agendado, removemos o agendamento anterior para esta seção
            proximoDespachoAgendado.erase({armazemOrigem, armazemDestino});

            // Encontra a pilha (seção) correta
            for (int i = 0; i < numeroSecoes; ++i) {
                if (secoes.GetElemento(i).armazem == armazemOrigem && secoes.GetElemento(i).secao == armazemDestino) {
                    int pacotesDespachados = 0;
                    while (!secoes.GetElemento(i).isEmpty() && pacotesDespachados < capacidadeDeTransporte) {
                        int pacote_id = secoes.GetElemento(i).desempilha();
                        int indicePacote = procuraPacote(pacote_id, pacotes, numeroPacotes);
                        
                        // Registra a remoção usando o tempoDoEventoAtual
                        registraEventoRemocao(indicePacote, tempoDoEventoAtual, pacotes);
                        
                        // Registra o trânsito usando o tempoDoEventoAtual
                        registraEventoTransito(indicePacote, tempoDoEventoAtual, pacotes);

                        // Escalona a chegada para armazenamento (Tipo 1) no armazém de destino
                        // O tempo de chegada é o tempoDoEventoAtual (início do transporte) + latenciaTransporte
                        long long int tempoChegadaPacote = tempoDoEventoAtual + latenciaTransporte;
                        string chave_chegada_str = criaChaveEventoPacote(tempoChegadaPacote, pacote_id);
                        minHeap.insert(stoll(chave_chegada_str));
                        
                        pacotesDespachados++;
                    }
                    break; // Seção encontrada e processada
                }
            }
        }
        // --- Evento Tipo 1: Postagem de Pacote / Chegada para Armazenamento ---
        else if (chaveProxEvento % 10 == 1) {
            chaveProxEvento /= 10;
            int pacote_id = chaveProxEvento % (1000000); 
            int indicePacote = procuraPacote(pacote_id, pacotes, numeroPacotes);
            
            // Verifica se o pacote chegou ao seu destino final
            if (pacotes.GetElemento(indicePacote).armazemAtual == pacotes.GetElemento(indicePacote).armazemFinal) {
                ostringstream tempoSS;
                tempoSS << setw(6) << setfill('0') << atualizaRelogio(tempoDoEventoAtual);

                ostringstream indicePacoteSS;
                indicePacoteSS << setw(3) << setfill('0') << indicePacote;

                ostringstream indiceArmazemFinalSS;
                indiceArmazemFinalSS << setw(3) << setfill('0') << pacotes.GetElemento(indicePacote).armazemFinal;

                cout << tempoSS.str() << " pacote " << indicePacoteSS.str() << " " << "entregue em " << indiceArmazemFinalSS.str() << endl;
                
            } else {
                
                empilhando(indicePacote, numeroPacotes, numeroSecoes, tempoDoEventoAtual, pacotes, secoes, minHeap, intervaloTransporte);
            }
        }
    }

    return 0;
}