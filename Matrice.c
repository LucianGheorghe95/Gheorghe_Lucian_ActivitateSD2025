/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// definim structura LaptopGaming
struct LaptopGaming {
    int id;
    char* model;    // acest atribut l-am alocat dinamic
    int memorieRam;    // in gigabites
    float frecventaProcesor; // acesta este in ghz
};


// asta este functia care citeste un laptop de la tastatura  si il returnaza
struct LaptopGaming citireLaptopDeLaTastatura() {
    struct LaptopGaming laptop;
    char buffer[100];

    printf("Introdu id-ul laptopului: ");
    scanf("%d", &laptop.id);
    getchar();

    printf("Introdu modelul laptop-ului: ");
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    laptop.model = (char*)malloc(strlen(buffer) + 1); //alocarea dinamica pentru model de laptop
    strcpy(laptop.model, buffer);

    printf("Introdu memoria RAM ( in GB): ");
    scanf("%d", &laptop.memorieRam);

    printf("Introdu frecventa procesorului (in ghz): ");
    scanf("%f", &laptop.frecventaProcesor);

    return laptop;
}

//functie care calculeaza frecventa procesorului in mhz
float calculeazaFrecventaMHz(struct LaptopGaming l) {
    return l.frecventaProcesor * 1000;
}


//functie care afiseaza toate informatiile despre un laptop
void afisareLaptop(struct LaptopGaming l) {
    printf("\n Laptop Gaming:\n");
    printf("iD: %d\n", l.id);
    printf("model: %s\n", l.model);
    printf("memorie RAM: %d GB\n", l.memorieRam);
    printf("frecventa procesor: %.2f GHz (%.0f MHz)\n", l.frecventaProcesor, calculeazaFrecventaMHz(l));
}

// functie de elibeare a memoria alocata dinamic
void dezalocareLaptop(struct LaptopGaming* l) {
    free(l->model);
    l->model = NULL;
}

// functie care modifica modelul unui laptop
void modificaModelLaptop(struct LaptopGaming* l, const char* modelNou) {
    free(l->model);
    l->model = (char*)malloc(strlen(modelNou) + 1);
    strcpy(l->model, modelNou);
}


void salvareLaptopuriInFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "w");
    if (!f) {
        perror("eroare cand ai deschis fisierul");
        return;
    }

    struct LaptopGaming laptopuri[10] = {
        {1, "Predator", 16, 2.8},
        {2, "Legion", 32, 3.2},
        {3, "tuf", 8, 2.3},
        {4, "rog", 16, 2.9},
        {5, "aspire", 12, 2.0},
        {6, "alienware", 64, 3.8},
        {7, "msi", 16, 2.5},
        {8, "hp", 24, 3.0},
        {9, "thibkpad", 8, 1.8},
        {10, "dell G5", 16, 2.6}
    };

    for (int i = 0; i < 10; i++) {
        fprintf(f, "%d %s %d %.2f\n", laptopuri[i].id, laptopuri[i].model, laptopuri[i].memorieRam, laptopuri[i].frecventaProcesor);
    }

    fclose(f);
    printf("laptopurile au fost salvate in fisierul %s\n", numeFisier);
}

struct LaptopGaming* citesteLaptopuriDinFisier(const char* numeFisier, int* dimensiune) {
    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        perror("eroare la deschiderea fisierului");
        *dimensiune = 0;
        return NULL;
    }

    struct LaptopGaming* laptopuri = (struct LaptopGaming*)malloc(10 * sizeof(struct LaptopGaming));
    *dimensiune = 0;

    while (!feof(f)) {
        struct LaptopGaming l;
        char buffer[100];

        if (fscanf(f, "%d %s %d %f", &l.id, buffer, &l.memorieRam, &l.frecventaProcesor) == 4) {
            l.model = (char*)malloc(strlen(buffer) + 1);
            strcpy(l.model, buffer);
            laptopuri[*dimensiune] = l;
            (*dimensiune)++;
        }
    }

    fclose(f);
    return laptopuri;
}

