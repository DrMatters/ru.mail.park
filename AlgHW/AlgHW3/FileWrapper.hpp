#ifndef FILEWRAPPER_HPP
#define FILEWRAPPER_HPP
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace drmatters {

class FileWrapper {
public:
  //public
  FileWrapper(const char* inputFilePath, const char* outputFilePath);
  ~FileWrapper();
  std::string transferWord();
  std::ofstream& getOutput() {
	return output;
  }
  bool emptyString = false;
  size_t totalLength = 0;
  size_t stringsProcessed = 0;
private:
  //private
 
  std::ifstream input;
  std::ofstream output;
};


}



#endif //#ifndef FILEWRAPPER_HPP