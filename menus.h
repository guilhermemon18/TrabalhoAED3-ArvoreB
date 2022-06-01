#pragma once
#include "menus.h"
#include "arvoreB.h"
#include "controle.h"

//apresenta o menu princial com as op�oes do programa
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuPrincipal(FILE* arqArv,FILE* arqProd);

//apresenta menu de inser��o de um novo produto
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuInserir(arqArv, arqProd);

//apresenta menu de altera��o de preco
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuAlterarPreco(FILE* arqArv, FILE* arqProd);

//apresenta menu de altera��o de estoque
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuAlterarEstoque(FILE* arqArv, FILE* arqProd);

//apresenta menu de altera��o de localiza��o
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuAlterarLocalizacao(FILE* arqArv, FILE* arqProd);

//apresenta um menu de impressao de produto por c�digo
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuInformacoesProduto(FILE* arqArv, FILE* arqProd);

//apresenta um menu que lista os produtos
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuListarProdutos(FILE* arqArv, FILE* arqProd);

//lista os produtos da arvore 
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void listarProdutosAux(arvoreB* r, FILE* arqArv, FILE* arqProd);

//imprime as posi��es livres no arquivo da arvoreB de chaves
//Pr�-condi��o: arquivo valido para arvoreB
//p�s-condi�ao:nenhuma
void imprimirPosicoesLivresChaves(FILE* arq);

//imprime as posi��es livres no arquivo de produtos
//Pr�-condi��o: arquivo valido para produto
//p�s-condi�ao:nenhuma
void imprimirPosicoesLivresProdutos(FILE* arq);

//apresenta um MENU  de remo��o.
//pr�-condi��o: arquivos v�lidos para arvore de chaves e produtos.
//pos-condi��o: remo��o no arquivo da chave ou msg na tela informando que nao achou a chave.
void menuRemover(FILE* arqArv,FILE* arqProd);

//apresenta um MENU que carrega a arvoreB com um arquivo de texto com opera��es.
//pr�-condi��o: Arquivo para produtos e arquivo para �rvore v�lidos.
//p�s-condi��o: opera��es na arvore
void carregarArquivoTexto(FILE* arqArv, FILE* arqProd);




