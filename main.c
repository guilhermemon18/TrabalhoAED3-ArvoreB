#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "produto.h"
#include "arvoreB.h"
#include "cabecalho.h"
#include <string.h>
#include "controle.h"
#include "menus.h"



int main()
{
    setlocale(LC_ALL, "Portuguese");
    
    FILE* arvore;//arquivo da arvore B com indices dos produtos.
    FILE* produtos;//arquivo de produtos.

    if(fopen("arvore.bin", "r+b")){ //Estrutura de condição que verifica se o arquivo ja existe
        arvore = fopen("arvore.bin", "r+b"); //Abre o arquivo que ja existe
    }else{
        arvore = fopen("arvore.bin", "w+b");//Cria o arquivo caso não exista
        cria_arvore_vazia(arvore);
    }
    if (fopen("produtos.bin", "r+b"))
    { //Estrutura de condição que verifica se o arquivo ja existe
        produtos = fopen("produtos.bin", "r+b"); //Abre o arquivo que ja existe
    }
    else
    {
        produtos = fopen("produtos.bin", "w+b");//Cria o arquivo caso não exista
        cria_arvore_vazia(produtos);
    }

    menuPrincipal(arvore, produtos);

    fclose(arvore);
    fclose(produtos);

    return 0;
}