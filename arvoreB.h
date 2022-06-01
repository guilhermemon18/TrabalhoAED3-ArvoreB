#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "cabecalho.h"
#include "produto.h"

#define ORDEM 5
#define MIN ORDEM / 2


//estruturas imprimir por n�veis
struct noLista
{
	int info;
	struct noLista* prox;
};

typedef struct noLista noL;

typedef struct noFila
{
	struct noLista* inicio;
	struct noLista* fim;
} Fila;

//estrutura de no para arvore B
//tem uma posicao a mais de chave e ponteiro de filho para
//facilitar a implementa��o da operac�o de split
typedef struct no
{
	int posicao;
	int numChaves;
	int chave[ORDEM];//arvore so armazena os codigos dos produtos
	int ptDados[ORDEM];//localiza��o, respectivamente de cada chave, no arquivo de produtos
	int filho[ORDEM + 1];//filhos sao inteiros, posi�oes no arquivo de dados, filho[0] tamb�m usado para armazenar posicao livre.
	int pai;//inteiro que representa a localiza�ao do pai no arquivo
} arvoreB;

typedef struct noArq
{
	int numChaves;
	int chave[ORDEM];//arvore so armazena os codigos dos produtos
	int ptDados[ORDEM];//localiza��o, respectivamente de cada chave, no arquivo de produtos
	int filho[ORDEM + 1];//filhos sao inteiros, posi�oes no arquivo de dados, filho[0] tamb�m usado para armazenar posicao livre.
	int pai;//inteiro que representa a localiza�ao do pai no arquivo
}arvoreBarq;

//le um no em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de arvoreB
// pos deve ser uma posicao valida da arvoreB
//Pos-condicao: ponteiro para no lido e retornado
arvoreB* le_no(FILE* arq, int pos);

//Escreve um no em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de arvoreB
// pos deve ser uma posicao valida do arquivo
//Pos-condicao: no escrito no arquivo
void escreve_no(FILE* arq, arvoreB* x, int pos);

//Cria um no com os parametros passados
//pr�-condi��o: nenhuma
//pos-condi��o: retorna o n� criado
arvoreB* criaNo(int chaves[], int numChaves, int pai, int filhos[], int ptDados[]);

//cria uma raiz vazia
//pre-condi��o: nenhuma
//pos-condi�ao: ponteiro da arvoreB para raiz vazia
arvoreB* criaRaizVazia();

//verifica se o no e folha
//pr�-condi�ao: no nao nulo
//pos-conid�ao: 1 = sim, 0 = nao
int eh_folha(arvoreB* r);

//verifica se tem uma raiz no arquivo
//pre-condi�ao: arquivo de arvoreB aberto
//pos-condi�ao: 1 se tem 0 se nao tem.
int temRaiz(FILE* arqArv);

//verifica se um n�(lido) � nulo(arvore vazia)
//pre-condi�ao: n� lido
//pos-condi�ao: 0 se nao for vazia, !=0 se vazia
int vazia(arvoreB* r);

//verifica se deu overflow na arvoreB
//pre-condi��o: no n�o nulo
//pos-conid�ao: 1 se deu 0 se nao deu
int overflow(arvoreB* r);

// busca a posicao em que a chave info esta ou estaria em um no
//pre-condi��o: arvore nao nula
//pos-condicao retorna 1 se a chave esta presente ou 0 caso contrario
int buscaPos(arvoreB* r, int info, int* pos);

//Quebra o no x (com overflow) e retorna o no criado e chave m que
// deve ser promovida  e sua localiza��o no arquivo de dados(PtM)
arvoreB* split(FILE* arq, arvoreB* x, int* m, int* ptM);

//adiciona a um no 1 chave com 1 flho a
//um no em uma determinada posicao deslocando se necessario
//as outras chaves para a direita.
//pre-condi��o: arquivo v�ldio de arvore
//arvoreB nao nula e pos v�lida
//pos-condi��o: insercao a direita
void adicionaDireita(FILE* arq, arvoreB* r, int pos, int info, int ptDados, int filho);

