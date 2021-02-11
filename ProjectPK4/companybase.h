
#pragma once
#include "checking.h"
#include "company.h"
#include "employeebase.h"
#include "strategy.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <cstddef>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

#ifndef COMPANYBASE_H_
#define COMPANYBASE_H

extern int company_Amount;

#endif
class Strategy;
class EmployeeBase;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class responsible for task management for employee base
class CompanyBase : public Strategy {

protected:
	std::list <Company*> NumberComBase; // List in ascending order , increasing numbers
	vector <string> elements; // Vector, used during iniciacion of the employee
	EmployeeBase* employee_base;
public:
	// Constructor
	CompanyBase();
	// Deconstructor
	~CompanyBase();

	void set_base (EmployeeBase* pbase); // Set a base

	// Main functions 
	bool loadbase(vector <string> elements) override; // Load a company base from a .txt file
	bool savebase(std::ostream& outfile) override; // Save a company base to a .txt file
	void deletebase() override; // Delete a existing data base

	// Functions avaiable for user
    // Company functions
	void add_company(); // Add a company to the data base
	Company * find_company(int number, int &index); // Return a index of company in a list
	bool delete_company(); // Delete a company from the data base
	bool show_companies(); // Show full list of the companies
	void set_payments(); // Set a status payments

	// Workplace functions
	bool add_workplace(); // Adding a new workplace to the company
	bool show_workplace(); // Show a workplace details
	bool delete_workplace(); // Deleting a workplace from company
    bool show_workplaces(); // Show a all workplaces


    // Employee functions
	bool addemployeetoworkplace(); // Adding a employee to a workplace
	bool deleteemployeefromworkplace(); // Deleting a employee from a workplace
	Employee* findemployee(Workplace* pworklace); // Find a employee
	Workplace * deleteemp(int number,int pemp, int &index); // Finding a employee
	void deleteemployee(Workplace * ptr,int index); // Deleting a employee

    //Managment function
	bool help() override; // Show help information

	friend class Contex;
};

