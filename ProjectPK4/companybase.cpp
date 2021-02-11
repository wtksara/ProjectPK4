#include "companybase.h"
#include "company.h"
#include <regex>

#include <string>
#include <sstream>
#include <stdlib.h>

using std::string;
using std::regex;

int company_Amount = 0; // Global variable for company number

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
CompanyBase::CompanyBase() {
	employee_base = nullptr;
}

// Deconstructor
CompanyBase::~CompanyBase()
{
	deletebase();
	NumberComBase.clear();
	elements.clear();
	employee_base = nullptr;
}

// Set a base
void CompanyBase::set_base(EmployeeBase* pbase)
{
	this->employee_base = pbase;
}

// Load a company base from a .txt file
bool CompanyBase::loadbase(vector <string> pelements)
{
	std::smatch matching;
	// Matching the string 
	regex pattern("(.*?)(!)(.*)");
	if (regex_match(pelements[0], matching, pattern)) {}

	// Searching the first string which include a company details
	std::smatch scom;
	string sname = matching[1];

	regex spattern("[a-zA-Z0-9.]+");
	while (regex_search(sname, scom, spattern)) {
		for (auto x : scom) elements.push_back(x);
		sname = scom.suffix().str();
	}
	double pworkplace_t1Rate = atof(elements[1].c_str());
	double pworkplace_t2Rate = atof(elements[2].c_str());
	Company* pcompany = new Company(elements[0], pworkplace_t1Rate, pworkplace_t2Rate);
	NumberComBase.push_back(pcompany); // Adding to list in ascending order

	elements.clear();

	// Searching for workplace details
	std::smatch swork;
	string sworkname = matching[3];

	regex spatternwork("[a-zA-Z0-9!]+"); // Seperete workplaces
	while (regex_search(sworkname, swork, spatternwork)) {
		for (auto x : swork)  elements.push_back(x);
		sworkname = swork.suffix().str();
	}

	for (int i = 0; i < elements.size(); i++) {
		Workplace* ptr = new Workplace(elements[i]);
		pcompany->company_Workplaces.push_back(ptr);
		    int j = i + 1;
			while (elements[j] != "!") {
				int number = atoi(elements[j].c_str());
				Employee* emp = employee_base->findbynumber(number);
				emp->set_employee_status(1);
				emp->set_employee_comanyno(pcompany->company_No);
				ptr->workplace_Employees.push_back(emp);
				j++;
			}
			i = j;
	}
	elements.clear();
	return true;
}

// Save a company base to a .txt file
bool CompanyBase::savebase(std::ostream& outfile)
{
	outfile << "#";
	for (std::list <Company*>::iterator itr = NumberComBase.begin(); itr != NumberComBase.end(); itr++) {
			Company * ptr = *itr;
			outfile << *ptr;
	}
	
	return true;
}

