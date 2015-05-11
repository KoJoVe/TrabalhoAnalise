#include <stdio.h>

/* TODO:

-Criar struct do no com seguintes informações:
-Matriz para representar tabuleiro
-Lista de filhos

-Criar struct de lista encadeada

*/

typedef struct node
{
	GRA_Node* noGrafo;

	struct node * proximo;

} LIS_Node;

typedef struct list
{
	LIS_Node * origem;

	LIS_Node * fim;

	LIS_Node * elementoCorrente;

} LIS_Lista;

typedef struct granode
{
	int matriz[3][3];

	struct granode * proximo;

	LIS_Lista * listaFilhos;

} GRA_Node;

typedef struct grafo
{
	GRA_Node* origem;

	GRA_Node* corrente;

	GRA_Node* proximo;

} GRA_Grafo;



LIS_Node * LIS_CriaElemento(GRA_Node * no)
{
	LIS_Node * node;

	node = (LIS_Node*)malloc(sizeof(LIS_Node));

	if (node == NULL)
	{
		printf("erro no malloc");
		exit(0);
	}

	node->noGrafo = no;
	node->proximo = NULL;

	return node;
}

LIS_Lista * LIS_CriaLista()
{
	LIS_Lista * list = NULL;

	list = (LIS_Lista *)malloc(sizeof(LIS_Lista));

	if (list == NULL)
	{
		printf("erro no malloc");
		exit(0);
	}

	return list;
}

void LIS_InserirElemento(LIS_Lista * lista, GRA_Node * no)
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



GRA_Node* DFS(GRA_Grafo* G, int ** matriz) {

	GRA_Node* no = criaNo(matriz);
	adicionaAosExplorados(G, no);

	for (int i = 0; i < 4; ++i)
	{

		int** matrizFilho = achaMatriz(matriz, i);

		if (matrizFilho != NULL) {

			GRA_Node* noVizinho = verificaSeExplorado(G, matrizFilho);

			if (noVizinho == NULL) {
				noVizinho = DFS(G, matrizFilho);
			}

			adicionaVizinho(no, noVizinho);

		}
	}

	return no;
}

int main(void){
	printf("quero");
}