#include<stdio.h>
#include<malloc.h>
#define MAX_LEN 100

struct Serial {
	int id;
	char* titlu;
	float rating;
	int sezoane;
};


struct Serial initializare(int id, const char* titlu, float rating, int sezoane) {
	struct Serial s;
	s.id = id;
	s.titlu = (char*)malloc(strlen(titlu) + 1);
	strcpy_s(s.titlu, strlen(titlu) + 1, titlu);
	s.rating = rating;
	s.sezoane = sezoane;
	return s;
};

struct Serial citireTastatura() {
	struct Serial s;
	printf("Introdu id-ul serialului: ");
	scanf_s("%d", &s.id);
	getchar();
	printf("Introdu titlul serialului: ");
	s.titlu = (char*)malloc(MAX_LEN);
	fgets(s.titlu, MAX_LEN, stdin);
	size_t len = strlen(s.titlu);
	if (len > 0 && s.titlu[len - 1] == '\n') {
		s.titlu[len - 1] = '\0';
	};
	printf("Introdu ratingul serialului: ");
	scanf_s("%f", &s.rating);
	getchar();
	printf("Introdu nr de sezoane al serialului: ");
	scanf_s("%d", &s.sezoane);
	return s;
};

float calculRatingMediu(struct Serial* seriale, int nrSeriale) {
	float suma = 0;
	for (int i = 0;i < nrSeriale;i++) {
		suma += seriale[i].rating;
	}
	return suma / nrSeriale;
};

void  adaugaSezoane(struct Serial* s) {
	s->sezoane++;
}

void afisare(struct Serial s) {
	printf("Id: %d\n", s.id);
	printf("Titlu: %s\n", s.titlu);
	printf("Rating: %.2f\n", s.rating);
	printf("Numar sezoane: %d\n\n", s.sezoane);
};




int main() {
	struct Serial serial = initializare(1, "Yellowjackets", 8.5, 3);
	struct Serial serial2 = initializare(2, "Agatha All Along", 6.7, 1);
	afisare(serial);
	afisare(serial2);
	adaugaSezoane(&serial2);
	printf("Dupa adaugare=> \n");
	afisare(serial2);

	struct Serial serial = citireTastatura();
	afisare(serial);
	int nrSeriale = 3;
	struct Serial* seriale;
	seriale = (struct Serial*)malloc(nrSeriale * sizeof(struct Serial));
	seriale[0] = citireTastatura();
	seriale[1] = citireTastatura();
	seriale[2] = citireTastatura();

	printf("Ratingul mediu al serialelor este: %.2f", calculRatingMediu(seriale, nrSeriale));

	return 0;
}