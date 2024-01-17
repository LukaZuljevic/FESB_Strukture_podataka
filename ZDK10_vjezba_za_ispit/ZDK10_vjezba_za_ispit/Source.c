#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 30
struct _grad;
typedef struct _grad* pozicijaT;
typedef struct _grad {
	pozicijaT next;
	pozicijaT left;
	pozicijaT right;
	char ime[MAX];
	int populacija;

}grad;

struct _drzava;
typedef struct _drzava* pozicijaD;
typedef struct _drzava {
	pozicijaD next;
	pozicijaD left;
	pozicijaD right;
	char ime[MAX];
	grad headT;
	pozicijaT rootT;
	

}drzava;


int readFile(pozicijaD headD);
pozicijaD StvoriNovuDrzavu(char* imedrzave);
pozicijaT StvoriNoviGrad(char* imegrada, int populacija);
int StvoriNovuDrzavuSaGradovima(imedrzave, imefile);
pozicijaT StabloGradova(pozicijaT NoviGrad, pozicijaT rootT);
int printanjeDrzavaUListi(pozicijaD headD);
int NapraviListuDrzava(pozicijaD headT, pozicijaD NovaDrzava);

int main() {

	drzava headD = { .next = NULL, .left = NULL, .right = NULL, .ime = {0} , .headT = 
		           {.next = NULL, .left = NULL, .right = NULL, .ime = {0} , .populacija = 0}, .rootT=NULL };
	
	readFile(&headD);

	printanjeDrzavaUListi(&headD);



	return 0; 
}

int readFile(pozicijaD headD) {

	FILE* doc=NULL;
	doc = fopen("Text.txt", "r");

	if (!doc) {
		printf("greska");
		return -1;
	}

	char imedrzave[MAX] = {0};
	char imefile[MAX] = {0};

	while (!feof(doc)) {
		fscanf(doc, " %s %s", imedrzave, imefile);

		StvoriNovuDrzavuSaGradovima(imedrzave, imefile);
		
	}


	fclose(doc);

return 0;
}

int StvoriNovuDrzavuSaGradovima(char* imedrzave,char* imefile) {
	pozicijaD NovaDrzava;
	pozicijaT NoviGrad;
	FILE* doc1=NULL;
	char ime2file[MAX] = { 0 };
	strcpy(ime2file, imefile);
	doc1 = fopen("hrvatska.txt", "r");
	int populacija=0;
	char imegrada[MAX] = { 0 };

	if (!doc1) {
		printf("greska 2");
		return -1;
	}
	NovaDrzava=StvoriNovuDrzavu(imedrzave);


	while (!feof(doc1)) {
		fscanf(doc1, " %s %d", imegrada, &populacija);
		NoviGrad=StvoriNoviGrad(imegrada, populacija);
		NapraviListuDrzava(&NovaDrzava->headT, NovaDrzava);
		NovaDrzava->rootT = StabloGradova(NoviGrad, NovaDrzava->rootT);
	}



	fclose(doc1);

	return 0;
}
int NapraviListuDrzava(pozicijaD headT, pozicijaD NovaDrzava) {
	pozicijaD currentD = headT;
	while (currentD->next != NULL && strcmp(currentD->next->ime, currentD->ime) < 0) {
		currentD = currentD->next;
	}

	NovaDrzava->next = currentD->next;
	currentD->next = NovaDrzava;

	return 0;
}
pozicijaD StvoriNovuDrzavu(char* imedrzave) {
	pozicijaD NovaDrzava;

	NovaDrzava = (pozicijaD)malloc(sizeof(drzava));

	NovaDrzava->left = NULL;
	NovaDrzava->right = NULL;
	NovaDrzava->next = NULL;
	NovaDrzava->rootT = NULL;
	strcpy(NovaDrzava->ime, imedrzave);
	NovaDrzava->headT.populacija = 0;
	NovaDrzava->headT.next = NULL;
	NovaDrzava->headT.left = NULL;
	NovaDrzava->headT.right = NULL;

	return NovaDrzava;

}
pozicijaT StvoriNoviGrad(char* imegrada,int populacija){
	pozicijaT NoviGrad;

	NoviGrad = (pozicijaT)malloc(sizeof(grad));

	NoviGrad->next = NULL;
	NoviGrad->left = NULL;
	NoviGrad->right = NULL;
	NoviGrad->populacija = populacija;
	strcpy(NoviGrad->ime, imegrada);

	return NoviGrad;
}
pozicijaT StabloGradova(pozicijaT NoviGrad,pozicijaT rootT) {

	if (rootT == NULL) {
		return NoviGrad;
	}
	if (NoviGrad->populacija > rootT->populacija) {
		rootT->left = StabloGradova(NoviGrad, rootT->left);
	}
	else if (NoviGrad->populacija < rootT->populacija) {
		rootT->right = StabloGradova(NoviGrad, rootT->right);
	}

	return rootT;
}
int printanjeDrzavaUListi(pozicijaD headD) {
	pozicijaD currentD = headD->next;
	while (currentD != NULL) {
		printf("\n%s", currentD->ime);
		printanjeStablaGradova(currentD->rootT);
		currentD = currentD->next;
	}

}
int printanjeStablaGradova(pozicijaT rootT) {

	while (rootT) {
		printanjeStablaGradova(rootT->left);
		printf("\n\t%s %d", rootT->ime, rootT->populacija);
		printanjeStablaGradova(rootT->right);
	}
	return 0;
}

