#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

struct _direktorij;
typedef struct _direktorij* pozicijaDirektorij;
typedef struct _direktorij {
	pozicijaDirektorij next;
	pozicijaDirektorij subDirektorij;
	char name[MAX];

}direktorij;

struct _stack;
typedef struct _stack* pozicijaStack;
typedef struct _stack {
	pozicijaStack next;
	pozicijaStack level;
}stack;

pozicijaDirektorij createDirektorij(char name[MAX]);
pozicijaDirektorij createSubDirektorij(char imeDirektorija[MAX], pozicijaDirektorij currentDirektorij);
pozicijaDirektorij changeDirektorij(char imeDirektorija[MAX], pozicijaDirektorij currentDirektorij);
int push(pozicijaStack headStack, pozicijaDirektorij currentDirektorij);
int printanje(pozicijaDirektorij currentDirektorij);
pozicijaDirektorij pop(pozicijaStack headStack);
pozicijaStack createNewStackElement(pozicijaDirektorij currentDirektorij);





int main() {

	direktorij headDirektorij = { .next = NULL, .subDirektorij = NULL, .name = {0} };
	stack headStack = { .next = NULL, .level = NULL };
	
	pozicijaDirektorij rootDirektorij = createDirektorij("C:");
	headDirektorij.next = rootDirektorij;

	pozicijaDirektorij currentDirektorij = rootDirektorij;

	char znak;
	char imeDirektorija[MAX];

	while (1) {
		printf("1 - md (Create Directory)\n2 - cd dir (Change Directory)\n3 - cd.. (Go Up)\n4 - dir (List Contents)\n5 - exit\n");
		scanf(" %c",&znak);

		switch (znak) {
		case '1':
			printf("Unesi ime novog direktorija: \n");
			scanf("%s", imeDirektorija);
			createSubDirektorij(imeDirektorija, currentDirektorij);
			continue;
		case '2':
			printf("Unesi ime direktorija u koji zelis uc: ");
			scanf("%s", imeDirektorija);
			currentDirektorij = changeDirektorij(imeDirektorija, currentDirektorij);
			push(&headStack, currentDirektorij);
			continue;
		case '3':
			if (currentDirektorij != rootDirektorij) {
				currentDirektorij = pop(&headStack);
				printf("trenutno si u: %s\n", currentDirektorij->name);
			}
		case '4':
			printanje(currentDirektorij);
		case '5': break;
		default: printf("krivi broj");
			continue;
		}
	}







	return 0;
}

pozicijaDirektorij createDirektorij(char name[MAX]) {

	pozicijaDirektorij noviDirektorij;

	noviDirektorij = (pozicijaDirektorij)malloc(sizeof(direktorij));

	strcpy(noviDirektorij->name, name);
	noviDirektorij->next = NULL;
	noviDirektorij->subDirektorij = NULL;

	return noviDirektorij;

}
pozicijaDirektorij createSubDirektorij(char imeDirektorija[MAX], pozicijaDirektorij currentDirektorij) {
	pozicijaDirektorij newDirektorij;

	newDirektorij = createDirektorij(imeDirektorija);

	newDirektorij->next = currentDirektorij->subDirektorij;
	currentDirektorij->subDirektorij = newDirektorij;


	return newDirektorij;

}
pozicijaDirektorij changeDirektorij(char imeDirektorija[MAX], pozicijaDirektorij currentDirektorij) {

	pozicijaDirektorij subdirektorij;
	subdirektorij = currentDirektorij->subDirektorij;
	while (subdirektorij != NULL) {
		if (strcmp(subdirektorij->name, imeDirektorija) == 0) {
			return subdirektorij;
		}
		subdirektorij = subdirektorij->next;
	}

	printf("taj direktorij ne postoji");
	return currentDirektorij;
}
int push(pozicijaStack headStack, pozicijaDirektorij currentDirektorij) {
	pozicijaStack NoviStackElement;

	NoviStackElement = createNewStackElement(currentDirektorij);

	NoviStackElement->next = headStack->next;
	headStack->next = NoviStackElement;
}
pozicijaDirektorij pop(pozicijaStack headStack) {
	pozicijaStack toDelete;
	pozicijaDirektorij direktorij;

		toDelete = headStack->next;

		headStack->next = toDelete->next;
		direktorij = toDelete->level;
		free(toDelete);

		return direktorij;
}
pozicijaStack createNewStackElement(pozicijaDirektorij currentDirektorij){
	pozicijaStack NoviStackElement;

	NoviStackElement = (pozicijaStack)malloc(sizeof(stack));

	NoviStackElement->level = currentDirektorij;
	NoviStackElement->next = NULL;

	return NoviStackElement;

}
int printanje(pozicijaDirektorij currentDirektorij) {
	printf("popis elemenata ovog direktorija - %s", currentDirektorij->name);

	pozicijaDirektorij subdirektorij = currentDirektorij->subDirektorij;

	while (subdirektorij != NULL) {
		printf("-%s\n", subdirektorij->name);
		subdirektorij = subdirektorij->next;

	}
	return 0;

}
