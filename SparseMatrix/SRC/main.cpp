#include <iostream>
#include "SparseMatrix.h"
#include "celula.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Funçao que recebe um matriz e uma string armazena nessa matriz
// Os valores presentes no arquivo com o nome dessa string
void readSparseMatrix(SparseMatrix& m, ifstream& arquivo){
    int i, j;
    double valor;
    while(arquivo >> i >> j >> valor){
        if(i > 0 && j > 0 && i <= m.linha() && j <= m.colunas()){
            m.insert(i, j, valor);
        }
    }
}

// Função que serve apenas para verificar a matriz gerada
// Pela multiplicacao de duas matrizes
SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B){
    if(A.colunas() == B.linha()){
        double somatorio = 0;
        SparseMatrix C(A.linha(), B.colunas());
        for(int i = 1; i <= A.linha(); i++){
            for(int j = 1; j <= B.colunas(); j++){
                for(int k = 1; k <= B.linha(); k++){
                    somatorio += (A.get(i, k) * B.get(k,j));
                }
                C.insert(i, j, somatorio);
                somatorio = 0;
            }
        }
        return C;
    }else{
        // Foi usado runtime_error como excesão pois vi que poderia tratalo e
        // assim retornar uma excesão sem encerrar o programa 
        throw runtime_error("erro: Linhas e colunas da primeira diferente da segunda!!!");
    }
}

// Função que realiza a multiplicação de duas matrizes
// e armazena esse resultado em uma matriz previamente criada
// ja com a ordem nescessaria, a ideia é possibilitar ao usuario
// que ele verifique a operação com a funçao anterior e depois
// criar uma matriz para armazenar o resultado
void multiply(SparseMatrix& A, SparseMatrix& B, SparseMatrix& C){
    if(A.colunas() == B.linha()){
        double somatorio = 0;
        for(int i = 1; i <= A.linha(); i++){
            for(int j = 1; j <= B.colunas(); j++){
                for(int k = 1; k <= B.linha(); k++){
                    somatorio += (A.get(i, k) * B.get(k,j));
                }
                C.insert(i, j, somatorio);
                somatorio = 0;
            }
        }
    }else{
        throw runtime_error("erro: Linhas e colunas da primeira diferente da segunda!!!");
    }
}

// a mesma ideia da primeira função multiply
SparseMatrix sum(SparseMatrix& A, SparseMatrix& B){
    if( (A.linha() == B.linha() ) && ( A.colunas() == B.colunas() )){
        SparseMatrix C(A.linha(), A.colunas());
        for(int i = 1; i <= A.linha(); i++){
            for(int j = 1; j <= B.colunas(); j++){
                C.insert(i, j, A.get(i,j) + B.get(i,j));
            }
        }
        return C;
    }else{
        throw runtime_error("erro: Linhas e colunas da primeira diferente da segunda!!!");
    }
}

// tambem a mesma ideia da segunda fução multiply
void sum(SparseMatrix& A, SparseMatrix& B, SparseMatrix& C){
    if( (A.linha() == B.linha() ) && ( A.colunas() == B.colunas() )){
        for(int i = 1; i <= A.linha(); i++){
            for(int j = 1; j <= B.colunas(); j++){
                C.insert(i, j, A.get(i,j) + B.get(i,j));
            }
        }
    }else{
        throw runtime_error("erro: Linhas e colunas da primeira diferente da segunda!!!");
    }
}

