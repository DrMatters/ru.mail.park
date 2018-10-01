#include <fstream>
#include <iostream>
#include "FixedPointUInt.hpp"

using std::cout;
using std::endl;
using std::cin;

using namespace std;
int main(int argc, char **argv)
{
  ifstream input(argv[1]);
  ofstream output(argv[2]);
  ofstream err(argv[3]);
  if(argc != 4) {
	cout << "Wrong format of arguments" << endl;
  }
  if(!(input.is_open() && output.is_open() && err.is_open())) {
	cout << "Cannot open one of files" << endl;
	return 1;
  }
  
  myNamespace::LInt foo(err);
  myNamespace::LInt bar(err);
  input >> foo;
  input >> bar;
  
  foo = foo * bar;
  
  output << foo;
  
  input.close();
  output.close();
  err.close();
  
  return 0;
}
