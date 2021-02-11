#include "checking.h"
#include "employeebase.h"
#include <algorithm>
 

#include <sstream>
#include <algorithm>

int employee_Amount = 0; // Global variable for employee number
using std::vector;

/***********************************************************************************************************************************/
// Managment constructor
EmployeeBase::EmployeeBase() :company_base(nullptr)
{
	this->NumberBase.clear();
	this->SurnameBase.clear();
	this->elements.clear();
	
}

// EmployeeBase deconstructor
EmployeeBase::~EmployeeBase()
{
	this->NumberBase.clear();
	this->SurnameBase.clear();
	this->elements.clear();
	company_base = nullptr;
}

// Set a base
void EmployeeBase::set_base(IntCompany* poffice ,CompanyBase* pbase)
{
	this->company_base = pbase;
	this->office_base = poffice;
}

// Load a employee base from a .txt file
bool EmployeeBase::loadbase (vector <string> pelements)
{
	elements.assign(pelements.begin(), pelements.end());
	addtolist();
	elements.clear();
	return true;
}

// Save a employee base to a .txt file
bool EmployeeBase::savebase(std::ostream& outfile)
{
	for (std::list <Employee*>::iterator itr = NumberBase.begin(); itr != NumberBase.end(); itr++) {
		Employee* ptr = *itr;
		outfile << *ptr;
	}
	return true;
}

// Delete a existing data base
void EmployeeBase::deletebase()
{
	cout << "                            DELETING THE EXISTING DATA IN PROGRAM" << endl << endl;
	
	for (std::list <Employee*>::iterator pitr = NumberBase.begin(); pitr != NumberBase.end(); pitr++) {
		Employee* emp = *pitr;
		delete emp;
	}
	NumberBase.clear();
	SurnameBase.clear();
	this->elements.clear();
	employee_Amount = 0;
}

/***********************************************************************************************************************************/
// Add a employee to data base
void EmployeeBase::addemployee()
{
	elements.clear();
	cout << "                            ADD A EMPLOYEE DETAILS " << endl;
	kindofwork();

	int number;
	if (choice(number) == true) {
		string choice = std::to_string(number);
		elements.push_back(choice);
		check();
	}
}