int main(){
    string opcao = "1";
    string opcao_auxiliar;
    int i, iaux;
    vector <SparseMatrix> Vetor_De_Matrizes_Esparsas;
    while(opcao != "exit"){
        if(opcao == "1")
            cout << "digite 'help' para mostrar os comandos " << endl;
        getline(cin, opcao);

        // tabela com todos os comandos da main e oq eles fazem
        if(opcao == "help"){
            cout << "             comando             |             o que faz             "
            << endl
            <<      "                                 |                                   "
            << endl 
            <<      "             create              | o usuario digita a quantidade de linhas"
            << endl
            <<      "                                 | e colunas e E criada uma matriz com essa ordem"
            << endl
            <<      "                                 |                                   "
            << endl
            <<      "           create copy           | o usuario digita o indice de uma de suas matrizes"
            << endl
            <<      "                                 | e E criada uma copia dessa matriz "
            << endl
            <<      "                                 |                                   "
            << endl
            <<      "           create sum            | o usuario digita os indices da primeira e segunda matriz"
            << endl
            <<      "                                 | e E criada uma matriz que E a soma dessas duas"
            << endl
            <<      "                                 |                                   "
            << endl
            <<      "         create multiply         | o usuario digita os indices da primeira e segunda matriz"
            << endl
            <<      "                                 | e E criada uma matriz que E a multiplicacao dessas duas"
            << endl
            <<      "                                 |                                   "
            << endl
            <<      "             show                | o usuario vai digitando os indices de suas matrizes"
            << endl
            <<      "                                 | para serem impressas na tela, digite 'back' para sair do comando"
            << endl
            <<      "                                 |                                   "
            << endl
            <<      "           show all              | imprimi todas as matrizes         "
            << endl
            <<      "                                 |                                   "
            << endl
            <<      "                                 | o usario escolhe uma de suas matrizes depois vai digitando"
            << endl
            <<      "             add                 | linha, coluna e valor para ser armazenado"
            << endl
            <<      "                                 | digite enter para armazenar e digite linhas ou colunas invalidas para encerrar o comando"
            << endl
            <<      "                                 |                                   "
            << endl
            <<      "            clear                | o usuario vai digitando os indices de suas matrizes"
            << endl
            <<      "                                 | para serem limpadas, digite 'back' para sair do comando"
            << endl
            <<      "                                 |                                   "
            << endl
            <<      "          clear all              | limpa todas as matrizes"
            << endl
            <<      "                                 |                                   "
            << endl
            <<      "            sum                  | o usuario escolhe a primeira e a segunda matriz"
            << endl
            <<      "                                 | e apenas sera impresso na tela o resultado da soma"
            << endl
            <<      "                                 |                                   "
            << endl
            <<      "          multiply               | o usuario escolhe a primeira e a segunda matriz"
            << endl
            <<      "                                 | e apenas sera impresso na tela o resultado da multiplicacao"
            << endl
            <<      "                                 |                                   "
            << endl
            <<      "          ler file               | o usuario digita o indice de uma matriz e um string"
            << endl
            <<      "                                 | e coloca na matriz os elementos do arquivo com o nome da string"
            << endl;
           
        }
        else if(opcao == "create"){
            int m, n;
            cin >> m >> n;
            cin.ignore();
            try{
                Vetor_De_Matrizes_Esparsas.push_back(SparseMatrix(m,n));
            }catch(exception& e){
                cout << e.what() << endl;
            }
            cout << "$create" << endl;
        }

        else if(opcao == "create copy"){
            cin >> i;
            cin.ignore();
            if(i >= 0 && i < Vetor_De_Matrizes_Esparsas.size()) Vetor_De_Matrizes_Esparsas.push_back(Vetor_De_Matrizes_Esparsas[i]);
            else cout << "nao existe essa matriz" << endl;
            cout << "$create copy" << endl;
        }

        else if(opcao == "create sum"){
            cout << "escolha a primeira e a segunda matriz: ";
            cin >> i >> iaux;
            if(i < Vetor_De_Matrizes_Esparsas.size() && iaux < Vetor_De_Matrizes_Esparsas.size()){
                // testa se a soma das matrizes é valida
                try{
                    sum(Vetor_De_Matrizes_Esparsas[i], Vetor_De_Matrizes_Esparsas[iaux]);
                    SparseMatrix C(Vetor_De_Matrizes_Esparsas[i].linha(), Vetor_De_Matrizes_Esparsas[i].colunas());
                    sum(Vetor_De_Matrizes_Esparsas[i], Vetor_De_Matrizes_Esparsas[iaux], C);
                    Vetor_De_Matrizes_Esparsas.push_back(C);
                }catch(exception& e){
                    cout << e.what() << endl;
                }
            }else{
                cout << "voce ainda nao fez essa matriz" << endl;
            }
            cin.ignore();
            cout << "$create sum" << endl;
        }

        else if(opcao == "create multiply"){
            cout << "escolha a primeira e a segunda matriz: ";
            cin >> i >> iaux;
            // testa se a multiplcação das matrizes é valida
            try{
                multiply(Vetor_De_Matrizes_Esparsas[i], Vetor_De_Matrizes_Esparsas[iaux]);
                SparseMatrix C(Vetor_De_Matrizes_Esparsas[i].linha(), Vetor_De_Matrizes_Esparsas[iaux].colunas());
                multiply(Vetor_De_Matrizes_Esparsas[i], Vetor_De_Matrizes_Esparsas[iaux], C);
                Vetor_De_Matrizes_Esparsas.push_back(C);
            }catch(exception &e){
                cout << e.what() << endl;
            }
            cin.ignore();
            cout << "$create multiply" << endl;
        }

        else if(opcao == "show all"){
            for(i = 0; i < Vetor_De_Matrizes_Esparsas.size(); ++i){
                cout << "matriz " << i << ":" << endl;
                Vetor_De_Matrizes_Esparsas[i].print();
            }
            cout << "$show all" << endl;
        }

        else if(opcao == "show"){
            while(opcao_auxiliar != "back"){
                int indici;
                getline(cin, opcao_auxiliar);
                try{
                    indici = stoi(opcao_auxiliar);
                    if(indici >= 0 && indici < Vetor_De_Matrizes_Esparsas.size())
                        Vetor_De_Matrizes_Esparsas[indici].print();
                    else{
                        cout << "nao ha matrizes nessas posicoes" << endl;
                    }
                }catch(const invalid_argument&){
                    if(opcao_auxiliar != "back")
                        cout << "digite 'back' para sair do comando" << endl;
                }
            }
            opcao_auxiliar = "0";
            cout << "$show" << endl;
        }

        else if(opcao == "add"){
            cout << "escolha uma de suas matrizes: ";
            cin >> i;
            if(i < Vetor_De_Matrizes_Esparsas.size()){
                int linha;
                int coluna;
                double valor;
                while(true){
                    cin >> linha >> coluna >> valor;
                    try{
                        Vetor_De_Matrizes_Esparsas[i].insert(linha, coluna, valor);
                    }catch(exception& e){
                        break;
                    }
                }
                cin.ignore();
            }
            else{
                cout << "voce ainda nao fez essa matriz" << endl;
            }
            cout << "$add" << endl;
        }

        else if(opcao == "clear all"){
            for(int i = 0; i < Vetor_De_Matrizes_Esparsas.size(); ++i){
                Vetor_De_Matrizes_Esparsas[i].clear();
            }
            cout << "$clear all" << endl;      
        }

        else if(opcao == "clear"){
            while(opcao_auxiliar != "back"){
                int indici;
                getline(cin, opcao_auxiliar);
                try{
                    indici = stoi(opcao_auxiliar);
                    if(indici >= 0 && indici < Vetor_De_Matrizes_Esparsas.size()) Vetor_De_Matrizes_Esparsas[indici].clear();
                    else cout << "nao ha matrizes nessa posicao" << endl;
                }catch(const invalid_argument&){
                    if(opcao_auxiliar != "back")
                        cout << "digite 'back' para sair do comando" << endl;
                }
            }
            cout << "$clear" << endl;
            opcao_auxiliar = "0";
        }

        else if(opcao == "sum"){
            cout << "escolha a primeira e a segunda matriz: ";
            cin >> i >> iaux;
            cin.ignore();
            try{
                sum(Vetor_De_Matrizes_Esparsas[i], Vetor_De_Matrizes_Esparsas[iaux]).print();
            }catch(exception& e){
                cout << e.what() << endl;
            }
            cout << "$sum" << endl;
        }

        else if(opcao == "multiply"){
            cout << "escolha a primeira e a segunda matriz: ";
            cin >> i >> iaux;
            try{
                multiply(Vetor_De_Matrizes_Esparsas[i], Vetor_De_Matrizes_Esparsas[iaux]).print();
            }catch(exception& e){
                cout << e.what() << endl;
            }
            cin.ignore();
            cout << "$multiply" << endl;
        }

        else if(opcao == "ler file"){
            string nome_do_arquivo;
            getline(cin, nome_do_arquivo);
            if(nome_do_arquivo != "celula.h" && nome_do_arquivo != "SparseMatrix.h" && nome_do_arquivo != "main.cpp"){
                ifstream arquivo(nome_do_arquivo);
                if(arquivo.is_open()){
                    int M, N;
                    arquivo >> M >> N;
                    SparseMatrix A(M,N);
                    readSparseMatrix(A, arquivo);
                    Vetor_De_Matrizes_Esparsas.push_back(A);
                    arquivo.close();
                }else{
                    cout << "este arquivo nao existe" << endl;
                }
            }
            cout << "$ler file" << endl;
        }
        
        else if(opcao != "exit"){
            cout << "comando inexistente" << endl;
        }
    }

}