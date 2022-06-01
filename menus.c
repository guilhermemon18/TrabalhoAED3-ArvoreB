
#pragma warning(disable : 4996)
#include "menus.h"
#include "arvoreB.h"
#include "controle.h"
#include "produto.h"
#include <stdio.h>
#include <stdlib.h>


//apresenta menu de inser��o de um novo produto
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuInserir(FILE* arqArv,FILE* arqProd)
{
	printf("MENU INSERIR:\n\n");
	Produto produto;
	printf("Digite o c�digo do produto:\n");
	scanf("%d", &produto.codigo);

	scanf("%*c");
	printf("Digite o nome:\n");
	scanf("%[^\n]s", produto.nome);
	scanf("%*c");

	printf("Digite o pre�o:\n");
	scanf("%f", &produto.preco);
	scanf("%*c");

	printf("Digite a quantidade:\n");
	scanf("%d", &produto.quantidade);
	scanf("%*c");
	printf("Digite a localizac�o:\n");
	scanf("%[^\n]s", produto.localizacao);
	scanf("%*c");

	int pos = -1;
	Produto* p = findProdutoByCodigo(arqArv, arqProd, produto.codigo, &pos);
	if (p == NULL)//produto nao existe ainda.
	{
		inserir(arqArv, arqProd, &produto);
		printf("Inserido com sucesso\n");
	}
	else
	{
		printf("Este c�digo de produto j� est� cadastrado!\n");
	}
	
}

//apresenta menu de altera��o de preco
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuAlterarPreco(FILE* arqArv,FILE* arqProd)
{
	printf("ALTERAR PRE�O:\n\n");
	int codigo;
	printf("Digite o c�digo do produto:\n");
	scanf("%d", &codigo);
	int pos = -1;
	Produto* p = findProdutoByCodigo(arqArv, arqProd, codigo, &pos);
	if (p != NULL)
	{
		printf("Produto a ser alterado:\n");
		imprime_produto(p);
	}
	else
	{
		printf("Este c�digo de produto n�o est� cadastrado\n");
		return;
	}
	printf("Digite o novo pre�o\n");
	scanf("%f", &p->preco);
	scanf("%*c");
	alterar(arqArv, arqProd, p);
	printf("Alterado com sucesso!\n");
	free(p);
}


//apresenta menu de altera��o de localiza��o
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuAlterarLocalizacao(FILE* arqArv, FILE* arqProd)
{
	printf("ALTERAR LOCALIZA��O:\n\n");
	int codigo;
	printf("Digite o c�digo do produto:\n");
	scanf("%d", &codigo);
	scanf("%*c");
	int pos = -1;
	Produto* p = findProdutoByCodigo(arqArv, arqProd, codigo, &pos);

	if (p != NULL)
	{
		printf("Produto a ser alterado:\n");
		imprime_produto(p);
	}
	else
	{
		printf("Este c�digo de produto n�o est� cadastrado\n");
		return;
	}
	printf("Digite a nova localiza��o\n");
	scanf("%[^\n]s", p->localizacao);
	scanf("%*c");
	alterar(arqArv, arqProd, p);
	printf("Alterado com sucesso!\n");
	free(p);
}

//apresenta um menu de impressao de produto por c�digo
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuInformacoesProduto(FILE* arqArv,FILE* arqProd)
{
	int codigo;
	printf("Digite o c�digo do produto:\n");
	scanf("%d", &codigo);
	scanf("%*c");
	int pos = -1;
	Produto* p = findProdutoByCodigo(arqArv, arqProd, codigo, &pos);
	if (p == NULL)
	{
		printf("C�digo inv�lido\n");
		return;
	}
	printf("Produto encontrado!\n");
	imprime_produto(p);
	free(p);
}

