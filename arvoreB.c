#include "arvoreB.h"
#include "cabecalho.h"
#include "produto.h"

//le um no em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de arvoreB
// pos deve ser uma posicao valida da arvoreB
//Pos-condicao: ponteiro para no lido e retornado
arvoreB* le_no(FILE* arq, int pos)
{
	arvoreB* x = malloc(sizeof(arvoreB));
	if (pos < 0)
	{
        free(x);
		return NULL;
	}
	fseek(arq, sizeof(cabecalho) + pos * sizeof(arvoreB), SEEK_SET);
	fread(x, sizeof(arvoreB), 1, arq);
  
	return x;
}

//Escreve um no em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de arvoreB
// pos deve ser uma posicao valida do arquivo
//Pos-condicao: no escrito no arquivo
void escreve_no(FILE* arq, arvoreB* x, int pos)
{
	fseek(arq, sizeof(cabecalho) + pos * sizeof(arvoreB), SEEK_SET);
	fwrite(x, sizeof(arvoreB), 1, arq);
}


//verifica se o no e folha
//prè-condiçao: no nao nulo
//pos-conidçao: 1 = sim, 0 = nao
int eh_folha(arvoreB* r)
{
	if (r->filho[0] == -1)
	{
		return 1;
	}
	return 0;
}

//verifica se tem uma raiz no arquivo
//pre-condiçao: arquivo de arvoreB aberto
//pos-condiçao: 1 se tem 0 se nao tem.
int temRaiz(FILE* arqArv)
{
	cabecalho* cab = le_cabecalho(arqArv);
	if (cab->pos_raiz == -1)
	{
		free(cab);
		return 0;
	}
	free(cab);
	return 1;
}

//verifica se um nó(lido) é nulo(arvore vazia)
//pre-condiçao: nó lido
//pos-condiçao: 0 se nao for vazia, !=0 se vazia
int vazia(arvoreB* r)
{
	return(r == NULL);
}

//cria uma raiz vazia
//pre-condição: nenhuma
//pos-condiçao: ponteiro da arvoreB para raiz vazia
arvoreB* criaRaizVazia()
{
	arvoreB* raiz = (arvoreB*)malloc(sizeof(arvoreB));
	raiz->numChaves = 0;
    for (int i = 0; i < ORDEM; i++)
    {
        raiz->filho[i] = -1;
        raiz->ptDados[i] = -1;
    }
	raiz->pai = -1;
	return raiz;
}

//Cria um no com os parametros passados
//pré-condição: nenhuma
//pos-condição: retorna o nó criado
arvoreB* criaNo(int chaves[],int numChaves,int pai,int filhos[],int ptDados[])
{
	arvoreB* no = (arvoreB*)malloc(sizeof(arvoreB));
	int i;
	for ( i = 0; i < ORDEM; i++)
	{
		no->chave[i] = chaves[i];
		no->ptDados[i] = ptDados[i];
		no->filho[i] = filhos[i];
	}
	no->filho[i] = filhos[i];
	no->numChaves = numChaves;
	no->pai = pai;
	return no;
}

//verifica se deu overflow na arvoreB
//pre-condição: no não nulo
//pos-conidçao: 1 se deu 0 se nao deu
int overflow(arvoreB* r)
{
	if (r != NULL)
	{
		if (r->numChaves == ORDEM)
			return 1;
	}
	return 0;
}

// busca a posicao em que a chave info esta ou estaria em um no
//pre-condição: arvore nao nula
// retorna 1 se a chave esta presente ou 0 caso contrario
int buscaPos(arvoreB* r, int info, int* pos)
{
	for ((*pos) = 0; (*pos) < r->numChaves; (*pos)++)
		if (info == r->chave[(*pos)])
			return 1; // chave ja esta na arvore
		else if (info < r->chave[(*pos)])
			break; // info pode estar na subarvore filho[*pos]
	return 0; // chave nao esta neste no
}

//Quebra o no x (com overflow) e retorna o no criado e chave m que
// deve ser promovida  e sua localização no arquivo de dados(PtM)
arvoreB* split(FILE* arq,arvoreB* x, int* m,int* ptM)
{
    
    arvoreB* y = criaRaizVazia();//(arvoreB*)malloc(sizeof(arvoreB));//nova arvore
    int pos = nextPositionArv(arq);
    y->posicao = pos;
	int q = x->numChaves / 2;
	y->numChaves = x->numChaves - q - 1;
	x->numChaves = q;
	*m = x->chave[q]; // chave mediana
	*ptM = x->ptDados[q];//sua localização nos arquivos de dados
	int i = 0;
	y->filho[0] = x->filho[q + 1];
	arvoreB* filho = le_no(arq, y->filho[0]);
	if (filho != NULL)
	{ //PAI
		filho->pai = y->posicao;//PAI
		escreve_no(arq, filho, filho->posicao);
	}
	free(filho);
	y->pai = x->pai;//PAI, o pai do y vai ser o mesmo do x
	for (i = 0; i < y->numChaves; i++)
	{
		y->chave[i] = x->chave[q + i + 1];
		y->ptDados[i] = x->ptDados[q + i + 1];
		y->filho[i + 1] = x->filho[q + i + 2];
		filho = le_no(arq, y->filho[i + 1]);
		if (filho != NULL)
		{//PAI
			filho->pai = y->posicao;//PAI
			escreve_no(arq, filho, filho->posicao);
			free(filho);
		}
	}
	escreve_no(arq, x, x->posicao);
	escreve_no(arq, y, y->posicao);
	return y;
}

