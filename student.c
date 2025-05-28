/*
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


// functie care afiseaza un student
void afisareStudent(struct Student s) {
    printf("\nStudent:\n");
    printf("ID: %d\n", s.id);
    printf("Nume: %s\n", s.nume);
    printf("Medie: %.2f\n", s.medie);
    printf("An de studiu: %d\n", s.anStudiu);
}

//functie care afiseaza studentul cu stele in functie de medie
void afisareGraficStudent(struct Student s) {
    printf("\n%s: ", s.nume);
    int nrStele = (int)(s.medie + 0.5f); 
    for (int i = 0; i < nrStele; i++) {
        printf("*");
    }
    printf(" (%.2f)\n", s.medie);
}

//dezalocarememoria alocata pentru un student
void dezalocareStudent(struct Student* s) {
    free(s->nume);
    s->nume = NULL;
}

// functie ce salveaza studentii in fisier
void salvareStudentiInFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "w");
    if (!f) {
        perror("eroare la deschiderea fisierului");
        return;
    }

    struct Student studenti[5] = {
        {1, "AnaPopescu", 9.5, 2},
        {2, "IonIonescu", 8.3, 1},
        {3, "MariaStan", 7.9, 3},
        {4, "GeorgeEnescu", 6.5, 2},
        {5, "AndreiVasile", 9.8, 1}
    };

    for (int i = 0; i < 5; i++) {
        fprintf(f, "%d %s %.2f %d\n", studenti[i].id, studenti[i].nume, studenti[i].medie, studenti[i].anStudiu);
    }

    fclose(f);
}

// functie care citeste studentii din fisier si ii returneaza intr-un vector
struct Student* citesteStudentiDinFisier(const char* numeFisier, int* dimensiune) {
    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        perror("Eroare la deschiderea fisierului");
        *dimensiune = 0;
        return NULL;
    }

    struct Student* studenti = (struct Student*)malloc(10 * sizeof(struct Student));
    *dimensiune = 0;
    char buffer[100];

    while (!feof(f)) {
        struct Student s;
        if (fscanf(f, "%d %s %f %d", &s.id, buffer, &s.medie, &s.anStudiu) == 4) {
            s.nume = (char*)malloc(strlen(buffer) + 1);
            strcpy(s.nume, buffer);
            studenti[*dimensiune] = s;
            (*dimensiune)++;
        }
    }

    fclose(f);
    return studenti;
}

// functie ce filtreaza studentii cu media peste o valare data
struct Student* filtreazaStudentiDupaMedie(struct Student* vector, int dim, int* dimNoua, float prag) {
    *dimNoua = 0;

    
    for (int i = 0; i < dim; i++) {  
        if (vector[i].medie > prag) {
            (*dimNoua)++;
        }
    }

    
    struct Student* rezultat = (struct Student*)malloc((*dimNoua) * sizeof(struct Student));
    int k = 0;
    for (int i = 0; i < dim; i++) {
        if (vector[i].medie > prag) {
            rezultat[k].id = vector[i].id;
            rezultat[k].medie = vector[i].medie;
            rezultat[k].anStudiu = vector[i].anStudiu;

            rezultat[k].nume = (char*)malloc(strlen(vector[i].nume) + 1);
            strcpy(rezultat[k].nume, vector[i].nume);
            k++;
        }
    }

    return rezultat;
}



//functie care cauta un student dupa id si il afiseaza daca exista
void cautaStudentDupaId(struct Student* vector, int dim, int idCautat) {
    for (int i = 0; i < dim; i++) {
        if (vector[i].id == idCautat) {
            printf("\nStudent gasit:\n");
            afisareStudent(vector[i]);
            return;
        }
    }
    printf("\nNu exista student cu id-ul %d.\n", idCautat);
}

//functie care sorteaza vectorul de studenti descrescator dupa medie
void sorteazaStudentiDupaMedie(struct Student* vector, int dim) {
    for (int i = 0; i < dim - 1; i++) {
        for (int j = i + 1; j < dim; j++) {
            if (vector[i].medie < vector[j].medie) {
                struct Student temp = vector[i];
                vector[i] = vector[j];
                vector[j] = temp;
            }
        }
    }
}


int main() {

  //salvam studentii in fisier
    salvareStudentiInFisier("studenti.txt");

              //citim din fisier
    int nrStudenti = 0;
    struct Student* studenti = citesteStudentiDinFisier("studenti.txt", &nrStudenti);

  //afisam toti studentii cititi
    printf("\nStudenti cititi din fisier:\n");
    for (int i = 0; i < nrStudenti; i++) {
        afisareStudent(studenti[i]);
    }

    printf("\n--- Reprezentare grafica a mediilor studentilor ---\n");
    for (int i = 0; i < nrStudenti; i++) {
        afisareGraficStudent(studenti[i]);
    }


   //citim un student de la tastatura
    struct Student s = citireStudentDeLaTastatura();
    afisareStudent(s);

    // sortam studentii dupa medie
    sorteazaStudentiDupaMedie(studenti, nrStudenti);
    printf("\n--- Studentii sortati descrescator dupa medie ---\n");
    for (int i = 0; i < nrStudenti; i++) {
        afisareStudent(studenti[i]);
    }


    //dezalocam memoria
    for (int i = 0; i < nrStudenti; i++) {
        dezalocareStudent(&studenti[i]);
    }
    free(studenti);

    dezalocareStudent(&s);

    int idCautat;
    printf("\nIntrodu ID-ul studentului pe care vrei sa-l cauti: ");
    scanf("%d", &idCautat);
    cautaStudentDupaId(studenti, nrStudenti, idCautat);

    return 0;
}

*/