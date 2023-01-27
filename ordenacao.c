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
void insereVetor(int arr[], int tam)
{
	int key = arr[tam];
	int j = tam - 1;
	while (j >= 0 && arr[j] > key)
	{
		arr[j + 1] = arr[j];
		j = j - 1;
	}
	arr[j + 1] = key;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void merge(int vetor[], int l, int m, int r)
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
			vetor[k] = L[i];
			i++;
		}
		else
		{
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
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	int temp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp;
	return (i + 1);
}

/* Funções principais */

/* -------------- Funções BUSCA Sequencial -------------- */
int buscaSequencial(int vetor[], int tam, int valor, int *numComparacoes)
{
	(*numComparacoes)++;
	if (tam == 0)
		return -1;
	if (vetor[tam - 1] == valor)
	{
		(*numComparacoes)++;
		return tam - 1;
	}
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
	return buscaBinariaRecursiva(vetor, 0, tam, valor, numComparacoes);
}

/* -------------- Funções INSETION SORT -------------- */
int insertionSort(int vetor[], int tam)
{
	if (0 >= tam)
	{
		return 1;
	}
	insertionSort(vetor, tam - 1);
	insereVetor(vetor, tam - 1);
	return 1;
}

/* -------------- Funções SELECTION SORT -------------- */
int selectionSortRecursive(int vetor[], int n, int index)
{
	if (index == n)
		return -1;

	// acha o menor valor do vetor
	int min_index = index;
	for (int i = index + 1; i < n; i++)
	{
		if (vetor[i] < vetor[min_index])
		{
			min_index = i;
		}
	}
	swap(&vetor[min_index], &vetor[index]);
	return selectionSortRecursive(vetor, n, index + 1);
}

int selectionSort(int vetor[], int tam)
{
	return selectionSortRecursive(vetor, tam, 0);
}

/* -------------- Funções MERGE SORT -------------- */
int mergeSortRecursive(int vetor[], int l, int r)
{
	if (l >= r)
		return -1;
	int m = l + (r - l) / 2;

	mergeSortRecursive(vetor, l, m);
	mergeSortRecursive(vetor, m + 1, r);

	merge(vetor, l, m, r);

	return 0;
}

int mergeSort(int vetor[], int tam)
{
	return mergeSortRecursive(vetor, 0, tam);
}

/* -------------- Funções QUICK SORT -------------- */
int quickSortRecursive(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSortRecursive(arr, low, pi - 1);
		quickSortRecursive(arr, pi + 1, high);
	}
	return -1;
}

int quickSort(int vetor[], int tam)
{
	return quickSortRecursive(vetor, 0, tam);
}

/* -------------- Funções HEAP SORT -------------- */
void heapify(int vetor[], int tam, int i)
{
	int maior = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < tam && vetor[l] > vetor[maior])
		maior = l;

	if (r < tam && vetor[r] > vetor[maior])
		maior = r;

	if (maior != i)
	{
		int swap = vetor[i];
		vetor[i] = vetor[maior];
		vetor[maior] = swap;

		heapify(vetor, tam, maior);
	}
}

int heapSort(int vetor[], int tam)
{
	int i;
	for (i = tam / 2 - 1; i >= 0; i--)
		heapify(vetor, tam, i);

	for (i = tam - 1; i >= 0; i--)
	{
		swap(&vetor[0], &vetor[i]);
		heapify(vetor, i, 0);
	}

	return 1;
}