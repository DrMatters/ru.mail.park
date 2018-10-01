#include "WordSorter.hpp"
#include <stdexcept>
#include <string>
#include <algorithm>
#include <boost/tokenizer.hpp>

using boost::tokenizer;
using std::pair;
using std::string;
namespace drmatters {
  bool stringEqPred(const std::pair<std::string, unsigned>& lh, const std::pair<std::string, unsigned>& rh) { //mb mk functor for access restriction?
	return (lh.first.compare(rh.first) == 0);
  }
  bool cmpPairs(const std::pair<std::string, unsigned>& lh, const std::pair<std::string, unsigned>& rh) {
	if(lh.second > rh.second) return true;
	if(lh.second < rh.second) return false;
	if(lh.first.compare(rh.first) < 0) return true;
	return false;
  }
  WordSorter::WordSorter(const char* inputFilePath, const char* outputFilePath, std::ostream& logStream)
	  : input(inputFilePath), output(outputFilePath), logOStream(logStream), dictSize(0) {
	if(!input.is_open()) {
	  throw std::runtime_error("Can't open input file\n");
	}
	if(!output.is_open()) {
	  throw std::runtime_error("Can't open output file\n");
	}
  }
  WordSorter::~WordSorter() {
    input.close();
    output.close();
  }
  void WordSorter::process() {
	string strBuf;
	while(!input.eof()) {
	  input >> strBuf;
	  if(input.fail()) {
		throw std::runtime_error("Logical or read/writing error on i/o operation while processing input file");
	  }
	  tokenizer<> tok(strBuf);
	  for(tokenizer<>::iterator tokIt = tok.begin(); tokIt != tok.end(); ++tokIt) {
		if(dictionary.size() != 0) {
		  std::vector<dictEntry>::iterator curIt;
		  
		  dictEntry curEntry = {*tokIt, 0};
		  
		  //std::search_n(dictionary.begin(), dictionary.end(), 1, curEntry, stringEqPred);
		  curIt = std::search_n(dictionary.begin(), dictionary.end(), 1, curEntry, stringEqPred);
		  if(curIt != dictionary.end()) {
			curIt->second++;
		  } else {
			dictionary.push_back({*tokIt, 1});
		  }
		} else {
		  dictionary.push_back({*tokIt, 1}); //push-back a pair of first = tokIt (string)
		}
	  }
	}
	std::sort(dictionary.begin(), dictionary.end(), cmpPairs);
	
  }
  void WordSorter::write() {
	for(auto& it : dictionary) {
	  output << it.first << " " << it.second << std::endl;
	}
  }
  
}