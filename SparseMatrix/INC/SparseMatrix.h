#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include "celula.h"
#include <iostream>
#include <iomanip>


class SparseMatrix{
private:
    // ponteiro para o primeiro sentinela
    Node *m_head;
    // variaveis que armazenam a quantidade de linhas
    // e colunas da matriz
    int m_linhas;
    int n_colunas;
public:
    // Construtor da matriz
    // cria uma matriz sparsa vazia de ordem MxN
    SparseMatrix(int m, int n){
        if(m > 0 && n > 0){
            // Inicializando o primeiro sentinela
            m_head = new Node(m_head, m_head, -1, -1, 0);
            m_head->direita = m_head;
            m_head->baixo = m_head;
            m_linhas = m;
            n_colunas = n;
            // Criando as celulas das colunas a ideia é semelhante ao push_front
            // da lista simplesmente encadeada
            while(n > 0){
                Node *aux1 = new Node(m_head->direita, aux1, 0, n, 0);
                aux1->baixo = aux1;
                m_head->direita = aux1;
                n--;
            }
            // Criando as celulas das linhas
            while(m > 0){
                Node *aux2 = new Node(aux2, m_head->baixo, m, 0, 0);
                aux2->direita = aux2;
                m_head->baixo = aux2;
                m--;
            }
        }else{
            throw std::runtime_error("erro: linhas ou colunas <= 0!!!");
        }
    }
    
    // construtor defolt, cria apenas um unico sentinela
    SparseMatrix(){
        m_head = new Node(m_head, m_head, -1, -1, 0);
        m_head->direita = m_head;
        m_head->baixo = m_head;
    }

    // construtor de copia
    SparseMatrix(const SparseMatrix& A) : SparseMatrix(A.m_linhas, A.n_colunas){

        // primeira versão do construtor de copia, esta função foi usada somente
        // para testar se resolvia o problema com a classe vector do c++, devido sua facilidade
        // na implementação
        
        /*

        for(int i = 1; i <= A.m_linhas; i++){
            for(int j = 1; j <= A.n_colunas; j++){
                this->insert(i, j, A.get(i, j));
            }
        }

        */

        // versão final, mais eficiente do que a anterior
        Node *aux = A.m_head->direita;
        while(aux != A.m_head){
            if(aux->baixo->linha != 0){
                aux = aux->baixo;
                this->insert(aux->linha, aux->coluna, aux->valor);
            }
            else{
                aux = aux->baixo->direita;
            }
        }    
    }

