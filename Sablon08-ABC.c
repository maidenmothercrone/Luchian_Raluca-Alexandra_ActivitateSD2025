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

//creare structura pentru un nod dintr-un arbore binar de cautare

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
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

int calculGradEchilibru(Nod* radacina) {
	return calculeazaInaltimeArbore(radacina->stanga) - calculeazaInaltimeArbore(radacina->dreapta);
}


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	if ((*radacina) != NULL) {
		if (masinaNoua.id < (*radacina)->info.id) {
			adaugaMasinaInArbore(&(*radacina)->stanga, masinaNoua);
		}
		else {
			adaugaMasinaInArbore(&(*radacina)->dreapta, masinaNoua);
		}

		//verificam gradul de echilibru
		int GE = calculGradEchilibru((*radacina));

		if (GE = -2) {
			//dezechilibru de dreapta

		}
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
		(*radacina) = nou;
	}

}

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

void afisareMasiniDinArbore(Nod* radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere

	//1. preordine
	if (radacina != NULL) {
		afisareMasina(radacina->info);
		afisareMasiniDinArbore(radacina->stanga);
		afisareMasiniDinArbore(radacina->dreapta);
	}

	////2. inordine
	//printf("Inordine:\n");
	//if ((*radacina) != NULL) {
	//	afisareMasiniDinArbore(&(*radacina)->stanga);
	//	afisareMasina((*radacina)->info);
	//	afisareMasiniDinArbore(&(*radacina)->dreapta);
	//}

	////3. postordine
	//printf("Postordine:\n");
	//if ((*radacina) != NULL) {
	//	afisareMasiniDinArbore(&(*radacina)->stanga);
	//	afisareMasiniDinArbore(&(*radacina)->dreapta);
	//	afisareMasina((*radacina)->info);
	//}
}

void dezalocareArboreDeMasini(Nod** radacina) {
	//sunt dezalocate toate masinile si arborele de elemente
	if ((*radacina) != NULL) {
		dezalocareArboreDeMasini(&(*radacina)->stanga);
		dezalocareArboreDeMasini(&(*radacina)->dreapta);
		free((*radacina)->info.model);
		free((*radacina)->info.numeSofer);
		free((*radacina));
		(*radacina) = NULL;
	}
}

Masina getMasinaByID(Nod* radacina, int id) {
	Masina m;
	m.id = -1;
	if (radacina != NULL) {
		if (radacina->info.id == id) {
			return radacina->info;
		}
		else if (id < radacina->info.id) {
			return getMasinaByID(radacina->stanga, id);
		}
		else {
			return getMasinaByID(radacina->dreapta, id);
		}
	}
	return m;
}

int determinaNumarNoduri(/*arborele de masini*/) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	return 0;
}

int calculeazaInaltimeArbore(Nod* radacina) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	if (radacina != NULL) {
		int HS = calculeazaInaltimeArbore(radacina->stanga);
		int HD = calculeazaInaltimeArbore(radacina->dreapta);
		if (HS > HD) {
			return HS + 1;
		}
		else {
			return HD + 1;
		}
	}
		else {
		return 0;
	}
}

float calculeazaPretTotal(/*arbore de masini*/) {
	//calculeaza pretul tuturor masinilor din arbore.
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {

	Nod* radacina = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisareMasiniDinArbore(radacina);

	afisareMasina(getMasinaByID(radacina, 7));

	return 0;
}