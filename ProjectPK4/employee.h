#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

// Data base which includes employees who work in England

// Abstract class 
class Employee
{
protected:
	int employee_No; // Individual employee number
	int employee_NoType; // Number of the type of work 
	string employee_Name; // Name of the employee
	string employee_Surname; // Surname of the employee
	string employee_Date; // Date of birth in format DD/MM/YYYY
	bool employee_Sex; // Sex of the employee true for Female, false for Man
	string employee_PhoneNo; // Phone number
	string employee_AccountNo; // Account number
	bool employee_Status; // Status of employee - working somewhere or no
	int employee_CompanyNo; // Number of the company

public:

	// Friendship
	friend class EmployeeBase; // Declaration of friendship with a class EmployeeBase

	friend std::ostream& operator<<(std::ostream& outfile, const Employee& pemployee); // Declaration of friendship with operator << which is overloaded

	// Constructor
	Employee(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount);

	// Deconstructor
	virtual ~Employee() {};

	// Abstract functions
	void virtual employee_show() = 0; // Show all details

	virtual std::ostream& save(std::ostream& outfile) const = 0; // Save to the file all details

	// Functions

	void employee_details(); // Show all employee details
	void employee_names(); // Show surname and name of the employee
	string employee_surname(); // Return a surname of the employee
	void set_employee_number( int pNumber); // Set a employee number
	void set_employee_status(bool status); // Set a employee status
	void set_employee_comanyno(int nnumber); // Set a company number
	int employee_number(); // Return a employee number 
	int employee_type (); // Return a type of employee
	int employee_status(); // Return a status of employee
	
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inheriting class 2 level
// Class which includes employees who are working on the construction site
class Construction : public Employee
{
protected:
	string con_CSCSNo; // CSCS Card number, which allows employee to work on construction site

public:
	// Constructor
	Construction(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount,
		string pCSCSNo);

	// Destruktor
	virtual ~Construction() {};

	// Abstract functions
	void virtual employee_show() = 0; // Show all details

	virtual std::ostream& save(std::ostream& outfile) const = 0;  // Save to the file all details

	// Functions
	void con_details(); // Show all construction details

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inheriting class 2 level
// Class which includes employees who are working at the office 
class Office : public Employee
{
protected:
	string office_INo; // Insurance Number allow to work legally in UK
	string office_TaxCode; // Tax code    typical 1250L where 1250 is the amount tax free
	// Types of the letters on the end
	// L - Standart tax free   ;    NT - No Tax  
	// If you have more than one job
	// BR - Basic rate   ;    D0 - Higher rate
	string office_CompanyPhoneNo; // Company phone number

public:
	// Constructor
	Office(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount,
		string pINo, string pTaxCode, string pCompanyPhoneNo);

	// Destruktor
	virtual ~Office() {};

	// Abstract functions
	void virtual employee_show() = 0; // Show all details

	virtual std::ostream& save(std::ostream& outfile) const = 0; // Save to the file all details

   // Functions
	void office_details(); // Show all office details
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inheriting class from Construction 3 level 
class Supervise : public Construction
{
protected:
	int sup_Oversee;  // Amount of the employees overseen on the workplace
	string sup_CompanyPhoneNo; // Company phone number

public:
	// Friendship
	friend class PaymentQueue; // Declaration of friendship with a class PaymentQueue

	// Constructor
	Supervise(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount,
		string pCSCSNo, int pOverseen, string pCompanyPhoneNo);

	// Destruktor
	~Supervise() {};

	// Override functions
	void  employee_show() override; // Show all details of the employee

	std::ostream& save(std::ostream& outfile) const override; // Save to the file all details
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inheriting class from Construction 3 level 
class Carpenter : public Construction
{
protected:
	int carpenter_NVQLevel; // Level of the Speciality

public:
	// Friendship
	friend class PaymentQueue; // Declaration of friendship with a class PaymentQueue

	// Constructor
	Carpenter(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount,
	     string pCSCSNo, int pNVQLevel);

	// Destruktor
	~Carpenter() {};

	// Override functions
	void  employee_show() override; // Show all details of the employee

	std::ostream& save(std::ostream& outfile) const override; // Show all details of the employee
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inheriting class from Office 3 level 
class Manager : public  Office
{
protected:
	int manager_QtyProjects; // Amount of the ongoing projects
	int manager_OwnCar; // Own Car or Comapny one

public:
	// Friendship
	friend class PaymentQueue; // Declaration of friendship with a class PaymentQueue

	// Constructor
	Manager(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount,
		string pINo, string pTaxCode, string pCompanyPhoneNo, int pQtyProjects, int pOwnCar);

	// Destruktor
	~Manager() {};

	// Overide functions
	void  employee_show() override; // Show all details of the employee

	std::ostream& save(std::ostream& outfile) const override; // Show all details of the employee
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inheriting class from Office 3 level 
class Account : public  Office
{
protected:
	string acc_Company; // Overseen company
	int acc_Oversee; // Amount of the employees overseen 

public:
	// Friendship
	friend class PaymentQueue; // Declaration of friendship with a class PaymentQueue

	// Constructor
	Account(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount,
		 string pINo, string pTaxCode, string pCompanyPhoneNo, string pCompany, int pOversee);

	// Destruktor
	~Account() {};

	// Overide functions
	void  employee_show() override; // Show all details of the employee

	std::ostream& save(std::ostream& outfile) const override; // Show all details of the employee
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inheriting class from Office 3 level 
class Driver : public  Office
{
protected:
	int driver_OwnCar; // Own Car or Comapny one
	string driver_Category; // Category of the driving licence
	string driver_ExpiryData;// Expiry date of the driving licence

public:
	// Friendship
		friend class PaymentQueue; // Declaration of friendship with a class PaymentQueue
	// Constructor
	Driver(int pNoType , int pNo,string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount,
	     string pINo, string pTaxCode, string pCompanyPhoneNo, int pOwnCar, string pCategory, string pExpiryData);

	// Destruktor
	~Driver() {};

	// Overide functions
	void employee_show() override; // Show all details of the employee

	std::ostream& save(std::ostream& outfile) const override; // Show all details of the employee
};
