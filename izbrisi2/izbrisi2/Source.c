#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

struct _osoba;
typedef struct _osoba* pozicija;
typedef struct _osoba {
	char ime[MAX];
	char prezime[MAX];
	int godina_rodenja;
	pozicija next;
}osoba;

pozicija novaOsoba1() {
	pozicija novaOsoba = NULL;

	char ime[MAX];
	char prezime[MAX];
	int godina;

	novaOsoba = (pozicija)malloc(sizeof(osoba));

	printf("Unesi ime:");
	scanf("%s", &ime);
	printf("Unesi prezime:");
	scanf("%s", &prezime);
	printf("Unesi godinu:");
	scanf("%d", &godina);

	strcpy(novaOsoba->ime, ime);
	strcpy(novaOsoba->prezime, prezime);
	novaOsoba->godina_rodenja = godina;

	return novaOsoba;
}

pozicija zadnji1(pozicija head) {

	pozicija current=head;

	while(current->next)
	{
		current = current->next;
	}
	return current;
}
//pozicija Trazi(pozicija head) {
//	char osoba1[MAX];
//
//	printf("Unesi prezime onoga koga trazis: ");
//	scanf("%s", osoba1);
//
//	pozicija element = head;
//
//	if(element)
//
//}
	

int UnosP(pozicija head) {
	
	pozicija novaOsoba=NULL;

	novaOsoba = novaOsoba1();

	if(novaOsoba)
	{
		novaOsoba->next = head->next;
		head->next = novaOsoba;
	}

	return 0;
}

int UnosK(pozicija head) {

	pozicija novaOsoba = NULL;
	pozicija zadnji=NULL;

	novaOsoba = novaOsoba1();
	
	zadnji = zadnji1(head);

	if (novaOsoba)
	{
		novaOsoba->next = zadnji->next;
		zadnji->next = novaOsoba;
	}

	return 0;
}

int Printanje(pozicija element) {

	pozicija trenutno = element;

	while (trenutno != NULL)
	{
		printf("Ime: %s\tPrezime: %s\tGodine: %d\n", trenutno->ime, trenutno->prezime, trenutno->godina_rodenja);
		trenutno = trenutno->next;
		}

	return 0;
}

int menu(pozicija head) {
	char znak;


	

	while (1)
	{
		printf("A - unos na pocetak liste\nB - unos na kraj liste\nP - printanje liste\n");
		scanf("%c", &znak);

		switch (znak)
		{
		case 'a':
		case 'A':
			UnosP(head);
			continue;
		case 'b':
		case 'B':
			UnosK(head);
			continue;
		case 'p':
		case 'P':
			Printanje(head->next);
			break;
		/*case 't':
		case 'T':
			Trazi(head);
			break;*/
		case 'x':
		case 'X':
			break;
		default:
			printf("unia si krivo slovo\n");
			continue;
		}
		break;
	}

	return 0;
}

int main() {
	osoba head = { .ime = {0}, .prezime = {0}, .next = NULL, .godina_rodenja = 0 };
	

	menu(&head);



	return 0;
}