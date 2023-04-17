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
typedef struct Nodo {
    int sourceid;
    int dstid;
    int hod;
    float mean_travel_time;
} Nodo;

// Función para crear un nuevo nodo
Nodo* crear_nodo(int sourceid, int dstid, int hod, float mean_travel_time) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->sourceid = sourceid;
    nodo->dstid = dstid;
    nodo->hod = hod;
    nodo->mean_travel_time = mean_travel_time;
    return nodo;
}

// Función principal
int main() {
    // Leer el archivo CSV
    FILE* archivo = fopen("datos.csv", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    // Abrir el archivo binario para escritura
    FILE* archivo_binario = fopen("binario.bin", "wb");
    if (archivo_binario == NULL) {
        printf("Error al abrir el archivo binario\n");
        return 1;
    }

    // Leer cada línea del archivo CSV y escribirla en el archivo binario
    char linea[1024];
    while (fgets(linea, 1024, archivo)) {
        int sourceid, dstid, hod;
        float mean_travel_time;
        sscanf(linea, "%d,%d,%d,%f", &sourceid, &dstid, &hod, &mean_travel_time);
        Nodo* nodo = crear_nodo(sourceid, dstid, hod, mean_travel_time);
        fwrite(nodo, sizeof(Nodo), 1, archivo_binario);
        free(nodo);
    }

    // Cerrar los archivos
    fclose(archivo);
    fclose(archivo_binario);

    // Abrir el archivo binario para lectura
    archivo_binario = fopen("binario.bin", "rb");
    if (archivo_binario == NULL) {
        printf("Error al abrir el archivo binario\n");
        return 1;
    }

    // Buscar una relación en el archivo binario
    Nodo nodo;
    int buscado_sourceid = 620, buscado_dstid = 12, buscado_hod = 21;
    fseek(archivo_binario, 0, SEEK_SET);  // Mover el puntero al inicio del archivo
    while (fread(&nodo, sizeof(Nodo), 1, archivo_binario)) {
        if (nodo.sourceid == buscado_sourceid && nodo.dstid == buscado_dstid && nodo.hod == buscado_hod) {
            printf("Tiempo promedio desde 1 a 2 a las 10am: %f\n", nodo.mean_travel_time);
            break;
        }
    }

    // Cerrar el archivo binario
    fclose(archivo_binario);

    return 0;
}
