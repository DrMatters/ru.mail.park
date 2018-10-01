#include "FixedPointUInt.hpp"

#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <climits>

namespace myNamespace {

  std::ostream& operator<<(std::ostream& stream, const LInt& obj) {
    //TODO
    int digPos = obj.afterPoint / 9;
    int pos = obj.afterPoint % 9;
    if(obj.digits.empty()) {
      stream << 0;
      return stream;
    }
    if(digPos != (int)obj.digits.size() - 1) {
      stream << obj.digits.back();
    } else {
      stream << obj.digits.back() / (int)pow(10, pos) << '.';
      stream << std::setw(pos) << std::setfill('0') << obj.digits.back() - (obj.digits.back() / (int)pow(10, pos)) * (int)pow(10, pos);
    }
    //TODO
	for(int i = (int)obj.digits.size() - 2; i >= 0; --i) {
      if(i != digPos) {
        stream << std::setw(9) << std::setfill('0') << obj.digits[i];
      } else {
        stream << std::setw(9 - pos) << std::setfill('0') << obj.digits[i] / (int)pow(10, pos);
        stream << '.';
        stream << std::setw(pos) << std::setfill('0')  << obj.digits[i] - (obj.digits[i] / (int)pow(10, pos)) * (int)pow(10, pos);
      }
	}
	return stream;
  }
  std::istream& operator>>(std::istream& stream, LInt& obj) {
	std::string s;
	stream >> s;
	obj.errors << "Warning: this program can contain values with less or 5 digits after point!" << std::endl;
    if(s.length() > 50) {
	  obj.errors << "Warning: values must have less than 50 digits according to task" << std::endl;
	}
	if(s.length() >= INT_MAX) {
	  obj.errors << "Error: cannot contain value with more than " << INT_MAX << " digits" << std::endl;
	  return stream;
	}
    int j;
    for(j = 0; j < (int)s.length(); j++) {
      if(s[j] == '.') {
        break;
      }
      if(!isdigit((int)s[j])) {
        obj.errors << "Error: value cannot include non-digit characters" << std::endl;
        return stream;
      }
    }
    s.erase((size_t)j, 1);
    //std::cout << s << std::endl << j << std::endl;
	for(int i = 0; i < obj.afterPoint; i++) {   //преобразование числа к станд. виду
      if(i + j < (int)s.length()) {
        if(!isdigit((int)s[i + j])){
          obj.errors << "Error: value cannot include non-digit characters" << std::endl;
          return stream;
        }
        continue;
      }
      if(i + j >= (int)s.length()) {
        s.push_back('0');
      }
    }
    s.erase(obj.afterPoint + j);
    //std::cout << s << std::endl;
    
	for(int i = (int)s.length(); i > 0; i -= 9) {
	  if(i < 9)
		obj.digits.push_back(atoi(s.substr(0, i).c_str()));
	  else 
		obj.digits.push_back(atoi(s.substr(i - 9, 9).c_str()));
	}
	while(obj.digits.size() > 1 && obj.digits.back() == 0)
	  obj.digits.pop_back();
	return stream;
  }
  LInt LInt::operator*(const LInt& rh) {
	LInt c(errors);
	
	c.digits.resize(this->digits.size() + rh.digits.size());
	for(size_t i = 0; i < this->digits.size(); ++i) {
	  for(int j = 0, carry = 0; j < (int)rh.digits.size() || carry; ++j) {
		long long cur = c.digits[i + j] + this->digits[i] * 1ll * (j < (int)rh.digits.size() ? rh.digits[j] : 0) + carry;
		c.digits[i + j] = int (cur % base);
		carry = int (cur / base);
	  }
	}
	while(c.digits.size() > 1 && c.digits.back() == 0) {
	  c.digits.pop_back();
	}
    c.lowerPrecision(5);
	
	return c;
  }
  void LInt::divideByShort(int divider) {
    int carry = 0;
    for(int i = (int)digits.size() - 1; i >= 0; --i) {
      long long cur = digits[i] + carry * 1ll * base;
      digits[i] = int (cur / divider);
      carry = int (cur % divider);
    }
    while(digits.size() > 1 && digits.back() == 0) {
      digits.pop_back();
    }
  }
  void LInt::lowerPrecision(const int digitsToRm) {
    int toPopFront = digitsToRm / 9;
    int toPop = digitsToRm % 9;
    for(int i = 0; i < toPopFront; i++) {
      digits.erase(digits.begin());
    }
    
    divideByShort((int)pow(10, toPop));
    
  }
  
}