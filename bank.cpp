#include "bank.h"
#include <iostream>
#include <cstdlib>
#include <string.h>

Bank::Bank(void)
{
	for (int i = 0; i < 1001; i++)
		customers[i] = nullptr;
	customer_count = 0;
}

void Bank::operator+=(Customer* customer)
{
	bool should_add_customer = true;
	const char *current_customer = customer->name;
	for (int i = 0; i < customer_count && should_add_customer; i++)
		if (strcmp(current_customer, customers[i]->name) == 0)
		{
			std::cout << "The user " << current_customer << " already exists!\n";
			delete customer;
			should_add_customer = false;
		}
	if (should_add_customer)
	{
		CreateCardNumber(customer);
		CreateStringCardNumber(customer);
		CreateExpirationMonth(customer);
		CreateExpirationYear(customer);
		CreateCVV(customer);
		CreatePIN(customer);
		CreateSold(customer);
		std::cout << "Hello, " << customer->name << "! Your credit card number is " << customer-> string_card_number << " and the PIN is " << customer->card_pin << "!\n";
		customers[customer_count] = customer;
		customer_count++;
	}
}

void Bank::operator-=(char* name)
{
	int i = 0;
	while (i < customer_count)
		if (strcmp(name, customers[i]->name) == 0)
		{
			std::cout << customers[i]->name << "'s account was deleted from our database!\n";
			delete customers[i];
			for (int j = i + 1; j < customer_count; j++)
				customers[j - 1] = customers[j];
			break;
		}
		else
			i++;
	if (i == customer_count)
		std::cout << "The requested user doesn't exist!\n";
	else
		customer_count--;
}

void Bank::SortCustomersByName(void)
{
	bool is_sorted;
	Customer* aux;
	do
	{
		is_sorted = true;
		for (int i = 0; i < customer_count - 1; i++)
			if (strcmp(customers[i]->name, customers[i + 1]->name) > 0)
			{
				aux = customers[i];
				customers[i] = customers[i + 1];
				customers[i + 1] = aux;
				is_sorted = false;
			}
	} while (!is_sorted);
}

void Bank::FindACustomer(char* customer_name)
{
	int left = 0, right = customer_count - 1, mid, search;
	do
	{
		mid = (left + right) / 2;
		search = strcmp(customer_name, customers[mid]->name);
		if (search == 0)
		{
			std::cout << "\nHere are some details about " << customers[mid]->name << ':';
			customers[mid]->GetCardInfo();
			return;
		}
		else if (search > 0)
			left = mid + 1;
		else
			right = mid - 1;
	} while (left <= right);
	std::cout << "\nWe didn't find this customer in our database!\n";
	return;
}

void Bank::CreateCardNumber(Customer* customer)
{
	bool is_valid;
	int possible_number;
	do
	{
		is_valid = true;
		possible_number = rand() % 89999999 + 10000000;
		for (int i = 0; i < customer_count; i++)
			if (customers[i]->card_number == possible_number)
				is_valid = false;
	} while (!is_valid);
	customer->card_number = possible_number;
}

void Bank::CreateStringCardNumber(Customer* customer)
{
	int card_number_copy = customer->card_number;
	for (int i = 8; i >= 0; i--)
		if (i != 4)
		{
			customer->string_card_number[i] = (card_number_copy % 10) + '0';
			card_number_copy = card_number_copy / 10;
		}
		else
			customer->string_card_number[4] = '-';
}

void Bank::CreateExpirationMonth(Customer* customer)
{
	customer->expiration_month = rand() % 12 + 1;
}

void Bank::CreateExpirationYear(Customer* customer)
{
	customer->expiration_year = rand() % 4 + 2022;
}

void Bank::CreateCVV(Customer* customer)
{
	customer->cvv = rand() % 899 + 100;
}

void Bank::CreatePIN(Customer* customer)
{
	customer->card_pin = rand() % 8999 + 1000;
}

void Bank::CreateSold(Customer* customer)
{
	customer->sold = 0.0;
}

void Bank::ShowAllCustomersInfo()
{
	std::cout << '\n';
	for (int i = 0; i < customer_count; i++)
	{
		std::cout << "Customer " << i + 1 << ": " << customers[i]->name << '\n';
		std::cout << "Card Number: " << customers[i]->string_card_number << '\n';
		std::cout << "Expiration Date: " << customers[i]->expiration_month << '/' << customers[i]->expiration_year << '\n';
		std::cout << "CVV: " << customers[i]->cvv << '\n';
		std::cout << "Card PIN: " << customers[i]->card_pin << '\n';
		std::cout << "Sold: " << customers[i]->sold << "\n\n";
	}
	if (customer_count == 0)
		std::cout << "Our database is empty at this moment!\n";
}

Customer* Bank::AuthCustomerLogin(char* card, int pin)
{
	for (int i = 0; i < customer_count; i++)
		if (strcmp(card, customers[i]->string_card_number) == 0)
		{
			if (pin == customers[i]->card_pin)
				return customers[i];
			std::cout << "Wrong PIN! Try again.\n";
			return nullptr;
		}
	std::cout << "Didn't find your card number in the database!\n";
	return nullptr;
}

void Bank::ProcessTransfer(Customer* customer, char* receiver_card, double sum)
{
	for (int i = 0; i < customer_count; i++)
		if (strcmp(receiver_card, customers[i]->string_card_number) == 0)
		{
			if (sum > customer->sold)
			{
				std::cout << "No sufficient funds for this transfer!\n";
				return;
			}
			customer->sold -= sum;
			customers[i]->pending_transfers.sums[customers[i]->pending_transfers.no_of_transfers] = sum;
			int n = strlen(customer->name);
			for (int j = 0; j <= n; j++)
				customers[i]->pending_transfers.senders[customers[i]->pending_transfers.no_of_transfers][j] = customer->name[j];
			customers[i]->pending_transfers.no_of_transfers++;
			std::cout << "Your transfer was completed successfully!\n";
			return;
		}
	std::cout << "We didn't find the receiver in our database! Try again.\n";
	return;
}