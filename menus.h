#pragma once
#include "menus.h"
#include "arvoreB.h"
#include "controle.h"

//apresenta o menu princial com as opçoes do programa
//Pré-condição:arquivo aberto de arvoreB e arquivo aberto de produto
//pós-condiçao:nenhuma
void menuPrincipal(FILE* arqArv,FILE* arqProd);

//apresenta menu de inserção de um novo produto
//Pré-condição:arquivo aberto de arvoreB e arquivo aberto de produto
//pós-condiçao:nenhuma
void menuInserir(arqArv, arqProd);

//apresenta menu de alteração de preco
//Pré-condição:arquivo aberto de arvoreB e arquivo aberto de produto
//pós-condiçao:nenhuma
void menuAlterarPreco(FILE* arqArv, FILE* arqProd);

//apresenta menu de alteração de estoque
//Pré-condição:arquivo aberto de arvoreB e arquivo aberto de produto
//pós-condiçao:nenhuma
void menuAlterarEstoque(FILE* arqArv, FILE* arqProd);

//apresenta menu de alteração de localização
//Pré-condição:arquivo aberto de arvoreB e arquivo aberto de produto
//pós-condiçao:nenhuma
void menuAlterarLocalizacao(FILE* arqArv, FILE* arqProd);

//apresenta um menu de impressao de produto por código
//Pré-condição:arquivo aberto de arvoreB e arquivo aberto de produto
//pós-condiçao:nenhuma
void menuInformacoesProduto(FILE* arqArv, FILE* arqProd);

//apresenta um menu que lista os produtos
//Pré-condição:arquivo aberto de arvoreB e arquivo aberto de produto
//pós-condiçao:nenhuma
void menuListarProdutos(FILE* arqArv, FILE* arqProd);

//lista os produtos da arvore 
//Pré-condição:arquivo aberto de arvoreB e arquivo aberto de produto
//pós-condiçao:nenhuma
void listarProdutosAux(arvoreB* r, FILE* arqArv, FILE* arqProd);

//imprime as posições livres no arquivo da arvoreB de chaves
//Pré-condição: arquivo valido para arvoreB
//pós-condiçao:nenhuma
void imprimirPosicoesLivresChaves(FILE* arq);

//imprime as posições livres no arquivo de produtos
//Pré-condição: arquivo valido para produto
//pós-condiçao:nenhuma
void imprimirPosicoesLivresProdutos(FILE* arq);

//apresenta um MENU  de remoção.
//pré-condição: arquivos válidos para arvore de chaves e produtos.
//pos-condição: remoção no arquivo da chave ou msg na tela informando que nao achou a chave.
void menuRemover(FILE* arqArv,FILE* arqProd);

//apresenta um MENU que carrega a arvoreB com um arquivo de texto com operações.
//pré-condição: Arquivo para produtos e arquivo para árvore válidos.
//pós-condição: operações na arvore
void carregarArquivoTexto(FILE* arqArv, FILE* arqProd);