    // Função que imprime na tela os elementos presentes na matriz
    // imprimindo 0 aonde não ha nos, existem 3 casos:
    // quando a linha esta sem nós imprimo uma linha de zeros
    // se ouver um elemento na linha vou ate o ultimo elemento dessa linha
    // imprimindo os valores e imprimindo zeros nos espaços entre um nó e outro
    // quando chego no ultimo nó dessa linha talvez não seja a ultima coluna
    // e imprimo zeros desse nó ate a ultima coluna
    void print(){
        Node *atual = m_head->baixo;
        Node *aux = m_head->baixo;
        int O = 0;
        while(atual != m_head){
            if(atual->direita == atual){
                atual = aux->baixo;
                aux = aux->baixo;
                for(int i = 0; i < n_colunas; i++) std::cout << std::setw(3) << O << " ";
                std::cout << std::endl;
            }else if(atual->direita != aux){
                for(int i = atual->coluna; i < atual->direita->coluna-1; i++) std::cout << std::setw(3) << O << " ";
                atual = atual->direita;
                std::cout << std::setw(3) << atual->valor << " ";
            }else{
                for(int i = atual->coluna+1; i <= n_colunas; i++) std::cout << std::setw(3) << O << " ";
                atual = aux->baixo;
                aux = aux->baixo;
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    // função que insere valores diferentes de 0 dentro da matriz
    void insert(int i, int j, double value){
        if(i > 0 && j > 0 && i <= m_linhas && j <= n_colunas){
            if(value != 0){
                // ponteiro para encontrar a linha
                Node *li = m_head->baixo;
                // ponteiro para encontra a coluna
                Node *co = m_head->direita;
                // encontrando a linha variando 'li' indo para baixo
                while(li->linha != i){
                    li = li->baixo;
                }
                // encontrando a coluna variando 'co' indo para direita
                while(co->coluna != j){
                    co = co->direita;
                } 
                // ponteiro para encontrar o nó a ser inserido um novo valor ou o nó uma coluna a traz para caso precise ser criado um novo nó
                Node *liaux = li;
                // ponteiro para encontrar o nó a ser inserido um novo valor ou o nó uma linha a cima para caso precise ser criado um novo nó
                Node *coaux = co;
                // entra no laço caso haver um elemento na linha, se tiver sai ate chegar no nó desejado
                // ou uma coluna atraz do nó a ser criado
                while(liaux->direita != li){
                    if(liaux->direita->coluna <= j) liaux = liaux->direita;
                    else break;
                }
                // entra no laço caso haver um elemento na coluna, se tiver sai ate chegar no nó desejado
                // ou uma linha a cima do nó a ser criado
                while(coaux->baixo != co){
                    if(coaux->baixo->linha <= i) coaux = coaux->baixo;
                    else break;
                }
                // 'coaux' esta na coluna que o usuario deseja inserir elemento, mais caso o ponteiro parou
                // uma linha a cima, sera nescesario criar um nó e fazer as devidas lincagens
                if(coaux->linha != i){
                    Node *aux = new Node(liaux->direita, coaux->baixo, i, j, value);
                    liaux->direita = aux;
                    coaux->baixo = aux;
                // caso 'coaux' tiver chegado na linha, o nó ja existe e o valor so precisa ser inserido
                }else{
                    // a inserção foi feita usando liaux mostrando que ele tambem chega no nó a ser inserido
                    liaux->valor = value;
                }
            }else{

            }
        }else{
            throw std::runtime_error("erro: indices fora do intervalo!!!");
        }
    }

    // Função que retorna o valor presente no nó da linha i e coluna j
    double get(int i, int j) const{
        if( i > 0 && j > 0 && i <= m_linhas && j <= n_colunas){
            // como a nescesidade é de apenas chegar nó basta apenas uma variavel
            Node *li = m_head->baixo;
            // encontrando a linha do nó
            while(li->linha != i){
                li = li->baixo;
            }
            // aqui encontramos o nó, ou paramos um nó a traz caso esse nó 
            // da linha i e coluna j não exista
            while(li->direita->coluna != 0){
                if(li->direita->coluna <= j) li = li->direita;
                else break;
            }
            if(li->coluna == j) return li->valor;
            else return 0;
        }else{
            throw std::runtime_error("erro: indices fora do intervalo!!!");
        }
    }

    // Retorna a quantidade de linhas da matriz
    int linha(){
        return m_linhas;
    }
    // Retorna a quantidade de colunas da matriz
    int colunas(){
        return n_colunas;
    }

    // limpa a matriz, deixando como foi criada
    void clear(){
        // usei um ponteiro 'm_head_aux' para sempre apontar para alguma linha
        // e usei o m_head para percorrer a matriz, no final fazendo ele apontar para onde apontava no inicio
        Node *m_head_aux = m_head;
        m_head = m_head->direita;
        // fazendo o ponteiro 'baixo' de todos os sentinelas das colunas apontarem para seus sentinelas
        while(m_head != m_head_aux){
            m_head->baixo = m_head;
            m_head = m_head->direita;
        }
        m_head_aux = m_head_aux->baixo;
        m_head = m_head_aux->direita;
        // deletando os nos que foram adicionados dentro da matriz
        // o laço para quando m_head chegar na ultima linha e não ouver mais elementos la
        while((m_head->linha != m_linhas) || (m_head != m_head_aux)){
            // caso não haja elemento na linha:
            if(m_head == m_head_aux){
                // faço o ponteiro 'direita' do sentinela da linha apontar para seu sentinela
                m_head_aux->direita = m_head_aux;
                // m_head_aux vai para baixo
                m_head_aux = m_head_aux->baixo;
                // m_head ja vai para o primeiro elemento da proxima linha
                m_head = m_head_aux->direita;
            // caso haja elemento na linha:
            }else{
                // faço o ponteiro 'direita' do sentinela da linha apontar para seu sentinela
                // faço isso pois quando o ultimo elemento da ultima linha for deletado, o laço vai terminar
                // se não houver isso o ponteiro 'direita' da ultima linha ira apontar para uma região de memoria desconhecida
                m_head_aux->direita = m_head_aux;
                Node *aux = m_head;
                m_head = m_head->direita;
                delete aux;
            }
        }
        // no final m_head volta a apontar para o primeiro sentinela
        m_head = m_head_aux->baixo;
    }

    // sobrecarga do operador de atribuição ( = )
    SparseMatrix& operator=(SparseMatrix& A){
        if((A.m_linhas == this->m_linhas) && (A.n_colunas == this->n_colunas)){
            // limpo a minha matriz
            this->clear();

            // mesma ideia da primeira versão do construtor de copia
            /*
            for(int i = 1; i <= K.m_linhas; i++){
                for(int j = 1; j <= K.n_colunas; j++){
                    this->insert(i, j, K.get(i, j));
                }
            }
            */

            // mesma ideia versão atual do construtor de copia
            Node *aux = A.m_head->direita;
            while(aux != A.m_head){
                if(aux->baixo->linha != 0){
                    aux = aux->baixo;
                    this->insert(aux->linha, aux->coluna, aux->valor);
                }
                else{
                    aux = aux->baixo->direita;
                }
            }

            return *this;
        }else{
            throw std::runtime_error("erro: matrizes de ordem diferentes!!!");
        }
    }

    

    //Destrutor
    ~SparseMatrix(){
        // limpa a minha matriz
        this->clear();
        // deleta os sentinelas das colunas
        while(m_head->direita != m_head){        
            Node *aux = m_head->direita;
            m_head->direita = aux->direita;
            delete aux;
        }
        // deleta os sentinelas das linhas
        while(m_head->baixo != m_head){        
            Node *aux = m_head->baixo;
            m_head->baixo = aux->baixo;
            delete aux;
        }
        delete m_head;

        // antiga versão do destrutor, OBS: não havia feito a função clear quando fiz essa
        /*
        Node *m_head_aux = m_head;
        m_head = m_head->direita;
        // o laço termina quando, m_head chegar na ultima linha e estiver havendo 1 ou 2 nós dessa linha, contando com o sentinela
        while(m_head->linha != m_linhas || m_head->direita != m_head_aux){
            // deletando os nos das linhas, ate m_head chegar no ultimo nó
            if(m_head->direita != m_head_aux){
                Node *aux = m_head;
                m_head = m_head->direita;
                delete aux;
            // aqui é quando m_head chegou no ultimo nó de sua linha:
            }else{
                // aux1 recebe m_head_aux, aux2 recebe m_head, m_head_aux vai
                // para a proxima linha e m_head para o primerio elemento dessa proxima linha
                // caso aux1 e aux2 apontem para locais diferentes deleto os dois
                // se não deleto so um
                Node *aux1 = m_head_aux;
                Node *aux2 = m_head;
                m_head_aux = m_head_aux->baixo;
                m_head = m_head_aux->direita;
                if(aux1 != aux2){
                    delete aux1;
                    delete aux2;
                }else{
                    delete aux1;
                    aux2 = nullptr;
                }
            }
        }
        // caso m_head e m_head_aux apontarem para locais diferentes deleto os dois, se não deleto m_head e acabou
        if(m_head != m_head_aux){
            delete m_head;
            delete m_head_aux;
        }else{
            delete m_head;
        }*/
    }
};

#endif