#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <string>

/**
The Bank has Customers.  Each Customer has a name, address, age, and telephone number.
Additionally, there are specialized types of Customers: Adult, Senior, and Student.
Each type of Customer has its own checking and savings interest rates, 
as well as its own checking and overdraft fees.

@author: Ed Walker
*/
class Customer // FIXME: Complete the implementation!
{
    protected:
        int age;
        std::string telephone;
        std::string address;
        std::string name;
        std::string customer_type;
        std::string account_type;
    
    public:
        int get_age() //getting age of customer
        {
            return age; 
        }

        void set_age(int age) //setting age of customer for account purposes
        {
            this->age = age;
        }

        string getCustomerName() //getting name of customer
        {
            return name;
        }

        void set_customer_name(string name) //setting name of customer for account purposes
        {
            this->name = name;
        }

        string getCustomerNumber() //getting customer's number
        {
            return customer_type;
        }

        void setCustomerNumber(int customerNumber) //setting customer's number for account purposes
        {
            this->customer_type = customerNumber;
        }

        string getTelephoneNumber() //getting telephone number of customer
        {
            return telephone;
        }

        void set_customer_phone_number(string telephone) //setting telephone number of customer for account purposes
        {
            this->telephone = telephone;
        }

        string getCustomerAddress() //getting address of customer
        {
            return address;
        }

        void set_customer_address(string address) //setting address of customer for account purposes
        {
            this->address = address;
        }

        string getCustomerType() //getting type of customer (adult, senior, or student)
        {
            return customer_type;
        }

        string getAccountType() //getting account type of customer (savings or checkings)
        {
            return account_type;
        }

        virtual double CHECK_CHARGES() = 0; //for subclasses to access (adult, student, senior) to add onto their account
        virtual double INTEREST_FOR_CHECKING() = 0; //for subclasses to access (adult, student, senior) to add onto their account
        virtual double PENALTY_FOR_OVERDRAFT() = 0; //for subclasses to access (adult, student, senior) to add onto their account
        virtual double INTEREST_FOR_SAVINGS() = 0; //for subclasses to access (adult, student, senior) to add onto their account
};

class Adult : public Customer 
{
    public:
        Adult(string name, string address, string telephone, int age, string customer_type, string account_type) : Customer(name, address, telephone, age, customer_type, account_type)
        {
            //setting constructor for adult subclass of customer
        }

        double INTEREST_FOR_CHECKING()
        {
            return 0.04; //returns the savings interest rate for regular adults
        }

        double CHECK_CHARGES()
        {
            return 2.50; //adds charges to see charges that went onto account for regular adults
        }

        double PENALTY_FOR_OVERDRAFT()
        {
            return 10.00; //returns the overdraft penalty for regular adults
        }

        double INTEREST_FOR_SAVINGS()
        {
            return 0.15; //returns the savings interest rate for regular adults
        }

}

class Student : public Customer 
{
    public:
        Student(string name, string address, string telephone, int age, string customer_type, string account_type) : Customer(name, address, telephone, age, customer_type, account_type)
        {
            //setting constructor for student subclass of customer
        }

        double INTEREST_FOR_CHECKING()
        {
            return 0.1; //returns the checking interest rate for students
        }

        double CHECK_CHARGES()
        {
            return 1.50; //adds charges to see charges that went onto account for students
        }

        double PENALTY_FOR_OVERDRAFT()
        {
            return 5.00; //returns the overdraft penalty for students
        }

        double INTEREST_FOR_SAVINGS()
        {
            return 0.30; //returns the savings interest rate for students
        }

}

class Senior : public Customer 
{
    public:
        Senior(string name, string address, string telephone, int age, string customer_type, string account_type) : Customer(name, address, telephone, age, customer_type, account_type)
        {
            //setting constructor for senior subclass of customer
        }

        double INTEREST_FOR_CHECKING()
        {
            return 0.07; //returns the checking interest rate for seniors
        }

        double CHECK_CHARGES()
        {
            return 2.25; //adds charges to see charges that went onto account for seniors
        }

        double PENALTY_FOR_OVERDRAFT()
        {
            return 7.50; //returns the overdraft penalty for seniors
        }

        double INTEREST_FOR_SAVINGS()
        {
            return 0.1; //returns the savings interest rate for seniors
        }

}


#endif