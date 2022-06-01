#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"
#include "cabecalho.h"
#include "produto.h"

//gerencia as fun��es do sistema;
//Une a �rvoreB com os seus produtos para fazer as opera��es de inser��o, altera��o e remo��o.

//insere na arvoreB de chaves e o produto no arquivo de produtos
//pre-condi�ao: arqARv e arqProd ponteiros para arquivo v�lidos(abertos) e prod ponteiro nao nulo de Produto
//pos-condi��o: nenhuma
void inserir(FILE* arqArv, FILE* arqProd,Produto* prod);

//alterar um produto
//pre-condi��o: arqARv e arqProd ponteiros para arquivo v�lidos(abertos) e
//prod ponteiro nao nulo de Produto, produto deve ter o c�digo do produto a ser alterado;
//alterar no sentido geral, tudo que tiver em novo produto
void alterar(FILE* arqArv, FILE* arqProd, Produto* newProd);


//remove um produto dada sua chave x
//pre-condi��o: arqprod e arqArv, arquivos para produto e chaves respectivamente, v�lidos, r = leitura da raiz do arquivo de chaves
//pos-condi��o: nenhuma;
void Remover(FILE* arqProd, FILE* arqArv, int x);
