#include "intcompany.h"
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IntCompany class constructor
IntCompany::IntCompany() : employee_base(nullptr), workplace_t3Rate(0.0), workplace_t4Rate(0.0), workplace_t5Rate(0.0) {};

// Deconstructor
IntCompany::~IntCompany()
{
    intcompany_Employees.clear();
	elements.clear();
	employee_base = nullptr;
}

// Load a company base from a .txt file
bool IntCompany::loadbase(vector <string> pelements)
{
	if (pelements[0] == "C") {
	 
		intcompany_Name = pelements[1];
		workplace_t3Rate = atof(pelements[2].c_str());
		workplace_t4Rate = atof(pelements[3].c_str());
		workplace_t5Rate = atof(pelements[4].c_str());
	}
	else if (pelements[0] == "E"){

		for (int i = 1; i < pelements.size(); i++)
		{
			int number = atoi(pelements[i].c_str());
			Employee* emp = employee_base->findbynumber(number);
			intcompany_Employees.push_back(emp);
			emp->set_employee_status(1);
		}
	}
	pelements.clear();
	return true;
}

// Save a company base to a .txt file
bool IntCompany::savebase(std::ostream& outfile)
{
	outfile << "#C;";
	outfile << intcompany_Name << ";" + std::to_string(workplace_t3Rate) << ";" << std::to_string(workplace_t4Rate) << ";" << std::to_string(workplace_t5Rate) << ";" << endl;
	outfile << "E;";
	for (std::vector <Employee*>::iterator itr = intcompany_Employees.begin(); itr != intcompany_Employees.end(); itr++) {
		Employee* ptr = *itr;
		outfile << ptr->employee_number() << ";";
	}
	outfile << endl;
	return true;
}

// Delete a existing data base
void IntCompany::deletebase()
{
	intcompany_Employees.clear(); 
}

// Set a internal comapany details
void IntCompany::setdetails(string pName, double pt3Rate, double pt4Rate, double pt5Rate)
{
	intcompany_Name = pName;
	workplace_t3Rate = pt3Rate;
	workplace_t4Rate = pt4Rate;
	workplace_t5Rate = pt5Rate;
}

// Set a base
void IntCompany::setbase(EmployeeBase* pemployee_base)
{
	employee_base = pemployee_base;
}

// Return a internal company name
string IntCompany::intcompany_name()
{
    return intcompany_Name;
}

// Add a employee to office base
void IntCompany::add_officeemployee()
{ 
     int index = 0;
     Employee* pemployee = employee_base->findemployee(2, index);
	 if (pemployee != nullptr) {
		 bool status = pemployee->employee_status();
		 if (status != 1) {
			 pemployee->set_employee_status(1);
			 pemployee->set_employee_comanyno(9999);
			 intcompany_Employees.push_back(pemployee);
		 }
		 else {
			 cout << "                            THAT EMPLOYEE IS ALREADY IN BASE" << endl;
		 }
	 }
	 else {
		 cout << "                            THERE NO EMPLOYEES TO ADD" << endl;
	 }
}

// Find a employee 
Employee * IntCompany::find_officeemployee(int number)
{
	vector <Employee*> vec;
	vector <int> indexes;
    if (intcompany_Employees.empty() == true) // Checking if the list is empty
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
		for (std::vector <Employee*>::iterator pitr = intcompany_Employees.begin(); pitr != intcompany_Employees.end(); pitr++) {
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
					if (number == 1) { // For showing all details
						vec[n1]->employee_details();
					}
					if (number == 2) {
						int index = indexes[n1];
						std::vector <Employee*>::iterator pitr = intcompany_Employees.begin();
						advance(pitr, (index));
						intcompany_Employees.erase(pitr);
					}
					return vec[n1];
				}

			
		}
	}
}

// Show all office employees
void IntCompany::show_allemployees()
{
	if (intcompany_Employees.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO EMPLOYEES IN A INTERNAL COMPANY BASE " << endl;
	}
	else {
		int i = 1;
		for (std::vector <Employee*>::iterator pitr = intcompany_Employees.begin(); pitr != intcompany_Employees.end(); pitr++) {
			Employee* person = *pitr;
			cout << i << ". ";
			person->employee_names();
			i++;
		}
	}
}

// Delete a employee from office base
void IntCompany::delete_officeemployee()
{
    if (intcompany_Employees.empty() == true) // Checking if the list is empty
    {
        cout << "                            NO EMPLOYEES IN A INTERNAL COMPANY BASE " << endl;
    }
    else {
        cout << "                            REMEMBER THAT YOU ARE DELETING A PERSON ONLY FROM A OFFICE" << endl << endl;
        Employee* person = find_officeemployee(2);
		person->set_employee_status(0);
    }
}

// Function which shows all internal company details
void IntCompany::intcompany_show()
{
	cout << "COMPANY DETAILS " << endl << endl << endl;
	cout << "COMPANY NAME: " << this->intcompany_Name << endl << endl;
	cout << "MANAGER RATE: " << this->workplace_t3Rate << endl << endl;
	cout << "ACCOUNT RATE: " << this->workplace_t4Rate << endl << endl;
	cout << "DRIVER RATE: " << this->workplace_t5Rate << endl << endl;
	cout << "EMPLOYEES: " << endl << endl;
	int number = 1;
	for (std::vector <Employee*>::iterator pitr = intcompany_Employees.begin(); pitr != intcompany_Employees.end(); pitr++) {
		Employee* person = *pitr;
		cout << number << ".";
		person->employee_names();
		number++;
	}
}

void IntCompany::update(int pnumber)
{
	int index = 0;
	for (std::vector <Employee*>::iterator pitr = intcompany_Employees.begin(); pitr != intcompany_Employees.end(); pitr++) {
		Employee* person = *pitr;
		if (person->employee_number() == pnumber)
		{
			break;
		}
		index++;
	}
	std::vector <Employee*>::iterator pitr = intcompany_Employees.begin();
	advance(pitr, (index));
	intcompany_Employees.erase(pitr);
}

// Save to the file all details
std::ostream& IntCompany::saveintcompany(std::ostream& outfile) const
{
	outfile << intcompany_Name << ";" + std::to_string(workplace_t3Rate) << ";" << std::to_string(workplace_t4Rate) << ";" << std::to_string(workplace_t5Rate) << ";";
    return outfile;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& outfile, const IntCompany& pintcompany)
{
    pintcompany.saveintcompany(outfile);
    outfile << endl;
    return outfile;
}

// Show help information
bool IntCompany::help()
{
	cout << endl;
	cout << "                            AVAIABLE OPTIONS" << endl << endl;
	cout << "                            1.ADD EMPLOYEE TO OFFICE " << endl;
	cout << "                            2.FIND EMPLOYEE " << endl;
	cout << "                            3.DELETE EMPLOYEE FROM OFFICE " << endl;
	cout << "                            4.SHOW ALL EMPLOYEES " << endl;
	cout << "                            5.SHOW ALL OFFICE DETAILS " << endl;
	cout << "                            6.BACK TO MENU " << endl << endl;
	cout << "                            CHOOSE A NUMBER OF THE OPTION " << endl;

	int number;
	if (choice(number) == true) {

		switch (number)
		{
		case 1:
		{
			system("cls");
			add_officeemployee();
			return true;
			break;
		}
		case 2:
		{
			system("cls");
			find_officeemployee(1);
			return true;
			break;
		}
		case 3:
		{
			system("cls");
			delete_officeemployee();
			return true;
			break;
		}
		case 4:
		{
			system("cls");
			show_allemployees();
			return true;
			break;
		}
		case 5:
		{
			system("cls");
			intcompany_show();
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