//adiciona a um no 1 chave com 1 flho a
//um no em uma determinada posicao deslocando se necessario
//as outras chaves para a direita.
//pre-condição: arquivo váldio de arvore
//arvoreB nao nula e pos válida
//pos-condição: insercao a direita
void adicionaDireita(FILE* arq,arvoreB* r, int pos, int info,int ptDados, int filho)
{
	int i;
	for (i = r->numChaves; i > pos; i--)
	{
		r->ptDados[i] = r->ptDados[i - 1];
		r->chave[i] = r->chave[i - 1];
		r->filho[i + 1] = r->filho[i];
	}
	r->chave[pos] = info;
	r->ptDados[pos] = ptDados;
	r->filho[pos + 1] = filho;
	r->numChaves++;
	escreve_no(arq, r, r->posicao);

    arvoreB* f = le_no(arq, filho);
    if (f != NULL)
    {//PAI
        f->pai = r->posicao;//PAI
        escreve_no(arq, f, filho);
        free(f);
    }
    
}

//insere uma chave em uma arvore B nao vazia de arquivo.
//pre-condição: arquivo válido de chaves, arvoreB nao nula.
//pos-condição: inserção no arquivo.
void insere_aux(FILE* arqArv,arvoreB* r, int info,int ptDados)
{
	int pos;
	if (!buscaPos(r, info, &pos))//n encontrou, mas deu a posicao que estaria se encontrasse
	{ 
		if (eh_folha(r))//verifica se é folha, so pode inserir em folha
		{//entao adiciona a direita
			adicionaDireita(arqArv,r, pos, info,ptDados, -1);
		}
		else
		{//não é nó folha precisa descer mais, inserção só é no nó folha
			arvoreB* filho_pos = le_no(arqArv, r->filho[pos]);//liberar memoria
			insere_aux(arqArv,filho_pos, info,ptDados);//chama recurisvamente na posiçao que foi dada pela busca
			if (overflow(filho_pos))
			{//adicionou a chave, precisa ver se deu overflow, se deu precisa de split
				int m; // valor da chave mediana
				int ptM;//posicao no arquivo de dados da chave mediana
				arvoreB* aux = split(arqArv,filho_pos, &m,&ptM);
                if (aux != NULL)
                {
                    aux->pai = r->posicao;//PAI
                    escreve_no(arqArv, aux, aux->posicao);
                    adicionaDireita(arqArv, r, pos, m, ptM, aux->posicao);//em vez de aux tem que ser posicao de aux.
                    free(aux);//se bota aqui funciona, mas teoricamente nao devia dar problema botar ali embaixo.
                }
                else
                {
                    adicionaDireita(arqArv, r, pos, m, ptM, -1);//em vez de aux tem que ser posicao de aux.
                }
                //free(aux);//este free dá problema nao sei pq.
                
			}
			free(filho_pos);
		}
	}
}

//insere uma chave  e sua localização no arquivo de dados na arvore do arquivo
//pre-condiçao: arquivo de arvoreB,no da raiz lida do arquivo,o info(chave), e posiçao no arquivo de dados(ptDados), todos válidos
//pos-condição: nenhuma
arvoreB* insere(FILE* arqArv,arvoreB* r, int info,int ptDados)
{
	if (vazia(r))//raiz vazia == NULL, tentou ler pelo le_no e retornou NULL la, não tem raiz ainda
	{
        r = criaRaizVazia();
		r->chave[0] = info;
		r->ptDados[0] = ptDados;
		r->filho[0] = -1;//-1 = NULL
		r->numChaves = 1;
		r->pai = -1;//PAI = NULL = -1;
		int posicao = nextPositionArv(arqArv);
		r->posicao = posicao;
		escreve_no(arqArv, r, posicao);
		mudarRaiz(arqArv, posicao);
	}
	else
	{
		insere_aux(arqArv,r, info,ptDados);
		if (overflow(r))
		{
			int m;
			int ptM;
			arvoreB* x = split(arqArv,r, &m,&ptM);
            arvoreB* novaRaiz = criaRaizVazia();

			novaRaiz->chave[0] = m;
			novaRaiz->ptDados[0] = ptM;
			novaRaiz->filho[0] = r->posicao;
			novaRaiz->filho[1] = x->posicao;
			novaRaiz->numChaves = 1;
			novaRaiz->pai = -1;//PAI, pai da raiz sempre NULL = -1.

			int posicao = nextPositionArv(arqArv);
			novaRaiz->posicao = posicao;
			escreve_no(arqArv, novaRaiz, novaRaiz->posicao);
			mudarRaiz(arqArv, posicao);
			x->pai = posicao;
			r->pai = posicao;

			escreve_no(arqArv, r, r->posicao);
			escreve_no(arqArv, x, x->posicao);

			free(r);
			free(x);

			return novaRaiz;
		}
	}
	return r;
}


