#pragma once
#include <stdlib.h>
#include <stdio.h>

// cabecalho do arquivo da �rvore 
typedef struct cabecalho
{
	int pos_raiz; //posicao da raiz da arvore
	int pos_topo; // 1a posic�o n�o usada no fim do arquivo
	int pos_livre; // posi��o livre
}cabecalho;

//Le o cabecalho do arquivo contendo as informacoes da arvoreB;
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de �rvoreB
//Pos-condicao: retorna o ponteiro para o cabecalho lido
cabecalho* le_cabecalho(FILE* arq);

//Escreve no arquivo o cabecalho contendo as informacoes da arvore
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de arvoreB
//Pos-condicao: cabecalho escrito no arquivo
void escreve_cabecalho(FILE* arq, cabecalho* cab);

//muda a raiz no cabecalho
//pr�-condi�ao: arquivo para arvoreB
//pos-condi��o: nenhuma
void mudarRaiz(FILE* arq, int raiz);

//Cria uma �rvore nova em arquivo
//Pre-condicao: arquivo aberto para leitura/escrita
//Pos-condicao: arquivo e inicializado com uma �rvore vazia
void cria_arvore_vazia(FILE* arq);

//retorna a posicao da raiz no arquivo
//pre-condi�ao: arquivo para arvore
//pos-condi�ao: retorna  a posi�ao atual da raiz
int getPosRaiz(FILE* arq);

//retorna a posicao do top do arquivo.
//pre-condi��o: arquivo com cabecalho de raiz.
//pos-condi��o: posicao do top
int getPosTop(FILE* arq);