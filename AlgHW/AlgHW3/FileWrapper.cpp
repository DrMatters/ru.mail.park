#include "FileWrapper.hpp"

namespace drmatters {
FileWrapper::FileWrapper(const char* inputFilePath, const char* outputFilePath)
    : input(inputFilePath), output(outputFilePath) {
  if(!input.is_open() || !output.is_open()) {
    throw std::runtime_error("Cannot find files");
  }
}
FileWrapper::~FileWrapper() {
  input.close();
  output.close();
}
std::string FileWrapper::transferWord() {
  std::string tempS;
  if(input.eof()) {
	tempS = "end";
  }
  while(!input.eof()) {
	char tempC;
	tempC = input.get();
	if(tempC == '\n') {
	  tempS = "new";
	  return tempS;
	}
	if(isspace((int)tempC)) {
	  break;
	}
	if(isdigit((int)tempC) || ((tempC == '-') && (tempS.size() == 0))) {
	  tempS.push_back(tempC);
	}
  }
  return tempS;
}


}