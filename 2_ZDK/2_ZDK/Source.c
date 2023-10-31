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
	int godine;
	pozicija next;
}osoba;

pozicija Pronadi(pozicija element) {
	char prezime[MAX];
	pozicija current=NULL;

	printf("Unesi prezime koje trazis:\n");
	scanf(" %s", prezime);

	while (element) {
		if (strcmp(element->prezime, prezime) != 0)
		{
			element = element->next;
		}
		else
		{
			current = element;
			return current;
		}

	}
	return 0;
}

pozicija Pronadi1(pozicija element) {
	char prezime[MAX];

	printf("Unesi prezime koje trazis:\n");
	scanf(" %s", prezime);

	while(element->next)
	{
		if (strcmp(element->next->prezime, prezime) == 0)
		{
			return element;
		}
		else element = element->next;
	}

	return 0;
}

pozicija Zadnji1(pozicija head) {
	pozicija zadnji=head;

	while (zadnji->next) {
		
		zadnji = zadnji->next;
	}
	return zadnji;
}

pozicija StvoriOsobu() {
	pozicija NovaOsoba = NULL;
	char ime[MAX];
	char prezime[MAX];
	int godine;
	NovaOsoba = (pozicija)malloc(sizeof(osoba));

	printf("Unesi Ime: \n");
	scanf(" %s", ime);
	printf("Unesi Prezime: \n");
	scanf(" %s", prezime);
	printf("Unesi Godine: \n");
	scanf(" %d", &godine);

	strcpy(NovaOsoba->ime, ime);
	strcpy(NovaOsoba->prezime, prezime);
	NovaOsoba->godine = godine;

	return NovaOsoba;
}

int UbaciPrije(pozicija element) {
	pozicija NovaOsoba;
	NovaOsoba = StvoriOsobu();

	NovaOsoba->next = element->next;
	element->next = NovaOsoba;
	return 0;
}

int UbaciNakon(pozicija element) {
	pozicija NovaOsoba;
	NovaOsoba = StvoriOsobu();

	NovaOsoba->next=element->next;
	element->next = NovaOsoba;

	return 0;
}
int Brisi(pozicija head) {
	pozicija current = head;
	pozicija prije = NULL;
	char prezime[MAX];

	printf("Unesi prezime koje trazis:\n");
	scanf(" %s", prezime);

	while (current->next && strcmp(current->prezime, prezime) != 0) 
	{
		prije = current;
		current = current->next;
	}

	if(strcmp(current->prezime, prezime)==0)
	{
		prije->next = current->next;
		current->next = prije;
	}

	return 0;
}

int UnosP(pozicija head) {
	pozicija NovaOsoba;
	NovaOsoba = StvoriOsobu();

	NovaOsoba->next = head->next;
	head->next = NovaOsoba;

	return 0;
}

int UnosK(pozicija head) {
	pozicija NovaOsoba;
	NovaOsoba = StvoriOsobu();
	pozicija zadnji = Zadnji1(head);

	NovaOsoba->next = zadnji->next;
	zadnji->next = NovaOsoba;

	return 0;
}

int Printanje(pozicija element) {

	while (element) {
		printf("Ime: %s\tPrezime: %s\tGodine: %d\n", element->ime,element->prezime, element->godine);
		element = element->next;
	}

	return 0;
}

int menu(pozicija head) {
	char znak;
	pozicija osoba1, osoba2 = NULL;

	while (1)
	{
		printf("a - unos na pocetak\nb - unos na kraj\np - printanje\nr - pronadi\nw - izbrisi\ne - ubaci nakon\n-------------------\n ");
		scanf(" %c", &znak);
		switch (znak)
		{
		case'a':
			UnosP(head);
			continue;
		case'b':
			UnosK(head);
			continue;
		case'p':
			Printanje(head->next);
			continue;
		case'r':
			Pronadi(head->next);
			continue;
		case'w':
			Brisi(head);
			continue;
		case'e':
			osoba1 = Pronadi(head->next);
			UbaciNakon(osoba1);
			continue;
		case'q':
			osoba2 = Pronadi1(head);
			UbaciPrije(osoba2);
			continue;
		default:
			printf("krivo slovo\n");
			continue;
		}
		break;
	}

	return 0;
}

int main() {
	osoba head = { .ime = {0}, .prezime = {0}, .next = NULL, .godine = 0 };

	menu(&head);



	return 0;
}