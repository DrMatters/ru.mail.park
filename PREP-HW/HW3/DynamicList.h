#ifndef _DYNAMICLIST_h
#define _DYNAMICLIST_H

#include <stdlib.h>
#include <stdio.h>

typedef void* voidptr;
struct DynamicList;
typedef struct DynamicList DynamicList;

DynamicList* initDynamicList(voidptr elem);
DynamicList* createDynamicList();
void freeDynamicList(DynamicList* list, void (*dataDestructor)(voidptr data));
unsigned short pushDescending(DynamicList* list, voidptr data, int (*compar)(const voidptr, const voidptr));
DynamicList* iteratePrev(DynamicList* head, short* iterationStatus);
DynamicList* iterateNext(DynamicList* head, short* iterationStatus);
voidptr getData(DynamicList* head);

#endif //#ifndef _DYNAMICLIST_H