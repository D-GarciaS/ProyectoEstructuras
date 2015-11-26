
#include <stdlib.h>
#include "HashTable.h"

struct strHash {
    int capacity;
    int size;
    List *l_array;
    hashcodeFunc hashcode;
    equalsFunc comparison;
};

HashTable hashtable_create(int capacity, hashcodeFunc hc, equalsFunc eq) {
    HashTable new_hash;
    int i;
    new_hash = (HashTable) malloc(sizeof (struct strHash));
    new_hash->size = 0;
/*
    new_hash->l_array = (List*) malloc(sizeof (List) * capacity);
    for (i = 0; i < capacity; i++) {
        new_hash->l_array[i] = list_create();
    }
*/
    new_hash->capacity = capacity;
    new_hash->comparison = eq;
    new_hash->hashcode = hc;
}

void hashtable_destroy(HashTable ht) {
    if (ht == NULL)
        return;
    int i = 0;
    for (i = 0; i < ht->capacity; i++) {
        if (ht->l_array[i] != NULL)
            list_destroy(ht->l_array[i]);
    }
    free(ht);
}

int hashtable_size(HashTable ht) {
    return ht->size;
}