//insere uma chave em uma arvore B nao vazia de arquivo.
//pre-condi��o: arquivo v�lido de chaves, arvoreB nao nula.
//pos-condi��o: inser��o no arquivo.
void insere_aux(FILE* arqArv, arvoreB* r, int info, int ptDados);

//insere uma chave na arvore do arquivo
//pre-condi�ao: arquivo de arvore binaria
//pos-condi��o: nenhuma
arvoreB* insere(FILE* arqArv, arvoreB* r, int info, int ptDados);

//acha a proxima posi��o a ser utilizada no arquivo de chaves
//pre-condi��o: arquivo para arvoreB v�lido
//pos-condi��o: proxima posi��o
int nextPositionArv(FILE* arqArv);

//adiciona uma posicao �s livres
//pre-condi��o: posicao v�lida  a ser adicionada a lista de livres
//pos-condi��o: atualiza cabecalho com a inclusao da posi��o
void addPosLivreArv(FILE* arqArv, int posicao);

// retorna o no que contem info e sua posicao no no ou
//pre-condi�ao ler o no da raiz e passar para o ponteiro r;
// NULL se info nao esta na arvore.
arvoreB* busca(FILE* arq, arvoreB* r, int info, int* pos);

//----------------fun��es de imprimir n�veis-----------------------///
//busca o n�vel de uma chave na arvore R.
//pre-condi��o: arquivo v�lido de arvoreB, count come�a em zero na primeira chamada
//pos-condi��o: o nivel da chave.
int buscaNivel(FILE* arq, arvoreB* r, int chave, int count);

//coloca os filhos na fila.
//pre-condi��o: arquivo valido para arvoreB.
//pos-condi��o: coloca os filhos na fila.
void enfileiraFilhos(FILE* arq, arvoreB* r, Fila* f);

//enfileira um elemento na fila
//pre-condi��o: fila v�lida.
//pos-condi��o: nenhuma.
void enqueue(Fila* f, int x);

//cria fila vazia
//pre-condi�ao: nenhuma
//pos-condi��o: fila vazia criada.
Fila* cria_fila_vazia();

//testa se uma fila � vazia.
//pre-condi��o: fila v�lida
//pos-condi��o: retorna se a fila � vazia
int vaziaFila(Fila* f);

//desinfileira uma fila.
int* dequeue(Fila* f);

//imprimr as chave da arvoreB por n�veis.
//pr�-condi��o: raiz lida e arquivo valido para arvoreB.
//pos-condi��o: impressao da arvore por n�veis.
void imprimir_por_niveis(FILE* arq, arvoreB* r);
//---------------------------------------------------------------///

//imprime a arvore in_ordem
//pre_condi�ao: arquivo de arvoreB v�lido
//pos_condi�ao: nenhuma
void in_ordem(FILE* arq,arvoreB* r);

//acha a menor chave da arvoreB
//pre-condi��o: arquivo v�lido de arvoreB e raiz nao nula, pois n�o tem como definir um minimo se nao tem informa��o.
//pos_condi��o:  a chave minima dessa arvore
int minimo(FILE* arqArv, arvoreB* r);

//acha a maior chave da arvore
//pre-condi��o: raiz da arvore nao nula
//pos-condi��o: o maximo dessa arvoreB
int maximo(FILE* arqArv, arvoreB* r);


//------------------------------------------REMO��O-----------------------------------------------------//
//acha a maior chave da arvore
//pre-condi��o: raiz da arvore nao nula
//pos-condi��o: o maximo dessa arvoreB e copia o ponteiro para os dados, a posicao dos dados recebe -1.
int maximoRemove(FILE* arqArv, arvoreB* r, int* pt);

//retorna o irmao esquerdo ou NULL se n�o tem irmao esquerdo.
//pre-condi��o: arvore do filho que quer achar seu irm�o esq, filho deve ter pai != NULL.
//pos-condi��o: no do irm�o esquerdo
arvoreB* find_irmao_esq(FILE* arqArv, arvoreB* filho);

