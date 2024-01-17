#include <stdio.h>

void ispis(char* p) {
	printf(" %c", *p);
	p++;
	if (*p != '\0')
		ispis(p);
}

 void main() {
	ispis("ABC");
}