#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod {
	Masina info;
	struct Nod* next;
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

void afisareListaMasini(Nod* cap) {
	while (cap != NULL) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua; //shallow copy
	nodNou->next = NULL;

	if ((*cap)) {
		Nod* p = (*cap);
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nodNou;
	}
	else {
		(*cap) = nodNou;
		(*cap)->next = NULL;
	}
}

void adaugaLaInceputInLista(Nod* *cap, Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua; //shallow copy
	nodNou->next = (*cap);
	(*cap) = nodNou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			//creem lista cu inserare la sfarsit
			adaugaMasinaInLista(&cap, citireMasinaDinFisier(f));

		}
	}
	fclose(f);
	return cap;
}

void dezalocareListaMasini(Nod* *cap) {
	//dezalocare lista
	Nod* p = (*cap);
	while (p != NULL) {
		Nod* aux = p;
		p = p->next;
		free(aux->info.model);
		free(aux->info.numeSofer);
		free(aux);
	}
	(*cap) = NULL;
}

float calculeazaPretMediu(Nod* cap) {
	//calculeaza pretul mediu al masinilor din lista.
	float suma = 0;
	int nrMasini = 0;
	while (cap != NULL) {
		suma += cap->info.pret;
		nrMasini++;
		cap = cap->next;
	}
	if (nrMasini != 0) {
		return (suma / nrMasini);
	}
	else return 0;
}

void stergeMasiniDinSeria(Nod* *cap, char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	Nod* p = (*cap);
	Nod* aux = NULL;
	while (p != NULL) {
		if (p->info.serie == serieCautata) {
			if (p == (*cap)) {
				aux = p;
				(*cap) = (*cap)->next;
				free(aux->info.model);
				free(aux->info.numeSofer);
				free(aux);
				p = (*cap);
			}
			else {
				aux->next = p->next;
				free(p->info.model);
				free(p->info.numeSofer);
				free(p);
				p = aux->next;
			}
		}
		else {
			aux = p;
			p = p->next;
		}
	}
}

float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	float suma = 0;
	while (cap != NULL) {
		if (strcmp(cap->info.numeSofer, numeSofer) == 0) {
			suma += cap->info.pret;
		}
		cap = cap->next;
	}

	return suma;
}

int main() {
	Nod* cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);
	printf("\n\nPretul mediu este: %.2f", calculeazaPretMediu(cap));

	printf("\n\nPretul masinilor soferului Gigel este: %.2f\n", calculeazaPretulMasinilorUnuiSofer(cap, "Gigel"));

	stergeMasiniDinSeria(&cap, 'A');
	afisareListaMasini(cap);

	dezalocareListaMasini(&cap);
	afisareListaMasini(cap);

	return 0;
}