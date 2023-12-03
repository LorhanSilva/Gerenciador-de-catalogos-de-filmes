#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stfilme{// Estrutura Filme.
    char titulo[81], diretor[51], genero[31];
    int lancamento, duracao;
}TFM;

typedef struct ArvB{ //árvore B com campo vetor de filmes associado a chave.
  int nchaves, folha, *chave;
  TFM** filmes;
  struct ArvB **filho;
}TARVB;

TARVB *TARVB_Inicializa();
TARVB *TARVB_Cria(int t);
TARVB *TARVB_Libera(TARVB *a);
TARVB *TARVB_Busca(TARVB* x, int ch);
TARVB *TARVB_Insere(TARVB *T, int k, TFM* f, int t);//Insere tbm recebe um TFM além da chave.
TARVB* TARVB_Retira(TARVB* arv, int k, int t);
void TARVB_Imprime(TARVB *a);

//Funcs para os filmes
TFM *cria_filme(char* nome, char* diretor, char* genero, int lancamento, int duracao);
void imprime_filme(TFM* filme);
TARVB *Busca_filmes(TARVB* x, int ch, int *pos);
int hash_filme(char* titulo, int data);//func para transformar titudo e lancamento em um inteiro.
