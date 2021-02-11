#include "employeebase.h"
#include "employee.h"



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Abstract class constructor
Employee::Employee(int pNoType,int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount)
{
	employee_No = pNo;
	employee_NoType = pNoType;
	employee_Name = pName;
	employee_Surname = pSurname;
	employee_Date = pDate;
	employee_Sex = pSex;
	employee_PhoneNo = pPhone;
	employee_AccountNo = pAccount;
	employee_Status = 0;
	employee_CompanyNo = 9999;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function which shows all employee details
void Employee::employee_details()

{
	cout << endl;
	cout << "EMPLOYEE DETAILS " << endl << endl << endl;

	cout << "NAME: " << this->employee_Name << endl << endl;

	cout << "SURNAME: " << this->employee_Surname << endl << endl;

	cout << "DATE OF BIRTH: " << this->employee_Date[0] << this->employee_Date[1] << "." << this->employee_Date[2] << this->employee_Date[3] << ".";
	for (int i = 4; i < 8; i++)
	{
		cout << this->employee_Date[i];
	}
	cout << endl << endl;

	cout << "SEX: ";
	if (this->employee_Sex == 1) {
		cout << "FEMALE";
	}
	else {
		cout << "MALE";
	}
	cout << endl << endl;

	cout << "PHONE NUMBER: " << this->employee_PhoneNo << endl << endl;

	cout << "ACCOUNT NUMBER: "<< this->employee_AccountNo << endl << endl;

	cout << "TYPE OF WORK: ";
	switch (employee_NoType)
	{
	case 1: { cout << "SUPERVISE \n\n"; break; }
	case 2: { cout << "CARPENTER \n\n"; break; }
	case 3: { cout << "MANAGER \n\n"; break; }
	case 4: { cout << "ACCOUNT \n\n"; break; }
	case 5: { cout << "DRIVER \n\n"; break; }
	}
	
}

// Show surname and name of the employee
void Employee::employee_names()
{
	cout << this->employee_Surname << "  " << this->employee_Name << endl;
}

// Return a surname of the employee
string Employee::employee_surname()
{
	return employee_Surname;
}

// Set a employee number
void Employee::set_employee_number(int pNumber)
{
	employee_No = pNumber;
}

// Set a employee status
void Employee::set_employee_status(bool status)
{
	employee_Status = status;
}

void Employee::set_employee_comanyno(int nnumber)
{
	employee_CompanyNo = nnumber; 
}

// Return a employee number 
int Employee::employee_number()
{
	return employee_No;
}

// Return a type of employee
int Employee::employee_type()
{
	return employee_NoType;
}

// Return a status of employee
int Employee::employee_status()
{ 
	return employee_Status;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constuction class constructor
Construction::Construction(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount,string pCSCSNo)
	:Employee(pNoType, pNo, pName, pSurname, pDate, pSex, pPhone, pAccount)
{
    con_CSCSNo = pCSCSNo;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function which shows all construction details
void Construction::con_details()
{
	cout << "CSCS NUMBER: "<< this->con_CSCSNo << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Office class constructor
Office::Office(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount, string pINo, string pTaxCode, string pCompanyPhoneNo)
	:Employee(pNoType, pNo, pName, pSurname, pDate, pSex, pPhone, pAccount)
{
	office_INo = pINo;
	office_TaxCode = pTaxCode;
	office_CompanyPhoneNo = pCompanyPhoneNo;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function which shows all office details
void Office::office_details()
{
	cout << "INSURANCE NUMBER: " << this->office_INo << endl << endl;
	cout << "TAX CODE: " << this->office_TaxCode << endl << endl;
	cout << "COMPANY PHONE NUMBER: "<< this->office_CompanyPhoneNo << endl << endl;
}

/***********************************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Supervise class constructor
Supervise::Supervise(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount, string pCSCSNo,int pOverseen, string pCompanyPhoneNo) :
	Construction(pNoType, pNo, pName, pSurname, pDate, pSex, pPhone, pAccount, pCSCSNo)
{
	employee_NoType = 1;
	sup_Oversee = pOverseen;
	sup_CompanyPhoneNo = pCompanyPhoneNo;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function which shows all details
void Supervise::employee_show()
{
	this->employee_details();
	this->con_details();

	cout << "OVERSEEN AMOUNT ON WORKPLACE: " << this->sup_Oversee << endl << endl;
	cout << "COMPANY PHONE NUMBER: " << this->sup_CompanyPhoneNo << endl << endl;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save to the file all details
std::ostream& Supervise::save(std::ostream& outfile) const
{
	outfile << con_CSCSNo << ";" + std::to_string(sup_Oversee) << ";" << sup_CompanyPhoneNo << ";";
	return outfile;
}

//-----------------------------------------------------------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Carpenter class constructor
Carpenter::Carpenter(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount, string pCSCSNo, int pNVQLevel)
	: Construction( pNoType, pNo, pName, pSurname, pDate, pSex, pPhone, pAccount, pCSCSNo)
{
	employee_NoType = 2;
	carpenter_NVQLevel = pNVQLevel;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function which shows all details
void Carpenter::employee_show()
{
	this->employee_details();
	this->con_details();
	cout << "NVQ LEVEL: " << this->carpenter_NVQLevel << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save to the file all details
std::ostream& Carpenter::save(std::ostream& outfile) const
{
	outfile << con_CSCSNo << ";" << std::to_string(carpenter_NVQLevel) << ";";
	return outfile;
}

//-----------------------------------------------------------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Manager class constructor
Manager::Manager(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount, string pINo, string pTaxCode, string pCompanyPhoneNo, int pQtyProjects, int pOwnCar)
	:Office (pNoType, pNo ,pName, pSurname, pDate, pSex, pPhone, pAccount, pINo, pTaxCode, pCompanyPhoneNo)
{
	employee_NoType = 3;
	manager_QtyProjects = pQtyProjects;
	manager_OwnCar = pOwnCar;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function which shows all details
void Manager::employee_show()
{

	this->employee_details();
	this->office_details();
	cout << "QUANTITY OF ONGOING PROJECTS: " << this->manager_QtyProjects << endl << endl;
	cout << "OWN CAR: ";
	if (this->manager_OwnCar == 1) {
		cout << "YES" << endl << endl;
	}
	else {
		cout << "NO" << endl << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save to the file all details
std::ostream& Manager::save(std::ostream& outfile) const
{
	outfile << office_INo << ";" << office_TaxCode << ";" << office_CompanyPhoneNo << ";" << std::to_string(manager_QtyProjects) << ";" << std::to_string(manager_OwnCar) << ";";
	return outfile;
}

//-----------------------------------------------------------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Account class constructor
Account::Account(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount, string pINo, string pTaxCode, string pCompanyPhoneNo, string pCompany, int pOversee)
	:Office(pNoType, pNo, pName, pSurname, pDate, pSex, pPhone, pAccount, pINo, pTaxCode, pCompanyPhoneNo)
{
	employee_NoType = 4;
	acc_Company = pCompany;
	acc_Oversee = pOversee;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function which shows all details
void Account::employee_show()
{
	this->employee_details();
	this->office_details();
	cout << "OVERSEEN COMPANY: " << this->acc_Company << endl << endl;
	cout << "OVERSEEN AMOUNT OF PEOPLE: " << this->acc_Oversee << endl << endl;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save to the file all details
std::ostream& Account::save(std::ostream& outfile) const
{
	outfile << office_INo << ";" << office_TaxCode << ";" << office_CompanyPhoneNo << ";" << acc_Company << ";" << std::to_string(acc_Oversee) << ";";
	return outfile;
}

//-----------------------------------------------------------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver class constructor
Driver::Driver(int pNoType, int pNo, string pName, string pSurname, string pDate, char pSex, string pPhone, string pAccount, string pINo, string pTaxCode, string pCompanyPhoneNo, int pOwnCar, string pCategory, string pExpiryData)
	:Office(pNoType, pNo, pName, pSurname, pDate, pSex, pPhone, pAccount, pINo, pTaxCode, pCompanyPhoneNo)
{
	employee_NoType = 5;
	driver_OwnCar = pOwnCar;
	driver_Category = pCategory;
    driver_ExpiryData = pExpiryData;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function which shows all details
void Driver::employee_show()
{
	this->employee_details();
	this->office_details();

	cout << "OWN CAR: ";
	if (driver_OwnCar == 1) {
		cout << "YES" << endl << endl;
	}
	else {
		cout << "NO" << endl << endl;
	}

	cout << "DRIVING LICENCE CATEGORY: " << this->driver_Category << endl << endl;

	cout << "EXPIRY DATE " << this->driver_ExpiryData[0] << this->driver_ExpiryData[1] << "." << this->driver_ExpiryData[2] << this->driver_ExpiryData[3] << ".";
	for (int i = 4; i < 8; i++)
	{
		cout << this->driver_ExpiryData[i];
	}
	cout << endl << endl;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save to the file all details
std::ostream& Driver::save(std::ostream& outfile) const
{
	outfile << office_INo << ";" << office_TaxCode << ";" << office_CompanyPhoneNo << ";" << std::to_string(driver_OwnCar) << ";" + driver_Category << ";" << driver_ExpiryData << ";";
	return outfile;
}

//-----------------------------------------------------------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Overloaded operator << which saves all employee details to the file

std::ostream& operator<<(std::ostream& outfile, const Employee & pemployee)
{
	outfile << pemployee.employee_NoType << ";"<<pemployee.employee_No<<";"<< pemployee.employee_Name << ";" << pemployee.employee_Surname << ";" << pemployee.employee_Date << ";";
	if (pemployee.employee_Sex == 1) {
				outfile << "true";
			}
	else {
				outfile << "false";
			}
	outfile << ";";
	outfile << pemployee.employee_PhoneNo << ";" << pemployee.employee_AccountNo << ";";
	
	pemployee.save(outfile);
	outfile << endl;
	
	return outfile;
}