//acha a proxima posição a ser utilizada no arquivo de chaves
//pre-condição: arquivo para arvoreB válido
//pos-condição: proxima posição
int nextPositionArv(FILE* arqArv)
{
	int pos = 0;
	cabecalho* cab = le_cabecalho(arqArv);
	if (cab->pos_livre == -1)
	{
		pos = cab->pos_topo++;
		escreve_cabecalho(arqArv, cab);
		free(cab);
		return pos;
	}
	pos = cab->pos_livre;//posicao pega das livres
	arvoreB* arv = le_no(arqArv, cab->pos_livre);//le o no da posição livre
	cab->pos_livre = arv->filho[0];//filho 0 é a proxima posiçao livre
	escreve_cabecalho(arqArv, cab);//reescreve o cabecalho com a nova posiçao livre
	free(cab);
	free(arv);
	return pos;
}

//adiciona uma posicao às livres
//pre-condição: posicao válida  a ser adicionada a lista de livres
//pos-condição: atualiza cabecalho com a inclusao da posição
void addPosLivreArv(FILE* arqArv, int posicao)
{
	cabecalho* cab = le_cabecalho(arqArv);
	arvoreB* a = le_no(arqArv, posicao);//REVER, era ler produto

	a->filho[0] = cab->pos_livre;
	escreve_no(arqArv, a, posicao);
	cab->pos_livre = posicao;
	escreve_cabecalho(arqArv, cab);
	free(a);
	free(cab);
}


// retorna o no que contem info e sua posicao no no ou
//pre-condiçao ler o no da raiz e passar para o ponteiro r;
// NULL se info nao esta na arvore
arvoreB* busca(FILE* arq,arvoreB* r, int info, int* pos)
{
	if (vazia(r))
		return NULL;
	int i = 0;
	while (i < r->numChaves && r->chave[i] < info) i++;
    if ((i + 1) > r->numChaves || r->chave[i] > info)
    {
        arvoreB* aux = le_no(arq, r->filho[i]);
        arvoreB* b = busca(arq, aux, info, pos);
        if (b != aux)
        {
            free(aux);
        }
        return b;
    }
	*pos = i;
	return r;
}

//-----------------------------------IMPRIMIR NÍVEIS-----------------------------------------//

//busca o nível de uma chave na arvore R.
//pre-condição: arquivo válido de arvoreB, count começa em zero na primeira chamada
//pos-condição: o nivel da chave.
int buscaNivel(FILE* arq, arvoreB* r,int chave, int count)
{
    if (!vazia(r))
    {
        for (int i = 0; i < r->numChaves; i++){
            if (r->chave[i] == chave)
            {
                return count;
            }
        }
        
        for (int i = 0; i < r->numChaves; i++)
        {
            if (chave < r->chave[i])
            {
                arvoreB* filho_i = le_no(arq, r->filho[i]);
                if (filho_i != NULL)
                {
                    int retorno = 1 + buscaNivel(arq, filho_i, chave, count);
                    free(filho_i);
                    return retorno;
                }
                
            }
        }

        arvoreB* filho_i = le_no(arq, r->filho[r->numChaves]);
        if (filho_i != NULL)
        {
            int retorno = 1 + buscaNivel(arq, filho_i, chave, count);
            free(filho_i);
            return retorno;
        }
        
    }
    return 0;
}

