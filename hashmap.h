#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define NUM_HOURS 24

typedef struct {
    int sourceid;
    int dstid;
    float mean_travel_time[NUM_HOURS];
} TravelData;

typedef struct Node {
    TravelData data;
    struct Node* next;
} Node;

typedef struct {
    Node** buckets;
    int num_buckets;
} HashTable;

int hash(int sourceid, int dstid, int num_buckets) {
    return (sourceid * 31 + dstid) % num_buckets;
}

void insert(HashTable* table, TravelData data) {
    int bucket = hash(data.sourceid, data.dstid, table->num_buckets);
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->next = table->buckets[bucket];
    table->buckets[bucket] = node;
}

TravelData* lookup(HashTable* table, int sourceid, int dstid) {
    int bucket = hash(sourceid, dstid, table->num_buckets);
    Node* node = table->buckets[bucket];
    while (node != NULL) {
        if (node->data.sourceid == sourceid && node->data.dstid == dstid) {
            return &(node->data);
        }
        node = node->next;
    }
    return NULL;
}

void read_csv(char* filename, HashTable* table) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int line_num = 0;
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        line_num++;
        if (line_num == 1) {
            continue; // skip header row
        }

        char* sourceid_str = strtok(line, ",");
        char* dstid_str = strtok(NULL, ",");
        char* hod_str = strtok(NULL, ",");
        char* mean_travel_time_str = strtok(NULL, ",");

        int sourceid = atoi(sourceid_str);
        int dstid = atoi(dstid_str);
        int hod = atoi(hod_str);
        float mean_travel_time = atof(mean_travel_time_str);

        TravelData* data = lookup(table, sourceid, dstid);
        if (data == NULL) {
            TravelData new_data = { sourceid, dstid, { 0 } };
            insert(table, new_data);
            data = lookup(table, sourceid, dstid);
        }
        data->mean_travel_time[hod] = mean_travel_time;
    }

    fclose(file);
}

int main() {
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

return 0;}
