#include<stdio.h>
#include<stdlib.h>

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
	t.producator = (char*)malloc(sizeof(char) * (strlen(producator)+1));
	strcpy_s(t.producator, strlen(producator) + 1, producator);
	t.pret = pret;
	t.serie = serie;
	return t;
}

void afisare(struct Telefon t) {
	printf("%d. Telefonul %s seria %c are %d Gb RAM si costa %5.2f RON.\n",
		t.id, t.producator, t.serie, t.RAM, t.pret);
}

void modificaPret(struct Telefon* t, float noulPret) {
	if (noulPret > 0) {
		t->pret = noulPret;
	}
}

void dezalocare(struct Telefon *t) {
	if (t->producator != NULL) {
		free(t->producator);
		t->producator = NULL;
		printf("Memoria pentru producator a fost eliberata.\n");
	}
}

int main() {
	struct Telefon t;
	t = initializare(1, 256, "Samsung", 2000.5, 'A');
	afisare(t);
	modificaPret(&t, 1500.5);
	afisare(t);
	dezalocare(&t);
	return 0;
}