#include <iostream>
#include <string.h>
#include "bank.h"
#include "customer.h"

char* CreateFullName(char* first_name, char* last_name)
{
    char customer_name[101] = "";
    int n = strlen(first_name);
    for (int i = 0; i < n; i++)
        customer_name[i] = first_name[i];
    customer_name[n] = ' ';
    for (int i = 0; i < strlen(last_name); i++)
        customer_name[n + 1 + i] = last_name[i];
    return customer_name;
}

int main()
{
    Bank my_bank;
    const char* admin_password = "admin"; 
    const char admin_queries[][25] = { "1. Add New Customer", "2. Delete Customer", "3. Show All Customers", "4. Find A Customer", "0. Exit" };
    const char customer_queries[][25] = { "1. Get Full Card Info", "2. See Current Sold", "3. Deposit Cash" , "4. Withdraw Cash", "5. Update Card PIN", "6. Credit Transfer", "7. See Pending Requests", "0. Exit" };
    std::cout << "Developed by Lazar Cristian-Matei\nHello! This is our bank system. All you have to do is follow our instructions everytime we ask you to.\n\n";
    short query;
    std::cout << "Who are you?\n1. Admin\n2. Customer\n";
    std::cout << "Type in the number of the preferred instruction: ";
    std::cin >> query;
    do
    {
        int admin_tries = 0, user_tries = 0;
        switch (query)
        {
        case 1:
            do
            {
                char password[16];
                std::cout << "Please enter the special admin password: ";
                std::cin >> password;
                admin_tries++;
                if (strcmp(password, admin_password) != 0)
                    std::cout << "Wrong password! Try again! You don't have many attempts left...\n";
                else
                    do
                    {
                        std::cout << "\n";
                        char first_name[51], last_name[51];
                        std::cout << "Hey, Admin! What do you want to do?\n";
                        for (int i = 0; i < 5; i++)
                            std::cout << admin_queries[i] << '\n';
                        std::cout << "Type in the number of the preferred instruction: ";
                        std::cin >> query;
                        switch (query)
                        {
                        case 0:
                            std::cout << "\nQuitting session...\n";
                            query = 0;
                            break;
                        case 1:
                            std::cout << "\nWhat's his name?\n";
                            std::cout << "First name: ";
                            std::cin >> first_name;
                            std::cout << "Last name: ";
                            std::cin >> last_name;
                            my_bank += new Customer(CreateFullName(first_name, last_name));
                            my_bank.SortCustomersByName();
                            break;
                        case 2:
                            std::cout << "Which customer do you want to delete?\n";
                            std::cout << "First name: ";
                            std::cin >> first_name;
                            std::cout << "Last name: ";
                            std::cin >> last_name;
                            my_bank -= (CreateFullName(first_name, last_name));
                            my_bank.SortCustomersByName();
                            break;
                        case 3:
                            my_bank.ShowAllCustomersInfo();
                            break;
                        case 4:
                            std::cout << "Which customer do you want to find?\n";
                            std::cout << "First name: ";
                            std::cin >> first_name;
                            std::cout << "Last name: ";
                            std::cin >> last_name;
                            my_bank.FindACustomer(CreateFullName(first_name, last_name));
                            break;
                        default:
                            std::cout << "Wrong option! Try again...\n";
                            break;
                        }
                    } while (query >= 1 && query <= 4);
                    if (admin_tries == 4)
                        std::cout << "Your session has been disconnected, there were too many unsuccessful attempts!\n";
            } while (admin_tries < 4 && query != 0);
            break;
        case 2:
            do
            {
                char card[10];
                char receiver_card[10];
                Customer* user = nullptr;
                int pin;
                int pin2;
                double sum;
                std::cout << "\nPlease enter your card number: ";
                std::cin >> card;
                std::cout << "Please enter your card PIN: ";
                std::cin >> pin;
                user_tries++;
                user = my_bank.AuthCustomerLogin(card, pin);
                if (user)
                    do
                    {
                        std::cout << '\n';
                        std::cout << "Welcome, " << user->GetName() << "! " << "What do you want to do?\n";
                        for (int i = 0; i < 8; i++)
                            std::cout << customer_queries[i] << '\n';
                        std::cout << "Type in the number of the preferred instruction: ";
                        std::cin >> query;
                        switch (query)
                        {
                        case 0:
                            std::cout << "\nQuitting session...\n";
                            query = 0;
                            break;
                        case 1:
                            user->GetCardInfo();
                            break;
                        case 2:
                            user->GetSold();
                            break;
                        case 3:
                            std::cout << "Type in a sum of money between 1 and 4000: ";
                            std::cin >> sum;
                            user->IncreaseSold(sum);
                            break;
                        case 4:
                            std::cout << "Type in a sum of money between 1 and 4000: ";
                            std::cin >> sum;
                            user->WithdrawCash(sum);
                            break;
                        case 5:
                            std::cout << "Enter a new PIN that has to be four-digits long: ";
                            std::cin >> pin;
                            std::cout << "Type it again in order to confirm: ";
                            std::cin >> pin2;
                            if (pin == pin2)
                                user->UpdatePIN(pin);
                            else
                                std::cout << "Incorrect! Try again.\n";
                            break;
                        case 6:
                            std::cout << "Please type in the receiver's credit card number: ";
                            std::cin >> receiver_card;
                            std::cout << "Please enter the amount of sum you want to transfer him: ";
                            std::cin >> sum;
                            my_bank.ProcessTransfer(user, receiver_card, sum);
                            break;
                        case 7:
                            user->ProcessPendingTransfers();
                            break;
                        default:
                            std::cout << "Wrong option! Try again...\n";
                            break;
                        }
                    } while (query >= 1 && query <= 7);
                if (user_tries == 10)
                    std::cout << "Your session has been disconnected, there were too many unsuccessful attempts!\n";
            } while (user_tries < 10 && query != 0);
            break;
        default:
            std::cout << "\nYou pressed a wrong key! Quitting session...\n";
            break;
        }
        std::cout << "\nDo you want to do something else?\n1. Yes\n0. No\n";
        std::cout << "Type in the number of the preferred instruction: ";
        std::cin >> query;
        if (query == 1)
        {
            std::cout << "\nWho are you?\n1. Admin\n2. Customer\n";
            std::cout << "Type in the number of the preferred instruction: ";
            std::cin >> query;
        }
        else
        {
            std::cout << "\nAlright, goodbye and thank you for using our services! Feel free to use them whenever you want!\nPress 1 if you want to login as an admin!\nPress 2 if you want to login as a customer!\n";
            do
            {
                std::cin >> query;
            } while (query != 1 && query != 2);
        }
    } while (true);
    return 0;
}