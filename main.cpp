#include <stdio.h>

/* TODO:

-Criar struct do no com seguintes informações:
  -Matriz para representar tabuleiro
  -Lista de filhos

-Criar struct de lista encadeada

*/

typedef struct node
{
	GRA_Node * node;

	struct node * proximo;

} LIS_Node;

typedef struct list
{
	LIS_Node * origem;

	LIS_Node * fim;

	LIS_Node * elementoCorrente;

}LIS_lista;

LIS_Node * LIS_CriaElemento(GRA_Node * no)
{
	LIS_Node * node;

	node = (LIS_Node*)malloc(sizeof(LIS_Node));

	if (node == NULL)
	{
		printf("erro no malloc");
		exit(0);
	}

	node->node = no;
	node->proximo = NULL;

	return node;
}

LIS_lista * LIS_CriaLista()
{
	LIS_lista * list = NULL;

	list = (LIS_lista *)malloc(sizeof(LIS_lista));

	if (list == NULL)
	{
		printf("erro no malloc");
		exit(0);
	}

	return list;
}

void LIS_InserirElemento(LIS_lista * lista, GRA_Node * no)
{
	LIS_Node * node;

	node = LIS_CriaElemento(no);
	if (node == NULL)
	{
		printf("Falha ao criar o no");
		exit(0);
	}

	if (lista->elementoCorrente == NULL)
	{
		lista->origem = node;
		lista->fim = node;
	}

	else
	{
		if (lista->elementoCorrente->proximo != NULL)
		{
			node->proximo = lista->elementoCorrente->proximo;
		}

		else
		{
			lista->fim = node;
		}

		lista->elementoCorrente->proximo = node;
	}

	lista->elementoCorrente = node;
}

int main(void){
	printf("quero");
}

