#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

struct HashTable {
    int data[TABLE_SIZE];
    int isOccupied[TABLE_SIZE];
};

void initialize(struct HashTable *hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->data[i] = -1;
        hashTable->isOccupied[i] = 0;
    }
}

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void insert(struct HashTable *hashTable, int value) {
    int index = hashFunction(value);
    while (hashTable->isOccupied[index]) {
        index = (index + 1) % TABLE_SIZE;
    }
    hashTable->data[index] = value;
    hashTable->isOccupied[index] = 1;
}

int search(struct HashTable *hashTable, int value) {
    int index = hashFunction(value);
    while (hashTable->isOccupied[index]) {
        if (hashTable->data[index] == value) {
            return index;
        }
        index = (index + 1) % TABLE_SIZE;
    }
    return -1;  // Value not found
}

void display(struct HashTable *hashTable) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable->isOccupied[i]) {
            printf("%d -> %d\n", i, hashTable->data[i]);
        } else {
            printf("%d -> Empty\n", i);
        }
    }
}

int main() {
    struct HashTable hashTable;
    initialize(&hashTable);

    insert(&hashTable, 15);
    insert(&hashTable, 25);
    insert(&hashTable, 35);
    insert(&hashTable, 45);

    display(&hashTable);

    int key = 25;
    int index = search(&hashTable, key);
    if (index != -1) {
        printf("%d found at index %d.\n", key, index);
    } else {
        printf("%d not found.\n", key);
    }

    return 0;
}

