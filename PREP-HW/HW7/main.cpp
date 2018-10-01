#include "String.hpp"
#include "Map.hpp"
#include "Vector.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char **argv)
{
  /*drmatters::String foo;
  foo += ("hey there");
  
  drmatters::String bar(foo);
  drmatters::String foobar = bar;
  foobar += foo;
  foo = foobar;
  cout << foo << endl;
  cout << foo.size() << endl;
  cout << bar << endl;
  cout << bar.size() << endl;
  cout << foobar << endl;
  cout << foobar.size() << endl;
  try {
    cout << foo[1] << " " << bar.at(1) << endl;
  } catch (std::out_of_range& oor) {
    cout << "out of range" << oor << endl;
  }
  foo.clear();
  cin >> foo;
  cout << foo << endl;
  //drmatters::Map<int, int> fooMap;
  //drmatters::Map<int, int> barMap(fooMap);
  //drmatters::Map<int, int>::iterator alpha;
*/
  std::vector<int> stAlpha = {1, 2, 3, 4, 6};
  std::vector<int> stBeta(stAlpha);
  
  auto itBeta = stBeta.begin();
  auto iteBeta = stBeta.end();
  auto itAlpha = stAlpha.begin();
  auto iteAlpha = stAlpha.end();
  
  drmatters::Vector<int> beta;
  auto tit = beta.begin();
  auto tite = beta.end();
  drmatters::Vector<int> gamma(10);
  drmatters::Vector<int> delta(gamma);
  beta.pushBack(22);
  beta.pushBack(228);
  beta.pushBack(1388);
  
  tit = beta.begin();
  cout << tit[1] << endl;
  tite = beta.end();
  
  drmatters::Vector<int> epsilon = {1, 2, 3, 4, 5, 10, 15};
  /*for(auto& item : epsilon) {
	cout << item << endl;
  }*/
  
  gamma = epsilon;
  try {
    gamma.at(4);
  } catch (std::out_of_range& oor) {
    cout << "Out of range exception catched " << oor.what() << endl;
  }
  for(auto& item : gamma) {
	cout << item << endl;
  }
  
  return 0;
}
