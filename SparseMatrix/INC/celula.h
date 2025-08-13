#ifndef CELULA_H
#define CELULA_H

struct Node{
    Node *direita;
    Node *baixo;
    int linha;
    int coluna;
    double valor;

    // Construtor que inicializa todos os campos do nó
    Node(Node *direita, Node *baixo, int linha, int coluna, double valor){
        this->direita = direita;
        this->baixo = baixo;
        this->linha = linha;
        this->coluna = coluna;
        this->valor = valor;
    }
};

#endif