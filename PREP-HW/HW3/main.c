/*
 * Написать программу, которая в качестве аргументов командной строки принимает имена двух
 * текстовых файлов. В первом файле содержится последовательность слов. Необходимо
 * записать во второй файл слова, содержащиеся в первом файле, упорядоченные в порядке
 * убывания (в качестве функции сравнения слов использовать лексикографическое сравнение).
 * При реализации алгоритма необходимо использовать динамический список. Слова в первом
 * файле разделяются символами, для которых библиотечная функция isspace() возвращает
 * ненулевое значение
 * */
#include <stdio.h>
#include <string.h>
#include "DynamicList.h"

#define MAX_WORD_LENGTH 128


void freeString(voidptr str);
int compareInt(const voidptr lh, const voidptr rh);
int compareStrVoid(const voidptr lh, const voidptr rh);
unsigned short processFiles(FILE* input, FILE* output);
short printListInFile(FILE* output, DynamicList* head); //поскольку си не умеет определять тип, мы не знаем какой формат использовать
//поэтому лепим эту функцию в main
int main(int argc, char **argv) {
  if(argc != 3) {
	printf("Error: no input/output files in arguments\n");
	printf("Run program like this prep-hw3 input_filename output_filename\n");
	return 10;
  }
  
  FILE* input = fopen(argv[1], "r");
  FILE* output = fopen(argv[2], "w");
  
  if(!(input && output)) {
	printf("Error: %s, %s: no such file or directory\n", argv[1], argv[2]);
	return 10;
  }
  
  processFiles(input, output);
  
  
  
  fclose(input);
  fclose(output);
  
  return 0;
}

short printListInFile(FILE* output, DynamicList* head) {
  if(head == NULL) {
    printf("Cannot print an empty file\n");
    return NULL;
  }
  
  short iterationStatus;
  iteratePrev(head, &iterationStatus);//запись статуса возможной итерации
  if(iterationStatus == -1) {
	return -1;
  }
  
  while(iterationStatus == 1) {
	head = iteratePrev(head, &iterationStatus);
	iteratePrev(head, &iterationStatus); //получаем статус следующей итерации
  }
  
  iterateNext(head, &iterationStatus);
  while(iterationStatus == 1) {
	fprintf(output, "%s ", (char*)getData(head));
	head = iterateNext(head, &iterationStatus);
	iterateNext(head, &iterationStatus);
  }
  
  fprintf(output, "%s ", (char*)getData(head));
  
  return 1;
}

unsigned short processFiles(FILE* input, FILE* output) {
  DynamicList* simpleList = createDynamicList(sizeof(int));
  
  
  while(!feof(input)) {
	char string[MAX_WORD_LENGTH];
	
	if(fscanf(input, "%127s", string) != 1) {
	  if(feof(input)) {
		break;
	  } else {
		freeDynamicList(simpleList, freeString);
		printf("Too long word to process it\n");
		return 0;
	  }
	}
	
	char* pString = malloc(sizeof(string));
	strcpy(pString, string);
    unsigned short noErrFlag = pushDescending(simpleList, (voidptr)pString, compareStrVoid);
    if(!noErrFlag) {
      freeDynamicList(simpleList, freeString);
      return 0;
    }
  }
  printListInFile(output, simpleList);
  freeDynamicList(simpleList, freeString);
  return 1;
}
int compareInt(const voidptr lh, const voidptr rh) {
  if(*(int*)lh < *(int*)rh) return -1;
  if(*(int*)lh == *(int*)rh) return 0;
  if(*(int*)lh > *(int*)rh) return 1;
  return 0;
}
int compareStrVoid(const voidptr lh, const voidptr rh) {
  return strcmp((const char*)lh, (const char*)rh);
}
void freeString(voidptr str) {
  free((char*)str);
}