//apresenta menu de altera��o de estoque
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuAlterarEstoque(FILE* arqArv,FILE* arqProd)
{
	printf("ALTERAR ESTOQUE:\n\n");
	int codigo;
	printf("Digite o c�digo do produto:\n");
	scanf("%d", &codigo);
	int pos;
	Produto* p;
	arvoreB* a = busca(arqArv, le_no(arqArv, getPosRaiz(arqArv)), codigo, &pos);
	if (a != NULL)
	{
		p = le_produto(arqProd, a->ptDados[pos]);
		printf("Produto a ser alterado:\n");
		imprime_produto(p);
	}
	else
	{
		printf("Este c�digo de produto n�o est� cadastrado\n");
		return;
	}
	printf("Digite o novo valor do estoque\n");
	scanf("%d", &p->quantidade);
	scanf("%*c");
	alterar(arqArv, arqProd, p);
	printf("Alterado com sucesso!\n");
	free(a);
	free(p);
}

//apresenta um menu que lista os produtos
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void menuListarProdutos(FILE* arqArv, FILE* arqProd)
{
	printf("LISTAR PRODUTOS:\n\n");
	arvoreB* r = le_no(arqArv, getPosRaiz(arqArv));
	if (r == NULL)
	{
		printf("Nenhum produto encontrado na arvoreB!\n");
		return;
	}
	printf("Listando produtos\n");
	listarProdutosAux(r, arqArv, arqProd);
	free(r);
}

//lista os produtos da arvore 
//Pr�-condi��o:arquivo aberto de arvoreB e arquivo aberto de produto
//p�s-condi�ao:nenhuma
void listarProdutosAux(arvoreB* r, FILE* arqArv, FILE* arqProd)
{
	if (!vazia(r))
	{
		for (int i = 0; i <= r->numChaves; i++)
		{
			arvoreB* filho_i = le_no(arqArv, r->filho[i]);
			if (filho_i != NULL)
				listarProdutosAux(filho_i,arqArv,arqProd);
			free(filho_i);
			if (i < r->numChaves)
			{
				Produto* p = le_produto(arqProd, r->ptDados[i]);
				imprime_produto(p);
				printf("\n");
				free(p);
			}
		}
	}
}


//imprime as posi��es livres no arquivo da arvore binaria
//Pr�-condi��o: arquivo valido para arvore binaria
//p�s-condi�ao:nenhuma
void imprimirPosicoesLivresChaves(FILE* arq)
{
	printf("IMPRIMIR POSI��ESS LIVRES: ARQUIVO DE CHAVES\n\n");
	arvoreB* aux_no;
	cabecalho* aux = le_cabecalho(arq);
	int posicao = aux->pos_livre;

	aux_no = le_no(arq, posicao);
	if (aux_no == NULL)
	{
		printf("Nenhuma posi��o livre no arquivo de chaves da �rvoreB\n");
	}
	else
	{
		printf("Posi��es livres: \n");
		printf("%d\n", posicao);
		while (aux_no != NULL && aux_no->filho[0] != -1)
		{
			printf("%d\n", aux_no->filho[0]);
			posicao = aux_no->filho[0];
			free(aux_no);
			aux_no = le_no(arq, posicao);
		}
	}
	free(aux);
}

//imprime as posi��es livres no arquivo de produtos
//Pr�-condi��o: arquivo valido para produto
//p�s-condi�ao:nenhuma
void imprimirPosicoesLivresProdutos(FILE* arq)
{
	printf("IMPRIMIR POSI��ESS LIVRES: ARQUIVO DE PRODUTOS\n\n");
	Produto* aux_Prod;
	cabecalho* aux = le_cabecalho(arq);
	int posicao = aux->pos_livre;
	
	aux_Prod = le_produto(arq, posicao);
	if (aux_Prod == NULL)
	{
		printf("Nenhuma posi��o livre no arquivo de produtos\n");
	}
	else
	{
		printf("Posi��es livres: \n");
		printf("%d\n", posicao);
		while (aux_Prod != NULL && aux_Prod->codigo != -1)
		{
			printf("%d\n", aux_Prod->codigo);
			posicao = aux_Prod->codigo;
			free(aux_Prod);
			aux_Prod = le_produto(arq, posicao);
		}
	}
	free(aux);
}

