#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};

typedef struct StructuraMasina Masina;

//structura pentru heap
//un vector de elemente, lungimea vectorului si numarul de elemente din vector

struct Heap {
	Masina* vector;
	int lungime;
	int nrMasini;
};

typedef struct Heap Heap;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m;
	m.id = atoi(strtok(buffer, sep));
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m.model = malloc(strlen(aux) + 1);
	strcpy_s(m.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	m.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m.numeSofer, strlen(aux) + 1, aux);
	m.serie = *strtok(NULL, sep);
	return m;
}

void afisareMasini(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr usi: %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrMasini = 0;
	heap.vector = (Masina*)malloc(lungime * sizeof(Masina));
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	//filtreaza heap-ul pentru nodul a carei pozitie o primeste ca parametru
	int fiuStanga = 2 * pozitieNod + 1;
	int fiuDreapta = 2 * pozitieNod + 2;
	int pozitieMaxima = pozitieNod;
	if (fiuStanga < heap.nrMasini && heap.vector[pozitieMaxima].pret < heap.vector[fiuStanga].pret) {
		pozitieMaxima = fiuStanga;
	} 
	if (fiuDreapta < heap.nrMasini && heap.vector[pozitieMaxima].pret < heap.vector[fiuDreapta].pret) {
		pozitieMaxima = fiuDreapta;
	}
	if (pozitieMaxima != pozitieNod) {
		Masina aux = heap.vector[pozitieMaxima];
		heap.vector[pozitieMaxima] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;
		if (pozitieMaxima <= (heap.nrMasini - 2) / 2) {
			filtreazaHeap(heap, pozitieMaxima);
		}
	}
}

Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");

	Heap heap = initializareHeap(10);
	while (!feof(f)) {
		heap.vector[heap.nrMasini++] = citireMasinaDinFisier(f);
	}

	fclose(f);

	for (int i = (heap.nrMasini - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrMasini;i++) {
		afisareMasini(heap.vector[i]);
	}
}

void afisareHeapAscuns(Heap heap) {
	for (int i = heap.nrMasini;i < heap.lungime;i++) {
		afisareMasini(heap.vector[i]);
	}
}

Masina extrageMasina(Heap* heap) {
	if (heap->nrMasini > 0) {
		Masina aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrMasini - 1];
		heap->vector[heap->nrMasini - 1] = aux;
		heap->nrMasini--;
		for (int i = (heap->nrMasini - 2) / 2;i >= 0;i--) {
			filtreazaHeap(*heap, i);
		}
		return aux;
	}
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++) {
		free(heap->vector[i].model);
		free(heap->vector[i].numeSofer);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->lungime = 0;
	heap->nrMasini = 0;
}

int main() {
	Heap heap = citireHeapDeMasiniDinFisier("masini_arbore.txt");
	afisareHeap(heap);
	printf("Masini extrase:\n");
	afisareMasini(extrageMasina(&heap));


	printf("Heap-ul ascuns:\n");
	afisareHeapAscuns(heap);

	dezalocareHeap(&heap);
	afisareHeap(heap);

	return 0;
}