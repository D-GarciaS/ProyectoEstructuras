/*
 * Set.h
 *
 *  Created on: 11/11/2015
 *      Author: Cursos
 */

#ifndef SET_H_
#define SET_H_

typedef void* Type;
typedef int (*CompareFunc) (Type, Type);
typedef enum {FALSE, TRUE} Bool;
typedef struct strSet* Set;

Set set_create(CompareFunc);
int set_size(Set);
Bool set_add(Set, Type);

#endif /* SET_H_ */