//apresenta um MENU  de remo��o.
//pr�-condi��o: arquivos v�lidos para arvore de chaves e produtos.
//pos-condi��o: remo��o no arquivo da chave ou msg na tela informando que nao achou a chave.
void menuRemover(FILE* arqArv, FILE* arqProd)
{
	printf("REMOVER:\n\n");
	int codigo;
	printf("Digite o c�digo do produto:\n");
	scanf("%d", &codigo);
	scanf("%*c");
	int pos = -1;
	Produto* p = findProdutoByCodigo(arqArv, arqProd, codigo, &pos);

	if (p != NULL)
	{
		printf("Produto a ser removido:\n");
		imprime_produto(p);
	}
	else
	{
		printf("Este c�digo de produto n�o est� cadastrado\n");
		return;
	}
	printf("Digite 1 para confirmar a exclus�o\n");

	int confirmacao;
	scanf("%d", &confirmacao);
	scanf("%*c");

	if (confirmacao == 1)
	{
		Remover(arqProd, arqArv, codigo);
		printf("Removido com sucesso!\n");
	}
	else
	{
		printf("Remo��o cancelada\n");
	}
	free(p);
	
}

//apresenta um MENU que carrega a arvoreB com um arquivo de texto com opera��es.
//pr�-condi��o: Arquivo para produtos e arquivo para �rvore v�lidos.
//p�s-condi��o: opera��es na arvore
void carregarArquivoTexto(FILE* arqArv, FILE* arqProd)
{
	char nome_arquivo[50];
	FILE* arquivo;
	Produto* produtoAuxiliar = NULL;//ponteiro para produto.
	char operacao;
	int codigo;
	int pos_produto;

	printf("Digite o nome do arquivo:\n");
	scanf("%[^\n]", nome_arquivo);
	scanf("%*c");

	arquivo = fopen(nome_arquivo, "r");//abre para leitura o arquivo 
	if (arquivo == NULL)
	{
		printf("N�o foi poss�vel abrir o arquivo\n");
		return;
	}
	while (1)
	{
		fscanf(arquivo, "%*[ ]");//le espa�os em branco.
		fscanf(arquivo, "%c", &operacao);//obgrigatorio
		fscanf(arquivo, "%*[ ]");//le espa�os em branco.
		fscanf(arquivo, "%*c");//le o ; seguinte ao char de opera��o

		fscanf(arquivo, "%*[ ]");//le espacos em branco
		fscanf(arquivo, "%d", &codigo);//obrigatorio
		fscanf(arquivo, "%*[ ]");//le espacos em branco
		fscanf(arquivo, "%*c");//le ; ou \n se for remover
		if (operacao != 'R')
		{
			if (operacao == 'A')
			{
				produtoAuxiliar = findProdutoByCodigo(arqArv, arqProd, codigo, &pos_produto);
				if (produtoAuxiliar != NULL)
				{
					produtoAuxiliar->codigo = codigo;
				}
				else
				{
					produtoAuxiliar = (Produto*)malloc(sizeof(Produto));
					produtoAuxiliar->codigo = codigo;
				}
			}
			else //� inserir, cria um novo produto
			{
				produtoAuxiliar = (Produto*)malloc(sizeof(Produto));
				produtoAuxiliar->codigo = codigo;
			}
			if (operacao != 'A')
			{
				fscanf(arquivo, "%*[ ]");
				fscanf(arquivo, "%[^;]s", produtoAuxiliar->nome);//obrigatorio
				fscanf(arquivo, "%*c");
			}

			fscanf(arquivo, "%*[ ]");
			fscanf(arquivo, "%d", &produtoAuxiliar->quantidade);//obrigatorio
			fscanf(arquivo, "%*[ ]");//le espacos em branco
			fscanf(arquivo, "%*c");

			fscanf(arquivo, "%*[ ]");
			fscanf(arquivo, "%f", &produtoAuxiliar->preco);//obrigatorio
			fscanf(arquivo, "%*[ ]");//le espacos em branco
			fscanf(arquivo, "%*c");

			fscanf(arquivo, "%*[ ]");
			fscanf(arquivo, "%[^\n]s", produtoAuxiliar->localizacao);//obrigatorio
			fscanf(arquivo, "%*c");
		}
		if (feof(arquivo))
		{
			break;
		}
		if (operacao == 'I')
		{
			inserir(arqArv, arqProd, produtoAuxiliar);
		}
		else if (operacao == 'A')
		{
			alterar(arqArv, arqProd, produtoAuxiliar);
		}
		else if (operacao == 'R')
		{
			Remover(arqProd, arqArv, codigo);
		}
		free(produtoAuxiliar);//libera a memoria alocada
		produtoAuxiliar = NULL;//seta o ponteiro em NULL.
	}
	fclose(arquivo);
	printf("Arquivo lido com sucesso!\n");
}

