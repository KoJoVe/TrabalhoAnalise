#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 1000000000

long globalVertex = 0;
long globalEdges = 0;
int qtd = 0;
int** ListaDeMatrizes[362880];

typedef struct granode
{
	int** matriz;

	struct granode * proximo;

	int explorado;
	int visitado;

	struct granode * pai;
	int posicaoPai;

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

	node = (LIS_Node*)malloc(sizeof(LIS_Node));

	if (node == NULL)
	{
		printf("erro no malloc");
		exit(0);
	}

	node->no = no;
	node->proximo = NULL;

	if (lista->cabeca == NULL) {
		lista->cabeca = node;
		lista->fim = node;
	}
	else {
		lista->fim->proximo = node;
		lista->fim = node;
	}

}

GRA_Node * removeDaLista(LIS_ListaDeOrigens* lista)
{
	GRA_Node * aux;
	LIS_Node * lisAux;

	aux = lista->cabeca->no;
	lisAux = lista->cabeca;

	lista->cabeca = lista->cabeca->proximo;

	free(lisAux);

	return aux;
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

void swap(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void SwapNumbers(int** matriz, int linS, int colS, int linE, int colE)
{
	int temp;
	temp = matriz[linS][colS];
	matriz[linS][colS] = matriz[linE][colE];
	matriz[linE][colE] = temp;
}

void permute(int *a, int i, int n)
{
	int j;
	if (i == n)
	{
		int** matriz;

		matriz = (int **)malloc(3 * sizeof(int *));

		for (int y = 0; y<3; y++)
			matriz[y] = (int *)malloc(3 * sizeof(int));

		matriz[0][0] = a[0];
		matriz[0][1] = a[1];
		matriz[0][2] = a[2];
		matriz[1][0] = a[3];
		matriz[1][1] = a[4];
		matriz[1][2] = a[5];
		matriz[2][0] = a[6];
		matriz[2][1] = a[7];
		matriz[2][2] = a[8];

		ListaDeMatrizes[qtd] = matriz;
		qtd++;
		//printf("%d\n", qtd);
	}
	else
	{
		for (j = i; j <= n; j++)
		{
			swap((a + i), (a + j));
			permute(a, i + 1, n);
			swap((a + i), (a + j)); //backtrack
		}
	}
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
	node->pai = NULL;
	node->explorado = 0;
	node->visitado = 0;
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

	if (grafo[posicao] == NULL) {
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

	globalVertex++;

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
			globalEdges++;

		}
	}

	return no;
}

GRA_Node * BFS(GRA_Node * noRaiz, int NVertices)
{
	LIS_ListaDeOrigens * listaAdjacencia;
	GRA_Node * aux;
	GRA_Node * ultimo;
	int i, j;
	int conta = 0;
	listaAdjacencia = criaLista();

	for (i = 0; i < NVertices; i++)
	{
		insereNaLista(listaAdjacencia, noRaiz);
		conta++;
		noRaiz->visitado = 1;
		while (listaAdjacencia->cabeca != NULL)
		{

			aux = removeDaLista(listaAdjacencia);

			for (j = 0; j < 4; j++)
			{
				switch (j)
				{
				case 0:
					if (aux->cima != NULL)
					{
						if (aux->cima->visitado == 0)
						{
							aux->cima->visitado = 1;
							insereNaLista(listaAdjacencia, aux->cima);
							ultimo = aux->cima;
							aux->cima->pai = aux;
							aux->cima->posicaoPai = 0;
							conta++;
							// printf("Contador: %d\n", conta);
						}
					}
					break;
				case 1:
					if (aux->direita != NULL)
					{
						if (aux->direita->visitado == 0)
						{
							aux->direita->visitado = 1;
							insereNaLista(listaAdjacencia, aux->direita);
							ultimo = aux->direita;
							aux->direita->pai = aux;
							aux->direita->posicaoPai = 1;
							conta++;
							// printf("Contador: %d\n", conta);

						}
					}
					break;
				case 2:
					if (aux->baixo != NULL)
					{
						if (aux->baixo->visitado == 0)
						{
							aux->baixo->visitado = 1;
							insereNaLista(listaAdjacencia, aux->baixo);
							ultimo = aux->baixo;
							aux->baixo->pai = aux;
							aux->baixo->posicaoPai = 2;
							conta++;
							// printf("Contador: %d\n", conta);
						}
					}
					break;
				case 3:
					if (aux->esquerda != NULL)
					{
						if (aux->esquerda->visitado == 0)
						{
							aux->esquerda->visitado = 1;
							insereNaLista(listaAdjacencia, aux->esquerda);
							ultimo = aux->esquerda;
							aux->esquerda->pai = aux;
							aux->esquerda->posicaoPai = 3;
							conta++;
							// printf("Contador: %d\n", conta);
						}
					}
					break;
				}
			}
		}
	}

	return ultimo;
}

int main(void){

	LIS_ListaDeOrigens *listaOrigens = criaLista();
	int** matriz;
	int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	int nVert;
	GRA_Node * referenciaUltimoNo;

	matriz = (int **)malloc(3 * sizeof(int *));

	for (int y = 0; y < 3; y++)
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

	permute(a, 0, 8);

	int contador = 0;

	for (int i = 0; i < 362880; ++i)
	{
		int** matrizNumero = ListaDeMatrizes[i];
		int numero = matrizParaNumero(matrizNumero);

		if (grafo[numero] == NULL) {
			insereNaLista(listaOrigens, DFS(matrizNumero));
			printf("\nNumero de verticies da componente %d: %ld\n", contador + 1, globalVertex);
			nVert = globalVertex;
			printf("\nNumero de arestas da componente %d: %ld\n", contador + 1, globalEdges / 2);
			contador++;
			globalVertex = 0;
			globalEdges = 0;
		}
	}

	printf("\nAchados %d componentes conexas\n", contador);

	referenciaUltimoNo = BFS(grafo[123456780], 181440);

	printf("\nArrumacao do jogo mais distante da solucao:");
	printMatriz(referenciaUltimoNo->matriz);
	printf("\nSequencia de movimentos para se chegar a solucao: \n");

	while(referenciaUltimoNo->pai!=NULL) {
		//printMatriz(referenciaUltimoNo->matriz);
		if(referenciaUltimoNo->posicaoPai == 2) {
			printf("CIMA, ");
		}
		if(referenciaUltimoNo->posicaoPai == 3) {
			printf("DIREITA, ");
		}
		if(referenciaUltimoNo->posicaoPai == 0) {
			printf("BAIXO, ");
		}
		if(referenciaUltimoNo->posicaoPai == 1) {
			printf("ESQUERDA, ");
		}
		referenciaUltimoNo = referenciaUltimoNo->pai;
	}

	printf("\n\nSolucao final: ");
	printMatriz(referenciaUltimoNo->matriz);

	return 0;
}