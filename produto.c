#include "produto.h"
#include <stdio.h>
#include <stdlib.h>
#include "cabecalho.h"
#include "arvoreB.h"
#pragma warning(disable : 4996)


//le um produto em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de produto
// pos deve ser uma posicao valida no arquivo
//Pos-condicao: ponteiro para produto lido e retornado
Produto* le_produto(FILE* arq, int pos)
{
	Produto* x = (Produto*)malloc(sizeof(Produto));
	if (pos < 0)
	{
		return NULL;
	}
	fseek(arq, sizeof(cabecalho) + pos * sizeof(Produto), SEEK_SET);
	fread(x, sizeof(Produto), 1, arq);
	return x;
}

//Escreve um produto em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de produto
// pos deve ser uma posicao valida do arquivo
//Pos-condicao: produto escrito no arquivo
void escreve_produto(FILE* arq, Produto* x, int pos)
{
	fseek(arq, sizeof(cabecalho) + pos * sizeof(Produto), SEEK_SET);
	fwrite(x, sizeof(Produto), 1, arq);
}

//acha a proxima posição a ser utilizada no arquivo de produtos
//pre-condição: arquivo para produtos válido
//pos-condição: proxima posição
int nextPositionProdts(FILE* arqProd)
{
	int pos = 0;
	cabecalho* cab = le_cabecalho(arqProd);
	if (cab->pos_livre == -1)
	{
		pos = cab->pos_topo++;
		escreve_cabecalho(arqProd, cab);
		free(cab);
		return pos;
	}
	pos = cab->pos_livre;//posicao pega das livres
	Produto* pro = le_produto(arqProd, cab->pos_livre);//le o produto da posição livre
	cab->pos_livre = pro->codigo;//código é a proxima posiçao livre
	escreve_cabecalho(arqProd, cab);//reescreve o cabecalho com a nova posiçao livre
	free(cab);
	free(pro);
	return pos;
}

//adiciona uma posicao às livres
//pre-condição: posicao válida
//pos-condição: atualiza cabecalho com a inclusao da posição
void addPosLivreProd(FILE* arqProd, int posicao)
{
	cabecalho* cab = le_cabecalho(arqProd);
	Produto* p = le_produto(arqProd, posicao);
	if (p != NULL)
	{
		p->codigo = cab->pos_livre;
		escreve_produto(arqProd, p, posicao);
		cab->pos_livre = posicao;
		escreve_cabecalho(arqProd, cab);
		free(p);
	}
	free(cab);
}

//acha o produto e sua posição no arquivo de produtos
//pre-condiçao: nenhuma
//pos-condição: retorna NULL e *pos = -1 se nao achar, se achar retorna o produto e sua posicao.
Produto* findProdutoByCodigo(FILE* arqArv ,FILE* arqProd,int codigo, int* pos_produto)
{
	int pos;
	
	arvoreB* a = busca(arqArv, le_no(arqArv, getPosRaiz(arqArv)), codigo, &pos);
	if (a != NULL)
	{
		(*pos_produto) = a->ptDados[pos];
		Produto* p = le_produto(arqProd, a->ptDados[pos]);
		free(a);
		return p;
	}
	else
	{
		(*pos_produto) = -1;
		return NULL;
	}
}



//imprime um produto
//Pré-condição: produto nao nulo
//pós-condiçao: nenhuma
void imprime_produto(Produto* aux)
{
	if (aux != NULL)
	{
		printf("Código: %d\n", aux->codigo);
		printf("Nome: %s\n", aux->nome);
		printf("Preço: %.2f\n", aux->preco);
		printf("Quantidade: %d\n", aux->quantidade);
		printf("Localização: %s\n", aux->localizacao);
	}
}




