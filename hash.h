#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> 

#define MAX_LINE_LENGTH 5024
#define HASH_SIZE 1160
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


// Función para buscar un nodo en el archivo binario
Nodo* buscar_binario(FILE* binario, int sourceid, int dstid, int hod) {
    struct timeval inicio, fin;
    gettimeofday(&inicio, NULL);
    // Buscar el nodo en el archivo binario
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    while (fread(nodo, sizeof(Nodo), 1, binario) != 0) {
        if (nodo->sourceid == sourceid && nodo->dstid == dstid && nodo->hod == hod) {
            gettimeofday(&fin, NULL); // Obtener el tiempo de fin de la búsqueda
            double tiempo_transcurrido = (fin.tv_sec - inicio.tv_sec) + (fin.tv_usec - inicio.tv_usec) / 1000000.0; // Calcular el tiempo transcurrido en segundos
            printf("\nTiempo busar_binario transcurrido: %.6f segundos\n", tiempo_transcurrido);
            return nodo;
        }
    }
    free(nodo);
    return NULL;
}
int hashDocument(){
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
float search(int sourceid, int dstid, int hod) {
    // Obtener el tiempo de inicio
    struct timeval inicio;
    gettimeofday(&inicio, NULL);
    double tiempo_inicio = (double)inicio.tv_sec + (double)inicio.tv_usec / 1000000.0;

    // Abrir el archivo binario para lectura
    FILE* binario = fopen("binario.bin", "rb");
    if (binario == NULL) {
        printf("Error al abrir el archivo binario\n");
        return 1;
    }

    // Pedir al usuario que ingrese los valores de sourceid, dstid y hod

    // buscar el nodo en el archivo binario
    Nodo* nodo = buscar_binario(binario, sourceid, dstid, hod);
    if (nodo == NULL) {
        printf("NA\n");
        
    } else {
        printf("Tiempo de viaje medio: %f\n", nodo->mean_travel_time);
    }

    // Cerrar el archivo
    fclose(binario);

    // Obtener el tiempo de fin
    struct timeval fin;
    gettimeofday(&fin, NULL);
    double tiempo_fin = (double)fin.tv_sec + (double)fin.tv_usec / 1000000.0;

    // Calcular el tiempo transcurrido en segundos
    double tiempo_transcurrido = tiempo_fin - tiempo_inicio;

    // Imprimir el tiempo transcurrido
    printf("\nTiempo de search transcurrido: %f segundos\n", tiempo_transcurrido);

    return 0;
}
