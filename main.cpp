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

void adicionaAosExplorados(GRA_Grafo* G,GRA_Node* no) {

	GRA_Node* noAux;

	if(G->origem == NULL) {
		G->origem = no;
	} else {
		noAux = G->origem;
		while(noAux->proximo != NULL) {
			noAux = noAux -> proximo;
		}
		noAux->proximo = no;
	}
}

GRA_Node* verificaSeExplorado(GRA_Grafo* G,int** matrizFilho) {

	GRA_Node* noAux = G->origem;

	while(noAux->proximo != NULL) {
		if (comparaMatriz(noAux->matriz,matrizFilho) == 1) {
			return noAux;
		}
	}

	return NULL;
}

void adicionaVizinho(GRA_Node* no, GRA_Node* noVizinho, int i) {

	if(i==0) {
		no->cima = noVizinho;
	}
	if(i==1) {
		no->direita = noVizinho;
	}
	if(i==2) {
		no->baixo = noVizinho;
	}
	if(i==3) {
		no->esquerda = noVizinho;
	}
	
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

			adicionaVizinho(no, noVizinho,i);

		}
	}

	return no;
}

int main(void){
	printf("quero");
}