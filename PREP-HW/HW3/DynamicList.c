#include "DynamicList.h"

#include <stdlib.h>

struct DynamicList {
  voidptr data;

  
  unsigned short isEmpty;
  struct DynamicList* prev;
  struct DynamicList* next;
};


void addDescending(DynamicList* head, DynamicList* toAdd, int (*compar)(const voidptr, const voidptr));
DynamicList* initDynamicList(voidptr elem) {
  DynamicList* list = malloc(sizeof(DynamicList));
  if(list == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  list->data = elem;
  list->next = NULL;
  list->prev = NULL;
  list->isEmpty = 0;
  return list;
}
DynamicList* createDynamicList() {
  DynamicList* list = malloc(sizeof(DynamicList));
  if(list == NULL) {
	printf("Memory allocation error\n");
	return NULL;
  }
  list->data = 0;
  list->next = NULL;
  list->prev = NULL;
  list->isEmpty = 1;
  return list;
}
unsigned short pushDescending(DynamicList* list, voidptr data, int (*compar)(const voidptr, const voidptr)) {
  if(list == NULL) {
    printf("Cannot push data to NULL list\n");
    return 0;
  }
  if(list->isEmpty) {
    list->data = data;
    list->isEmpty = 0;
    return 1;
  } else {
    DynamicList* inited = initDynamicList(data);
    addDescending(list, inited, compar);
    return 1;
  }
}
void freeDynamicList(DynamicList* list, void (*dataDestructor)(voidptr data)) {
  if(list == NULL) {
	printf("Error: cannot free empty pointer\n");
	return;
  }
  if(!list->isEmpty) {
	while(list->next != NULL) {
	  list = list->next;
	}
	
	while(list->prev != NULL) {
	  
	  dataDestructor(list->data);
	  list = list->prev;
	  free(list->next);
	}
	
	dataDestructor(list->data);
  }
  free(list);
}
voidptr getData(DynamicList* list) {
  if(list == NULL) {
	printf("Error: cannot get data from NULL list\n");
	return NULL;
  }
  if(list->isEmpty) {
    printf("Error: list is empty\n");
    return NULL;
  }
  return list->data;
}
DynamicList* iteratePrev(DynamicList* head, short* iterationStatus) {
  if(head == NULL) {
    printf("Error: Cannot iterate in NULL list\n");
    *iterationStatus = -1;
  }
  if(head->isEmpty) {
    printf("Error: Cannot iterate in empty list\n");
	*iterationStatus = -1;
    return NULL;
  }
  if(head->prev == NULL) {
	*iterationStatus = 0;
	return NULL;
  } else {
	*iterationStatus = 1;
	return head->prev;
  }
}
DynamicList* iterateNext(DynamicList* head, short* iterationStatus) {
  if(head == NULL) {
    printf("Error: Cannot iterate in NULL list\n");
    *iterationStatus = -1;
  }
  if(head->isEmpty) {
    printf("Error: Cannot iterate in empty list\n");
	*iterationStatus = -1;
    return NULL;
  }
  if(head->next == NULL) {
	*iterationStatus = 0;
	return NULL;
  } else {
	*iterationStatus = 1;
	return head->next;
  }
}
void addNextDynamicList(DynamicList* list, DynamicList* toAdd) {
  //Эта функция работает внутри либы, и поэтому результатов проверок
  //она не возвращает
  if((toAdd->prev) || (toAdd->next)) {
	printf("Error\n");
	return;
  }
  
  if(list->next == NULL) {
	toAdd->prev = list;
	list->next = toAdd;
  } else {
	DynamicList* savedNext = list->next;
	
	toAdd->prev = list;
	list->next = toAdd;
	
	savedNext->prev = toAdd;
	toAdd->next = savedNext;
	
  }
}
void addPrevDynamicList(DynamicList* list, DynamicList* toAdd) {
  if((toAdd->prev) || (toAdd->next)) {
	
	printf("Error");
	return;
  }
  
  if(list->prev == NULL) {
	toAdd->next = list;
	list->prev = toAdd;
  } else {
	DynamicList* savedPrev = list->prev;
	
	toAdd->next = list;
	list->prev = toAdd;
	
	savedPrev->next = toAdd;
	toAdd->prev = savedPrev;
	
  }
}
void addDescending(DynamicList* head, DynamicList* toAdd, int (*compar)(const voidptr, const voidptr)) {
  DynamicList* cur = head;
  while(cur->prev != NULL) {
	cur = cur->prev;
  }
  while(cur != NULL) {		//движемся по списку слева направо, и если текущий эл. больше, то вставл. слева
	if(compar(cur->data, toAdd->data) < 0) {
	  addPrevDynamicList(cur, toAdd);
	  return;
	}
	if(cur->next == NULL) {		//если мы достигли конца, а больше элементов не появилось - вставлсяем в конец
	  addNextDynamicList(cur, toAdd);
	  return;
	}
	cur = cur->next;
  }
}