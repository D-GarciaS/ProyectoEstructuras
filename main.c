/* 
 * File:   main.c
 * Author: Hogar
 *
 * Created on 25 de noviembre de 2015, 09:01 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"
/*
 * 
 */

int hc_flot2dec(void* a){
    return (int)(*((float *)a)*100);
}

Bool igu_flot2dec(void* a, void *b){
    return (*(float*)a == *(float*)b)? TRUE : FALSE;
}

int main(int argc, char** argv) {
    HashTable ht1;
    ht1 = hashtable_create(100, hc_flot2dec,igu_flot2dec);
    float a = 1.1, b = 2.2;
    hashtable_put(ht1,&a,"A");
    return (EXIT_SUCCESS);
}

