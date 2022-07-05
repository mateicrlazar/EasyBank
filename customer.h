#pragma once

class Customer
{
private:
	char name[51] = "";
	int card_number;
	char string_card_number[10] = "";
	int expiration_month;
	int expiration_year;
	int cvv;
	int card_pin;
	double sold;
	struct
	{
		int no_of_transfers = 0;
		double sums[31] = { 0 };
		char senders[31][51];
	} pending_transfers;
public:
	Customer(char* _name);
	const char* GetName(void);
	void GetCardInfo(void);
	void GetSold(void);
	void UpdatePIN(int pin);
	void IncreaseSold(double sum);
	void WithdrawCash(double sum);
	void ProcessPendingTransfers(void);
	friend class Bank;
};