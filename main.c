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
	clock_t start, end;
	double total;

	int tamVetor = 65000; /* se colocar um valor muito alto aqui, os números de comparação no terminal vão ficar negativos por estourarem o valor máximo permitido do int, 65000 foi o maior valor que eu encontrei sem deixar os números de comparações negativos */
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
	idxBusca = buscaSequencial(vetor, tamVetor, 13455, &numComp);
	printf("\nBusca Sequencial: \nindice do vetor = %d \nnumero de comparacoes = %d \n", idxBusca, numComp);

	/* Busca Binária Test */
	numComp = 0;
	idxBusca = buscaBinaria(vetor, tamVetor, 13455, &numComp);
	printf("\nBusca binaria: \nindice do vetor = %d \nnumero de comparacoes = %d \n", idxBusca, numComp);

	/* Insertion Sort Test */
	criaVetor(vetor, tamVetor);
	numComp = 0;
	start = clock();
	numComp = insertionSort(vetor, tamVetor);
	end = clock();
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf("\nTempo total Insertion Sort: %f \n", total);
	printf("Numero total de comparações Insertion Sort: %d \n", numComp);
	printf("\n");

	/* Selection Sort Test */
	criaVetor(vetor, tamVetor);
	numComp = 0;
	start = clock();
	numComp = selectionSort(vetor, tamVetor);
	end = clock();
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf("\nTempo total Selection Sort: %f \n", total);
	printf("Numero total de comparações Selection Sort: %d \n", numComp);
	printf("\n");

	/* Merge Sort Test */
	criaVetor(vetor, tamVetor);
	numComp = 0;
	start = clock();
	numComp = mergeSort(vetor, tamVetor);
	end = clock();
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf("\nTempo total Merge Sort: %f \n", total);
	printf("Numero total de comparações Merge Sort: %d \n", numComp);
	printf("\n");

	/* Quick Sort Test */
	criaVetor(vetor, tamVetor);
	numComp = 0;
	start = clock();
	numComp = quickSort(vetor, tamVetor);
	end = clock();
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf("\nTempo total Quick Sort: %f \n", total);
	printf("Numero total de comparações Quick Sort: %d \n", numComp);
	printf("\n");

	/* Heap Sort Test */
	criaVetor(vetor, tamVetor);
	numComp = 0;
	start = clock();
	numComp = heapSort(vetor, tamVetor);
	end = clock();
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf("\nTempo total Heap Sort: %f \n", total);
	printf("Numero total de comparações Heap Sort: %d \n", numComp);
	printf("\n");

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
