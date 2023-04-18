#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "leer.h"
#include <unistd.h>
// Definición de la estructura de datos para almacenar la información de tiempos de viaje

//create a function called ingresar origen that receives a pointer to a integer and wait for input,verifies if the input is between 1 and 1160, the input is saved on the integer else it prints an error message
void ingresar_origen(int* sourceid) {
    int input;
    printf("Ingrese el origen:");
    scanf("%d", &input);
    if (input >= 1 && input <= 1160) {
        *sourceid = input; // save input to the integer pointed by ptr
    } else {
        printf("Error: el valor ingresado no está entre 1 y 1160.\n");
    }
}
//create a function called ingresar destino that receives a pointer to a integer and wait for input,verifies if the input is between 1 and 1160, the input is saved on the integer else it prints an error message
void ingresar_destino(int* dstid) {
    int input;
    printf("Ingrese el destino:");
    scanf("%d", &input);
    if (input >= 1 && input <= 1160) {
        *dstid = input; // save input to the integer pointed by ptr
    } else {
        printf("Error: el valor ingresado no está entre 1 y 1160.\n");
    }
}
//create a function called ingresar hora that receives a pointer to a integer and wait for input,verifies if the input is between 0 and 23, the input is saved on the integer else it prints an error message
void ingresar_hora(int* hod) {
    int input;
    printf("Ingrese la hora:");
    scanf("%d", &input);
    if (input >= 0 && input <= 23) {
        *hod = input; // save input to the integer pointed by ptr
    } else {
        printf("Error: el valor ingresado no está entre 0 y 23.\n");
    }
}

int main() {
    
    //create a if statement that verifies if the file hash.bin exist if it does, it calls hashDocument function with parameters datos.csv, hash.bin and 1160, else it calls hashDocument function with parameters datos.csv, hash.bin and 1160
    hashDocument();
    //print document hashed
    printf("Document hashed\n");

    // Menú de opciones
    int option = 0;
    int sourceid = 0;
    int dstid = 0;
    int hod = 0;
    float mean_travel_time = 0.0;

    //declare a pointer to v
    while (option != 5) {
        printf("Bienvenido\n");
        printf("1. Ingresar origen\n");
        printf("2. Ingresar destino\n");
        printf("3. Ingresar hora\n");
        printf("4. Buscar tiempo de viaje medio\n");
        printf("5. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &option);
    switch (option) {
            case 1:
             ingresar_origen(&sourceid);
                break;
            case 2:

                ingresar_destino(&dstid);
                break;
            case 3:

                ingresar_hora(&hod);
                break;
            case 4:
                // Buscar tiempo de viaje medio usando la funcion search de la libreria hash
                search(sourceid, dstid, hod);
                break;
            case 5:
                // Salir del programa
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Por favor ingrese una opcion valida.\n");
                break;
        }
    }
}
//create a function called ingresar origen that receives a pointer to a struct travel_time_data and wait for input, the input is saved on the struct


