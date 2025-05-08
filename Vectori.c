/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definim structura LaptopGaming
struct LaptopGaming {
    int id;
    char* model;
    int memorieRam;           // in GB
    float frecventaProcesor;  // in GHz
};

// functie care citeste un laptop de la tastatura
struct LaptopGaming citireLaptopDeLaTastatura() {
    struct LaptopGaming laptop;
    char buffer[100];

    printf("Introdu id-ul laptopului: ");
    scanf("%d", &laptop.id);
    getchar();

    printf("Introdu modelul laptopului: ");
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    laptop.model = (char*)malloc(strlen(buffer) + 1);
    strcpy(laptop.model, buffer);

    printf("Introdu memoria RAM (GB): ");
    scanf("%d", &laptop.memorieRam);

    printf("Introdu frecventa procesorului (GHz): ");
    scanf("%f", &laptop.frecventaProcesor);

    return laptop;
}

// functie care calculeaza frecventa in MHz
float calculeazaFrecventaMHz(struct LaptopGaming l) {
    return l.frecventaProcesor * 1000;
}

// functie care afiseaza un laptop
void afisareLaptop(struct LaptopGaming l) {
    printf("\n- Laptop Gaming -\n");
    printf("ID: %d\n", l.id);
    printf("Model: %s\n", l.model);
    printf("Memorie RAM: %d GB\n", l.memorieRam);
    printf("Frecventa procesor: %.2f GHz (%.0f MHz)\n", l.frecventaProcesor, calculeazaFrecventaMHz(l));
}

// functie care afiseaza un vector de laptopuri
void afisareVectorLaptopuri(struct LaptopGaming* vector, int dim) {
    for (int i = 0; i < dim; i++) {
        afisareLaptop(vector[i]);
    }
}

// functie care elibereaza memoria unui laptop
void dezalocareLaptop(struct LaptopGaming* l) {
    free(l->model);
    l->model = NULL;
}

// functie care filtreaza laptopurile cu minim 16 GB RAM
struct LaptopGaming* filtreazaLaptopuriCuRamMare(struct LaptopGaming* vector, int dim, int* dimNoua) {
    *dimNoua = 0;

    for (int i = 0; i < dim; i++) {
        if (vector[i].memorieRam >= 16) {
            (*dimNoua)++;
        }
    }

    struct LaptopGaming* vectorNou = (struct LaptopGaming*)malloc((*dimNoua) * sizeof(struct LaptopGaming));
    int k = 0;
    for (int i = 0; i < dim; i++) {
        if (vector[i].memorieRam >= 16) {
            vectorNou[k].id = vector[i].id;
            vectorNou[k].memorieRam = vector[i].memorieRam;
            vectorNou[k].frecventaProcesor = vector[i].frecventaProcesor;
            vectorNou[k].model = (char*)malloc(strlen(vector[i].model) + 1);
            strcpy(vectorNou[k].model, vector[i].model);
            k++;
        }
    }

    return vectorNou;
}

struct LaptopGaming* mutaLaptopuriFrecventaMica(struct LaptopGaming* vector, int dim, int* dimNoua) {
    *dimNoua = 0;

    for (int i = 0; i < dim; i++) {
        if (vector[i].frecventaProcesor < 2.5f) {
            (*dimNoua)++;
        }
    }

    //functie care muta laptopurile cu frecventa < 2.5 ghz
    struct LaptopGaming* vectorNou = (struct LaptopGaming*)malloc((*dimNoua) * sizeof(struct LaptopGaming));
    int k = 0;
    for (int i = 0; i < dim; i++) {
        if (vector[i].frecventaProcesor < 2.5f) {
            vectorNou[k].id = vector[i].id;
            vectorNou[k].memorieRam = vector[i].memorieRam;
            vectorNou[k].frecventaProcesor = vector[i].frecventaProcesor;

            vectorNou[k].model = (char*)malloc(strlen(vector[i].model) + 1);
            strcpy(vectorNou[k].model, vector[i].model);

            k++;
        }
    }

    return vectorNou;
}

