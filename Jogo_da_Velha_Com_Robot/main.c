#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "header.h"

#if defined(_WIN32) || defined(_WIN64)
        const char* os = "Windoze";
#else
#ifdef __linux
        const char* os = "Linux";
#else
        const char* os = "Unknown";
#endif
#endif



int main (){

    int i, j, opcao=0;
    jogada game;

    setlocale(LC_ALL,"");

    char tabuleiro[TAM][TAM];

    preencherTabuleiroVazio(tabuleiro, &game);


    do{
        if (opcao == 0){
            printf("Escolha: \n\nJogador Humano X Jogador Humano(1)\nJogador Humano x AI(2)\n");
            scanf("%d", &opcao);
        } else if (opcao !=1 && opcao !=2){
            printf("\n**Escolha uma opção válida**\n");
            scanf("%d", &opcao);
        }


    } while (opcao !=1 && opcao !=2);

    limparTela(os);

    while (game.endgame == 0 && game.jogadas <9){
        if (game.jogadas == 0){
            printf("\n\n");
            printTabuleiro(tabuleiro, &game);
            printf("\n\nPreparem-se para o Jogo!\n\n");
            getchar();
            jogadaTabuleiro(tabuleiro, &game, opcao);
            limparTela(os);
            verificaEndGame (tabuleiro, &game);
        }else{

            limparTela(os);
            printf("\n\n\n", game.jogadas);
            printTabuleiro(tabuleiro, &game);
            printf("\n\n");
            jogadaTabuleiro(tabuleiro, &game, opcao);
            limparTela(os);
            verificaEndGame (tabuleiro, &game);
        }
    }

    printf("\n\n\n");
    printTabuleiro(tabuleiro, &game);
    if (game.endgame == 1) printf("\n\n**JOGADOR 1 VENCEU**\n\n");
    else if (game.endgame == 2) printf("\n\n**JOGADOR 2 VENCEU**\n\n");
    else if (game.endgame == 0) printf("\n\n**JOGO TERMINOU EMPATADO**\n\n");
    else printf("\n\nALGUMA COISA DEU ERRADA AQUI, NÃO?!\n\n");


    getchar();

    return 0;
}

void limparTela(const char* os){

    if(os == "Windoze"){
        system("cls");
    } else system("clear");
}

void preencherTabuleiroVazio (char vetor[TAM][TAM], jogada *game){
    int i, j;
    for (i = 0; i < 3; i++){
        for ( j = 0; j < 3; j++ ){

            vetor[i][j] = ' ';

        }
    }

    game->endgame = 0;
    game->jogadas = 0;
}

void printTabuleiro (char vetor[TAM][TAM], jogada *game){
    int i, j;

    printf("\t %c \t|\t %c \t|\t %c \t\n", vetor[0][0], vetor[0][1], vetor[0][2]);
    printf("------------------------------------------------\n");
    printf("\t %c \t|\t %c \t|\t %c \t\n", vetor[1][0], vetor[1][1], vetor[1][2]);
    printf("------------------------------------------------\n");
    printf("\t %c \t|\t %c \t|\t %c \t\n", vetor[2][0], vetor[2][1], vetor[2][2]);

    game->jogadas++;
}

