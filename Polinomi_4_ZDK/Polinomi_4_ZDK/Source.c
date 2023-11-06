#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _element;
typedef struct _element* pozicija;
typedef struct _element {
	int koef;
	int exp;
	pozicija next;
}Element;

int read_file(pozicija headpoly1, pozicija headpoly2);
int printanje(pozicija element1, pozicija element2, pozicija headzbrajanje, pozicija headmnozenje);
pozicija stvori();
int sortiranje(pozicija element, pozicija novielement);
int zbrajanje(pozicija element1, pozicija element2, pozicija element3);
int mnozenje(pozicija element1, pozicija element2, pozicija element3);

int main() {
	Element headpoly1 = { .koef = 0, .exp = 0, .next = NULL };
	Element headpoly2 = { .koef = 0, .exp = 0, .next = NULL };
	Element headzbrajanje = { .koef = 0, .exp = 0, .next = NULL };
	Element headmnozenje = { .koef = 0, .exp = 0, .next = NULL };

	read_file(&headpoly1, &headpoly2);
	zbrajanje(headpoly1.next, headpoly2.next, &headzbrajanje);
	mnozenje(headpoly1.next, headpoly2.next, &headmnozenje);
	printanje(headpoly1.next, headpoly2.next, headzbrajanje.next, headmnozenje.next);
	
	return 0;
}
int read_file(pozicija headpoly1, pozicija headpoly2) {
	pozicija current1;
	pozicija current2;
	int poly1koef;
	int poly1exp;
	char znak='0';
	int poly2koef;
	int poly2exp;
	FILE* str;
	str = fopen("C:\\Users\\Luka\\Desktop\\Polinomi.txt", "r");

	if (str == NULL) {
		printf("error");
	}

	while (znak!='\n') {
		current1 = stvori();
		fscanf(str, "%dx^%d", &poly1koef, &poly1exp);
		znak = fgetc(str);
		current1->koef = poly1koef;
		current1->exp = poly1exp;
		sortiranje(headpoly1, current1);
	}
	while (feof(str)==0) {
		current2 = stvori();
		fscanf(str, "%dx^%d", &poly2koef, &poly2exp);
		current2->koef = poly2koef;
		current2->exp = poly2exp;
		sortiranje(headpoly2, current2);
	}

	fclose(str);
	return 0;
}
int printanje(pozicija element1, pozicija element2, pozicija element3, pozicija element4) {

	pozicija current1 = element1;
	pozicija current2 = element2;
	pozicija current3 = element3;

	while (current1) {
		printf("%dx^%d ", current1->koef, current1->exp);

		current1 = current1->next;
	}
	printf("\n");
	while (current2) {
		printf("%dx^%d ", current2->koef, current2->exp);

		current2 = current2->next;
	}
	printf("\n");
	while (current3) {
		printf("%dx^%d ", current3->koef, current3->exp);

		current3 = current3->next;
	}
	printf("\n");
	while (element4) {
		printf("%dx^%d ", element4->koef, element4->exp);

		element4 = element4->next;
	}
	return 0;
}
pozicija stvori() {
	pozicija Broj;

	Broj = (pozicija)malloc(sizeof(Element));

	Broj->next = NULL;
	Broj->exp = 0;
	Broj->koef = 0;

	return Broj;
}
int sortiranje(pozicija element, pozicija novielement) {
	
	while (element->next != NULL && element->next->exp < novielement->exp) {
			element = element->next;
	}
	novielement->next = element->next;
	element->next = novielement;


	return 0;
}
int zbrajanje(pozicija element1, pozicija element2, pozicija headzbrajanje) {
	pozicija current=NULL;

	while (element1!= NULL&&element2!=NULL) {
		if (element1->exp == element2->exp) {
			current = stvori();
			current->exp = element1->exp;
			current->koef = element1->koef + element2->koef;
			current->next = headzbrajanje->next;
			headzbrajanje->next = current;

			element1 = element1->next;
			element2 = element2->next;
			headzbrajanje = headzbrajanje->next;
		}
		else if (element1->exp < element2->exp) {
			current = stvori();
			current->exp = element1->exp;
			current->koef = element1->koef;

			current->next = headzbrajanje->next;
			headzbrajanje->next = current;

			element1 = element1->next;
			headzbrajanje = headzbrajanje->next;
		}
		else {
			current = stvori();
			current->exp = element2->exp;
			current->koef = element2->koef;

			current->next = headzbrajanje->next;
			headzbrajanje->next = current;

			element2 = element2->next;
			headzbrajanje = headzbrajanje->next;
		}

		
	}
	return 0;
}
int mnozenje(pozicija element1, pozicija element2, pozicija headmnozenje) {
	pozicija current=NULL;
	pozicija currentpoly1=element1;
	pozicija currentpoly2 = element2;
	if (element1 != NULL || element2 != NULL) {
		for (currentpoly1; currentpoly1 != NULL; currentpoly1 = currentpoly1->next) {
			for (currentpoly2; currentpoly2 != NULL; currentpoly2 = currentpoly2->next) {
				current = stvori();
				current->exp = currentpoly1->exp + currentpoly2->exp;
				current->koef = currentpoly1->koef * currentpoly2->koef;

				current->next = headmnozenje-> next;
				headmnozenje->next = current;
				
			}
		}
	}

	return 0;
}

