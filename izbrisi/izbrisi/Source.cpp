#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MAX_BODOVI 5



typedef struct {

    char ime[20];
    char prezime[20];
    int bodovi;
    double relativni;


}Student1;


void ispis(Student1* student, int n) {
    int i = 0;

    for (i = 0; i < n; i++)
    {
        printf("%s %s %d %.2lfposto \n", student[i].ime, student[i].prezime, student[i].bodovi, student[i].relativni * 100);
    }

}
void relativni(Student1* student, int n) {
    int i;

    for (i = 0; i < n; i++)
    {
        student[i].relativni = (double)student[i].bodovi / MAX_BODOVI;
    }

}



int main() {
    Student1* student;
    FILE* test = NULL;
    int i;
    int n = 1;


    test = fopen("C:\\Users\\Luka\\Desktop\\program.txt", "r");

     if (test == NULL)
    {
        printf("Error!!!");
        exit(1);
    }


     while (!feof(test))
    {
        if (fgetc(test) == '\n')
        {
            n++;
        }
    }

    rewind(test);

    student = malloc(n * sizeof(Student1));

    for (i = 0; i < n; i++)
    {
        fscanf(test, "%s\n", student[i].ime);
        fscanf(test, "%s\n", student[i].prezime);
        fscanf(test, "%d\n", &student[i].bodovi);

    }

    relativni(student, n);

    ispis(student, n);

    printf("radi sve");

    fclose(test);


    return 0;
}