int jogadaTabuleiro(char vetor[TAM][TAM], jogada *game, int opcao){

    int linha, coluna, verifica=0;
    char linhachar;

    if ((game->jogadas % 2) != 0){

            while (verifica != 1 || linha == -1){

                if (verifica == 0){

                    printf("\n\nJogador 1, seu turno. Escolha a Linha e Coluna da sua jogada.\n");
                    fflush(stdin);
                    printf("Linha(A, B ou C): \n");
                    scanf("%c",&linhachar);
                    getchar();
                    linha = linhaChartoInt(linhachar);
                    printf("Coluna(1, 2 ou 3): \n");
                    scanf("%d",&coluna);
                    getchar();
                    coluna--;


                } else if (verifica == -1){


                    printf("\n\nJogador 1, esta posição não é válida. Escolha corretamente.\n");
                    fflush(stdin);
                    printf("Linha(A, B ou C): \n");
                    scanf("%c",&linhachar);
                    getchar();
                    linha = linhaChartoInt(linhachar);
                    printf("Coluna(1, 2 ou 3): \n");
                    scanf("%d",&coluna);
                    getchar();
                    coluna--;

                }

                if (vetor[linha][coluna] != ' ' || linha==-1) verifica = -1;
                else {

                    vetor[linha][coluna] = 'X';
                    verifica = 1;

                }
            }
        }

        else if ((game->jogadas % 2) == 0){

            while (verifica != 1 || linha == -1){

                if (verifica == 0){

                    printf("\n\nJogador 2, seu turno. Escolha a Linha e Coluna da sua jogada.\n");
                    fflush(stdin);
                    if (opcao == 1){
                        printf("Linha(A, B ou C): \n");
                        scanf("%c",&linhachar);
                        getchar();
                        linha = linhaChartoInt(linhachar);
                        printf("Coluna(1, 2 ou 3): \n");
                        scanf("%d",&coluna);
                        getchar();
                        coluna--;
                    }


                } else if (verifica == -1){

                        printf("\n\nJogador 2, esta posição não é válida. Escolha corretamente.\n");
                        fflush(stdin);
                        printf("Linha(A, B ou C): \n");
                        scanf("%c",&linhachar);
                        getchar();
                        linha = linhaChartoInt(linhachar);
                        printf("Coluna(1, 2 ou 3): \n");
                        scanf("%d",&coluna);
                        getchar();
                        coluna--;

                }

                if (opcao == 1){
                    if (vetor[linha][coluna] != ' ' || linha==-1) verifica = -1;
                    else {
                    vetor[linha][coluna] = 'O';
                    verifica = 1;

                }

                } else {
                    int jogadas = game->jogadas;
                    int number = respostaAI(vetor, jogadas);
                    linha = number / 10;
                    coluna = number % 10;

                    if (vetor[linha][coluna] != ' ' || linha==-1) verifica = -1;
                    else {

                        vetor[linha][coluna] = '0';
                        verifica = 1;

                    }
                }

            }
        }
}

int linhaChartoInt (char letra){
    int num;

    if (letra == 'A' || letra == 'a') num = 0;
    else if (letra == 'B' || letra == 'b') num = 1;
    else if (letra == 'C' || letra == 'c') num = 2;
    else num = -1;

    return num;
}

int verificaEndGame (char vetor[TAM][TAM], jogada *game){
    int i, j;

    if  (   (vetor[0][0]=='X' && vetor[0][1]=='X' && vetor[0][2]=='X') ||
            (vetor[1][0]=='X' && vetor[1][1]=='X' && vetor[1][2]=='X') ||
            (vetor[2][0]=='X' && vetor[2][1]=='X' && vetor[2][2]=='X')
        ) {
            game->endgame = 1;
        }

    else if  (   (vetor[0][0]=='X' && vetor[1][0]=='X' && vetor[2][0]=='X') ||
            (vetor[0][1]=='X' && vetor[1][1]=='X' && vetor[2][1]=='X') ||
            (vetor[0][2]=='X' && vetor[1][2]=='X' && vetor[2][2]=='X')
        ) {
            game->endgame = 1;
        }

    else if  (   (vetor[0][0]=='X' && vetor[1][1]=='X' && vetor[2][2]=='X') ) {
            game->endgame = 1;
        }

    else if  (   (vetor[2][0]=='X' && vetor[1][1]=='X' && vetor[0][2]=='X') ) {
            game->endgame = 1;
        }

    if  (   (vetor[0][0]=='0' && vetor[0][1]=='0' && vetor[0][2]=='0') ||
            (vetor[1][0]=='0' && vetor[1][1]=='0' && vetor[1][2]=='0') ||
            (vetor[2][0]=='0' && vetor[2][1]=='0' && vetor[2][2]=='0')
        ) {
            game->endgame = 2;
        }

    else if  (   (vetor[0][0]=='0' && vetor[1][0]=='0' && vetor[2][0]=='0') ||
            (vetor[0][1]=='0' && vetor[1][1]=='0' && vetor[2][1]=='0') ||
            (vetor[0][2]=='0' && vetor[1][2]=='0' && vetor[2][2]=='0')
        ) {
            game->endgame = 2;
        }

    else if  (   (vetor[0][0]=='0' && vetor[1][1]=='0' && vetor[2][2]=='0') ) {
            game->endgame = 2;
        }

    else if  (   (vetor[2][0]=='0' && vetor[1][1]=='0' && vetor[0][2]=='0') ) {
            game->endgame = 2;
        }
}

