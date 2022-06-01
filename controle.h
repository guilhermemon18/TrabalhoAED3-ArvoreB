#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"
#include "cabecalho.h"
#include "produto.h"

//gerencia as funções do sistema;
//Une a árvoreB com os seus produtos para fazer as operações de inserção, alteração e remoção.

//insere na arvoreB de chaves e o produto no arquivo de produtos
//pre-condiçao: arqARv e arqProd ponteiros para arquivo válidos(abertos) e prod ponteiro nao nulo de Produto
//pos-condição: nenhuma
void inserir(FILE* arqArv, FILE* arqProd,Produto* prod);

//alterar um produto
//pre-condição: arqARv e arqProd ponteiros para arquivo válidos(abertos) e
//prod ponteiro nao nulo de Produto, produto deve ter o código do produto a ser alterado;
//alterar no sentido geral, tudo que tiver em novo produto
void alterar(FILE* arqArv, FILE* arqProd, Produto* newProd);


//remove um produto dada sua chave x
//pre-condição: arqprod e arqArv, arquivos para produto e chaves respectivamente, válidos, r = leitura da raiz do arquivo de chaves
//pos-condição: nenhuma;
void Remover(FILE* arqProd, FILE* arqArv, int x);
