#include "checking.h"
#include "employee.h"
#include "employeebase.h"

#include <sstream>
#include <algorithm>

using std::vector;


/***********************************************************************************************************************************/

// Check if the written string is correct (contains only letters)
bool stringcheck(string& line)
{
	for (int i = 0; i < line.size(); i++)
	{
		if (!(isalpha(line[i])))
		{
			cin.clear();
			cin.ignore(std::numeric_limits <std::streamsize >::max(), '\n');
			cout << "                            ONLY LETTERS. TRY AGAIN: ";
			cin >> line;
			i = 0;
		}
	}
	transform(line.begin(), line.end(), line.begin(), ::toupper);
	return true;
}

// Check if the written date is correct and contais only digits
int datecheck(string& line)
{
	string day;
	string month;
	string year;

	cout << "DAY:  "; cin >> day;
	if (numbercheck(day, 2) == true) {};
	cout << "MONTH:  "; cin >> month;
	if (numbercheck(month, 2) == true) {};
	cout << "YEAR:  "; cin >> year;
	if (numbercheck(year, 4) == true) {};

	int nday = atoi(day.c_str());
	int nmonth = atoi(month.c_str());
	int nyear = atoi(year.c_str());

	if ((nyear < 0) || (nyear > 2040)) {
		cout << "                            INCORRECT YEAR " << endl;
		return 0;
	}
	if (nmonth < 0 || nmonth > 12) {
		cout << "                            INCORRECT MONTH " << endl;
		return 0;
	}
	if (nmonth == 2)
	{
		if (nyear % 4 == 0)
		{
			if (nday > 29 || nday < 0) {
				cout << "                            FEBRUARY IN LEAP YEAR HAS ONLY 29 DAYS " << endl;
				return 0;
			}
		}
		else
		{
			if (nday > 28 || nday < 0) {
				cout << "                            FEBRUARY HAS ONLY 28 DAYS " << endl;
				return 0;
			}
		}
	}
	else if (nmonth == 1 || nmonth == 3 || nmonth == 5 || nmonth == 7 || nmonth == 8 || nmonth == 10 || nmonth == 12) {
		if (nday > 31 || nday < 0) {
			cout << "                            THAT MONTH HAS ONLY 31 DAYS " << endl;
			return 0;
		}
	}
	else {
		if (nday > 30 || nday < 0) {
			cout << "                            THAT MONTH HAS ONLY 30 DAYS  " << endl;
			return 0;
		}
	}

	if (day.size() != 2) {
		day = "0" + day;
	}
	if (month.size() != 2) {
		month = "0" + month;
	}
	int i = year.size();

	if (i == 3) {
		year = "0" + year;
	}
	else if (i == 2) {
		year = "00" + year;
	}
	else if (i == 1) {
		year = "000" + year;
	}

	line = day + month + year;
	return 1;

}

// Check if the written string is correct (contains only digits and check if the lenght is correct)
bool numbercheck(string& line, int amount)
{
int number = 0;
	string nline;
	if (amount == 1)
	{
		for (int j = 0; j < line.size(); j++) {
			if ((line[j] == ',') || (line[j] == '.'))
			{
				number = j;
				line.erase(line.begin() + number);
				break;
			}
		}
		for (int i = 0; i < line.size(); i++)
		{
			if (!(isdigit(line[i])))
			{
				cin.clear();
				cin.ignore(std::numeric_limits <std::streamsize >::max(), '\n');
				cout << "                            ONLY NUMBERS.TRY AGAIN: ";
				cin >> line;
				for (int j = 0; j < line.size(); j++) {
					if ((line[j] == ',') || (line[j] == '.'))
					{
						number = j;
						line.erase(line.begin() + number);
						break;
					}
				}
				i = 0;
			}
		}

		for (int j = 0; j < line.size(); j++)
		{
			if (j == number) {
				nline = nline + '.';
			}
			nline = nline + line[j];
		}
		line = nline;

	}
	else if ((amount == 2) || (amount == 3) || (amount == 4))
	{
		for (int i = 0; i < line.size(); i++)
		{
			if ((line.size() > amount) || (!(isdigit(line[i]))))
			{
				cin.clear();
				cin.ignore(std::numeric_limits <std::streamsize >::max(), '\n');
				if (amount == 3) { cout << "                            ONLY NUMBERS.THE LIMIT IS THREE DIGITS. TRY AGAIN: "; }
				if (amount == 2) { cout << "                            ONLY NUMBERS.THE LIMIT IS TWO DIGITS. TRY AGAIN: "; }
				if (amount == 4) { cout << "                            ONLY NUMBERS.THE LIMIT IS FOUR DIGITS.  TRY AGAIN: "; }
				cin >> line;
				i = 0;
			}
		}

	}
	else {

		for (int i = 0; i < line.size(); i++)
		{
			if ((line.size() != amount) || (!(isdigit(line[i]))))
			{
				cin.clear();
				cin.ignore(std::numeric_limits <std::streamsize >::max(), '\n');

				if (amount == 8) { cout << "                            ONLY NUMBERS. IT HAS TO BE EIGHT NUMBERS AGAIN: "; }
				if (amount == 10) { cout << "                            ONLY NUMBERS.IT HAS TO BE TEN NUMBERS. TRY AGAIN: "; }
				cin >> line;
				i = 0;
			}
		}
	}

	return true;
}

