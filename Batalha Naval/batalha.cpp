#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

//Cabe�alhos de fun��es
void menuInicial();


void limpaTela(){
    system("CLS");
}

void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]){

     //Enche o tabuleiro com �gua
    int linha,coluna;
    for(linha = 0; linha < 10; linha++){
         for(coluna = 0; coluna < 10; coluna++){
            tabuleiro[linha][coluna] = 'A';
            mascara[linha][coluna] = '*';
         }
    }

}

void exibeMapa(){
    //Indica colunas
    int cont;
    for(cont=0; cont < 10; cont++){
        if(cont == 0){
            cout << "     ";
        }
        cout << cont << "| ";
    }
    cout << "\n";

}

void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], bool mostraGabarito){


    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };

    //Exibe o tabuleiro
    int linha,coluna;
    for(linha = 0; linha < 10; linha++){
         cout << linha << " - ";
         for(coluna = 0; coluna < 10; coluna++){

            switch(mascara[linha][coluna]){
                case 'A':
                    cout << blue << " " <<mascara[linha][coluna] << normal;
                    break;
                case 'P':
                    cout << green << " " <<mascara[linha][coluna] << normal;
                    break;
                default:
                    cout << " " <<mascara[linha][coluna];
                    break;
            }

         }
         cout << "\n";
    }

    if(mostraGabarito == true){
        for(linha = 0; linha < 10; linha++){
             for(coluna = 0; coluna < 10; coluna++){
                 cout << " " <<tabuleiro[linha][coluna];
             }
             cout << "\n";
        }
    }


}

void posicionaBarcos(char tabuleiro[10][10]){

    //Coloca os barcos no tabuleiro
    int cont, quantidade = 10, quantidadePosicionada = 0;

    //Verifica��o do posicionamento de todos os barcos
    while(quantidadePosicionada < quantidade){

        int linhaAleatoria = rand() % 10;  //Gera n�mero aleat�rio de 0 a 9
        int colunaAleatoria = rand() % 10; //Gera n�mero aleat�rio de 0 a 9

        if(tabuleiro[linhaAleatoria][colunaAleatoria] == 'A'){

            //Posiciona 10 barcos random
            tabuleiro[linhaAleatoria][colunaAleatoria] = 'P';

            //Aumenta o contador de barcos posicionados
            quantidadePosicionada++;

         }

    }

}

void verificaTiro(char tabuleiro[10][10], int linhaJogada, int colunaJogada, int *pontos, string *mensagem){

    //Verifica pontos para adicionar
    switch(tabuleiro[linhaJogada][colunaJogada]){
        case 'P':
            *pontos = *pontos + 10;
            *mensagem = "Voce acertou um barco pequeno! (10 pts)";
            break;
        case 'A':
            *mensagem = "Voce acertou a agua";
            break;
    }

}

void jogo(string nomeDoJogador){

    ///Vari�veis Gerais
    char tabuleiro[10][10],mascara[10][10];             //Tabuleiro do Jogo
    int linha,coluna;                                   //Auxiliares de navega��o
    int linhaJogada, colunaJogada;                      //Posicao escolhida pelo jogador
    int estadoDeJogo = 1;                               //1 = Jogo Acontecendo, 0 = Fim de Jogo
    int pontos = 0;                                     //Pontua��o do Jogador
    int tentativas = 0, maximoDeTentativas = 5;         //Tentativas do jogador
    int opcao;                                          //Op��es de fim de jogo
    string mensagem = "Bem vindo ao jogo!";             //Mensagem de feedback para o jogador

    //Inicia com �gua no tabuleiro
    iniciaTabuleiro(tabuleiro,mascara);

    //Posiciona os barcos aleatoriamente
    posicionaBarcos(tabuleiro);

    while(tentativas < maximoDeTentativas){

        limpaTela();

        //Exibe indica��es
        exibeMapa();

        //Exibe tabuleiro
        exibeTabuleiro(tabuleiro,mascara, false);

        cout << "\nPontos:" << pontos << ", Tentativas Restantes:" << maximoDeTentativas - tentativas;
        cout << "\n" << mensagem;

        //Verifica��o os dados
        linhaJogada = -1;
        colunaJogada = -1;

        while( (linhaJogada < 0 || colunaJogada < 0) ||  (linhaJogada > 9 || colunaJogada > 9)) {

            cout << "\n" << nomeDoJogador << ", digite uma linha:";
            cin >> linhaJogada;
            cout <<  "\n" << nomeDoJogador << ", digite uma coluna:";
            cin >> colunaJogada;

        }

        //Verifica o que acontece
        verificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontos, &mensagem);

        //Revela o que esta no tabuleiro
        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;

    }

    cout << "Fim de jogo, o que deseja fazer?";
    cout << "\n1-Jogar Novamente";
    cout << "\n2-Ir para o Menu";
    cout << "\n3-Sair";
    cin >> opcao;
    switch(opcao){
        case 1:
            jogo(nomeDoJogador);
            break;
        case 2:
            menuInicial();
            break;
           }

}

void menuInicial(){

    //Op��o escolhida pelo jogador
    int opcao = 0;

    //Nome do jogador
    string nomeDoJogador;

    //Mostra o menu novamente se digitar comando invalido
    while(opcao < 1 || opcao > 3){
        limpaTela();
        cout << "Bem vindo ao Jogo de Batalha Naval";
        cout << "\n1 - Jogar";
        cout << "\n2 - Sobre";
        cout << "\n3 - Sair";
        cout << "\nEscolha uma opcao e tecle ENTER:";

        //Faz a leitura da opcao
        cin >> opcao;

        //Faz algo de acordo com a opcao escolhida
        switch(opcao){
            case 1:
                //Inicia o jogo
                cout << "Qual seu nome?";
                cin >> nomeDoJogador;
                jogo(nomeDoJogador);
                break;
            case 2:
                //Mostra informacoes do Jogo
                cout << "Informacoes do jogo";
                limpaTela();
                cout << "Jogo desenvolvido por Pedro em 2020";
                cout << "\n1 - Voltar";
                cout << "\n2 - Sair";
                cin >> opcao;
                if(opcao == 1){
                    menuInicial();
                }

                break;
            case 3:
                cout << "Ate mais!";
                break;
        }
    }

}

int main(){

    //Gerador de numeros aleat�rios
    srand((unsigned)time(NULL));

    menuInicial();
    return 0;
}
