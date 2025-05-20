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

struct Nod {
	Masina info;
	struct Nod* stanga;
	struct Nod* dreapta;

};

typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	Masina m;
	m.id = atoi(strtok(buffer, sep));
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));
	char* aux;
	aux = strtok(NULL, sep);
	m.model = malloc(strlen(aux) + 1);
	strcpy_s(m.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	m.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m.numeSofer, strlen(aux) + 1, aux);
	m.serie = *strtok(NULL, sep);
	return m;
}

void afisareMasina(Masina m) {
	printf("ID: %d\n", m.id);
	printf("Nr usi: %d\n", m.nrUsi);
	printf("Pret: %.2f\n", m.pret);
	printf("Model: %s\n", m.model);
	printf("Sofer: %s\n", m.numeSofer);
	printf("Serie: %c\n", m.serie);
}

void adaugaMasinaInArbore(Nod** rad, Masina masinaNoua) {
	if (*rad != NULL) {
		if (masinaNoua.id < &(*rad)->info.id) {
			adaugaMasinaInArbore(&(*rad)->stanga, masinaNoua);
		}
		else adaugaMasinaInArbore(&(*rad)->dreapta, masinaNoua);
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->info.model = (char*)malloc(strlen(masinaNoua.model) + 1);
		strcpy_s(nou->info.model, strlen(masinaNoua.model) + 1, masinaNoua.model);
		nou->info.numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
		strcpy_s(nou->info.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
		nou->stanga = NULL;
		nou->dreapta = NULL;
		(*rad) = nou;
	}
};

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* nou = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);	
		adaugaMasinaInArbore(&nou, m);
		free(m.model);
		free(m.numeSofer);
	}
	fclose(f);
	return nou;
}

void afisareMasiniDinArborePreordine(Nod* rad) {
	if (rad != NULL) {
		afisareMasina(rad->info);
		afisareMasiniDinArborePreordine(rad->stanga);
		afisareMasiniDinArborePreordine(rad->dreapta);
	}
}

void afisareMasiniDinArboreInordine(Nod* rad) {
	if (rad != NULL) {
		afisareMasiniDinArboreInordine(rad->stanga);
		afisareMasina(rad->info);
		afisareMasiniDinArboreInordine(rad->dreapta);
	}
}

void afisareMasiniDinArborePostordine(Nod* rad) {
	if (rad != NULL) {
		afisareMasiniDinArborePostordine(rad->stanga);
		afisareMasiniDinArborePostordine(rad->dreapta);
		afisareMasina(rad->info);
	}
}

void dezalocareArboreDeMasini(Nod** rad) {
	if (*rad != NULL) {
		dezalocareArboreDeMasini(&(*rad)->stanga);
		dezalocareArboreDeMasini(&(*rad)->dreapta);
		free((*rad)->info.model);
		free((*rad)->info.numeSofer);
		free((*rad));
		(*rad) = NULL;
	}
}

int main() {
	Nod* rad = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	printf("Afisare preordine:\n");
	afisareMasiniDinArborePreordine(rad);
	printf("Afisare inordine:\n");
	afisareMasiniDinArboreInordine(rad);
	printf("Afisare postordine:\n");
	afisareMasiniDinArborePostordine(rad);
	dezalocareArboreDeMasini(&rad);
	afisareMasiniDinArborePreordine(rad);


	return 0;
}