// Delete a existing data base /// TUTAJ BLAD
void CompanyBase::deletebase()
{
	for (std::list <Company*>::iterator itr = NumberComBase.begin(); itr != NumberComBase.end(); itr++) {
			Company* ptr = *itr;
			ptr->delete_workplaces();
			delete ptr; // Delete a company
	}
	NumberComBase.clear();
	company_Amount = 0;
	this->elements.clear();
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Add a company to the data base
void CompanyBase::add_company()
{
	elements.clear();
	cout << "                            ADD A COMPANY" << endl;
	string line;
	double pworkplace_t1Rate = 0.0;
	double pworkplace_t2Rate = 0.0;

	cout << "NAME:  ";   cin >> line;
	if (stringcheck(line) == true) { elements.push_back(line); }

    cout << "RATE FOR SUPERVISE:  ";  cin >> line;
	if (numbercheck(line, 1) == true) { pworkplace_t1Rate = atof(line.c_str()); }
	
	cout << "RATE FOR CARPENTER:  ";  cin >> line;
	if (numbercheck(line, 1) == true) { pworkplace_t2Rate = atof(line.c_str()); }

	Company * pcompany = new Company (elements[0], pworkplace_t1Rate, pworkplace_t2Rate);
	NumberComBase.push_back(pcompany); // Adding to list in ascending order
}

// Return a index of company in a list
Company* CompanyBase::find_company(int number, int& index)
{
	if (NumberComBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO COMPANIES IN A BASE DATA " << endl;
		return nullptr;
	}
	else {
		show_companies();
		string pname;
		cout << "                            FIND A COMPANY BY NAME " << endl;
		cout << "                            ENTER THE NAME :" << endl;
		cin >> pname;
		if (stringcheck(pname) == true) {};

		const char* name = pname.c_str();
		for (std::list <Company*>::iterator itr = NumberComBase.begin(); itr != NumberComBase.end(); itr++) {
			Company* ptr = *itr;

			string ptrname = ptr->company_name();
			const char* psurnamekey = ptrname.c_str();
			if ((_stricmp(name, psurnamekey) == 0))
			{
				if (number == 1) { // For showing all details
					ptr->company_show();
				}
				return ptr;
			}
			index++;
		}
		cout << "                            THE COMPANY HASN'T BEEN FOUND IN BASE DATA" << endl;
		return nullptr;
	}
}

// Delete a company from the data base
bool CompanyBase::delete_company()
{
	if (NumberComBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO COMPANIES IN A BASE DATA " << endl;
		return false;
	}
	else {
		std::list<Company*>::iterator check = NumberComBase.begin(); // Iterator 
		cout << "                            DELETING A COMPANY FROM THE DATEBASE " << endl;
		int index = 0;
		Company* ptr = find_company(0,index);
		if (ptr!=nullptr) {

		    std::list<Company*>::iterator itr = NumberComBase.begin(); // Iterator 
	
			advance(itr, (index)); // Founding a right company 
			NumberComBase.erase(itr); // Delete a company from the list

			itr = NumberComBase.begin();
			advance(itr, (index)); // Going to the point, where the last item has been deleted
		
			delete ptr; // Delete a company

			cout << "                            THE COMPANY HAS BEEN DELETED FROM DATEBASE " << endl;
		}
		else {
			cout << "                            NO COMPANY IN A BASE DATA " << endl;
			return false;

		}
		return true;
	}
}

// Show full list of the companies
bool CompanyBase::show_companies()
{
	if (NumberComBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO COMPANIES IN A BASE DATA " << endl;
		return false;
	}
	else {

		int i = 1;
		for (std::list <Company*>::iterator itr = NumberComBase.begin(); itr != NumberComBase.end(); itr++) {
			Company* ptr = *itr;
			cout << i << ". ";
			string pname = ptr->company_name();
			cout << pname << endl;
			i++;
		
		}
		return true;
	}
}

// Set a status payments
void CompanyBase::set_payments()
{
	for (std::list <Company*>::iterator itr = NumberComBase.begin(); itr != NumberComBase.end(); itr++) {
		Company* ptr = *itr;
		ptr->payment_status = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Workplace functions

// Adding a new workplace to the companyEmployee
bool CompanyBase::add_workplace()
{
	if (NumberComBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO COMPANIES IN A BASE DATA " << endl;
		return false;
	}
	else {

		cout << "                            LIST OF COMPANIES" << endl << endl;
		int index = 0;
		Company* ptr = find_company(0,index);

		if (ptr!=nullptr) {

			cout << "                            INSERT THE NAME OF WORKPLACE" << endl << endl;
			string line;
			cin >> line;
			if (stringcheck(line) == true) {}
			Workplace* newworkplace = new Workplace(line); // Creating new workplace
			ptr->add_workplace(newworkplace); // Adding workplace to the list of workplaces
		}
		return true;
	}
}
 
// Show a workplace details
bool CompanyBase::show_workplace()
{
	if (NumberComBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO COMPANIES IN A BASE DATA " << endl;
		return false;
	}
	else {

		cout << "                            LIST OF COMPANIES" << endl << endl;
		int index = 0;
		Company* ptr = find_company(0, index);
		if (ptr != nullptr) {
			Workplace* place = ptr->find_workplace(1);
			if (place == nullptr) {
				cout << "                            WRONG NAME OF THE PLACE" << endl << endl;
				return false;
			}
		}
		return true;
	}
}

// Deleting a workplace from company
bool CompanyBase::delete_workplace()
{
	if (NumberComBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO COMPANIES IN A BASE DATA " << endl;
		return false;
	}
	else {

		cout << "                            LIST OF COMPANIES" << endl << endl;
		int index = 0;
		Company* ptr = find_company(0,index);
		if (ptr!=nullptr) {
			ptr->find_workplace(2);
		}
		return true;
	}
}

// Show a workplace details
bool CompanyBase::show_workplaces()
{
	if (NumberComBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO COMPANIES IN A BASE DATA " << endl;
		return false;
	}
	else {

		cout << "                            LIST OF COMPANIES" << endl << endl;
		int index = 0;
		Company* ptr = find_company(0, index);
		if (ptr != nullptr) {
			index = 1;
			for (std::vector <Workplace*>::iterator itr = ptr->company_Workplaces.begin(); itr != ptr->company_Workplaces.end(); itr++) {
				Workplace* place = *itr;
				string name = place->workplace_name();
				cout <<index <<". "<< name << endl;
				index++;
			}
			return true;
		}
		else {
			return false;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Adding a employee to a workplace
bool CompanyBase::addemployeetoworkplace()
{
	if (NumberComBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO COMPANIES IN A BASE DATA " << endl;
		return false;
	}
	else {
		int index = 0;
		Company* ptr = find_company(0, index);
		if (ptr!=nullptr) {
			Workplace * place = ptr->find_workplace(0);
			if (place != nullptr) {
				system("cls");
				Employee* pemployee = employee_base->findemployee(3,index);
				if (pemployee != nullptr) {
					int status = pemployee->employee_status();
					if (status != 1) {
						pemployee->set_employee_status(1);
						pemployee->set_employee_comanyno(ptr->company_No);
						place->add_employee(pemployee);
						return true;
					}
					else {
						cout << "                            THAT EMPLOYEE IS ALREADY ON DIFFERENT WORKPLACE" << endl;
						return false;
					}
				}
				else {
					cout << "                            NO THAT EMPLOYEE IN BASE DATA" << endl;
					return false;
				}
			}
			else {
				return false;
			}
		}
		return false;
	}
}

// Deleting a employee from a workplace
bool CompanyBase::deleteemployeefromworkplace()
{
	if (NumberComBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO COMPANIES IN A BASE DATA " << endl;
		return false;
	}
	else {
		cout << "                            LIST OF COMPANIES" << endl << endl;
		int index = 0;
		Company* ptr = find_company(0, index);
		if (ptr != nullptr) {

			Workplace* place = ptr->find_workplace(1);
			if (place != nullptr) {
				cout << "                            REMEMBER THAT YOU ARE DELETING A PERSON ONLY FROM A WORKPLACE" << endl << endl;
				place->delete_employee();
			}
		}
		return true;
	}
}

// Find a employee
Employee* CompanyBase::findemployee( Workplace * pworklace)
{
	vector <Employee*> vec;
	vector <int> indexes;
	if (pworklace->workplace_Employees.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO EMPLOYEES IN A INTERNAL COMPANY BASE " << endl;
		return nullptr;
	}
	else {
		cout << "                            ENTER THE SURNAME OF THE EMPLOYEE \n";
		string surname;
		cin >> surname;
		if (stringcheck(surname) == true) {};
		const char* psurname = surname.c_str();
		int i = 0;
		for (std::vector <Employee*>::iterator pitr = pworklace->workplace_Employees.begin(); pitr != pworklace->workplace_Employees.end(); pitr++) {
			Employee* person = *pitr;
			string ptrsurname = person->employee_surname();
			const char* psurnamekey = ptrsurname.c_str();
			if ((_stricmp(psurname, psurnamekey) == 0))
			{
				if ((_stricmp(psurname, psurnamekey) == 0))
				{
					vec.push_back(person);
					indexes.push_back(i);
				}
				i++;
			}
		}

		if (vec.empty() == true) {
			cout << "                            THE EMPLOYEE HASN'T BEEN FOUND IN BASE DATA" << endl;
			return nullptr;
		}
		else {
			////////////////////////////////////////////////////////////////////////////////////////////////////////
				cout << "                            THE LIST OF THE PEOPLE WITH THAT SURNAME" << endl;
				int i = 1;
				for (std::vector <Employee*>::iterator pitr = vec.begin(); pitr != vec.end(); pitr++) {
					Employee* patr = *pitr;
					cout << i << ". ";
					patr->employee_names();
					i++;
				}
				cout << "                            CHOOSE THE PERSON. INSERT THE NUMBER" << endl;
				int n;
				if (choiceforemp(n, i) == true) {
					int n1 = n - 1;
					return vec[n1];
				}
			}
		
	}
}

// Finding a employee
Workplace* CompanyBase::deleteemp(int number, int pemp, int &index)
{
	for (std::list <Company*>::iterator itr = NumberComBase.begin(); itr != NumberComBase.end(); itr++) {
		Company* ptr = *itr;
		if (ptr->company_No == number) {
			for (std::vector <Workplace*>::iterator pitr = ptr->company_Workplaces.begin(); pitr != ptr->company_Workplaces.end(); itr++) {
				Workplace* place = *pitr;
				for (std::vector <Employee*>::iterator patr = place->workplace_Employees.begin(); patr != place->workplace_Employees.end(); itr++) {
					Employee* emp = *patr;
					if (emp->employee_number() == pemp) {
						return place;
					}
					index++;
				}
			}
		}
	}
}

// Deleting a employee
void CompanyBase::deleteemployee(Workplace* ptr, int index)
{
	std::vector<Employee*>::iterator patr = ptr->workplace_Employees.begin();
	advance(patr, (index)); // Founding a right person 
	ptr->workplace_Employees.erase(patr);
}

// Show help information
bool CompanyBase::help()
{
	cout << endl;
	cout << "                            AVAIABLE OPTIONS" << endl << endl;
	cout << "                            1.ADD COMPANY " << endl;
	cout << "                            2.FIND COMPANY " << endl;
	cout << "                            3.DELETE COMPANY " << endl;
	cout << "                            4.SHOW FULL LIST OF COMPANY" << endl;
	cout << "                            5.ADD WORKPLACE TO COMPANY " << endl;
	cout << "                            6.FIND WORKPLACE AND SHOW DETAILS " << endl;
	cout << "                            7.DELETE WORKPLACE FROM COMPANY " << endl;
	cout << "                            8.SHOW ALL WORKPLACES " << endl;
	cout << "                            9.ADD EMPLOYEE TO WORKPLACE " << endl;
	cout << "                            10.DELETE EMPLOYEE FROM WORKPLACE " << endl;
	cout << "                            11.BACK TO MENU " << endl << endl;
	cout << "                            CHOOSE A NUMBER OF THE OPTION " << endl;

	int number;
	if (choice(number) == true) {

		switch (number)
		{
		case 1:
		{
			system("cls");
			add_company();
			return true;
			break;
		}
		case 2:
		{
			system("cls");
			int index = 0;
			find_company(1,index);
			return true;
			break;
		}
		case 3:
		{
			system("cls");
			delete_company();
			return true;
			break;
		}
		case 4:
		{
			system("cls");
			show_companies();
			return true;
			break;
		}
		case 5:
		{
			system("cls");
			add_workplace();
			return true;
			break;
		}
		case 6:
		{
			system("cls");
			show_workplace();
			return true;
			break;
		}
		case 7:
		{
			system("cls");
			delete_workplace();
			return true;
			break;
		}
		case 8:
		{
			system("cls");
			show_workplaces();
			return true;
			break;
		}
		case 9:
		{
			system("cls");
			addemployeetoworkplace();
			return true;
			break;
		}
		case 10:
		{
			system("cls");
			deleteemployeefromworkplace();
			return true;
			break;
		}
		case 11:
		{
			system("cls");
			return false;
			break;
		}
		default: {

			system("cls");
			cout << "                            TRY AGAIN PUT A NUMBER OF THE OPTION ";
			return true;
			break;
		}
		}
	}
}

