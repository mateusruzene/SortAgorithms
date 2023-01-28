#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenacao.h"

void getNome(char nome[])
{
	// substitua por seu nome
	strncpy(nome, "Mateus Siqueira Ruzene", MAX_CHAR_NOME);
	nome[MAX_CHAR_NOME - 1] = '\0'; // adicionada terminação manual para caso de overflow
}

// a função a seguir deve retornar o seu número de GRR
unsigned int getGRR()
{
	return 20221223;
}

/* Funções Auxiliares */
// insere elementos no vetor
int *insereVetor(int arr[], int tam, int *numComparacoes)
{
	int key = arr[tam];
	int j = tam - 1;
	while (j >= 0 && arr[j] > key)
	{
		arr[j + 1] = arr[j];
		j = j - 1;
		(*numComparacoes)++;
	}
	arr[j + 1] = key;
	return numComparacoes;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int left(int i)
{
	return (2 * i + 1);
}

int right(int i)
{
	return ((2 * i) + 2);
}

int *merge(int vetor[], int l, int m, int r, int *numComparacoes)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
	{
		L[i] = vetor[l + i];
	}
	for (j = 0; j < n2; j++)
	{
		R[j] = vetor[m + 1 + j];
	}

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			(*numComparacoes)++;
			vetor[k] = L[i];
			i++;
		}
		else
		{
			(*numComparacoes)++;
			vetor[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		vetor[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		vetor[k] = R[j];
		j++;
		k++;
	}

	return numComparacoes;
}

int partition(int vetor[], int low, int high, int *numComparacoes)
{
	int pivo = vetor[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (vetor[j] <= pivo)
		{
			i++;
			swap(&vetor[i], &vetor[j]);
		}
		(*numComparacoes)++;
	}
	swap(&vetor[i + 1], &vetor[high]);
	return (i + 1);
}

/* Funções principais */

/* -------------- Funções BUSCA Sequencial -------------- */
int buscaSequencial(int vetor[], int tam, int valor, int *numComparacoes)
{
	if (tam == 0)
		return -1;
	(*numComparacoes)++;
	if (vetor[tam - 1] == valor)
		return tam - 1;
	return buscaSequencial(vetor, tam - 1, valor, numComparacoes);
}
/* -------------- Funções BUSCA BINÁRIA -------------- */
int buscaBinariaRecursiva(int vetor[], int esquerda, int direita, int valor, int *numComparacoes)
{
	if (esquerda > direita)
		return -1;

	int meio = esquerda + (direita - esquerda) / 2;

	(*numComparacoes)++;
	if (vetor[meio] == valor)
		return meio;
	else if (vetor[meio] > valor)
	{
		(*numComparacoes)++;
		return buscaBinariaRecursiva(vetor, esquerda, meio - 1, valor, numComparacoes);
	}
	else
	{
		(*numComparacoes)++;
		return buscaBinariaRecursiva(vetor, meio + 1, direita, valor, numComparacoes);
	}
}

int buscaBinaria(int vetor[], int tam, int valor, int *numComparacoes)
{
	return buscaBinariaRecursiva(vetor, 0, tam - 1, valor, numComparacoes);
}

/* -------------- Funções INSETION SORT -------------- */
int insertionSortRecursive(int vetor[], int tam, int *numComparacoes)
{
	if (0 < tam)
	{
		insertionSortRecursive(vetor, tam - 1, numComparacoes);
		numComparacoes = insereVetor(vetor, tam - 1, numComparacoes);
	}
	return *numComparacoes;
}

int insertionSort(int vetor[], int tam)
{
	int numComp = 0;
	numComp = insertionSortRecursive(vetor, tam, &numComp);
	return numComp;
}

/* -------------- Funções SELECTION SORT -------------- */
int selectionSortRecursive(int vetor[], int n, int index, int *numComparacoes)
{
	if (index == n)
		return *numComparacoes;

	// acha o menor valor do vetor
	int min_index = index;
	for (int i = index + 1; i < n; i++)
	{
		if (vetor[i] < vetor[min_index])
			min_index = i;
		(*numComparacoes)++;
	}
	swap(&vetor[min_index], &vetor[index]);
	return selectionSortRecursive(vetor, n, index + 1, numComparacoes);
}

int selectionSort(int vetor[], int tam)
{
	int numComp = 0;
	numComp = selectionSortRecursive(vetor, tam, 0, &numComp);
	return numComp;
}

/* -------------- Funções MERGE SORT -------------- */
int mergeSortRecursive(int vetor[], int l, int r, int *numComparacoes)
{
	int m = l + (r - l) / 2;
	if (l < r)
	{
		mergeSortRecursive(vetor, l, m, numComparacoes);
		mergeSortRecursive(vetor, m + 1, r, numComparacoes);
		numComparacoes = merge(vetor, l, m, r, numComparacoes);
	}

	return *numComparacoes;
}

int mergeSort(int vetor[], int tam)
{
	int numComp = 0;
	numComp = mergeSortRecursive(vetor, 0, tam, &numComp);
	return numComp;
}

/* -------------- Funções QUICK SORT -------------- */
int quickSortRecursive(int arr[], int low, int high, int *numComparacoes)
{
	if (low < high)
	{
		int pi = partition(arr, low, high, numComparacoes);

		quickSortRecursive(arr, low, pi - 1, numComparacoes);
		quickSortRecursive(arr, pi + 1, high, numComparacoes);
	}
	return *numComparacoes;
}

int quickSort(int vetor[], int tam)
{
	int numComp = 0;
	numComp = quickSortRecursive(vetor, 0, tam, &numComp);
	return numComp;
}

/* -------------- Funções HEAP SORT -------------- */
void heapify(int vetor[], int i, int tam, int *numComparacoes)
{
	int l, r, maior;
	int n = tam - 1;
	maior = i;

	l = left(i);
	r = right(i);

	(*numComparacoes)++;
	if (l <= n && vetor[l] > vetor[maior])
		maior = l;
	(*numComparacoes)++;
	if (r <= n && vetor[r] > vetor[maior])
		maior = r;

	if (maior != i)
	{
		swap(&vetor[i], &vetor[maior]);
		heapify(vetor, maior, tam, numComparacoes);
	}
}
void heap(int vetor[], int tam, int *numComparacoes)
{
	for (int i = tam / 2 - 1; i >= 0; i--)
		heapify(vetor, i, tam, numComparacoes);
}
int heapSort(int vetor[], int tam)
{
	int i;
	int numComp = 0;

	heap(vetor, tam, &numComp);
	for (i = tam - 1; i >= 0; i--)
	{
		swap(&vetor[0], &vetor[i]);
		heapify(vetor, i, 0, &numComp);
	}

	return numComp;
}