#include "controle.h"

//insere na arvoreB de chaves e o produto no arquivo de produtos
//pre-condiçao: arqARv e arqProd ponteiros para arquivo válidos(abertos) e prod ponteiro nao nulo de Produto
//pos-condição: nenhuma
void inserir(FILE* arqArv, FILE* arqProd, Produto* prod)
{
	int pos_busca;
	arvoreB* r =  le_no(arqArv, getPosRaiz(arqArv));
	if (busca(arqArv, r, prod->codigo, &pos_busca) != NULL)//retornou != NULL, entao ja tem a chave na arvore.
	{
		free(r);
		return;//sai da função
	}
	int posicao = nextPositionProdts(arqProd);
	escreve_produto(arqProd, prod,posicao);
	r = insere(arqArv, r, prod->codigo, posicao);
	
	free(r);
}

//alterar um produto
//pre-condição: arqARv e arqProd ponteiros para arquivo válidos(abertos) e
//prod ponteiro nao nulo de Produto, produto deve ter o código do produto a ser alterado;
//pos-condição: alterar no sentido geral, tudo que tiver em novo produto
void alterar(FILE* arqArv, FILE* arqProd, Produto* newProd)
{
	int pos_busca;
	arvoreB* r = le_no(arqArv, getPosRaiz(arqArv));
	if (busca(arqArv, r, newProd->codigo, &pos_busca) == NULL)//retornou NULL, entao nao tem a chave na arvore, nao fazer nada.
	{
		return;//sai da função
	}
	arvoreB* a = busca(arqArv, r, newProd->codigo, &pos_busca);
	escreve_produto(arqProd, newProd, a->ptDados[pos_busca]);
	//free(r);
	free(a);
}

// remove um produto dada sua chave x
//pre-condição: arqprod e arqArv, arquivos para produto e chaves respectivamente, válidos, r = leitura da raiz do arquivo de chaves
//pos-condição: nenhuma;
void Remover(FILE* arqProd, FILE* arqArv,  int x)
{
	int pos;
	Produto* p = findProdutoByCodigo(arqArv, arqProd, x, &pos);
	if (p != NULL)//se != NULL, o produto existe
	{
		arvoreB* raiz = le_no(arqArv, getPosRaiz(arqArv));
		arvoreB* r = remover(arqProd, arqArv, raiz, x);
		
		//printf("REMOVER DO CONTROLE.C\n");
		//printf("Crashou aqui!!!!!!!!!!!!!!!!!!!!!!!!!!\n");//falar para o professor.
		//free(raiz);
		free(r);
		free(p);
	}
	
}