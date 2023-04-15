#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 116000

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

void load_table(hash_table *table, char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    fread(table, sizeof(hash_table), 1, fp);

    fclose(fp);
}

travel_data *find(hash_table *table, int sourceid, int dstid, int hod) {
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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input_file = argv[1];

    hash_table table = {0};
    load_table(&table, input_file);

    int sourceid, dstid, hod;
    printf("Enter sourceid, dstid, and hod separated by spaces:\n");
    if (scanf("%d %d %d", &sourceid, &dstid, &hod) != 3) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    travel_data *data = find(&table, sourceid, dstid, hod);
    if (data != NULL) {
        printf("mean_travel_time = %.2f\n", data->mean_travel_time);
    } else {
        printf("Error: combination not found\n");
    }

    return EXIT_SUCCESS;
}
