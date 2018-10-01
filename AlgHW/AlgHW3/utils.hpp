#include <vector>
#include <string>
#include "FileWrapper.hpp"
#include "mergeSort.hpp"
namespace drmatters {

//class FileWrapper;
std::vector<std::string> stringsToVec(FileWrapper& wrapper) {
  std::vector<std::string> tempV;
  std::string tempS;
  wrapper.emptyString = false;
  while(true) {
    tempS = wrapper.transferWord();
	if(tempS.size() == 0) {
	  wrapper.emptyString = true;
	  wrapper.totalLength++;
	  return tempV;
	}
	if(tempS == "new") {
	  wrapper.emptyString = true;
	  return tempV;
	}
    if((tempS != "end")) {
      tempV.push_back(tempS);
	  wrapper.totalLength += tempV.size();
    } else {
      return tempV;
    }
  }
}
std::vector<int> transformToInt(const std::vector<std::string>& toProcess) {
  std::vector<int> toReturn;
  for(auto itB = toProcess.cbegin(); itB != toProcess.cend(); itB++) {
	toReturn.push_back(std::stoi(*itB));
  }
  return toReturn;
}
void sendResults(FileWrapper& wrapper) {
  std::vector<std::string> strVec;
  std::vector<int> intVec;
  do {
	strVec = stringsToVec(wrapper);
	wrapper.stringsProcessed++;
	intVec = transformToInt(strVec);
	merge_sort(intVec.begin(), intVec.end());
	for(auto i : intVec) {
	  wrapper.getOutput() << i << ' ';
	}
	wrapper.getOutput() << '\n';
  } while(intVec.size() != 0 || wrapper.emptyString);
}
}