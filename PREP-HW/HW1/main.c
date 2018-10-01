/*
 * Вариант 10
 *Написать программу, которая в качестве аргумента командной строки принимает имя текстового файла (документа),
 *а на выходной поток выдаёт различные слова в этом файле с указанием их частоты встречаемости в тексте документа.
 *Слова должны выводиться в порядке убывания их частоты встречаемости. При одинаковой частоте встречаемости выдавать
 *слова в лексикографическом порядке. Частоту встречаемости считать как отношение количества вхождений слова к общему
 *количеству слов в тексте документа. Слова во входном файле разделяются символами, для которых библиотечные функции
 *isspace() или ispunct() возвращают ненулевое значение. Считать, что словарь различных слов можно хранить в оперативной памяти.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_DICTIONARY_SIZE 1000
#define MAX_LETTERS_OF_WORD_SIZE 128

typedef struct Word {
  unsigned int counter;
  char letters[MAX_LETTERS_OF_WORD_SIZE];
} Word;


void reset_word(Word* pArgWord, const char* pArgLetters);
void init_word(Word* pArgWord);


unsigned short fill_dictionary_from_file(FILE* pArgFile, Word* pArgDict, size_t* pArgDictSize, size_t* pArgTotalWords);
unsigned short get_word_from_file(FILE* pArgFile, Word* pArgWord);
void put_word_to_dictionary(Word* pArgDict, Word* pArgWord, size_t* pArgDictSize, size_t* pArgTotalWords);
Word* search(Word* pArgDict, const Word* key, const size_t argDictSize);
void print_dictionary(const Word* pArgDict, const size_t argDictSize, const size_t argTotalWords);

int compare_words(const void* lh, const void* rh);


int main(int argc, char **argv) {
  if(argc != 2) {
    printf("Fatal error: no input files\n");
    return 1;
  }
  
  FILE* input = fopen(argv[1], "r");
  if(input == NULL) {
	printf("Error: %s: no such file or directory\n", argv[1]);
	return 2;
  }
  
  
  Word dictionary[MAX_DICTIONARY_SIZE] = {{0}};
  for(int i = 0; i < MAX_DICTIONARY_SIZE; i++) {
	init_word(&dictionary[i]);
  }
  size_t currentDictionarySize = 0;
  size_t totalWords = 0;
  
  short int error_flag = fill_dictionary_from_file(input, dictionary, &currentDictionarySize, &totalWords);
  
  if(error_flag != 0) {
	return 1;
  }
  
  qsort(dictionary, currentDictionarySize, sizeof(Word), compare_words);
  print_dictionary(dictionary, currentDictionarySize, totalWords);


  fclose(input);    
  return 0;
}

void init_word(Word* pArgWord) {
  pArgWord->counter = 0;
  pArgWord->letters[0] = 0;
}
unsigned short fill_dictionary_from_file(FILE* pArgFile, Word* pArgDict, size_t* pArgDictSize, size_t* pArgTotalWords) {
  unsigned short errorFlag;
  Word temp;
  while(!feof(pArgFile)) {
	if(MAX_DICTIONARY_SIZE <= *pArgDictSize) {
	  
	  printf("Error: Maximum size of dictionary exceeded");
	  return 10;
	}
	errorFlag = get_word_from_file(pArgFile, &temp);
	if(!errorFlag) {
	  put_word_to_dictionary(pArgDict, &temp, pArgDictSize, pArgTotalWords);
	} else {
	  return errorFlag;
	}
  }
  return 0;
}
unsigned short get_word_from_file(FILE* pArgFile, Word* pArgWord) {
  size_t i = 0;
  char buff[MAX_LETTERS_OF_WORD_SIZE];
  char cTemp;
  while(!feof(pArgFile)) {
	cTemp = getc(pArgFile);
	if(!isspace((int)cTemp) && !ispunct((int)cTemp) && cTemp != EOF) {
	  buff[i] = cTemp;
	} else {
	  buff[i] = '\0';
	  break;
	}
	i++;
	if(i == MAX_LETTERS_OF_WORD_SIZE) {
	  printf("Error: Maximum size of word exceeded");
	  return 11;
	}
	if(ferror(pArgFile)) {
	  printf("Error: Unknown error of reading");
	  return 1;
	}
  }
  reset_word(pArgWord, buff);
  return 0;
}
void put_word_to_dictionary(Word* pArgDict, Word* pArgWord, size_t* pArgDictSize, size_t* pArgTotalWords) {
  Word* soughtWord = search(pArgDict, pArgWord, *pArgDictSize);
  if(soughtWord != NULL) {
	(soughtWord->counter)++;
	(*pArgTotalWords)++;
  } else {
	reset_word(&pArgDict[*pArgDictSize], pArgWord->letters);
	(*pArgDictSize)++;
	(*pArgTotalWords)++;
  }
}
Word* search(Word* pArgDict, const Word* key, const size_t argDictSize) {
  for(int i = 0; i < argDictSize; i++) {
	if(!strcmp(pArgDict[i].letters, key->letters)) {
	  return &pArgDict[i];
	}
  }
  return NULL;
}
void reset_word(Word* pArgWord, const char* pArgLetters) {
  pArgWord->counter = 1;
  strcpy(pArgWord->letters, pArgLetters);
}
int compare_words(const void* lh, const void* rh) {
  Word* pLH = (Word*)lh;
  Word* pRH = (Word*)rh;
  if(pLH->counter < pRH->counter) return 1;
  if(pLH->counter > pRH->counter) return -1;
  
  return strcmp(pLH->letters, pRH->letters);
}
void print_dictionary(const Word* pArgDict, const size_t argDictSize, const size_t argTotalWords) {
  for(size_t i = 0; i < argDictSize; i++) {
	printf("%s: %f \n", pArgDict[i].letters, ((float)pArgDict[i].counter)/(float)argTotalWords);
  }
}
