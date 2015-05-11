#include <stdio.h>

/* TODO:

-Criar struct do no com seguintes informações:
-Matriz para representar tabuleiro
-Lista de filhos

-Criar struct de lista encadeada

*/


typedef struct granode
{
	int matriz[3][3];

	struct granode * proximo;

	struct granode * left;

	struct granode * up;

	struct granode * right;

	struct granode * down;

} GRA_Node;

typedef struct node
{
	GRA_Node* noGrafo;

	struct node * proximo;

}LIS_Node;

typedef struct list
{
	LIS_Node * origem;

	LIS_Node * fim;

	LIS_Node * elementoCorrente;

} LIS_Lista;

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

void AchaZero(int matriz[3][3], int * linha, int * coluna)
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (matriz[i][j] == 0)
			{
				*linha = i;
				*coluna = j;
				return;
			}
		}
	}
}

void SwapNumbers(int matriz[3][3], int linS, int colS, int linE, int colE)
{
	int temp;
	temp = matriz[linS][colS];
	matriz[linS][colS] = matriz[linE][colE];
	matriz[linE][colE] = temp;
}

int ** acharMatriz(int matriz[3][3], int i)
{
	int linAux, colAux;

	AchaZero(matriz, &linAux, &colAux);

	if (i == 0)
	{
		if (linAux - 1 < 0){
			return NULL;
		}

		SwapNumbers(matriz, linAux, colAux, linAux - 1, colAux);

	}

	else if (i == 1)
	{
		if (colAux + 1 > 3){
			return NULL;
		}

		SwapNumbers(matriz, linAux, colAux, linAux, colAux + 1);
	}

	else if (i == 2)
	{
		if (linAux + 1 > 3){
			return NULL;
		}

		SwapNumbers(matriz, linAux, colAux, linAux + 1, colAux);
	}

	else if (i == 3)
	{
		if (colAux - 1 < 0){
			return NULL;
		}

		SwapNumbers(matriz, linAux, colAux, linAux, colAux - 1);
	}

	return matriz;
}

/*
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
*/

int main(void){
	int i, j;
	int lin = 0, col = 0;
	int matrix[3][3] = { 4, 1, 2, 3, 0, 5, 6, 7, 8 };
	int ** matrizTeste;

	matrizTeste = acharMatriz(matrix, 1);

	for (i = 0; i < 3; i++)
	{
		printf("\n");
		for (j = 0; j < 3; j++)
		{
			printf("%d", matrizTeste[i][j]);
		}
	}


	/*
	AchaZero(matrix, &lin, &col);

	printf("quero %d, %d\n", lin, col);

	for (i = 0; i < 3; i++)
	{
	printf("\n");
	for (j = 0; j < 3; j++)
	{
	printf("%d", matrix[i][j]);
	}
	}

	printf("\n");

	SwapNumbers(matrix, lin, col, 0, 0);

	for (i = 0; i < 3; i++)
	{
	printf("\n");
	for (j = 0; j < 3; j++)
	{
	printf("%d", matrix[i][j]);
	}
	}
	*/
}