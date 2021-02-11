#include "checking.h"
#include "employee.h"
#include "employeebase.h"
#include "intcompany.h"
#include "payment.h"
#include "strategy.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <thread>         =
#include <chrono>  
using std::cout;
void begin(string& name, double& t3, double& t4, double& t5);
bool mainmenu(vector <Strategy*> vec, Contex* contex);
bool menu(vector <Strategy*> vec, Contex* contex);

int main() {

	IntCompany* intcom = new IntCompany(); 
	EmployeeBase* emp = new EmployeeBase();
	CompanyBase* com = new CompanyBase();
	PaymentQueue* pay = new PaymentQueue();
	//Setting bases
	intcom->setbase(emp);
	com->set_base(emp);
	emp->set_base(intcom,com);
	pay->set_base(com,intcom);
	Strategy* sintcom = dynamic_cast<Strategy*>(intcom);
	Strategy* semp = dynamic_cast<Strategy*>(emp);
	Strategy* scom = dynamic_cast<Strategy*>(com);
	Strategy* spay = dynamic_cast<Strategy*>(pay);
	vector <Strategy*> vec = {semp,sintcom,scom,spay };
	Contex* contex = new Contex();
	
	bool option = mainmenu(vec,contex);
	while (option != false)
	{
		cout << endl << endl;
		option = mainmenu(vec, contex);
	}
	delete intcom, emp, com, pay, contex, sintcom, semp, scom, spay;
	
    system("PAUSE");
};

void begin(string &name, double & t3, double & t4, double & t5){

	cout << endl;
	cout << "                            ENTER THE NAME OF INTERNAL COMPANY " << endl << endl;
	string l3, l4, l5;
	cin >> name;
	if (stringcheck(name) == true) {}
	cout << "                            ENTER THE RATES " << endl;
	cout << "                            RATE FOR MANAGER " << endl;
	cin >> l3;
	if (numbercheck(l3, 1) == true) { t3 = atof(l3.c_str()); }
	cout << "                            RATE FOR ACCOUNT " << endl;
	cin >> l4;
	if (numbercheck(l4, 1) == true) { t4 = atof(l4.c_str()); }
	cout << "                            RATE FOR DRIVER " << endl;
	cin >> l5;
	if (numbercheck(l5, 1) == true) { t5 = atof(l5.c_str()); }
}

bool mainmenu(vector <Strategy*> vec, Contex* contex)
{
	system("cls");
	cout << endl;
	cout << "                            MAIN MENU" << endl << endl;
	cout << "                            1.LOAD BASE FROM TXT FILE " << endl;
	cout << "                            2.SAVE BASE TO TXT FILE " << endl;
	cout << "                            3.CREATE NEW BASE " << endl;
	cout << "                            4.CLOSE THE PROGRAM " << endl << endl;
	int number;
	if (choice(number) == true) {

		switch (number)
		{
		case 1:
		{
			system("cls");
		
			contex->setstrategy(vec[0]);
			contex->deletebase();
			contex->setstrategy(vec[1]);
			contex->deletebase();
			contex->setstrategy(vec[2]);
			contex->deletebase();
			contex->setstrategy(vec[3]);
			contex->deletebase();

			bool option1 = loaddatabase(vec, contex);
			if (option1!=true){
				cout << "                            THE FILE HASN'T BEEN OPENED " << endl << endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
				return true;
			}
			bool option = menu(vec, contex);
			while (option != false)
			{
				cout << endl << endl;
				option = menu(vec, contex);
			}
			return true;
			break;
		}
		case 2:
		{
			system("cls");
			bool option1 = savedatabase(vec,contex);
			if (option1 != true) {
				cout << "                            THE FILE HASN'T BEEN OPENED " << endl << endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
				return true;
			}
			return true;
			break;
		}
		case 3:
		{
			system("cls");
	
			contex->setstrategy(vec[0]);
			contex->deletebase();
			contex->setstrategy(vec[1]);
			contex->deletebase();
			contex->setstrategy(vec[2]);
			contex->deletebase();
			contex->setstrategy(vec[3]);
			contex->deletebase();

			string name;
			double t3, t4, t5;
			begin(name, t3, t4, t5);
			IntCompany* sintcom = dynamic_cast<IntCompany*>(vec[1]);
			sintcom->setdetails(name, t3, t4, t5);
			bool option = menu(vec, contex);
			while (option != false)
			{
				cout << endl << endl;
				option = menu(vec, contex);
			}
			return true;
			break;
		}
		case 4:
		{
			system("cls");
			cout << "                            END OF THE PROGRAM ";
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


bool menu(vector <Strategy*> vec, Contex* contex) {

	system("cls");
	cout << "                            CLASS MENU " << endl << endl;
	cout << "                            1.EMPLOYEES" << endl;
	cout << "                            2.OFFICE " << endl;
	cout << "                            3.COMPANIES AND WORKPLACES " << endl;
	cout << "                            4.PAYMENTS " << endl;
	cout << "                            5.BACK TO MAIN MENU " << endl << endl;
	cout << "                            CHOOSE A NUMBER OF THE OPTION " << endl;

	int number;
	if (choice(number) == true) {
		switch (number) {

		case 1:
		{
			system("cls");
			contex->setstrategy(vec[0]);
			contex->method();
			return true;
			break;
		}
		case 2:
		{
			system("cls");
			contex->setstrategy(vec[1]);
			contex->method();
			return true;
			break;
		}
		case 3:
		{
			system("cls");
			contex->setstrategy(vec[2]);
			contex->method();
			return true;
			break;
		}
		case 4:
		{
			system("cls");
			contex->setstrategy(vec[3]);
			contex->method();
			return true;
			break;
		}
		case 5:
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
