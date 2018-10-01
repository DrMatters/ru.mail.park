#include "Customer.hpp"
#include "AppliedFuncs.hpp"
#include <cstring>
#include <string>
namespace hw4 {
  Customer::Customer() : name(nullptr), surname(nullptr), patronymic(nullptr), address(nullptr),
		phoneNumber(nullptr), creditCardNumber(0), bankAccount(nullptr), totalPurchaseSum(-1) {
  }
  Customer::Customer(const Customer& object) {
	name = new char[strlen(object.getName()) + 1];
	strcpy(name, object.getName());
	
	surname = new char[strlen(object.getSurname()) + 1];
	strcpy(surname, object.getSurname());
	
	patronymic = new char[strlen(object.getPatronymic()) + 1];
	strcpy(patronymic, object.getPatronymic());
	
	address = new char[strlen(object.getAddress()) + 1];
	strcpy(address, object.getAddress());
	
	phoneNumber = new char[strlen(object.getPhoneNumber()) + 1];
	strcpy(phoneNumber, object.getPhoneNumber());
	
	creditCardNumber =  object.getCreditCardNumber();
	
	bankAccount = new char[strlen(object.getBankAccount()) + 1];
	strcpy(bankAccount, object.getBankAccount());
	
	setTotalPurchaseSum(object.getTotalPurchaseSum());
  }
  Customer::~Customer() {
	delete[] name;
	delete[] surname;
	delete[] patronymic;
	delete[] address;
	delete[] phoneNumber;
	delete[] bankAccount;
  }
  Customer::Customer(const char* pName, const char* pSurname, const char* pPatronymic, const char* pAddress, //только ради фичи ++11
	  const char* pPhone, const unsigned pCredit, const char* pBank, const int total) {
		name = new char[strlen(pName) + 1];
		strcpy(name, pName);
		
		surname = new char[strlen(pSurname) + 1];
		strcpy(surname, pSurname);
		
		patronymic = new char[strlen(pPatronymic) + 1];
		strcpy(patronymic, pPatronymic);
		
		address = new char[strlen(pAddress) + 1];
		strcpy(address, pAddress);
		
		phoneNumber = new char[strlen(pPhone) + 1];
		strcpy(phoneNumber, pPhone);
		
		creditCardNumber = pCredit;
		
		bankAccount = new char[strlen(pBank) + 1];
		strcpy(bankAccount, pBank);
		
		setTotalPurchaseSum(total);
		
	  }
  void Customer::show(std::ostream& stream) const { //большая и скучная функция: алгоритмов - 0
	if(name != nullptr) {
	  stream << "Name: " << name << " | ";
	} else {
	  stream << "Name is not filled | ";
	}
	if(surname  != nullptr) {
	  stream << "Surname: " << surname << " | ";
	} else {
	  stream << "Surname is not filled | ";
	}
	if(patronymic != nullptr) {
	  stream << "Patronymic: " << patronymic << " | ";
	} else {
	  stream << "Patronymic is not filled | ";
	}
	if(address != nullptr) {
	  stream << "Address: " << address << " | ";
	} else {
	  stream << "Address is not filled | ";
	}
	if(phoneNumber != nullptr) {
	  stream << "Phone number: " << phoneNumber << " | ";
	} else {
	  stream << "Phone number is not filled | ";
	}
	
	stream << "Credit card number: " << creditCardNumber << " | ";
	
	if(bankAccount != nullptr) {
	  stream << "Bank account: " << bankAccount << " | ";
	} else {
	  stream << "Bank account is not filled | ";
	}
	if(totalPurchaseSum != -1) {
	  stream << "Total purchase sum: " << totalPurchaseSum << " |\n";
	} else {
	  stream << "Total purchase sum is not filled |\n";
	}
  }
  bool Customer::operator<(const Customer& op2) const {
	if(this->getName() == nullptr) return true;
	if(op2.getName() == nullptr) return false;
	if(strcmp(this->getName(), op2.getName()) < 0) return true;
	if(strcmp(this->getName(), op2.getName()) > 0) return false;
	
	if(this->getSurname() == nullptr) return true;
	if(op2.getSurname() == nullptr) return false;
	if(strcmp(this->getSurname(), op2.getSurname()) < 0) return true;
	if(strcmp(this->getSurname(), op2.getSurname()) > 0) return false;
	
	if(this->getPatronymic() == nullptr) return true;
	if(op2.getPatronymic() == nullptr) return false;
	if(strcmp(this->getPatronymic(), op2.getPatronymic()) < 0) return true;
	if(strcmp(this->getPatronymic(), op2.getPatronymic()) > 0) return false;
  }
  std::istream &operator>>(std::istream &stream, Customer& obj) {
	std::string temp;
	int tempI;
	stream >> temp;
	obj.setName(temp.c_str());
	stream >> temp;
	obj.setSurname(temp.c_str());
	stream >> temp;
	obj.setPatronymic(temp.c_str());
	stream >> temp;
	obj.setAddress(temp.c_str());
	stream >> temp;
	obj.setPhoneNumber(temp.c_str());
	stream >> tempI;
	obj.setCreditCardNumber(tempI);
	stream >> temp;
	obj.setBankAccount(temp.c_str());
	stream >> tempI;
	obj.setTotalPurchaseSum(tempI);
	return stream;
  }
  const char* Customer::getName() const {
	return name;
  }
  void Customer::setName(const char* pArgName) {
	if(pArgName != nullptr) {
		if(initSet::initialIsOk(pArgName)){
		  delete [] name;
		  name = new char[strlen(pArgName) + 1];
		  strcpy(name, pArgName);
		  initSet::normaliseInit(name);
		} else {
		  std::cout << "Error: Wrong format of name" << std::endl;
		}
	} else {
	  std::cout << "Error: Cannot set empty name" << std::endl;
	}
  }
  const char* Customer::getSurname() const {
	return surname;
  }
  void Customer::setSurname(const char* pArgSurname) {
	if(pArgSurname != nullptr) {
	  if(initSet::initialIsOk(pArgSurname)) {
		delete [] surname;
		surname = new char[strlen(pArgSurname) + 1];
		strcpy(surname, pArgSurname);
		initSet::normaliseInit(surname);
	  } else {
		std::cout << "Error: Wrong format of surname" << std::endl;
	  }
	} else {
	  std::cout << "Error: Cannot set empty surname" << std::endl;
	}
  }
  const char* Customer::getPatronymic() const {
	return patronymic;
  }
  void Customer::setPatronymic(const char* pArgPatronymic) {
	if(pArgPatronymic != nullptr) {
	  if(initSet::initialIsOk(pArgPatronymic)) {
		delete [] patronymic;
		patronymic = new char[strlen(pArgPatronymic) + 1];
		strcpy(patronymic, pArgPatronymic);
		initSet::normaliseInit(patronymic);
	  } else {
		std::cout << "Error: Wrong format of patronymic" << std::endl;
	  }
	} else {
	  std::cout << "Error: Cannot set empty patronymic" << std::endl;
	}
  }
  const char* Customer::getAddress() const {
	return address;
  }
  void Customer::setAddress(const char* pArgAddress) {
	if(pArgAddress != nullptr) {
	  delete [] address;
	  address = new char[strlen(pArgAddress) + 1];
	  strcpy(address, pArgAddress);
	} else {
	  std::cout << "Error: Cannot set empty address" << std::endl;
	}
  }
  const char* Customer::getPhoneNumber() const {
	return phoneNumber;
  }
  void Customer::setPhoneNumber(const char* pArgPhone) {
	if(pArgPhone != nullptr) {
	  delete [] phoneNumber;
	  phoneNumber = new char[strlen(pArgPhone) + 1];
	  strcpy(phoneNumber, pArgPhone);
	} else {
	  std::cout << "Error: Cannot set empty phone" << std::endl;
	}
  }
  unsigned Customer::getCreditCardNumber() const {
	return creditCardNumber;
  }
  void Customer::setCreditCardNumber(const unsigned pArgCredit) {
	creditCardNumber = pArgCredit;
  }
  const char* Customer::getBankAccount() const {
	return bankAccount;
  }
  void Customer::setBankAccount(const char* pArgBank) {
	if(pArgBank != nullptr) {
	  delete [] bankAccount;
	  bankAccount = new char[strlen(pArgBank) + 1];
	  strcpy(bankAccount, pArgBank);
	} else {
	  std::cout << "Error: Cannot set empty bank account" << std::endl;
	}
  }
  const int Customer::getTotalPurchaseSum() const {
	return totalPurchaseSum;
  }
  void Customer::setTotalPurchaseSum(const int argTotal) {
	if(argTotal > 0) {
	  totalPurchaseSum = argTotal;
	} else {
	  std::cout << "Error: Cannot set negative total purchase sum" << std::endl;
	}
  }

} //end of namespace hw4
