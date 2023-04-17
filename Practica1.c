#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "leer.h"
#include <unistd.h>
// Definición de la estructura de datos para almacenar la información de tiempos de viaje

//create a function called ingresar origen that receives a pointer to a struct travel_time_data and wait for input, verifies if the input is between 1 and 1160, if it is, it saves the input on the struct, else it prints an error message
void ingresar_origen(travel_time_data* v){
    int origen;
    printf("Ingrese el origen: \n");
    scanf("%d", &origen);
    if(origen >= 1 && origen <= 1160){
        v->sourceid = origen;
    }
    else{
        printf("El origen debe estar entre 1 y 1160\n");
    }
}
//create a function called ingresar destino that receives a pointer to a struct travel_time_data and wait for input, verifies if the input is between 1 and 1160, if it is, it saves the input on the struct, else it prints an error message
void ingresar_destino(travel_time_data* v){
    int destino;
    printf("Ingrese el destino: \n");
    scanf("%d", &destino);
    if(destino >= 1 && destino <= 1160){
        v->dstid = destino;
    }
    else{
        printf("El destino debe estar entre 1 y 1160\n");
    }
}
//create a function called ingresar hora that receives a pointer to a struct travel_time_data and wait for input, verifies if the input is between 0 and 23, if it is, it saves the input on the struct, else it prints an error message
void ingresar_hora(travel_time_data* v){
    int hora;
    printf("Ingrese la hora: \n");
    scanf("%d", &hora);
    if(hora >= 0 && hora <= 23){
        v->hod = hora;
    }
    else{
        printf("La hora debe estar entre 0 y 23\n");
    }}

int main() {
    
    //create a if statement that verifies if the file hash.bin exist if it does, it calls hashDocument function with parameters datos.csv, hash.bin and 1160, else it calls hashDocument function with parameters datos.csv, hash.bin and 1160
    if (access("tabla_hash.bin", F_OK) == -1) {
        char *args[] = {"hashDocument", "datos.csv", "tabla_hash.bin", NULL};
        int argc = sizeof(args) / sizeof(char *) - 1;
        hashDocument(argc, args);
        //print 'document hashed'
        printf("Document hashed\n");

    }
    // Menú de opciones
    int option = 0;
    int sourceid = 0;
    int dstid = 0;
    int hod = 0;
    float mean_travel_time = 0.0;
    travel_time_data viaje;

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
             ingresar_origen(&viaje);
                break;
            case 2:

                ingresar_destino(&viaje);
                break;
            case 3:

                ingresar_hora(&viaje);
                break;
            case 4:
                //use the search function in the leer.h using the pointer to viaje
                char *args[] = {"datos.csv", "tabla_hash.bin"};
                search(2, args, viaje);
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


