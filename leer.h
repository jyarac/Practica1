#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int sourceid;
    int dstid;
    int hod;
    float mean_travel_time;
    float standard_deviation_travel_time;
    float geometric_mean_travel_time;
    float geometric_standard_deviation_travel_time;
} travel_time_data;
// Definición de la estructura de un nodo
typedef struct Nodo_L {
    int sourceid;
    int dstid;
    int hod;
    float mean_travel_time;
    struct Nodo_L* siguiente;
} Nodo_L;

// Definición de la estructura de la tabla hash
typedef struct HashTable {
    int tamano;
    Nodo_L** tabla;
} HashTable;

// Función hash para calcular el índice
int funcion_hash(int sourceid, int dstid, int hod, int tamano) {
    return (((sourceid * 31) ^ dstid) * 17 ^ hod) % tamano;
}

// Función para crear un nuevo nodo
Nodo_L* crear_nodo_L(int sourceid, int dstid, int hod, float mean_travel_time) {
    Nodo_L* nodo = (Nodo_L*)malloc(sizeof(Nodo_L));
    nodo->sourceid = sourceid;
    nodo->dstid = dstid;
    nodo->hod = hod;
    nodo->mean_travel_time = mean_travel_time;
    nodo->siguiente = NULL;
    return nodo;
}

// Función para insertar un nodo en la tabla hash
void insertar(HashTable* tabla, int sourceid, int dstid, int hod, float mean_travel_time) {
    // Calcular el índice de la tabla hash
    int indice = funcion_hash(sourceid, dstid, hod, tabla->tamano);

    // Crear un nuevo nodo
    Nodo_L* nodo = crear_nodo_L(sourceid, dstid, hod, mean_travel_time);

    // Insertar el nodo en la tabla hash
    if (tabla->tabla[indice] == NULL) {
        tabla->tabla[indice] = nodo;
    } else {
        Nodo_L* actual = tabla->tabla[indice];
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nodo;
    }
}

// Función para buscar un nodo en la tabla hash
Nodo_L* buscar(HashTable* tabla, int sourceid, int dstid, int hod) {
    // Calcular el índice de la tabla hash
    int indice = funcion_hash(sourceid, dstid, hod, tabla->tamano);

    // Buscar el nodo en la tabla hash
    Nodo_L* actual = tabla->tabla[indice];
    while (actual != NULL) {
        if (actual->sourceid == sourceid && actual->dstid == dstid && actual->hod == hod) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

// Función para buscar un nodo en el archivo binario
Nodo_L* buscar_binario(FILE* binario, int sourceid, int dstid, int hod) {
    // Buscar el nodo en el archivo binario
    Nodo_L* nodo = (Nodo_L*)malloc(sizeof(Nodo_L));
    while (fread(nodo, sizeof(Nodo_L), 1, binario) != 0) {
        if (nodo->sourceid == sourceid && nodo->dstid == dstid && nodo->hod == hod) {
            return nodo;
        }
    }
    free(nodo);
    return NULL;
}






float search(int sourceid, int dstid, int hod) {
    // Abrir el archivo binario para lectura
    FILE* binario = fopen("binario.bin", "rb");
    if (binario == NULL) {
        printf("Error al abrir el archivo binario\n");
        return 1;
    }

    // Pedir al usuario que ingrese los valores de sourceid, dstid y hod

    // Buscar el nodo en el archivo binario
    Nodo_L* nodo = buscar_binario(binario, sourceid, dstid, hod);
    if (nodo == NULL) {
        printf("No se encontró el nodo en el archivo binario\n");
    } else {
        printf("Mean travel time: %f\n", nodo->mean_travel_time);
    }

    // Cerrar el archivo
    fclose(binario);

    return 0;
}

