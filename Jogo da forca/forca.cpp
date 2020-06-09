#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

void limpatela(){  system("CLS"); }

string retornapalavraAleatoria()
{
    string palavra[3] = {"professor", "aprendizagem", "diciplina"};

    int indiceAleatorio = rand() %3;

    return palavra[indiceAleatorio];
}

string returnamascara (string palavra, int tamanhodaPalavra)
{
   int cont = 0;
    string palavraOculta;

    //coloca a mascara
    while(cont < tamanhodaPalavra){
        palavraOculta += "_";
        cont ++;
    }
  return palavraOculta;
}

void exibestatus(string palavraOculta, int tamanhodaPalavra, int tentativasrestantes, string letrasArriscadas, string mensagem)
{
   cout << mensagem;
   cout << "Palavra: " << palavraOculta << "Tamanho(" << tamanhodaPalavra << ")";
   cout << "\nTentativas Restantes: " << tentativasrestantes;

   //Exibi as letras arriscadas
   int cont;
   cout << "\nLetras arriscadas:";
   for(cont = 0; cont < letrasArriscadas.size(); cont ++){
    cout << letrasArriscadas << ",";
   }
}

int jogar(int numeroDeJogadores)
{
    //palavra a ser adivinhada
    string palavra;

    if(numeroDeJogadores == 1){
        palavra = retornapalavraAleatoria();
    } else {
        cout << "\nDigite uma palavra:";
        cin >> palavra;

    }

    //Tamanho da palavra
    int tamanhodaPalavra = palavra.size();

   //palavra mascarada
   string palavraOculta = returnamascara(palavra, tamanhodaPalavra);

   ///Variaveis principais
   int tentativas = 0, maximotentativas = 10;        //numero de tentativas
   char letra;                                      // letras arriscadas
   int cont = 0;                                    // auxiliar para laço de repetiçao
   int opcao;                                       //opção finais
   string letrasArriscadas;                         // acumula tentativas
   string mensagem = "Bem vindo ao jogo!";          //Feedback
   string palavraArriscada;                         //Tentativa de arrisca palavra completa
   bool jadigitada = false, acertouLetra = false;   //Saber se a letra ja foi digitada

   while(palavra != palavraOculta && maximotentativas - tentativas > 0)
   {
         limpatela();

       //exibi o status atual do jogo
       exibestatus(palavraOculta, tamanhodaPalavra, maximotentativas - tentativas, letrasArriscadas,mensagem);

      //lê um palpite
      cout << "\nDigite uma letra (Ou digite 1 para arriscar a palavra): ";
      cin >> letra;

      if(letra == '1'){
        cin >> palavraArriscada;
        if(palavraArriscada == palavra){
            palavraOculta = palavraArriscada;
        }else {
            tentativas = maximotentativas;
        }
      }

      //para letras ja arriscadas
      for(cont = 0; cont < tentativas; cont++){

        //Se encontrar a letra
        if(letrasArriscadas[cont] == letra){
            mensagem = "Essa letra ja foi digitada.";

            //indica com a booleana
            jadigitada = true;
        }

      }

      //Se for letra nao digitada
      if(jadigitada == false){

        letrasArriscadas += tolower(letra);

      //percorrer a palavra
      for(cont = 0; cont <tamanhodaPalavra; cont ++)
      {
          //Se a letra existir
          if(palavra[cont] == tolower(letra))
          {
              //mostra a letra
              palavraOculta[cont] = palavra[cont];

              acertouLetra = true;
          }
      }

       if(acertouLetra == false){

                mensagem = "Voce errou uma letra!";

            }else{

                mensagem = "Voce acertou uma letra!";

            }

      //aumenta valor de tentativas gastas
      tentativas++;

      }

        //Reinicia auxiliares
        jadigitada = false;
        acertouLetra = false;

   }


    if(palavra == palavraOculta){

        limpatela();
        cout << "Parabens, você venceu!";
        cout << "\nDeseja reiniciar?";
        cout << "\n1-Sim";
        cout << "\n2-Nao";
        cin >> opcao;
        return opcao;

    }else{

        limpatela();
        cout << "Opa, você perdeu!";
        cout << "\nDeseja reiniciar?";
        cout << "\n1-Sim";
        cout << "\n2-Nao";
        cin >> opcao;
        return opcao;
    }

}

void menuinicial()
{
    int opcao = 0;

    while(opcao < 1 || opcao > 3)
    {
    cout << "    Bem Vindo ao Jogo!!!  ";
    cout << "\n 1- Jogar.";
    cout << "\n 2- Jogar em Dupla.";
    cout << "\n 3- Sobre.";
    cout << "\n 4- Sair.";
    cout << "\nEscolha uma opcao e aperte Enter:";
    cin >> opcao;

     limpatela();

    //Faz algo de acordo com a opcao escolhida
        switch(opcao){
            case 1:
                //Inicia o jogo
                if(jogar(1) == 1){
                    menuinicial();
                }
                break;
            case 2:
                //Inicia o jogo
                if(jogar(2) == 1){
                    menuinicial();
                }
                break;
            case 3:
                //Mostra informacoes do Jogo
                cout << "Informacoes do jogo";
                limpatela();
                cout << "Jogo desenvolvido por Pedro em 2020";
                cout << "\n1 - Voltar";
                cout << "\n2 - Sair";
                cin >> opcao;
                if(opcao == 1){
                    menuinicial();
                }

                break;
            case 4:
                cout << "Ate mais!";
                break;
        }
    }

}




int main()
{

    srand((unsigned)time(NULL));

    menuinicial();




    return 0;
}
