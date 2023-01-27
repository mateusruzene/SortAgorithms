#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenacao.h"

void imprimeVetor(int vetor[], int tam)
{
	printf("Vetor:");
	for (int i = 0; i < tam; i++)
	{
		printf("%d ", vetor[i]);
	}
}

int *criaVetor(int vetor[], int tam)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < tam; i++)
	{
		vetor[i] = rand() % tam + 1;
	}
	return vetor;
}

int main()
{
	char nome[MAX_CHAR_NOME];
	int idxBusca;
	int numComp;
	// Para medir o tempo, inclua time.h, e siga o exemplo:
	clock_t start, end; // variáveis do tipo clock_t
	double total;

	int tamVetor = 100000;
	int *vetor = malloc(tamVetor * sizeof(int));
	if (vetor == NULL)
	{
		printf("Falha fatal. Impossível alocar memoria.");
		return 1;
	}

	getNome(nome);
	printf("Trabalho de %s\n", nome);
	printf("GRR %u\n\n", getGRR());

	printf("\n--------Vetor Desordenado--------\n");
	criaVetor(vetor, tamVetor);
	/* Busca Sequencial Test */
	numComp = 0;
	idxBusca = buscaSequencial(vetor, tamVetor, 1, &numComp);
	printf("\nBusca Sequencial: \nindice do vetor = %d \nnumero de comparacoes = %d \n", idxBusca, numComp);

	/* Busca Binária Test */
	numComp = 0;
	idxBusca = buscaBinaria(vetor, tamVetor, 16, &numComp);
	printf("\nBusca binaria: \nindice do vetor = %d \nnumero de comparacoes = %d \n", idxBusca, numComp);

	/* Insertion Sort Test */
	criaVetor(vetor, tamVetor);
	start = clock();
	numComp = insertionSort(vetor, tamVetor);
	end = clock();
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf("\nTempo total Insertion Sort: %f \n", total);
	printf("\n");

	/* Selection Sort Test */
	criaVetor(vetor, tamVetor);
	start = clock();
	numComp = selectionSort(vetor, tamVetor);
	end = clock();
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf("\nTempo total Selection Sort: %f \n", total);
	printf("\n");

	/* Merge Sort Test */
	criaVetor(vetor, tamVetor);
	start = clock();
	numComp = mergeSort(vetor, tamVetor);
	end = clock();
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf("\n");
	printf("\nTempo total Merge Sort: %f \n", total);

	/* Quick Sort Test */
	criaVetor(vetor, tamVetor);
	start = clock();
	numComp = quickSort(vetor, tamVetor);
	end = clock();
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf("\n");
	printf("\nTempo total Quick Sort: %f \n", total);

	/* Heap Sort Test */
	criaVetor(vetor, tamVetor);
	start = clock();
	numComp = heapSort(vetor, tamVetor);
	end = clock();
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf("\n");
	printf("\nTempo total Heap Sort: %f \n", total);

	printf("\n-----------Vetor Ordenado---------\n");
	/* Busca Sequencial Test */
	numComp = 0;
	idxBusca = buscaSequencial(vetor, tamVetor, 16, &numComp);
	printf("\nBusca Sequencial: \nindice do vetor = %d \nnumero de comparacoes = %d \n", idxBusca, numComp);
	/* Busca Binária Test */
	numComp = 0;
	idxBusca = buscaBinaria(vetor, tamVetor, 16, &numComp);
	printf("\nBusca binaria: \nindice do vetor = %d \nnumero de comparacoes = %d \n", idxBusca, numComp);

	free(vetor);

	return 0;
}
