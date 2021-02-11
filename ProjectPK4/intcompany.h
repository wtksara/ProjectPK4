#pragma once
#include "employee.h"
#include "employeebase.h"
#include "strategy.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

class EmployeeBase;
class IntCompany : public Strategy {
private:
	string intcompany_Name;  // Name of the company
	double workplace_t3Rate; // Rate per h for Manager 
	double workplace_t4Rate; // Rate per h for Account
	double workplace_t5Rate; // Rate per h for Driver
	vector <Employee*> intcompany_Employees; // Base of employees working on internal company
	vector <string> elements; // Vector, used during iniciacion of the employee
	EmployeeBase* employee_base;

public:
	// Constructor
	IntCompany();
	// Deconstructor
	~IntCompany();

	// Main functions 
	bool loadbase(vector <string> elements) override; // Load a company base from a .txt file
	bool savebase(std::ostream& outfile) override; // Save a company base to a .txt file
	void deletebase() override; // Delete a existing data base

	// Functions avaiable for user
	void setdetails(string pName, double pt3Rate, double pt4Rate, double pt5Rate);
	void setbase(EmployeeBase* pemployee_base); // Set a base
	string intcompany_name(); // Return a internal company name
	void add_officeemployee(); // Add a employee to office base
	Employee* find_officeemployee(int number); // Find a employee 
	void show_allemployees(); // Show all office employees
	void delete_officeemployee(); // Delete a employee from office base
	void intcompany_show(); // Show all internal company details

	void update(int pnumber);// Update after deleting a employee
    //Managment function
	bool help() override; // Show help information

	std::ostream& saveintcompany(std::ostream& outfile) const ; // Save to the file all details
	friend std::ostream& operator<<(std::ostream& outfile, const IntCompany& pcompany); // Declaration of friendship with operator << which is overloaded
	friend class PaymentQueue;
};