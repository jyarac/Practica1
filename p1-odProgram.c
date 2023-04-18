#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Definición de la estructura de datos para almacenar la información de tiempos de viaje

//create a function called ingresar origen that receives a pointer to a integer and wait for input,verifies if the input is between 1 and 1160, the input is saved on the integer else it prints an error message
void ingresar_origen(int* sourceid) {
    int input;
    printf("Ingrese ID del origen:");
    scanf("%d", &input);
    if (input >= 1 && input <= 1160) {
        *sourceid = input; // save input #include <unistd.h>

    } else {
        printf("Error: el valor ingresado no está entre 1 y 1160.\n");
    }
}
//create a function called ingresar destino that receives a pointer to a integer and wait for input,verifies if the input is between 1 and 1160, the input is saved on the integer else it prints an error message
void ingresar_destino(int* dstid) {
    int input;
    printf("Ingrese ID del destino:");
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
    printf("Ingrese hora del dia:");
    scanf("%d", &input);
    if (input >= 0 && input <= 23) {
        *hod = input; // save input to the integer pointed by ptr
    } else {
        printf("Error: el valor ingresado no está entre 0 y 23.\n");
    }
}
// Función para enviar datos a través del pipe
void enviar_datos(int fd[], int sourceid, int dstid, int hod) {
    write(fd[1], &sourceid, sizeof(sourceid));
    write(fd[1], &dstid, sizeof(dstid));
    write(fd[1], &hod, sizeof(hod));
}

// Función para recibir datos a través del pipe
void recibir_datos(int fd[], int *sourceid, int *dstid, int *hod) {
    read(fd[0], sourceid, sizeof(*sourceid));
    read(fd[0], dstid, sizeof(*dstid));
    read(fd[0], hod, sizeof(*hod));
}

int main() {
    
    //create a if statement that verifies if the file hash.bin exist if it does, it calls hashDocument function with parameters datos.csv, hash.bin and 1160, else it calls hashDocument function with parameters datos.csv, hash.bin and 1160
    hashDocument();
    //print document hashed
    printf("Document hashed\n");

    // Creación de proceso hijo
    pid_t pid;
    int fd1[2]; // pipe de recepcion de datos para el proceso hijo
    int sourceid = 0;
    int dstid = 0;
    int hod = 0;
    float mean_travel_time = 0.0;
    int option = 0;

    

    // Creación del pipe
    if (pipe(fd1) == -1) {
        perror("Error en la creación del pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("Error en la creación del proceso hijo");
        exit(EXIT_FAILURE);
        } 

    else if (pid == 0) {
        // Proceso hijo: búsqueda y lectura
        close(fd1[1]); // Cerrar descriptor de escritura del pipe
        while (1) {
            recibir_datos(fd1, &sourceid, &dstid, &hod);
            search(sourceid, dstid, hod);
            }
    } else{
        //proceso padre
    close(fd1[0]);
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
            //use the function enviar datos
                enviar_datos(fd1, sourceid, dstid, hod);
                break;             
            case 5:

                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Por favor ingrese una opcion valida.\n");
                break;
        }
    }
    }
}
//create a function called ingresar origen that receives a pointer to a struct travel_time_data and wait for input, the input is saved on the struct


