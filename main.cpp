#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 1000000000
/* TODO:

-Criar struct do no com seguintes informações:
-Matriz para representar tabuleiro
-Lista de filhos
999999999
-Criar struct de lista encadeada

*/

long global = 0;

typedef struct granode
{
	int** matriz;

	struct granode * proximo;

	int explorado;

	struct granode * cima;
	struct granode * baixo;
	struct granode * esquerda;
	struct granode * direita;

} GRA_Node;

GRA_Node* grafo[N];

typedef struct listanode
{
	GRA_Node* no;

	struct listanode* proximo;
	
} LIS_Node;

typedef struct lista
{
	LIS_Node* cabeca;

	LIS_Node* fim;
	
} LIS_ListaDeOrigens;

LIS_ListaDeOrigens * criaLista() {

	LIS_ListaDeOrigens * lista;

	lista = (LIS_ListaDeOrigens*)malloc(sizeof(LIS_ListaDeOrigens));

	if (lista == NULL)
	{
		printf("erro no malloc");
		exit(0);
	}

	lista->cabeca = NULL;
	lista->fim = NULL;

	return lista;
}

void insereNaLista(LIS_ListaDeOrigens* lista, GRA_Node* no) {

	LIS_Node* node;
	LIS_Node* aux;

	node = (LIS_Node*)malloc(sizeof(LIS_Node));

	if (node == NULL)
	{
		printf("erro no malloc");
		exit(0);
	}

	node->no = no;
	node->proximo = NULL;

	if(lista->cabeca == NULL) {
		lista->cabeca = node;
		lista->fim = node;
	} else {
		aux = lista->cabeca;
		while(aux->proximo != NULL) {
			aux = aux->proximo;
		}
		aux->proximo = node;
		lista->fim = node;
	}

}

long matrizParaNumero(int** matriz) {

	long number = 0;
	long divisor = 100000000;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			number += (divisor*matriz[i][j]);
			divisor /= 10;
		}
	}

	return number;

}

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
		if (colAux + 1 > 2){
			return NULL;
		}

		SwapNumbers(matrizNova, linAux, colAux, linAux, colAux + 1);
	}

	else if (i == 2)
	{
		if (linAux + 1 > 2){
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
	long posicao;

	posicao = matrizParaNumero(matriz);

	node = (GRA_Node*)malloc(sizeof(GRA_Node));

	if (node == NULL)
	{
		printf("erro no malloc");
		exit(0);
	}

	node->matriz = matriz;
	node->explorado = 0;
	node->proximo = NULL;
	node->cima = NULL;
	node->baixo = NULL;
	node->esquerda = NULL;
	node->direita = NULL;

	grafo[posicao] = node;

	return node;
}

void adicionaAosExplorados(GRA_Node* no) {

	no->explorado = 1;
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

GRA_Node* verificaSeExplorado(int** matrizFilho) {

	long posicao = matrizParaNumero(matrizFilho);

	if(grafo[posicao]==NULL) {
		return NULL;
	}

	return grafo[posicao];
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

void printMatriz(int** matriz) {

	for (int o = 0; o < 3; ++o)
	{
		printf("\n");
		for (int p = 0; p < 3; ++p)
		{
			printf("%d", matriz[o][p]);
		}
	}
	printf("\n");
}

GRA_Node* DFS(int ** matriz) {

	GRA_Node* no = criaNo(matriz);
	adicionaAosExplorados(no);

	global++;

	printf("\nNumero: %ld\n", global);
	//printf("Combinaçao do puzzle: ");
	//printMatriz(matriz);

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

			GRA_Node* noVizinho = verificaSeExplorado(matrizFilho);

			// printf("Achou vizinho\n");

			if (noVizinho == NULL) {
				noVizinho = DFS(matrizFilho);
			}

			adicionaVizinho(no, noVizinho, i);

		}
	}

	return no;
}

int main(void){

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

	no = DFS(matriz);
}
