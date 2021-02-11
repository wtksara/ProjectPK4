#pragma once
#include "employee.h"
#include "companybase.h"
#include "strategy.h"
#include "intcompany.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <cstddef>

#ifndef EMPLOYEEBASE_H_
#define EMPLOYEEBASE_H

extern int employee_Amount;

#endif

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

class IntCompany;
class CompanyBase;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class responsible for task management for employee base
class EmployeeBase : public Strategy {

protected:
	std::list <Employee*> SurnameBase; // List in alfabetical order
	std::list <Employee*> NumberBase; // List in ascending order , increasing numbers
	vector <string> elements; // Vector, used during iniciacion of the employee
	IntCompany* office_base;
	CompanyBase* company_base;

public:
    // Constructor
	EmployeeBase();
	// Deconstructor
	~EmployeeBase();

	// Main functions 
	void set_base(IntCompany* poffice ,CompanyBase* pbase); // Set a base
	bool loadbase(vector <string> elements) override; // Load a employee base from a .txt file
	bool savebase(std::ostream& outfile) ; // Save a employee base to a .txt file
	void deletebase(); // Delete a existing data base

	// Funcions available for user
	void addemployee(); // Add a employee to data base
	Employee* findemployee(int number, int& index); // Return employee in a list
	bool deleteemployee(); // Delete a employee from the data base
	bool showemployees(); // Show full list of the employees 
	bool showemployeesbyclass(); // Show list of the employees by kind of work

    // Managment function
	bool help() override; // Show help information

	/***********************************************************************************************************************************/
    // Additional functions
	void addtolist(); // Function, which add employee do the list
	void check(); // Function which check the all details
	void findindex ( Employee* pptr); // Function, which find a index for new employee
	Employee* findbynumber(int number); // Find employee by his number
	friend class Contex;

};

