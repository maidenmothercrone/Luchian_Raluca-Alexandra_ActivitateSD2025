#include<stdio.h>
#include<malloc.h>

struct Telefon {
	int id;
	int RAM;
	char* producator;
	float pret;
	char serie;
};

struct Telefon initializare(int id, int ram, const char* producator, float pret, char serie) {
	struct Telefon t;
	t.id = id;
	t.RAM = ram;
	t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy_s(t.producator, strlen(producator) + 1, producator);
	t.pret = pret;
	t.serie = serie;
	return t;
}

void afisare(struct Telefon t) {
	printf("%d. Telefonul %s seria %c are %d Gb RAM si costa %5.2f RON.\n",
		t.id, t.producator, t.serie, t.RAM, t.pret);
}


void afisareVector(struct Telefon* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	struct Telefon*vectorNou=NULL;
	if (nrElementeCopiate > 0 && nrElementeCopiate <= nrElemente) {
		vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++) {
			vectorNou[i] = vector[i]; 
			vectorNou[i].producator = (char*)malloc(sizeof(char) * (strlen(vector[i].producator) + 1));
			strcpy_s(vectorNou[i].producator, strlen(vector[i].producator) + 1, vector[i].producator);
		}
	}
	else {
		printf("Numarul de elemente copiate nu este valid!\n");
	}

	return vectorNou;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {
	if ((*vector) != NULL) {
		for (int i = 0; i < (*nrElemente); i++) {
			free((*vector)[i].producator);
		}
		free(*vector);
		*vector = NULL;
		*nrElemente = 0;
	}
}

void copiazaTelefoaneScumpe(struct Telefon* vector, char nrElemente, float pretMinim, struct Telefon** vectorNou, int* dimensiune) {
	struct Telefon* vectorNou = NULL;
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].pret >= pretMinim){
			(*dimensiune)++;
		}
	};
	*vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * (*dimensiune));
	for (int i = 0; i < (*dimensiune);i++){
		vectorNou[i] = vector[i];
		vectorNou[i].producator = (char*)malloc(sizeof(char) * (strlen(vector[i].producator) + 1));
		strcpy_s(vectorNou[i].producator, strlen(vector[i].producator) + 1, vector[i].producator);
	}
}

struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Telefon t;
	t.id = 1;

	return t;
}
	


int main() {
	struct Telefon* telefoane = NULL;
	int nrTelefoane = 3;
	telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);
	telefoane[0] = initializare(1, 256, "Samsung", 2000, 'S');
	telefoane[1] = initializare(2, 512, "Motorola", 1500, 'M');
	telefoane[2] = initializare(3, 256, "Apple", 2200, 'A');

	afisareVector(telefoane, nrTelefoane);

	struct Telefon* telefoaneCopie = copiazaPrimeleNElemente(telefoane, nrTelefoane, 2);

	afisareVector(telefoaneCopie, 2);

	dezalocare(&telefoane, &nrTelefoane);
	afisareVector(telefoane, nrTelefoane);

	return 0;
}