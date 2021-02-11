#pragma once
#include "checking.h"
#include "companybase.h"
#include "employee.h"
#include "strategy.h"

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;



// Payment class
// Class using the details from class Employee and Company. It is independent, so it means that if a employee will be delated from base data, 
// the person will be still in payments. If you want to cancel his payment, he has to be deleted from payment queue or be paid :)
class Payment
{
protected:
	string com_Name;
	int emp_No;
	string emp_Name;
	string emp_Surname;
	string emp_AccountNo;
	double payment_Rate; 
	int payment_Hours; // Amount of hours
	double payment_Amount; // Amount to pay

public:
	// Constructors
	Payment (string pcom_Name, int pemp_No, string pName, string pSurname, string pAccountNo, double pRate, int pHours);
		
	Payment(string pcom_Name, int pemp_No, string pName, string pSurname, string pAccountNo, double pRate, int pHours, double pAmount) :
		com_Name(pcom_Name), emp_No(pemp_No), emp_Name(pName), emp_Surname(pSurname), emp_AccountNo(pAccountNo), payment_Rate(pRate),
		payment_Hours(pHours), payment_Amount(pAmount) {};

	// Deconstuctor
	~Payment();

	// Friend classes
	friend class PaymentQueue;
	friend std::ostream& operator<<(std::ostream& outfile, const Payment& ppayment); // Declaration of friendship with operator << which is overloaded

	std::ostream& savepayment(std::ostream& outfile) const; // Save to the file all details

	void topay_details(); // Show only important details to pay
	void payment_details(); // Showing all payments details
};

// Queue of payments class
class PaymentQueue : public Strategy
{
protected:
	std::list <Payment*> payments; // Queue of payments to do
	vector <string> elements; // Vector, used during iniciacion of the payments
	CompanyBase* company_base;
	IntCompany* office_base;
public:
	// Constructor
	PaymentQueue();
	// Deconstuctor
	~PaymentQueue();

	// Main functions 
	bool loadbase(vector <string> elements) override; // Load a payment base from a .txt file
	bool savebase(std::ostream& outfile) override; // Save a payment base to a .txt file
	void deletebase() override; // Delete the existing payment base

	// Functions avaiable for user
	void set_base(CompanyBase* pbase, IntCompany* obase); // Set a base
	void companypayment(); // Adding employees from company to the payment list
	void officepayment(); // Adding employee from office to the payment list
	bool addpayment(); // Add a payment for one employee
	Payment* findpayment(int number, int& index); // Find a payment in list
	void deletepayment(); // Delete a payment from the list
	void showallpayment(); // Show full list of payment
	void newpaylist(); // Create new paylist

	//Managment function
	bool help() override;  // Show help information
};

