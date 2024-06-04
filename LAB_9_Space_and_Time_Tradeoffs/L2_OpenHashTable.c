#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node *table[SIZE];
} HashTable;

void initializeHashTable(HashTable *hashTable) {
    for (int i = 0; i < SIZE; i++)
        hashTable->table[i] = NULL;
}

int hashFunction(int key) {
    return key % SIZE;
}

void insertKey(HashTable *hashTable, int key) {
    int index = hashFunction(key);
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = key;
    newNode->next = NULL;
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = newNode;
    } else {
        newNode->next = hashTable->table[index];
        hashTable->table[index] = newNode;
    }
}

Node *searchKey(HashTable *hashTable, int key) {
    int index = hashFunction(key);
    Node *current = hashTable->table[index];
    while (current != NULL) {
        if (current->data == key)
            return current;
        current = current->next;
    }
    return NULL;
}

int countKeyComparisons(HashTable *hashTable, int key, int *successfulComparisons, int *unsuccessfulComparisons) {
    Node *result = searchKey(hashTable, key);
    if (result != NULL)
        (*successfulComparisons)++;
    else
        (*unsuccessfulComparisons)++;
}

int main() {
    HashTable hashTable;
    initializeHashTable(&hashTable);

    insertKey(&hashTable, 5);
    insertKey(&hashTable, 15);
    insertKey(&hashTable, 25);

    int successfulComparisons = 0, unsuccessfulComparisons = 0;
    countKeyComparisons(&hashTable, 5, &successfulComparisons, &unsuccessfulComparisons);
    countKeyComparisons(&hashTable, 15, &successfulComparisons, &unsuccessfulComparisons);
    countKeyComparisons(&hashTable, 30, &successfulComparisons, &unsuccessfulComparisons);

    printf("Number of key comparisons for successful search: %d\n", successfulComparisons);
    printf("Number of key comparisons for unsuccessful search: %d\n", unsuccessfulComparisons);

    return 0;
}
