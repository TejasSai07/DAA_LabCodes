#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

typedef struct {
    int key;
    bool occupied;
} HashTableEntry;

void initializeHashTable(HashTableEntry *hashTable, int size) {
    for (int i = 0; i < size; i++) {
        hashTable[i].key = -1;
        hashTable[i].occupied = false;
    }
}

int hashFunction(int key) {
    return key % SIZE;
}

void insertKey(HashTableEntry *hashTable, int key) {
    int index = hashFunction(key);
    int i = 0;
    while (hashTable[(index + i) % SIZE].occupied) {
        i++;
    }
    hashTable[(index + i) % SIZE].key = key;
    hashTable[(index + i) % SIZE].occupied = true;
}

bool searchKey(HashTableEntry *hashTable, int key) {
    int index = hashFunction(key);
    int i = 0;
    while (hashTable[(index + i) % SIZE].occupied) {
        if (hashTable[(index + i) % SIZE].key == key)
            return true;
        i++;
    }
    return false;
}

int main() {
    HashTableEntry hashTable[SIZE];
    initializeHashTable(hashTable, SIZE);

    insertKey(hashTable, 5);
    insertKey(hashTable, 15);
    insertKey(hashTable, 25);

    printf("Key 5 found in the hash table: %s\n", searchKey(hashTable, 5) ? "Yes" : "No");
    printf("Key 15 found in the hash table: %s\n", searchKey(hashTable, 15) ? "Yes" : "No");
    printf("Key 30 found in the hash table: %s\n", searchKey(hashTable, 30) ? "Yes" : "No");

    return 0;
