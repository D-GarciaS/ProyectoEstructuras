
#include <stdlib.h>
#include "HashTable.h"

struct strHash {
    int capacity;
    int size;
    List *l_array;
    hashcodeFunc hashcodeF;
    equalsFunc comparison;
};

struct strHtEntry {
    Type key;
    Type Value;
};

typedef struct strHtEntry* HtEntry;

HashTable hashtable_create(int capacity, hashcodeFunc hc, equalsFunc eq) {
    HashTable new_hash;
    int i;
    new_hash = (HashTable) malloc(sizeof (struct strHash));
    new_hash->size = 0;
        new_hash->l_array = (List*) malloc(sizeof (List) * capacity);
/*
        for (i = 0; i < capacity; i++) {
            new_hash->l_array[i] = list_create();
        }
*/
    new_hash->capacity = capacity;
    new_hash->comparison = eq;
    new_hash->hashcodeF = hc;
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

void hashtable_put(HashTable ht, Type key, Type value) {
    int hashcode;
    if (key == NULL || ht == NULL) //clave o ht vacia
        return;
    hashcode = ht->hashcodeF(key);
    if (hashcode > ht->capacity) {
        hashcode = hashcode % ht->capacity; //aritmética modular si clave > capacidad
    }
    int i = hashcode;
    int comp;
    int flag = 0;
    HtEntry nueva;

    Iterator it;
    if (ht->l_array[i] == NULL) { // si aun no existe la lista la crea
        ht->l_array[i] = list_create();
        nueva = (HtEntry) malloc(sizeof (struct strHtEntry));
        nueva->Value = value;
        nueva->key = key;
        list_add(ht->l_array[i], nueva); // y agrega la nueva entrada
    } else { //si ya existia la lista
        it = list_begin(ht->l_array[i]);
        while (list_hasNext(it)) { //la recorre para ver si ya existe la key
            list_next(it);
            comp = ht->comparison(list_data(it), key);
            if (comp == 0) { //si ya existía remplaza el valor
                ((HtEntry) (list_data(it)))->Value = value;
                flag = 1;
            }
        }
        if (flag = 0) { //si recorrió y no encontro la clave debemos agregarla
            nueva = (HtEntry) malloc(sizeof (struct strHtEntry));
            nueva->Value = value;
            nueva->key = key;
            list_add(ht->l_array[i], nueva);
        }
    }
}
