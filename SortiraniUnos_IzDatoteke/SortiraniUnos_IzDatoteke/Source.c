#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

struct _drzava;
typedef struct _drzava* pozicija;

typedef struct _drzava{
	char ime[MAX];
	pozicija next;
}drzava;



pozicija StvoriDrzavu();
int read_file_drzave(pozicija head);



int main() {

	drzava head = { .next = NULL, .ime = {0} };

	read_file_drzave(&head);

	return 0;
}
pozicija StvoriDrzavu() {
	pozicija Drzava = NULL;

	Drzava = (pozicija)malloc(sizeof(drzava));

	strcpy(Drzava->ime, "");
	Drzava->next = NULL;

	return Drzava;
}

int read_file_drzave(pozicija head) {
	pozicija drzava = NULL;
	pozicija lista = head;
	char ime[MAX];
	int i = 0;
	int n = 0;
	FILE* str;
	str = fopen("C:\\Users\\Luka\\Desktop\\test.txt", "r");

	if (str == NULL) {
		printf("error");
	}

	while (feof(str) == 0) {
		if (fgetc(str) == '\n') {
			n++;
		}
	}
	rewind(str);
	for (i = 0; i < n-1; i++) {
		drzava= StvoriDrzavu();
		fscanf(str, " %s", ime);
		strcpy(drzava->ime, ime);
		lista->next = drzava;
		printf("%s\n", lista->next->ime);
		lista = lista->next;
	}



	fclose(str);


	return 0;
}