//functie care concateneaza doi vectori de laptopuri
struct LaptopGaming* concateneazaVectori(struct LaptopGaming* v1, int dim1, struct LaptopGaming* v2, int dim2, int* dimRezultat) {
    *dimRezultat = dim1 + dim2;
    struct LaptopGaming* vectorNou = (struct LaptopGaming*)malloc((*dimRezultat) * sizeof(struct LaptopGaming));

    int k = 0;
    // copiem din primul vector
    for (int i = 0; i < dim1; i++) {
        vectorNou[k].id = v1[i].id;
        vectorNou[k].memorieRam = v1[i].memorieRam;
        vectorNou[k].frecventaProcesor = v1[i].frecventaProcesor;
        vectorNou[k].model = (char*)malloc(strlen(v1[i].model) + 1);
        strcpy(vectorNou[k].model, v1[i].model);
        k++;
    }

    // copiem din al doilea vector
    for (int i = 0; i < dim2; i++) {
        vectorNou[k].id = v2[i].id;
        vectorNou[k].memorieRam = v2[i].memorieRam;
        vectorNou[k].frecventaProcesor = v2[i].frecventaProcesor;
        vectorNou[k].model = (char*)malloc(strlen(v2[i].model) + 1);
        strcpy(vectorNou[k].model, v2[i].model);
        k++;
    }

    return vectorNou;
}

int main() {
    int nrLaptopuri = 5;
    struct LaptopGaming* laptopuri = (struct LaptopGaming*)malloc(nrLaptopuri * sizeof(struct LaptopGaming));

    printf("Introdu informatii pentru 5 laptopuri:\n");
    for (int i = 0; i < nrLaptopuri; i++) {
        printf("\nLaptop %d:\n", i + 1);
        laptopuri[i] = citireLaptopDeLaTastatura();
    }

    printf("\n- Toate laptopurile introduse -\n");
    afisareVectorLaptopuri(laptopuri, nrLaptopuri);

    int nrLaptopuriFiltrate = 0;
    struct LaptopGaming* laptopuriRamMare = filtreazaLaptopuriCuRamMare(laptopuri, nrLaptopuri, &nrLaptopuriFiltrate);

    printf("\n- Laptopuri cu cel putin 16 GB RAM -\n");
    afisareVectorLaptopuri(laptopuriRamMare, nrLaptopuriFiltrate);
    
    
    // concatenam cele doua rezultate filtrate
    int dimVectorConcatenat = 0;
    struct LaptopGaming* vectorConcatenat = concateneazaVectori(laptopuriRamMare, nrLaptopuriFiltrate,
        laptopuriFrecventaMica, nrLaptopuriFrecventaMica,
        &dimVectorConcatenat);

    printf("\n- vector concatenat RAM >= 16 GB + frecventa < 2.5 ghz -\n");
    afisareVectorLaptopuri(vectorConcatenat, dimVectorConcatenat);

    // mutare inainte de eliberare, ca sa fie valid vectorul
    int nrLaptopuriFrecventaMica = 0;
    struct LaptopGaming* laptopuriFrecventaMica = mutaLaptopuriFrecventaMica(laptopuri, nrLaptopuri, &nrLaptopuriFrecventaMica);

    printf("\n- Laptopuri cu frecventa procesor mai mica de 2.5 GHz -\n");
    afisareVectorLaptopuri(laptopuriFrecventaMica, nrLaptopuriFrecventaMica);

    //dezalocare vectori
    for (int i = 0; i < nrLaptopuri; i++) {
        dezalocareLaptop(&laptopuri[i]);
    }
    free(laptopuri);

    for (int i = 0; i < nrLaptopuriFiltrate; i++) {
        dezalocareLaptop(&laptopuriRamMare[i]);
    }
    free(laptopuriRamMare);

    for (int i = 0; i < nrLaptopuriFrecventaMica; i++) {
        dezalocareLaptop(&laptopuriFrecventaMica[i]);
    }
    free(laptopuriFrecventaMica);

    for (int i = 0; i < dimVectorConcatenat; i++) {
        dezalocareLaptop(&vectorConcatenat[i]);
    }
    free(vectorConcatenat);

    return 0;
}

*/