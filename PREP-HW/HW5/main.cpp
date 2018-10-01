#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
#include <algorithm>
#include "Customer.hpp"

using hw4::Customer;
void showRanged(const std::set<Customer>& argSet, unsigned upperBound, unsigned lowerBound);
void showByTotalPurchase(const std::set<Customer>& argSet, int total);
int main(int argc, char **argv)
{
  std::ifstream input("input.txt");
  std::set<Customer> first;
  
  Customer alpha = {"Alting", "Matters", "Petrov", "Russia", "+78915", 2281488, "aqqaunt", 1488228}; //универсальная инициализация
  while(!input.eof()) {
	input >> alpha;
	first.insert(alpha);
  }
  
  int manualControl = 1;
  
  while((manualControl < 3) && (manualControl >=0)) {
	std::cout << "1) Input 0 to show descending customers list\n";
	std::cout << "2) Input 1 to show customers from selected range of credit card numbers\n";
	std::cout << "3) Input 2 to show customers with selected total purchase sum and above\n";
	std::cin >> manualControl;
	switch (manualControl) {
	case 0: 
	  for(auto it: first) 
		it.show(std::cout);
	  std::cout << "Press any key to continue\n";
	  std::cin.get();
	  std::cin.get();
	break;
	case 1:
	  unsigned upper, lower;
	  std::cout << "Input upper, and then lower bounds\n";
	  std::cin >> upper >> lower;
	  showRanged(first, upper, lower);
	  std::cout << "Press any key to continue\n";
	  std::cin.get();
	  std::cin.get();
	break;
	case 2:
	  int total;
	  std::cout << "Input total purchase amount\n";
	  std::cin >> total;
	  if(total >= 0) {
		showByTotalPurchase(first, total);
		std::cout << "Press any key to continue\n";
		std::cin.get();
		std::cin.get();
	  } else {
		break;
	  }
	 break;
	}
  }
  
  return 0;
}
void showRanged(const std::set<Customer>& argSet, unsigned upperBound, unsigned lowerBound) {
  for_each(argSet.cbegin(), argSet.cend(), [upperBound, lowerBound](const Customer& arg) { //lambda-функции и cbegin/cend итераторы
	if((arg.getCreditCardNumber() <= upperBound) && (arg.getCreditCardNumber() >= lowerBound)) {
	  arg.show(std::cout);
	}
  });
}
void showByTotalPurchase(const std::set<Customer>& argSet, int total) {
  for_each(argSet.cbegin(), argSet.cend(), [total](const Customer& arg) {
	if(arg.getTotalPurchaseSum() > total) {
	  arg.show(std::cout);
	}
  });
}