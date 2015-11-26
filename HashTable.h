/* 
 * File:   HashTable.h
 * Author: Hogar
 *
 * Created on 25 de noviembre de 2015, 09:24 PM
 */

#ifndef HASHTABLE_H
#define	HASHTABLE_H

#include "List.h"

typedef struct strHash* HashTable;
typedef void* Type;
typedef int (*hashcodeFunc) (Type);
Bool(*equalsFunc) (Type, Type);

HashTable hashtable_create(int capacity, hashcodeFunc, equalsFunc);
void hashtable_destroy(HashTable);
int hashtable_size(HashTable);
void hashtable_put(HashTable, Type key, Type value);
Type hashtable_get(HashTable, Type key);
Bool hashtable_contains(HashTable, Type key);
Bool hashtable_remove(HashTable, Type key);
Type* hashtable_getKeys(HashTable);
Type* hashtable_getValues(HashTable);

#endif	/* HASHTABLE_H */

