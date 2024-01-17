#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20
struct _osoba;
typedef struct _osoba* pozicija;
typedef struct _osoba {

	int broj;
	pozicija next;
}osoba;

int menu(pozicija head);
pozicija stvori();
pozicija pronadizadnji(pozicija head, pozicija element);
int UnosP(pozicija head);
int UnosK(pozicija head);
int printanje(pozicija head, pozicija element);
pozicija pronadi(pozicija head, pozicija element);
int UnosNakon( pozicija element);
int UnosIspred(pozicija head, pozicija element);
pozicija pronadi2(pozicija head, pozicija element);
void Brisanje(pozicija head);


int main() {

	osoba head = {.next=NULL, .broj=0 };

	menu(&head);

	return 0;
}

int menu(pozicija head) {

	char znak;
	pozicija broj1;
	pozicija broj2;

	while (1) {
		printf("a-unos pocetak\nb-unos kraj\np-printanje\n------------\n");
		scanf(" %c", &znak);
		switch (znak) {
		case'a':
			UnosP(head);
			continue;
		case'b':
			UnosK(head);
			continue;
		case'p':
			printanje(head, head->next);
			continue;
		case'n':
			broj1 = pronadi(head, head->next);
			UnosNakon(broj1);
			continue;
		case'i':
			broj2 = pronadi2(head, head->next);
			UnosIspred(head, broj2);
			continue;
		case'd':
			Brisanje(head, 1);
			continue;
		default:
			printf("Krivo slovo\n");
			continue;
		}

	}
}

pozicija stvori() {
	pozicija NoviBroj;
	int broj1;
	NoviBroj = (pozicija)malloc(sizeof(osoba));

	printf("Unesi broj: ");
	scanf("%d", &broj1);
	NoviBroj->broj = broj1;

	return NoviBroj;
}
pozicija pronadizadnji(pozicija head, pozicija element) {
	while (element->next != head->next) {
		element = element->next;
	}
	return element;
}
int UnosP(pozicija head) {
	pozicija NoviBroj = stvori();
	pozicija prvi;
	pozicija zadnji;
	if (head->next == NULL) {
		prvi = NoviBroj;
		NoviBroj->next = prvi;
		head->next = NoviBroj;
	}
	else {
		zadnji = pronadizadnji(head, head->next);
		NoviBroj->next = head->next;
		head->next = NoviBroj;
		prvi = NoviBroj;
		zadnji->next = prvi;
	}

	return 0;
}
int printanje(pozicija head, pozicija element) {
	pozicija prvi = head->next;
	while (element->next != prvi) {
		printf("%d--%d\n", element->broj, element->next->broj);
		element = element->next;
	}
	printf("%d--%d\n", element->broj, element->next->broj);
	
	printf("zadnji pokazuje na %d\n", element->next->broj);

	return 0;
}
int UnosK(pozicija head) {
	pozicija NoviBroj=stvori();
	pozicija prvi;
	pozicija zadnji;
	if (head->next == NULL) {
		prvi = NoviBroj;
		NoviBroj->next = prvi;
		head->next = NoviBroj;
	}
	else {
		zadnji = pronadizadnji(head, head->next);
		NoviBroj->next = zadnji->next;
		zadnji->next = NoviBroj;
	}
	
	return 0;
}
pozicija pronadi(pozicija head, pozicija element) {
	int broj1;
	printf("Nakon kojeg broja želis unos: ");
	scanf(" %d", &broj1);


	while (element->next != head->next&& element->broj!=broj1) {
		element = element->next;
	}

	return element;
}
int UnosNakon(pozicija element) {
	pozicija NoviBroj = stvori();

		NoviBroj->next = element->next;
		element->next = NoviBroj;

		return 0;
}
int UnosIspred(pozicija head, pozicija element) {
	pozicija NoviBroj = stvori();
	pozicija zadnji;
	

	if (element==NULL) {
		zadnji = pronadizadnji(head, head->next);
		NoviBroj->next = head->next;
		head->next = NoviBroj;
		zadnji->next = NoviBroj;
	}
	else {
		NoviBroj->next = element->next;
		element->next = NoviBroj;
	}

	return 0;
}
pozicija pronadi2(pozicija head, pozicija element) {
	int broj1;
	pozicija prije=NULL;
	printf("Prije kojeg broja želis unos: ");
	scanf(" %d", &broj1);


	while (element->next != head->next && element->broj != broj1) {
		prije = element;
		element = element->next;
	}

	return prije;
}
void Brisanje(pozicija head, int A) {

	pozicija current = head->next;
	pozicija zadnji = head->next;

	while (zadnji->next != head->next) {
		zadnji = zadnji->next;
	}
	pozicija prije = zadnji;

	while (current->broj != A && current->next != head->next) {
		prije = current;
		current = current->next;
}
	if (prije == zadnji) {
		head->next = current->next;
	}
	else if (current == zadnji) {
		printf("ovo je zadnji vec");
	}
	else {
		zadnji->next = prije->next;
		prije->next = current->next;
		current->next = head->next;
	}






}