#include <stdio.h>
#include <stdlib.h>

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

void AchaZero(int** matriz, int * linha, int * coluna)
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

void SwapNumbers(int** matriz, int linS, int colS, int linE, int colE)
{
	int temp;
	temp = matriz[linS][colS];
	matriz[linS][colS] = matriz[linE][colE];
	matriz[linE][colE] = temp;
}

int ** acharMatriz(int matriz[3][3], int i)
{
	int linAux, colAux;
	int ** matrizNova;

	matrizNova=(int **)malloc(3*sizeof(int *));

	for(int y=0;y<3;y++)
	    matrizNova[y]=(int *) malloc(3*sizeof(int));

	for (int k = 0; k < 3; ++k)
	{
		for (int j = 0; j < 3; ++j)
		{
			matrizNova[k][j] = matriz[k][j];
		}
	}

	AchaZero(matrizNova, &linAux, &colAux);

	if (i == 0)
	{
		if (linAux - 1 < 0){
			return NULL;
		}

		SwapNumbers(matrizNova, linAux, colAux, linAux - 1, colAux);

	}

	else if (i == 1)
	{
		if (colAux + 1 > 3){
			return NULL;
		}

		SwapNumbers(matrizNova, linAux, colAux, linAux, colAux + 1);
	}

	else if (i == 2)
	{
		if (linAux + 1 > 3){
			return NULL;
		}

		SwapNumbers(matrizNova, linAux, colAux, linAux + 1, colAux);
	}

	else if (i == 3)
	{
		if (colAux - 1 < 0){
			return NULL;
		}

		SwapNumbers(matrizNova, linAux, colAux, linAux, colAux - 1);
	}

	return matrizNova;
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