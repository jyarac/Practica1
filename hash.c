#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 5024
#define HASH_SIZE 1160

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

int main(int argc, char *argv[]) {
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
