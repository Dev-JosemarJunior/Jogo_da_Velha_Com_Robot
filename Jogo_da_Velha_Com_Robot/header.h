#ifndef UTIL_H
#define UTIL_H
#define TAM 3


typedef struct estrutura{
	int jogadas;
	int endgame;
} jogada;

void limparTela(const char* os);

void preencherTabuleiroVazio (char tabuleiro[TAM][TAM], jogada *game);

void printTabuleiro (char tabuleiro[TAM][TAM], jogada *game);

int jogadaTabuleiro(char vetor[TAM][TAM], jogada *game, int opcao);

int linhaChartoInt (char letra);

int verificaEndGame (char vetor[TAM][TAM], jogada *game);

int respostaAI (char vetor[TAM][TAM], int jogadas);

#endif // UTIL_H
