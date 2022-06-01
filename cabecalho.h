#pragma once
#include <stdlib.h>
#include <stdio.h>

// cabecalho do arquivo da árvore 
typedef struct cabecalho
{
	int pos_raiz; //posicao da raiz da arvore
	int pos_topo; // 1a posicão não usada no fim do arquivo
	int pos_livre; // posição livre
}cabecalho;

//Le o cabecalho do arquivo contendo as informacoes da arvoreB;
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de árvoreB
//Pos-condicao: retorna o ponteiro para o cabecalho lido
cabecalho* le_cabecalho(FILE* arq);

//Escreve no arquivo o cabecalho contendo as informacoes da arvore
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de arvoreB
//Pos-condicao: cabecalho escrito no arquivo
void escreve_cabecalho(FILE* arq, cabecalho* cab);

//muda a raiz no cabecalho
//pré-condiçao: arquivo para arvoreB
//pos-condição: nenhuma
void mudarRaiz(FILE* arq, int raiz);

//Cria uma árvore nova em arquivo
//Pre-condicao: arquivo aberto para leitura/escrita
//Pos-condicao: arquivo e inicializado com uma árvore vazia
void cria_arvore_vazia(FILE* arq);

//retorna a posicao da raiz no arquivo
//pre-condiçao: arquivo para arvore
//pos-condiçao: retorna  a posiçao atual da raiz
int getPosRaiz(FILE* arq);

//retorna a posicao do top do arquivo.
//pre-condição: arquivo com cabecalho de raiz.
//pos-condição: posicao do top
int getPosTop(FILE* arq);