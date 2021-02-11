#include "payment.h"

#include <typeinfo>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Payment class 
// Constructor
Payment::Payment(string pcom_Name, int pemp_No, string pName, string pSurname, string pAccountNo, double pRate, int pHours)
	: com_Name(pcom_Name), emp_No(pemp_No), emp_Name(pName), emp_Surname(pSurname), emp_AccountNo(pAccountNo), payment_Rate(pRate),
payment_Hours(pHours)
{
	this->payment_Amount = pRate * (double)pHours;
};

// Deconstructor
Payment::~Payment()
{

}

std::ostream& Payment::savepayment(std::ostream& outfile) const
{
	outfile << com_Name<< ";" + std::to_string(emp_No) << ";" << emp_Name << ";" << emp_Surname << ";" << emp_AccountNo << ";";
	outfile << std::to_string(payment_Rate) << ";" + std::to_string(payment_Hours)  << ";" << std::to_string(payment_Amount) << ";" << endl;
	return outfile;
}

// Important details about payment
void Payment::topay_details()
{
	cout << emp_Name <<"   " << emp_Surname <<"   "<<payment_Amount << endl;
}

// Showing all payments details
void Payment::payment_details()
{
	cout << "COMPANY: " << com_Name << endl;
	cout << "EMPLOYEE NUMBER: " << emp_No << endl;
	cout << "EMPLOYEE NAME: " << emp_Name << endl;
	cout << "EMPLOYEE SURNAME: " << emp_Surname << endl;
	cout << "ACCOUNT NUMBER: " << emp_AccountNo << endl;
	cout << "PAYMENT RATE: " << payment_Rate << endl;
	cout << "PAYMENT HOURS: " << payment_Hours << endl;
	cout << "AMOUNT TO PAY: " << payment_Amount << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PaymentQueue class 
// Constructor

PaymentQueue::PaymentQueue(): company_base(nullptr), office_base(nullptr)
{
}

// Deconstructor
PaymentQueue::~PaymentQueue()
{
	company_base = nullptr;
	office_base = nullptr;
	this->deletebase();
	payments.clear();
}

// Set a base
void PaymentQueue::set_base(CompanyBase* pbase, IntCompany* obase)
{
	this->company_base = pbase;
	this->office_base = obase;
}

// Load a company base from a .txt file
bool PaymentQueue::loadbase(vector <string> pelements)
{
	// Save elements to relevant variables
	int empNumber = atoi(pelements[1].c_str());
	double pRate = atof(pelements[5].c_str());
	int pHours = atoi(pelements[6].c_str());
	double pAmount = atof(pelements[7].c_str());
	Payment* ppayment = new Payment(pelements[0], empNumber, pelements[2], pelements[3], pelements[4], pRate, pHours, pAmount);
	payments.push_back(ppayment); // Adding to list 
	pelements.clear();
	return true;
}

// Save a company base to a .txt file
bool PaymentQueue::savebase (std::ostream& outfile)
{
	outfile << "#";
	for (std::list <Payment*>::iterator itr = payments.begin(); itr != payments.end(); itr++) {
			Payment* ptr = *itr;
			outfile << *ptr;
	}
	return true;
}

// Delete a existing data base
void PaymentQueue::deletebase()
{
	for (std::list <Payment*>::iterator pitr = payments.begin(); pitr != payments.end(); pitr++) {
			Payment* pay = *pitr;
			delete pay;
	}
	company_base->set_payments();
	payments.clear();
}

// Function, which adding employees from company to the payment list
void PaymentQueue::companypayment()
{
	cout << "                            ADDING EMPLOYEES TO PAYMENT LIST" << endl;
	int index = 0;
	Company* com = company_base->find_company(0,index);
	if (com != nullptr) {
		if (com->getstatus() == 0) {
			com->setstatus();
			for (std::vector <Workplace*>::iterator itr = com->company_Workplaces.begin(); itr != com->company_Workplaces.end(); itr++) {
				cout << "                            WORKPLACE: ";
				Workplace* place = *itr;
				cout << place->workplace_Name << endl << endl;
				if (place->workplace_Employees.empty() == true) {
					cout << "                            NO WORKERS ON SITE: ";
				}
				else {
					for (std::vector <Employee*>::iterator pitr = place->workplace_Employees.begin(); pitr != place->workplace_Employees.end(); pitr++) {
						Employee* employee = *pitr;
						employee->employee_names();
						cout << typeid(*employee).name();
						cout << "                            INSERT THE AMOUNT OF HOURS: ";
						string pamount;
						cin >> pamount;
						if (numbercheck(pamount, 2) == true) {}
						int ph = atoi(pamount.c_str());

						if (Supervise* d = dynamic_cast<Supervise*>(employee)) {
							Payment* topay = new Payment(com->company_Name, d->employee_No, d->employee_Name, d->employee_Surname, d->employee_AccountNo, com->workplace_t1Rate, ph);
							payments.push_back(topay);
						}
						else if (Carpenter* d = dynamic_cast<Carpenter*>(employee)) {
							Payment* topay = new Payment(com->company_Name, d->employee_No, d->employee_Name, d->employee_Surname, d->employee_AccountNo, com->workplace_t2Rate, ph);
							payments.push_back(topay);
						}
					}
				}
			}
		}
		else {
			cout << "                            YOU ALREADY ADDED THAT COMPANY TO PAYMENT" << endl;
		}

	}
	else {
		cout << "                            NO THAT COMPANY IN BASE DATA" << endl;
	}
}

// Function, which adding employees from office to the payment list
void PaymentQueue::officepayment()
{
	cout << "                            ADDING EMPLOYEES TO PAYMENT LIST" << endl;
	int index = 0;
	if (office_base->intcompany_Employees.empty() == true) {

		cout << "                            NO EMPLOYEE IN OFFICE" << endl;
	}
	else {
		for (std::vector <Employee*>::iterator pitr = office_base->intcompany_Employees.begin(); pitr != office_base->intcompany_Employees.end(); pitr++) {
			Employee* employee = *pitr;
			employee->employee_names();
			cout << typeid(*employee).name();
			cout << "                            INSERT THE AMOUNT OF HOURS: ";
			string pamount;
			cin >> pamount;
			if (numbercheck(pamount, 2) == true) {}
			int ph = atoi(pamount.c_str());

			if (Manager* d = dynamic_cast<Manager*>(employee)) {
				Payment* topay = new Payment(office_base->intcompany_Name, d->employee_No, d->employee_Name, d->employee_Surname, d->employee_AccountNo, office_base->workplace_t3Rate, ph);
				payments.push_back(topay);
			}
			else if (Account* d = dynamic_cast<Account*>(employee)) {
				Payment* topay = new Payment(office_base->intcompany_Name, d->employee_No, d->employee_Name, d->employee_Surname, d->employee_AccountNo, office_base->workplace_t4Rate, ph);
				payments.push_back(topay);
			}
			else if (Driver* d = dynamic_cast<Driver*>(employee)) {
				Payment* topay = new Payment(office_base->intcompany_Name, d->employee_No, d->employee_Name, d->employee_Surname, d->employee_AccountNo, office_base->workplace_t5Rate, ph);
				payments.push_back(topay);
			}

		}
	}
}

// Add a payment for one employee
bool PaymentQueue::addpayment()
{
	int option;
	cout << "                            ADDING EMPLOYEE TO A PAYMENT LIST" << endl;
	cout << "                            WHICH TYPE OF EMPLOYEE DO YOU WANT TO ADD ?" << endl;
	cout << "                            1.OFFICE " << endl;
	cout << "                            2.CONSTRUCTION " << endl;
	if (choice(option) == true) {
		switch (option) {
		case 1: {
			if (office_base->intcompany_Employees.empty() == true) {

				cout << "                            NO EMPLOYEE IN OFFICE" << endl;
				return false;
			}
			else {
				Employee* employee = office_base->find_officeemployee(0);
				if (employee != nullptr) {
					int numberemployee = employee->employee_number();
					for (std::list <Payment*>::iterator pitr = payments.begin(); pitr != payments.end(); pitr++) {
						Payment* pay = *pitr;
						if (numberemployee == pay->emp_No)
						{
							cout << "                            THERE IS ALREADY PAYMENT IN PAYLIST" << endl;
							return false;
						}
					}
					employee->employee_names();
					cout << typeid(*employee).name();
					cout << "                            INSERT THE AMOUNT OF HOURS: ";
					string pamount;
					cin >> pamount;
					if (numbercheck(pamount, 2) == true) {}
					int ph = atoi(pamount.c_str());
					if (Manager* d = dynamic_cast<Manager*>(employee)) {
						Payment* topay = new Payment(office_base->intcompany_Name, d->employee_No, d->employee_Name, d->employee_Surname, d->employee_AccountNo, office_base->workplace_t3Rate, ph);
						payments.push_back(topay);
					}
					else if (Account* d = dynamic_cast<Account*>(employee)) {
						Payment* topay = new Payment(office_base->intcompany_Name, d->employee_No, d->employee_Name, d->employee_Surname, d->employee_AccountNo, office_base->workplace_t4Rate, ph);
						payments.push_back(topay);
					}
					else if (Driver* d = dynamic_cast<Driver*>(employee)) {
						Payment* topay = new Payment(office_base->intcompany_Name, d->employee_No, d->employee_Name, d->employee_Surname, d->employee_AccountNo, office_base->workplace_t5Rate, ph);
						payments.push_back(topay);
					}
					return true;
				}
				else {

					cout << "                            THERE IS NO THAT PERSON IN OFFICE BASE" << endl;
					return false;

				}
			}
			break;
		}
		case 2: {

			int index = 0;
			Company* com = company_base->find_company(0, index);
			if (com != nullptr) {
				if (com->company_Workplaces.empty() == true) {
					cout << "                            NO WORKPLACES: ";
				}
				else {
					Workplace* place = com->find_workplace(0);
					if (place != nullptr) {

						if (place->workplace_Employees.empty() == true) {
							cout << "                            NO WORKERS ON SITE: ";
						}
						else {
							Employee* employee = company_base->findemployee(place);

							if (employee != nullptr) {
								int numberemployee = employee->employee_number();
								for (std::list <Payment*>::iterator pitr = payments.begin(); pitr != payments.end(); pitr++) {
									Payment* pay = *pitr;
									if (numberemployee == pay->emp_No)
									{
										cout << "                            THERE IS ALREADY PAYMENT IN PAYLIST" << endl;
										return false;
									}
								}
								employee->employee_names();
								cout << typeid(*employee).name();
								cout << "                            INSERT THE AMOUNT OF HOURS: ";
								string pamount;
								cin >> pamount;
								if (numbercheck(pamount, 2) == true) {}
								int ph = atoi(pamount.c_str());

								if (Supervise* d = dynamic_cast<Supervise*>(employee)) {
									Payment* topay = new Payment(com->company_Name, d->employee_No, d->employee_Name, d->employee_Surname, d->employee_AccountNo, com->workplace_t1Rate, ph);
									payments.push_back(topay);
								}
								else if (Carpenter* d = dynamic_cast<Carpenter*>(employee)) {
									Payment* topay = new Payment(com->company_Name, d->employee_No, d->employee_Name, d->employee_Surname, d->employee_AccountNo, com->workplace_t2Rate, ph);
									payments.push_back(topay);
								}
								return true;
							}
							else {

								cout << "                            THERE IS NO THAT PERSON IN COMPANY BASE" << endl;
								return false;

							}
						}
					}
					else {

						cout << "                            THERE IS NO WORKPLACE IN BASE DATA" << endl;
						return false;

					}
				}
				return false;
			}
			return false;
			break;
		}
		default: {
			cout << "                            WRONG OPTION" << endl;
			return false;
			break;
		}
		}
	}
}

// Find a payment in list
Payment* PaymentQueue::findpayment(int number, int& index)
{
	vector <Payment*> vec;
	cout << endl;
	cout << "                            FINDING A PAYMENT \n";
	if (payments.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO PAYMENTS IN A BASE DATA " << endl;
		return nullptr;
	}
	else {
		cout << "                            ENTER THE SURNAME OF THE EMPLOYEE \n";
		string surname;
		cin >> surname;
		if (stringcheck(surname) == true) {};
		const char* psurname = surname.c_str();
		for (std::list <Payment*>::iterator pitr = payments.begin(); pitr != payments.end(); pitr++) {
			Payment* pay = *pitr;
			string ptrsurname = pay->emp_Surname;
			const char* psurnamekey = ptrsurname.c_str();
			if ((_stricmp(psurname, psurnamekey) == 0))
			{
				vec.push_back(pay);
			}
			index++;

		}
		if (vec.empty() == true) {
			cout << "                            THE EMPLOYEE HASN'T BEEN FOUND IN BASE DATA" << endl;
			return nullptr;
		}
		else {
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			if ( (number == 1)||(number==2)) { // For showing all kind of workers with that surname
				cout << "                            THE LIST OF THE PEOPLE WITH THAT SURNAME" << endl;
				int i = 1;
				for (std::vector <Payment*>::iterator pitr = vec.begin(); pitr != vec.end(); pitr++) {
					Payment* patr = *pitr;
					cout << i << ". ";
					cout << patr->emp_Name << " " << patr->emp_Surname << endl;
					i++;
				}
				cout << "                            CHOOSE THE PERSON. INSERT THE NUMBER" << endl;
				int n;
				if (choiceforemp(n, i) == true) {
					int n1 = n - 1;
					if (number == 1) { // For showing all details
						vec[n1]->payment_details();
					}
					return vec[n1];
				}

			}
		}
	}
}

// Delete a payment from the list
void PaymentQueue::deletepayment()
{
	if (payments.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO PAYMENTS IN A BASE DATA " << endl;
	}
	else {
		int index = 0;
		Payment * pay = findpayment(2, index);
		for (std::list <Payment*>::iterator pitr = payments.begin(); pitr != payments.end(); pitr++) {
			Payment* patr = *pitr;
			if (pay == patr) {
				payments.erase(pitr);
				break;
			}
		}
		delete pay;
	}
	cout << "                            DELETING THE PAYMENT FROM THE LIST IN PROGRAM" << endl << endl;
}

// Show all payments
void PaymentQueue::showallpayment()
{
	if (payments.empty() == true) // Checking if the list is empty
	{
		cout << "                            NO PAYMENTS IN A BASE DATA " << endl;
	}
	else {
		cout << "NAME   SURNAME   AMOUNT TO PAY" << endl;
		int index = 1;
		for (std::list <Payment*>::iterator itr = payments.begin(); itr != payments.end(); itr++) {
			Payment* ptr = *itr;
			cout << index << ". ";
			ptr->topay_details();
			index++;
		}
	}
}

// Create new paylist
void PaymentQueue::newpaylist()
{
	deletebase();
	cout << "                            CREATING NEW PAYLIST DATA" << endl << endl;
}

std::ostream& operator<<(std::ostream& outfile, const Payment& ppayment)
{
	ppayment.savepayment(outfile);
	return outfile;
}

// Show help information
bool PaymentQueue::help()
{
	cout << endl;
	cout << "                            AVAIABLE OPTIONS" << endl << endl;
	cout << "                            1.ADD EMPLOYEES FROM COMPANY TO THE PAYMENT LIST " << endl;
	cout << "                            2.ADD OFFFICE EMPLOYEES TO PAYMENT LIST" << endl;
	cout << "                            3.ADD EMPLOYEE TO PAYEMENT LIST" << endl;
	cout << "                            4.FIND PAYMENT " << endl;
	cout << "                            5.DELETE THE PAYMENT FROM THE LIST " << endl;
	cout << "                            6.SHOW ALL PAYMENTS " << endl;
	cout << "                            7.CREATE NEW PAYLIST " << endl;
	cout << "                            8.BACK TO MENU " << endl << endl;
	cout << "                            CHOOSE A NUMBER OF THE OPTION " << endl;

	int number;
	if (choice(number) == true) {

		switch (number)
		{
		case 1:
		{
			system("cls");
			companypayment();
			return true;
			break;
		}
		case 2:
		{
			system("cls");
			officepayment();
			return true;
			break;
		}
		case 3:
		{
			system("cls");
			int index = 0;
			addpayment();
			return true;
			break;
		}
		case 4:
		{
			system("cls");
			int index = 0;
			findpayment(1, index);
			return true;
			break;
		}
	
		case 5:
		{
			system("cls");
			deletepayment();
			return true;
			break;
		}
		case 6:
		{
			system("cls");
			showallpayment();
			return true;
			break;
		}
		case 7:
		{
			system("cls");
			newpaylist();
			return true;
			break;
		}

		case 8:
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
