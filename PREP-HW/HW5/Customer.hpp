#pragma once
#include <iostream>
#include <cstring>
namespace hw4 {
class Customer {
public:
  Customer();
  ~Customer();
  Customer(const char* pName, const char* pSurname, const char* pPatronymic, const char* pAddress,
	  const char* pPhone, const unsigned pCredit, const char* pBank, const int total);
  Customer(const Customer& object);
  void show(std::ostream& stream) const;
  bool operator<(const Customer& op2) const;
  friend std::istream &operator>>(std::istream &stream, Customer& obj);
  
  //геттеры и сеттеры
  const char* getName() const;
  void setName(const char* pArgName);
  const char* getSurname() const;
  void setSurname(const char* pArgSurname);
  const char* getPatronymic() const;
  void setPatronymic(const char* pArgPatronymic);
  const char* getAddress() const;
  void setAddress(const char* pArgAddress);
  const char* getPhoneNumber() const;
  void setPhoneNumber(const char* pArgPhone);
  unsigned getCreditCardNumber() const;
  void setCreditCardNumber(const unsigned pArgCredit);
  const char* getBankAccount() const;
  void setBankAccount(const char* pArgBank);
  const int getTotalPurchaseSum() const;
  void setTotalPurchaseSum(const int argTotal);
  
  
private:
  char* name;
  char* surname;
  char* patronymic;
  char* address;
  char* phoneNumber;
  unsigned creditCardNumber;
  char* bankAccount;
  int totalPurchaseSum;
};
}