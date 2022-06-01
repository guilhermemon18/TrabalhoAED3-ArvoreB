#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "cabecalho.h"
#include "produto.h"

#define ORDEM 5
#define MIN ORDEM / 2


//estruturas imprimir por níveis
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
//facilitar a implementação da operacão de split
typedef struct no
{
	int posicao;
	int numChaves;
	int chave[ORDEM];//arvore so armazena os codigos dos produtos
	int ptDados[ORDEM];//localização, respectivamente de cada chave, no arquivo de produtos
	int filho[ORDEM + 1];//filhos sao inteiros, posiçoes no arquivo de dados, filho[0] também usado para armazenar posicao livre.
	int pai;//inteiro que representa a localizaçao do pai no arquivo
} arvoreB;

typedef struct noArq
{
	int numChaves;
	int chave[ORDEM];//arvore so armazena os codigos dos produtos
	int ptDados[ORDEM];//localização, respectivamente de cada chave, no arquivo de produtos
	int filho[ORDEM + 1];//filhos sao inteiros, posiçoes no arquivo de dados, filho[0] também usado para armazenar posicao livre.
	int pai;//inteiro que representa a localizaçao do pai no arquivo
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
//pré-condição: nenhuma
//pos-condição: retorna o nó criado
arvoreB* criaNo(int chaves[], int numChaves, int pai, int filhos[], int ptDados[]);

//cria uma raiz vazia
//pre-condição: nenhuma
//pos-condiçao: ponteiro da arvoreB para raiz vazia
arvoreB* criaRaizVazia();

//verifica se o no e folha
//prè-condiçao: no nao nulo
//pos-conidçao: 1 = sim, 0 = nao
int eh_folha(arvoreB* r);

//verifica se tem uma raiz no arquivo
//pre-condiçao: arquivo de arvoreB aberto
//pos-condiçao: 1 se tem 0 se nao tem.
int temRaiz(FILE* arqArv);

//verifica se um nó(lido) é nulo(arvore vazia)
//pre-condiçao: nó lido
//pos-condiçao: 0 se nao for vazia, !=0 se vazia
int vazia(arvoreB* r);

//verifica se deu overflow na arvoreB
//pre-condição: no não nulo
//pos-conidçao: 1 se deu 0 se nao deu
int overflow(arvoreB* r);

// busca a posicao em que a chave info esta ou estaria em um no
//pre-condição: arvore nao nula
//pos-condicao retorna 1 se a chave esta presente ou 0 caso contrario
int buscaPos(arvoreB* r, int info, int* pos);

//Quebra o no x (com overflow) e retorna o no criado e chave m que
// deve ser promovida  e sua localização no arquivo de dados(PtM)
arvoreB* split(FILE* arq, arvoreB* x, int* m, int* ptM);

//adiciona a um no 1 chave com 1 flho a
//um no em uma determinada posicao deslocando se necessario
//as outras chaves para a direita.
//pre-condição: arquivo váldio de arvore
//arvoreB nao nula e pos válida
//pos-condição: insercao a direita
void adicionaDireita(FILE* arq, arvoreB* r, int pos, int info, int ptDados, int filho);

//insere uma chave em uma arvore B nao vazia de arquivo.
//pre-condição: arquivo válido de chaves, arvoreB nao nula.
//pos-condição: inserção no arquivo.
void insere_aux(FILE* arqArv, arvoreB* r, int info, int ptDados);

//insere uma chave na arvore do arquivo
//pre-condiçao: arquivo de arvore binaria
//pos-condição: nenhuma
arvoreB* insere(FILE* arqArv, arvoreB* r, int info, int ptDados);

//acha a proxima posição a ser utilizada no arquivo de chaves
//pre-condição: arquivo para arvoreB válido
//pos-condição: proxima posição
int nextPositionArv(FILE* arqArv);

//adiciona uma posicao às livres
//pre-condição: posicao válida  a ser adicionada a lista de livres
//pos-condição: atualiza cabecalho com a inclusao da posição
void addPosLivreArv(FILE* arqArv, int posicao);

// retorna o no que contem info e sua posicao no no ou
//pre-condiçao ler o no da raiz e passar para o ponteiro r;
// NULL se info nao esta na arvore.
arvoreB* busca(FILE* arq, arvoreB* r, int info, int* pos);

//----------------funções de imprimir níveis-----------------------///
//busca o nível de uma chave na arvore R.
//pre-condição: arquivo válido de arvoreB, count começa em zero na primeira chamada
//pos-condição: o nivel da chave.
int buscaNivel(FILE* arq, arvoreB* r, int chave, int count);

//coloca os filhos na fila.
//pre-condição: arquivo valido para arvoreB.
//pos-condição: coloca os filhos na fila.
void enfileiraFilhos(FILE* arq, arvoreB* r, Fila* f);

//enfileira um elemento na fila
//pre-condição: fila válida.
//pos-condição: nenhuma.
void enqueue(Fila* f, int x);

//cria fila vazia
//pre-condiçao: nenhuma
//pos-condição: fila vazia criada.
Fila* cria_fila_vazia();

//testa se uma fila é vazia.
//pre-condição: fila válida
//pos-condição: retorna se a fila é vazia
int vaziaFila(Fila* f);

//desinfileira uma fila.
int* dequeue(Fila* f);

//imprimr as chave da arvoreB por níveis.
//pré-condição: raiz lida e arquivo valido para arvoreB.
//pos-condição: impressao da arvore por níveis.
void imprimir_por_niveis(FILE* arq, arvoreB* r);
//---------------------------------------------------------------///

//imprime a arvore in_ordem
//pre_condiçao: arquivo de arvoreB válido
//pos_condiçao: nenhuma
void in_ordem(FILE* arq,arvoreB* r);

//acha a menor chave da arvoreB
//pre-condição: arquivo válido de arvoreB e raiz nao nula, pois não tem como definir um minimo se nao tem informação.
//pos_condição:  a chave minima dessa arvore
int minimo(FILE* arqArv, arvoreB* r);

//acha a maior chave da arvore
//pre-condição: raiz da arvore nao nula
//pos-condição: o maximo dessa arvoreB
int maximo(FILE* arqArv, arvoreB* r);


//------------------------------------------REMOÇÃO-----------------------------------------------------//
//acha a maior chave da arvore
//pre-condição: raiz da arvore nao nula
//pos-condição: o maximo dessa arvoreB e copia o ponteiro para os dados, a posicao dos dados recebe -1.
int maximoRemove(FILE* arqArv, arvoreB* r, int* pt);

//retorna o irmao esquerdo ou NULL se não tem irmao esquerdo.
//pre-condição: arvore do filho que quer achar seu irmão esq, filho deve ter pai != NULL.
//pos-condição: no do irmão esquerdo
arvoreB* find_irmao_esq(FILE* arqArv, arvoreB* filho);

//pre-condiçao: arvore do filho que quer achar seu irmao direito, filho deve ter pai != NULL
//pos condição: nó com irmao direito
arvoreB* find_irmao_dir(FILE* arqArv, arvoreB* filho);

//acha a posiçao da chave divisa entre irmao esq e irmao dir.
//pre-condição: os 2 irmãos devem ser filhos do memsmo pai.
//pos-condição: devolve o indice da chave que é divisa no pai entre os nós, ou -1 caso de erro.
int find_pos_ch_sep(FILE* arqArv, arvoreB* irmaoEsq, arvoreB* irmaoDir);

//verifica se r pode emprestar
//pre-condição: nenhuma
//pos-condiçao: 1 = sim, 0 = nao
int podeEmprestar(arvoreB* r);

//verfica se um no pode sofrer emprestimo dos seus irmaos
//pre-condiçao: nó nao raiz
//pos-condiçao: retorna 1 se puder, 0 se nao puder
int isEmprestimo(FILE* arqArv, arvoreB* r);

//redistribui a arvore r com base no irmao esq que pôde fazer emprestimo
//pre-condição: faz parte de remover, nao pode ser chamada solta
//pos-condição: redistribui r emprestando do irmao esq
void redistribuirByIrmaoEsquerdo(FILE* arqArv, arvoreB* r, arvoreB* esq);

//redistribui a arvore r com base no irmao dir que pôde fazer emprestimo
//pre-condição: faz parte de remover, nao pode ser chamada solta
//pos-condição: redistribui r emprestando do irmao dir
void redistribuirByIrmaoDireito(FILE* arqArv, arvoreB* r, arvoreB* dir);

//redistribui a arvore R com underflow
//pre-condição: função chamada automaticamente por balancear, nao deve ser chamada solta
//pos-condição: redistribui a árvore
void redistribuir(FILE* arqArv, arvoreB* r);

//verifica se deu underflow
//pre-condiçao: arvore nao nula
//pos-conidição: 1 se deu, 0 se nao deu, underflow
int underflow(arvoreB* r);

//concatena r com seu irmao esquerdo = esq
//pré-condiçao: função aux, nunca chmar manualmente, testar se o irmao esq é diferente de null antes
//pos-condição: concatenação com irmao esquerdo
void concatenarComIrmaoEsquerdo(FILE* arqArv, arvoreB* r, arvoreB* esq);

//concatena r com seu irmao direito = dir
//pré-condiçao: função aux, nunca chamar manualmente, testar se o irmao dir é diferente de null antes
//pos-condição: concatenação com irmao direito
void concatenarComIrmaoDireito(FILE* arqArv, arvoreB* r, arvoreB* dir);

//faz a concatenação, prioritariamente com o irmao esquerdo, se não o possuir, com o direito
// pré-condição: nó com underflow e que tenha sido redirecionado pela função balancear para fazer concatenação
//nao chamar esssa função manualmente, so deve ser chamada pela balancear
//pos-condição: concatena o no com o irmao sequerdo se possuir, ou direito caso nao possua irmao esquerdo
void concatenar(FILE* arqArv, arvoreB* r);

//testa se é raiz
//pre-condição: r nao pode ser NULL
//pos-condição: 1 se for raiz, 0 se nao for
int eh_raiz(arvoreB* r);

//faz redistribuição se possível, ou faz concatenação para ajustar o no com underflow
//pré-condição: no que ficou com underflow
//pos-condição: balanceia o nó
void balancear(FILE* arqArv, arvoreB* r);

//remove um produto
//pre-condição: arqprod e arqArv, arquivos para produto e chaves respectivamente, válidos, r = leitura da raiz do arquivo de chaves
//pos-condição retorna a nova raiz;
arvoreB* remover(FILE* arqProd, FILE* arqArv, arvoreB* r, int x);

