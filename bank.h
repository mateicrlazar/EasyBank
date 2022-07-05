#pragma once
#include "customer.h"

class Bank
{
private:
	Customer* customers[1001];
	int customer_count;
public:
	Bank(void);
	void operator+=(Customer* customer);
	void operator-=(char* name);
	void SortCustomersByName(void);
	void FindACustomer(char* customer_name);
	void CreateCardNumber(Customer* customer);
	void CreateStringCardNumber(Customer* customer);
	void CreateExpirationMonth(Customer* customer);
	void CreateExpirationYear(Customer* customer);
	void CreateCVV(Customer* customer);
	void CreatePIN(Customer* customer);
	void CreateSold(Customer* customer);
	void ShowAllCustomersInfo();
	Customer* AuthCustomerLogin(char* card, int pin);
	void ProcessTransfer(Customer* customer, char* receiver_card, double sum);
};