//coloca os filhos na fila.
//pre-condição: arquivo valido para arvoreB.
//pos-condição: coloca os filhos na fila.
void enfileiraFilhos(FILE* arq,arvoreB* r, Fila* f)
{
    arvoreB* aux = NULL;
    int p = 0;
    aux = busca(arq,r, f->inicio->info,&p);

    if (aux != NULL)
    {
        if (aux->filho[0] != -1)
        {
            int i;
            for (i = 0; i <= aux->numChaves; i++)
            {
                arvoreB* filho_i = le_no(arq, aux->filho[i]);
                if (filho_i != NULL)
                {
                    enqueue(f, filho_i->chave[0]);
                }
                free(filho_i);
                filho_i = NULL;
            }

        }
    }
}
//desinfileira uma fila.
int* dequeue(Fila* f)
{
    if (!vaziaFila(f))
    {
        int* x = (int*)malloc(sizeof(int));

        struct noLista* aux = f->inicio;
        *x = f->inicio->info;

        if (f->inicio == f->fim)
        {
            f->fim = NULL;
        }
        f->inicio = f->inicio->prox;
        free(aux);
        return x;
    }
    else
    {
        return NULL;
    }
}

//imprimr as chave da arvoreB por níveis.
//pré-condição: raiz lida e arquivo valido para arvoreB.
//pos-condição: impressao da arvore por níveis.
void imprimir_por_niveis(FILE* arq,arvoreB* r)
{
    Fila* f = cria_fila_vazia();
    int atual = 0, ant = 0;
    if (!vazia(r))
    {
        enqueue(f, r->chave[0]);
        while (!vaziaFila(f))
        {
            arvoreB* aux = NULL;
            enfileiraFilhos(arq,r, f);
            atual = buscaNivel(arq,r, f->inicio->info, 0);
            if (atual != ant)
            {
                printf("\n");
                ant = atual;
            }
            int p = 0;
            aux = busca(arq,r, f->inicio->info,&p);
            int j;
            printf("[");
            for (j = 0; j < aux->numChaves; j++)
            {
                printf("%d ", aux->chave[j]);
            }
            printf("] ");
            dequeue(f);
        }
    }
}
//testa se uma fila é vazia.
//pre-condição: fila válida
//pos-condição: retorna se a fila é vazia
int vaziaFila(Fila* f)
{
    return (f->inicio == NULL);
}

