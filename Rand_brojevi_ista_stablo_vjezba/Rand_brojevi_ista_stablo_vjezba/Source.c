#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>


struct _broj;
typedef struct _broj* pozicija;
typedef struct _broj {
	pozicija next;
	int broj;
}broj;
pozicija SNoviBroj();
int random();
double MinIMaks(pozicija head);
int Premjestanje(double srednja, pozicija head);


int main() {
	broj head = { .next = NULL, .broj = 0 };
	pozicija NoviBroj=NULL;
	pozicija current1=NULL;
	int i;
	int j = 15;
	double srednja;
	//Upisivanje novog broj i porvjera duplih
	for (i = 0; i < j; i++) {
		NoviBroj = NULL;
		NoviBroj = SNoviBroj();
		NoviBroj->broj = random();
		

		if (head.next != NULL) {
			current1 = head.next;
		}
		if (head.next == NULL) {
			NoviBroj->next = head.next;
			head.next = NoviBroj;
		}
		while (i>0&&current1!= NULL) {
			if (NoviBroj->broj == current1->broj) {
				++i;
				j += 2;
				break;
			}
			current1 = current1->next;
		}if (i>0&&current1 == NULL) {
			NoviBroj->next = head.next;
			head.next = NoviBroj;
		}
	}




	//printanje
	pozicija current = head.next;
	while (current != NULL) {
		printf("%d ", current->broj); 		
		current = current->next;
	}
	printf("\n");

	//pronalazenje MinIMaks i racunanje srednje
	srednja=MinIMaks(&head);

	Premjestanje(srednja, &head);

	return 0;
}

int random() {
	return (rand() % (120-100+1)) + 100;
}
pozicija SNoviBroj() {
	pozicija NoviBroj;

	NoviBroj = (pozicija)malloc(sizeof(broj));

	NoviBroj->next = NULL;
	NoviBroj->broj = 0;

	return NoviBroj;
}
double MinIMaks(pozicija head) {

	
	pozicija current = head->next;
	int min=current->broj;
	int max=current->broj;
	double srednja;

	while (current != NULL) {

		if (max < current->broj) {
			max = current->broj;
		}
		if (min > current->broj) {
			min = current->broj;
		}

		current = current->next;
	}

	srednja = (double)((min + max) / 2);

	


	return srednja;
}
int Premjestanje(double srednja, pozicija head) {
	pozicija zadnji=NULL;
	pozicija current = head->next;
	pozicija current2 = head->next;
	pozicija prije = head;
	pozicija current3 = head->next;

	while (current->next != NULL) {
		current = current->next;
		zadnji = current;
	}
	current = head->next;
	
	while (current != NULL) {

		if (current->broj > srednja) {
			prije->next = current2->next;
			current2->next = zadnji->next;
			zadnji->next = current2;
			
		}
		prije = current;
		current = current->next;
		
	}
	pozicija currrent = head->next;

	while (currrent != NULL) {
		printf("%d ", currrent->broj);
		currrent = currrent->next;
	}
	
	

	return 0;
}
