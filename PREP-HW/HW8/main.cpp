/*
 * Вариант 10
 * Написать программу, которая в качестве аргумента командной строки принимает
 * имя текстового файла (документа), а на выходной поток выдаёт различные слова
 * в этом файле с указанием их частоты встречаемости в тексте документа. Слова
 * должны выводиться в порядке убывания их частоты встречаемости. При одинаковой
 * частоте встречаемости выдавать слова в лексикографическом порядке. Частоту
 * встречаемости считать как отношение количества вхождений слова к общему количеству
 * слов в тексте документа. Слова во входном файле разделяются символами, для которых
 * библиотечные функции isspace() или ispunct() возвращают ненулевое значение.
 * Считать, что словарь различных слов можно хранить в оперативной памяти.
 */

#include <stdexcept>
#include <iostream>
#include <string>
#include "WordSorter.hpp"
#include <boost/algorithm/string/split.hpp>
#include <boost/tokenizer.hpp>

using std::cout;
using std::endl;
using boost::tokenizer;
int main(int argc, char **argv)
{
  if(argc != 3) {
	cout << "Wrong arguments" << endl;
	return EXIT_FAILURE;
  }
  try {
	drmatters::WordSorter alpha(argv[1], argv[2], cout);
	alpha.process();
	alpha.write();
  } catch(std::exception& exc) {
	cout << "Error: " << exc.what() << endl;
  } catch(...) {
	cout << "Something went wrong" << endl;
  }
  
  return 0;
}
