#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10 // Tamaño de la tabla hash

// Estructura para los nodos de la tabla hash
struct Node {
    char key[100]; // Clave
    int value;     // Valor asociado
    struct Node* next; // Puntero al siguiente nodo
};

// Función para crear un nuevo nodo
struct Node* createNode(const char* key, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strncpy(newNode->key, key, sizeof(newNode->key));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Función hash para calcular el índice de la clave en la tabla
int hash(const char* key) {
    int sum = 0;
    for (int i = 0; i < strlen(key); i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

// Función para insertar un par clave-valor en la tabla hash
void insert(struct Node* hashTable[], const char* key, int value) {
    int index = hash(key);
    struct Node* newNode = createNode(key, value);
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        struct Node* current = hashTable[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Función para buscar el valor asociado a una clave en la tabla hash
int search(struct Node* hashTable[], const char* key) {
    int index = hash(key);
    struct Node* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Si la clave no se encuentra en la tabla
}
