#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <vector>
#include <sstream>
#include "Customer.h"
#include "Transaction.h"

/**
The Bank has Accounts and an Account belongs to a Customer.
Additionally, there are specialized types of accounts: Checking_Account and Savings_Account.
Checking_Account and Savings_Account have specialized ways of adding interest, and describing itself.

@author: Ed Walker
*/

class Account {
protected:
	Customer *customer;		// The customer who owns this account
	double balance;			// The available balance in this account
	int account_number;		// A unique number identifying this account
	std::vector<Transaction *> transactions;  // The record of transactions that have occured with this account

	/**
	Describe fees associated with the customer who owns this account.
	The fee will depend on the specific type of customer.
	@return string showing checking and overdraft fees
	*/
	std::string get_fees()
	{
		int overdraft, charge;

		// Polymorphism: calls the correct virtual methods from the specific customer type
		// FIXME: Get the overdraft and check charge information from this accounts customer
		overdraft = customer->PENALTY_FOR_OVERDRAFT(); 
		charge = customer->CHECK_CHARGES();
		std::stringstream ss;
		ss << "Check Charge: " << charge << " Overdraft Fee: " << overdraft;
		return ss.str();
	}

protected:
	/**
	Add interest based on a specified interest rate to account
	@param interest	The interest rate
	*/
	void add_interest(double interest) {
		double amt = balance*interest;
		balance = balance + amt;
		std::string fees = get_fees();
		Transaction *tran = NULL;

		// FIXME: Create a Transaction object and assign it to the transaction vector.
		tran = new Transaction(customer->getCustomerNumber(), type, amt, fees);
		transactions.push_back(tran);
	}

public:
	/**
	Constructor requires a customer to create an account
	Balance always starts with 0 when account is created.
	*/
	Account(Customer *cust, int id) : customer(cust), account_number(id), balance(0) {}

	/**
	Generic accesser and setter methods for properties customer, balance, and account_number
	*/

	Customer *get_customer() {
		return customer;
	}

	void set_customer(Customer *cust) {
		customer = cust;
	}

	int get_account() {
		return account_number;
	}

	void set_balance(double new_balance) {
		balance = new_balance;
	}

	void set_account(int account_number) {
		this->account_number = account_number;
	}

	double get_balance() {
		return balance;
	}

	/**
	Generic method describing the account information.

	Remember that you will need to indicate if an account is Savings or Checking in 
	an overridden version of to_string() in the derived classes. 

	@return string describing generic information about the account
	*/
	virtual std::string to_string() {
		std::stringstream ss; // for composing the string that describes this account

		// FIXME: Add information about the customer who owns this account.
		ss << " Customer Name: " << customer->getCustomerName() << endl;
		ss << " Customer ID: " << customer->getCustomerNumber() << endl;
		ss << "  Balance: " << balance << std::endl;
		ss << "  Account ID: " << account_number << std::endl;
		return ss.str();
	}

	/**
	Deposits amount into account
	@param amt The deposit amount
	*/
	virtual void deposit(double amt) {
		balance += amt;
		std::string fees = get_fees();
		Transaction *tran = NULL;
		std::string transaction_type = "Deposit";

		// FIXME: Create a Transaction object and assign it to transaction vector.
		tran = new Transaction(customer->getCustomerNumber(), transaction_type, amt, fees);

		transactions.push_back(tran);
	}

	/**
	Withdraws amount from account
	@param amt The withdrawal amount
	*/
	virtual void withdraw(double amt) {
	if (balance - amt >= 0) //if amount withdrew minus balance is more than or equal to 0, transaction is processed.
	{	
		balance -= amt;
		std::string fees = get_fees();
		Transaction *tran = NULL;
		std::string transaction_type = "Withdrawal";

		// FIXME: Create a Transaction object and assign it to tran.
		tran = new Transaction(customer->getCustomerNumber(), transaction_type, amount, fees);

		transactions.push_back(tran);
	} else {
		cout << "Not enough funds in your current balance." << endl;
		//If the person tries to withdraw more than what is in their account, transaction does not go through.
	}

	// We want the Savings_Account and Checking_Account to implement this.
	virtual void add_interest() = 0;

};

class CheckingAccount : public Account 
{
	public:
		//Checking Account constructor
		CheckingAccount(Customer *cust, int id) : Account(cust, id) 
		{
			balance = 0;
			customer = cust;
			account_number = id;
		}

