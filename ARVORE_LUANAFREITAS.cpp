#include<string.h>
#include<conio.h>
#include<windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct arvore
{
	struct arvore *pais;
	struct arvore *esquerda;
	struct arvore *direita;
	int chave;
} node;

int main(int argc, char *argv[])
{
	
	setlocale (LC_ALL, "Portuguese");
	
	// Funções declaradas	
	node *busca (node *raiz, int chave);
	node *inserir (node *raiz, int chave);
	node *minimo (node *raiz);
	node *maximo (node *raiz);
	void imprimir (node *raiz);
	void deletar (node *raiz, int chave);


	node *root, *aux;
	root = NULL;


	int op, dado;
	do {
		printf ("\nÁRVORE BINÁRIA\n[1] Inserir\n[2] Apagar\n[3] Minimo\n[4] Maximo\n[5] Imprimir\n[0] Sair\n");
		scanf ("%d", &op);

		switch(op){
			case 1:
				printf ("Insira um número: ");
				scanf ("%d", &dado);
				root = inserir (root, dado);
				break;

			case 2:
				printf ("Insira o valor a ser apagado: ");
				scanf ("%d", &dado);
				deletar (root, dado);
				break;
			
			case 3:
				printf ("Menor valor: ");
				aux = minimo (root);
				printf ("%d\n", (*aux).chave);
				break;

			case 4:
				printf ("Maior valor: ");
				aux = maximo (root);
				printf ("%d\n", (*aux).chave);
				break;

			case 5:
				imprimir (root);
				printf("\n");
				break;
		}    		
	}while (op != 0);

	return 0;
}

node *busca (node *raiz, int chave)
{
	node *aux = raiz;

	while (aux != NULL) 
	{
		if ((*aux).chave == chave) {		
			return aux;
		} else if (chave < (*aux).chave) {
			aux = (*aux).esquerda;
		} else {
			aux = (*aux).direita;
		}
	}
	return NULL;
}

node *inserir (node *raiz, int chave) 
{
	node *aux;

	if (raiz == NULL) {
		raiz = (node*) malloc (sizeof(node));
		(*raiz).chave = chave;
		(*raiz).pais = (*raiz).esquerda = (*raiz).direita = NULL;
	}

	else { 
		if (chave <= (*raiz).chave) {
			aux = inserir ((*raiz).esquerda, chave);
			(*raiz).esquerda = aux;
			(*aux).pais = raiz;
		} else {
			aux = inserir ((*raiz).direita, chave);
			(*raiz).direita = aux;
			(*aux).pais = raiz;
		}
	}

	return raiz;
}

void imprimir (node *raiz)
{
	if (raiz != NULL) {
		imprimir ((*raiz).esquerda);
		printf("%d  ", (*raiz).chave);
		imprimir ((*raiz).direita);
	}
}

node *minimo (node *raiz) 
{
	node *aux = raiz;

	while (aux != NULL)
	{
		if ((*aux).esquerda == NULL) {
			break;
		} else {
			aux = (*aux).esquerda;
		}
	}
	return aux;
}

node *maximo (node *raiz) 
{
	node *aux = raiz;

	while (aux != NULL)
	{
		if ((*aux).direita == NULL) {
			break;
		} else {
			aux = (*aux).direita;
		}
	}
	return aux;
}





void deletar (node *raiz, int chave)
{
	if (raiz == NULL) {
		return;
	}

	node *pai, *filho, *aux, *set;

	set = busca (raiz, chave);
	if (set == NULL){
		printf("Valor não encontrado.\n");
		return;
	} else
		printf("Deletado.\n");

	pai = (*set).pais;


	if (((*set).esquerda == NULL) && ((*set).direita == NULL)) {

		if ((*pai).direita == set)
			(*pai).direita = NULL;
		

		else
			(*pai).esquerda = NULL;
		
		free (set);
		return;
	}
	

	if ((*set).esquerda == NULL) {
		filho = (*set).direita;

		if (chave < (*pai).chave)
			(*pai).esquerda = (*set).direita;
		else
			(*pai).direita = (*set).direita;

		(*filho).pais = (*set).pais;
		free(set);

	} else if ((*set).direita == NULL) {
		filho = (*set).esquerda;

		if (chave > (*pai).chave)
			(*pai).direita = (*set).esquerda;
		else
			(*pai).esquerda = (*set).esquerda;

		(*filho).pais = (*set).pais;
		free(set);
	}

	else {
		aux = minimo ((*set).direita);

		(*set).chave = (*aux).chave;
		
		deletar ((*set).direita, (*aux).chave);

		return;
	}
	return;
}
