#include "String.hpp"

#include <cstddef> //std::size_t
#include <algorithm>
#include <cstring>
#include <stdexcept>
namespace drmatters {
  String::String() : curSize(0), capacity(0), pStr(nullptr) {
  }
  
  String::String(const String& toCpy) : curSize(toCpy.curSize),
      capacity(toCpy.capacity),
      pStr(toCpy.capacity ? new char[toCpy.capacity] : nullptr) {
		
      std::copy(toCpy.pStr, toCpy.pStr + curSize, pStr);
  }
  
  String::String(const char* cStr) : curSize(strlen(cStr) + 1),
	  capacity(strlen(cStr) + 1),
	  pStr(new char[strlen(cStr) + 1]) {
	memcpy(pStr, cStr, curSize);
  }
  
  String::~String() {
	delete[] pStr;
  }
  
  String& String::operator=(String str) { //parameter taken by-value!
	swap(*this, str);
	
	return *this;
  }
  
  String& String::operator=(const char* cStr) {
	String tempS(strlen(cStr) + 1);
	//on this stage bad_alloc can be thrown
	strcpy(tempS.pStr, cStr);
	swap(*this, tempS);
	
	return *this;
  }
  
  char& String::operator[](size_t pos) {
	return pStr[pos];
  }
  const char& String::operator[](size_t pos) const {
	return pStr[pos];
  }
  char& String::at(size_t pos) {
	if(pos >= curSize) throw std::out_of_range("out of range in String::at");//out of range
	return pStr[pos];
  }
  const char& String::at(size_t pos) const {
	if(pos >= curSize) throw std::out_of_range("out of range in String::at");//out of range
	return pStr[pos];
  }
  
  bool String::operator==(const String& toCheck) {
    if(curSize != toCheck.curSize) {
      return false;
    }
    for(size_t i = 0; i < curSize; ++i) {
      if(pStr[i] != toCheck.pStr[i])  {
        return false;
      }
    }
    return true;
  }
  bool String::operator!=(const String& toCheck) {
    if(curSize != toCheck.curSize) {
      return true;
    }
    for(size_t i = 0; i < curSize; ++i) {
      if(pStr[i] != toCheck.pStr[i])  {
        return true;
      }
    }
    return false;
  }
  
  void String::clear() {
	delete [] pStr;
	pStr = nullptr;
	curSize = 0;
	capacity = 0;
  }
  bool String::empty() const {
	return curSize == 0;
  }
  String& String::operator +=(const String& str) {
	String tempS(curSize + str.curSize);
	
	std::copy(pStr, pStr + curSize, tempS.pStr);
	std::copy(str.pStr, str.pStr + str.curSize, tempS.pStr + curSize);
	
	swap(*this, tempS);
	return *this;
  }
  String& String::operator+(const String& str) {
    String tempS(curSize + str.curSize);
    
    std::copy(pStr, pStr + curSize, tempS.pStr);
    std::copy(str.pStr, str.pStr + str.curSize, tempS.pStr + curSize);
    
    return *this;
  }
  String& String::insert(const String& str, const size_t pos) {
    if((curSize + str.curSize) > capacity) {
      increaseCapacity(curSize + str.curSize - capacity);
    }
	
    String tempS(pStr + pos);
    std::copy(str.pStr, str.pStr + str.curSize, pStr + pos);
    *this += tempS;
    
    return *this;
  }
  
  const char* String::data() const {
	return pStr;
  }
  const char* String::c_str() const {
	return pStr;
  }
  size_t String::size() const {
	return curSize - 1;
  }
  void String::increaseCapacity(size_t n) {
	String tempS(capacity + n);
	tempS.curSize = curSize;
	std::copy(pStr, pStr + curSize, tempS.pStr);
	
	swap(*this, tempS);
  }
  void String::pushBack(char c) {
	if(capacity <= curSize) {
	  increaseCapacity(10);
	}
	pStr[curSize] = c;
	curSize++;
  }
  std::ostream& operator<<(std::ostream& stream, String& obj) {
	if(obj.pStr != nullptr) {
	  for(size_t i = 0; i < obj.size(); i++) {
		stream << obj.pStr[i];
	  }
	}
	return stream;
  }
  std::istream& operator>>(std::istream& stream, String& obj) {
	char tempC;
    while(!(stream.rdstate() & std::istream::eofbit)) {
	  stream.get(tempC);
	  if(tempC == '\n') {
		obj.pushBack('\0');
		break;
	  }
	  obj.pushBack(tempC);
	}
	obj.curSize++;
	return stream;
  }
}