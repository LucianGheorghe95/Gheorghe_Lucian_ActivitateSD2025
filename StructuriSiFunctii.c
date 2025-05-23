/*#define _CRT_SECURE_NO_WARNINGS
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

int main() {
    struct LaptopGaming laptop = citireLaptopDeLaTastatura();
    afisareLaptop(laptop);

 // modificare model de laptop
    modificaModelLaptop(&laptop, "Asus TUF gaming");
    printf("\nDupa modificarea modelului:\n");
    afisareLaptop(laptop);

    dezalocareLaptop(&laptop);

    return 0;
}

*/