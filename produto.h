#pragma once
#include <stdio.h>
#include <stdlib.h>


//estrutura para o produto da loja de materiais
typedef struct Produto
{
	int codigo;
	char nome[50];
	int quantidade;
	float preco;
	char localizacao[50];
}Produto;

//le um produto em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de produto
// pos deve ser uma posicao valida no arquivo
//Pos-condicao: ponteiro para produto lido e retornado
Produto* le_produto(FILE* arq, int pos);

//Escreve um produto em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de produto
// pos deve ser uma posicao valida do arquivo
//Pos-condicao: produto escrito no arquivo
void escreve_produto(FILE* arq, Produto* x, int pos);

//acha a proxima posi��o a ser utilizada no arquivo de produtos
//pre-condi��o: arquivo para produtos v�lido
//pos-condi��o: proxima posi��o
int nextPositionProdts(FILE* arqProd);

//adiciona uma posicao �s livres
//pre-condi��o: posicao v�lida
//pos-condi��o: atualiza cabecalho com a inclusao da posi��o
void addPosLivreProd(FILE* arqProd, int posicao);

//acha o produto e sua posi��o no arquivo de produtos
//pre-condi�ao: nenhuma
//pos-condi��o: retorna NULL e *pos = -1 se nao achar, se achar retorna o produto e sua posicao.
Produto* findProdutoByCodigo(FILE* arqArv, FILE* arqProd, int codigo, int* pos_produto);

//imprime um produto
//Pr�-condi��o: produto nao nulo
//p�s-condi�ao: nenhuma
void imprime_produto(Produto* aux);