//pre-condi�ao: arvore do filho que quer achar seu irmao direito, filho deve ter pai != NULL
//pos condi��o: n� com irmao direito
arvoreB* find_irmao_dir(FILE* arqArv, arvoreB* filho);

//acha a posi�ao da chave divisa entre irmao esq e irmao dir.
//pre-condi��o: os 2 irm�os devem ser filhos do memsmo pai.
//pos-condi��o: devolve o indice da chave que � divisa no pai entre os n�s, ou -1 caso de erro.
int find_pos_ch_sep(FILE* arqArv, arvoreB* irmaoEsq, arvoreB* irmaoDir);

//verifica se r pode emprestar
//pre-condi��o: nenhuma
//pos-condi�ao: 1 = sim, 0 = nao
int podeEmprestar(arvoreB* r);

//verfica se um no pode sofrer emprestimo dos seus irmaos
//pre-condi�ao: n� nao raiz
//pos-condi�ao: retorna 1 se puder, 0 se nao puder
int isEmprestimo(FILE* arqArv, arvoreB* r);

//redistribui a arvore r com base no irmao esq que p�de fazer emprestimo
//pre-condi��o: faz parte de remover, nao pode ser chamada solta
//pos-condi��o: redistribui r emprestando do irmao esq
void redistribuirByIrmaoEsquerdo(FILE* arqArv, arvoreB* r, arvoreB* esq);

//redistribui a arvore r com base no irmao dir que p�de fazer emprestimo
//pre-condi��o: faz parte de remover, nao pode ser chamada solta
//pos-condi��o: redistribui r emprestando do irmao dir
void redistribuirByIrmaoDireito(FILE* arqArv, arvoreB* r, arvoreB* dir);

//redistribui a arvore R com underflow
//pre-condi��o: fun��o chamada automaticamente por balancear, nao deve ser chamada solta
//pos-condi��o: redistribui a �rvore
void redistribuir(FILE* arqArv, arvoreB* r);

//verifica se deu underflow
//pre-condi�ao: arvore nao nula
//pos-conidi��o: 1 se deu, 0 se nao deu, underflow
int underflow(arvoreB* r);

//concatena r com seu irmao esquerdo = esq
//pr�-condi�ao: fun��o aux, nunca chmar manualmente, testar se o irmao esq � diferente de null antes
//pos-condi��o: concatena��o com irmao esquerdo
void concatenarComIrmaoEsquerdo(FILE* arqArv, arvoreB* r, arvoreB* esq);

//concatena r com seu irmao direito = dir
//pr�-condi�ao: fun��o aux, nunca chamar manualmente, testar se o irmao dir � diferente de null antes
//pos-condi��o: concatena��o com irmao direito
void concatenarComIrmaoDireito(FILE* arqArv, arvoreB* r, arvoreB* dir);

//faz a concatena��o, prioritariamente com o irmao esquerdo, se n�o o possuir, com o direito
// pr�-condi��o: n� com underflow e que tenha sido redirecionado pela fun��o balancear para fazer concatena��o
//nao chamar esssa fun��o manualmente, so deve ser chamada pela balancear
//pos-condi��o: concatena o no com o irmao sequerdo se possuir, ou direito caso nao possua irmao esquerdo
void concatenar(FILE* arqArv, arvoreB* r);

//testa se � raiz
//pre-condi��o: r nao pode ser NULL
//pos-condi��o: 1 se for raiz, 0 se nao for
int eh_raiz(arvoreB* r);

//faz redistribui��o se poss�vel, ou faz concatena��o para ajustar o no com underflow
//pr�-condi��o: no que ficou com underflow
//pos-condi��o: balanceia o n�
void balancear(FILE* arqArv, arvoreB* r);

//remove um produto
//pre-condi��o: arqprod e arqArv, arquivos para produto e chaves respectivamente, v�lidos, r = leitura da raiz do arquivo de chaves
//pos-condi��o retorna a nova raiz;
arvoreB* remover(FILE* arqProd, FILE* arqArv, arvoreB* r, int x);