		virtual std::string to_string() 
		{
			std::stringstream ss; // for composing the string that describes this account

			// FIXME: Add information about the customer who owns this account.
			ss << " Customer Name: " << customer->getCustomerName() << endl;
			ss << " Customer ID: " << customer->getCustomerNumber() << endl;
			ss << "Account Type: Checking" << endl;
			ss << "  Balance: " << balance << std::endl;
			ss << "  Account ID: " << account_number << std::endl;
			return ss.str();
		}
		
		void AddingInterest() //Adding interest on top of current balance in checking account. 
		{
			double interest = customer->INTEREST_FOR_CHECKING();
			double amount = balance*interest;
			balance = balance+amount;
			string fees = get_fees();
			string type = "Interest";
			int cust_num = customer->getCustomerNumber();
			Transaction *tran = NULL;
			//Creating a new transaction object and appends new transaction into the transactions vector
			tran = new Transaction(cust_num, type, amount, fees);
			transactions.push_back(tran);
		}

		virtual void deposit(double amt) //Deposits amount of money into the checking account.
		{
			balance += amt;
			string fees = get_fees();
			string type = "Deposit";
			int cust_num = customer->getCustomerNumber();
			Transaction *tran = NULL;
			//Creating a new transaction object and appends new transaction into the transactions vector
			tran = new Transaction(cust_num, type, amount, fees);
			transactions.push_back(tran);
		}

		virtual void withdraw(double amt) //Withdraws amount of money from checking account.
		{
			if (balance - amt >= 0) //If the amount of money requested to withdraw from the balance results in balance to be greater than or equal to 0, transaction will go through.
			{
				balance -= amt;
				string fees = get_fees();
				string type = "Withdrawal";
				int cust_num = customer->getCustomerNumber();
				Transaction *tran = NULL;
				//Creating a new transaction object and appends new transaction into the transactions vector
				tran = new Transaction(cust_num, type, amt, get_fees());
				transactions.push_back(tran);
			} else {
				cout << "Not enough funds in your account. " << endl;
				//Withdrawal transaction will not process if user tries to request more than what is currently available in the checking account.
			}
		}
};

class SavingsAccount : public Account 
{
	public:
		//Savings account constructor
		SavingsAccount(Customer *cust, int id) : Account(cust, id) 
		{
			balance = 0;
			customer = cust;
			account_number = id;
		}

		virtual std::string to_string() 
		{
			std::stringstream ss; // for composing the string that describes this account

			// FIXME: Add information about the customer who owns this savings account.
			ss << " Customer Name: " << customer->getCustomerName() << endl;
			ss << " Customer ID: " << customer->getCustomerNumber() << endl;
			ss << "Account Type: Savings" << endl;
			ss << "  Balance: " << balance << std::endl;
			ss << "  Account ID: " << account_number << std::endl;
			return ss.str();
		}
		
		void AddingInterest() //adds interest onto amount in savings account
		{
			double interest = customer->INTEREST_FOR_SAVINGS();
			double amount = balance*interest;
			balance = balance+amount;
			string fees = get_fees();
			string type = "Interest";
			int cust_num = customer->getCustomerNumber();
			Transaction *tran = NULL;
			//Creating a new transaction object and appends new transaction into the transactions vector
			tran = new Transaction(cust_num, type, amount, fees); 
			transactions.push_back(tran);
		}

		virtual void deposit(double amt) //deposits amount of money into savings account
		{
			balance += amt;
			string fees = get_fees();
			string type = "Deposit";
			int cust_num = customer->getCustomerNumber();
			Transaction *tran = NULL;
			//Creating a new transaction object and appends new transaction into the transactions vector
			tran = new Transaction(cust_num, type, amount, fees);
			transactions.push_back(tran);
		}

		virtual void withdraw(double amt) //withdraws amount of money from savings account
		{
			if (balance - amt >= 0) //transaction will only happen if amount withdrawn from balance is greater than or equal to 0
			{
				balance -= amt;
				string fees = get_fees();
				string type = "Withdrawal";
				int cust_num = customer->getCustomerNumber();
				Transaction *tran = NULL;
				tran = new Transaction(cust_num, type, amt, get_fees());
				transactions.push_back(tran);
			} else {
				std::cout << "Not enough funds in your account. " << endl;
				//If user tries to take out more than what is available in their account, the transaction will not go through.
			}
		}
}

#endif