#pragma once
#include "employee.h"


#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class workplace
class Workplace {

protected:
	string workplace_Name; // Name of the workplace
	vector <Employee*> workplace_Employees; // Base of employees working on workplace 
public:
	// Friend classes
	friend class Company;
	friend class CompanyBase;
	friend class PaymentQueue;

	// Constructor
	Workplace(string pName);
	// Deconstructor
	~Workplace();

	string workplace_name(); // Return a name of the workplace
	void show_workplace(); // Show workplace details
	void add_employee(Employee* pemployee); // Adding a employee to workplace
	bool delete_employee (); // Deleting a employee from workplace

};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ExtCompany class 
class Company {

protected:
	int company_No;
	// Number of the company. Different numbers for external companies - construction employees.
	string company_Name;  // Name of the company
	double workplace_t1Rate; // Rate per h for Supervise
	double workplace_t2Rate; // Rate per h for Carpenter
	vector <Workplace*> company_Workplaces; // Base of workplaces
	int payment_status; // Payment status
public:

	// Constructor
	Company(string pName, double pt1Rate, double pt2Rate); 
	// Deconstuctor
	~Company();

	std::ostream& savecompany(std::ostream& outfile) ; // Save to the file all company details
	std::ostream& saveworkplaces(std::ostream& outfile);

	friend std::ostream& operator<<(std::ostream& outfile, Company& pcompany); // Declaration of friendship with operator << which is overloaded

	// Main functions 
	string company_name(); // Return a company name
	void set_company_number(int pnumber); // Set a company number
	void company_show(); // Show all company details


	// Workplace functions
	void add_workplace(Workplace* pworkplace); // Function which add a workplace
	Workplace* find_workplace(int number); // Function which finding a workplace
	void delete_workplace(vector <Workplace*>::iterator pitr, int pindex);
	void delete_workplaces(); // Function which delete a workplace 
	void setstatus(); // Function which set status of payment
	int getstatus(); // Function which return status of payment

	// Friend classes
	friend class Workplace;
	friend class CompanyBase;
	friend class PaymentQueue;
};




