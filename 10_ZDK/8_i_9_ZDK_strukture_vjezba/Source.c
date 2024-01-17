#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 30

struct _grad;
typedef struct _grad* pozicijaG;
typedef struct _grad {
	char ime[MAX];
	int ID;
	pozicijaG left;
	pozicijaG right;
}grad;

struct _drzava;
typedef struct _drzava* pozicijaD;
typedef struct _drzava {
	pozicijaD next;
	char ime[MAX];
	int ID;
	pozicijaG root;
}Drzava;



int UnosSort(pozicijaD NovaDrzava, pozicijaD headD);
int printanjeDrzava(pozicijaD headD);
pozicijaD stvoriDrzavu(char* imeDrzave, int ID);
pozicijaG stvoriGrad(char* imeGrada, int ID2);
int PoveziGradIDrzavu(pozicijaG NoviGrad, pozicijaD headD);
pozicijaG NapraviStablo(pozicijaG NoviGrad, pozicijaG currentDroot);



int main() {
	Drzava headD = { .next = NULL, .ime = {0}, .ID = 0, .root = NULL };
	
	//citanje drzava i stvaranje vezane liste za drzave
	char imeDrzave[MAX];
	int ID;
	pozicijaD NovaDrzava;

	FILE* doc1 = fopen("drzave.txt", "r");
	
	if (!doc1) {
		printf("erorr");
		return -1;
	}

	while (!feof(doc1)) {
		fscanf(doc1, " %s %d", imeDrzave, &ID);
		NovaDrzava=stvoriDrzavu(imeDrzave, ID);
		UnosSort(NovaDrzava, &headD);
	}
	fclose(doc1);

	//citanje gradova i stavaranje stabla za gradove
	char imeGrada[MAX];
	int ID2;
	pozicijaG NoviGrad;

	FILE* doc2 = fopen("gradovi.txt", "r");

	if (!doc1) {
		printf("erorr22");
		return -1;
	}
	while (!feof(doc2)) {
		fscanf(doc2, "%s %d", imeGrada, &ID2);
		NoviGrad=stvoriGrad(imeGrada, ID2);
		PoveziGradIDrzavu(NoviGrad, &headD);
	
	}

	pozicijaD currentD = &headD.next;

	while (currentD->next != NULL) {
		printf("%s\n", currentD->ime);
		PrintanjeGradova(currentD->root);
		currentD = currentD->next;
	}



	return 0;
}


pozicijaD stvoriDrzavu(char* imeDrzave, int ID) {
	pozicijaD NovaDrzava;

	NovaDrzava = (pozicijaD)malloc(sizeof(Drzava));

	strcpy(NovaDrzava->ime, imeDrzave);
	NovaDrzava->ID = ID;
	NovaDrzava->next = NULL;
	NovaDrzava->root = NULL;

	return NovaDrzava;
}
int printanjeDrzava(pozicijaD headD) {
	pozicijaD currentD = headD->next;

	while (currentD!= NULL) {
		printf("%s %d\n", currentD->ime, currentD->ID);
		currentD = currentD->next;
	}


	return 0;
}
int UnosSort(pozicijaD NovaDrzava, pozicijaD headD) {
	pozicijaD current = headD;
	while (current->next != NULL && strcmp(current->next->ime, NovaDrzava->ime) < 0) {
		current = current->next;
	}
	NovaDrzava->next = current->next;
	current->next = NovaDrzava;

	return 0;
}
pozicijaG stvoriGrad(char* imeGrada, int ID2) {

	pozicijaG NoviGrad;

	NoviGrad = (pozicijaG)malloc(sizeof(grad));

	strcpy(NoviGrad->ime, imeGrada);
	NoviGrad->ID = ID2;
	NoviGrad->right = NULL;
	NoviGrad->left = NULL;

	return NoviGrad;
}
int PoveziGradIDrzavu(pozicijaG NoviGrad, pozicijaD headD) {
	pozicijaD currentD = headD->next;

	while (currentD->next != NULL && currentD->ID != NoviGrad->ID ) {
		currentD = currentD->next;
	}

	currentD->root = NapraviStablo(NoviGrad, currentD->root);
	


	return 0;
}
pozicijaG NapraviStablo(pozicijaG NoviGrad, pozicijaG currentDroot) {
	if (currentDroot == NULL) {
		return NoviGrad;
	}
	if (strcmp(NoviGrad->ime, currentDroot->ime) < 0) {
		currentDroot->left = NapraviStablo(NoviGrad, currentDroot->left);
	}
	else if (strcmp(NoviGrad->ime, currentDroot->ime) > 0) {
		currentDroot->right = NapraviStablo(NoviGrad, currentDroot->right);

	}

	return currentDroot;
}
int PrintanjeGradova(pozicijaG root) {
	if (root) {
		PrintanjeGradova(root->left);
		printf("\t%s\n", root->ime);
		PrintanjeGradova(root->right);
	}
}

