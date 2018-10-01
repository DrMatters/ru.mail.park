#ifndef FIXEDPOINTUINT_HPP
#define FIXEDPOINTUINT_HPP
#include <vector>
#include <iostream>
#include <fstream>

namespace myNamespace {
  const int base = 1000 * 1000 * 1000;
  
  class LInt {
  public:
	LInt(std::ofstream& err) : errors(err) {
	  };

	LInt(const LInt& toCpy) : errors(toCpy.errors){
	  digits = toCpy.digits;
	};
	friend std::ostream& operator<<(std::ostream& stream, const LInt& obj);
	friend std::istream& operator>>(std::istream& stream, LInt& obj);
	LInt operator*(const LInt& rh);
	LInt operator=(const LInt& rh) {
	  digits = rh.digits;
	  return *this;
	};
	void lowerPrecision(const int afterPointBefore);
    
  private:
    void divideByShort(int divider);
    const int afterPoint = 5;
	std::ofstream& errors;
	std::vector<int> digits;
  };
}


#endif //#ifndef _FIXEDPOINTUINT_HPP_