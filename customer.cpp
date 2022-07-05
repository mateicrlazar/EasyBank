#include <iostream>
#include "customer.h"

Customer::Customer(char* _name)
{
	int i = 0;
	while (_name[i] != '\0')
	{
		name[i] = _name[i];
		i++;
	}
}

const char* Customer::GetName(void)
{
	return name;
}

void Customer::GetCardInfo(void)
{
	std::cout << "\nCard Number: " << string_card_number << '\n';
	std::cout << "Expiration Date: " << expiration_month << '/' << expiration_year << '\n';
	std::cout << "CVV: " << cvv << '\n';
}

void Customer::GetSold(void)
{
	std::cout << "\nYou currently have " << sold << " EBC left!\n";
}

void Customer::IncreaseSold(double sum)
{
	std::cout << '\n';
	if (sum < 0 || sum > 4000)
		std::cout << "Please enter a valid sum!\n";
	else
	{
		sold += sum;
		std::cout << "You just added " << sum << " EBC to your sold!\n";
	}
}

void Customer::WithdrawCash(double sum)
{
	std::cout << '\n';
	if (sum < 0 || sum > 4000)
		std::cout << "Please withdraw a valid sum!\n";
	else if (sold - sum < 0)
		std::cout << "No sufficient funds for this withdrawal!\n";
	else
	{
		sold -= sum;
		std::cout << "You just withdrew " << sum << " EBC from your sold!\n";
	}
}

void Customer::UpdatePIN(int pin)
{
	std::cout << '\n';
	if (pin < 1000 || pin > 9999)
		std::cout << "You set an invalid PIN! Try again.\n";
	else
	{
		card_pin = pin;
		std::cout << "Your new PIN is " << pin << "!\n";
	}
}

void Customer::ProcessPendingTransfers(void)
{
	if (pending_transfers.no_of_transfers == 0)
		std::cout << "\nNo pending transfers available!\n";
	else
	{
		std::cout << "\nProcessing your tranfers...\n";
		while (pending_transfers.no_of_transfers > 0)
		{
			std::cout << pending_transfers.senders[pending_transfers.no_of_transfers - 1] << " sent you " << pending_transfers.sums[pending_transfers.no_of_transfers - 1] << " EBC!\n";
			sold += pending_transfers.sums[pending_transfers.no_of_transfers - 1];
			pending_transfers.no_of_transfers--;
		}
	}
}