e o matrice de laptopuri grupate dupa RAM
struct LaptopGaming** creeazaMatriceDupaRam(struct LaptopGaming* vector, int dim, int* nrLinii, int** dimensiuniLinii) {
    int maxRam = 0;

    for (int i = 0; i < dim; i++) {
        if (vector[i].memorieRam > maxRam) {
            maxRam = vector[i].memorieRam;
        }
    }

    *nrLinii = maxRam / 8 + 1;
    struct LaptopGaming** matrice = (struct LaptopGaming**)malloc((*nrLinii) * sizeof(struct LaptopGaming*));
    *dimensiuniLinii = (int*)calloc(*nrLinii, sizeof(int));
    int* contor = (int*)calloc(*nrLinii, sizeof(int));

    for (int i = 0; i < dim; i++) {
        int linie = vector[i].memorieRam / 8;
        (*dimensiuniLinii)[linie]++;
    }

    for (int i = 0; i < *nrLinii; i++) {
        matrice[i] = (struct LaptopGaming*)malloc((*dimensiuniLinii)[i] * sizeof(struct LaptopGaming));
    }

    for (int i = 0; i < dim; i++) {
        int linie = vector[i].memorieRam / 8;
        int poz = contor[linie];

        matrice[linie][poz].id = vector[i].id;
        matrice[linie][poz].memorieRam = vector[i].memorieRam;
        matrice[linie][poz].frecventaProcesor = vector[i].frecventaProcesor;
        matrice[linie][poz].model = (char*)malloc(strlen(vector[i].model) + 1);
        strcpy(matrice[linie][poz].model, vector[i].model);

        contor[linie]++;
    }

    free(contor);
    return matrice;
}

// functie care afiseaza matricea de laptopuri
void afiseazaMatriceLaptopuri(struct LaptopGaming** matrice, int nrLinii, int* dimensiuniLinii) {
    for (int i = 0; i < nrLinii; i++) {
        printf("\n--- Linia %d (RAM = %d GB) ---\n", i, i * 8);
        for (int j = 0; j < dimensiuniLinii[i]; j++) {
            afisareLaptop(matrice[i][j]);
        }
    }
}

int main() {
    // salvam in fisier 10 laptopuri
    salvareLaptopuriInFisier("laptopuri.txt");

    // citire din fisier in vector
    int nrLaptopuriCitite = 0;
    struct LaptopGaming* vectorCitit = citesteLaptopuriDinFisier("laptopuri.txt", &nrLaptopuriCitite);

    printf("\nLaptopuri citite din fisier:\n");
    for (int i = 0; i < nrLaptopuriCitite; i++) {
        afisareLaptop(vectorCitit[i]);
    }

    // creare matrice grupata dupa RAM
    int nrLinii = 0;
    int* dimensiuniLinii = NULL;
    struct LaptopGaming** matrice = creeazaMatriceDupaRam(vectorCitit, nrLaptopuriCitite, &nrLinii, &dimensiuniLinii);

    sorteazaLiniileDupaNumarElemente(&matrice, dimensiuniLinii, nrLinii);

    // afisare matrice
    printf("\n--- Afisare matrice grupata dupa RAM ---\n");
    afiseazaMatriceLaptopuri(matrice, nrLinii, dimensiuniLinii);

    // citire, modificare si afisare laptop individual
    struct LaptopGaming laptop = citireLaptopDeLaTastatura();
    afisareLaptop(laptop);

    modificaModelLaptop(&laptop, "asus TUF gaming");
    printf("\ndupa modificarea modelului:\n");
    afisareLaptop(laptop);
    dezalocareLaptop(&laptop);

    // dezalocare pentru matrice
    for (int i = 0; i < nrLinii; i++) {
        for (int j = 0; j < dimensiuniLinii[i]; j++) {
            dezalocareLaptop(&matrice[i][j]);
        }
        free(matrice[i]);
    }
    free(matrice);
    free(dimensiuniLinii);

    // abia acum e safe sa dezalocam vectorul
    for (int i = 0; i < nrLaptopuriCitite; i++) {
        dezalocareLaptop(&vectorCitit[i]);
    }
    free(vectorCitit);

    return 0;
}


*/