// Find a employee by surname
Employee* EmployeeBase::findemployee(int number, int& index)
{
	vector <int> indexes;
	vector <Employee*> vec;
	if (SurnameBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO EMPLOYEES IN A BASE DATA " << endl;
		return nullptr;
	}
	else {
		string surname;
		cout << "                            FIND A EMPLOYEE BY SURNAME " << endl;
		cout << "                            ENTER THE SURNAME " << endl;
		cin >> surname;
		if (stringcheck(surname) == true) {};
		const char* psurname = surname.c_str();
		int l = 0;
		for (std::list <Employee*>::iterator itr = SurnameBase.begin(); itr != SurnameBase.end(); itr++) {
			Employee* ptr = *itr;

			string ptrsurname = ptr->employee_surname();
			const char* psurnamekey = ptrsurname.c_str();
			if ((_stricmp(psurname, psurnamekey) == 0))
			{
				vec.push_back(ptr);
				indexes.push_back(l);
			}
			l++;
		}
		if (vec.empty() == true) {
			cout << "                            THE EMPLOYEE HASN'T BEEN FOUND IN BASE DATA" << endl;
			return nullptr;
		}
		else {
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (number == 1) { // For showing all kind of workers with that surname
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
					if (number == 1) { // For showing all details
						vec[n1]->employee_show();
					}
					index = indexes[n1];
;					return vec[n1];
				}

			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (number == 2) { // Showing office workers with that surname
				vector <Employee*> office;
				cout << "                            THE LIST OF THE PEOPLE WITH THAT SURNAME" << endl;
				int i = 1;
				for (std::vector <Employee*>::iterator pitr = vec.begin(); pitr != vec.end(); pitr++) {

					Employee* emp = *pitr;
					if (Manager* base = dynamic_cast<Manager*>(emp)) {
						office.push_back(emp);
						cout << i << ". ";
						emp->employee_names();
						i++;
					}
					else if (Account* base = dynamic_cast<Account*>(emp)) {
						office.push_back(emp);
						cout << i << ". ";
						emp->employee_names();
						i++;
					}
					else if (Driver* base = dynamic_cast<Driver*>(emp)) {
						office.push_back(emp);
						cout << i << ". ";
						emp->employee_names();
						i++;
					}
				}
				cout << "                            CHOOSE THE PERSON. INSERT THE NUMBER" << endl;
				if (office.empty() == true) {
					cout << "                            THE EMPLOYEE IS NOT FROM THAT CLASS" << endl;
					return nullptr;
				}
				else {
					int n;
					if (choiceforemp(n, i) == true) {
						int n1 = n - 1;
						if (number == 1) { // For showing all details
							office[n1]->employee_details();
						}
						return office[n1];
					}
				}
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (number == 3) { // Showing consturction workers with that surname
				vector <Employee*> construction;
				cout << "                            THE LIST OF THE PEOPLE WITH THAT SURNAME" << endl;
				int i = 1;
				for (std::vector <Employee*>::iterator pitr = vec.begin(); pitr != vec.end(); pitr++) {

					Employee* emp = *pitr;
					if (Supervise* base = dynamic_cast<Supervise*>(emp)) {
						construction.push_back(emp);
						cout << i << ". ";
						emp->employee_names();
						i++;
					}
					else if (Carpenter* base = dynamic_cast<Carpenter*>(emp)) {
						construction.push_back(emp);
						cout << i << ". ";
						emp->employee_names();
						i++;
					}
				}
				if (construction.empty() == true) {
					cout << "                            THE EMPLOYEE IS NOT FROM THAT CLASS" << endl;
					return nullptr;
				}
				else {
					cout << "                            CHOOSE THE PERSON. INSERT THE NUMBER" << endl;
					int n;
					if (choiceforemp(n, i) == true) {
						int n1 = n - 1;
						if (number == 1) { // For showing all details
							construction[n1]->employee_details();
						}
						return construction[n1];
					}
				}
			}
		}
	}
}

// Delete a employee from the data base
bool EmployeeBase::deleteemployee()
{
	if (SurnameBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO EMPLOYEES IN A BASE DATA " << endl;
		return false;
	}
	else {
		cout << "                            DELETING A EMPLOYEE FROM THE DATEBASE " << endl;
     	int index = 0;
		Employee* employee = findemployee(1,index);
		if (employee!=nullptr) {
			std::list<Employee*>::iterator l1itr = SurnameBase.begin(); // Iterator for moving in the list (alfabetical)
			std::list<Employee*>::iterator l2itr = NumberBase.begin(); // Iterator for moving in the list (in order)

			advance(l1itr, (index)); // Founding a right person in first list (alfabetical)
			SurnameBase.erase(l1itr); // Delete a person from the list

			int number = employee->employee_number(); // Checking the employee number
			int i = 0;
			for (std::list <Employee*>::iterator itr = NumberBase.begin(); itr != NumberBase.end(); itr++) {
				Employee* ptr = *itr;
				if (ptr->employee_No == number) {
					break;
				}
				i++;
			}
			advance(l2itr, (i)); // Founding a right person in second list (in order)
			NumberBase.erase(l2itr); // Delete a person from the list

			int index1 = 0;
			if (employee->employee_status() == 1) {
				if (employee->employee_CompanyNo != 9999) {
					Workplace* ptr = company_base->deleteemp(employee->employee_CompanyNo, number, index1);
					company_base->deleteemployee(ptr, index1);
				}
				else {
					office_base->update(number);
				}
			}
			delete employee; // Delete a person
		
			cout << "                            THE PERSON HAS BEEN DELETED FROM DATEBASE " << endl;
			return true;
		}
		else {
			cout << "                            THERE IS NOT THAT EMPLOYEE IN BASE DATA " << endl;
			return false;
		}
	}

}

// Show full list of the employees in alfabetical order 
bool EmployeeBase::showemployees()
{
	if ( SurnameBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO EMPLOYEES IN A BASE DATA " << endl;
		return false;
	}
	else {
		int i = 1;
		for (std::list <Employee*>::iterator itr = SurnameBase.begin(); itr != SurnameBase.end(); itr++) {
			Employee* ptr = *itr;
			cout << i << ". ";
			ptr->employee_names();
			i++;
		}
		return true;
	}
}

// Show list of the employees by kind of work
bool EmployeeBase::showemployeesbyclass()
{
	if (SurnameBase.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO EMPLOYEES IN A BASE DATA " << endl;
		return false;
	}
	else {
		kindofwork();
		int number;
		if (choice(number) == true) {

			if ((number == 5) || (number == 4) || (number == 3) || (number == 2) || (number == 1))
			{
				int i = 1;
				for (std::list <Employee*>::iterator itr = SurnameBase.begin(); itr != SurnameBase.end(); itr++) {
					Employee* ptr = *itr;
					int ptrnumber = ptr->employee_type();
					if (ptrnumber == number) {
						cout << i << ". ";
						ptr->employee_names();
						i += 1;
					} }
				return true;
			}
			else {
				cout << "                            WRONG NUMBER. TRY AGAIN" << endl;
				return false;
			}
		}
		return false;
	}
	return false;
}

/***********************************************************************************************************************************/
// Additional functions

// Function, which add employee do the list
void  EmployeeBase::addtolist()
{
	int pNumber = atoi(elements[0].c_str());
	int number = atoi(elements[1].c_str());
	employee_Amount++;
	if (number > employee_Amount) {
		employee_Amount = number;
	}
	bool pSex;
	if (elements[5] == "1") { pSex = 1; }
	else {  pSex = 0; }

	switch (pNumber) {

	    case 1: // Class supervise
	    {
		int pOverseen = atoi(elements[9].c_str());

		Employee * employee = new Supervise (pNumber, number, elements[2], elements[3], elements[4], pSex, elements[6], elements[7], elements[8], pOverseen, elements[10]);
		findindex(employee);
		break;
	    }
	    case 2: // Class carpenter 
	    {
		int pNVQLevel = atoi(elements[9].c_str());

		Employee * employee =  new Carpenter(pNumber, number, elements[2], elements[3], elements[4], pSex, elements[6], elements[7], elements[8], pNVQLevel);
		findindex(employee);
		break;
	    }
	    case 3: // Class manager
	    {
		int pQtyProjects = atoi(elements[11].c_str());
		int pOwnCar = atoi(elements[12].c_str());

		Employee* employee = new Manager(pNumber, number, elements[2], elements[3], elements[4], pSex, elements[6], elements[7], elements[8], elements[9], elements[10], pQtyProjects, pOwnCar);;
		findindex(employee);
		break;
	    }
	    case 4: // Class account
	    {
		int pOversee = atoi(elements[12].c_str());

		Employee* employee = new Account(pNumber, number, elements[2], elements[3], elements[4], pSex, elements[6], elements[7], elements[8], elements[9], elements[10], elements[11], pOversee);
		findindex(employee);
		break;
	    }
	    case 5: // Class driver
	    {
		int pOwnCar = atoi(elements[11].c_str());
		Employee* employee =new Driver(pNumber, number, elements[2], elements[3], elements[4], pSex, elements[6], elements[7], elements[8], elements[9], elements[10], pOwnCar, elements[12], elements[13]);

		findindex(employee);
		break;
	    }
	}
}

// Function, which check the all details
void  EmployeeBase::check()
{
	system("cls");
	int pNumber = atoi(elements[0].c_str());
	string line;
	string s = std::to_string(employee_Amount);
	elements.push_back(s);

	cout << "NAME:  ";   cin >> line;
	if (stringcheck(line) == true) { elements.push_back(line); }

	cout << "SURNAME:  ";   cin >> line;
	if (stringcheck(line) == true) { elements.push_back(line); }

	cout << "DATE OF BIRTH:  " << endl;
	int check;
	do { check = datecheck(line); } while (check != 1);
	elements.push_back(line);

	cout << "SEX (F or M):  ";  cin >> line;
	line = truecheck(line, 1);
	elements.push_back(line);

	cout << "PHONE NUMBER:  ";  cin >> line;
	if (numbercheck(line, 10) == true) { elements.push_back(line); }

	cout << "ACCOUNT NUMBER:  ";  cin >> line;
	if (numbercheck(line, 8) == true) { elements.push_back(line); }

	switch (pNumber)
	{
	case 1: // Class supervise
	{
		cout << "CSCS NUMBER:  ";  cin >> line;
		if (numbercheck(line, 8) == true) { elements.push_back(line); }

		cout << "AMOUNT OF OVERSEEN PEOPLE:  ";  cin >> line;
		if (numbercheck(line, 3) == true) { elements.push_back(line); }

		cout << "COMPANY PHONE NUMBER:  ";  cin >> line;
		if (numbercheck(line, 10) == true) { elements.push_back(line); }

		cout << endl;
		addtolist();

		break;
	}
	case 2: // Class carpenter 
	{
		cout << "CSCS NUMBER:  ";  cin >> line;
		if (numbercheck(line, 8) == true) { elements.push_back(line); }

		cout << "NATIONAL VOCATIONAL QUALIFICATIONS LEVEL (5 LEVELS):  ";
		line = optioncheck(2);
		while (line == "0")
		{
			line = optioncheck(2);
		}
		elements.push_back(line);
		cout << endl;
		addtolist();

		break;
	}
	case 3: // Class manager
	{
		cout << "INSURANCE NUMBER:  ";  cin >> line;
		if (numbercheck(line, 10) == true) { elements.push_back(line); }

		cout << "TAX CODE CHOOSE FROM THE LIST  " << endl;
		line = optioncheck(1);
		while (line == "0")
		{
			line.clear();
			line = optioncheck(1);
		}
		elements.push_back(line);   cout << endl;
		cout << "COMPANY PHONE NUMBER:  ";  cin >> line;
		if (numbercheck(line, 10) == true) { elements.push_back(line); }

		cout << "QUANTITY OF THE PROJECTS:  ";  cin >> line;
		if (numbercheck(line, 2) == true) { elements.push_back(line); }

		cout << "OWN CAR:  ";  cin >> line;
		line = truecheck(line, 2);
		elements.push_back(line);
		cout << endl;
		addtolist();

		break;
	}
	case 4: // Class account
	{
		cout << "INSURANCE NUMBER:  ";  cin >> line;
		if (numbercheck(line, 10) == true) { elements.push_back(line); }

		cout << "TAX CODE CHOOSE FROM THE LIST  " << endl;
		line = optioncheck(1);
		while (line == "0")
		{
			line.clear();
			line = optioncheck(1);
		}
	
		elements.push_back(line);   cout << endl;

		cout << "COMPANY PHONE NUMBER:  ";  cin >> line;
		if (numbercheck(line, 10) == true) { elements.push_back(line); }

		cout << "OVERSEEN COMPANY:  ";  cin >> line;
		if (stringcheck(line) == true) { elements.push_back(line); }

		cout << "AMOUNT OF OVERSEEN PEOPLE:  ";  cin >> line;
		if (numbercheck(line, 2) == true) { elements.push_back(line); }

		cout << endl;
		addtolist();

		break;
	}
	case 5: // Class driver
	{
		cout << "INSURANCE NUMBER:  ";  cin >> line;
		if (numbercheck(line, 10) == true) { elements.push_back(line); }

		cout << "TAX CODE CHOOSE FROM THE LIST  " << endl;
		line = optioncheck(1);
		while (line == "0")
		{
			line.clear();
			line = optioncheck(1);
		}

		elements.push_back(line);   cout << endl;

		cout << "COMPANY PHONE NUMBER:  ";  cin >> line;
		if (numbercheck(line, 10) == true) { elements.push_back(line); }

		cout << "OWN CAR (Y OR N):  ";  cin >> line;
		line = truecheck(line, 2);
		elements.push_back(line);

		cout << "DRIVING LICENCE CATEGORY "<< endl;
		line = optioncheck(3);
		while (line == "0")
		{
			line = optioncheck(3);
		}
		elements.push_back(line);

		cout << "DRIVING LICENCE EXPIRY DATE:  " << endl;
		int check;
		do {
			check = datecheck(line);
		} while (check != 1);
		elements.push_back(line);

		cout << endl;
		addtolist();
		break;
	}

	default: {

		system("cls");
		cout << "                            INCORRECT NUMBER. TRY AGAIN ENTRY THE NUMBER:   \n";
		addemployee();
		break;
	}
	}

};

// Function, which find the right index for new employee
void EmployeeBase::findindex (Employee * pemployee) {

	NumberBase.push_back(pemployee); // Adding to list in ascending order

	if (SurnameBase.empty() == true) // Checking if the list is empty
	{
		SurnameBase.push_front(pemployee); // Add on the begging
	}
	else { 

		std::list<Employee*>::iterator itr = SurnameBase.begin(); // Iterator for moving in the list

		for (itr; itr != SurnameBase.end(); itr++) { // Searching for a place until end of the list

			Employee* iptr = *itr; 
			string psurname = pemployee->employee_surname().c_str(); // Surname of the adding employee
			string indexsurname = iptr->employee_surname().c_str(); // Surname of the employee in actual index
			const char* pCKey = psurname.c_str();
			const char* pCHeadKey = indexsurname.c_str();


			if ((_stricmp(pCKey, pCHeadKey) == 0) || (strcoll(pCKey, pCHeadKey) < 0))
			// If the key from new object if equal to key from index, the new object is going to be added before the existing one
			// If the key from new object is first in alphabetical order
			{
				SurnameBase.insert(itr, pemployee); // Adding a element to the right place by using iterator for moving
				break; // Throwing out of the loop
			}
			// If the key from new object is after the key from index, the loop is going to be repeated for next index in list
		}
		// Whole list has been searched, the new element has to be added on the end
		if (itr == SurnameBase.end()) {
			SurnameBase.push_back(pemployee);

		}
	}
	cout << "                            PERSON HAS BEEN ADDED TO THE BASE " << endl;
}

// Find employee by his number
Employee* EmployeeBase::findbynumber(int number)
{
		for (std::list <Employee*>::iterator itr = SurnameBase.begin(); itr != SurnameBase.end(); itr++) {
			Employee* ptr = *itr;
			if (ptr->employee_No==number)
			{
				return ptr;
			}
		}
}

// Shows help information
bool EmployeeBase::help()
{
	cout << endl;
	cout << "                            EMPLOYEE BASE " << endl;
	cout << "                            AVAIABLE OPTIONS" << endl << endl;
	cout << "                            1.ADD EMPLOYEE " << endl;
	cout << "                            2.FIND EMPLOYEE " << endl;
	cout << "                            3.DELETE EMPLOYEE " << endl;
	cout << "                            4.SHOW FULL LIST OF EMPLOYEES " << endl;
	cout << "                            5.SHOW LIST OF EMPLOYEES BY KIND OF WORK" << endl;
	cout << "                            6.BACK TO MENU " << endl << endl;
	cout << "                            CHOOSE A NUMBER OF THE OPTION " << endl;

	int number;
	if (choice(number) == true) {

		switch (number)
		{
		case 1:
		{
			system("cls");
			addemployee();
			return true;
			break;
		}
		case 2:
		{
			system("cls");
			int index = 0;
			findemployee(1,index);
			return true;
			break;
		}
		case 3:
		{
			system("cls");
			deleteemployee();
			return true;
			break;
		}
		case 4:
		{
			system("cls");
			showemployees();
			return true;
			break;
		}
		case 5:
		{
			system("cls");
			showemployeesbyclass();
			return true;
			break;
		}
		case 6:
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