// Show a list of option depends of the variable
string optioncheck(int option)
{
	switch (option) {
	case 1: {
		cout << "1.1250 L  " << endl;
		cout << "2.1250 NT  " << endl;
		cout << "3.1250 BR  " << endl;
		cout << "4.1250 D0  " << endl;
		cout << "YOUR CHOICE:   ";
		int number;
		if (choice(number) == true) {

			switch (number)
			{
			case 1:
			{   return "1250 L";
			break;
			}
			case 2:
			{   return "1250 NT";
			break;
			}
			case 3:
			{   return "1250 BR";
			break;
			}
			case 4:
			{   return "1250 D0";
			break;
			}
			default:
			{
				cout << "                            INCORRECT NUMBER. TRY AGAIN ENTRY THE NUMBER:   " << endl;
				return "0";
				break;
			}
			}
		}
	}
	case 2: {

		string line;
		int number;
		if (choice(number) == true) {

			if ((number == 1) || (number == 2) || (number == 3) || (number == 4) || (number == 5))
			{
				line = std::to_string(number);
				return line;
			}
			else {
				cout << "                            THERE ARE ONLY 5 LEVELS OF NVQ:   " << endl;
				return "0";
			}
		}
	}
	case 3: {

		cout << "                            LIST OF EXISTING CATEGORIES OF DRIVING LICENCE" << endl;
		cout << "1.B1 " << endl;
		cout << "2.B " << endl;
		cout << "3.C1 " << endl;
		cout << "4.C " << endl;
		cout << "5.D1" << endl;
		cout << "6.D" << endl;
		cout << "7.BE" << endl;

		int number;
		if (choice(number) == true) {

			switch (number)
			{
			case 1:
			{   return "B1";
			break;
			}
			case 2:
			{   return "B";
			break;
			}
			case 3:
			{   return "C1";
			break;
			}
			case 4:
			{   return "C";
			break;
			}
			case 5:
			{   return "D1";
			break;
			}
			case 6:
			{   return "D";
			break;
			}
			case 7:
			{   return "BE";
			break;
			}
			default:
			{
				cout << "                            INCORRECT NUMBER. TRY AGAIN ENTRY THE NUMBER:   ";
				return "0";
				break;
			}
			}
		}
	}
	}

}

// Check if the bool answer
string truecheck(string& line, int amount)
{
	for (int i = 0; i < line.size(); i++)
	{
		if ((!(isalpha(line[i]))) || (line.size() != 1))
		{
			cin.clear();
			cin.ignore(std::numeric_limits <std::streamsize >::max(), '\n');
			if (amount == 1) {
				cout << "                            ONLY ONE LETTER. TRY AGAIN" << endl;
				cout << "                            AVAIABLE OPTIONS. F OR M:  ";
			}
			if (amount == 2) {
				cout << "                            ONLY ONE LETTER. TRY AGAIN" << endl;
				cout << "                            AVAIABLE OPTIONS. Y OR N:  ";
			}
			cin >> line;
			i = 0;
		}
	}
	transform(line.begin(), line.end(), line.begin(), ::toupper);
	if (amount == 1) {
		char sign = line[0];
		switch (sign) {
		case 'F':
		{
			return "1";
			break;
		}
		case 'M':
		{
			return "0";
			break;
		}
		default:
		{
			cout << "                            INCORRECT. THERE IS ONLY 2 OPTIONS : F OR M . TRY AGAIN : " << endl;
			cin >> line;
			line = truecheck(line, amount);
			return line;
			break;
		}
		}
	}
	if (amount == 2) {
		char sign = line[0];
		switch (sign) {
		case 'Y':
		{
			return "1";
			break;
		}
		case 'N':
		{
			return "0";
			break;
		}
		default:
		{
			cout << "                            INCORRECT. THERE IS ONLY 2 OPTIONS : Y OR N . TRY AGAIN : " << endl;
			cin >> line;
			line = truecheck(line, amount);
			return line;
			break;
		}
		}
	}
}

// Check if the choice is a number
bool choice(int& number)
{
	cin >> number;
	while (cin.fail())
	{
		cout << "                            TRY AGAIN PUT A NUMBER OF THE OPTION " << std::endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> number;
	}
	return true;
}

// Check if the choice is a number and if it is lower
bool choiceforemp(int & number,int index)
{
	cin >> number;
	while (cin.fail()&& (number>index)&& (number<0))
	{
		cout << "                            TRY AGAIN PUT A NUMBER OF THE OPTION " << std::endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> number;
	}
	return true;
}

// Show kind of work
void kindofwork()
{
	cout << "                            CHOSE THE KIND OF WORK " << endl;
	cout << "                            AVAIABLE OPTIONS" << endl;
	cout << "                            1.SUPERVISE" << endl;
	cout << "                            2.CARPENTER" << endl;
	cout << "                            3.MANAGER" << endl;
	cout << "                            4.ACCOUNT" << endl;
	cout << "                            5.DRIVER" << endl;
	cout << "                            ENTER THE NUMBER:  ";
}


