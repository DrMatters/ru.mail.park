#ifndef WORDSORTER_HPP_
#define WORDSORTER_HPP_

#include <iostream>
#include <fstream>
#include <vector>

namespace drmatters {
class WordSorter {
public:
  typedef std::pair<std::string, unsigned> dictEntry;
  WordSorter(const char* inputFilePath, const char* outputFilePath, std::ostream& logStream);
  
  ~WordSorter();
  void process();
  void write();
private:
  std::ifstream input;
  std::ofstream output;
  std::ostream& logOStream;
  
  size_t dictSize;
  std::vector<dictEntry> dictionary;
};
}
#endif //#ifndef WORDSORTER_HPP_