//apresenta o menu princial com as op�oes do programa
//Pr�-condi��o:arquivo aberto de arvoreB e de produto
//p�s-condi�ao:nenhuma
void menuPrincipal(FILE* arqArv, FILE* arqProd)
{
	arvoreB* r;
	int numero;
	printf("MENU PRINCIPAL\n\n");
	printf("Escolha uma opc�o\n");

	printf("1.Cadastrar produto\n");
	printf("2.Remover produto\n");
	printf("3.Alterar estoque\n");
	printf("4.Alterar pre�o\n");
	printf("5.Alterar localiza��o\n");
	printf("6.Informac�es do produto\n");
	printf("7.Listar produtos\n");
	printf("9.Imprimir Posi��es livres: arquivo de dados\n");
	printf("10.Imprimir Posi��es livres: arquivo de �ndices\n");
	printf("11.Carregar arquivo texto\n");
	printf("12.Imprimir por n�veis\n");

	printf("0.Sair\n");

	scanf("%d", &numero);
	scanf("%*c");
	system("cls");

	switch (numero)
	{
	case 0:
		printf("Ate mais\n");
		system("pause");
		break;
	case 1:
		menuInserir(arqArv,arqProd);
		printf("\n\n");
		menuPrincipal(arqArv, arqProd);
		break;
	case 2:
		menuRemover(arqArv, arqProd);
		printf("\n\n");
		menuPrincipal(arqArv, arqProd);
		break;
	case 3:
		menuAlterarEstoque(arqArv, arqProd);
		printf("\n\n");
		menuPrincipal(arqArv, arqProd);
		break;
	case 4:
		menuAlterarPreco(arqArv, arqProd);
		printf("\n\n");
		menuPrincipal(arqArv, arqProd);
		break;
	case 5:
		menuAlterarLocalizacao(arqArv, arqProd);
		printf("\n\n");
		menuPrincipal(arqArv, arqProd);
		break;
	case 6:
		menuInformacoesProduto(arqArv, arqProd);
		printf("\n\n");
		menuPrincipal(arqArv, arqProd);
		break;
	case 7:
		menuListarProdutos(arqArv, arqProd);
		printf("\n\n");
		menuPrincipal(arqArv, arqProd);
		break;
	case 9:
		imprimirPosicoesLivresProdutos(arqProd);
		printf("\n\n");
		menuPrincipal(arqArv, arqProd);
		break;
	case 10:
		imprimirPosicoesLivresChaves(arqArv);
		printf("\n\n");
		menuPrincipal(arqArv, arqProd);
		break;
	case 11:
		carregarArquivoTexto(arqArv, arqProd);
		printf("\n\n");
		menuPrincipal(arqArv, arqProd);
		break;
	case 12:
		printf("IMPRIMIR POR N�VEIS: \n\n");
		r = le_no(arqArv, getPosRaiz(arqArv));
		if (r == NULL)
		{
			printf("A �rvoreB est� vazia!\n");
		}
		imprimir_por_niveis(arqArv, r);
		free(r);
		printf("\n\n");
		menuPrincipal(arqArv, arqProd);
		break;	
	default:
		printf("Op��o inv�lida, tente novamente\n");// caso nao seja um opcao valida
		menuPrincipal(arqArv, arqProd);
	}
}



