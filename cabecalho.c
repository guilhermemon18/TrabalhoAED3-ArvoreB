#include "cabecalho.h"
#include <stdlib.h>
#include <stdio.h>
//o cabecalho � universal e pode ser usado para v�rias organiza��es nos arquivos


//Le o cabecalho do arquivo contendo as informacoes da arvoreB;
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de arvoreB
//Pos-condicao: retorna o ponteiro para o cabecalho lido
cabecalho* le_cabecalho(FILE* arq)
{
	cabecalho* cab = (cabecalho*)malloc(sizeof(cabecalho));
	fseek(arq, 0, SEEK_SET); // posiciona no inicio do arquivo
	fread(cab, sizeof(cabecalho), 1, arq);//le o cabecalho do arquivo e retorna a estrutura com os dados.
	return cab;
}

//Escreve no arquivo o cabecalho contendo as informacoes da arvore
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de arvoreB
//Pos-condicao: cabecalho escrito no arquivo
void escreve_cabecalho(FILE* arq, cabecalho* cab)
{
	fseek(arq, 0, SEEK_SET); //posiciona no inicio do arquivo
	fwrite(cab, sizeof(cabecalho), 1, arq);//escreve no arquivo no cabecalho
}

//Cria uma �rvore nova em arquivo
//Pre-condicao: arquivo aberto para leitura/escrita
//Pos-condicao: arquivo e inicializado com uma �rvore vazia
void cria_arvore_vazia(FILE* arq)
{
	cabecalho* cab = (cabecalho*)malloc(sizeof(cabecalho));
	cab->pos_raiz = -1;
	cab->pos_topo = 0;
	cab->pos_livre = -1;
	escreve_cabecalho(arq, cab);
	free(cab);
}

//muda a raiz no cabecalho
//pr�-condi�ao: arquivo para arvoreB
//pos-condi��o: nenhuma
void mudarRaiz(FILE* arq, int raiz)
{
	cabecalho* cab = le_cabecalho(arq);
	cab->pos_raiz = raiz;
	escreve_cabecalho(arq, cab);
	free(cab);
}

//retorna a posicao da raiz no arquivo
//pre-condi�ao: arquivo para arvore
//pos-condi�ao: retorna  a posi�ao atual da raiz
int getPosRaiz(FILE* arq)
{
	cabecalho* cab = le_cabecalho(arq);
	int pos = cab->pos_raiz;
	free(cab);
	return pos;
}


//retorna a posicao do top do arquivo.
//pre-condi��o: arquivo com cabecalho de raiz.
//pos-condi��o: posicao do top
int getPosTop(FILE* arq)
{
	cabecalho* cab = le_cabecalho(arq);
	int pos = cab->pos_topo;
	free(cab);
	return pos;
}

//