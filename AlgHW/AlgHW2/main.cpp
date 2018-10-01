#include "String.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char **argv)
{
drmatters::String foo;
  foo += ("hey there");
  
  drmatters::String bar(foo);
  drmatters::String foobar = bar;
  foobar += foo;
  foo = foobar;
  cout << foo << endl;
  cout << bar << endl;
  cout << foobar << endl;
  try {
    cout << foo[1] << " " << bar.at(1) << endl;
  } catch (std::out_of_range& oor) {
    cout << "Error: :" << oor.what() << endl;
  }
  foo.clear();
  cin >> foo;
  cout << foo << endl;
  
  drmatters::String processed;
  for(size_t i = 0; i < foo.size(); i++) {
	if(foo.at(i) != '*') {
	  processed.pushBack(foo.at(i));
	  processed.pushBack(foo.at(i));
	} else {
	  continue;
	}
  }
  
  foo = processed;
  cout << foo << endl;
  
  system("pause");
  return 0;
}