//cria fila vazia
//pre-condiçao: nenhuma
//pos-condição: fila vazia criada.
Fila* cria_fila_vazia()
{
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

//enfileira um elemento na fila
//pre-condição: fila válida.
//pos-condição: nenhuma.
void enqueue(Fila* f, int x)
{
    struct noLista* aux = (struct noLista*)malloc(sizeof(struct noLista));
    aux->info = x;
    aux->prox = NULL;
    if (vaziaFila(f))
    {
        f->inicio = aux;
    }
    else
    {
        f->fim->prox = aux;
    }
    f->fim = aux;
}

//----------------------------------------------------------------------------------------///

//imprime a arvore in_ordem
//pre_condiçao: arquivo de arvoreB válido e raiz lida
//pos_condiçao: nenhuma
void in_ordem(FILE* arq, arvoreB* r)
{
	if (!vazia(r))
	{
		for (int i = 0; i <= r->numChaves; i++)
		{
			arvoreB* filho_i = le_no(arq, r->filho[i]);
			if (filho_i != NULL)
				in_ordem(arq,filho_i);
			free(filho_i);
			if (i < r->numChaves)
			{
				printf("chave: %d ", r->chave[i]);
                printf("pai: %d ", r->pai);
                printf("ptDados: %d ", r->ptDados[i]);
			}
		}
	}
}












//--------------------------------------------REMOÇÃO------------------------------------------------------------//
//acha a menor chave da arvoreB
//pre-condição: arquivo válido de arvoreB e raiz nao nula, pois não tem como definir um minimo se nao tem informação.
//pos_condição:  a chave minima dessa arvore
int minimo(FILE* arqArv,arvoreB* r)
{
    if (r != NULL)
    {
        arvoreB* filho_0 = le_no(arqArv, r->filho[0]);
        if (filho_0 == NULL)
        {
            return r->chave[0];
        }
        int min = minimo(arqArv, filho_0);
        free(filho_0);
        return min;
        
    }
    return 0;
}
//acha a maior chave da arvore
//pre-condição: raiz da arvore nao nula
//pos-condição: o maximo dessa arvoreB
int maximo(FILE* arqArv,arvoreB* r)
{
    if (r != NULL)
    {
        arvoreB* filho = le_no(arqArv, r->filho[r->numChaves]);
        if (filho == NULL)
        {
            return r->chave[r->numChaves - 1];
        }
        int max = maximo(arqArv, filho);
        free(filho);
        return max;
    }
    return 0;
}

//acha a maior chave da arvore
//pre-condição: raiz da arvore nao nula
//pos-condição: o maximo dessa arvoreB e copia a posiçao pt dos dados para pt.
int maximoRemove(FILE* arqArv, arvoreB* r,int * pt)
{
    if (r != NULL)
    {
        arvoreB* filho = le_no(arqArv, r->filho[r->numChaves]);
        if (filho == NULL)
        {
            
            (*pt) = r->ptDados[r->numChaves - 1];
            r->ptDados[r->numChaves - 1] = -1;
            escreve_no(arqArv, r, r->posicao);//reescreve essa posição com -1 para indicar que não é pra remover.
            return r->chave[r->numChaves - 1];
        }
        int max = maximoRemove(arqArv, filho,pt);
        free(filho);
        return max;
    }
    (*pt) = -1;
    return 0;
}

//retorna o irmao esquerdo ou NULL se não tem irmao esquerdo.
//pre-condição: arvore do filho que quer achar seu irmão esq, filho deve ter pai != NULL.
//pos-condição: no do irmão esquerdo
arvoreB* find_irmao_esq(FILE* arqArv,arvoreB* filho)
{
    arvoreB* pai = le_no(arqArv,filho->pai);
    if (!vazia(pai))
    {
        if (filho->posicao == pai->filho[0])
        {
            free(pai);
            return NULL;
        }
        int i = 0;
        for (i = 0; i <= pai->numChaves; i++)
        {
            if (pai->filho[i] == filho->posicao)
            {
                arvoreB* irmao = le_no(arqArv, pai->filho[i - 1]);
                free(pai);
                return irmao;

            }
        }
    }
    return NULL;
}
//pre-condiçao: arvore do filho que quer achar seu irmao direito, filho deve ter pai != NULL
//pos condição: nó com irmao direito
arvoreB* find_irmao_dir(FILE* arqArv,arvoreB* filho)
{
    arvoreB* pai = le_no(arqArv, filho->pai);
    if (!vazia(pai))
    {
        if (filho->posicao == pai->filho[pai->numChaves])
        {
            free(pai);
            return NULL;
        }
        int i = 0;
        for (i = 0; i <= pai->numChaves; i++)
        {
            if (pai->filho[i] == filho->posicao)
            {
                arvoreB* irmao = le_no(arqArv, pai->filho[i + 1]);
                free(pai);
                return irmao;
               
            }
        }
    }
    return NULL;
}
//acha a posiçao da chave divisa entre irmao esq e irmao dir.
//pre-condição: os 2 irmãos devem ser filhos do memsmo pai.
//pos-condição: devolve o indice da chave que é divisa no pai entre os nós, ou -1 caso de erro.
int find_pos_ch_sep(FILE* arqArv,arvoreB* irmaoEsq, arvoreB* irmaoDir)
{//irmao esq e irmão dir
    arvoreB* pai = le_no(arqArv, irmaoEsq->pai);
    int pos = -1;
    if (!vazia(pai))
    {
        if (pai->filho[0] == irmaoEsq->posicao)
        { //se o filho esq for igual ao filho[0] no pai, a posicao da chave separadora é 0;
            free(pai);
            return 0;
        }
        else if (pai->filho[pai->numChaves] == irmaoDir->posicao)
        {
            pos = pai->numChaves - 1;
            free(pai);
            return pos;
        }
        int i = 0;
        for (i = 0; i < pai->numChaves; i++)
        {
            if (irmaoEsq->posicao == pai->filho[i] && irmaoDir->posicao == pai->filho[i + 1])
            {
                free(pai);
                return i;
            }
        }
        return -1;
    }
    return -1;
}

//verifica se r pode emprestar
//pre-condição: nenhuma
//pos-condiçao: 1 = sim, 0 = nao
int podeEmprestar(arvoreB* r)
{
    if (r != NULL)
    {
        if (r->numChaves > MIN)
            return 1;
        return 0;
    }
    return 0;
}

//verfica se um no pode sofrer emprestimo dos seus irmaos
//pre-condiçao: nó nao raiz
//pos-condiçao: retorna 1 se puder, 0 se nao puder
int isEmprestimo(FILE* arqArv,arvoreB* r)
{
    arvoreB* esq = find_irmao_esq(arqArv,r);
    arvoreB* dir = find_irmao_dir(arqArv,r);

    if (podeEmprestar(esq) || podeEmprestar(dir))
    {
        free(esq);
        free(dir);
        return 1;
    }
    free(esq);
    free(dir);
    return 0;

}

//redistribui a arvore r com base no irmao esq que pôde fazer emprestimo
//pre-condição: faz parte de remover, nao pode ser chamada solta
//pos-condição: redistribui r emprestando do irmao esq
void redistribuirByIrmaoEsquerdo(FILE* arqArv,arvoreB* r, arvoreB* esq)
{
    int i;
    int pos_chave_separadora = find_pos_ch_sep(arqArv,esq, r);//posicao da chave que separa os irmaos.


    for (i = r->numChaves; i >= 0; i--)
    {
        r->chave[i] = r->chave[i - 1];
        r->ptDados[i] = r->ptDados[i - 1];
        r->filho[i + 1] = r->filho[i];
    }

    arvoreB* pai = le_no(arqArv, r->pai);

    r->chave[0] = pai->chave[pos_chave_separadora];
    r->ptDados[0] = pai->ptDados[pos_chave_separadora];

    pai->chave[pos_chave_separadora] = esq->chave[esq->numChaves - 1];
    pai->ptDados[pos_chave_separadora] = esq->ptDados[esq->numChaves - 1];
    escreve_no(arqArv, pai, pai->posicao);
    free(pai);

    r->filho[0] = esq->filho[esq->numChaves];
    arvoreB* filho = le_no(arqArv, r->filho[0]);
    if (filho != NULL)
    {
        filho->pai = r->posicao;
        escreve_no(arqArv, filho, filho->posicao);
        free(filho);
    }

    r->numChaves++;

    esq->filho[esq->numChaves] = -1;
    esq->numChaves--;

    //atualiza os nós no arquivo
    escreve_no(arqArv, r, r->posicao);
    escreve_no(arqArv, esq, esq->posicao);

    

}
//redistribui a arvore r com base no irmao dir que pôde fazer emprestimo
//pre-condição: faz parte de remover, nao pode ser chamada solta
//pos-condição: redistribui r emprestando do irmao dir
void redistribuirByIrmaoDireito(FILE* arqArv,arvoreB* r, arvoreB* dir)
{
    int i;
    int pos_chave_separadora = find_pos_ch_sep(arqArv,r, dir);//posicao da chave que separa os irmãos
    arvoreB* pai = le_no(arqArv,r->pai);

    r->chave[r->numChaves] = pai->chave[pos_chave_separadora];
    r->ptDados[r->numChaves++] = pai->ptDados[pos_chave_separadora];

    pai->chave[pos_chave_separadora] = dir->chave[0];
    pai->ptDados[pos_chave_separadora] = dir->ptDados[0];
    escreve_no(arqArv, pai, pai->posicao);
    free(pai);

    r->filho[r->numChaves] = dir->filho[0];

    arvoreB* filho = le_no(arqArv, r->filho[r->numChaves]);//rever se realmente precisa disso!!
    if (filho != NULL)
    {
        filho->pai = r->posicao;
        escreve_no(arqArv, filho, filho->posicao);
        free(filho);
    }

    for (i = 0; i < dir->numChaves; i++)
    {
        dir->chave[i] = dir->chave[i + 1];
        dir->ptDados[i] = dir->ptDados[i + 1];
        dir->filho[i] = dir->filho[i + 1];
    }

    dir->filho[dir->numChaves] = -1;
    dir->numChaves--;

    //atualiza os nós no arquivo.
    escreve_no(arqArv, dir, dir->posicao);
    escreve_no(arqArv, r, r->posicao);
}

//redistribui a arvore R com underflow
//pre-condição: função chamada automaticamente por balancear, nao deve ser chamada solta
//pos-condição: redistribui a árvore
void redistribuir(FILE* arqArv,arvoreB* r)
{
    arvoreB* esq = find_irmao_esq(arqArv,r);//usa memoria dinamica, liberar
    arvoreB* dir = find_irmao_dir(arqArv,r);//usa memoria dinamica, liberar
    int i = 0;

    if (podeEmprestar(esq))
    {
        redistribuirByIrmaoEsquerdo(arqArv,r, esq);
        free(esq);

    }
    else if (podeEmprestar(dir))
    {
        redistribuirByIrmaoDireito(arqArv,r, dir);
        free(dir);
    }

}
//verifica se deu underflow
//pre-condiçao: arvore nao nula
//pos-conidição: 1 se deu, 0 se nao deu, underflow
int underflow(arvoreB* r)
{
    if (r != NULL)
    {
        if (r->numChaves < MIN && !eh_raiz(r) )
            return 1;
        return 0;
    }
    return 0;
}

//concatena r com seu irmao esquerdo = esq
//pré-condiçao: função aux, nunca chmar manualmente, testar se o irmao esq é diferente de null antes
//pos-condição: concatenação com irmao esquerdo
void concatenarComIrmaoEsquerdo(FILE* arqArv,arvoreB* r, arvoreB* esq)
{
    arvoreB* aux = r;//guarda o endereco de r para dar free e liberar a posicao depois que fizer a concatenação

    int pos_chave_separadora = find_pos_ch_sep(arqArv,esq, r);//posicao da chave separadora.
    arvoreB* pai = le_no(arqArv, r->pai);

    esq->chave[esq->numChaves] = pai->chave[pos_chave_separadora];
    esq->ptDados[esq->numChaves] = pai->ptDados[pos_chave_separadora];
    esq->filho[esq->numChaves + 1] = r->filho[0];

    arvoreB* filho = le_no(arqArv, esq->filho[esq->numChaves + 1]);
    if (filho != NULL)
    {
        filho->pai = esq->posicao;
        escreve_no(arqArv, filho, filho->posicao);
        free(filho);
        filho = NULL;
    }

    esq->numChaves++;

    for (int i = 0; i < r->numChaves; i++)
    {
        esq->chave[esq->numChaves] = r->chave[i];
        esq->ptDados[esq->numChaves++] = r->ptDados[i];
        filho = le_no(arqArv, r->filho[i + 1]);
        if (filho != NULL)
        {
            filho->pai = esq->posicao;
            escreve_no(arqArv, filho, filho->posicao);
            free(filho);
            filho = NULL;
        }
        esq->filho[esq->numChaves] = r->filho[i + 1];
    }
    for (int i = pos_chave_separadora; i < pai->numChaves; i++)
    {
        pai->chave[i] = pai->chave[i + 1];
        pai->ptDados[i] = pai->ptDados[i + 1];
        pai->filho[i + 1] = pai->filho[i + 2];
    }
    pai->numChaves--;

    //atualiza o pai.
    escreve_no(arqArv, pai, pai->posicao);//atualiza o pai
    free(pai);
    
    //atualiza irmão esquerdo:
    escreve_no(arqArv, esq, esq->posicao);

    //adiciona a posicao que estava em r para as livres.
    addPosLivreArv(arqArv, aux->posicao);
    //free(aux);
   // aux = NULL;

}

//concatena r com seu irmao direito = dir
//pré-condiçao: função aux, nunca chamar manualmente, testar se o irmao dir é diferente de null antes
//pos-condição: concatenação com irmao direito
void concatenarComIrmaoDireito(FILE* arqArv,arvoreB* r, arvoreB* dir)
{

    int pos_chave_separadora = find_pos_ch_sep(arqArv,r, dir);//posição da chave separadora.
    
    arvoreB* pai = le_no(arqArv, r->pai);
   
    r->chave[r->numChaves] = pai->chave[pos_chave_separadora];
    r->ptDados[r->numChaves] = pai->ptDados[pos_chave_separadora];
    r->filho[r->numChaves + 1] = dir->filho[0];

    arvoreB* filho = le_no(arqArv, r->filho[r->numChaves + 1]);
    if (filho != NULL)
    {
        filho->pai = r->posicao;
        escreve_no(arqArv, filho, filho->posicao);
        free(filho);
        filho = NULL;
    }
    r->numChaves++;


    for (int i = 0; i < dir->numChaves; i++)
    {
        r->chave[r->numChaves] = dir->chave[i];
        r->ptDados[r->numChaves++] = dir->ptDados[i];
        r->filho[r->numChaves] = dir->filho[i + 1];

        filho = le_no(arqArv, r->filho[r->numChaves]);
        if (filho != NULL)
        {
            filho->pai = r->posicao;
            escreve_no(arqArv, filho, filho->posicao);
            free(filho);
            filho = NULL;
        }
    }
    for (int i = pos_chave_separadora; i < pai->numChaves; i++)
    {
        pai->chave[i] = pai->chave[i + 1];
        pai->ptDados[i] = pai->ptDados[i + 1];
        pai->filho[i + 1] = pai->filho[i + 2];//2 e 3 
    }
    pai->numChaves--;

    //atualiza o pai.
    escreve_no(arqArv, pai, pai->posicao);
    free(pai);

    //atualiza o r.
    escreve_no(arqArv, r, r->posicao);

    //adiciona a posicao do irmao da direita qeu se juntou com r às livres.
    addPosLivreArv(arqArv, dir->posicao);
    //free(dir);
    //dir = NULL;
}

//faz a concatenação, prioritariamente com o irmao esquerdo, se não o possuir, com o direito
// pré-condição: nó com underflow e que tenha sido redirecionado pela função balancear para fazer concatenação
//nao chamar esssa função manualmente, so deve ser chamada pela balancear
//pos-condição: concatena o no com o irmao sequerdo se possuir, ou direito caso nao possua irmao esquerdo
void concatenar(FILE* arqArv,arvoreB* r)
{

    arvoreB* esq = find_irmao_esq(arqArv,r);
    arvoreB* dir = find_irmao_dir(arqArv,r);

    if (esq != NULL)
    {//tem irmão esquerdo, pode concatenar com ele
        concatenarComIrmaoEsquerdo(arqArv,r, esq);
        free(esq);//dúvida sobre o free.
    }
    else if (dir != NULL)
    {//tem irmao direito pode concatenar com ele
        concatenarComIrmaoDireito(arqArv,r, dir);
        free(dir);//dúvida sobre o free.
    }

}

//testa se é raiz
//pre-condição: r nao pode ser NULL
//pos-condição: 1 se for raiz, 0 se nao for
int eh_raiz(arvoreB* r)
{
    if (r != NULL)
    {
        if (r->pai == -1)
        {
            return 1;
        }
    }
    return 0;
}

//faz redistribuição se possível, ou faz concatenação para ajustar o no com underflow
//pré-condição: no que ficou com underflow
//pos-condição: balanceia o nó
void balancear(FILE* arqArv,arvoreB* r)
{
    if (isEmprestimo(arqArv,r))
    {//se pode emprestar, faz a redistribuição
        redistribuir(arqArv,r);
    }
    else
    {//nao da pra emprestar, faz concatenação
        concatenar(arqArv,r);
    }
}

//remove um produto
//pre-condição: arqprod e arqArv, arquivos para produto e chaves respectivamente, válidos, r = leitura da raiz do arquivo de chaves
//pos-condição retorna a nova raiz;
arvoreB* remover(FILE* arqProd, FILE* arqArv, arvoreB* r, int x)
{
    if (!vazia(r))
    {
        int i = 0;
        for (i = 0; i < r->numChaves; i++)
        { //varre o vetor em busca da chave se achar dá break
            if (r->chave[i] == x)
            {
                break;
            }
            else if (r->chave[i] > x)
            { //compara o valor da arvore r atual com a chave a ser encontrada, se for maior busca no filho
                arvoreB* filho_i = le_no(arqArv, r->filho[i]);
                filho_i = remover(arqProd, arqArv, filho_i, x);
                if (underflow(filho_i))
                {
                    balancear(arqArv, filho_i);
                }
                if (filho_i != NULL)
                {
                    r->filho[i] = filho_i->posicao;
                    free(filho_i);
                }
                else
                {
                    r->filho[i] = -1;
                }
                
                int pos = r->posicao;
                free(r);//libera o nó anterior
                r = le_no(arqArv, pos);//atualiza o nó que foi mudado pelo balancear.
                //escreve_no(arqArv, r, r->posicao);
                //return r;
            }
        }
        if (i >= r->numChaves)
        { // nao encntrou a chave neste nó,todos os numero aqui sao menores que a chave, por isso procura no filho mais a direita
            arvoreB* filho_i = le_no(arqArv, r->filho[i]);
            filho_i = remover(arqProd, arqArv, filho_i, x);
            if (filho_i != NULL)
            {
                r->filho[i] = filho_i->posicao;
            }
            else
            {
                r->filho[i] = -1;
            }
            if (underflow(filho_i))
            {
                balancear(arqArv, filho_i);
            }
        }
        else
        { //i é menor que núermo de chaves: achou algo neste nó,quando encontra a chave, sempre libera posições do arquivo de produto aqui
            if (eh_folha(r))
            {
                addPosLivreProd(arqProd, r->ptDados[i]);
                while (i + 1 < r->numChaves)
                {
                    r->chave[i] = r->chave[i + 1];
                    r->ptDados[i] = r->ptDados[i + 1];
                    i++;
                }
                r->numChaves--;//diminui uma chave;
                escreve_no(arqArv, r, r->posicao);

            }
            else if (!eh_folha(r))
            { //é no interno, não é folha
                addPosLivreProd(arqProd, r->ptDados[i]);
               
                arvoreB* filho_i = le_no(arqArv, r->filho[i]);
                int pt = -1;
                r->chave[i] = maximoRemove(arqArv, filho_i,&pt);
                r->ptDados[i] = pt;
                escreve_no(arqArv, r, r->posicao);
                filho_i = remover(arqProd,arqArv,filho_i, r->chave[i]);
                if (filho_i != NULL)
                {
                    r->filho[i] = filho_i->posicao;
                }
                else
                {
                    r->filho[i] = -1;
                }
                if (underflow(filho_i))
                {
                    balancear(arqArv,filho_i);
                }

            }
            
        }
        //testa se a raiz ficou vazia.
        int pos = r->posicao;
        free(r);
        r = le_no(arqArv, pos);
        if (r != NULL)
        {
          
            if (eh_raiz(r) && r->numChaves <= 0)
            {
                arvoreB* aux = le_no(arqArv, r->filho[0]);

                if (aux != NULL)
                {
                    aux->pai = -1;
                    mudarRaiz(arqArv, aux->posicao);
                    escreve_no(arqArv, aux, aux->posicao);
                }
                else
                {
                    mudarRaiz(arqArv, -1);
                }
                addPosLivreArv(arqArv, r->posicao);
                free(r);
                r = NULL;
                return aux;
            }
        }

        if (r != NULL)
        {

            escreve_no(arqArv, r, r->posicao);
        }
        return r;

    }
    
    return NULL;
}
