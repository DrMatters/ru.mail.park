#ifndef STRING_H
#define STRING_H
#include <iostream>

namespace drmatters {
  
  class String {
  public:
    
    String(); //default
    String(const String& toCpy); //copy
	String(const char* cStr); //c-str
    
	~String(); //destr
	
	String& 	operator=(String str);
	String& 	operator=(const char* cStr);
	char& 		operator[](size_t pos);
	const char& operator[](size_t pos) const;
	char& at(size_t pos);
	const char& at(size_t pos) const;
	
	String& operator+=(const String& str);
	const char* data() const;
	const char* c_str() const;
	
	friend std::ostream& operator<<(std::ostream& stream, String& obj);
	friend std::istream& operator>>(std::istream& stream, String& obj);
	
    size_t size() const;
	void clear(); //delete all string
	bool empty() const;
	friend void swap(String& lh, String& rh) {
	  using std::swap;
	  
	  swap(lh.curSize, rh.curSize);
	  swap(lh.capacity, rh.capacity);
	  swap(lh.pStr, rh.pStr);
	}
	void pushBack(char c);
    
  private:
    size_t curSize;
    size_t capacity;
	char* pStr;
	
	void increaseCapacity(size_t n);
	String(size_t length) :
		curSize(length),
		capacity(length),
		pStr(new char[length]) {
	}
  };
}

#endif //#ifndef STRING_H