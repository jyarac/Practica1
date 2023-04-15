#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

// Definición de la estructura de datos para almacenar la información de tiempos de viaje
typedef struct{
    int sourceid;
    int dstid;
    int hod;
    float mean_travel_time;
    float standard_deviation_travel_time;
    float geometric_mean_travel_time;
    float geometric_standard_deviation_travel_time;
} travel_time_data;

// Función para leer los datos de tiempo de viaje desde un archivo csv y almacenarlos en un arreglo de estructuras de datos
travel_time_data* read_travel_times_from_csv(char* filename, int* num_records) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo %s\n", filename);
        exit(1);
    }

    // Contar el número de registros en el archivo
    char line[1024];
    int n = 0;
    while (fgets(line, 1024, fp)) {
        n++;
    }
    rewind(fp);

    // Crear un arreglo de estructuras de datos para almacenar los registros
    travel_time_data* data = (travel_time_data*)malloc(n * sizeof(travel_time_data));
    if (data == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    // Leer los datos de cada registro en el archivo y almacenarlos en el arreglo
    int i = 0;
    while (fgets(line, 1024, fp)) {
        char* tok;
        tok = strtok(line, ",");
        data[i].sourceid = atoi(tok);
        tok = strtok(NULL, ",");
        data[i].dstid = atoi(tok);
        tok = strtok(NULL, ",");
        data[i].hod = atoi(tok);
        tok = strtok(NULL, ",");
        data[i].mean_travel_time = atof(tok);
        tok = strtok(NULL, ",");
        data[i].standard_deviation_travel_time = atof(tok);
        tok = strtok(NULL, ",");
        data[i].geometric_mean_travel_time = atof(tok);
        tok = strtok(NULL, ",");
        data[i].geometric_standard_deviation_travel_time = atof(tok);
        i++;
    }

    // Actualizar el número de registros leídos
    *num_records = n;

    // Cerrar el archivo
    fclose(fp);

    // Devolver el arreglo de datos
    return data;
}
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
    }
}

int main() {

    // Leer los datos de tiempo de viaje desde el archivo csv
    int num_records = 0;
    travel_time_data* data = read_travel_times_from_csv("datos.csv", &num_records);
    //print data

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
                // Código para ingresar destino
                // ...
                ingresar_destino(&viaje);
                break;
            case 3:
                // Código para ingresar hora
                // ...
                ingresar_hora(&viaje);
                break;
            case 4:
                // Código para buscar tiempo de viaje medio
                // ...
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

//create a function called buscar tiempo de viaje medio that receives a pointer to a struct viaje and checks if sourceid, dstid and hod exists on the struct, if it does, it prints the mean travel time
/*void buscar_tiempo_viaje_medio(travel_time_data *v){
    if(v->sourceid != 0 && v->dstid != 0 && v->hod != 0){
        printf("El tiempo de viaje medio es: %f", v->mean_travel_time);
    }
    else{
        printf("No se ha ingresado origen, destino o hora");
    }



    HashTable table = { NULL, 0 };
    table.num_buckets = 1160 * 1160;
    table.buckets = (Node**) calloc(table.num_buckets, sizeof(Node*));

    read_csv("datos.csv", &table);

    int sourceid = 5;
    int dstid = 451;
    TravelData* data = lookup(&table, sourceid, dstid);
    if (data != NULL) {
        printf("Mean travel time from %d to %d:\n", sourceid, dstid);
        for (int hod = 0; hod < NUM_HOURS; hod++) {
            printf("%d: %.2f minutes\n", hod, data->mean_travel_time[hod]);
}
} else {
printf("No data found for %d -> %d\n", sourceid, dstid);
}
// Free memory
for (int i = 0; i < table.num_buckets; i++) {
    Node* node = table.buckets[i];
    while (node != NULL) {
        Node* next_node = node->next;
        free(node);
        node = next_node;
    }
}
free(table.buckets);

return 0;


}*/
