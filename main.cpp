#include <stdio.h>
#include <stdlib.h>

/* TODO:

-Criar struct do no com seguintes informações:
-Matriz para representar tabuleiro
-Lista de filhos

-Criar struct de lista encadeada

*/

long global = 0;

typedef struct granode
{
	int** matriz;

	struct granode * proximo;

	struct granode * cima;
	struct granode * baixo;
	struct granode * esquerda;
	struct granode * direita;

} GRA_Node;

typedef struct grafo
{
	GRA_Node* origem;

	GRA_Node* corrente;

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

int ** acharMatriz(int** matriz, int i)
{
	int linAux, colAux;
	int ** matrizNova;

	matrizNova = (int **)malloc(3 * sizeof(int *));

	for (int y = 0; y<3; y++)
		matrizNova[y] = (int *)malloc(3 * sizeof(int));

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

GRA_Node* criaNo(int** matriz) {

	GRA_Node * node;

	node = (GRA_Node*)malloc(sizeof(GRA_Node));

	if (node == NULL)
	{
		printf("erro no malloc");
		exit(0);
	}

	node->matriz = matriz;
	node->proximo = NULL;
	node->cima = NULL;
	node->baixo = NULL;
	node->esquerda = NULL;
	node->direita = NULL;

	return node;
}

void adicionaAosExplorados(GRA_Grafo* G, GRA_Node* no) {

	GRA_Node* noAux;

	if (G->origem == NULL) {
		G->origem = no;
	} else {
		noAux = G->origem;
		while (noAux->proximo != NULL) {
			noAux = noAux->proximo;
		}
		noAux->proximo = no;
	}
}

int comparaMatriz(int** mat1, int** mat2)
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (mat1[i][j] != mat2[i][j])
			{
				return 0;
			}
		}
	}

	return 1;
}

GRA_Node* verificaSeExplorado(GRA_Grafo* G, int** matrizFilho) {

	GRA_Node* noAux = G->origem;

	while (noAux->proximo != NULL) {
		if (comparaMatriz(noAux->matriz, matrizFilho) == 1) {
			return noAux;
		}
		noAux = noAux->proximo;
	}

	return NULL;
}

void adicionaVizinho(GRA_Node* no, GRA_Node* noVizinho, int i) {

	if (i == 0) {
		no->cima = noVizinho;
	}
	if (i == 1) {
		no->direita = noVizinho;
	}
	if (i == 2) {
		no->baixo = noVizinho;
	}
	if (i == 3) {
		no->esquerda = noVizinho;
	}

}

GRA_Grafo * GRA_CriaGrafo()
{
	GRA_Grafo * grafo = NULL;

	grafo = (GRA_Grafo *)malloc(sizeof(GRA_Grafo));

	if (grafo == NULL)
	{
		printf("erro no malloc");
		exit(0);
	}

	grafo->origem = NULL;

	return grafo;
}

GRA_Node* DFS(GRA_Grafo* G, int ** matriz) {

	GRA_Node* no = criaNo(matriz);
	adicionaAosExplorados(G, no);

	global++;

	printf("Numero: %ld\n", global);

	for (int i = 0; i < 4; ++i)
	{

		// printf("Entra vizinhos\n");

		int ** matrizFilho;

		matrizFilho = (int **)malloc(3 * sizeof(int *));

		for (int y = 0; y<3; y++)
			matrizFilho[y] = (int *)malloc(3 * sizeof(int));

		matrizFilho = acharMatriz(matriz, i);

		// printf("Achou filhos\n");

		if (matrizFilho != NULL) {

			GRA_Node* noVizinho = verificaSeExplorado(G, matrizFilho);

			// printf("Achou vizinho\n");

			if (noVizinho == NULL) {
				noVizinho = DFS(G, matrizFilho);
			}

			adicionaVizinho(no, noVizinho, i);

		}
	}

	return no;
}

int main(void){

	GRA_Grafo *grafo;
	GRA_Node *no;
	int** matriz;

	matriz = (int **)malloc(3 * sizeof(int *));

	for (int y = 0; y<3; y++)
		matriz[y] = (int *)malloc(3 * sizeof(int));

	matriz[0][0] = 0;
	matriz[0][1] = 1;
	matriz[0][2] = 2;
	matriz[1][0] = 3;
	matriz[1][1] = 4;
	matriz[1][2] = 5;
	matriz[2][0] = 6;
	matriz[2][1] = 7;
	matriz[2][2] = 8;

	grafo = GRA_CriaGrafo();
	
	no = DFS(grafo,matriz);
}
