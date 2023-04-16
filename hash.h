#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 5024
#define HASH_SIZE 116000
typedef struct{
    int sourceid;
    int dstid;
    int hod;
    float mean_travel_time;
    float standard_deviation_travel_time;
    float geometric_mean_travel_time;
    float geometric_standard_deviation_travel_time;
} travel_time_data;

typedef struct {
    int sourceid;
    int dstid;
    int hod;
    double mean_travel_time;
} travel_data;

typedef struct {
    int key;
    travel_data value;
} hash_node;

typedef struct {
    int count;
    hash_node nodes[HASH_SIZE];
} hash_table;

int hash_function(int key) {
    return key % HASH_SIZE;
}

//Funciones de la antigua libreria leer

void load_table(hash_table *table, char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    fread(table, sizeof(hash_table), 1, fp);

    fclose(fp);
}
travel_data *findl(hash_table *table, int sourceid, int dstid, int hod) {
    int key = sourceid * HASH_SIZE + dstid;
    int index = hash_function(key);
    int i = index;
    do {
        if (table->nodes[i].key == 0) {
            return NULL;
        }
        if (table->nodes[i].key == key &&
            table->nodes[i].value.sourceid == sourceid &&
            table->nodes[i].value.dstid == dstid &&
            table->nodes[i].value.hod == hod) {
            return &table->nodes[i].value;
        }
        i = (i + 1) % HASH_SIZE;
    } while (i != index);
    return NULL;
}
int search(int argc, char *argv[], travel_time_data travel) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input_file = argv[1];

    hash_table table = {0};
    load_table(&table, input_file);

    travel_data *data = findl(&table, travel.sourceid, travel.dstid, travel.hod);
    if (data != NULL) {
        printf("mean_travel_time = %.2f\n", data->mean_travel_time);
    } else {
        printf("NA\n");
    }

    return EXIT_SUCCESS;
}


//funciones de libreria hash-


void insert(hash_table *table, int key, travel_data value) {
    int index = hash_function(key);
    int i = index;
    do {
        if (table->nodes[i].key == 0) {
            table->nodes[i].key = key;
            table->nodes[i].value = value;
            table->count++;
            return;
        }
        if (table->nodes[i].key == key) {
            table->nodes[i].value = value;
            return;
        }
        i = (i + 1) % HASH_SIZE;
    } while (i != index);
}

travel_data *find(hash_table *table, int key) {
    int index = hash_function(key);
    int i = index;
    do {
        if (table->nodes[i].key == 0) {
            return NULL;
        }
        if (table->nodes[i].key == key) {
            return &table->nodes[i].value;
        }
        i = (i + 1) % HASH_SIZE;
    } while (i != index);
    return NULL;
}

void load_data(hash_table *table, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        char *token;
        int sourceid, dstid, hod;
        double mean_travel_time;

        token = strtok(line, ",");
        sourceid = atoi(token);

        token = strtok(NULL, ",");
        dstid = atoi(token);

        token = strtok(NULL, ",");
        hod = atoi(token);

        token = strtok(NULL, ",");
        mean_travel_time = atof(token);

        travel_data data = {sourceid, dstid, hod, mean_travel_time};
        insert(table, sourceid * HASH_SIZE + dstid, data);
    }

    fclose(fp);
}
void save_table(hash_table *table, char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    fwrite(table, sizeof(hash_table), 1, fp);

    fclose(fp);
}

int hashDocument(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input_file = argv[1];
    char *output_file = argv[2];

    hash_table table = {0};
    load_data(&table, input_file);
    save_table(&table, output_file);

    return EXIT_SUCCESS;
}
