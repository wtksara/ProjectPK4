#include "company.h"
#include "companybase.h"

#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ExtCompany class constructor
Company::Company(string pName, double pt1Rate, double pt2Rate)
{
    company_No = company_Amount;
    company_Name = pName;
	workplace_t1Rate = pt1Rate;
	workplace_t2Rate = pt2Rate;
    payment_status = 0;
    company_Amount++;
}

// Deconstructor
Company::~Company()
{
    this->delete_workplaces();
    company_Workplaces.clear();
}

// Save to the file all details
std::ostream& Company::savecompany(std::ostream& outfile) 
{
    outfile << company_Name << " " + std::to_string(workplace_t1Rate) << " " << std::to_string(workplace_t2Rate) << " !";
    return outfile;
}

std::ostream& Company::saveworkplaces(std::ostream& outfile)
{
    for (std::vector <Workplace*>::iterator itr = company_Workplaces.begin(); itr != company_Workplaces.end(); itr++) {
        Workplace* ptr = *itr;
        outfile << ptr->workplace_Name << " ";
        for (std::vector <Employee*>::iterator itr = ptr->workplace_Employees.begin(); itr != ptr->workplace_Employees.end(); itr++) {
            Employee* emp = *itr;
            outfile << emp->employee_number() << " ";
        }
        outfile << "!";
    }
    
    return outfile;

}

// Return a company name
string Company::company_name()
{
    return company_Name;
}

// Set a company number
void Company::set_company_number(int pnumber)
{
    company_No = pnumber;
}

// Function which shows all company details
void Company::company_show()
{
    cout << "COMPANY DETAILS " << endl << endl << endl;
    cout << "COMPANY NUMBER: " << this->company_No << endl << endl;
    cout << "COMPANY NAME: " << this->company_Name << endl << endl;
    cout << "SUPERVISE RATE: " << this->workplace_t1Rate << endl << endl;
    cout << "CARPETER RATE: " << this->workplace_t2Rate << endl << endl;
    if (company_Workplaces.empty() == true) // Checking if the list is empty
    {
        cout << "                            NO WORKPLACES IN COMPANY " << endl;
    }
    else {
        int index = 1;
        for (std::vector <Workplace*>::iterator itr = this->company_Workplaces.begin(); itr != this->company_Workplaces.end(); itr++) {
            Workplace* place = *itr;
            string name = place->workplace_name();
            cout << index <<". "<< name << endl;
            index++;
        }
    }
}

// Function which add a workplace 
void Company::add_workplace(Workplace* pworkplace)
{
    company_Workplaces.push_back(pworkplace);

}

// Function which finding or deleteing workplace
Workplace * Company::find_workplace(int number)
{
    if (company_Workplaces.empty() == true) // Checking if the list is empty
    {
        cout << "                            NO WORKPLACE IN A BASE DATA " << endl;
        return nullptr;
    }
    else {
        int i = 1;
        for (std::vector <Workplace*>::iterator pitr = company_Workplaces.begin(); pitr != company_Workplaces.end(); pitr++) {
            Workplace* ptr = *pitr;
            cout << i << ". " << ptr->workplace_name() << endl;
            i++;
        }

        cout << "                            INSERT THE NAME OF WORKPLACE" << endl << endl;
        string line;
        int index = 0;
        cin >> line;
        if (stringcheck(line) == true) {}
        const char* pline = line.c_str();

        for (std::vector <Workplace*>::iterator itr = company_Workplaces.begin(); itr != company_Workplaces.end(); itr++) {
            Workplace* ptr = *itr;

            string ptrname = ptr->workplace_Name;
            const char* pnamekey = ptrname.c_str();
       
            if ((_stricmp(pline, pnamekey) == 0))
            {
                if (number == 1) { // For showing all details
                    ptr->show_workplace();
                }
                if (number == 2) {
                    this->delete_workplace(itr,index);
                }
                return ptr;
            }
            index++;
        }
        cout << "                            THE WORKPLACE HASN'T BEEN FOUND IN BASE DATA" << endl;
        return nullptr;
    }

}

// Deleting a workplace
void Company::delete_workplace(vector <Workplace*>::iterator pitr, int pindex)
{

        cout << "                            DELETING A WORKPLACE FROM THE DATEBASE " << endl;
        Workplace* pptr = *pitr;
        company_Workplaces.erase(pitr); // Delete a company from the list

        delete pptr; // Delete a workplace
        cout << "                            THE WORKPLACE HAS BEEN DELETED FROM DATEBASE " << endl;

}

// Function which delete a all workplaces 
void Company::delete_workplaces()
{
    if (company_Workplaces.empty() == true) // Checking if the list is empty
    {
      
    }
    else {
        cout << "                            DELETING THE EXISTING WORKPLACE DATA IN PROGRAM" << endl << endl;
        for (std::vector <Workplace*>::iterator itr = company_Workplaces.begin(); itr != company_Workplaces.end(); itr++) {

            Workplace* ptr = *itr;
            ptr->workplace_Employees.clear();
            delete ptr; // Delete a company
        }
        company_Workplaces.clear();
    }
}

// Function which set status of payment
void Company::setstatus()
{
    payment_status = 1;
}

// Function which return status of payment
int Company::getstatus()
{
    return payment_status;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& outfile, Company& pcompany)
{
    pcompany.savecompany(outfile); 
    pcompany.saveworkplaces(outfile);
    outfile << ";"<<endl;
    return outfile;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Workplace class constructor
Workplace::Workplace(string pName) : workplace_Name(pName){}

// Deconstructor
Workplace::~Workplace()
{
    this->workplace_Employees.clear();
}

// Return a name of the workplace
string Workplace::workplace_name()
{
    return workplace_Name;
}

// Show all workplace details
void Workplace::show_workplace()
{
    cout << "                            NAME OF WORKPLACE :";
    cout << this->workplace_Name << endl;
    cout << "                            EMPLOYEES WORKING ON THE SITE: " << endl;
    if (this->workplace_Employees.empty() == true)
    {
    cout << "                            THERE IS NO EMPLOYEE ON THE SITE";

    }
    else {
        int i = 1;
        for (std::vector <Employee*>::iterator itr = workplace_Employees.begin(); itr != workplace_Employees.end(); itr++) {
            Employee* pemployee = *itr;
            cout << i << ". ";
            pemployee->employee_names();
            i++;
        }
    }
    
}

// Adding a employee to workplace
void Workplace::add_employee(Employee * pemployee)
{
    workplace_Employees.push_back(pemployee); 
}

// Deleting a employee from a workplace
bool Workplace::delete_employee() {

    if (workplace_Employees.empty() == true) // Checking if the list is empty
    {
        cout << "                            NO EMPLOYEE IN A BASE DATA " << endl;
        return false;
    }
    else {

        cout << "                            INSERT A SURNAME OF EMPLOYEE " << endl;
        string line;
        cin >> line;
        if (stringcheck(line) == true) {}
        const char* pline = line.c_str();

        for (std::vector <Employee*>::iterator itr = workplace_Employees.begin(); itr != workplace_Employees.end(); itr++) {
            Employee* ptr = *itr;
            string ptrname = ptr->employee_surname();
            const char* psurnamekey = ptrname.c_str();
            if ((_stricmp(pline, psurnamekey) == 0))
            {
                workplace_Employees.erase(itr); // Delete a employee from a vector
                ptr->set_employee_status(0);
                ptr->set_employee_comanyno(9999);
                return true;
            }
        }
        cout << "                            THE EMPLOYEE HASN'T BEEN FOUND IN BASE DATA" << endl;
        return false;
    }
}



