#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//OVAJ KOD FUNKCIONIRA SKROZ I KORZ NJEGA PONOVI DVOSTRUKO VEZANE LISTE!!!!!!!!!!
//
//
//
struct _broj;
typedef struct _broj* pozicija;
typedef struct _broj{
	int broj;
	pozicija next;
	pozicija prev;
}element;
pozicija PronadiPrije(pozicija head, pozicija element);
pozicija Pronadi(pozicija element);
pozicija stvori();
pozicija PronadiZadnji(pozicija head);
pozicija PronadiPredZadnji(pozicija head);
int menu(pozicija head);
int UnosP(pozicija head);
int UnosK(pozicija head);
int printanje(pozicija element);
int BrisanjeListe(pozicija head);
int BrisanjeOdZadnjeg(pozicija head);
int UnesiIspred(pozicija head,pozicija element);
int UnesiNakon(pozicija element);
int BrisanjeElementa(pozicija head, pozicija element);


int main() {

	element head = { .broj = 0, .next = NULL, .prev= NULL };

	menu(&head);

	return 0;
}

int menu(pozicija head) {
	char znak;
	pozicija broj1=NULL;
	pozicija broj2=NULL;
	pozicija broj3 = NULL;

	while (1) {
		printf("a-pocetak\nb-kraj\np-printanje\nl-brisanje liste\nz-bris od zadnjeg\ne-unesi nakon\nq-unesi ispred\nd-bris elementa\n------------\n");
		scanf(" %c", &znak);
		switch (znak) {
		case'a':
			UnosP(head);
			continue;
		case'b':
			UnosK(head);
			continue;
		case'p':
			printanje(head->next);
			continue;
		case'l':
			BrisanjeListe(head);
			continue;
		case'z':
			BrisanjeOdZadnjeg(head);
			continue;
		case'd':
			broj3 = Pronadi(head->next);
			BrisanjeElementa(head, broj3);
			continue;
		case'q':
			broj1 = PronadiPrije(head, head->next);
			UnesiIspred(head, broj1);
			continue;
		case'e':
			broj2 = Pronadi(head->next);
			UnesiNakon(broj2);
			continue;
		case'x':
			break;
		default:
			printf("Unia si krivo slovo");
			continue;
		}
		break;
	}
	return 0;
}
pozicija Pronadi(pozicija element) {
	int broj = 0;

	printf("Unsi trazeni broj: ");
	scanf(" %d", &broj);

	while (element->broj != broj) {
		element = element->next;
	}
	return element;

}
pozicija PronadiPrije(pozicija head, pozicija element) {
	pozicija Broj=NULL;
	int broj = 0;

	printf("Unsi trazeni broj: ");
	scanf(" %d", &broj);
	if (element == NULL) {
		return head;
	}
	while (element->broj != broj) {
		Broj = element;
		element = element->next;
	}
	return Broj;
}
pozicija PronadiZadnji(pozicija head) {
	pozicija zadnji=head;
	//Ode pripazi da incijaliziras na head pa u uvjet stavis zadnji->next!!!!
	while (zadnji->next) {
		zadnji = zadnji->next;
	}
	return zadnji;
}
pozicija PronadiPredZadnji(pozicija head) {
	pozicija zadnji = head;
	pozicija predzadnji=NULL;
	while (zadnji->next) {
		predzadnji = zadnji;
		zadnji = zadnji->next;
	}
	return predzadnji;

}
pozicija stvori() {
	pozicija NoviBroj;
	int broj = 0;

	NoviBroj = (pozicija)malloc(sizeof(element));

	printf("Unesi novi broj: ");
	scanf(" %d", &broj);

	NoviBroj->broj = broj;

	return NoviBroj;
}
int UnosP(pozicija head) {
	pozicija NoviBroj = NULL;
	NoviBroj = stvori();

	NoviBroj->next = head->next;
	head->next = NoviBroj;
	NoviBroj->prev = head;
	if (NoviBroj->next != NULL) {
		NoviBroj->next->prev = NoviBroj;
	}
	return 0;

}
int UnosK(pozicija head) {
	pozicija NoviBroj = NULL;
	pozicija zadnji=NULL;
	zadnji = PronadiZadnji(head);
	NoviBroj = stvori();

	NoviBroj->next = zadnji->next;
	zadnji->next = NoviBroj;
	NoviBroj->prev = zadnji;

	return 0;
}
int printanje(pozicija element) {
	while (element) {
		printf("%d-%d\n", element->broj, element->prev->broj);
		element = element->next;
	}
	return 0;
}
int BrisanjeListe(pozicija head) {
	pozicija temp = NULL;

	while (head->next) {
		temp = head->next;
		head->next=temp->next;
		free(temp);
	}
	

	return 0;
}
int UnesiIspred(pozicija head, pozicija element) {
	pozicija NoviBroj;
	NoviBroj = stvori();

	if (element == NULL) {
		NoviBroj->next = head->next;
		head->next = NoviBroj;
		NoviBroj->prev = head;
		NoviBroj->next->prev = NoviBroj;

	}
	else {
		NoviBroj->next = element->next;
		element->next = NoviBroj;
		NoviBroj->prev = element;
		NoviBroj->next->prev = NoviBroj;
	}

	return 0;
}
int UnesiNakon(pozicija element) {
	pozicija NoviBroj;
	NoviBroj = stvori();

	NoviBroj->next = element->next;
	element->next = NoviBroj;
	NoviBroj->prev = element;
	if (NoviBroj->next != NULL) {
		NoviBroj->next->prev = NoviBroj;
	}
}
int BrisanjeOdZadnjeg(pozicija head) {
	pozicija temp = NULL;
	pozicija zadnji;
	while (head->next) {
		zadnji = PronadiPredZadnji(head);
		temp = zadnji->next;
		zadnji->next = temp->next;
		free(temp);
	}
	return 0;
}
int BrisanjeElementa(pozicija head, pozicija element) {
	pozicija temp = NULL;
	//ode je krivo nesto(neznan kako prev od iduceg spojit na prosli od izbrisanog!!!!
	if (element->next != NULL) {
		element->next->prev = element->prev;
		element->prev->next = element->next;
		free(element);
	}
	else { 
		element->prev->next = NULL;
		free(element); }
	return 0;

}