int respostaAI (char vetor[TAM][TAM], int jogadas){
    int i, j, k;
    int vetorpesos[TAM][TAM];

    for (i = 0; i < TAM; i++){
        for (j = 0; j < TAM; j++){
            vetorpesos[i][j] = 0;
        }
    }

    // Pesos X no meio esquerdo
    if (vetor[1][0] ==  'X'){
        if (vetor[1][1] ==  'X') vetorpesos[1][2]+=3;
        else if (vetor[1][2] ==  'X') vetorpesos[1][1]+=3;
        else {
            if (vetor[1][1] == ' ') vetorpesos[1][1]++;
            if (vetor[1][2] == ' ') vetorpesos[1][2]++;
        }
    }

    // Pesos X no meio direito
    if (vetor[1][2] ==  'X'){
        if (vetor[1][1] ==  'X') vetorpesos[1][0]+=3;
        else if (vetor[1][0] ==  'X') vetorpesos[1][1]+=3;
        else {
            if (vetor[1][1] == ' ') vetorpesos[1][1]++;
            if (vetor[1][0] == ' ') vetorpesos[1][0]++;
        }
    }

    // Pesos X no meio esquerdo-cima
    if (vetor[0][1] ==  'X'){
        if (vetor[1][1] ==  'X') vetorpesos[2][1]+=3;
        else if (vetor[2][1] ==  'X') vetorpesos[1][1]+=3;
        else {
            if (vetor[1][1] == ' ') vetorpesos[1][1]++;
            if (vetor[2][1] == ' ') vetorpesos[2][1]++;
        }
    }

    // Pesos X no meio esquerdo-baixo
    if (vetor[2][1] ==  'X'){
        if (vetor[1][1] ==  'X') vetorpesos[0][1]+=3;
        else if (vetor[0][1] ==  'X') vetorpesos[1][1]+=3;
        else {
            if (vetor[1][1] == ' ') vetorpesos[1][1]++;
            if (vetor[0][1] == ' ') vetorpesos[0][1]++;
        }
    }

    // Pesos para X no centro
    if (vetor[1][1] ==  'X'){
        if (vetor[0][0] ==  'X') vetorpesos[2][2]+=2;
        else if (vetor[2][2] ==  'X') vetorpesos[0][0]+=2;
        else {
            if (vetor[0][0] == ' ') vetorpesos[0][0]++;
            if (vetor[0][2] == ' ') vetorpesos[0][2]++;
            if (vetor[2][0] == ' ') vetorpesos[2][0]++;
            if (vetor[2][2] == ' ') vetorpesos[2][2]++;
        }
    }

    // Pesos para X no centro por linha
    for (i = 0; i < 3; i++){
        if (i == 0 || i == 2){
            if (vetor[i][1] ==  'X'){
                if (vetor[i][0] ==  'X') vetorpesos[i][2]+= 2;
                else if (vetor[i][2] ==  'X') vetorpesos[i][0]+= 2;
                else {
                    if (vetor[i][0] == ' ') vetorpesos[i][0]++;
                    if (vetor[i][2] == ' ') vetorpesos[i][2]++;
                }
            }
        }
    }

    // Pesos para X no centro por coluna
    for (i = 0; i <3; i++){
        if (i==0 || i==2){
            if (vetor[1][i] ==  'X'){
                if (vetor[i][0] ==  'X') vetorpesos[2][i]+= 2;
                else if (vetor[2][i] ==  'X') vetorpesos[0][i]+= 2;
                else {
                    if (vetor[0][i] == ' ') vetorpesos[0][i]++;
                    if (vetor[2][i] == ' ') vetorpesos[2][i]++;
                }
            }
        }
    }

    // Pesos para X nas quinas
    // X Esquerda em Cima
    if (vetor[0][0] ==  'X'){

        //Linha
        if (vetor[0][1] ==  'X') vetorpesos[0][2]+= 2;
        else if (vetor[0][2] ==  'X') vetorpesos[0][1]+= 2;
        else {
            if (vetor[0][1] == ' ') vetorpesos[0][1]++;
            if (vetor[0][2] == ' ') vetorpesos[0][2]++;
        }

        //Coluna
        if (vetor[1][0] ==  'X') vetorpesos[2][0]+= 2;
        else if (vetor[2][0] ==  'X') vetorpesos[1][0]+= 2;
        else {
            if (vetor[1][0] == ' ') vetorpesos[1][0]++;
            if (vetor[2][0] == ' ') vetorpesos[2][0]++;
        }

        //Vertical
        if (vetor[1][1] ==  'X') vetorpesos[2][2]+= 2;
        else if (vetor[2][2] ==  'X') vetorpesos[1][1]+= 2;
        else {
            if (vetor[1][1] == ' ') vetorpesos[1][1]++;
            if (vetor[2][2] == ' ') vetorpesos[2][2]++;
        }

    }

    // X Esquerda em Embaixo
    if (vetor[2][0] ==  'X'){

        //Linha
        if (vetor[2][1] ==  'X') vetorpesos[2][2]+= 2;
        else if (vetor[2][2] ==  'X') vetorpesos[2][1]+= 2;
        else {
            if (vetor[2][1] == ' ') vetorpesos[2][1]++;
            if (vetor[2][2] == ' ') vetorpesos[2][2]++;
        }

        //Coluna
        if (vetor[1][0] ==  'X') vetorpesos[0][0]+= 2;
        else if (vetor[0][0] ==  'X') vetorpesos[1][0]+= 2;
        else {
            if (vetor[1][0] == ' ') vetorpesos[1][0]++;
            if (vetor[0][0] == ' ') vetorpesos[0][0]++;
        }

        //Vertical
        if (vetor[1][1] ==  'X') vetorpesos[0][2]+= 2;
        else if (vetor[0][2] ==  'X') vetorpesos[1][1]+= 2;
        else {
            if (vetor[1][1] == ' ') vetorpesos[1][1]++;
            if (vetor[0][2] == ' ') vetorpesos[0][2]++;
        }

    }

 // X Direita em Em cima
    if (vetor[0][2] ==  'X'){

        //Linha
        if (vetor[0][1] ==  'X') vetorpesos[0][0]+= 2;
        else if (vetor[0][0] ==  'X') vetorpesos[0][1]+= 2;
        else {
            if (vetor[0][1] == ' ') vetorpesos[0][1]++;
            if (vetor[0][0] == ' ') vetorpesos[0][0]++;
        }

        //Coluna
        if (vetor[1][2] ==  'X') vetorpesos[2][2]+= 2;
        else if (vetor[2][2] ==  'X') vetorpesos[1][2]+= 2;
        else {
            if (vetor[1][2] == ' ') vetorpesos[1][2]++;
            if (vetor[2][2] == ' ') vetorpesos[2][2]++;
        }

        //Vertical
        if (vetor[1][1] ==  'X') vetorpesos[2][0]+= 2;
        else if (vetor[2][0] ==  'X') vetorpesos[1][1]+= 2;
        else {
            if (vetor[1][1] == ' ') vetorpesos[1][1]++;
            if (vetor[2][0] == ' ') vetorpesos[2][0]++;
        }

    }

// X Direita em Embaixo
    if (vetor[2][2] ==  'X'){

        //Linha
        if (vetor[2][1] ==  'X') vetorpesos[2][0]+= 2;
        else if (vetor[2][0] ==  'X') vetorpesos[2][1]+= 2;
        else {
            if (vetor[2][1] == ' ') vetorpesos[2][1]++;
            if (vetor[2][0] == ' ') vetorpesos[2][0]++;
        }

        //Coluna
        if (vetor[1][2] ==  'X') vetorpesos[0][2]+= 2;
        else if (vetor[0][2] ==  'X') vetorpesos[1][2]+= 2;
        else {
            if (vetor[0][2] == ' ') vetorpesos[0][2]++;
            if (vetor[1][2] == ' ') vetorpesos[1][2]++;
        }

        //Vertical
        if (vetor[1][1] ==  'X') vetorpesos[0][0]+= 2;
        else if (vetor[0][0] ==  'X') vetorpesos[1][1]+= 2;
        else {
            if (vetor[1][1] == ' ') vetorpesos[1][1]++;
            if (vetor[0][0] == ' ') vetorpesos[0][0]++;
        }
    }

    //Seqencia de cálculos para vitória
    //Linhas
    if (vetor[0][0]=='0' && vetor[0][1]=='0') vetorpesos[0][2]+=5; else if (vetor[0][0]=='0' && vetor[0][2]=='0') vetorpesos[0][1]+=5;
    if (vetor[1][0]=='0' && vetor[1][1]=='0') vetorpesos[1][2]+=5; else if (vetor[1][0]=='0' && vetor[1][2]=='0') vetorpesos[1][1]+=5;
    if (vetor[2][0]=='0' && vetor[2][1]=='0') vetorpesos[2][2]+=5; else if (vetor[2][0]=='0' && vetor[2][2]=='0') vetorpesos[2][1]+=5;

    //Colunas
    if (vetor[0][0]=='0' && vetor[1][0]=='0') vetorpesos[2][0]+=5; else if (vetor[0][0]=='0' && vetor[2][0]=='0') vetorpesos[1][0]+=5;
    if (vetor[0][1]=='0' && vetor[1][1]=='0') vetorpesos[2][1]+=5; else if (vetor[0][1]=='0' && vetor[2][1]=='0') vetorpesos[1][1]+=5;
    if (vetor[0][2]=='0' && vetor[1][2]=='0') vetorpesos[2][2]+=5; else if (vetor[0][2]=='0' && vetor[2][2]=='0') vetorpesos[1][2]+=5;

    //Diagonais
    if (vetor[0][0]=='0' && vetor[1][1]=='0') vetorpesos[2][2]+=5; else if (vetor[0][0]=='0' && vetor[2][2]=='0') vetorpesos[1][1]+=5;
    if (vetor[2][0]=='0' && vetor[1][1]=='0') vetorpesos[0][2]+=5; else if (vetor[2][0]=='0' && vetor[2][2]=='0') vetorpesos[1][1]+=5;

    //Jogada inicial: priorizar centro
    if (vetor[1][1] == ' ' && jogadas == 2 ) vetorpesos[1][1] +=6;

    //cálculos do AI
    printf("\n\n %d | %d | %d \n%d | %d | %d \n%d | %d | %d \n\n", vetorpesos[0][0], vetorpesos[0][1], vetorpesos[0][2], vetorpesos[1][0], vetorpesos[1][1], vetorpesos[1][2], vetorpesos[2][0], vetorpesos[2][1], vetorpesos[2][2]);

    getchar();

    int maiorLC = 0;
    int maiorvalor = 0;

    for (i = 0; i < TAM; i++){
        for (j = 0; j < TAM; j++){
            if (vetorpesos[i][j] > maiorvalor && vetor[i][j] == ' ') {
                maiorvalor = vetorpesos[i][j];
                maiorLC = i*10;
                maiorLC = maiorLC + j;
            }
        }
    }

    return maiorLC;
}
