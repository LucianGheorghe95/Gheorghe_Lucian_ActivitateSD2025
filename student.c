#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definim structura Student
struct Student {
    int id;
    char* nume;
    float medie;
    int anStudiu;
};

//asta e o functie care citeste un student de la tastatura
struct Student citireStudentDeLaTastatura() {
    struct Student s;
    char buffer[100];

    printf("Introdu id-ul studentului: ");
    scanf("%d", &s.id);
    getchar();

    printf("Introdu numele studentului: ");
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    s.nume = (char*)malloc(strlen(buffer) + 1);
    strcpy(s.nume, buffer);

    printf("Introdu media genarala: ");
    scanf("%f", &s.medie);

    printf("Introdu anul de studiu: ");
    scanf("%d", &s.anStudiu);

    return s;
}

int main() {

    return 0;
}