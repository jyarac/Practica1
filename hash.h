#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura de un nodo
typedef struct Nodo {
    int sourceid;
    int dstid;
    int hod;
    float mean_travel_time;
    struct Nodo* siguiente;
} Nodo;

// Definición de la estructura de la tabla hash
typedef struct HashTable {
    int tamano;
    Nodo** tabla;
} HashTable;

// Función hash para calcular el índice
int funcion_hash(int sourceid, int dstid, int hod, int tamano) {
    return (((sourceid * 31) ^ dstid) * 17 ^ hod) % tamano;
}

// Función para crear un nuevo nodo
Nodo* crear_nodo(int sourceid, int dstid, int hod, float mean_travel_time) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
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
    Nodo* nodo = crear_nodo(sourceid, dstid, hod, mean_travel_time);

    // Insertar el nodo en la tabla hash
    if (tabla->tabla[indice] == NULL) {
        tabla->tabla[indice] = nodo;
    } else {
        Nodo* actual = tabla->tabla[indice];
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nodo;
    }
}

// Función para buscar un nodo en la tabla hash
Nodo* buscar(HashTable* tabla, int sourceid, int dstid, int hod) {
    // Calcular el índice de la tabla hash
    int indice = funcion_hash(sourceid, dstid, hod, tabla->tamano);

    // Buscar el nodo en la tabla hash
    Nodo* actual = tabla->tabla[indice];
    while (actual != NULL) {
        if (actual->sourceid == sourceid && actual->dstid == dstid && actual->hod == hod) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}


int hashDocument() {
    // Leer el archivo CSV
    FILE* archivo = fopen("datos.csv", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    // Abrir el archivo binario para escritura
    FILE* binario = fopen("binario.bin", "wb");
    if (binario == NULL) {
        printf("Error al abrir el archivo binario\n");
        return 1;
    }

    // Leer cada línea del archivo CSV y guardarla en el archivo binario
    char linea[1024];
    while (fgets(linea, 1024, archivo)) {
        int sourceid, dstid, hod;
        float mean_travel_time;
        sscanf(linea, "%d,%d,%d,%f", &sourceid, &dstid, &hod, &mean_travel_time);

        // Crear un nuevo nodo
        Nodo* nodo = crear_nodo(sourceid, dstid, hod, mean_travel_time);

        // Escribir el nodo en el archivo binario
        fwrite(nodo, sizeof(Nodo), 1, binario);

        // Liberar la memoria del nodo
        free(nodo);
    }

    // Cerrar los archivos
    fclose(archivo);
    fclose(binario);

    return 0;
}

