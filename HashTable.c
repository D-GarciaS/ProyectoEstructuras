
#include <stdlib.h>
#include "HashTable.h"

struct strHash {
    int capacity;
    int size;
    List *l_array;
    hashcodeFunc hashcodeF;
    equalsFunc isKeyEqual;
};

struct strHtEntry {
    Type Key;
    Type Value;
};

typedef struct strHtEntry* HtEntry;

Type retrieveValueFromIterator(Iterator ite){
    return ((HtEntry) (list_data(ite)))->Value;
}

Type retrieveKeyFromIterator(Iterator ite){
    return ((HtEntry) (list_data(ite)))->Key;
}

void setEntryValue(Iterator ite, Type val){
    ((HtEntry) (list_data(ite)))->Value = val; 
}

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
    new_hash->isKeyEqual = eq;
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
    int iguales;
    int flag = 0;
    HtEntry nueva;

    Iterator it;
    if (ht->l_array[i] == NULL) { // si aun no existe la lista la crea
        ht->l_array[i] = list_create();
        nueva = (HtEntry) malloc(sizeof (struct strHtEntry));
        nueva->Value = value;
        nueva->Key = key;
        list_add(ht->l_array[i], nueva); // y agrega la nueva entrada
        ht->size++;
    } else { //si ya existia la lista
        it = list_begin(ht->l_array[i]);
        while (list_hasNext(it)) { //la recorre para ver si ya existe la key
            it = list_next(it);
            iguales = ht->isKeyEqual(retrieveKeyFromIterator(it), key);
            if (iguales == TRUE) { //si ya existía remplaza el valor
                setEntryValue(it, value);
                flag = 1;
            }
        }
        if (flag = 0) { //si recorrió y no encontro la clave debemos agregarla
            nueva = (HtEntry) malloc(sizeof (struct strHtEntry));
            nueva->Value = value;
            nueva->Key = key;
            list_add(ht->l_array[i], nueva);
        }
    }
}

Type hashtable_get(HashTable ht, Type key) {  //recupera el value con el key
    if (ht == NULL || key == NULL)
        return NULL;
    int i;

    i = ht->hashcodeF(key) % ht->capacity;
    if (ht->l_array[i] == NULL)
        return NULL;
    Iterator ite;
    ite = list_begin(ht->l_array[i]);
    while (list_hasNext(ite)) {
        ite = list_next(ite);
        if (ht->isKeyEqual(retrieveKeyFromIterator(ite), key)) {
            return retrieveValueFromIterator(ite);
        }
    }
    return NULL;
}

Bool hashtable_contains(HashTable ht, Type key) { //compreuba que exista el key
    if (ht == NULL || key == NULL)
        return FALSE;
    int i;

    i = ht->hashcodeF(key) % ht->capacity;
    if (ht->l_array[i] == NULL)
        return FALSE;
    Iterator ite;
    ite = list_begin(ht->l_array[i]);
    while (list_hasNext(ite)) {
        ite = list_next(ite);
        if (ht->isKeyEqual(retrieveKeyFromIterator(ite), key)) {
            return TRUE;
        }
    }
    return FALSE;
}

/*
Bool hashtable_remove(HashTable ht, Type key) { //elimina con el key
    if (ht == NULL || key == NULL)
        return FALSE;
    int i;

    i = ht->hashcodeF(key) % ht->capacity;
    if (ht->l_array[i] == NULL)
        return FALSE;
    Iterator ite;
    ite = list_begin(ht->l_array[i]);
    while (list_hasNext(ite)) {
        ite = list_next(ite);
        if (ht->isKeyEqual(list_data(ite), key)) {
            
            return TRUE;
        }
    }
    return FALSE;
}
 */

Type* hashtable_getKeys(HashTable ht) { //devuelve un arreglo con los key de la tabla
    Type* array; //contiene los key a devolver
    array = (Type *) malloc(sizeof (Type) * ht->size);
    Iterator ite;
    int i;
    int count;
    count = 0;
    for (i = 0; i < ht->capacity; i++) {
        if (ht->l_array[i] != NULL) {
            ite = list_begin(ht->l_array[i]);
            while (list_hasNext(ite)) {
                ite = list_next(ite);
                array[count] = retrieveKeyFromIterator(ite);
                count++;
            }
        }
    }
    return array; 

}

Type* hashtable_getValues(HashTable ht) { //devuelve un arreglo con los key de la tabla
    Type* array; //contiene los values a devolver
    array = (Type *) malloc(sizeof (Type) * ht->size);
    Iterator ite;
    int i;
    int count;
    count = 0;
    for (i = 0; i < ht->capacity; i++) {
        if (ht->l_array[i] != NULL) {
            ite = list_begin(ht->l_array[i]);
            while (list_hasNext(ite)) {
                ite = list_next(ite);
                array[count] = retrieveValueFromIterator(ite);
                count++;
            }
        }
    }
    return array; 
}